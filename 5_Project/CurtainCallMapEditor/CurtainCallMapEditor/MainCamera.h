#pragma once
#include <string>

class MainCamera : public Component
{
public:
	MainCamera(GameObject* obj);
	~MainCamera();
public:
	virtual void Update() override;
	float speed = 500;
	float fixBoundary = 300; //fixBoundarty ± padding 사이의 줌 배율을 유지
	float maxPositionX = 500; //fixBoundarty ± padding 사이의 줌 배율을 유지
	float maxPositionY = 420; //fixBoundarty ± padding 사이의 줌 배율을 유지
	float padding = 10;
	float zoomStep = 0.005f; //스탭
	float minScale = 1; //카메라는 이 값보다 줌 할수 없음
	float maxScale = 1.7; //카메라는 이 값보다 줌 할수 없음
	float coefficient = 0.4f; //거리와 줌간 비율을 조정하는 계수 (클수록 급격하게 변함)

	std::wstring str = L"여기임";
	
};

