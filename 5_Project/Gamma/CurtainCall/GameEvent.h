#pragma once
using namespace GammaEngine;

class GameEvent
{
public:
	void EventStart();
	void EventEnd();
	void DisposeEvent();

	TimerHandler* handler;
	float stratTime;
	float endTime;
};

