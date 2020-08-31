#pragma once
#pragma once
#include <iostream>
#pragma comment(lib,"ws2_32")
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#define SERVERPORT 9000
#define BUFSIZE 512



void err_quit(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);



}

void err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}



int main()
{
	int retval;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//socket()
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	//bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	//데이터 통신에 사용할 변수.
	SOCKADDR_IN clientaddr;
	int addrlen;
	//char buf[BUFSIZE + 1];

	//클라이언트와 데이터통신
	//while (1)
	//{
		//데이터 받기
	addrlen = sizeof(clientaddr);
	//Tank recv_tank;
	char* recv_tank = (char*)malloc(sizeof(Tank));
	memset(recv_tank, 0x00, sizeof(Tank));




	retval = recvfrom(sock, (char*)&recv_tank, sizeof(Tank), 0, (SOCKADDR *)&clientaddr, &addrlen);
	if (retval == SOCKET_ERROR) {
		err_display("recvfrom()");
		//continue;
	}
	Tank* tmp_tank = (Tank*)recv_tank;

	//받은 데이터 출력.
	//buf[retval] = '\0';
	//printf("[UDP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), buf);

	printf("tank x,y: %d , %d", tmp_tank->x, tmp_tank->y);

	char* send_tank = (char*)malloc(sizeof(Tank));
	memset(send_tank, 'A', sizeof(Tank));
	retval = sendto(sock, (char*)&send_tank, sizeof(Tank), 0, (SOCKADDR *)&clientaddr, sizeof(clientaddr));
	if (retval == SOCKET_ERROR) {
		err_display("sendto()");
		//continue;
	}
	//}

	closesocket(sock);

	WSACleanup();
	return 0;


}




