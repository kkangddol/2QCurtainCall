#pragma once

using namespace GammaEngine;

/// <summary>
/// ������Ʈ�� ���Ͻ�Ű�� ��ũ��Ʈ
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

