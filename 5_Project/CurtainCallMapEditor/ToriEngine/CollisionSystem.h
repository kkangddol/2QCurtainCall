#pragma once

#include <unordered_map>
#include <list>

class Collider;
class CircleCollider2D;
class BoxCollider2D;
class Scene;

/// <summary>
/// �浹üũ�� �����ϴ� Ŭ����
/// ICollider�� �����ϴ� Ŭ������ �����ϰ� PhysicsUpdate�� �������ش�.
/// 
/// </summary>
class CollisionSystem
{
public:
	~CollisionSystem() {};

	static CollisionSystem& Instance()
	{
		static CollisionSystem instance;
		return instance;
	}

	void Initialize();
	void Finalize();

	void CheckCollision();
	bool CheckCC(CircleCollider2D* const lhs, CircleCollider2D* const rhs);
	bool CheckAABB(BoxCollider2D* lhs, BoxCollider2D* rhs);
	bool CheckOBB(BoxCollider2D* lhs, BoxCollider2D* rhs);

	void RegisterCollider(Collider& collider);
	void RemoveCollider(Collider& collider);

private:
	CollisionSystem();

	std::unordered_map<Scene*, std::list<Collider*>> colliderList_;
	std::unordered_map<Collider*, std::unordered_map<Collider*, bool>> prevStatus_;
	std::unordered_map<Collider*, std::unordered_map<Collider*, bool>> statusBuffer_;
};
