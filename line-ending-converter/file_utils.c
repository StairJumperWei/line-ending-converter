#include <stdbool.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#endif
#include "file_utils.h"

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
