#pragma once
#include <Singleton.h>
namespace GammaEngine
{
	/// <summary>
	/// deltaTime을 계산하기위한 Time class  
	/// </summary>
	class GammaEngineAPI Time
	{
	public:
		Time();
		~Time();

	public:
		void Frame();

	public:
		static double deltaTime; //프레임 사이의 시간 Time.deltaTime으로 호출
		static void SetTimeScale(float timeScale);
		static double GetForceDelta();

	private:
		__int64 periodFrequency;
		__int64 curTime;
		__int64 lastTime;
		static float timeScale_;
		static double forceDeltaTime_;
	};
}
