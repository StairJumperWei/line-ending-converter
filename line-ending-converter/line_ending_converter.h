#ifndef LINE_ENDING_CONVERTER_H
#define LINE_ENDING_CONVERTER_H

#include <stdio.h>

#define BUFFER_SIZE 1024

extern const char* WINDOWS_EOL;
extern const char* UNIX_EOL;

void convert_line_endings(FILE* src, FILE* dst, const char* new_line_ending);

#endif // LINE_ENDING_CONVERTER_H