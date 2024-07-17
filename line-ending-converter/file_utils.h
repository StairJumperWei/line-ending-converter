#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>

bool is_hidden_or_system_file(const char* path);
bool is_hidden_or_system_dir(const char* path);
bool is_text_file(const char* path); 

#endif // FILE_UTILS_H
