#include <windows.h>
#include <stdio.h>

int main() {

    SYSTEMTIME localTime;
    SYSTEMTIME SysTime;

    GetSystemTime(&SysTime);
    GetLocalTime(&localTime);

    printf("[�ý��� �ð�] �� : %d, �� : %d �� : %d\n", SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
    printf("[���� �ð� ]  �� : %d, �� : %d �� : %d\n", localTime.wHour, localTime.wMinute, localTime.wSecond);

    return 0;
}