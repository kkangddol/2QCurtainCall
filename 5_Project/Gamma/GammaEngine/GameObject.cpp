#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::GameObject::GameObject()
{
	componentList = new std::vector<Component*>();
	transform = new Transform(this);
	tag = new std::string();
}

GammaEngine::GameObject::GameObject(const GameObject& obj)
{
	transform = obj.transform;
	tag = obj.tag;
	componentList = obj.componentList;
}

GammaEngine::GameObject::~GameObject()
{
	Tween::CancelAnimate(transform->position);
	Tween::CancelAnimate(transform->rotation);
	Tween::CancelAnimate(transform->scale);
	for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
	{
		delete	(*iter);
	}
	componentList->clear();
	
	delete transform;
}

void GammaEngine::GameObject::Start()
{
	if (!isStarted)
	{
		for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
		{
			if((*iter)->isEnabled)
				(*iter)->Start();
		}
		isStarted = true;
	}
}

void GammaEngine::GameObject::Update()
{
	if (!isEnabled)
	{
		return;
	}

	for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->Update();
	}
}

void GammaEngine::GameObject::LateUpdate()
{
	for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->LateUpdate();
	}
}


void GammaEngine::GameObject::OnDestroy()
{
	for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
	{
		(*iter)->OnDestroy();
	}
}

void GammaEngine::GameObject::OnDisable()
{
	for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
	{
		(*iter)->OnDisable();
	}
}

void GammaEngine::GameObject::OnEnable()
{
	for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
	{
		(*iter)->OnEnable();
	}
}

void GammaEngine::GameObject::OnCollisionEnter(CollisionResponse response)
{
	for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->OnCollisionEnter(response);
	}
}

void GammaEngine::GameObject::OnCollisionStay(CollisionResponse response)
{
	for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->OnCollisionStay(response);
	}
}

void GammaEngine::GameObject::OnCollisionExit(CollisionResponse response)
{
	for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->OnCollisionExit(response);
	}
}

bool GammaEngine::GameObject::CompareTag(std::string str)
{
	if (strcmp(this->tag->c_str(), str.c_str()) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GammaEngine::GameObject::CompareTag(char* str)
{
	if (strcmp(this->tag->c_str(), str)==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GammaEngine::GameObject::CompareTags(std::vector<std::string> strList)
{
	for (auto iter = strList.begin(); iter < strList.end(); iter++)
	{
		if (CompareTag((*iter)))
		{
			return true;
		}
	}
	return false;
}

void GameObject::Disable()
{
	isEnabled = false;

	for (auto& compo : *componentList)
	{
		compo->isEnabled = false;
	}
	OnDisable();
}

void GameObject::Enable()
{
	isEnabled = true;

	for (auto& compo : *componentList)
	{
		compo->isEnabled = true;
	}
	OnEnable();
}

bool GammaEngine::GameObject::CompareTags(std::vector<char*> strList)
{
	std::vector<char*>::iterator iter;
	for (iter = strList.begin(); iter < strList.end(); iter++)
	{
		if (CompareTag((*iter)))
		{
			return true;
		}
	}
	return false;
}
