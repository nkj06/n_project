/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수
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
    위에서 struct _finddata_t 는 MS사에서 제공하는 구조체
    자료형으로서 파일 정보 관리를 위한 자료형 입니다.
*/

struct NO { // 파일이름 저장하기 위한 구조체
    char n[100];
};

int i; // 반복 변수 
struct NO no[100]; // 중복 파일 확인을 위한 변수 
int count = 0; // 파일 개수 확인용 변수

int file(file_pt) { // .txt파일 출력

    FILE* output;
    int ch; // 문자를 저장할 변수

    fopen_s(&output, file_pt, "r"); // 여기서 file_pt는 파일 경로
    if (output == NULL) {
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
    char file_path2[100];

    strcat(file_path, "\\");  // file_path 뒤에 \\를 붙임
    strcpy(file_path2, file_path); // file_path의 문자열을 file_path2로 복사
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

        check = isFileOrDir();    //파일인지 디렉토리 인지 식별

        if (check == 0 && fd.name[0] != '.')
        {
            FileSearch(file_pt);    //하위 디렉토리 검색 재귀함수
        }

        else if (check == 1 && fd.size != 0 && fd.name[0] != '.')
        {
            int nameCheck = 0;

            for (i = 0; i < count; i++) // 체크
            {
                if (strcmp(no[i].n, fd.name) == 0) // 같으면 0 
                {
                    nameCheck = 1;
                    break;
                }
            }

            if (nameCheck == 1) // 같은게 있다면 패스
            {
                continue;
            }

            if (strstr(fd.name, ".txt")) // txt 파일이 있는가 확인
            {
                strcpy(no[count].n, fd.name); // 배열에 복사해 넣기
                count++; // 증가시켜

                printf("파일명 : %s\n", fd.name);
                file(file_pt);

            }
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