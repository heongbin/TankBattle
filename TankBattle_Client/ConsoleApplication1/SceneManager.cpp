#include "SceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "EndScene.h"

SceneManager::SceneManager()
{
	mScene = NULL;
}


SceneManager::~SceneManager()
{
}
int SceneManager::GetScore(int playerID) const
{
	if (playerID == 1)
	{
		return mScore1;
	}
	if (playerID == 2)
	{
		return mScore2;
	}
	else
		return 0;
}


Scene* SceneManager::GetScene() const
{
	return mScene;
}

void SceneManager::SetScore(int score1, int score2)
{
	mScore1 = score1;
	mScore2 = score2;
}


void SceneManager::SetScene(Scene* scene)
{
	mScene = scene;
}

void SceneManager::SceneChange(int scene)
{
	if (mScene)
	{
		mScene->Release();
		delete mScene;
	}
	switch (scene)
	{
	case eTitle:
		mScene = new TitleScene;
		break;
	case eMain:
		mScene = new MainScene;
		break;
	case eEnd:
		mScene = new EndScene;
		break;
	}
	if (mScene)
	{
		mScene->Init();
	}
}