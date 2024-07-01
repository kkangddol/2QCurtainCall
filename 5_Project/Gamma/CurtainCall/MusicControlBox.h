#pragma once
#include "Trigger.h"
#include "Manageable.h"
#include <vector>
using namespace GammaEngine;

class MusicControlBox : public Trigger, public IInteractable, public Manageable
{
public:
	MusicControlBox(GameObject* t);
	virtual void Start() override;
	virtual void Update() override;
	//virtual void Success();
	//virtual void Fail();
	//virtual void Reset();
	virtual void Use(Player* p);

	virtual bool CheckStatus(int archIndex, int archDown, int archUp,
		int sound, int rainRatio, int skyIndex, int skyAppear,
		int actorDown, int actorUp, int actressDown, int actressUp) override;

public:
	void InitSuccess();

public:
	std::mt19937* gen;
	std::uniform_int_distribution<int>* dist;
	std::uniform_int_distribution<int>* len;
	std::vector<int> qte;
	std::vector<int> answer;
	int index = 0;
	bool success = false;
	std::vector<GameObject*> infoList;


};



