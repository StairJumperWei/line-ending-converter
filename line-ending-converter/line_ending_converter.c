#include <stdio.h>
#include "line_ending_converter.h"

void convert_line_endings(FILE* src, FILE* dst, const char* new_line_ending) {
    int c;
    while ((c = fgetc(src)) != EOF) {
        if (c == '\r') {
            // 忽略 \r
            continue;
        }
        else if (c == '\n') {
            // 输出新的换行符
            fputs(new_line_ending, dst);
        }
        else {
            // 输出其他字符
            fputc(c, dst);
        }
    }
}