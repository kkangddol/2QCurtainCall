#include "GammaEngine.h"
#include "GameEvent.h"

using namespace GammaEngine;

void GameEvent::EventStart()
{
	//�̺�Ʈ�� ���۵Ǹ� �ڽ��� ��� ������ EventEnd�� ȣ������ �˰� �ȴ�.
	handler = Timer::Delay(endTime, false, [this]() {
		EventEnd();
		});
}

void GameEvent::EventEnd()
{

}

void GameEvent::DisposeEvent()
{
	//�̺�Ʈ�� ������ �� Timer�� �����ش�
	Timer::Cancel(handler);
}
