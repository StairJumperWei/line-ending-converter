#include "platform_utils.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif

// Windows 平台上的高精度时间测量函数
double current_time_ms() {
#ifdef _WIN32
    LARGE_INTEGER frequency;
    LARGE_INTEGER now;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&now);
    return (double)now.QuadPart / frequency.QuadPart * 1000.0;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
#endif
}

// 创建目录
void create_directory(const char* path) {
#ifdef _WIN32
    _mkdir(path);
#else
    mkdir(path, 0755);
#endif
}

// 判断路径是否为目录
bool is_directory(const char* path) {
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        return false;
    }
    return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
    struct stat st;
    if (stat(path, &st) != 0) {
        return false;
    }
    return S_ISDIR(st.st_mode);
#endif
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
            fprintf(report, "\"%s\",\"%s\",\"N/A\",\"N/A\",\"Skipped (hidden/system directory/not text file)\",\"0.0000\"\n", input_path, output_path);
            continue;
        }

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            create_directory(output_path);
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

        if (is_hidden_or_system_dir(input_path) || !is_text_file(input_path)) {
            fprintf(report, "\"%s\",\"%s\",\"N/A\",\"N/A\",\"Skipped (hidden/system directory/not text file)\",\"0.0000\"\n", input_path, output_path);
            continue;
        }

        if (entry->d_type == DT_DIR) {
            create_directory(output_path);
            process_directory_platform(input_path, output_path, new_line_ending, report);
        }
        else {
            process_file(input_path, output_path, new_line_ending, report);
        }
    }
    closedir(dir);
#endif
}