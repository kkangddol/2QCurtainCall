#include "TextRenderer.h"
#include "RenderSystem.h"

#include "GameObject.h"

TextRenderer::TextRenderer(GameObject* obj)
	: Renderer(obj), text_(), cameraLeft_(0), cameraTop_(0)
{
}

void TextRenderer::Render()
{
	if (!object_->IsActive())
	{
		return;
	}

	RenderSystem::DrawText2D(
		text_,
		cameraLeft_,
		cameraTop_,
		r_,g_,b_,a_
	);
}