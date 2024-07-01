#pragma once
#include "Component.h"

#define DEFAULTSIZE 50

class GameObject;

/// <summary>
/// �������� ������ ����
/// D2D���� �׷��޶�� ��û�Ѵ�
/// 
/// 22.12.28 ������ �����
/// </summary>
class Renderer : public Component
{
public:
	Renderer(GameObject* object);
	virtual ~Renderer();
	virtual void Render() abstract;
	int GetOrder() const;
	void SetOrder(int order);
	void SetRGBA(float r, float g, float b, float a);

protected:
	int order_;
	float r_;
	float g_;
	float b_;
	float a_;
};

