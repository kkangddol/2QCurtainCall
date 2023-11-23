#pragma once

#include <list>
#include <string>

class GameObject;

/// <summary>
/// ���Դϴ�.
/// ���� Object�� Renderable�� ����Ͽ� ���
/// 
/// 2022.12.13 ������ ��
/// 
/// ����ڰ� ������ ���� ��ӹ��� BaseClass
/// ���⼭ ����� ������Ʈ�� ������ ������Ʈ�� ���� �ڵ�����
/// ObjectSystem, ColliderSystem, RenderSystem�� ��ϵȴ�.
/// 
/// 2022.12.28 ������ �����
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
