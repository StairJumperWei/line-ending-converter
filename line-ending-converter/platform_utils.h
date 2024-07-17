#ifndef PLATFORM_UTILS_H
#define PLATFORM_UTILS_H

#define MAX_PATH_LENGTH 1024

#include <stdio.h>
#include <stdbool.h>

double current_time_ms();
void create_directory(const char* path);
bool is_directory(const char* path);
void process_directory(const char* input_dir, const char* output_dir, const char* new_line_ending, FILE* report);

#endif // PLATFORM_UTILS_H

