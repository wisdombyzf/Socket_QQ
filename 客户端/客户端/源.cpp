#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>  
#include<iostream>
#include <stdlib.h>  
#include <WinSock2.h>  
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll  
#define BUF_SIZE 10086

using std::cout;
using std::cin;
using std::endl;

/*
WinSock2.h �е�һЩ�궨��

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
	//��ʼ��DLL  
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//���������������  
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���  
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");		//���͵�ַ
	sockAddr.sin_port = htons(1234);

	char bufSend[BUF_SIZE] = { 0 };
	char bufRecv[BUF_SIZE] = { 0 };

	while (1)
	{
		//�����׽���  
		SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		//��ȡ�û�������ַ��������͸�������  
		cout << "����";
		cin >> bufSend;
		send(sock, bufSend, strlen(bufSend), 0);
		//���շ��������ص�����  
		recv(sock, bufRecv, BUF_SIZE, 0);
		//������յ�������  
		cout << "���������ͻص�����Ϊ��" << bufRecv << endl;
		memset(bufSend, 0, BUF_SIZE);  //���û�����  
		memset(bufRecv, 0, BUF_SIZE);  //���û�����  
		closesocket(sock);  //�ر��׽���

	}
	WSACleanup();  //��ֹʹ�� DLL  
	return 0;
}