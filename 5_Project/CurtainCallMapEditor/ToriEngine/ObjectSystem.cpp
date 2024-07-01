#include "ObjectSystem.h"

#include "GameObject.h"

ObjectSystem::ObjectSystem()
{

}

ObjectSystem::~ObjectSystem()
{

}

void ObjectSystem::Initialize()
{

}

void ObjectSystem::Finalize()
{
	for (auto list : objectList_)
	{
		for (auto object : list.second)
		{
			delete object;
		}
	}
}

void ObjectSystem::UpdateIndestructible()
{
	for (auto indest : indestructibleList_)
	{
		indest->Update();
	}
}

void ObjectSystem::Update(Scene* scene)
{
	for (auto& object : objectList_[scene])
	{
		object->Update();
	}

	for (auto& object : destroyBuffer_)
	{
		objectList_[scene].remove(object);
		delete object;
	}

	destroyBuffer_.clear();
}

void ObjectSystem::RegistObject(Scene* currentScene, GameObject& object)
{
	objectList_[currentScene].push_back(&object);
}

void ObjectSystem::RegistIndestructible(GameObject& object)
{
	indestructibleList_.push_back(&object);
}

void ObjectSystem::DestroyObject(GameObject& obj)
{
	destroyBuffer_.push_back(&obj);
}

std::list<GameObject*>& ObjectSystem::GetCurrentSceneObjects(Scene* scene)
{
	return objectList_[scene];
}
