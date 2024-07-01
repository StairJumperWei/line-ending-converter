#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// 转化换行符为指定系统的换行符
void convert_line_endings(FILE* src, FILE* dst, const char* new_line_ending) {
    char buffer[BUFFER_SIZE];
    size_t len = strlen(new_line_ending);

    while (fgets(buffer, BUFFER_SIZE, src)) {
        for (char* p = buffer; *p; ++p) {
            if (*p == '\r') {  // 检查是否为 '\r'
                if (*(p + 1) == '\n') {  // 检查是否为 '\r\n'
                    fputs(new_line_ending, dst);
                    ++p; // 跳过 '\n' 后的 '\r'
                }
                else {
                    fputs(new_line_ending, dst);
                }
            }
            else if (*p == '\n') {  // 检查是否为 '\n'
                fputs(new_line_ending, dst);
            }
            else {  // 其他字符直接写入目标文件
                fputc(*p, dst);
            }
        }
    }
}

// 处理文件，将其换行符转换为指定的格式
void process_file(const char* input_file, const char* output_file, const char* new_line_ending) {
    FILE* src = fopen(input_file, "rb");
    FILE* dst = fopen(output_file, "wb");
    if (!src) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }
    if (!dst) {
        perror("Failed to open output file");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    convert_line_endings(src, dst, new_line_ending);

    fclose(src);
    fclose(dst);
}

// 解析命令行参数
void parse_arguments(int argc, char* argv[], char** input_file, char** output_file, char** new_line_ending) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <system>\n", argv[0]);
        fprintf(stderr, "system options: Windows, Linux, macOS\n");
        exit(EXIT_FAILURE);
    }

    *input_file = argv[1];
    *output_file = argv[2];

    if (strcmp(argv[3], "Windows") == 0) {
        *new_line_ending = "\r\n";
    }
    else if (strcmp(argv[3], "Linux") == 0) {
        *new_line_ending = "\n";
    }
    else if (strcmp(argv[3], "macOS") == 0) {
        *new_line_ending = "\n";
    }
    else {
        fprintf(stderr, "Invalid system. Use Windows, Linux, or macOS.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    char* input_file;
    char* output_file;
    char* new_line_ending;

    parse_arguments(argc, argv, &input_file, &output_file, &new_line_ending);  // 解析命令行参数
    process_file(input_file, output_file, new_line_ending);  // 处理文件

    return 0;
}