#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif
#include "arg_parser.h"
#include "file_processor.h"
#include "file_utils.h"

int main(int argc, char* argv[]) {
    char* input_path;
    char* output_path;
    const char* new_line_ending;

    // ���������в���
    parse_arguments(argc, argv, &input_path, &output_path, &new_line_ending);

    // ��ת�������ļ�
    FILE* report = fopen("conversion_report.csv", "w");
    if (!report) {
        perror("Failed to create report file");
        return EXIT_FAILURE;
    }

    // д�뱨���ļ��ı�ͷ
    fprintf(report, "\"Input File\",\"Output File\",\"Original EOL\",\"New EOL\",\"Status\",\"Duration (ms)\"\n");

    // �ж�����·����Ŀ¼�����ļ�
    if (is_directory(input_path)) {
#ifdef _WIN32
        _mkdir(output_path);  // �������Ŀ¼��Windows��
#else
        mkdir(output_path, 0755);  // �������Ŀ¼��POSIX��
#endif
        // ����Ŀ¼
        process_directory(input_path, output_path, new_line_ending, report);
    }
    else {
        // �������ļ�
        process_file(input_path, output_path, new_line_ending, report);
    }

    // �رձ����ļ�
    fclose(report);
    return EXIT_SUCCESS;
}
