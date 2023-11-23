#include "stdafx.h"
using namespace GammaEngine;

CollisionSpace* GammaEngine::CollisionSpace::root = nullptr;
int GammaEngine::CollisionSpace::maxDepth = 0;
float GammaEngine::CollisionSpace::minAreaSize = 3000.0f;

GammaEngine::CollisionSpace::CollisionSpace()
{
	division[4] = { nullptr, };

	areaSize = 0.0f;
	if (root == nullptr)
	{
		root = this;
		root->colliderList = nullptr;
		root->removeBuffer = nullptr;
		root->areaSize = minAreaSize * maxDepth;
		root->center = vector2();
		root->depth = 0;

		auto temp = CollisionSystem::Instance()->colliderList;
		for (auto iter = temp->begin(); iter < temp->end(); iter++)
		{
			root->Add(*iter);
		}
	}
	else
	{
		removeBuffer = nullptr;
		colliderList = nullptr;
	}


}

GammaEngine::CollisionSpace::~CollisionSpace()
{

}

void GammaEngine::CollisionSpace::Frame()
{
	vector2 p1 = center + vector2(-areaSize / 2, -areaSize / 2);
	vector2 p2 = center + vector2(areaSize / 2, -areaSize / 2);
	vector2 p3 = center + vector2(areaSize / 2, areaSize / 2);
	vector2 p4 = center + vector2(-areaSize / 2, areaSize / 2);
	auto collidedMap = *CollisionSystem::collidedMap;
#ifdef DEBUG
	Debug::DrawRectangle(vector2(areaSize, areaSize), center, 0);
#endif
	if (colliderList && colliderList->size() > 0)
	{
		for (auto iter = colliderList->begin(); iter < colliderList->end(); iter++)
		{
			if ((*iter)->transform->position.x < p1.x || (*iter)->transform->position.x > p3.x || (*iter)->transform->position.y < p1.y || (*iter)->transform->position.y > p3.y)
			{
				removeBuffer->push_back(*iter);
			}
		}

		for (auto iter = removeBuffer->begin(); iter < removeBuffer->end(); iter++)
		{
			Remove(*iter);
			root->Add(*iter);
		}
		removeBuffer->clear();
		for (auto iter1 = colliderList->begin(); iter1 < colliderList->end(); iter1++)
		{
			if ((*iter1)->gameObject->isEnabled && (*iter1)->isEnabled)
			{

				if (Collider::GJK(*iter1, p1) || Collider::GJK(*iter1, p2) || Collider::GJK(*iter1, p3) || Collider::GJK(*iter1, p4))
				{
					for (auto iter2 = CollisionSystem::Instance()->colliderList->begin(); iter2 < CollisionSystem::Instance()->colliderList->end(); iter2++)
					{
						if ((*iter2)->gameObject->isEnabled && *iter1 != *iter2)
						{
							bool collided = false;
							if (find(collidedMap[*iter1]->begin(), collidedMap[*iter1]->end(), (*iter2)) != collidedMap[*iter1]->end())
							{
								collided = true;
							}
							CollisionResponse response = (*iter1)->Collide(*iter2, collided);
							if (response.state == CollisionState::Enter)
							{
								(*iter1)->gameObject->OnCollisionEnter(response);
								collidedMap[*iter1]->push_back(*iter2);
							}
						}
					}
				}
				else
				{
					for (auto iter2 = colliderList->begin(); iter2 < colliderList->end(); iter2++)
					{
						if ((*iter2)->gameObject->isEnabled && (*iter2)->isEnabled && *iter1 != *iter2)
						{
							bool collided = false;
							if (find(collidedMap[*iter1]->begin(), collidedMap[*iter1]->end(), (*iter2)) != collidedMap[*iter1]->end())
							{
								collided = true;
							}
							CollisionResponse response = (*iter1)->Collide(*iter2, collided);
							if (response.state == CollisionState::Enter)
							{
								(*iter1)->gameObject->OnCollisionEnter(response);
								collidedMap[*iter1]->push_back(*iter2);
							}
						}
					}
				}

				for (auto iter3 = collidedMap[*iter1]->begin(); iter3 < collidedMap[*iter1]->end(); iter3++)
				{
					bool collided = true;
					CollisionResponse response = (*iter1)->Collide(*iter3, collided);
					if (response.state == CollisionState::Exit)
					{
						(*iter1)->gameObject->OnCollisionExit(response);
						iter3 = collidedMap[*iter1]->erase(remove_if(collidedMap[*iter1]->begin(), collidedMap[*iter1]->end(), [iter3](Collider* x) { if (x == *iter3) return true; else return false; }), collidedMap[*iter1]->end());
						if (iter3 == collidedMap[*iter1]->end())
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
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (division[i])
			{
				division[i]->Frame();
			}
		}
	}

}
void GammaEngine::CollisionSpace::Remove(Collider* newCollider)
{
	colliderList->erase(remove(colliderList->begin(), colliderList->end(), newCollider), colliderList->end());
}

bool GammaEngine::CollisionSpace::RemoveEmptySpace()
{
	for (int i = 0; i < 4; i++)
	{
		if (division[i] && !division[i]->colliderList)
		{
			if (division[i]->RemoveEmptySpace())
			{
				delete division[i];
				division[i] = nullptr;
			}
		}
		else if (division[i] && division[i]->IsEmpty())
		{
			delete division[i];
			division[i] = nullptr;
		}
		
	}
	return !division[0] && !division[1] && !division[2] && !division[3];
}
bool GammaEngine::CollisionSpace::IsEmpty()
{
	if (colliderList && colliderList->size() == 0)
	{
		return true;
	}
	else
		return false;
}
void GammaEngine::CollisionSpace::Add(Collider* newCollider)
{
	if (depth >= maxDepth)
	{
		if (!colliderList)
		{
			colliderList = new std::vector<Collider*>();
			removeBuffer = new std::vector<Collider*>();
		}
	}

	if (depth < maxDepth)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!division[i])
			{
				division[i] = new CollisionSpace();
				division[i]->areaSize = areaSize / 2;
				division[i]->depth = depth + 1;
			}
		}

		division[0]->center = center + vector2(-division[0]->areaSize / 2, -division[0]->areaSize / 2);
		division[1]->center = center + vector2(division[1]->areaSize / 2, -division[1]->areaSize / 2);
		division[2]->center = center + vector2(division[2]->areaSize / 2, division[2]->areaSize / 2);
		division[3]->center = center + vector2(-division[3]->areaSize / 2, division[3]->areaSize / 2);

		for (int i = 0; i < 4; i++)
		{
			vector2 p1 = division[i]->center + vector2(-division[i]->areaSize / 2, -division[i]->areaSize / 2);
			vector2 p2 = division[i]->center + vector2(division[i]->areaSize / 2, -division[i]->areaSize / 2);
			vector2 p3 = division[i]->center + vector2(division[i]->areaSize / 2, division[i]->areaSize / 2);
			vector2 p4 = division[i]->center + vector2(-division[i]->areaSize / 2, division[i]->areaSize / 2);

			if (newCollider->transform->position.x >= p1.x && newCollider->transform->position.x <= p3.x && newCollider->transform->position.y >= p1.y && newCollider->transform->position.y <= p3.y)
			{
				division[i]->Add(newCollider);
				break;
			}
		}
	}
	else
	{
		colliderList->push_back(newCollider);
	}


}