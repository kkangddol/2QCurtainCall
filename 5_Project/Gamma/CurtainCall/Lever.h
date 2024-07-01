#pragma once
#include "Trigger.h"
#include <random>
using namespace GammaEngine;



class Lever : public Trigger, public IInteractable
{
private:
	enum LeverState {
		SNAG,
		COMMON
	};
public:
	Lever(GameObject* t);
	//virtual void Start() override;
	virtual void Update() override;
	virtual void Start() override;
	//virtual void Success();
	//virtual void Fail();
	//virtual void Reset();
	virtual void Use(Player* p);
public:
	LeverState state=COMMON;
	std::mt19937* gen;
	std::uniform_real_distribution<float>* tick;
	std::uniform_real_distribution<float>* dist;
	float minTick = 0.05f;
	float maxTick = 0.1f;
	float snagProbability = 0.01f;
	float initialProgress = 0.0f;
	TweenData* _tween=nullptr;
	GammaEngine::Transform* stick;
	GameObject* L_shake;
};

