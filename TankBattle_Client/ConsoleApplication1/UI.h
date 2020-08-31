#pragma once

#include <string>
#include "Screen.h"

class UI
{
public :
	UI();
	UI(std::string, int, int);
	~UI();

	void SetString(std::string);
	void SetX(int);
	void SetY(int);

	void DrawString();

private:
	std::string mString;
	int mX;
	int mY;

};

