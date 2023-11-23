#pragma once
#include "GRX.h"
#include "Trigger.h"
#include "Reactant.h"
using namespace GammaEngine;


class Elevator : public GammaEngine::Component, public Reactant
{
public:
	Elevator(GameObject* t);
	~Elevator();

public:
	virtual void Start();
	virtual void Update();
	virtual void OnCollisionEnter(CollisionResponse);
	virtual void OnCollisionExit(CollisionResponse);
public:
	float initialHeight;
	float maxHeight=1200;
	float speed=200.0f;
	float movable = true;
};
