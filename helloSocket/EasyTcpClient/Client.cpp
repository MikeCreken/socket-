
//#define WIN32_LEAN_AND_MEAN  //����2 ��Ҫ����ǰ��
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
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("����,�����׽���ʧ��\n");
	}
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	_sin.sin_port = htons(1234);//����������ת��Ϊ�����ֽ���
	//���ӷ�����
	int ret=connect(_sock,(sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
	{
		printf("�������ӷ�����ʧ��");
	}
	else
	{
		printf("����socket�ɹ�������������");
	}
	//ע��ͷ���˴�Сһ��
	char cmdBuf[128] = { 0 };
	while (true)
	{
		//ע��ͷ���˴�Сһ�� ������������
		char cmdBuf[128] = { 0 };
		scanf("%s", cmdBuf);
		if (0 == strcmp(cmdBuf, "exit"))
		{
			break;
		}
		else
		{
			send(_sock, cmdBuf, strlen(cmdBuf)+1,0);
		}
		//����recv
		char recvBuf[256] = {};
		int nlen = recv(_sock, recvBuf, sizeof(recvBuf), 0);
		if (nlen > 0)
		{
			printf("���յ�����:%s\n", recvBuf);
		}
	}


	closesocket(_sock);
	WSACleanup();
	printf("�˳����������\n");
	system("pause");
	return 0;
}