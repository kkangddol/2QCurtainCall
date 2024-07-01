#pragma once
#include <unordered_map>
namespace GammaEngine
{
	class Collider;

	/// <summary>
	/// �ݸ����� ���� ���¸� �����ϴ� enum Ÿ��
	/// </summary>
	enum class CollisionState
	{
		Enter,
		Exit,
		Stay,
		Not
	};

	/// <summary>
	/// �ݸ��� ����� ��ȯ�� ���� ����ü
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
		CollisionState state; //����
		Collider* other; //�ٸ� �浹ü
		vector2 normal; //��������
		vector2 contactPoint; //�浹 ����
		float distance; //ħ�� �Ÿ�
		bool isTrigger;
	};


	/// <summary>
	/// �ݸ����� �����ϴ� class
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
