#pragma once

#include <mutex>
#include <Windows.h>
#include "Singleton.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 30

class Screen : public Singleton<Screen>
{

	static const int ScreenWidth = SCREEN_WIDTH;
	static const int ScreenHeight = SCREEN_HEIGHT;

	char scBuff1[ScreenWidth * ScreenHeight];
	char scBuff2[ScreenWidth * ScreenHeight];

	char * frontBuff, *backBuff;
	std::mutex frontLock, backLock;


public:
	bool done;

	void ShowConsoleCursor(bool showFlag)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}

	void begin() {

		backLock.lock();
	}

	void clearScreen() {
		int x, y;

		for (x = 0; x < ScreenWidth; x++) {
			for (y = 0; y < ScreenHeight; y++) {
				backBuff[y * ScreenWidth + x] = ' ';
			}
		}
	}


	void end() {
		backLock.unlock();
	}

	void present() {
		frontLock.lock();
		backLock.lock();

		if (frontBuff == scBuff1) {
			frontBuff = scBuff2;
			backBuff = scBuff1;
		}
		else {
			frontBuff = scBuff1;
			backBuff = scBuff2;
		}

		frontLock.unlock();
		backLock.unlock();
	}


	void Draw(const char* img, int w, int h, int x, int y) {

		int i, j;
		for (i = 0; i < w; i++) {
			for (j = 0; j < h; j++) {
				int ty = y + j;
				int tx = x + i;
				if (tx < 0 || tx >= ScreenWidth) {
					continue;
				}
				if (ty < 0 || ty >= ScreenHeight) {
					continue;
				}
				backBuff[ty*ScreenWidth + tx] = img[j*w + i];
			}
		}

	}





	Screen() :done(false), scBuff1(), scBuff2(), frontBuff(nullptr), backBuff(nullptr) {

		ShowConsoleCursor(false);

		int x, y;

		for (x = 0; x < ScreenWidth; x++) {
			for (y = 0; y < ScreenHeight; y++) {
				scBuff1[y* ScreenWidth + x] = ' ';
				scBuff2[y * ScreenWidth + x] = ' ';
			}

		}

		frontBuff = scBuff1;
		backBuff = scBuff2;
		done = false;
	}


	void Update() {

		COORD pos;
		while (done == false) {


			frontLock.lock();


			int x, y;
			for (y = 0; y < ScreenHeight; y++) {
				pos.X = 0;
				pos.Y = y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				for (x = 0; x < ScreenWidth; x++) {

					putchar((int)frontBuff[y * ScreenWidth + x]);
				}
			}
			frontLock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

	}
};