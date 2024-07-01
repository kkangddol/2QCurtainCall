#include "stdafx.h"
using namespace GammaEngine;

std::unordered_map<Collider*, std::vector<Collider*>*>* GammaEngine::CollisionSystem::collidedMap;

GammaEngine::CollisionSystem::CollisionSystem()
{
	colliderList = new std::vector<Collider*>();
	collidedMap = new std::unordered_map<Collider*, std::vector<Collider*>*>();
}

GammaEngine::CollisionSystem::~CollisionSystem()
{

}

void GammaEngine::CollisionSystem::Initialize()
{
	CollisionSpace* collisionSpace = new CollisionSpace();
}

void GammaEngine::CollisionSystem::Add(Collider* newCollider)
{
	colliderList->push_back(newCollider);
	CollisionSpace::root->Add(newCollider);
}

void GammaEngine::CollisionSystem::Remove(Collider* newCollider)
{
	colliderList->erase(remove(colliderList->begin(), colliderList->end(), newCollider), colliderList->end());

	delete (*collidedMap)[newCollider];
	(*collidedMap).erase(newCollider);
	for (auto iter : (*collidedMap))
	{
		if (iter.second)
		{
			(iter.second)->erase(remove((iter.second)->begin(), (iter.second)->end(), newCollider), (iter.second)->end());
		}
	}

}

void GammaEngine::CollisionSystem::Frame()
{
	//CollisionSpace* current = CollisionSpace::root;
	//current->Frame();
	//current->RemoveEmptySpace();
	for (auto iter1 = colliderList->begin(); iter1 < colliderList->end(); iter1++)
	{
		if ((*iter1) && (*iter1)->gameObject->isEnabled && (*iter1)->isEnabled)
		{

			for (auto iter2 = CollisionSystem::Instance()->colliderList->begin(); iter2 < CollisionSystem::Instance()->colliderList->end(); iter2++)
			{
				if ((*iter2) && (*iter2)->gameObject->isEnabled && *iter1 != *iter2)
				{
					bool collided = false;
					if ((*collidedMap)[*iter1] && find((*collidedMap)[*iter1]->begin(), (*collidedMap)[*iter1]->end(), (*iter2)) != (*collidedMap)[*iter1]->end())
					{
						collided = true;
					}
					CollisionResponse response = (*iter1)->Collide(*iter2, collided);
					if (response.state == CollisionState::Enter)
					{
						(*iter1)->gameObject->OnCollisionEnter(response);
						(*collidedMap)[*iter1]->push_back(*iter2);
					}
				}
			
			}
		
				for (auto iter2 = colliderList->begin(); iter2 < colliderList->end(); iter2++)
				{
					if ((*iter2) && (*iter2)->gameObject->isEnabled && (*iter2)->isEnabled && *iter1 != *iter2)
					{
						bool collided = false;
						if ((*collidedMap)[*iter1] && find((*collidedMap)[*iter1]->begin(), (*collidedMap)[*iter1]->end(), (*iter2)) != (*collidedMap)[*iter1]->end())
						{
							collided = true;
						}
						CollisionResponse response = (*iter1)->Collide(*iter2, collided);
						if (response.state == CollisionState::Enter)
						{
							(*iter1)->gameObject->OnCollisionEnter(response);
							(*collidedMap)[*iter1]->push_back(*iter2);
						}
					}
				}
			

			for (auto iter3 = (*collidedMap)[*iter1]->begin(); iter3 < (*collidedMap)[*iter1]->end(); iter3++)
			{
				bool collided = true;
				CollisionResponse response = (*iter1)->Collide(*iter3, collided);
				if (response.state == CollisionState::Exit)
				{
					(*iter1)->gameObject->OnCollisionExit(response);
					iter3 = (*collidedMap)[*iter1]->erase(remove_if((*collidedMap)[*iter1]->begin(), (*collidedMap)[*iter1]->end(), [iter3](Collider* x) { if (x == *iter3) return true; else return false; }), (*collidedMap)[*iter1]->end());
					if (iter3 == (*collidedMap)[*iter1]->end())
					{
						break;
					}
				}
				else if (response.state == CollisionState::Stay)
				{
					(*iter1)->gameObject->OnCollisionStay(response);
				}	
			}
		}
	}
}