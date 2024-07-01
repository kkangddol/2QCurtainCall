#pragma once

#include <windows.h>

/// <summary>
/// 프레임 관리를 위해 제작한 클래스
/// 
/// 22.12.18 강석원 집
/// </summary>
class TimeSystem 
{
public:
	~TimeSystem() {};

	// 싱글턴
	static TimeSystem& Instance()
	{
		static TimeSystem instance;
		return instance;
	}

	void Initialize();
	void Finalize();
	void MeasureTime();

	static double GetDeltaTime() { return deltaTime_; }
	static float GetFrameRate() { return frameRate_; }

private:
	TimeSystem();

	LARGE_INTEGER frequency_;
	LARGE_INTEGER startTick_;
	LARGE_INTEGER endTick_;

	double elipseTick_;
	static double deltaTime_;
	static float frameRate_;
};

