#pragma once

#include <winsock2.h>

#define PORT 8000
#define BUFFER_SIZE 1024
#define IP "127.0.0.1"

class TcpClient
{
private:
    WSADATA wsaData;

	SOCKET socketClient;

    SOCKADDR_IN servAddr = { 0 };
public:
    TcpClient();
    ~TcpClient();

    void Client_Setting();

    int Client_Connet();

    void Client_Send(char*);

    int Client_Recv(char*);
};