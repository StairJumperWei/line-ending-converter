#include <stdio.h>
#include "line_ending_converter.h"

// ת���ļ��е��н�����
void convert_line_endings(FILE* src, FILE* dst, const char* new_line_ending) {
    int c;
    while ((c = fgetc(src)) != EOF) {
        if (c == '\r') {
            continue; // ���� '\r'
        }
        else if (c == '\n') {
            fputs(new_line_ending, dst); // ����µ��н�����
        }
        else {
            fputc(c, dst); // ��������ַ�
        }
    }
}
