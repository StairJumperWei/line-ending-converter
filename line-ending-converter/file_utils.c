#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>
#include "file_utils.h"

// �ж��ļ��Ƿ�Ϊ�����ļ���ϵͳ�ļ�
bool is_hidden_or_system_file(const char* path) {
    // ��ȡ�ļ���
    const char* filename = strrchr(path, '\\');
    if (!filename) {
        filename = path; // û���ҵ� '\\'��·�������ļ���
    }
    else {
        filename++; // ���� '\\'
    }

    // ���������ļ���Ŀ¼���Ե�ſ�ͷ��
    if (filename[0] == '.') {
        return true;
    }

    // �����ض���ϵͳĿ¼���ļ�
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

// �ж�·���Ƿ�Ϊ���ػ�ϵͳĿ¼
bool is_hidden_or_system_dir(const char* path) {
    // ��ȡĿ¼��
    const char* dirname = strrchr(path, '\\');
    if (!dirname) {
        dirname = path; // û���ҵ� '\\'��·������Ŀ¼��
    }
    else {
        dirname++; // ���� '\\'
    }

    // ��������Ŀ¼���Ե�ſ�ͷ��
    if (dirname[0] == '.') {
        return true;
    }

    // �����ض���ϵͳĿ¼
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
    DWORD attr = GetFileAttributesA(path);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        return false;
    }
    return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}