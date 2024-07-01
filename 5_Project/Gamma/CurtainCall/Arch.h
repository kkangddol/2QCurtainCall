#pragma once
#include "GRX.h"
#include "Trigger.h"
#include "Reactant.h"
#include "Manageable.h"
using namespace GammaEngine;

class ArchDisk;
class Arch : public GammaEngine::Component, public Reactant, public Manageable
{
public:
	Arch(GameObject* t);
	~Arch();

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual bool CheckStatus(int archIndex, int archDown, int archUp,
		int sound, int rainRatio, int skyIndex, int skyAppear,
		int actorDown, int actorUp, int actressDown, int actressUp) override;

public:
	float initialHeight;
	float minHeight = 700;
	float speed = 200.0f;
	ArchDisk* disk;
	std::wstring image[3];

/// <summary>
/// 기믹 완료 조건 판단용 변수들
/// </summary>
private:
	int imageIndex_;
	bool isDown_;
	bool isUp_;
};
