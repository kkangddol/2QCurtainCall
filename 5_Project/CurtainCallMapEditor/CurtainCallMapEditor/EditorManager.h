#pragma once
#include <list>
#include "Component.h"

class GameObject;
class Scene;

/// <summary>
/// 맵 에디터에서 배치한 오브젝트들의 정보들을 관리할 매니저
/// 
/// 23.02.18 강석원 집
/// </summary>
class EditorManager : public Component
{
public:
	enum class eObject
	{
		BOX,
		LADDER,
		LEFTPLATFORM,
		RIGHTPLATFORM,
		WATERTANK,
		ARCH,
		ELEVATOR,
		CONTROL,
		MUSIC,
		WHEEL,
		SCAFFOLDING,
		LEVER,
		CYCLE
	};

public:
	EditorManager(GameObject* obj);
	~EditorManager();

public:
	static void AddToList(GameObject* obj);
	static void RemoveFromList(GameObject* obj);
	static GameObject* GetDragObject();
	static void SetDragObject(GameObject* obj);
	static void EndDrag();
	static void EndDrag(bool justChangeToNullptr);
	static void RightClick(GameObject* obj);
	static bool SaveAllData();
	static bool LoadAllData();
	static GameObject* Instantiate(eObject objEnum);
	static GameObject* Instantiate(eObject objEnum, bool dataLoad);
	static void SetScene(Scene* scene);
	static int GetObjectCount();

private:
	static void Unbind(GameObject* obj);
	static void Bind(GameObject* lhs, GameObject* rhs);

private:
	static Scene* currentScene_;
	static int objectIndex_;
	static std::list<GameObject*> objectList_;
	static GameObject* draggingObject_;
	static GameObject* bindingObject_;
};
