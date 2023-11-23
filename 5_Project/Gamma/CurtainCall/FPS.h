#pragma once

using namespace GammaEngine;

/// <summary>
/// 오브젝트를 낙하시키는 스크립트
/// </summary>
class FPS : public GammaEngine::Component
{
public:
	FPS(GameObject* t);
	virtual void Start() override;
	virtual void Update() override;

public:
	int count=0;
	int value=0;

};

