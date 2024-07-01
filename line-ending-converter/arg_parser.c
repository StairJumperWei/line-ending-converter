#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg_parser.h"
#include "line_ending_converter.h"

// 解析命令行参数函数
void parse_arguments(int argc, char* argv[], char** input_path, char** output_path, const char** new_line_ending) {
    // 如果参数数量不等于4，则打印用法提示并退出程序
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_path> <output_path> <system>\n", argv[0]);
        fprintf(stderr, "system options: Windows, Linux, macOS\n");
        exit(EXIT_FAILURE);
    }

    *input_path = argv[1];  // 获取输入文件路径
    *output_path = argv[2]; // 获取输出文件路径

    // 根据系统类型设置新的行结尾符
    if (strcmp(argv[3], "Windows") == 0) {
        *new_line_ending = WINDOWS_EOL; // Windows系统的行结尾符
    }
    else if (strcmp(argv[3], "Linux") == 0 || strcmp(argv[3], "macOS") == 0) {
        *new_line_ending = UNIX_EOL; // Linux和macOS系统的行结尾符
    }
    else {
        fprintf(stderr, "Invalid system. Use Windows, Linux, or macOS.\n"); // 无效的系统类型提示
        exit(EXIT_FAILURE);
    }
}
