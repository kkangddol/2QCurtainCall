#pragma once

#include "Trigger.h"
#include <random>

class Scaffolding : public Trigger
{
public:
	Scaffolding(GameObject* t);
	 
	virtual void Update() override;
	virtual void OnCollisionEnter(CollisionResponse);
	virtual void OnCollisionExit(CollisionResponse);
public:
	std::random_device* rd;
	std::mt19937* gen;
	std::uniform_real_distribution<float>* tick;
};

