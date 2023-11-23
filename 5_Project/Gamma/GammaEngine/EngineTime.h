#pragma once
#include <Singleton.h>
namespace GammaEngine
{
	/// <summary>
	/// deltaTime�� ����ϱ����� Time class  
	/// </summary>
	class GammaEngineAPI Time
	{
	public:
		Time();
		~Time();

	public:
		void Frame();

	public:
		static double deltaTime; //������ ������ �ð� Time.deltaTime���� ȣ��
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
