#include <string.h>
#include "file_utils.h"

// �ж��ļ��Ƿ�Ϊ�����ļ���ϵͳ�ļ�
int is_hidden_or_system_file(const char* path) {
    // ��ȡ�ļ���
    const char* filename = strrchr(path, '/');
    if (!filename) {
        filename = path;
    }
    else {
        filename++;
    }

    // ���������ļ���Ŀ¼���Ե�ſ�ͷ��
    if (filename[0] == '.') {
        return 1;
    }

    // �����ض���ϵͳĿ¼���ļ�
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