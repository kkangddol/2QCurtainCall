#pragma once

#include <list>
#include <string>

class GameObject;

/// <summary>
/// 씬입니다.
/// 씬에 Object와 Renderable을 등록하여 사용
/// 
/// 2022.12.13 강석원 집
/// 
/// 사용자가 생성할 씬이 상속받을 BaseClass
/// 여기서 등록한 오브젝트는 부착된 컴포넌트에 따라 자동으로
/// ObjectSystem, ColliderSystem, RenderSystem에 등록된다.
/// 
/// 2022.12.28 강석원 인재원
/// </summary>
class Scene
{
public:
	Scene(std::string sceneName);
	~Scene();

	GameObject& CreateObject();

	void SetSceneName(const std::string& sceneName)
	{
		sceneName_ = sceneName;
	}

	std::string GetSceneName() const
	{
		return sceneName_;
	};

	bool operator==(const Scene& rhs)
	{
		return this->sceneName_ == rhs.sceneName_;
	}

	bool operator==(const std::string sceneName)
	{
		return this->sceneName_ == sceneName;
	}

	bool operator!=(const Scene& rhs)
	{
		return this->sceneName_ != rhs.sceneName_;
	}

	bool operator!=(const std::string sceneName)
	{
		return this->sceneName_ != sceneName;
	}

private:
	std::string sceneName_;
};
