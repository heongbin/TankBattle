#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "UI.h"

class TitleScene : public Scene
{

public:
	TitleScene();
	~TitleScene();

	virtual void Init();
	//virtual void Update();
	virtual void Update(int*);
	virtual void Render();

private:
	UI* text;
	std::vector<UI> ui;
};

