#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h> 
#include<iostream>
#include<string>
#include<thread>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll  

#define BUF_SIZE 10086
//ֱ����std��������bug
using std::cout;
using std::thread;
//��Ϊsocketʵ������int�������ʿ�ֱ�ӷ���int
int make_socket(int port)
{
	//��ʼ��dll
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���  
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);

	//���׽���  
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���  
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ  
	//sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //����IP��ַ 
	sockAddr.sin_addr.s_addr = INADDR_ANY;			//������ֱ��Ĭ�ϱ���ip
	sockAddr.sin_port = htons(port);  //�˿�  
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//�������״̬  
	listen(servSock, 20);
	return servSock;
}

void handle_accept(int socket_feed)
{
	cout <<"�߳�Ϊ:"<<std::this_thread::get_id() << std::endl;

	char buffer[BUF_SIZE] = { 0 };  //������  
	int strLen = recv(socket_feed, buffer, BUF_SIZE, 0);  //���տͻ��˷���������  
	send(socket_feed, buffer, strLen, 0);  //������ԭ������  
	closesocket(socket_feed);  //�ر��׽���  
	memset(buffer, 0, BUF_SIZE);  //���û�����  
	//�ر��׽���  
	closesocket(socket_feed);
}

int main() {
	int servSock = make_socket(1234);
	while (true)
	{
		int socket_feed= accept(servSock, nullptr, nullptr);
		thread t(handle_accept, socket_feed);
		t.detach();			//�����߳�
	}

	//��ֹ DLL ��ʹ��  
	WSACleanup();

	return 0;
}