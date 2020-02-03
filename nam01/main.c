#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <Windows.h>

struct _finddata_t fd;

int file(file_pt) {
    FILE* output;
    int ch; // 문자를 저장할 변수

    fopen_s(&output, file_pt, "r");
    if (output == NULL) {
        printf("파일 없음\n");

        return 1;
    }

    while (1)
    {
        ch = fgetc(output); // 파일에서 문자 입력
        if (ch == EOF) {
            printf("\n");
            break;
        }
        putchar(ch); // 화면에 문자 출력
    }

    fclose(output);
}

int isFileOrDir()
{
    if (fd.attrib & _A_SUBDIR)
        return 0; // 디렉토리면 0 반환
    else
        return 1; // 그밖의 경우는 "존재하는 파일"이기에 1 반환

}

void FileSearch(char file_path[])
{
    intptr_t handle;
    int check = 0;
    char file_path2[_MAX_PATH];

    strcat(file_path, "\\");  // file_path 뒤에 \\를 붙임
    strcpy(file_path2, file_path); // file_path의 문자열을 file_path2로 복사
    strcat(file_path, "*");

    if ((handle = _findfirst(file_path, &fd)) == -1)
    {
        printf("No such file or directory\n");
        return;
    }

    while (_findnext(handle, &fd) == 0)
    {
        char file_pt[_MAX_PATH];
        strcpy(file_pt, file_path2);
        strcat(file_pt, fd.name);

        check = isFileOrDir();    //파일인지 디렉토리 인지 식별

        if (check == 0 && fd.name[0] != '.')
        {
            FileSearch(file_pt);    //하위 디렉토리 검색 재귀함수
        }
        else if (check == 1 && fd.size != 0 && fd.name[0] != '.')
        {
            printf("파일명 : %s\n", file_pt);
            file(file_pt);
        }
    }

    _findclose(handle);
}

int main()
{
    while (1) {
        char file_path[_MAX_PATH] = "C:\\Document";    //file_path는 경로
        FileSearch(file_path);
    }

    return 0;
}