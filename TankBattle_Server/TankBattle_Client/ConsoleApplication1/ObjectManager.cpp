#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::AddObject(GameObject* obj)
{
	objectVector.push_back(obj);
}

GameObject* ObjectManager::GetObject(int idx)
{
	return objectVector[idx];
}

void ObjectManager::Release()
{
	for (unsigned int i = 0; i < objectVector.size(); i++)
	{
		delete objectVector[i];
	}
	objectVector.clear();
}

