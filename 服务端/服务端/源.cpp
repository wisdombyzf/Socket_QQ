#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h> 
#include<iostream>
#include<string>
#include<thread>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll  

#define BUF_SIZE 10086
//直接用std好像会出现bug
using std::cout;
using std::thread;
//因为socket实际上是int变量，故可直接返回int
int make_socket(int port)
{
	//初始化dll
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字  
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);

	//绑定套接字  
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充  
	sockAddr.sin_family = PF_INET;  //使用IPv4地址  
	//sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //回送IP地址 
	sockAddr.sin_addr.s_addr = INADDR_ANY;			//服务器直接默认本地ip
	sockAddr.sin_port = htons(port);  //端口  
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//进入监听状态  
	listen(servSock, 20);
	return servSock;
}

void handle_accept(int socket_feed)
{
	cout <<"线程为:"<<std::this_thread::get_id() << std::endl;

	char buffer[BUF_SIZE] = { 0 };  //缓冲区  
	int strLen = recv(socket_feed, buffer, BUF_SIZE, 0);  //接收客户端发来的数据  
	send(socket_feed, buffer, strLen, 0);  //将数据原样返回  
	closesocket(socket_feed);  //关闭套接字  
	memset(buffer, 0, BUF_SIZE);  //重置缓冲区  
	//关闭套接字  
	closesocket(socket_feed);
}

int main() {
	int servSock = make_socket(1234);
	while (true)
	{
		int socket_feed= accept(servSock, nullptr, nullptr);
		thread t(handle_accept, socket_feed);
		t.detach();			//分离线程
	}

	//终止 DLL 的使用  
	WSACleanup();

	return 0;
}