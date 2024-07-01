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

    // ���������в���
    parse_arguments(argc, argv, &input_path, &output_path, &new_line_ending);

    // �������·����Ŀ¼������Ŀ¼
    if (is_directory(input_path)) {
        CreateDirectoryA(output_path, NULL);
        process_directory(input_path, output_path, new_line_ending);
    }
    else {
        // �������·�����ļ��������ļ�
        process_file(input_path, output_path, new_line_ending);
    }

    return 0;
}
