#include <stdio.h>
#include "line_ending_converter.h"

// 转换文件的行结尾符
void convert_line_endings(FILE* src, FILE* dst, const char* new_line_ending) {
    int c;
    // 逐字符读取输入文件内容
    while ((c = fgetc(src)) != EOF) {
        if (c == '\r') {
            // 跳过'\r'字符（Windows行结束符的第一部分）
            continue;
        }
        else if (c == '\n') {
            // 将'\n'转换为指定的新行结尾符
            fputs(new_line_ending, dst);
        }
        else {
            // 将非行结束符字符直接写入输出文件
            fputc(c, dst);
        }
    }
}
