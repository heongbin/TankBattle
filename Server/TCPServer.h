#pragma once

#include <winsock2.h>

#define MAX_SOCKET 3 // 최대 접속 가능 수 + 1
#define PORT 8000
#define BUFFER_SIZE 1024

class TcpServer
{
private:
    WSADATA wsaData;

    SOCKET socketArry[MAX_SOCKET] = {0};
    HANDLE hEventArry[MAX_SOCKET] = {0};

    int index;

    SOCKADDR_IN servAddr;
public:
    TcpServer();
    ~TcpServer();

    void ServerSetting();

    int bind_listen();

    int Event_Handle_Setting();

    void Server_Start();

    char* Get_Buffer();

    void Change_Array(char*,int); //1플레이어 2플레이어 구분

    void Server_Send(char[]);
};