#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>
#include "file_utils.h"

// 判断文件是否为隐藏文件或系统文件
bool is_hidden_or_system_file(const char* path) {
    // 获取文件名
    const char* filename = strrchr(path, '\\');
    if (!filename) {
        filename = path; // 没有找到 '\\'，路径就是文件名
    }
    else {
        filename++; // 跳过 '\\'
    }

    // 忽略隐藏文件和目录（以点号开头）
    if (filename[0] == '.') {
        return true;
    }

    // 忽略特定的系统目录和文件
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

// 判断路径是否为隐藏或系统目录
bool is_hidden_or_system_dir(const char* path) {
    // 获取目录名
    const char* dirname = strrchr(path, '\\');
    if (!dirname) {
        dirname = path; // 没有找到 '\\'，路径就是目录名
    }
    else {
        dirname++; // 跳过 '\\'
    }

    // 忽略隐藏目录（以点号开头）
    if (dirname[0] == '.') {
        return true;
    }

    // 忽略特定的系统目录
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

// 判断路径是否为目录
bool is_directory(const char* path) {
    DWORD attr = GetFileAttributesA(path);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        return false;
    }
    return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}