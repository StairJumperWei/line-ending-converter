#include <stdio.h>
#include "line_ending_converter.h"

// 转换文件中的行结束符
void convert_line_endings(FILE* src, FILE* dst, const char* new_line_ending) {
    int c;
    while ((c = fgetc(src)) != EOF) {
        if (c == '\r') {
            continue; // 忽略 '\r'
        }
        else if (c == '\n') {
            fputs(new_line_ending, dst); // 输出新的行结束符
        }
        else {
            fputc(c, dst); // 输出其他字符
        }
    }
}
