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
/// 파티클 객체를 생성하고 초기화한 후 방출하는 객체
/// 파티클 객체의 오브젝트 풀을 갖고 있다.
/// 
/// 2023.02.07 강석원 인재원
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
		/// Easing 함수 테이블 인덱스
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
	/// 이 친구를 관리하는 ParticleSystem에서 사용하는 함수
	/// </summary>
	public:
		std::list<Particle*>* GetRunningParticles();

	public:
		Transform transform;
		ParticleSystem* particleSystem;
		//ObjectPool<Particle>* particlePool;	// dll문제인지 템플릿문제인지 오류때문에 풀링자체를 emitter에 흡수시킴ㅠㅠ
		std::queue<Particle*>* particlePool;
		std::list<Particle*>* runningParticles;
		std::vector<Particle*>* returnBuffer;

	/// <summary>
	/// Easing 관련
	/// </summary>
	private:
		static std::function<float(float)> easingFuction[31];

	/// <summary>
	/// 코드 가독성을 위해 내부적으로 사용하는 함수
	/// </summary>
	private:
		void ApplyEase();
		void EmitParticle();
		Particle& GetParticle();

	/// <summary>
	/// 무작위 관련 멤버
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
	/// ParticleEmitter의 속성을 가져오는 함수
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
	/// ParticleEmitter의 속성을 설정하는 함수
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
	/// ParticleEmitter의 속성
	/// </summary>
	private:
		float duration_;					// 방출할 시간길이
		float currentTime_;					// 현재 시간(초단위)
		bool isLoop_;						// 반복하는 emitter인지?
		bool isActive_;						// 방출 중인지?
		Shape shape_;						// emitter의 모양	// arc 또는 rect
		unsigned int maxCount_;				// 파티클의 최대 개수
		bool isWorldEmit_;					// 파티클을 월드기준으로 뿌리는지?

		unsigned int countPerEmit_;			// 한 번 방출할 때의 방출 개수
		unsigned int countPerEmitStart_;	// 시작할 때의 방출 개수
		unsigned int countPerEmitEnd_;		// 끝날 때의 방출 개수
		int countPerEmitRange_;				// 방출량의 랜덤 범위 (+- 로 적용)
		Ease countPerEmitEase_;				// easing 함수 인덱스

		float emitInterval_;				// 다음 방출까지 남은 시간
		float emitIntervalStart_;			// 시작 방출 간격
		float emitIntervalEnd_;				// 끝 방출 간격
		float emitIntervalRange_;			// 방출 간격 랜덤 범위 (+- 로 적용)
		Ease emitIntervalEase_;				// easing 함수 인덱스

		float gravity_;						// 중력값
		float drag_;						// 저항(0~1 사이의 값으로 준다.)
		float arcAngle_;					// 방출할 각도	// 0이면 Up	// emitter 모양이 원(호)일때 유효
		float minRadius_;					// 모양이 arc일때 사용할 최소 반지름	// 파티클의 시작 위치
		float maxRadius_;					// 모양이 arc일때 사용할 최대 반지름	// 파티클의 시작 위치
		float width_;						// 모양이 rect일때 사용할 너비	// 파티클의 시작 위치
		float height_;						// 모양이 rect일때 사용할 높이	// 파티클의 시작 위치
		std::wstring* bitmap_;				// 파티클 이미지
		vector2 size_;						// 파티클 사이즈

	/// <summary>
	/// Particle의 속성을 설정하는 함수
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
	/// Particle의 속성
	/// </summary>
	private:
		bool isStartWithRandomAngle_;	// 파티클이 생성될 때 랜덤한 각도인지

		float lifeTime_;				// 파티클의 생명 (초)
		float lifeTimeStart_;			// 파티클의 시작 생명 (초)
		float lifeTimeEnd_;				// 파티클의 끝 생명 (초)
		float lifeTimeRange_;			// 파티클의 생명 랜덤 범위 (+- 로 적용)
		Ease lifeTimeEase_;				// easing 함수 인덱스

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

		vector2 sizeOverLifeTimeStart_;	// 파티클이 시간에 따라 변할 사이즈 시작 값
		vector2 sizeOverLifeTimeEnd_;	// 파티클이 시간에 따라 변할 사이즈 끝 값
		Ease sizeOverLifeTimeEase_;		// easing 함수 인덱스

		vector4 tintOverLifeTimeStart_;	// 파티클이 시간에 따라 변할 색상 시작 값
		vector4 tintOverLifeTimeEnd_;	// 파티클이 시간에 따라 변할 색상 끝 값
		Ease tintOverLifeTimeEase_;		// easing 함수 인덱스
	};
}
