#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"
#include "line_ending_converter.h"
#include "arg_parser.h"
#include "file_processor.h"

#define REPORT_FILE "conversion_report.csv"

int main(int argc, char* argv[]) {
    char* input_path;
    char* output_path;
    const char* new_line_ending;

    // ���������в���
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_path> <output_path> <system>\n", argv[0]);
        fprintf(stderr, "System options: Windows, Linux, macOS\n");
        return EXIT_FAILURE;
    }

    input_path = argv[1];
    output_path = argv[2];

    if (strcmp(argv[3], "Windows") == 0) {
        new_line_ending = WINDOWS_EOL;
    }
    else if (strcmp(argv[3], "Linux") == 0 || strcmp(argv[3], "macOS") == 0) {
        new_line_ending = UNIX_EOL;
    }
    else {
        fprintf(stderr, "Invalid system. Use Windows, Linux, or macOS.\n");
        return EXIT_FAILURE;
    }

    // �򿪱����ļ�
    FILE* report = fopen(REPORT_FILE, "w");
    if (!report) {
        perror("Failed to open report file");
        return EXIT_FAILURE;
    }

    // д��CSV�ļ��ı�ͷ
    fprintf(report, "Source File,Destination File,Original Line Ending,New Line Ending,Result,Time Elapsed (ms)\n");

    // �������·����Ŀ¼������Ŀ¼
    if (is_directory(input_path)) {
        CreateDirectoryA(output_path, NULL);
        process_directory(input_path, output_path, new_line_ending, report);
    }
    else {
        // �������·�����ļ��������ļ�
        process_file(input_path, output_path, new_line_ending, report);
    }

    fclose(report);
    printf("Conversion report saved to %s\n", REPORT_FILE);

    return EXIT_SUCCESS;
}
