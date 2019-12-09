
//#define WIN32_LEAN_AND_MEAN  //方法2 需要放在前面
#include <WinSock2.h>//方法1 需要放在前面
#include <windows.h>
#include <stdlib.h>
//#pragma  comment(lib,"ws2_32.lib")//否则出现连接失败的库 同时可以放在附加目录中适合全平台
int main()
{

	WORD version = MAKEWORD(2,2);//创建版本号
	WSADATA data;
	WSAStartup(version,&data);


	WSACleanup();
	system("pause");
	return 0;
}