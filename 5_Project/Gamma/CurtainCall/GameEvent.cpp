#include "GammaEngine.h"
#include "GameEvent.h"

using namespace GammaEngine;

void GameEvent::EventStart()
{
	//이벤트가 시작되면 자신이 어느 시점에 EventEnd를 호출할지 알게 된다.
	handler = Timer::Delay(endTime, false, [this]() {
		EventEnd();
		});
}

void GameEvent::EventEnd()
{

}

void GameEvent::DisposeEvent()
{
	//이벤트가 끝났을 때 Timer를 지워준다
	Timer::Cancel(handler);
}
