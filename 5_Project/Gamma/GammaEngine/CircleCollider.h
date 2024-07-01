#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif
namespace GammaEngine
{
	class Collider;
	class Transform;
	class BoxCollider;
	struct CollisionResponse;

	/// <summary>
	/// �� �ݶ��̴� class
	/// </summary>

	class GammaEngineAPI CircleCollider :public Collider
	{
	public:
		CircleCollider(GameObject*);
		~CircleCollider();

	public:
		virtual vector2 FarthestPoint(vector2 v);
		virtual bool InBound(vector2);
		virtual CollisionResponse Collide(Collider*, bool);

	public:
		float radius;
	};
}


