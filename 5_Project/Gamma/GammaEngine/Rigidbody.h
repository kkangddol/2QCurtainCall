#pragma once
#include <set>
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// 강체
/// </summary>
namespace GammaEngine {
	class GammaEngineAPI Rigidbody : public Component
	{
	public:
		enum ForceMode
		{
			Force, //연속적인 무게 적용 가속

			Impulse, //순간적인 무게 적용 가속

			Acceleration, //연속적인 무게 무시 가속

			VelocityChange //순간적인 무게 무시 가속
		};
	public:
		Rigidbody(GameObject* t);
		~Rigidbody();

	public:
		void AddForce(vector2 v,ForceMode mode= ForceMode::Force);
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void OnCollisionEnter(CollisionResponse) override;
		virtual void OnCollisionStay(CollisionResponse) override;
		virtual void OnCollisionExit(CollisionResponse) override;
		void UpdateMomentOfInertia();
		void SetIgnore(std::string);
		void RemoveIgnore(std::string);
	private:
		static vector2 ResolveImpulse(Rigidbody* A, Rigidbody* B, CollisionResponse res);
		static vector2 ResolveFrictionImpulse(Rigidbody* A, Rigidbody* B, CollisionResponse res);
		static void PositionalCorrection(Rigidbody* A, Rigidbody* B, CollisionResponse res);
	

	public:
		float mass;
		float drag;
		float staticFriction;
		float dynamicFriction;
		float angularDrag;
		float restitution;
		vector2 velocity;
		vector2 orient;
		vector2 torque;
		float angularVelocity;
		vector2 gravity;
		float momentOfInertia;
		bool useGravity;
		vector2 impulse;
		vector2 frictionImpulse;
		bool fixRotation;
		std::set<std::string> ignoreList;

	};
}

