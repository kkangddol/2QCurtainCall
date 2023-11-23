#pragma once
using namespace GammaEngine;

class SpineTest : public GammaEngine::Component
{
public:
	SpineTest(GameObject* t);
	~SpineTest();
public:
	virtual void Start();
	virtual void Update();
	bool drag = false;

public:

private:
	vector2 startpoint;
	vector2 endpoint;
	vector2 altpoint;
	bool alt = false;

};



