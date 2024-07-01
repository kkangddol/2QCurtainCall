#pragma once
#include <vector>

namespace GammaEngine
{
	class TimerHandler;
	/// <summary>
	/// Ÿ�̸Ӹ� ���� ���� �����ϴ� Ŭ����
	/// </summary>
	class GammaEngineAPI Timer : public Singleton<Timer>
	{
	public:
		Timer();
		~Timer();

	public:
		void Frame();

	public:
		static TimerHandler* Delay(float delay, bool loop, std::function<void()> callback);//���� ������ ���Ŀ� Callback�Լ��� ȣ���ϴ� Ÿ�̸Ӹ� ����
		static void Cancel(TimerHandler* handler);//Ÿ�̸Ӹ� �����ϴ� �Լ�
		static void CancelAll();
	public:
		static std::vector<TimerHandler*>* timerHandlerList;
		static std::vector<TimerHandler*>* addTimerBuffer;
	};

}
