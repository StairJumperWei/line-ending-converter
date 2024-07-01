#include <string.h>
#include "line_ending_converter.h"

const char* WINDOWS_EOL = "\r\n";
const char* UNIX_EOL = "\n";

// 转换文件中的换行符
void convert_line_endings(FILE* src, FILE* dst, const char* new_line_ending) {
    char buffer[BUFFER_SIZE];
    size_t len = strlen(new_line_ending);

    while (fgets(buffer, BUFFER_SIZE, src)) {
        for (char* p = buffer; *p; ++p) {
            if (*p == '\r') {
                if (*(p + 1) == '\n') {
                    fputs(new_line_ending, dst);
                    ++p; // 跳过 '\n'
                }
                else {
                    fputs(new_line_ending, dst);
                }
            }
            else if (*p == '\n') {
                fputs(new_line_ending, dst);
            }
            else {
                fputc(*p, dst);
            }
        }
    }
}