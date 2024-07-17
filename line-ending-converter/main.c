#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg_parser.h"
#include "file_processor.h"
#include "file_utils.h"
#include "platform_utils.h"

int main(int argc, char* argv[]) {
    char* input_path;
    char* output_path;
    const char* new_line_ending;

    // 解析命令行参数
    parse_arguments(argc, argv, &input_path, &output_path, &new_line_ending);

    // 打开转换报告文件
    FILE* report = fopen("conversion_report.csv", "w");
    if (!report) {
        perror("Failed to create report file");
        return EXIT_FAILURE;
    }

    // 写入报告文件的表头
    fprintf(report, "\"Input File\",\"Output File\",\"Original EOL\",\"New EOL\",\"Status\",\"Duration (ms)\"\n");

    // 判断输入路径是目录还是文件
    int status = is_directory(input_path);
    if (status) {
        create_directory(output_path);
        // 处理目录
        process_directory(input_path, output_path, new_line_ending, report);
    }
    else {
        // 处理单个文件
        process_file(input_path, output_path, new_line_ending, report);
    }

    // 关闭报告文件
    fclose(report);
    return EXIT_SUCCESS;
}
