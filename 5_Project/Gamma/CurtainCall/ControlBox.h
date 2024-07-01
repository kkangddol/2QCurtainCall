#pragma once
#include <random>
#include "Trigger.h"
#include "Manageable.h"

using namespace GammaEngine;

class SkyObject;

class ControlBox : public Trigger, public IInteractable, public Manageable
{
public:
	ControlBox(GameObject* t);
	virtual void Start() override;
	virtual void Update() override;
	virtual bool CheckStatus(int archIndex, int archDown, int archUp,
		int sound, int rainRatio, int skyIndex, int skyAppear,
		int actorDown, int actorUp, int actressDown, int actressUp) override;
	//virtual void Success();
	//virtual void Fail();
	//virtual void Reset();
	virtual void Use(Player* p);
	void ShowInfo();

public:
	vector2 velocity = vector2();
	SkyObject* currentSky;
	vector2 rightPos = vector2(600, -150);
	vector2 leftPos = vector2(-600, -150);
	vector2 center = vector2(0, -130);

	float moveSpeed = 300;
	int index = 0;

	GameObject* lb;
	GameObject* rb;
	GameObject* L_shake;
	GameObject* L_updown;
	GameObject* popupbubble;
	GameObject* actorA;
	GameObject* actorB;
	GameObject* sun_moon_cloud;

public:
	void SetActorNeutral();
	void SetActorDown();
	void SetActorUp();
	void SetActressNeutral();
	void SetActressDown();
	void SetActressUp();

	/// <summary>
	/// 기믹 완료 조건 판단용 변수들
	/// </summary>
private:
	bool isSkyAppear_;
	bool isActorDown_;
	bool isActorUp_;
	bool isActressDown_;
	bool isActressUp_;
};
