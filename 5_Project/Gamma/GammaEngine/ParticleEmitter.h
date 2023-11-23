#pragma once

#include <functional>
#include <random>
#include <queue>

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

using namespace GammaEngine;

/// <summary>
/// ��ƼŬ ��ü�� �����ϰ� �ʱ�ȭ�� �� �����ϴ� ��ü
/// ��ƼŬ ��ü�� ������Ʈ Ǯ�� ���� �ִ�.
/// 
/// 2023.02.07 ������ �����
/// </summary>
namespace GammaEngine
{
	class ParticleSystem;
	class Particle;
	template class GammaEngineAPI std::function<float(float)>;

	class GammaEngineAPI ParticleEmitter final
	{
	public:
		/// <summary>
		/// Easing �Լ� ���̺� �ε���
		/// </summary>
		enum class Ease
		{
			LINEAR,
			INBACK,
			OUTBACK,
			INOUTBACK,
			INBOUNCE,
			OUTBOUNCE,
			INOUTBOUNCE,
			INELASTIC,
			OUTELASTIC,
			INOUTELASTIC,
			INSINE,
			OUTSINE,
			INOUTSINE,
			INEXPO,
			OUTEXPO,
			INOUTEXPO,
			INCIRC,
			OUTCIRC,
			INOUTCIRC,
			INQUAD,
			OUTQUAD,
			INOUTQUAD,
			INCUBIC,
			OUTCUBIC,
			INOUTCUBIC,
			INQUART,
			OUTQUART,
			INOUTQUART,
			INQUINT,
			OUTQUINT,
			INOUTQUINT
		};

		enum class Shape
		{
			ARC,
			RECT
		};

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
		ParticleEmitter(unsigned int maxCount, std::wstring fileName, float order);
		~ParticleEmitter();

		void Update();

	/// <summary>
	/// �� ģ���� �����ϴ� ParticleSystem���� ����ϴ� �Լ�
	/// </summary>
	public:
		std::list<Particle*>* GetRunningParticles();

	public:
		Transform transform;
		ParticleSystem* particleSystem;
		//ObjectPool<Particle>* particlePool;	// dll�������� ���ø��������� ���������� Ǯ����ü�� emitter�� �����Ŵ�Ф�
		std::queue<Particle*>* particlePool;
		std::list<Particle*>* runningParticles;
		std::vector<Particle*>* returnBuffer;

	/// <summary>
	/// Easing ����
	/// </summary>
	private:
		static std::function<float(float)> easingFuction[31];

	/// <summary>
	/// �ڵ� �������� ���� ���������� ����ϴ� �Լ�
	/// </summary>
	private:
		void ApplyEase();
		void EmitParticle();
		Particle& GetParticle();

	/// <summary>
	/// ������ ���� ���
	/// </summary>
	private:
		std::random_device* rd_;
		std::mt19937* mt_;
		std::uniform_int_distribution<int>* emitRangeDist_;
		std::uniform_real_distribution<float>* intervalRangeDist_;
		std::uniform_real_distribution<float>* lifeTimeRangeDist_;

		std::uniform_real_distribution<float>* speedRangeDist_;
		std::uniform_real_distribution<float>* accelRangeDist_;
		std::uniform_real_distribution<float>* deltaAngleRangeDist_;
		std::uniform_real_distribution<float>* randomAngleDist_;

		std::uniform_real_distribution<float>* minusOneToOne_;
		std::uniform_real_distribution<float>* arcRadius_;
		std::uniform_real_distribution<float>* rectX_;
		std::uniform_real_distribution<float>* rectY_;

	/// <summary>
	/// ParticleEmitter�� �Ӽ��� �������� �Լ�
	/// </summary>
	public:
		float GetDrag() const;
		float GetGravity() const;
		bool GetIsWorldEmit() const;

		vector2 GetSizeStart() const;
		vector2 GetSizeEnd() const;
		std::function<float(float)> GetSizeEase() const;

		vector4 GetTintStart() const;
		vector4 GetTintEnd() const;
		std::function<float(float)> GetTintEase() const;

	/// <summary>
	/// ParticleEmitter�� �Ӽ��� �����ϴ� �Լ�
	/// </summary>
	public:
		void SetDuration(float duration);
		void SetLoop(bool isLoop);
		void SetActive(bool isActive);
		void SetShape(Shape shape);
		void SetMaxCount(unsigned int count);
		void SetWorldEmit(bool isWorldEmit);
		void SetCountPerEmit(unsigned int start, unsigned int end, int range, Ease easing = Ease::LINEAR);
		void SetInterval(float start, float end, float range, Ease easing = Ease::LINEAR);
		void SetGravity(float value);
		void SetDrag(float drag);
		void SetArcAngle(float angle);
		void SetRadius(float minRadius, float maxRadius);
		void SetWidth(float width);
		void SetHeight(float height);
		void LoadBitmapImage(wstring filename);

	/// <summary>
	/// ParticleEmitter�� �Ӽ�
	/// </summary>
	private:
		float duration_;					// ������ �ð�����
		float currentTime_;					// ���� �ð�(�ʴ���)
		bool isLoop_;						// �ݺ��ϴ� emitter����?
		bool isActive_;						// ���� ������?
		Shape shape_;						// emitter�� ���	// arc �Ǵ� rect
		unsigned int maxCount_;				// ��ƼŬ�� �ִ� ����
		bool isWorldEmit_;					// ��ƼŬ�� ����������� �Ѹ�����?

		unsigned int countPerEmit_;			// �� �� ������ ���� ���� ����
		unsigned int countPerEmitStart_;	// ������ ���� ���� ����
		unsigned int countPerEmitEnd_;		// ���� ���� ���� ����
		int countPerEmitRange_;				// ���ⷮ�� ���� ���� (+- �� ����)
		Ease countPerEmitEase_;				// easing �Լ� �ε���

		float emitInterval_;				// ���� ������� ���� �ð�
		float emitIntervalStart_;			// ���� ���� ����
		float emitIntervalEnd_;				// �� ���� ����
		float emitIntervalRange_;			// ���� ���� ���� ���� (+- �� ����)
		Ease emitIntervalEase_;				// easing �Լ� �ε���

		float gravity_;						// �߷°�
		float drag_;						// ����(0~1 ������ ������ �ش�.)
		float arcAngle_;					// ������ ����	// 0�̸� Up	// emitter ����� ��(ȣ)�϶� ��ȿ
		float minRadius_;					// ����� arc�϶� ����� �ּ� ������	// ��ƼŬ�� ���� ��ġ
		float maxRadius_;					// ����� arc�϶� ����� �ִ� ������	// ��ƼŬ�� ���� ��ġ
		float width_;						// ����� rect�϶� ����� �ʺ�	// ��ƼŬ�� ���� ��ġ
		float height_;						// ����� rect�϶� ����� ����	// ��ƼŬ�� ���� ��ġ
		std::wstring* bitmap_;				// ��ƼŬ �̹���
		vector2 size_;						// ��ƼŬ ������

	/// <summary>
	/// Particle�� �Ӽ��� �����ϴ� �Լ�
	/// </summary>
	public:
		void StartWithRandomAngle(bool isRandom);
		void SetLifeTime(float start, float end, float range, Ease easing = Ease::LINEAR);
		void SetSpeed(float start, float end, float range, Ease easing = Ease::LINEAR);
		void SetAcceleration(float start, float end, float range, Ease easing = Ease::LINEAR);
		void SetDeltaRotate(float start, float end, float range, Ease easing = Ease::LINEAR);
		void SetSizeOverLifeTime(vector2 start, vector2 end, Ease easing = Ease::LINEAR);
		void SetTintOverLifeTime(vector4 start, vector4 end, Ease easing = Ease::LINEAR);

	/// <summary>
	/// Particle�� �Ӽ�
	/// </summary>
	private:
		bool isStartWithRandomAngle_;	// ��ƼŬ�� ������ �� ������ ��������

		float lifeTime_;				// ��ƼŬ�� ���� (��)
		float lifeTimeStart_;			// ��ƼŬ�� ���� ���� (��)
		float lifeTimeEnd_;				// ��ƼŬ�� �� ���� (��)
		float lifeTimeRange_;			// ��ƼŬ�� ���� ���� ���� (+- �� ����)
		Ease lifeTimeEase_;				// easing �Լ� �ε���

		float speed_;
		float speedStart_;
		float speedEnd_;
		float speedRange_;
		Ease speedEase_;

		float acceleration_;
		float accelStart_;
		float accelEnd_;
		float accelRange_;
		Ease accelEase_;

		float deltaAngle_;
		float deltaAngleStart_;
		float deltaAngleEnd_;
		float deltaAngleRange_;
		Ease deltaAngleEase_;

		vector2 sizeOverLifeTimeStart_;	// ��ƼŬ�� �ð��� ���� ���� ������ ���� ��
		vector2 sizeOverLifeTimeEnd_;	// ��ƼŬ�� �ð��� ���� ���� ������ �� ��
		Ease sizeOverLifeTimeEase_;		// easing �Լ� �ε���

		vector4 tintOverLifeTimeStart_;	// ��ƼŬ�� �ð��� ���� ���� ���� ���� ��
		vector4 tintOverLifeTimeEnd_;	// ��ƼŬ�� �ð��� ���� ���� ���� �� ��
		Ease tintOverLifeTimeEase_;		// easing �Լ� �ε���
	};
}
