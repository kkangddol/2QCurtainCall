#include "stdafx.h"

using namespace GammaEngine;
std::unordered_map<std::string, Scene*>* GammaEngine::SceneManager::sceneList;
Scene* GammaEngine::SceneManager::currentScene=NULL;
Scene* GammaEngine::SceneManager::nextScene=NULL;

GammaEngine::SceneManager::SceneManager()
{
	sceneList = new std::unordered_map<std::string, Scene*>();
}

GammaEngine::SceneManager::~SceneManager()
{

}

void GammaEngine::SceneManager::Initialize()
{
	//assert((*sceneList)[0]);
	//LoadScene(0);
}

void GammaEngine::SceneManager::AddScene(Scene* scene)
{
	if (sceneList->find(scene->GetSceneName()) != sceneList->end())
	{
		return;
	}

	sceneList->insert({ scene->GetSceneName(), scene } );
}

void GammaEngine::SceneManager::Update()
{
	if (nextScene)
	{
		Timer::CancelAll();
		currentScene->Disable();
		currentScene = nextScene;
		nextScene = nullptr;
		currentScene->Enable();
	}
	
}

void GammaEngine::SceneManager::LoadScene(std::string sceneName)
{
	if (currentScene)
	{
		nextScene = sceneList->at(sceneName);
	}
	else
	{
		currentScene = sceneList->at(sceneName);
		currentScene->Enable();
	}
}

GammaEngine::Scene* SceneManager::CreateScene(std::string sceneName)
{
	Scene* temp = new Scene(sceneName);
	AddScene(temp);
	return temp;
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}
