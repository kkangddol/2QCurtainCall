#pragma once
using namespace GammaEngine;

class Actor : public GammaEngine::Component
{
public:
	Actor(GameObject* t);
	~Actor();

public:
	virtual void Update() override;

private:
	float initialHeight;
	float initialPosX_;
	float minHeight = 700;
	float speed = 300.0f;
	float centerHeight = 80;
	vector2 boundary = vector2(400, 320);
};
