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
/// ���⼭ Collider delete ������� �� ������ ����.
/// ��� �Ҹ�Ǵ��� �����ؾ� �� �ʿ䰡 �ִ�.
/// 
/// 22.12.28 ������ ��
/// </summary>
void CollisionSystem::Finalize()
{
}

/// <summary>
/// ��ϵ� �ݶ��̴��鿡 ���� ���� �浹üũ�� �ؼ� ���¸� ����Ѵ�.
/// ��ϵ� �ݶ��̴� : ���� ���� ������Ʈ���� �����ִ� �ݶ��̴�
/// 
/// 22.12.22 ������ �����
/// 
/// 22.12.28 ������ ���浹��
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
