#pragma once
#include <vector>

namespace GammaEngine
{
	class TimerHandler;
	/// <summary>
	/// 타이머를 생성 제거 관리하는 클래스
	/// </summary>
	class GammaEngineAPI Timer : public Singleton<Timer>
	{
	public:
		Timer();
		~Timer();

	public:
		void Frame();

	public:
		static TimerHandler* Delay(float delay, bool loop, std::function<void()> callback);//일정 딜레이 이후에 Callback함수를 호출하는 타이머를 생성
		static void Cancel(TimerHandler* handler);//타이머를 제거하는 함수
		static void CancelAll();
	public:
		static std::vector<TimerHandler*>* timerHandlerList;
		static std::vector<TimerHandler*>* addTimerBuffer;
	};

}
