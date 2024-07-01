#pragma once
#include "Renderer.h"

class BoxRenderer : public Renderer
{
public:
	BoxRenderer(GameObject* obj);

	virtual void Render() override;

	void SetRect(float left, float top, float right, float bottom)
	{
		left_ = left;
		top_ = top;
		right_ = right;
		bottom_ = bottom;
	}

private:
	float left_;
	float top_;
	float right_;
	float bottom_;
};

