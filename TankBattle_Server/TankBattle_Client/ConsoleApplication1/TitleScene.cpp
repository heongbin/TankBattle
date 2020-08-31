#include "TitleScene.h"
TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
	for (unsigned int i = 0; i < ui.size(); ++i)
	{
		delete &ui[i];
	}
	ui.clear();
}

void TitleScene::Init()
{
	text = new UI("T A N K  B A T T L E", 30, 10);
	ui.push_back(*text);

	text = new UI("PRESS SPACE BAR", 33, 20);
	ui.push_back(*text);
}

void TitleScene::Update(int* keyboard)
{
	if (keyboard[4] || keyboard[9])
		SceneManager::GetInstance()->SceneChange(SceneManager::eMain);
}
void TitleScene::Render()
{
	Screen::GetInstance()->begin();
	Screen::GetInstance()->clearScreen();

	for (auto i = ui.begin(); i != ui.end(); ++i)
	{
		i->DrawString();
	}

	Screen::GetInstance()->end();
	Screen::GetInstance()->present();
}
