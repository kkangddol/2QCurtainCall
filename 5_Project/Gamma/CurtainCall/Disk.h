#pragma once
#include "Trigger.h"
#include "Reactant.h"
#include <random>
using namespace GammaEngine;



class Disk : public Trigger, public IInteractable
{
protected:
	enum DiskState {
		R,
		G,
		B
	};
public:
	Disk(GameObject* t);
	//virtual void Start() override;
	virtual void Update() override;
	//virtual void Success();
	//virtual void Fail();
	//virtual void Reset();
	virtual void Use(Player* p);

public:
	DiskState state = R;
	float term = 1.0f;
};

