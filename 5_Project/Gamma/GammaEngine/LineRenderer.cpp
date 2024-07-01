#include "stdafx.h"
using namespace GammaEngine;
GammaEngine::LineRenderer::LineRenderer(GameObject* t) :Renderer(t)
{

}

GammaEngine::LineRenderer::~LineRenderer()
{

}
void GammaEngine::LineRenderer::Render()
{
    vector2 s = src;
    vector2 d = dst;
    Adjust(s);
    Adjust(d);
    GraphicSystem::DrawLine(s, d,Camera::main->Projection(), material);
}