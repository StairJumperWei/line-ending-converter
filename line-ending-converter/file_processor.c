#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#endif
#include "file_utils.h"
#include "line_ending_converter.h"
#include "file_processor.h"

#ifdef _WIN32
// Windows 平台上的高精度时间测量函数
static double current_time_ms() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER now;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&now);
    return (double)now.QuadPart / frequency.QuadPart * 1000.0;
}
#else
// POSIX 系统上的高精度时间测量函数
static double current_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
}
#endif

// 处理文件
void process_file(const char* input_file, const char* output_file, const char* new_line_ending, FILE* report) {
    double start_time = current_time_ms();
    char original_line_ending[10] = "";

    // 如果是隐藏或系统文件，则跳过
    if (is_hidden_or_system_file(input_file)) {
        fprintf(report, "\"%s\",\"%s\",\"N/A\",\"N/A\",\"Skipped (hidden/system file)\",\"0.0000\"\n", input_file, output_file);
        return;
    }

    // 打开输入文件
    FILE* src = fopen(input_file, "rb");
    if (!src) {
        perror("Failed to open input file");
        fprintf(report, "\"%s\",\"%s\",\"N/A\",\"N/A\",\"Error (failed to open input file)\",\"0.0000\"\n", input_file, output_file);
        return;
    }

    // 打开输出文件
    FILE* dst = fopen(output_file, "wb");
    if (!dst) {
        perror("Failed to open output file");
        fclose(src);
        fprintf(report, "\"%s\",\"%s\",\"N/A\",\"N/A\",\"Error (failed to open output file)\",\"0.0000\"\n", input_file, output_file);
        return;
    }

    // 检测原始的换行符类型
    int c;
    while ((c = fgetc(src)) != EOF) {
        if (c == '\r') {
#ifdef _WIN32
            strcpy_s(original_line_ending, sizeof(original_line_ending), "CRLF");
#else
            strcpy(original_line_ending, "CRLF");
#endif
            int next_c = fgetc(src);
            if (next_c != '\n') {
                ungetc(next_c, src);
            }
            break;
        }
        else if (c == '\n') {
#ifdef _WIN32
            strcpy_s(original_line_ending, sizeof(original_line_ending), "LF");
#else
            strcpy(original_line_ending, "LF");
#endif
            break;
        }
    }
    rewind(src); // 重置文件指针到文件开头

    // 转换行结束符
    convert_line_endings(src, dst, new_line_ending);

    // 关闭文件
    fclose(src);
    fclose(dst);

    double end_time = current_time_ms();
    double duration = end_time - start_time;

    fprintf(report, "\"%s\",\"%s\",\"%s\",\"%s\",\"Converted\",\"%.4f\"\n", input_file, output_file, original_line_ending, (strcmp(new_line_ending, "\r\n") == 0) ? "CRLF" : "LF", duration);
}

// 处理目录
void process_directory(const char* input_dir, const char* output_dir, const char* new_line_ending, FILE* report) {
#ifdef _WIN32
    WIN32_FIND_DATAA find_data;
    char search_path[MAX_PATH_LENGTH];
    snprintf(search_path, sizeof(search_path), "%s\\*", input_dir);
    HANDLE hFind = FindFirstFileA(search_path, &find_data);

    if (hFind == INVALID_HANDLE_VALUE) {
        perror("Failed to open directory");
        return;
    }

    do {
        char input_path[MAX_PATH_LENGTH];
        char output_path[MAX_PATH_LENGTH];
        snprintf(input_path, sizeof(input_path), "%s\\%s", input_dir, find_data.cFileName);
        snprintf(output_path, sizeof(output_path), "%s\\%s", output_dir, find_data.cFileName);

        if (strcmp(find_data.cFileName, ".") == 0 || strcmp(find_data.cFileName, "..") == 0) {
            continue;
        }

        if (is_hidden_or_system_dir(input_path)) {
            fprintf(report, "\"%s\",\"%s\",\"N/A\",\"N/A\",\"Skipped (hidden/system directory)\",\"0.0000\"\n", input_path, output_path);
            continue;
        }

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            _mkdir(output_path);
            process_directory(input_path, output_path, new_line_ending, report);
        }
        else {
            process_file(input_path, output_path, new_line_ending, report);
        }
    } while (FindNextFileA(hFind, &find_data) != 0);

    FindClose(hFind);
#else
    DIR* dir = opendir(input_dir);
    if (!dir) {
        perror("Failed to open directory");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        char input_path[MAX_PATH_LENGTH];
        char output_path[MAX_PATH_LENGTH];
        snprintf(input_path, sizeof(input_path), "%s/%s", input_dir, entry->d_name);
        snprintf(output_path, sizeof(output_path), "%s/%s", output_dir, entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (is_hidden_or_system_dir(input_path)) {
            fprintf(report, "\"%s\",\"%s\",\"N/A\",\"N/A\",\"Skipped (hidden/system directory)\",\"0.0000\"\n", input_path, output_path);
            continue;
        }

        if (entry->d_type == DT_DIR) {
            mkdir(output_path, 0755);
            process_directory(input_path, output_path, new_line_ending, report);
        }
        else {
            process_file(input_path, output_path, new_line_ending, report);
        }
    }
    closedir(dir);
#endif
}
