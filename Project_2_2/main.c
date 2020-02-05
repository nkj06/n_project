/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수
  --------------------------------------------------------------------------------
  first created - 2020.02.05
  writer - Nam Kyung Jin
*/

#include <stdlib.h>
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32")

typedef BOOL(WINAPI* MYPROC)(LPTSTR, LPDWORD);
IN_ADDR GetDefaultMyIP();

// 메인함수
int main(void)
{
    printf("호스트 이름:\t\t %s \n", getenv("COMPUTERNAME"));

    printf("OS 이름: \n");
    printf("OS 버전: \n");
    printf("OS 제조업체: \n");
    printf("OS 구성: \n");
    printf("OS 빌드 종류: \n");
    printf("등록된 소유자: \n");
    printf("등록된 조직: \n");
    printf("제품 ID: \n");
    printf("원래 설치 날짜: \n");
    printf("시스템 부트 시간: \n");
    printf("시스템 제조업체: \n");
    printf("시스템 모델: \n");
    printf("시스템 종류: \n");

    printf("프로세서: \n");

    printf("BIOS 버전: \n");
    printf("Windows 디렉터리: \n");
    printf("시스템 디렉터리: \n");
    printf("부팅 장치: \n");
    printf("시스템 로캘: \n");
    printf("입력 로캘: \n");
    printf("표준 시간대: \n");
    printf("총 실제 메모리: \n");
    printf("사용 가능한 실제 메모리: \n");
    printf("가상 메모리: 최대 크기: \n");
    printf("가상 메모리: 사용 가능: \n");
    printf("가상 메모리: 사용 중: \n");
    printf("페이지 파일 위치: \n");
    printf("도메인: \n");

    // 로그온 서버
    printf("로그온 서버: \n");
    printf("핫픽스: \n");
    printf("네트워크 카드: \n");
    printf("\t\t\t IP 주소\n");
   
    // ip 주소 얻는 소스코드
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    IN_ADDR addr;

    addr = GetDefaultMyIP();//디폴트 IPv4 주소 얻어오기
    printf("\t\t\t [01]: %s\n", inet_ntoa(addr));//IPv4 주소를 문자열로 출력

    WSACleanup();
    // 여기까지


    printf("Hyper-V 요구 사항: \n");

    return 0;
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