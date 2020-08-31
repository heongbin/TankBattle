#pragma once

#include "Scene.h"
#include "Singleton.h"
class SceneManager : public Singleton<SceneManager>
{
public:
	enum Type
	{
		eTitle,
		eMain,
		eEnd,
	};

	SceneManager();
	~SceneManager();

	int GetScore(int playerID) const;
	Scene* GetScene() const;

	void SetScore(int score1, int score2);
	void SetScene(Scene* scene);

	void SceneChange(int scene);

private:
	Scene* mScene;
	int mScore1;
	int mScore2;
};

