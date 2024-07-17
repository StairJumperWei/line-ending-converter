#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include "platform_utils.h"

// 判断文件是否为隐藏文件或系统文件
bool is_hidden_or_system_file(const char* path) {
    const char* filename = strrchr(path, '/');
    if (!filename) {
        filename = strrchr(path, '\\');
    }
    if (!filename) {
        filename = path;
    }
    else {
        filename++;
    }

    // 检查文件名是否以点号开头
    if (filename[0] == '.') {
        return true;
    }

    // 定义一些常见的系统文件
    const char* system_files[] = {
        "System32", ".svn", ".ssh", ".gitconfig", NULL
    };
    for (int i = 0; system_files[i] != NULL; ++i) {
        if (strcmp(filename, system_files[i]) == 0) {
            return true;
        }
    }
    return false;
}

// 判断目录是否为隐藏目录或系统目录
bool is_hidden_or_system_dir(const char* path) {
    const char* dirname = strrchr(path, '/');
    if (!dirname) {
        dirname = strrchr(path, '\\');
    }
    if (!dirname) {
        dirname = path;
    }
    else {
        dirname++;
    }

    // 检查目录名是否以点号开头
    if (dirname[0] == '.') {
        return true;
    }

    // 定义一些常见的系统目录
    const char* system_dirs[] = {
        "System32", ".svn", ".ssh", ".gitconfig", NULL
    };
    for (int i = 0; system_dirs[i] != NULL; ++i) {
        if (strcmp(dirname, system_dirs[i]) == 0) {
            return true;
        }
    }
    return false;
}

// 判断文件是否为纯文本文件
bool is_text_file(const char* path) {

    FILE* file = fopen(path, "rb");
    if (!file) {
        return false;
    }

    int c;
    bool is_text = true;

    // 逐字节检查文件内容
    while ((c = fgetc(file)) != EOF) {
        // 检查控制字符，排除常见的换行符、回车符和制表符
        if ((c < 32 && c != '\n' && c != '\r' && c != '\t') || c == 127) {
            is_text = false;
            break;
        }

        // 检查字符是否为有效的可打印ASCII字符
        if (c < 128 && !isprint(c) && c != '\n' && c != '\r' && c != '\t') {
            is_text = false;
            break;
        }
    }

    fclose(file);
    return is_text;
}
