#pragma once
#include "Subject.h"
#include "IInteractable.h"
using namespace GammaEngine;

class Player;
class Trigger;


class Trigger : public GammaEngine::Component
{
public:
	Trigger(GameObject* t);
	~Trigger();
	virtual void Start() override;
	virtual void Update() override;
	virtual void Reset();
	virtual void RegistPlayer(Player* p);
	virtual void Toggle();
	virtual void Hold();
	virtual void OnCollisionEnter(CollisionResponse);
	virtual void OnCollisionStay(CollisionResponse);
	virtual void OnCollisionExit(CollisionResponse);

public:
	Subject<Trigger*> startSubject;
	Subject<Trigger*> updateSubject;
	Subject<Trigger*> resetSubject;
	Player* user;
	float progress;
	int padId;
	bool useDebug;

};

