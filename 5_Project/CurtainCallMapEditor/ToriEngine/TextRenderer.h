#pragma once
#include "Renderer.h"

class GameObject;

/// <summary>
/// �ؽ�Ʈ ������ ������Ʈ
/// 2023.01.21 ������ ��
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
/// ���������� Camera�� left�� top�� �������� ��Բ� ��..! �³�?!
/// 2023.01.21 ������ ��
/// </summary>
private:
	const char* text_;
	float cameraLeft_;
	float cameraTop_;
};
