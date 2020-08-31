#include<conio.h>
#include<stdio.h>
#include <bitset>
#include <thread>
#include <queue>

#include "TCPClient.h"
#include <Windows.h>
#include <mutex> 

#include "Screen.h"
#include "SceneManager.h"


int main() {

	std::bitset<0xff> keyPress;
	std::mutex keyLock;
	std::thread t1(&Screen::Update, Screen::GetInstance()); 
	SceneManager::GetInstance()->SceneChange(SceneManager::eTitle);
	int keyboard[11] = { 0 , };

	TcpClient client;
	client.Client_Setting();
	client.Client_Connet();

	int index[5] = { 72,80,75,77,32 };


	std::thread KeyUpdate([&] {
		int c;
		while (true) {
			c = _getch();
			
			if (c < 256) {
				keyLock.lock();
				keyPress[c] = 1;
				for (int i = 0; i < 5; i++)
				{
					if (c == index[i])
					{
						char buffer[BUFFER_SIZE] = { " " };
						buffer[0] = (char)('0' + i);
						client.Client_Send(buffer);
						break;
					}
				}
				keyLock.unlock();
				if (c == 27) {
					break;
				}
			}
		}
	});

	queue<int> qnum;
	std::thread a([&] {
		while (true) {
			char recv_buffer[BUFFER_SIZE]{ 0 };
			client.Client_Recv(recv_buffer);
			
				qnum.push((int)(recv_buffer[0] - '0'));
		}
	});

	std::thread Update([&] {
		while (true) {
			/*keyboard[0] = keyPress[72];
			keyboard[1] = keyPress[80];
			keyboard[2] = keyPress[75];
			keyboard[3] = keyPress[77];
			keyboard[4] = keyPress[32];
			keyboard[5] = keyPress[119];
			keyboard[6] = keyPress[115];
			keyboard[7] = keyPress[97];
			keyboard[8] = keyPress[100];
			keyboard[9] = keyPress[102];*/
			keyPress.reset();

			int q = 10;
			bool q_isempty = qnum.empty();
			if (!q_isempty) {
				q = qnum.front();
				keyboard[q] = 1;
			}
			
			// 키입력받아 Update
			SceneManager::GetInstance()->GetScene()->Update(keyboard);

			
			if (!q_isempty) {
				keyboard[q] = 0;
				qnum.pop();
			}

			// Render
			SceneManager::GetInstance()->GetScene()->Render();
			if (keyPress[27]) {
				Screen::GetInstance()->done = true;
				break;
			}
		}
	});

	a.join();
	Update.join();
	KeyUpdate.join();
	t1.join();

}
