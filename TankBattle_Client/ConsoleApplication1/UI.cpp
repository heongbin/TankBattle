#include "UI.h"



UI::UI()
{

}
UI::UI(std::string string, int x, int y)
{
	mString = string;
	mX = x;
	mY = y;
}
UI::~UI()
{

}

void UI::SetString(std::string string)
{

	mString = string;
}
void UI::SetX(int x)
{
	mX = x;

}
void UI::SetY(int y)
{
	mY = y;

}


void UI::DrawString()
{
	Screen::GetInstance()->Draw(mString.c_str(), mString.length(), 1, mX, mY);
}
