// client_char.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>  
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>  
#include <memory.h>  
#include <string.h> 
#pragma comment(lib,"ws2_32.lib")



int _tmain(int argc, _TCHAR* argv[])
{//初始化socket编程环境
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	struct in_addr s;
	
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return 0;
	}
	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return 0;
	}
	//建立客户端socket
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	//服务器地址
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr =inet_addr("192.168.41.129"); 
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8888);
	//连接服务器


	//等待接收服务器的响应
	char recvBuf[100];
	memset(recvBuf, 0, 100);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	int r = 0;
	do//不断与服务器连接，直到它关闭
	{
		printf("receiving.....\n");
		r = recv(sockClient, recvBuf, 100, 0);
		printf("receive end.....\n");
		printf("data from server: %s\n", recvBuf);
		char sendBuf[100];
		printf("input the message to send[1-100]: ");
		gets_s(sendBuf);
		printf("sending.....\n");
		r = send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
		printf("send ended. waiting for server\n");


	} while (r != SOCKET_ERROR);
	printf("server connect error! app will exit\n");
	system("PAUSE");
	closesocket(sockClient);
	WSACleanup();


	return 0;
}