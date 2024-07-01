#include <stdio.h>
#include "line_ending_converter.h"

// ת���ļ����н�β��
void convert_line_endings(FILE* src, FILE* dst, const char* new_line_ending) {
    int c;
    // ���ַ���ȡ�����ļ�����
    while ((c = fgetc(src)) != EOF) {
        if (c == '\r') {
            // ����'\r'�ַ���Windows�н������ĵ�һ���֣�
            continue;
        }
        else if (c == '\n') {
            // ��'\n'ת��Ϊָ�������н�β��
            fputs(new_line_ending, dst);
        }
        else {
            // �����н������ַ�ֱ��д������ļ�
            fputc(c, dst);
        }
    }
}
