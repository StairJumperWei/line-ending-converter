#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include "line_ending_converter.h"
#include "arg_parser.h"
#include "file_processor.h"

int main(int argc, char* argv[]) {
    char* input_path;
    char* output_path;
    const char* new_line_ending;

    // 解析命令行参数
    parse_arguments(argc, argv, &input_path, &output_path, &new_line_ending);

    // 如果输入路径是目录，则处理目录
    if (is_directory(input_path)) {
        CreateDirectoryA(output_path, NULL);
        process_directory(input_path, output_path, new_line_ending);
    }
    else {
        // 如果输入路径是文件，则处理文件
        process_file(input_path, output_path, new_line_ending);
    }

    return 0;
}
