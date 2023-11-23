#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif
namespace GammaEngine
{
	class Component;
	class GameObject;
	class BoxCollider;
	class CircleCollider;
	class LineCollider;

	/// <summary>
	/// 콜라이더 추상 class
	/// </summary>
	class GammaEngineAPI Collider : public Component
	{
	public:
		Collider(GameObject*);
		virtual ~Collider();

	public:
		static void DecideCollisionState(CollisionResponse&, bool, bool);
		static bool GJK(Collider* pointA, Collider* pointB, std::vector<vector2>& result);
		static bool GJK(Collider* pointA, vector2 v);
		static void EPA(Collider* A, Collider* B, std::vector<vector2>& polytope, vector2& normal, float& distance);
		static void ComputeContactPoint(Collider* A, Collider* B, vector2& contactPoint);

	private:
		static vector2 Support(Collider*, Collider*, vector2);
		static vector2 Support(Collider* A, vector2 v, vector2 direction);

	public:
		bool CompareTag(std::string str);
		bool CompareTag(char* str);
		bool CompareTags(std::vector<std::string> strList);
		bool CompareTags(std::vector<char*> strList);

	public:
		virtual bool InBound(vector2) = 0;
		virtual vector2 FarthestPoint(vector2 v) = 0;
		virtual CollisionResponse Collide(Collider*, bool) = 0;
		virtual std::vector<vector2> ComputePoints();
		virtual vector2 GetBounds();

	public:
		bool isTrigger=false;
	};


}
