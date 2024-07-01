#pragma once
using std::function;

/// <summary>
/// 타이머 핸들러를 관리하는 class
/// </summary>
namespace GammaEngine
{
	template class GammaEngineAPI std::function<void()>;
	class GammaEngineAPI TimerHandler
	{
	public:
		TimerHandler(float, bool, function<void()>);
		~TimerHandler();

	public:
		void Frame();

	public:
		float accumulation = 0;//deltaTime을 누적
		float delay = 0;//딜레이 시간 accumulation과 비교
		bool timeOut = false;//이미 종료된 타이머는 true를 반환
		bool loop;//반복 여부
		function<void()> callback;//callback함수
	private:

	};
}


