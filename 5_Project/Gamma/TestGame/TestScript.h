#pragma once

using namespace GammaEngine;

class TestScript : public GammaEngine::Component
{
	TestScript(GameObject* g);
	~TestScript();
	virtual void Start() override;
	virtual void Update() override;
};

