#include "SceneSystem.h"
#include "Scene.h"

SceneSystem::SceneSystem()
	:currentScene_(nullptr), UIScene_(nullptr), sceneMap_()
{
}

SceneSystem::~SceneSystem()
{
}

/// <summary>
/// SceneManager를 초기화
/// 멤버 변수를 전부 초기화
/// 
/// 2022.12.13 강석원 집
/// </summary>
void SceneSystem::Initialize()
{
	for (auto e : sceneMap_)
	{
		delete e.second;
	}

	sceneMap_.clear();

	Scene* defaultScene = new Scene("DefaultScene");
	currentScene_ = defaultScene;
	sceneMap_["DefaultScene"] = defaultScene;
}

void SceneSystem::Finalize()
{
	for (auto e : sceneMap_)
	{
		delete e.second;
	}
}

/// <summary>
/// Scene을 생성
/// 
/// 2022.12.13 강석원 집
/// </summary>
Scene& SceneSystem::CreateScene(const std::string& sceneName)
{
	Scene* newScene = new Scene(sceneName);
	sceneMap_[sceneName] = newScene;

	return *newScene;
}

/// <summary>
/// 현재 Scene의 주소를 반환
/// 
/// 2022.12.13 강석원 집
/// </summary>
Scene* SceneSystem::GetCurrentScene() const
{
	return currentScene_;
}

/// <summary>
/// 현재 Scene을 인자로 넘어온 이름의 Scene으로 변경
/// 
/// 2022.12.13 강석원 집
/// </summary>
Scene* SceneSystem::SetCurrentScene(const std::string& sceneName)
{
	if (sceneMap_.at(sceneName))
	{
		currentScene_ = sceneMap_[sceneName];
		return currentScene_;
	}

	return nullptr;
}

Scene* SceneSystem::SetCurrentScene(Scene* scene)
{
	if (sceneMap_.at(scene->GetSceneName()))
	{
		currentScene_ = sceneMap_[scene->GetSceneName()];
		return currentScene_;
	}

	return nullptr;
}

Scene* SceneSystem::GetUIScene() const
{
	return UIScene_;
}

Scene* SceneSystem::SetUIScene(const std::string& sceneName)
{
	if (sceneMap_.at(sceneName))
	{
		UIScene_ = sceneMap_[sceneName];
		return UIScene_;
	}

	return nullptr;
}

Scene* SceneSystem::SetUIScene(Scene* scene)
{
	if (sceneMap_.at(scene->GetSceneName()))
	{
		UIScene_ = sceneMap_[scene->GetSceneName()];
		return UIScene_;
	}

	return nullptr;
}
