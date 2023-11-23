#include "Scene.h"

#include "GameObject.h"
#include "ObjectSystem.h"

Scene::Scene(std::string sceneName)
	:sceneName_(sceneName)
{
}

Scene::~Scene()
{
}

GameObject& Scene::CreateObject()
{
	GameObject* object = new GameObject();

	ObjectSystem::Instance().RegistObject(this, *object);

	return *object;
}