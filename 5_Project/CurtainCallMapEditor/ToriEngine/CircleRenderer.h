#pragma once
#include "Renderer.h"

class GameObject;

class CircleRenderer : public Renderer
{
public:
	CircleRenderer(GameObject* obj);

	virtual void Render() override;

	void SetRadius(float radius)
	{
		radius_ = radius;
	}

private:
	float radius_;
};

