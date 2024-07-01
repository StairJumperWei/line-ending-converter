#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include <locale.h>
#include <wchar.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

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

    if (filename[0] == '.') {
        return true;
    }

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

    if (dirname[0] == '.') {
        return true;
    }

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

bool is_directory(const char* path) {
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        return false;
    }
    return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
    struct stat st;
    if (stat(path, &st) != 0) {
        return false;
    }
    return S_ISDIR(st.st_mode);
#endif
}

bool is_text_file(const char* path) {
    setlocale(LC_ALL, "en_US.UTF-8");

    FILE* file = fopen(path, "rb");
    if (!file) {
        return false;
    }

    int c;
    bool is_text = true;

    while ((c = fgetc(file)) != EOF) {
        // Check for control characters excluding common ones like '\n', '\r', '\t'
        if ((c < 32 && c != '\n' && c != '\r' && c != '\t') || c == 127) {
            is_text = false;
            break;
        }

        // Check if the character is a valid printable ASCII character
        if (c < 128 && !isprint(c) && c != '\n' && c != '\r' && c != '\t') {
            is_text = false;
            break;
        }
    }

    fclose(file);
    return is_text;
}