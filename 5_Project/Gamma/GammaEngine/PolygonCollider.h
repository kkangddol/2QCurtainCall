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
	class GammaEngineAPI PolygonCollider :public Collider
	{
	public:
		friend class Collider;
		friend class Physics;

	public:
		PolygonCollider(GameObject*);
		~PolygonCollider();

	public:
		std::vector<vector2> ComputePoints();
		virtual vector2 FarthestPoint(vector2 v);
		virtual bool InBound(vector2);
		virtual CollisionResponse Collide(Collider*, bool);

	public:
		void SetPoints(std::vector<vector2>);
		void ResetPoints();
	private:
		std::vector<vector2>* points;
		std::vector<vector2>* simplex;
		Material* debug;
	};
}

