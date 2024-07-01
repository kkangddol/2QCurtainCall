#pragma once
#include "Renderer.h"

class GameObject;

/// <summary>
/// 텍스트 렌더러 컴포넌트
/// 2023.01.21 강석원 집
/// </summary>
class TextRenderer : public Renderer
{
public:
	TextRenderer(GameObject* obj);

	virtual void Render() override;

	void SetText(const char* input) 
	{
		text_ = input;
	}

	void SetPosition(float left, float top)
	{
		cameraLeft_ = left;
		cameraTop_ = top;
	}

/// <summary>
/// 강제적으로 Camera의 left와 top을 기준으로 찍게끔 함..! 맞냐?!
/// 2023.01.21 강석원 집
/// </summary>
private:
	const char* text_;
	float cameraLeft_;
	float cameraTop_;
};
