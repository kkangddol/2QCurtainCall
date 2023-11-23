#include "GameObject.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Component.h"
#include "ObjectSystem.h"

/// <summary>
/// 생성자

/// 22.12.14 강석원 인재원
/// </summary>
GameObject::GameObject()
	: transform(this),
	isActive_(true)
{

}

GameObject::~GameObject()
{
	for (auto& vec : componentMap)
	{
		for (auto& component : vec.second)
		{
			delete component;
		}
		vec.second.clear();
	}
	componentMap.clear();
}

void GameObject::Update() const
{
	if (!isActive_)
	{
		return;
	}

	for (const auto& iter : componentMap)
	{
		for (const auto& component : iter.second)
		{
			component->Update();
		}
	}
}

void GameObject::OnCollisionEnter(Collider* other) const
{
	if (!isActive_)
	{
		return;
	}

	for (const auto& iter : componentMap)
	{
		for (const auto& component : iter.second)
		{
			component->OnCollisionEnter(other);
		}
	}
}

void GameObject::OnCollisionStay(Collider* other) const
{
	if (!isActive_)
	{
		return;
	}

	for (const auto& iter : componentMap)
	{
		for (const auto& component : iter.second)
		{
			component->OnCollisionStay(other);
		}
	}
}

void GameObject::OnCollisionExit(Collider* other) const
{
	if (!isActive_)
	{
		return;
	}

	for (const auto& iter : componentMap)
	{
		for (const auto& component : iter.second)
		{
			component->OnCollisionExit(other);
		}
	}
}

void GameObject::Destroy()
{
	Disable();
	ObjectSystem::Instance().DestroyObject(*this);
}

void GameObject::Enable()
{
	isActive_ = true;
}

void GameObject::Disable()
{
	isActive_ = false;
}

bool GameObject::IsActive() const
{
	return isActive_;
}

