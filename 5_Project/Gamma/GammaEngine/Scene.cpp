#include "stdafx.h"
using namespace GammaEngine;

Scene::Scene(std::string sceneName)
{
	sceneName_ = new std::string(sceneName);
	initializer_ = new std::function<void()>();
	gameObjectList_ = new std::vector<GameObject*>();
	holdList = new std::vector<GameObject*>();
}

GammaEngine::Scene::~Scene()
{

}

void GammaEngine::Scene::Start()
{
	for (auto iter = gameObjectList_->begin(); iter < gameObjectList_->end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->Start();
	}
}

void GammaEngine::Scene::Frame()
{
	for (auto iter = gameObjectList_->begin(); iter < gameObjectList_->end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->Update();
	}

	for (auto iter = gameObjectList_->begin(); iter < gameObjectList_->end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->LateUpdate();
	}
}

void GammaEngine::Scene::OnDestroy()
{
	for (auto iter = gameObjectList_->begin(); iter < gameObjectList_->end(); iter++)
	{
		(*iter)->OnDestroy();
	}
}

void GammaEngine::Scene::OnDisable()
{
	for (auto iter = gameObjectList_->begin(); iter < gameObjectList_->end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->OnDisable();
	}
}

void GammaEngine::Scene::OnEnable()
{
	for (auto iter = gameObjectList_->begin(); iter < gameObjectList_->end(); iter++)
	{
		if((*iter)->isEnabled)
			(*iter)->OnEnable();
	}
}

void GammaEngine::Scene::Enable()
{
	//for (auto iter = holdList->begin(); iter < holdList->end(); iter++)
	//{
	//	GameObject* newObj = new GameObject(**iter);
	//	Add(newObj);
	//}
	gameObjectList_->clear();
	Initialize();
	OnEnable();
}

void GammaEngine::Scene::Disable()
{
	OnDisable();
	OnDestroy();
	for (auto iter = gameObjectList_->begin(); iter < gameObjectList_->end(); iter++)
	{
		delete (*iter);
	}
}

void GammaEngine::Scene::Add(GameObject* obj)
{
	gameObjectList_->push_back(obj);
	//obj->isEnabled = true;
}

void GammaEngine::Scene::Remove(GameObject* obj)
{
	gameObjectList_->erase(
		remove_if(
			gameObjectList_->begin(),
			gameObjectList_->end(),
			[obj](GameObject* x) 
			{ 
				if (x == obj) return true; 
				else return false; 
			}),
		gameObjectList_->end()
				);
	obj->OnDisable();
	obj->OnDestroy();
	delete obj;
}

std::string Scene::GetSceneName() const
{
	return *sceneName_;
}

GameObject* Scene::CreateObject()
{
	GameObject* temp = new GameObject();
	gameObjectList_->push_back(temp);
	return temp;
}

void Scene::Initialize()
{
	(*initializer_)();
}

void Scene::SetInitializer(std::function<void()> initializer)
{
	initializer_->swap(initializer);
}

void GammaEngine::Scene::Hold(GameObject* obj)
{
	GameObject* newObj = new GameObject(*obj);
	holdList->push_back(newObj);
};
