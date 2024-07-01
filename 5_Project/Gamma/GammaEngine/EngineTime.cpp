#include "stdafx.h"

using namespace GammaEngine;

double GammaEngine::Time::deltaTime = 0;
double GammaEngine::Time::forceDeltaTime_ = 0;

double Time::GetForceDelta()
{
    return forceDeltaTime_;
}

float GammaEngine::Time::timeScale_ = 1;

void Time::SetTimeScale(float timeScale)
{
    timeScale_ = timeScale;

    if (1 < timeScale_)
    {
        timeScale_ = 1;
    }
    
    if (timeScale_ < 0)
    {
        timeScale_ = 0;
    }
}

GammaEngine::Time::Time()
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency); 
    QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
}

GammaEngine::Time::~Time()
{

}


void GammaEngine::Time::Frame()
{
    QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
    forceDeltaTime_ = (double)(curTime - lastTime) / (double)periodFrequency;
    deltaTime = forceDeltaTime_ * timeScale_;
    lastTime = curTime;
}