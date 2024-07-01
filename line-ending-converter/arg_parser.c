#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg_parser.h"
#include "line_ending_converter.h"

// 解析命令行参数
void parse_arguments(int argc, char* argv[], char** input_path, char** output_path, const char** new_line_ending) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_path> <output_path> <system>\n", argv[0]);
        fprintf(stderr, "system options: Windows, Linux, macOS\n");
        exit(EXIT_FAILURE);
    }

    *input_path = argv[1];
    *output_path = argv[2];

    if (strcmp(argv[3], "Windows") == 0) {
        *new_line_ending = WINDOWS_EOL;
    }
    else if (strcmp(argv[3], "Linux") == 0 || strcmp(argv[3], "macOS") == 0) {
        *new_line_ending = UNIX_EOL;
    }
    else {
        fprintf(stderr, "Invalid system. Use Windows, Linux, or macOS.\n");
        exit(EXIT_FAILURE);
    }
}