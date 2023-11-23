#pragma once
#include "GRX.h"
#include "Trigger.h"
#include "Reactant.h"
using namespace GammaEngine;


class TitleBoard : public GammaEngine::Component
{
public:
	TitleBoard(GameObject* t);
	~TitleBoard();

public:
	virtual void Start();
	virtual void Update();

public:
	TitleBoard* next;
	TitleBoard* previous;
	int index;
};
