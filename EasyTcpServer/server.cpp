
//#define WIN32_LEAN_AND_MEAN  //方法2 需要放在前面
#define _WINSOCK_DEPRECATED_NO_WARNINGS
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
	/*
	1 建立socket
	2 绑定
	3 监听
	4 连接
	5 发送
	6 关闭
	*/
	//1 建立socket
	SOCKET _sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;
	_sin.sin_port = htons(1234);//这里是主机转换为网络字节序
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin)))
	{
		printf("ERRPR 绑定失败\n");
	}
	else
	{
		printf("SUCESS 绑定端口成功\n");

	}
	listen(_sock, 5);
	sockaddr_in clientAddr = {};
	int nAddrlen = sizeof(sockaddr_in);
	SOCKET _csock = INVALID_SOCKET;
	
	
	_csock = accept(_sock, (sockaddr*)&clientAddr, &nAddrlen);
	if (INVALID_SOCKET == _csock)
	{
	printf("错误，接收到无效的socket\n");
	}
	printf("新的客户端加入:socket=%d,ip=%s \n",(int)_csock, inet_ntoa(clientAddr.sin_addr));//数字转换

	char recvbuf[128] = {};
	while (true)
	{
		/*_csock = accept(_sock, (sockaddr*)&clientAddr, &nAddrlen);
		if (INVALID_SOCKET == _csock)
		{
			printf("错误，接收到无效的socket\n");
		}
		//错误	3	error C4996 : 'inet_ntoa' : Use inet_ntop() or InetNtop() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings	e : \编程语言\open_project\c++socket\easytcpserver\server.cpp	50	1	EasyTcpServer

		printf("新的客户端加入:ip=%s \n", inet_ntoa(clientAddr.sin_addr));//数字转换*/
		//接受客户端数据
		int nlen = recv(_csock, recvbuf, 128, 0);
		if (nlen < 0)
		{
			printf("客户端已退出,任务结束\n");
			break;
		}
		printf("收到命令:%s\n", recvbuf);
		//判断客户端发送过来的数据
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
	printf("退出，任务结束\n");
	system("pause");
	return 0;
}