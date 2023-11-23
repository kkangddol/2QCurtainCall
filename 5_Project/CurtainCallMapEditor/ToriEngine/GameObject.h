#pragma once
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "Vector2D.h"
#include "Transform.h"

class Component;
class Collider;

/// <summary>
/// 모든 오브젝트가 기본적으로 상속받는 base object 클래스
/// 나중에는 필요한 오브젝트들을 생성해주는 팩토리를 만들어서 전달받아 쓸 수 있게 할 예정
/// 
/// 2022.12.14 강석원 집
/// </summary>
class GameObject final
{
public:
	/// 생성자, 소멸자
	GameObject();	
	~GameObject();

public:
	/// 오브젝트에 추가한 컴포넌트의 Update를 호출해준다.
	/// 이 Update는 Core에서 일괄적으로 호출된다.
	/// -> ObjectSystem으로 변경할까 아니면 Scene으로 할까
	/// 
	/// 23.01.10 강석원 인재원
	void Update() const;

	/// Collider에서 충돌감지가 되면 CollisionSystem에서 호출시키는 콜백 함수들
	/// 오브젝트에 추가한 컴포넌트의 OnCollision들을 호출해준다.
	/// 
	/// 23.01.10 강석원 인재원
	void OnCollisionEnter(Collider* other) const;
	void OnCollisionStay(Collider* other) const;
	void OnCollisionExit(Collider* other) const;

	void Destroy();

	void Enable();
	void Disable();
	bool IsActive() const;

/// <summary>
/// 디버그용
/// </summary>
public:
	int GetComponentSize()
	{
		return componentMap.size();
	}

public:
	/// Transform
	Transform transform;

private:
	bool isActive_;

/// <summary>
/// 컴포넌트 관련
/// </summary>
public:
	// 컴포넌트를 추가 또는 획득
	template <typename T>
	T* AddComponent();
	
	template <typename T>
	T* GetComponent();

	template <typename T>
	std::vector<T*> GetComponents();

private:
	std::unordered_map<const std::type_info*, std::vector<Component*>> componentMap;
};

template <typename T>
T* GameObject::AddComponent()
{
	T* component = GetComponent<T>();
// 	if (component)
// 	{
// 		return component;
// 	}

	component = new T(this);
	componentMap[&typeid(T)].push_back(component);
	return component;
}

template <typename T>
T* GameObject::GetComponent()
{
	auto iter = componentMap.find(&typeid(T));
	if (iter != componentMap.end()) 
	{
		return dynamic_cast<T*>(iter->second.front());
	}

	return nullptr;
}

template <typename T>
std::vector<T*> GameObject::GetComponents()
{
	std::vector<T*> result;
	auto iter = componentMap.find(&typeid(T));
	if (iter != componentMap.end())
	{
		for (auto component : iter->second)
		{
			T* casted_component = dynamic_cast<T*>(component);
			if (casted_component)
			{
				result.push_back(casted_component);
			}
		}
	}

	return result;
}
