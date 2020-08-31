#pragma once

#include <bitset>

#include "ObjectManager.h"
#include "CollisionManager.h"

class Scene
{
public:
	Scene();
	~Scene();

	virtual void Init() = 0;
	//virtual void Update() = 0;
	virtual void Update(int*) = 0;
	virtual void Render() = 0;
	virtual void Release();

};

