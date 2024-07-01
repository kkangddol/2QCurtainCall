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
	class CircleCollider;
	struct CollisionResponse;

	/// <summary>
	/// 박스 콜라이더 class
	/// </summary>
	class GammaEngineAPI BoxCollider :public Collider
	{
	public:
		friend class Collider;
		friend class Physics;

	public:
		BoxCollider(GameObject*);
		~BoxCollider();

	public:
		virtual std::vector<vector2> ComputePoints();
		virtual vector2 FarthestPoint(vector2 v);
		virtual bool InBound(vector2);
		virtual CollisionResponse Collide(Collider*, bool);
	
	public:
		void SetBounds(vector2);
		virtual vector2 GetBounds();
		void ResetPoints();
	private:
		vector2 bounds;
		std::vector<vector2>* simplex;
		Material* debug;
	};
}

