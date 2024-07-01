#ifndef LINE_ENDING_CONVERTER_H
#define LINE_ENDING_CONVERTER_H

#define WINDOWS_EOL "\r\n"
#define UNIX_EOL "\n"

void convert_line_endings(FILE* src, FILE* dst, const char* new_line_ending);

#endif // LINE_ENDING_CONVERTER_H