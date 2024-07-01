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
/// SceneManager�� �ʱ�ȭ
/// ��� ������ ���� �ʱ�ȭ
/// 
/// 2022.12.13 ������ ��
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
/// Scene�� ����
/// 
/// 2022.12.13 ������ ��
/// </summary>
Scene& SceneSystem::CreateScene(const std::string& sceneName)
{
	Scene* newScene = new Scene(sceneName);
	sceneMap_[sceneName] = newScene;

	return *newScene;
}

/// <summary>
/// ���� Scene�� �ּҸ� ��ȯ
/// 
/// 2022.12.13 ������ ��
/// </summary>
Scene* SceneSystem::GetCurrentScene() const
{
	return currentScene_;
}

/// <summary>
/// ���� Scene�� ���ڷ� �Ѿ�� �̸��� Scene���� ����
/// 
/// 2022.12.13 ������ ��
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
