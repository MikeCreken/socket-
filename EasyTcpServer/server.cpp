
//#define WIN32_LEAN_AND_MEAN  //����2 ��Ҫ����ǰ��
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>//����1 ��Ҫ����ǰ��
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#pragma  comment(lib,"ws2_32.lib")//�����������ʧ�ܵĿ� ͬʱ���Է��ڸ���Ŀ¼���ʺ�ȫƽ̨
int main()
{

	WORD version = MAKEWORD(2, 2);//�����汾��
	WSADATA data;
	WSAStartup(version, &data);
	/*
	1 ����socket
	2 ��
	3 ����
	4 ����
	5 ����
	6 �ر�
	*/
	//1 ����socket
	SOCKET _sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;
	_sin.sin_port = htons(1234);//����������ת��Ϊ�����ֽ���
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin)))
	{
		printf("ERRPR ��ʧ��\n");
	}
	else
	{
		printf("SUCESS �󶨶˿ڳɹ�\n");

	}
	listen(_sock, 5);
	sockaddr_in clientAddr = {};
	int nAddrlen = sizeof(sockaddr_in);
	SOCKET _csock = INVALID_SOCKET;
	
	
	_csock = accept(_sock, (sockaddr*)&clientAddr, &nAddrlen);
	if (INVALID_SOCKET == _csock)
	{
	printf("���󣬽��յ���Ч��socket\n");
	}
	printf("�µĿͻ��˼���:socket=%d,ip=%s \n",(int)_csock, inet_ntoa(clientAddr.sin_addr));//����ת��

	char recvbuf[128] = {};
	while (true)
	{
		/*_csock = accept(_sock, (sockaddr*)&clientAddr, &nAddrlen);
		if (INVALID_SOCKET == _csock)
		{
			printf("���󣬽��յ���Ч��socket\n");
		}
		//����	3	error C4996 : 'inet_ntoa' : Use inet_ntop() or InetNtop() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings	e : \�������\open_project\c++socket\easytcpserver\server.cpp	50	1	EasyTcpServer

		printf("�µĿͻ��˼���:ip=%s \n", inet_ntoa(clientAddr.sin_addr));//����ת��*/
		//���ܿͻ�������
		int nlen = recv(_csock, recvbuf, 128, 0);
		if (nlen < 0)
		{
			printf("�ͻ������˳�,�������\n");
			break;
		}
		printf("�յ�����:%s\n", recvbuf);
		//�жϿͻ��˷��͹���������
		if (0 == strcmp(recvbuf, "getName"))
		{
			char msgBuf[] = "20";
			send(_csock, msgBuf, strlen(msgBuf), 0);
		}
		else if(0 == strcmp(recvbuf, "getAge"))
		{
			char msgBuf[] = "xiao ming";
			send(_csock, msgBuf, strlen(msgBuf) + 1, 0);
		}
		else
		{
			char *msg = "??????";
			send(_csock, msg, strlen(msg)+1, 0);
		}
		
	}
	
	closesocket(_sock);
	WSACleanup();
	printf("�˳����������\n");
	system("pause");
	return 0;
}