#include "CollisionSystem.h"

#include <vector>

#include "Collider.h"
#include "GameObject.h"
#include "CircleCollider2D.h"
#include "BoxCollider2D.h"
#include "SceneSystem.h"
#include "Vector2D.h"

#include "CC.h"
#include "AABB.h"
#include "OBB.h"

void CollisionSystem::Initialize()
{
	colliderList_.clear();
	prevStatus_.clear();
	statusBuffer_.clear();
}

/// <summary>
/// 여기서 Collider delete 해줬더니 힙 오류가 난다.
/// 어디서 소멸되는지 추적해야 할 필요가 있다.
/// 
/// 22.12.28 강석원 집
/// </summary>
void CollisionSystem::Finalize()
{
}

/// <summary>
/// 등록된 콜라이더들에 대해 전부 충돌체크를 해서 상태를 기록한다.
/// 등록된 콜라이더 : 현재 씬의 오브젝트들이 갖고있는 콜라이더
/// 
/// 22.12.22 강석원 인재원
/// 
/// 22.12.28 지금은 원충돌만
/// </summary>
void CollisionSystem::CheckCollision()
{
	Scene* currentScene = SceneSystem::Instance().GetCurrentScene();

	for (auto lhs : colliderList_[currentScene])
	{
		for (auto rhs : colliderList_[currentScene])
		{
			if (lhs->GetColliderType() != rhs->GetColliderType())
			{
				continue;
			}

			if (lhs == rhs)
			{
				continue;
			}

			if (lhs->GetColliderType() == Collider::ColliderType::CIRCLE)
			{
				if (CheckCC((CircleCollider2D*)lhs, (CircleCollider2D*)rhs))
				{
					statusBuffer_[lhs][rhs] = true;
					statusBuffer_[rhs][lhs] = true;

					if (prevStatus_.empty())
					{
						lhs->GetObj()->OnCollisionEnter(rhs);
						continue;
					}

					if (prevStatus_[lhs][rhs])
					{
						lhs->GetObj()->OnCollisionStay(rhs);
					}
					else
					{
						lhs->GetObj()->OnCollisionEnter(rhs);
					}
				}
				else
				{
					statusBuffer_[lhs][rhs] = false;
					statusBuffer_[rhs][lhs] = false;

					if (prevStatus_.empty())
					{
						lhs->GetObj()->OnCollisionExit(rhs);
						continue;
					}

					if (prevStatus_[lhs][rhs])
					{
						lhs->GetObj()->OnCollisionExit(rhs);
					}
				}
			}
			else if (lhs->GetColliderType() == Collider::ColliderType::RECTANGLE)
			{
				//if (CheckAABB((BoxCollider2D*)lhs, (BoxCollider2D*)rhs))
				if (CheckOBB((BoxCollider2D*)lhs, (BoxCollider2D*)rhs))
				{
					statusBuffer_[lhs][rhs] = true;
					statusBuffer_[rhs][lhs] = true;

					if (prevStatus_.empty())
					{
						lhs->GetObj()->OnCollisionEnter(rhs);
						continue;
					}

					if (prevStatus_[lhs][rhs])
					{
						lhs->GetObj()->OnCollisionStay(rhs);
					}
					else
					{
						lhs->GetObj()->OnCollisionEnter(rhs);
					}
				}
				else
				{
					statusBuffer_[lhs][rhs] = false;
					statusBuffer_[rhs][lhs] = false;

					if (prevStatus_.empty())
					{
						lhs->GetObj()->OnCollisionExit(rhs);
						continue;
					}

					if (prevStatus_[lhs][rhs])
					{
						lhs->GetObj()->OnCollisionExit(rhs);
					}
				}
			}
		}
	}

	prevStatus_ = statusBuffer_;
}

bool CollisionSystem::CheckCC(CircleCollider2D* const lhs, CircleCollider2D* const rhs)
{
	float x1 = lhs->GetWorldPosition().x;
	float y1 = lhs->GetWorldPosition().y;
	float radius1 = lhs->GetRadiusRelative();

	float x2 = rhs->GetWorldPosition().x;
	float y2 = rhs->GetWorldPosition().y;
	float radius2 = rhs->GetRadiusRelative();

	return DetectCC(x1, y1, radius1, x2, y2, radius2);
}

bool CollisionSystem::CheckAABB(BoxCollider2D* lhs, BoxCollider2D* rhs)
{
	float left1 = lhs->GetWorldLeft();
	float top1 = lhs->GetWorldTop();
	float right1 = lhs->GetWorldRight();
	float bottom1 = lhs->GetWorldBottom();

	float left2 = rhs->GetWorldLeft();
	float top2 = rhs->GetWorldTop();
	float right2 = rhs->GetWorldRight();
	float bottom2 = rhs->GetWorldBottom();

	return DetectAABB(left1, top1, right1, bottom1, left2, top2, right2, bottom2);
}

bool CollisionSystem::CheckOBB(BoxCollider2D* lhs, BoxCollider2D* rhs)
{
	std::vector<Vector2D> lhsPoints;
	std::vector<Vector2D> rhsPoints;

	lhsPoints.push_back(lhs->GetWorldLT());
	lhsPoints.push_back(lhs->GetWorldRT());
	lhsPoints.push_back(lhs->GetWorldRB());
	lhsPoints.push_back(lhs->GetWorldLB());

	rhsPoints.push_back(rhs->GetWorldLT());
	rhsPoints.push_back(rhs->GetWorldRT());
	rhsPoints.push_back(rhs->GetWorldRB());
	rhsPoints.push_back(rhs->GetWorldLB());

	return DetectOBB(lhsPoints, rhsPoints);
}

void CollisionSystem::RegisterCollider(Collider& collider)
{
	colliderList_[SceneSystem::Instance().GetCurrentScene()].push_back(&collider);
}

void CollisionSystem::RemoveCollider(Collider& collider)
{
	colliderList_[SceneSystem::Instance().GetCurrentScene()].remove(&collider);
}

CollisionSystem::CollisionSystem()
{

}
