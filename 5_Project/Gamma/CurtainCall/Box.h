#pragma once
class Player;

class Box : public GammaEngine::Component, public IInteractable
{
public:
	Box(GameObject* t);

	virtual void Update();
	virtual void Use(Player*);
public:

};

