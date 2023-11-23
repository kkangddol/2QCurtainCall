#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::TimerHandler::~TimerHandler()
{

}

GammaEngine::TimerHandler::TimerHandler(float d, bool l, function<void()> c)
{
	delay = d;
	loop = l;
	callback = c;
}

void GammaEngine::TimerHandler::Frame()
{                       
	if (!timeOut)
	{
		accumulation += (float)Time::GetForceDelta();
		if (delay <= accumulation)
		{
			callback();
			if (!loop)
			{
				Timer::Cancel(this);
			}
			else
			{
				accumulation = 0;
			}
		}
	}
}