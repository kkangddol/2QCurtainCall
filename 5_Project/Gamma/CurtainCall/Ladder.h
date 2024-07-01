#pragma once
class Player;

class Ladder : public GammaEngine::Component, public IInteractable
{
public:
	Ladder(GameObject* t);

	virtual void Update();
	virtual void Start();
	virtual void Use(Player*);
public:
	float bottom;
	float top;
	float offset = 1;
};

