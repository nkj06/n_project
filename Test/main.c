#include <windows.h>
#include <stdio.h>

int main() {

    SYSTEMTIME localTime;
    SYSTEMTIME SysTime;

    GetSystemTime(&SysTime);
    GetLocalTime(&localTime);

    printf("[시스템 시간] 시 : %d, 분 : %d 초 : %d\n", SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
    printf("[로컬 시간 ]  시 : %d, 분 : %d 초 : %d\n", localTime.wHour, localTime.wMinute, localTime.wSecond);

    return 0;
}