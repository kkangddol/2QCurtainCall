#include "Renderer.h"
#include "RenderSystem.h"
#include "SceneSystem.h"

Renderer::Renderer(GameObject* object)
	: Component(object), order_(0), r_(0.0f), g_(0.0f), b_(0.0f), a_(0.0f)
{
	RenderSystem::Instance().AddList(SceneSystem::Instance().GetCurrentScene(), this);
}

Renderer::~Renderer()
{
	RenderSystem::Instance().RemoveList(SceneSystem::Instance().GetCurrentScene(), this);
}

int Renderer::GetOrder() const
{
	return order_;
}

void Renderer::SetOrder(int order)
{
	order_ = order;
}

void Renderer::SetRGBA(float r, float g, float b, float a)
{
	r_ = r;
	g_ = g;
	b_ = b;
	a_ = a;
}
