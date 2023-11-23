#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// ��ƼŬ �ý����� ��ƼŬ �ϳ��� ��ü
/// ���� �Ӽ��� �� �Ӽ��� �־ �켱�� ���������� ��ȭ�ϸ鼭 ���ư� ����?
/// Tween ���̵�� Ȱ���ؼ� �߰��ص� ���� �� �ϴ�.
/// 
/// 2023.02.06 ������ �����
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
		float lifeTime_;			// ��ƼŬ�� ����ð�
		float currentTime_;			// Update�ϸ鼭 ���������� ����. lifeTime_���� Ŀ���� pool�� ��ȯ
		vector2 velocity_;			// �ӵ��� �׻� World ����
		vector2 acceleration_;		// �ӵ��� ���� ���ӵ��� World ����
		float deltaAngle_;			// ��ƼŬ�� �����Ӵ� ȸ���� ���� (60�й�)
		std::wstring* bitmap_;
		vector2 size_;
		Material* material_;
		std::vector<IEffect*>* appliedEffect_;
		TintEffect* tint;
		float order_;
	};
}
