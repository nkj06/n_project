
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>
#include <locale.h>
#include <sysinfoapi.h>

#define  ENV_VAR_STRING_COUNT  (sizeof(envVarStrings)/sizeof(TCHAR*))
#define INFO_BUFFER_SIZE 32767
#define DIV 1024
#define WIDTH 7

#pragma comment(lib,"ws2_32")

typedef BOOL(WINAPI* MYPROC)(LPTSTR, LPDWORD);
IN_ADDR GetDefaultMyIP();


// 메인함수
int main(void)
{
    //system("systeminfo");

    _wsetlocale(LC_ALL, _T("korean"));

    DWORD i;
    TCHAR  infoBuf[INFO_BUFFER_SIZE];
    DWORD  bufCharCount = INFO_BUFFER_SIZE;

    // Get and display the name of the computer. 호스트 이름
    bufCharCount = INFO_BUFFER_SIZE;
    GetComputerName(infoBuf, &bufCharCount);
    _tprintf(TEXT("호스트 이름: \t\t\t%s\n"), infoBuf);

    printf("OS 이름: \n");
    printf("OS 버전: \n");
    printf("OS 제조업체: \n");
    printf("OS 구성: \n");
    printf("OS 빌드 종류: \n");

    // Get and display the user name. 등록된 소유자
    bufCharCount = INFO_BUFFER_SIZE;
    GetUserName(infoBuf, &bufCharCount);
    _tprintf(TEXT("등록된 소유자: \t\t\t%s\n"), infoBuf);

    printf("등록된 조직: \n");
    printf("제품 ID: \n");
    printf("원래 설치 날짜: \n");
    printf("시스템 부트 시간: \n");
    printf("시스템 제조업체: \n");
    printf("시스템 모델: \n");
    printf("시스템 종류: \n");

    printf("프로세서: \n");

    printf("BIOS 버전: \n");

    // Get and display the Windows directory. Windows 디렉터리
    GetWindowsDirectory(infoBuf, INFO_BUFFER_SIZE);
    _tprintf(TEXT("Windows 디렉터리: \t\t%s\n"), infoBuf);

    // Get and display the system directory. 시스템 디렉터리
    GetSystemDirectory(infoBuf, INFO_BUFFER_SIZE);
    _tprintf(TEXT("시스템 디렉터리: \t\t%s\n"), infoBuf);


    printf("부팅 장치: \n");
    printf("시스템 로캘: \n");
    printf("입력 로캘: \n");
    printf("표준 시간대: \n");


    DWORD dwVersion = 0;
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0;
    DWORD dwBuild = 0;

    dwVersion = GetVersion();

    // Get the Windows version.

    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.

    if (dwVersion < 0x80000000)
        dwBuild = (DWORD)(HIWORD(dwVersion));

    printf("윈도우 버전 : \t\t\tVersion is %d.%d (%d)\n",
        dwMajorVersion,
        dwMinorVersion,
        dwBuild);

    MEMORYSTATUSEX statex;

    statex.dwLength = sizeof(statex);

    GlobalMemoryStatusEx(&statex);

    // 총 실제 메모리
    _tprintf(TEXT("총 실제 메모리: \t\t%*I64d MB\n"), WIDTH, statex.ullTotalPhys / DIV / DIV);

    // 사용 가능한 실제 메모리
    _tprintf(TEXT("사용 가능한 실제 메모리: \t%*I64d MB\n"), WIDTH, statex.ullAvailPhys / DIV / DIV);

    // 가상 메모리: 최대 크기
    _tprintf(TEXT("가상 메모리: 최대 크기: \t%*I64d MB\n"), WIDTH, statex.ullTotalPageFile / DIV / DIV);

    // 가상 메모리: 사용 가능
    _tprintf(TEXT("가상 메모리: 사용 가능: \t%*I64d MB\n"), WIDTH, statex.ullAvailPageFile / DIV / DIV);

    // 가상 메모리: 사용 중
    _tprintf(TEXT("가상 메모리: 사용 중: \t\t%*I64d MB\n"), WIDTH, (statex.ullTotalPageFile / DIV / DIV) - (statex.ullAvailPageFile / DIV / DIV));

    printf("\n");

    printf("페이지 파일 위치: \n");
    printf("도메인: \n");

    // 로그온 서버
    printf("로그온 서버: \n");
    printf("핫픽스: \n");
    printf("네트워크 카드: \n");
    printf("\t\t\t\t IP 주소\n");

    // ip 주소 얻는 소스코드
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    IN_ADDR addr;

    addr = GetDefaultMyIP();//디폴트 IPv4 주소 얻어오기
    printf("\t\t\t\t [01]: %s\n", inet_ntoa(addr));//IPv4 주소를 문자열로 출력

    WSACleanup();
    // 여기까지


    printf("Hyper-V 요구 사항: \n");

    system("pause");
    return EXIT_SUCCESS;
}

IN_ADDR GetDefaultMyIP() // 네트워크 카드 ip
{
    char localhostname[MAX_PATH];
    IN_ADDR addr = { 0, };

    if (gethostname(localhostname, MAX_PATH) == SOCKET_ERROR)//호스트 이름 얻어오기
    {
        return addr;
    }
    HOSTENT* ptr = gethostbyname(localhostname);//호스트 엔트리 얻어오기
    while (ptr && ptr->h_name)
    {
        if (ptr->h_addrtype == PF_INET)//IPv4 주소 타입일 때
        {
            memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);//메모리 복사
            break;//반복문 탈출
        }
        ptr++;
    }
    return addr;
}