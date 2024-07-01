#include "CircleRenderer.h"
#include "RenderSystem.h"
#include "GameObject.h"

CircleRenderer::CircleRenderer(GameObject* obj)
	: Renderer(obj), radius_(DEFAULTSIZE)
{
}

void CircleRenderer::Render()
{
	if (object_ == nullptr)
	{
		return;
	}

	RenderSystem::SetBrushColor(r_, g_, b_, a_);

	RenderSystem::DrawCircle(
		object_->transform.GetLocalPosition().x,
		object_->transform.GetLocalPosition().y,
		object_->transform.GetLocalScale().y * radius_
	);
}

