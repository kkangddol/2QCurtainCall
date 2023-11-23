#include "TimeSystem.h"

double TimeSystem::deltaTime_ = 0;
float TimeSystem::frameRate_ = 0;

TimeSystem::TimeSystem()
	:frequency_(LARGE_INTEGER()),
	startTick_(LARGE_INTEGER()),
	endTick_(LARGE_INTEGER()),
	elipseTick_(0.0)
{

}

/// TimeSystem 초기화
/// 22.12.18 강석원 집
void TimeSystem::Initialize()
{
	QueryPerformanceFrequency(&frequency_);
	QueryPerformanceCounter(&startTick_);	// 초기 시작 값
}

void TimeSystem::Finalize()
{

}

/// 한 프레임에 걸린 시간 측정 및 델타타임 계산
/// 22.12.18 강석원 집
void TimeSystem::MeasureTime()
{
	QueryPerformanceCounter(&endTick_);

	elipseTick_ = (double)(endTick_.QuadPart - startTick_.QuadPart) /
		(double)(frequency_.QuadPart);
	deltaTime_ = elipseTick_;// *1000;	// 1000을 곱하면 ms 단위 안곱하면 s단위
	if (deltaTime_ != 0)
	{
		frameRate_ = 1 / deltaTime_;	// 초당 프레임
	}

	QueryPerformanceCounter(&startTick_);
}

