#include <stdio.h>
#include <windows.h>
#include <sys/timeb.h>
#include "file_utils.h"
#include "line_ending_converter.h"
#include "file_processor.h"

#define MAX_PATH_LENGTH 1024

// 获取文件的原始行结束符类型
const char* detect_line_ending(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) return "Unknown";

    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\r') {
            int next_c = fgetc(file);
            fclose(file);
            return (next_c == '\n') ? "CRLF" : "CR";
        }
        if (c == '\n') {
            fclose(file);
            return "LF";
        }
    }
    fclose(file);
    return "Unknown";
}

// 处理文件
void process_file(const char* input_file, const char* output_file, const char* new_line_ending, FILE* report) {
    struct _timeb start_time, end_time;
    ftime(&start_time);

    const char* original_line_ending = detect_line_ending(input_file);

    if (is_hidden_or_system_file(input_file)) {
        fprintf(report, "\"%s\",\"%s\",\"%s\",\"%s\",\"Skipped (hidden or system file)\",0\n",
            input_file, output_file, original_line_ending, original_line_ending);
        return;
    }

    FILE* src = fopen(input_file, "rb");
    if (!src) {
        fprintf(report, "\"%s\",\"%s\",\"%s\",\"%s\",\"Error (failed to open input file)\",0\n",
            input_file, output_file, original_line_ending, original_line_ending);
        perror("Failed to open input file");
        return;
    }

    FILE* dst = fopen(output_file, "wb");
    if (!dst) {
        fprintf(report, "\"%s\",\"%s\",\"%s\",\"%s\",\"Error (failed to open output file)\",0\n",
            input_file, output_file, original_line_ending, original_line_ending);
        perror("Failed to open output file");
        fclose(src);
        return;
    }

    convert_line_endings(src, dst, new_line_ending);

    fclose(src);
    fclose(dst);

    ftime(&end_time);
    double elapsed_time = 1000.0 * (end_time.time - start_time.time) + (end_time.millitm - start_time.millitm);

    fprintf(report, "\"%s\",\"%s\",\"%s\",\"%s\",\"Converted\",%.3f\n",
        input_file, output_file, original_line_ending, strcmp(new_line_ending, WINDOWS_EOL) == 0 ? "CRLF" : "LF", elapsed_time);
}

// 处理目录
void process_directory(const char* input_dir, const char* output_dir, const char* new_line_ending, FILE* report) {
    WIN32_FIND_DATAA find_data;
    char search_path[MAX_PATH_LENGTH];
    snprintf(search_path, sizeof(search_path), "%s\\*", input_dir);
    HANDLE hFind = FindFirstFileA(search_path, &find_data);

    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(report, "\"%s\",\"%s\",\"Unknown\",\"Unknown\",\"Error (failed to open directory)\",0\n",
            input_dir, output_dir);
        perror("Failed to open directory");
        return;
    }

    do {
        char input_path[MAX_PATH_LENGTH];
        char output_path[MAX_PATH_LENGTH];
        snprintf(input_path, sizeof(input_path), "%s\\%s", input_dir, find_data.cFileName);
        snprintf(output_path, sizeof(output_path), "%s\\%s", output_dir, find_data.cFileName);

        if (strcmp(find_data.cFileName, ".") == 0 || strcmp(find_data.cFileName, "..") == 0) {
            continue; // 跳过当前目录和父目录条目
        }

        if (is_hidden_or_system_dir(input_path)) {
            fprintf(report, "\"%s\",\"%s\",\"Unknown\",\"Unknown\",\"Skipped (hidden or system directory)\",0\n",
                input_path, output_path);
            continue;
        }

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            CreateDirectoryA(output_path, NULL);
            process_directory(input_path, output_path, new_line_ending, report);
        }
        else {
            process_file(input_path, output_path, new_line_ending, report);
        }
    } while (FindNextFileA(hFind, &find_data) != 0);

    FindClose(hFind);
}
