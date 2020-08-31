#include "TCPServer.h"
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

TcpServer::TcpServer()
{
    WSAStartup(WINSOCK_VERSION, &wsaData);
}

TcpServer::~TcpServer()
{
    closesocket(socketArry[0]);
    WSACleanup();
}

void TcpServer::ServerSetting()
{
    socketArry[0] = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(PORT);
}

int TcpServer::bind_listen()
{
    //bind()
    if (bind(socketArry[0], (sockaddr *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
    {

        closesocket(socketArry[0]);

        printf("bind error");
        return SOCKET_ERROR;
    }
    //listen()
    if (listen(socketArry[0], SOMAXCONN) == SOCKET_ERROR)
    {
        closesocket(socketArry[0]);
        printf("listen error");
        return SOCKET_ERROR;
    }
	return 0;
}

int TcpServer::Event_Handle_Setting()
{
    for (int i = 0; i < MAX_SOCKET; i++)
    {
        hEventArry[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (hEventArry[i] == INVALID_HANDLE_VALUE)
        {
            closesocket(socketArry[0]);
            return SOCKET_ERROR;
        }
    }

    if (WSAEventSelect(socketArry[0], hEventArry[0], FD_ACCEPT) == SOCKET_ERROR)
    {
        closesocket(socketArry[0]);
        CloseHandle(hEventArry[0]);
        return SOCKET_ERROR;
    }
	return 0;
}

void TcpServer::Server_Start()
{
    ServerSetting();
    bind_listen();
    Event_Handle_Setting();

    cout << "server open" << endl;

    int clinet = 1;
    while (true)
    {
        //connect wait
        DWORD dObject = WaitForMultipleObjectsEx(clinet, hEventArry, FALSE, INFINITE, 0);
        if (dObject == INFINITE)
        {
            continue;
        }
        if (dObject == WAIT_OBJECT_0)
        {
            //create client socket
            SOCKADDR_IN clntAddr;
            int clntLen = sizeof(clntAddr);
            SOCKET socketClient = accept(socketArry[0], (SOCKADDR *)&clntAddr, &clntLen);

            index = -1;
            for (int c = 1; c < MAX_SOCKET; c++)
            {
                if (socketArry[c] == 0)
                {
                    index = c;
                    break;
                }
            }

            if (index > 0)
            {
                if (WSAEventSelect(socketClient, hEventArry[index], FD_READ | FD_CLOSE) == SOCKET_ERROR)
                {
                    continue;
                }

                printf("- 플레이어 %d 접속 -\n", index);

                //socket save
                socketArry[index] = socketClient;
                clinet = max(clinet, index + 1);
            }
            else //
            {
                printf("제한 인원 초과\n");
                closesocket(socketClient);
            }
        }
        else
        {
            index = (dObject - WAIT_OBJECT_0);

            char buffer[BUFFER_SIZE] = {0};
            
            // 메세지 수신
            int cnt = recv(socketArry[index], buffer, sizeof(buffer), 0);
            if (cnt <= 0) //접속 종료
            {
                closesocket(socketArry[index]);
                printf("플레이어%d 접속해제\n", index);

                //소켓 제거
                socketArry[index] = 0;
                continue;
            }
			cout << "플레이어" << index << " : " << buffer << endl;

			Change_Array(buffer, index);
            Server_Send(buffer);
        }
    }
}

void TcpServer::Server_Send(char *_buffer)
{   
    for (int c = 1; c < MAX_SOCKET; c++)
    {
        if (socketArry[c] != 0) // && c != index)
        {
			cout << "버퍼 내용 :"<<_buffer << endl;
            send(socketArry[c], _buffer, strlen(_buffer), 0);
        }
    }
}

void TcpServer::Change_Array(char _buffer[BUFFER_SIZE],int _index)
{
	if (_index == 2)
	{
		_buffer[0] += 5;
	}
}