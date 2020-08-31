#include "EndScene.h"
EndScene::EndScene()
{
}


EndScene::~EndScene()
{
	for (unsigned int i = 0; i < ui.size(); ++i)
	{
		delete &ui[i];
	}
	ui.clear();
}

void EndScene::Init()
{
	

	if (SceneManager::GetInstance()->GetScore(1) > SceneManager::GetInstance()->GetScore(2))
	{
		text = new UI("P L A Y E R  1  W I N !", 30, 10);
		ui.push_back(*text);
	}
	else if (SceneManager::GetInstance()->GetScore(1) < SceneManager::GetInstance()->GetScore(2))
	{
		text = new UI("P L A Y E R  2  W I N !", 30, 10);
		ui.push_back(*text);
	}
	else
	{
		text = new UI("D R A W !", 37, 10);
		ui.push_back(*text);
	}
	
	text = new UI("PRESS SPACE BAR", 33, 20);
	ui.push_back(*text);
}

void EndScene::Update(int* keyboard)
{
	if (keyboard[4] || keyboard[9])
		SceneManager::GetInstance()->SceneChange(SceneManager::eTitle);
}
void EndScene::Render()
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
