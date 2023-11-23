#include "BoxRenderer.h"
#include "RenderSystem.h"
#include "GameObject.h"
#include "Vector2D.h"

BoxRenderer::BoxRenderer(GameObject* obj)
	: Renderer(obj), left_(-DEFAULTSIZE), top_(-DEFAULTSIZE), right_(DEFAULTSIZE), bottom_(DEFAULTSIZE)
{
}

void BoxRenderer::Render()
{
	RenderSystem::SetBrushColor(r_, g_, b_, a_);

	/// <summary>
	/// DrawLine으로 꼭짓점을 이어 다각형을 그리는 방식.
	/// 2023.01.21 강석원 집
	/// </summary>
	Vector2D LT = object_->transform.SRT(left_, top_);
	Vector2D RT = object_->transform.SRT(right_, top_);
	Vector2D RB = object_->transform.SRT(right_, bottom_);
	Vector2D LB = object_->transform.SRT(left_, bottom_);

	RenderSystem::DrawLine(LT.x, LT.y, RT.x, RT.y);
	RenderSystem::DrawLine(RT.x, RT.y, RB.x, RB.y);
	RenderSystem::DrawLine(RB.x, RB.y, LB.x, LB.y);
	RenderSystem::DrawLine(LB.x, LB.y, LT.x, LT.y);
}

