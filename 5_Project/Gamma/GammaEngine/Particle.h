#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// 파티클 시스템의 파티클 하나의 객체
/// 시작 속성과 끝 속성이 있어서 우선은 선형적으로 변화하면서 나아갈 예정?
/// Tween 아이디어 활용해서 추가해도 좋을 듯 하다.
/// 
/// 2023.02.06 강석원 인재원
/// </summary>
class TintEffect;
namespace GammaEngine
{
	class ParticleEmitter;

	class GammaEngineAPI Particle final
	{
	public:
		class Transform
		{
		public:
			Transform()
				: position(0, 0), rotation(0), scale(1, 1)
			{
			}

			Transform(float x, float y, float rot, float scaleX, float scaleY)
				: position(x, y), rotation(rot), scale(scaleX, scaleY)
			{
			}

		public:
			void SetTransform(float x, float y, float eulerAngle, float scaleX, float scaleY)
			{
				position.x = x;
				position.y = y;
				rotation = eulerAngle;
				scale.x = scaleX;
				scale.y = scaleY;
			}

			void Translate(float x, float y)
			{
				position.x += x;
				position.y += y;
			}

			void Rotate(float eulerAngle)
			{
				rotation += eulerAngle;
			}

			void Scale(float x, float y)
			{
				if (x < 0 || y < 0)
				{
					return;
				}

				scale.x *= x;
				scale.y *= y;
			}

		public:
			Matrix3x3 GetLocalMatrix()
			{
				Matrix3x3 localMatrix;
				localMatrix = Matrix3x3::Scale(scale.x, scale.y) * Matrix3x3::Rotate(rotation) * Matrix3x3::Translation(position.x, position.y);
				return localMatrix;
			}

		public:
			vector2 position;
			float rotation;
			vector2 scale;
		};

	public:
		Particle();
		Particle(ParticleEmitter* emitter, std::wstring bitmap, vector2 size);

		void Initialize(float x, float y, float eulerAngle, float scaleX, float scaleY,
			float lifeTime, float velocityX, float velocityY, float AccelX, float AccelY, float deltaAngle);
		void Finalize();
		void Update();
		void Render();

	public:
		Transform transform;

	private:
		ParticleEmitter* emitter_;

	public:
		void SetLifeTime(float lifeTime);
		void SetVelocity(float x, float y);
		void SetAccel(float x, float y);
		void SetDeltaAngle(float deltaAngle);
		void SetBitmap(std::wstring bitmap, vector2 size);
		float GetOrder() const;
		void SetOrder(float order);

	private:
		float lifeTime_;			// 파티클의 생명시간
		float currentTime_;			// Update하면서 지속적으로 누산. lifeTime_보다 커지면 pool에 반환
		vector2 velocity_;			// 속도는 항상 World 기준
		vector2 acceleration_;		// 속도에 맞춰 가속도도 World 기준
		float deltaAngle_;			// 파티클이 프레임당 회전할 각도 (60분법)
		std::wstring* bitmap_;
		vector2 size_;
		Material* material_;
		std::vector<IEffect*>* appliedEffect_;
		TintEffect* tint;
		float order_;
	};
}
