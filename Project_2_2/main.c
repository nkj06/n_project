/*
  filename - main.c
  version - 1.0
  description - �⺻ ���� �Լ�
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

// �����Լ�
int main(void)
{
    printf("ȣ��Ʈ �̸�:\t\t %s \n", getenv("COMPUTERNAME"));

    printf("OS �̸�: \n");
    printf("OS ����: \n");
    printf("OS ������ü: \n");
    printf("OS ����: \n");
    printf("OS ���� ����: \n");
    printf("��ϵ� ������: \n");
    printf("��ϵ� ����: \n");
    printf("��ǰ ID: \n");
    printf("���� ��ġ ��¥: \n");
    printf("�ý��� ��Ʈ �ð�: \n");
    printf("�ý��� ������ü: \n");
    printf("�ý��� ��: \n");
    printf("�ý��� ����: \n");

    printf("���μ���: \n");

    printf("BIOS ����: \n");
    printf("Windows ���͸�: \n");
    printf("�ý��� ���͸�: \n");
    printf("���� ��ġ: \n");
    printf("�ý��� ��Ķ: \n");
    printf("�Է� ��Ķ: \n");
    printf("ǥ�� �ð���: \n");
    printf("�� ���� �޸�: \n");
    printf("��� ������ ���� �޸�: \n");
    printf("���� �޸�: �ִ� ũ��: \n");
    printf("���� �޸�: ��� ����: \n");
    printf("���� �޸�: ��� ��: \n");
    printf("������ ���� ��ġ: \n");
    printf("������: \n");

    // �α׿� ����
    printf("�α׿� ����: \n");
    printf("���Ƚ�: \n");
    printf("��Ʈ��ũ ī��: \n");
    printf("\t\t\t IP �ּ�\n");
   
    // ip �ּ� ��� �ҽ��ڵ�
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    IN_ADDR addr;

    addr = GetDefaultMyIP();//����Ʈ IPv4 �ּ� ������
    printf("\t\t\t [01]: %s\n", inet_ntoa(addr));//IPv4 �ּҸ� ���ڿ��� ���

    WSACleanup();
    // �������


    printf("Hyper-V �䱸 ����: \n");

    return 0;
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