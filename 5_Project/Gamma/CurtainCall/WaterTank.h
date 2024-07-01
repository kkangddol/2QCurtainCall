#pragma once
#include "GRX.h"
#include "Trigger.h"
#include "Reactant.h"
#include "Manageable.h"
using namespace GammaEngine;

class WaterTank : public GammaEngine::Component, public Reactant, public Manageable
{
public:
	WaterTank(GameObject* t);
	~WaterTank();

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual bool CheckStatus(int archIndex, int archDown, int archUp,
		int sound, int rainRatio, int skyIndex, int skyAppear,
		int actorDown, int actorUp, int actressDown, int actressUp) override;

public:
	void AddRainEmitter(ParticleEmitter* emitter);

private:
	void StartRain();
	void StopRain();
	void SetRainAmount(float interval);

private:
	std::vector<ParticleEmitter*> rainEmitters_;

	/// <summary>
	/// 기믹 완료 조건 판단용 변수들
	/// </summary>
private:
	float wheelRatio_;
};
