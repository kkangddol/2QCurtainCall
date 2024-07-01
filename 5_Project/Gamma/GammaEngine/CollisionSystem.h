#pragma once
#include <unordered_map>
namespace GammaEngine
{
	class Collider;

	/// <summary>
	/// 콜리전의 현재 상태를 구분하는 enum 타입
	/// </summary>
	enum class CollisionState
	{
		Enter,
		Exit,
		Stay,
		Not
	};

	/// <summary>
	/// 콜리전 결과를 반환을 위한 구조체
	/// </summary>
	struct GammaEngineAPI CollisionResponse
	{
		CollisionResponse() : 
			state(CollisionState::Not), 
			other(nullptr), 
			distance(0.0f),
			normal(vector2()),
			contactPoint(vector2()),
			isTrigger(false) {}
		CollisionState state; //상태
		Collider* other; //다른 충돌체
		vector2 normal; //법선벡터
		vector2 contactPoint; //충돌 지점
		float distance; //침투 거리
		bool isTrigger;
	};


	/// <summary>
	/// 콜리전을 관리하는 class
	/// </summary>
	class GammaEngineAPI CollisionSystem : public Singleton<CollisionSystem>
	{
	public:
		CollisionSystem();
		~CollisionSystem();

	public:
		void Frame();
		void Initialize();
		void Add(Collider*);
		void Remove(Collider*);
	public:
		std::vector<Collider*>* colliderList;
		static std::unordered_map<Collider*, std::vector<Collider*>* >* collidedMap;
	};
}
