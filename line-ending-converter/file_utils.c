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

// �ж��ļ��Ƿ�Ϊ�����ļ���ϵͳ�ļ�
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

    // ����ļ����Ƿ��Ե�ſ�ͷ
    if (filename[0] == '.') {
        return true;
    }

    // ����һЩ������ϵͳ�ļ�
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

// �ж�Ŀ¼�Ƿ�Ϊ����Ŀ¼��ϵͳĿ¼
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

    // ���Ŀ¼���Ƿ��Ե�ſ�ͷ
    if (dirname[0] == '.') {
        return true;
    }

    // ����һЩ������ϵͳĿ¼
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

// �ж�·���Ƿ�ΪĿ¼
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

// �ж��ļ��Ƿ�Ϊ���ı��ļ�
bool is_text_file(const char* path) {
    setlocale(LC_ALL, "en_US.UTF-8");

    FILE* file = fopen(path, "rb");
    if (!file) {
        return false;
    }

    int c;
    bool is_text = true;

    // ���ֽڼ���ļ�����
    while ((c = fgetc(file)) != EOF) {
        // �������ַ����ų������Ļ��з����س������Ʊ��
        if ((c < 32 && c != '\n' && c != '\r' && c != '\t') || c == 127) {
            is_text = false;
            break;
        }

        // ����ַ��Ƿ�Ϊ��Ч�Ŀɴ�ӡASCII�ַ�
        if (c < 128 && !isprint(c) && c != '\n' && c != '\r' && c != '\t') {
            is_text = false;
            break;
        }
    }

    fclose(file);
    return is_text;
}
