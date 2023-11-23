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
	float fixBoundary = 1000; //fixBoundarty ± padding 사이의 줌 배율을 유지
	float maxPositionX = 2000;
	float maxPositionY = 950; 
	float padding = 0.1;
	float zoomStep = 0.003f; //스탭
	float minScale = 1.2; //카메라는 이 값보다 줌 할수 없음
	float coefficient = 0.0015; //거리와 줌간 비율을 조정하는 계수 (클수록 급격하게 변함)
	TweenData* zoomOutAnimateHandler =nullptr;
	TweenData* zoomInAnimateHandler =nullptr;
};



