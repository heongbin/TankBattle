#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")

#include "TCPClient.h"
#include <stdio.h>

TcpClient::TcpClient()
{
	WSAStartup(WINSOCK_VERSION, &wsaData);
	//socketClient = socket(AF_INET, SOCK_STREAM, 0);
}

TcpClient::~TcpClient()
{
	closesocket(socketClient);
}

void TcpClient::Client_Setting()
{
	socketClient = socket(AF_INET, SOCK_STREAM, 0);
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(IP);
	servAddr.sin_port = htons(PORT);
}

int TcpClient::Client_Connet()
{
	if (connect(socketClient, (struct sockaddr *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		closesocket(socketClient);
		printf("false");
		return SOCKET_ERROR;
	}
	else
	{
		printf("connet\n");
	}
}

void TcpClient::Client_Send(char *buffer)
{
	send(socketClient, buffer, strlen(buffer), 0);
}

int TcpClient::Client_Recv(char *buffer)
{
	return recv(socketClient, buffer, sizeof(buffer), 0);
}
