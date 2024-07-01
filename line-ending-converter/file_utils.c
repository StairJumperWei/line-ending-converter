#include <string.h>
#include "file_utils.h"

// 判断文件是否为隐藏文件或系统文件
int is_hidden_or_system_file(const char* path) {
    // 获取文件名
    const char* filename = strrchr(path, '/');
    if (!filename) {
        filename = path;
    }
    else {
        filename++;
    }

    // 忽略隐藏文件和目录（以点号开头）
    if (filename[0] == '.') {
        return 1;
    }

    // 忽略特定的系统目录和文件
    const char* system_dirs[] = {
        "System32", ".svn", ".ssh", ".gitconfig", NULL
    };
    for (int i = 0; system_dirs[i] != NULL; ++i) {
        if (strcmp(filename, system_dirs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}