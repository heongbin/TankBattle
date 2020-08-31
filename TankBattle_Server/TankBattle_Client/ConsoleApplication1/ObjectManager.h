#pragma once

#include <vector>

#include "GameObject.h"
#include "Singleton.h"

using namespace std;

class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager();
	~ObjectManager();

	void AddObject(GameObject* obj);
	GameObject* GetObject(int idx);
	void Release();

private:
	vector<GameObject*> objectVector;

};