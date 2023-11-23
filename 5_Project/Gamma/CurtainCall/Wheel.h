#pragma once
#include "Trigger.h"
#include <random>
using namespace GammaEngine;


class Wheel : public Trigger, public IInteractable
{
public:
	Wheel(GameObject* t);
	virtual void Start() override;
	virtual void Update() override;
	//virtual void Success();
	//virtual void Fail();
	//virtual void Reset();
	virtual void Use(Player* p);

public:
	std::random_device* rd;
	std::mt19937* gen;
	std::uniform_real_distribution<float>* tick;
	GammaEngine::Transform* wheel;
	GammaEngine::GameObject* rotateL;
};

