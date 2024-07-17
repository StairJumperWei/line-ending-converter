#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"
#include "file_processor.h"
#include "platform_utils.h"

// 处理文件
void process_file(const char* input_file, const char* output_file, const char* new_line_ending, FILE* report) {
    double start_time = current_time_ms();
    char original_line_ending[10] = "";

    // 如果是隐藏或系统文件或者非纯文本文件，则跳过
    if (is_hidden_or_system_file(input_file) || !is_text_file(input_file)) {
        fprintf(report, "\"%s\",\"%s\",\"N/A\",\"N/A\",\"Skipped (hidden/system file/not text file)\",\"0.0000\"\n", input_file, output_file);
        return;
    }

    // 打开输入文件
    FILE* src = fopen(input_file, "rb");
    if (!src) {
        perror("Failed to open input file");
        fprintf(report, "\"%s\",\"%s\",\"N/A\",\"N/A\",\"Error (failed to open input file)\",\"0.0000\"\n", input_file, output_file);
        return;
    }

    // 打开输出文件
    FILE* dst = fopen(output_file, "wb");
    if (!dst) {
        perror("Failed to open output file");
        fclose(src);
        fprintf(report, "\"%s\",\"%s\",\"N/A\",\"N/A\",\"Error (failed to open output file)\",\"0.0000\"\n", input_file, output_file);
        return;
    }

    // 检测原始的换行符类型
    int c;
    while ((c = fgetc(src)) != EOF) {
        if (c == '\r') {
            strcpy(original_line_ending,"CRLF");
            int next_c = fgetc(src);
            if (next_c != '\n') {
                ungetc(next_c, src);
            }
            break;
        }
        else if (c == '\n') {
            strcpy(original_line_ending, "LF");
            break;
        }
    }
    rewind(src); // 重置文件指针到文件开头

    // 转换行结束符
    convert_line_endings(src, dst, new_line_ending);

    // 关闭文件
    fclose(src);
    fclose(dst);

    double end_time = current_time_ms();
    double duration = end_time - start_time;

    fprintf(report, "\"%s\",\"%s\",\"%s\",\"%s\",\"Converted\",\"%.4f\"\n", input_file, output_file, original_line_ending, (strcmp(new_line_ending, "\r\n") == 0) ? "CRLF" : "LF", duration);
}


