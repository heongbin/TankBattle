#include "TCPServer.h"
#include <iostream>
#include <thread>

using namespace std;


int main()
{
	TcpServer server;
	
	std::thread t([&]() {server.Server_Start(); });
		
	t.join();
	
	return 0;
}