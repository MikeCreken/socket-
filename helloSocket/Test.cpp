
//#define WIN32_LEAN_AND_MEAN  //����2 ��Ҫ����ǰ��
#include <WinSock2.h>//����1 ��Ҫ����ǰ��
#include <windows.h>
#include <stdlib.h>
//#pragma  comment(lib,"ws2_32.lib")//�����������ʧ�ܵĿ� ͬʱ���Է��ڸ���Ŀ¼���ʺ�ȫƽ̨
int main()
{

	WORD version = MAKEWORD(2,2);//�����汾��
	WSADATA data;
	WSAStartup(version,&data);


	WSACleanup();
	system("pause");
	return 0;
}