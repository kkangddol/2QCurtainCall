#pragma once
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "Vector2D.h"
#include "Transform.h"

class Component;
class Collider;

/// <summary>
/// ��� ������Ʈ�� �⺻������ ��ӹ޴� base object Ŭ����
/// ���߿��� �ʿ��� ������Ʈ���� �������ִ� ���丮�� ���� ���޹޾� �� �� �ְ� �� ����
/// 
/// 2022.12.14 ������ ��
/// </summary>
class GameObject final
{
public:
	/// ������, �Ҹ���
	GameObject();	
	~GameObject();

public:
	/// ������Ʈ�� �߰��� ������Ʈ�� Update�� ȣ�����ش�.
	/// �� Update�� Core���� �ϰ������� ȣ��ȴ�.
	/// -> ObjectSystem���� �����ұ� �ƴϸ� Scene���� �ұ�
	/// 
	/// 23.01.10 ������ �����
	void Update() const;

	/// Collider���� �浹������ �Ǹ� CollisionSystem���� ȣ���Ű�� �ݹ� �Լ���
	/// ������Ʈ�� �߰��� ������Ʈ�� OnCollision���� ȣ�����ش�.
	/// 
	/// 23.01.10 ������ �����
	void OnCollisionEnter(Collider* other) const;
	void OnCollisionStay(Collider* other) const;
	void OnCollisionExit(Collider* other) const;

	void Destroy();

	void Enable();
	void Disable();
	bool IsActive() const;

/// <summary>
/// ����׿�
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
/// ������Ʈ ����
/// </summary>
public:
	// ������Ʈ�� �߰� �Ǵ� ȹ��
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
