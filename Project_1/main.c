/*
  filename - main.c
  version - 1.0
  description - �⺻ ���� �Լ�
  --------------------------------------------------------------------------------
  first created - 2020.02.03
  writer - Nam Kyung Jin
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

struct _finddata_t fd;
/*
    ������ struct _finddata_t �� MS�翡�� �����ϴ� ����ü
    �ڷ������μ� ���� ���� ������ ���� �ڷ��� �Դϴ�.
*/

struct NO { // �����̸� �����ϱ� ���� ����ü
    char n[100];
};

int i; // �ݺ� ���� 
struct NO no[100]; // �ߺ� ���� Ȯ���� ���� ���� 
int count = 0; // ���� ���� Ȯ�ο� ����

int file(file_pt) { // .txt���� ���

    FILE* output;
    int ch; // ���ڸ� ������ ����

    fopen_s(&output, file_pt, "r"); // ���⼭ file_pt�� ���� ���
    if (output == NULL) {
        return 1;
    }

    while (1)
    {
        ch = fgetc(output); // ���Ͽ��� ���� �Է�
        if (ch == EOF) {
            printf("\n");
            break;
        }
        putchar(ch); // ȭ�鿡 ���� ���
    }

    fclose(output);
}

int isFileOrDir()
{
    if (fd.attrib & _A_SUBDIR)
        return 0; // ���丮�� 0 ��ȯ
    else
        return 1; // �׹��� ���� "�����ϴ� ����"�̱⿡ 1 ��ȯ

}

void FileSearch(char file_path[])
{
    intptr_t handle;
    int check = 0;
    char file_path2[100];

    strcat(file_path, "\\");  // file_path �ڿ� \\�� ����
    strcpy(file_path2, file_path); // file_path�� ���ڿ��� file_path2�� ����
    strcat(file_path, "*");

    if ((handle = _findfirst(file_path, &fd)) == -1)
    {
        return;
    }

    while (_findnext(handle, &fd) == 0)
    {
        char file_pt[100];
        strcpy(file_pt, file_path2);
        strcat(file_pt, fd.name);

        check = isFileOrDir();    //�������� ���丮 ���� �ĺ�

        if (check == 0 && fd.name[0] != '.')
        {
            FileSearch(file_pt);    //���� ���丮 �˻� ����Լ�
        }

        else if (check == 1 && fd.size != 0 && fd.name[0] != '.')
        {
            int nameCheck = 0;

            for (i = 0; i < count; i++) // üũ
            {
                if (strcmp(no[i].n, fd.name) == 0) // ������ 0 
                {
                    nameCheck = 1;
                    break;
                }
            }

            if (nameCheck == 1) // ������ �ִٸ� �н�
            {
                continue;
            }

            if (strstr(fd.name, ".txt")) // txt ������ �ִ°� Ȯ��
            {
                strcpy(no[count].n, fd.name); // �迭�� ������ �ֱ�
                count++; // ��������

                printf("���ϸ� : %s\n", fd.name);
                file(file_pt);

            }
        }
    }

    _findclose(handle);
}

int main()
{
    while (1) {
        char file_path[_MAX_PATH] = "C:\\Document";    //file_path�� ���
        FileSearch(file_path);
    }

    return 0;
}