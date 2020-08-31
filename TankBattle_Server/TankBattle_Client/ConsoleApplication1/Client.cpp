//#include<conio.h>
//#include<stdio.h>
//#include <bitset>
//#include <thread>
//#include <Windows.h>
//#include <mutex> 
//#include <vector>
//
//
//#include "Player.h"
//#include "Projectile.h"
//#include "Block.h"
//#include "Collision.h"
//#include "ObjectPool.h"
//
//#pragma comment( lib, "Winmm.lib" )
//
//#define TANK_SIZE 3
//#define PROJECTILE_SIZE 1
//#define BLOCK_SIZE 1
//#define SCREEN_WIDTH 80
//#define SCREEN_HEIGHT 30
//
//
//class Screen {
//
//	static const int ScreenWidth = SCREEN_WIDTH;
//	static const int ScreenHeight = SCREEN_HEIGHT;
//
//	char scBuff1[ScreenWidth * ScreenHeight];
//	char scBuff2[ScreenWidth * ScreenHeight];
//
//	char * frontBuff, *backBuff;
//	std::mutex frontLock, backLock;
//
//
//public:
//	bool done;
//
//	void ShowConsoleCursor(bool showFlag)
//	{
//		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
//
//		CONSOLE_CURSOR_INFO     cursorInfo;
//
//		GetConsoleCursorInfo(out, &cursorInfo);
//		cursorInfo.bVisible = showFlag; // set the cursor visibility
//		SetConsoleCursorInfo(out, &cursorInfo);
//	}
//
//	void begin() {
//
//		backLock.lock();
//	}
//
//	void clearScreen() {
//		int x, y;
//
//		for (x = 0; x < ScreenWidth; x++) {
//			for (y = 0; y < ScreenHeight; y++) {
//				backBuff[y * ScreenWidth + x] = ' ';
//			}
//		}
//	}
//
//
//	void end() {
//		backLock.unlock();
//	}
//
//	void present() {
//		frontLock.lock();
//		backLock.lock();
//
//		if (frontBuff == scBuff1) {
//			frontBuff = scBuff2;
//			backBuff = scBuff1;
//		}
//		else {
//			frontBuff = scBuff1;
//			backBuff = scBuff2;
//		}
//
//		frontLock.unlock();
//		backLock.unlock();
//	}
//
//
//	void Draw(const char* img, int w, int h, int x, int y) {
//
//		int i, j;
//		for (i = 0; i < w; i++) {
//			for (j = 0; j < h; j++) {
//				int ty = y + j;
//				int tx = x + i;
//				if (tx < 0 || tx >= ScreenWidth) {
//					continue;
//				}
//				if (ty < 0 || ty >= ScreenHeight) {
//					continue;
//				}
//				backBuff[ty*ScreenWidth + tx] = img[j*w + i];
//			}
//		}
//
//	}
//
//
//
//
//
//	Screen() :done(false), scBuff1(), scBuff2(), frontBuff(nullptr), backBuff(nullptr) {
//
//		ShowConsoleCursor(false);
//
//		int x, y;
//
//		for (x = 0; x < ScreenWidth; x++) {
//			for (y = 0; y < ScreenHeight; y++) {
//				scBuff1[y* ScreenWidth + x] = ' ';
//				scBuff2[y * ScreenWidth + x] = ' ';
//			}
//
//		}
//
//		frontBuff = scBuff1;
//		backBuff = scBuff2;
//		done = false;
//	}
//
//
//	void Update() {
//
//		COORD pos;
//		while (done == false) {
//
//
//			frontLock.lock();
//
//
//			int x, y;
//			for (y = 0; y < ScreenHeight; y++) {
//				pos.X = 0;
//				pos.Y = y;
//				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//				for (x = 0; x < ScreenWidth; x++) {
//
//					putchar((int)frontBuff[y * ScreenWidth + x]);
//				}
//			}
//			frontLock.unlock();
//			std::this_thread::sleep_for(std::chrono::milliseconds(1));
//		}
//
//	}
//};
//
//
//int main() {
//
//	std::bitset<0xff> keyPress;
//
//	Screen screen;
//
//	std::mutex keyLock;
//
//	std::thread t1(&Screen::Update, &screen);
//
//	std::thread KeyUpdate([&] {
//		int c;
//
//		while (true) {
//
//			c = _getch();
//			if (c < 256) {
//				keyLock.lock();
//				keyPress[c] = 1;
//				keyLock.unlock();
//				if (c == 27) {
//					break;
//				}
//			}
//
//		}
//	});
//
//	char p1Img[9] = { char(1),'l',char(2),' ', '1', ' ',char(3), ' ',char(4) };
//	char p2Img[9] = { char(1),'l',char(2),' ', '2', ' ',char(3), ' ',char(4) };
//	char blockImg[1] = { 'W' };
//	char brokenblockImg[1] = { 'w' };
//	char solidblockImg[1] = { '#' };
//	char projImg[1] = { 'o' };
//	char projImg1[1] = { 'O' };
//	/*char powerupImg[1] = { 'P' };
//	char powerupImg[1] = { 'H' };*/
//
//	int map[30][80];
//	for (int i = 0; i < 30; ++i)
//	{
//		map[i][0] = 3;
//		map[i][1] = 3;
//		map[i][78] = 3;
//		map[i][79] = 3;
//	}
//	for (int j = 0; j < 80; ++j)
//	{
//		map[0][j] = 3;
//		map[1][j] = 3;
//		map[28][j] = 3;
//		map[29][j] = 3;
//	}
//	map[15][30] = 2;
//
//	
//	Player* player = new Player;
//	player1->SetX(10);
//	player1->SetY(5);
//	player1->SetDir(1);
//	player1->SetSize(TANK_SIZE);
//	player1->SetHP(3);
//	player1->SetDamage(1);
//	player1->SetImage(p1Img);
//
//
//	Player* player2 = new Player; // 테스트용 적 객체
//	player2->SetX(40);
//	player2->SetY(20);
//	player2->SetDir(3);
//	player2->SetSize(TANK_SIZE);
//	player2->SetHP(3);
//	player2->SetDamage(1);
//	player2->SetImage(p2Img);
//
//	std::vector<Projectile> v;
//	std::vector<Block> b;
//
//	for (int i = 0; i < 30; ++i)
//	{
//		for (int j = 0; j < 80; ++j)
//		{
//			if (map[i][j] == 3)
//			{
//				Block* block = new Block; // 체력3 = 무적
//				block->SetX(j);
//				block->SetY(i);
//				block->SetSize(BLOCK_SIZE);
//				block->SetHP(3);
//				block->SetImage(solidblockImg);
//				b.push_back(*block);
//			}
//			if (map[i][j] == 2)
//			{
//				Block* block = new Block; // 완전한블록
//				block->SetX(j);
//				block->SetY(i);
//				block->SetSize(BLOCK_SIZE);
//				block->SetHP(2);
//				block->SetImage(blockImg);
//				b.push_back(*block);
//			}
//			if (map[i][j] == 1)
//			{
//				Block* block = new Block; // 반파된블록
//				block->SetX(j);
//				block->SetY(i);
//				block->SetSize(BLOCK_SIZE);
//				block->SetHP(1);
//				block->SetImage(brokenblockImg);
//				b.push_back(*block);
//			}
//		}
//	}
//
//
//
//	int playerID = 1; // 일단 1
//
//	std::thread Update([&] {
//		while (true) {
//
//			bool isDone = false;
//
//			// Key 처리
//
//			keyLock.lock();
//
//			isDone = keyPress[27];
//
//			if (keyPress[72]) {
//				// 위쪽 보내기
//			}
//			if (keyPress[80]) {
//				// 아래쪽 보내기
//			}
//			if (keyPress[75]) {
//				// 왼쪽 보내기
//			}
//			if (keyPress[77]) {
//				// 오른쪽 보내기
//			}
//			if (keyPress[32]) {
//				// 스페이스바 보내기
//			}
//
//			keyPress.reset();
//			keyLock.unlock();
//
//			// 상황에 따른 이미지 변경
//			switch (player1->GetDir())
//			{
//			case 1:
//				p1Img[1] = 'l';
//				p1Img[3] = ' ';
//				p1Img[5] = ' ';
//				p1Img[7] = ' ';
//				break;
//			case 2:
//				p1Img[1] = ' ';
//				p1Img[3] = ' ';
//				p1Img[5] = ' ';
//				p1Img[7] = 'l';
//				break;
//			case 3:
//				p1Img[1] = ' ';
//				p1Img[3] = '-';
//				p1Img[5] = ' ';
//				p1Img[7] = ' ';
//				break;
//			case 4:
//				p1Img[1] = ' ';
//				p1Img[3] = ' ';
//				p1Img[5] = '-';
//				p1Img[7] = ' ';
//				break;
//
//			}
//			switch (player2->GetDir())
//			{
//			case 1:
//				p2Img[1] = 'l';
//				p2Img[3] = ' ';
//				p2Img[5] = ' ';
//				p2Img[7] = ' ';
//				break;
//			case 2:
//				p2Img[1] = ' ';
//				p2Img[3] = ' ';
//				p2Img[5] = ' ';
//				p2Img[7] = 'l';
//				break;
//			case 3:
//				p2Img[1] = ' ';
//				p2Img[3] = '-';
//				p2Img[5] = ' ';
//				p2Img[7] = ' ';
//				break;
//			case 4:
//				p2Img[1] = ' ';
//				p2Img[3] = ' ';
//				p2Img[5] = '-';
//				p2Img[7] = ' ';
//				break;
//
//			}
//
//
//			
//
//			// Draw 처리
//			screen.begin();
//			screen.clearScreen();
//			screen.Draw(player1->GetImage(), player1->GetSize(), player1->GetSize(), player1->GetX(), player1->GetY());
//			screen.Draw(player2->GetImage(), player2->GetSize(), player2->GetSize(), player2->GetX(), player2->GetY());
//
//			for (auto i = v.begin(); i != v.end(); ++i)
//			{
//				screen.Draw(i->GetImage(), i->GetSize(), i->GetSize(), i->GetX(), i->GetY());
//			}
//
//			for (auto i = b.begin(); i != b.end(); ++i)
//			{
//				screen.Draw(i->GetImage(), i->GetSize(), i->GetSize(), i->GetX(), i->GetY());
//			}
//
//			screen.end();
//			screen.present();
//
//			if (isDone) {
//				screen.done = true;
//				break;
//
//			}
//		}
//
//	});
//
//	Update.join();
//
//	KeyUpdate.join();
//	t1.join();
//
//	printf("종료!");
//}
