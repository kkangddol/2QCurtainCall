#pragma once
#include <functional>
#define TWEEN_STEP 0.01

using std::function;

namespace GammaEngine
{
	struct TweenDataF;
	struct TweenDataV;
	template class GammaEngineAPI std::function<float(float)>;
	template class GammaEngineAPI std::function<void(TweenDataF*)>;
	template class GammaEngineAPI std::function<void(TweenDataV*)>;
	/// <summary>
	/// Easing 함수 테이블 인덱스
	/// </summary>
	enum EASING
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

	/// <summary>
	/// Tween과 관련한 정보를 포함하는 기본 구조체 
	/// </summary>
	struct TweenData 
	{
		TweenData() : 
			duration(0), 
			callback(nullptr), 
			accumulation(0),
			handler(0){}
		float duration;//기간
		function<void()> callback;//콜백함수
		float accumulation;//누적
		TimerHandler* handler;//핸들러
		virtual ~TweenData()
		{
			Timer::Cancel(handler);
		}
	};

	/// <summary>
	/// Float형 TweenData
	/// </summary>
	struct TweenDataF :public TweenData
	{
		function<float(float)> easingFunc;
		float& src;
		float dst;
		float original;
		float difference;
		TweenDataF(float& s, float d, function<float(float)> ef, float dur, function<void()> cb) :src(s)
		{
			original = s;
			difference = d - s;
			dst = d;
			easingFunc = ef;
			duration = dur;
			callback = cb;
			accumulation = 0;
		};
		virtual ~TweenDataF()
		{

		}
	};

	/// <summary>
	/// vector2형 TweenData
	/// </summary>
	struct TweenDataV :public TweenData
	{
		function<float(float)> easingFunc;
		vector2& src;
		vector2 dst;
		vector2 original;
		vector2 difference;
		TweenDataV(vector2& s, vector2 d, function<float(float)> ef, float dur, function<void()> cb) :src(s)
		{
			original = s;
			difference = d - s;
			dst = d;
			easingFunc = ef;
			duration = dur;
			callback = cb;
			accumulation = 0;
		};
		virtual ~TweenDataV()
		{

		}
	};

	/// <summary>
	/// Tween 애니메이션을 생성 제거 관리하는 class
	/// </summary>
	class GammaEngineAPI Tween
	{
	public:
		Tween();
		~Tween();

	public:
		static void CancelAnimate(TweenData* data);//Tween Animation을 취소하는 함수
		static void CancelAnimate(float& data);
		static void CancelAnimate(vector2& data);
		static void CancelAll();
		static TweenData* Animate(float& src, PLAYBACK playback, float dst, EASING easing, float duration, float delay = 0, function<void()> callback = nullptr);//Tween 애니메이션을 생성하는 함수
		static TweenData* Animate(vector2& src, PLAYBACK playback, vector2 dst, EASING easing, float duration, float delay = 0, function<void()> callback = nullptr);//Tween 애니메이션을 생성하는 함수
	
	private:
		static function<float(float)> easingFuction[31];
		static function<void(TweenDataF*)> stepF[6];
		static function<void(TweenDataV*)> stepV[6];
		static std::vector<TweenData*>* tweenDataList;
	};

	static void StepOnceForwardF(TweenDataF* data);
	static void StepOnceBackwardF(TweenDataF* data);
	static void StepOncePingpongF(TweenDataF* data);
	static void StepLoopForwardF(TweenDataF* data);
	static void StepLoopBackwardF(TweenDataF* data);
	static void StepLoopPingpongF(TweenDataF* data);

	static void StepOnceForwardV(TweenDataV* data);
	static void StepOnceBackwardV(TweenDataV* data);
	static void StepOncePingpongV(TweenDataV* data);
	static void StepLoopForwardV(TweenDataV* data);
	static void StepLoopBackwardV(TweenDataV* data);
	static void StepLoopPingpongV(TweenDataV* data);

	static float easeLinear(float x);
	static float easeInSine(float x);
	static float easeOutSine(float x);
	static float easeInOutSine(float x);
	static float easeInCubic(float x);
	static float easeOutCubic(float x);
	static float easeInOutCubic(float x);
	static float easeInQuint(float x);
	static float easeOutQuint(float x);
	static float easeInOutQuint(float x);
	static float easeInCirc(float x);
	static float easeOutCirc(float x);
	static float easeInOutCirc(float x);
	static float easeInElastic(float x);
	static float easeOutElastic(float x);
	static float easeInOutElastic(float x);
	static float easeInQuad(float x);
	static float easeOutQuad(float x);
	static float easeInOutQuad(float x);
	static float easeInQuart(float x);
	static float easeOutQuart(float x);
	static float easeInOutQuart(float x);
	static float easeInExpo(float x);
	static float easeOutExpo(float x);
	static float easeInOutExpo(float x);
	static float easeInBack(float x);
	static float easeOutBack(float x);
	static float easeInOutBack(float x);
	static float easeOutBounce(float x);
	static float easeInBounce(float x);
	static float easeInOutBounce(float x);

}
