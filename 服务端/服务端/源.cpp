#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>  
#include <winsock2.h>  
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll  

int main() {
	//��ʼ�� DLL  
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���  
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���׽���  
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���  
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ  
	sockAddr.sin_addr.s_addr = inet_addr("10.135.32.3");  //�����IP��ַ  
	sockAddr.sin_port = htons(1234);  //�˿�  
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//�������״̬  ,.
	listen(servSock, 20);

	//���տͻ������� 
	int sum = 0;
	while (true)
	{
		SOCKADDR clntAddr;
		int nSize = sizeof(SOCKADDR);
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

		//��ͻ��˷�������  
		char *str = "test";
		send(clntSock, str, strlen(str) + sizeof(char), NULL);
		closesocket(clntSock);
	}


	//�ر��׽���  
	closesocket(servSock);

	//��ֹ DLL ��ʹ��  
	WSACleanup();

	return 0;
}