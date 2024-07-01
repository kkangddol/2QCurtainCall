#pragma once
using namespace GammaEngine;

class Player;
class Trigger;


class HighLighter : public GammaEngine::Component
{
public:
	HighLighter(GameObject* t);
	~HighLighter();
	void On();
	void Off();
	virtual void Update() override;

public:
	IEffect* effect;

private:
	bool isOn = false;
};

