#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "file_utils.h"
#include "line_ending_converter.h"
#include "arg_parser.h"

#define MAX_PATH_LENGTH 1024

// 处理文件
void process_file(const char* input_file, const char* output_file, const char* new_line_ending) {
    if (is_hidden_or_system_file(input_file)) {
        printf("Skipping hidden or system file: %s\n", input_file);
        return;
    }

    FILE* src = fopen(input_file, "rb");
    if (!src) {
        perror("Failed to open input file");
        return;
    }

    FILE* dst = fopen(output_file, "wb");
    if (!dst) {
        perror("Failed to open output file");
        fclose(src);
        return;
    }

    convert_line_endings(src, dst, new_line_ending);

    fclose(src);
    fclose(dst);

    printf("Converted: %s -> %s\n", input_file, output_file);
}

// 处理目录
void process_directory(const char* input_dir, const char* output_dir, const char* new_line_ending) {
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
            continue; // 跳过当前目录和父目录条目
        }

        if (is_hidden_or_system_dir(input_path)) {
            printf("Skipping hidden or system directory: %s\n", input_path);
            continue;
        }

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            CreateDirectoryA(output_path, NULL);
            process_directory(input_path, output_path, new_line_ending);
        }
        else {
            process_file(input_path, output_path, new_line_ending);
        }
    } while (FindNextFileA(hFind, &find_data) != 0);

    FindClose(hFind);
}

int main(int argc, char* argv[]) {
    char* input_path;
    char* output_path;
    const char* new_line_ending;

    parse_arguments(argc, argv, &input_path, &output_path, &new_line_ending);

    if (is_directory(input_path)) {
        CreateDirectoryA(output_path, NULL);
        process_directory(input_path, output_path, new_line_ending);
    }
    else {
        process_file(input_path, output_path, new_line_ending);
    }

    return 0;
}
