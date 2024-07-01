#include <stdio.h>
#include "line_ending_converter.h"

void convert_line_endings(FILE* src, FILE* dst, const char* new_line_ending) {
    int c;
    while ((c = fgetc(src)) != EOF) {
        if (c == '\r') {
            continue;
        }
        else if (c == '\n') {
            fputs(new_line_ending, dst);
        }
        else {
            fputc(c, dst);
        }
    }
}
