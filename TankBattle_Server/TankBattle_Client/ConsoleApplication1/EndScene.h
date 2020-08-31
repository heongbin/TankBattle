#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "UI.h"

class EndScene : public Scene
{

public:
	EndScene();
	~EndScene();

	virtual void Init();
	//virtual void Update();
	virtual void Update(int*);
	virtual void Render();

private:
	UI* text;
	std::vector<UI> ui;
};

