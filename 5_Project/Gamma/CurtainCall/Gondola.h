#pragma once
#include "GRX.h"
#include "Trigger.h"
#include "Reactant.h"
#include "Manageable.h"
using namespace GammaEngine;

class Gondola : public GammaEngine::Component, public Reactant
{
public:
	Gondola(GameObject* t);
	~Gondola();

public:
	virtual void Start() override;
	virtual void Update() override;

public:
	int index;	//1 actor, 2 actress

private:
	ControlBox* controlBox_;


private:
	float initialHeight;
	float initialPosX_;
	float minHeight = 700;
	float speed = 300.0f;


	/// <summary>
	/// 기믹 완료 조건 판단용 변수들
	/// </summary>
private:
	bool isActorDown_;
	bool isActorUp_;
	bool isActressDown_;
	bool isActressUp_;
	vector2 velocity;
	vector2 boundary = vector2(400, 320);
	float centerHeight=80;
};
