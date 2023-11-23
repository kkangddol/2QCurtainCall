#pragma once

#include "State.h"
using namespace GammaEngine;

class TitleState : public GammaEngine::Component, public State<TitleState>
{
public:
	TitleState(GameObject*);
	virtual void Start();
	virtual void Update();
	virtual void OnEnter();
	virtual void OnExit();
};