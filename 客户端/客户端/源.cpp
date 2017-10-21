#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>  
#include<iostream>
#include <stdlib.h>  
#include <WinSock2.h>  
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll  
#define BUF_SIZE 10086

using std::cout;
using std::cin;
using std::endl;

/*
WinSock2.h 中的一些宏定义

#define PF_INET         AF_INET
#define AF_UNSPEC       0               // unspecified
#define AF_UNIX         1               // local to host (pipes, portals)
#define AF_INET         2               // internetwork: UDP, TCP, etc.
#define AF_IMPLINK      3               // arpanet imp addresses
#define AF_PUP          4               // pup protocols: e.g. BSP
#define AF_CHAOS        5               // mit CHAOS protocols
#define AF_NS           6               // XEROX NS protocols

#define SOCK_STREAM     1               // stream socket
#define SOCK_DGRAM      2               // datagram socket

*/
int main() {
	//初始化DLL  
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//向服务器发起请求  
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充  
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");		//回送地址
	sockAddr.sin_port = htons(1234);

	char bufSend[BUF_SIZE] = { 0 };
	char bufRecv[BUF_SIZE] = { 0 };

	while (1)
	{
		//创建套接字  
		SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		//获取用户输入的字符串并发送给服务器  
		cout << "输入";
		cin >> bufSend;
		send(sock, bufSend, strlen(bufSend), 0);
		//接收服务器传回的数据  
		recv(sock, bufRecv, BUF_SIZE, 0);
		//输出接收到的数据  
		cout << "服务器传送回的数据为：" << bufRecv << endl;
		memset(bufSend, 0, BUF_SIZE);  //重置缓冲区  
		memset(bufRecv, 0, BUF_SIZE);  //重置缓冲区  
		closesocket(sock);  //关闭套接字

	}
	WSACleanup();  //终止使用 DLL  
	return 0;
}