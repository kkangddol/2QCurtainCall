#include "GammaEngine.h"
#include "WaterTank.h"
using namespace GammaEngine;

WaterTank::WaterTank(GameObject* t) : Component(t)
{

}

WaterTank::~WaterTank()
{

}

void WaterTank::Start()
{
	if (trigger_)
	{
		trigger_->updateSubject.Select<float>([](Trigger* x) 
			{
			return x->progress;
			}).Where([this](float x)
				{
				wheelRatio_ = x * 100;
				return x >= 0.3;
				}).Subscribe([this](float x)
					{
						StartRain();
						SetRainAmount(x * 20);
					});
		trigger_->updateSubject.Select<float>([](Trigger* x)
			{
			return x->progress;
			}).Where([this](float x) 
				{
				wheelRatio_ = x * 100;
				return x < 0.3;
				}).Subscribe([this](float x)
					{
						if (x <= 0)
						{
							StopRain();
						}
						else
						{
							SetRainAmount(x);
						}
					});
	}	
}

void WaterTank::Update()
{

}

bool WaterTank::CheckStatus(int archIndex, int archDown, int archUp,
	int sound, int rainRatio, int skyIndex, int skyAppear,
	int actorDown, int actorUp, int actressDown, int actressUp)
{
	int temp = 1;

	if (rainRatio != -1)
	{
		temp *= (rainRatio <= wheelRatio_);
	}

	return temp;
}

void WaterTank::AddRainEmitter(ParticleEmitter* emitter)
{
	rainEmitters_.push_back(emitter);
}

void WaterTank::StartRain()
{	
	for (auto& emitter : rainEmitters_)
	{
		emitter->SetActive(true);
	}
}

void WaterTank::StopRain()
{
	for (auto& emitter : rainEmitters_)
	{
		emitter->SetActive(false);
	}
}

void WaterTank::SetRainAmount(float interval)
{
	for (auto& emitter : rainEmitters_)
	{
		emitter->SetInterval((1 / interval) / 5, (1 / interval) / 5, 0);
	}
}
