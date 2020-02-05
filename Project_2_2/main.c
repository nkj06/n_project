
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


// �����Լ�
int main(void)
{
    //system("systeminfo");

    _wsetlocale(LC_ALL, _T("korean"));

    DWORD i;
    TCHAR  infoBuf[INFO_BUFFER_SIZE];
    DWORD  bufCharCount = INFO_BUFFER_SIZE;

    // Get and display the name of the computer. ȣ��Ʈ �̸�
    bufCharCount = INFO_BUFFER_SIZE;
    GetComputerName(infoBuf, &bufCharCount);
    _tprintf(TEXT("ȣ��Ʈ �̸�: \t\t\t%s\n"), infoBuf);

    printf("OS �̸�: \n");
    printf("OS ����: \n");
    printf("OS ������ü: \n");
    printf("OS ����: \n");
    printf("OS ���� ����: \n");

    // Get and display the user name. ��ϵ� ������
    bufCharCount = INFO_BUFFER_SIZE;
    GetUserName(infoBuf, &bufCharCount);
    _tprintf(TEXT("��ϵ� ������: \t\t\t%s\n"), infoBuf);

    printf("��ϵ� ����: \n");
    printf("��ǰ ID: \n");
    printf("���� ��ġ ��¥: \n");
    printf("�ý��� ��Ʈ �ð�: \n");
    printf("�ý��� ������ü: \n");
    printf("�ý��� ��: \n");
    printf("�ý��� ����: \n");

    printf("���μ���: \n");

    printf("BIOS ����: \n");

    // Get and display the Windows directory. Windows ���͸�
    GetWindowsDirectory(infoBuf, INFO_BUFFER_SIZE);
    _tprintf(TEXT("Windows ���͸�: \t\t%s\n"), infoBuf);

    // Get and display the system directory. �ý��� ���͸�
    GetSystemDirectory(infoBuf, INFO_BUFFER_SIZE);
    _tprintf(TEXT("�ý��� ���͸�: \t\t%s\n"), infoBuf);


    printf("���� ��ġ: \n");
    printf("�ý��� ��Ķ: \n");
    printf("�Է� ��Ķ: \n");
    printf("ǥ�� �ð���: \n");


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

    printf("������ ���� : \t\t\tVersion is %d.%d (%d)\n",
        dwMajorVersion,
        dwMinorVersion,
        dwBuild);

    MEMORYSTATUSEX statex;

    statex.dwLength = sizeof(statex);

    GlobalMemoryStatusEx(&statex);

    // �� ���� �޸�
    _tprintf(TEXT("�� ���� �޸�: \t\t%*I64d MB\n"), WIDTH, statex.ullTotalPhys / DIV / DIV);

    // ��� ������ ���� �޸�
    _tprintf(TEXT("��� ������ ���� �޸�: \t%*I64d MB\n"), WIDTH, statex.ullAvailPhys / DIV / DIV);

    // ���� �޸�: �ִ� ũ��
    _tprintf(TEXT("���� �޸�: �ִ� ũ��: \t%*I64d MB\n"), WIDTH, statex.ullTotalPageFile / DIV / DIV);

    // ���� �޸�: ��� ����
    _tprintf(TEXT("���� �޸�: ��� ����: \t%*I64d MB\n"), WIDTH, statex.ullAvailPageFile / DIV / DIV);

    // ���� �޸�: ��� ��
    _tprintf(TEXT("���� �޸�: ��� ��: \t\t%*I64d MB\n"), WIDTH, (statex.ullTotalPageFile / DIV / DIV) - (statex.ullAvailPageFile / DIV / DIV));

    printf("\n");

    printf("������ ���� ��ġ: \n");
    printf("������: \n");

    // �α׿� ����
    printf("�α׿� ����: \n");
    printf("���Ƚ�: \n");
    printf("��Ʈ��ũ ī��: \n");
    printf("\t\t\t\t IP �ּ�\n");

    // ip �ּ� ��� �ҽ��ڵ�
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    IN_ADDR addr;

    addr = GetDefaultMyIP();//����Ʈ IPv4 �ּ� ������
    printf("\t\t\t\t [01]: %s\n", inet_ntoa(addr));//IPv4 �ּҸ� ���ڿ��� ���

    WSACleanup();
    // �������


    printf("Hyper-V �䱸 ����: \n");

    system("pause");
    return EXIT_SUCCESS;
}

IN_ADDR GetDefaultMyIP() // ��Ʈ��ũ ī�� ip
{
    char localhostname[MAX_PATH];
    IN_ADDR addr = { 0, };

    if (gethostname(localhostname, MAX_PATH) == SOCKET_ERROR)//ȣ��Ʈ �̸� ������
    {
        return addr;
    }
    HOSTENT* ptr = gethostbyname(localhostname);//ȣ��Ʈ ��Ʈ�� ������
    while (ptr && ptr->h_name)
    {
        if (ptr->h_addrtype == PF_INET)//IPv4 �ּ� Ÿ���� ��
        {
            memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);//�޸� ����
            break;//�ݺ��� Ż��
        }
        ptr++;
    }
    return addr;
}