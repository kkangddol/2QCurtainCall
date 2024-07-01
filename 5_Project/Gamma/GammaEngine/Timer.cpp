#include "stdafx.h"
using namespace GammaEngine;
std::vector<TimerHandler*>* Timer::timerHandlerList;
std::vector<TimerHandler*>* Timer::addTimerBuffer;

GammaEngine::Timer::Timer()
{
	timerHandlerList = new std::vector<TimerHandler*>();
	addTimerBuffer = new std::vector<TimerHandler*>();
}

GammaEngine::Timer::~Timer()
{

}

TimerHandler* GammaEngine::Timer::Delay(float delay, bool loop, function<void()> callback)
{
	TimerHandler* newHandler =new TimerHandler(delay, loop, callback);
	addTimerBuffer->push_back(newHandler);
	return newHandler;
}

void GammaEngine::Timer::Cancel(TimerHandler* handler)
{
	handler->timeOut = true;
}

void GammaEngine::Timer::CancelAll()
{
	for (auto handler : *timerHandlerList)
	{
		handler->timeOut = true;
	}
		
}

void GammaEngine::Timer::Frame()
{

	for (auto iter : *addTimerBuffer)
	{
		timerHandlerList->push_back(iter);
	}
	addTimerBuffer->clear();
	for (auto iter : *timerHandlerList)
	{
		iter->Frame();
	}

	timerHandlerList->erase(remove_if(timerHandlerList->begin(), timerHandlerList->end(), [](TimerHandler* x) {
	if (x->timeOut)
	{
		delete x;
		return true;
	}
	else
	{
		return false;
	}}), timerHandlerList->end());
}