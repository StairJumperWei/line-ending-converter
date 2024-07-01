#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <stdio.h>

// 处理文件函数声明
void process_file(const char* input_file, const char* output_file, const char* new_line_ending, FILE* report);

// 处理目录函数声明
void process_directory(const char* input_dir, const char* output_dir, const char* new_line_ending, FILE* report);

#endif // FILE_PROCESSOR_H
