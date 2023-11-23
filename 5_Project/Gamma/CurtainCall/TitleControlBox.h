#pragma once
#include "Trigger.h"
#include <vector>
using namespace GammaEngine;

class TitleControlBox : public Trigger, public IInteractable
{
public:
	TitleControlBox(GameObject* t);
	virtual void Start() override;
	//virtual void Update() override;
	//virtual void Success();
	//virtual void Fail();
	//virtual void Reset();
	virtual void Use(Player* p);
	void ShowInfo();
public:
	GameObject* infoUp;
	GameObject* infoLeft;
	GameObject* infoRight;
	GameObject* infoDown;
	GameObject* infoStick;
};

