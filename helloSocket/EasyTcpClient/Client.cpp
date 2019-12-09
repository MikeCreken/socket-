
//#define WIN32_LEAN_AND_MEAN  //方法2 需要放在前面
#include <WinSock2.h>//方法1 需要放在前面
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#pragma  comment(lib,"ws2_32.lib")//否则出现连接失败的库 同时可以放在附加目录中适合全平台
int main()
{

	WORD version = MAKEWORD(2, 2);//创建版本号
	WSADATA data;
	WSAStartup(version, &data);
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("错误,建立套接字失败\n");
	}
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	_sin.sin_port = htons(1234);//这里是主机转换为网络字节序
	//连接服务器
	int ret=connect(_sock,(sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
	{
		printf("错误，连接服务器失败");
	}
	else
	{
		printf("建立socket成功，。。。。。");
	}
	//注意和服务端大小一致
	char cmdBuf[128] = { 0 };
	while (true)
	{
		//注意和服务端大小一致 输入请求命令
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
		//接收recv
		char recvBuf[256] = {};
		int nlen = recv(_sock, recvBuf, sizeof(recvBuf), 0);
		if (nlen > 0)
		{
			printf("接收到数据:%s\n", recvBuf);
		}
	}


	closesocket(_sock);
	WSACleanup();
	printf("退出，任务结束\n");
	system("pause");
	return 0;
}