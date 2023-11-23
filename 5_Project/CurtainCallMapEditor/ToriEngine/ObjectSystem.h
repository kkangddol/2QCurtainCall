#pragma once

#include <unordered_map>
#include <list>
#include <vector>

class Scene;
class GameObject;

class ObjectSystem
{
public:
	~ObjectSystem();

	// �̱���
	static ObjectSystem& Instance()
	{
		static ObjectSystem instance;
		return instance;
	}

public:
	void Initialize();
	void Finalize();

	void UpdateIndestructible();
	void Update(Scene* scene);

public:
	void RegistObject(Scene* currentScene, GameObject& object);
	void RegistIndestructible(GameObject& object);
	void DestroyObject(GameObject& obj);

/// <summary>
/// Debug�� BruteRender���� �ʿ��� �Լ�...
/// Deprecate ����
/// </summary>
public:
	std::list<GameObject*>& GetCurrentSceneObjects(Scene* scene);

private:
	ObjectSystem();

private:
	std::unordered_map<Scene*, std::list<GameObject*>> objectList_;
	std::vector<GameObject*> destroyBuffer_;
	std::list<GameObject*> indestructibleList_;
};
