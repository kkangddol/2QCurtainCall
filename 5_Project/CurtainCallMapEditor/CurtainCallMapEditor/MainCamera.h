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
	float fixBoundary = 300; //fixBoundarty �� padding ������ �� ������ ����
	float maxPositionX = 500; //fixBoundarty �� padding ������ �� ������ ����
	float maxPositionY = 420; //fixBoundarty �� padding ������ �� ������ ����
	float padding = 10;
	float zoomStep = 0.005f; //����
	float minScale = 1; //ī�޶�� �� ������ �� �Ҽ� ����
	float maxScale = 1.7; //ī�޶�� �� ������ �� �Ҽ� ����
	float coefficient = 0.4f; //�Ÿ��� �ܰ� ������ �����ϴ� ��� (Ŭ���� �ް��ϰ� ����)

	std::wstring str = L"������";
	
};

