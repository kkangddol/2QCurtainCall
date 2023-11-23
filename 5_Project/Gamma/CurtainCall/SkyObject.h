#pragma once
#include "GRX.h"
#include "Trigger.h"
#include "Reactant.h"
using namespace GammaEngine;


class SkyObject : public GammaEngine::Component, public Reactant
{
public:
	SkyObject(GameObject* t);
	~SkyObject();

public:
	virtual void Start();
	virtual void Update();

public:
	int index;	//-1 더미, 0 해, 1 달, 2 구름
	SkyObject* next;
	SkyObject* previous;
	vector2 velocity;
	vector2 boundary = vector2(400, 425);

};
