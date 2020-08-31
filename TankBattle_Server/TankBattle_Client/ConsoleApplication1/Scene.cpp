#include "Scene.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Release()
{
	ObjectManager::GetInstance()->Release();
}