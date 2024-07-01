#pragma once
using namespace GammaEngine;

class MainCamera : public GammaEngine::Component
{
public:
	MainCamera(GameObject* t);
	~MainCamera();
public:
	virtual void Start() override;
	virtual void Update() override;

	float speed = 10;
	float fixBoundary = 1000; //fixBoundarty �� padding ������ �� ������ ����
	float maxPositionX = 2000;
	float maxPositionY = 950; 
	float padding = 0.1;
	float zoomStep = 0.003f; //����
	float minScale = 1.2; //ī�޶�� �� ������ �� �Ҽ� ����
	float coefficient = 0.0015; //�Ÿ��� �ܰ� ������ �����ϴ� ��� (Ŭ���� �ް��ϰ� ����)
	TweenData* zoomOutAnimateHandler =nullptr;
	TweenData* zoomInAnimateHandler =nullptr;
};



