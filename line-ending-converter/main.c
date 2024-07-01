#include <stdio.h>
#include "file_utils.h"
#include "line_ending_converter.h"
#include "arg_parser.h"

int main(int argc, char* argv[]) {
    char* input_file;
    char* output_file;
    const char* new_line_ending;

    parse_arguments(argc, argv, &input_file, &output_file, &new_line_ending);

    if (is_hidden_or_system_file(input_file)) {
        printf("Skipping hidden or system file: %s\n", input_file);
        return 0;
    }

    FILE* src = fopen(input_file, "rb");
    if (!src) {
        perror("Failed to open input file");
        return 1;
    }

    FILE* dst = fopen(output_file, "wb");
    if (!dst) {
        perror("Failed to open output file");
        fclose(src);
        return 1;
    }

    convert_line_endings(src, dst, new_line_ending);

    fclose(src);
    fclose(dst);

    return 0;
}