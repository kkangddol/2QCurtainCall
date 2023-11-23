#include <string>
#include "Vector2D.h"

#include "UISpriteRenderer.h"

#include "Matrix.h"
#include "RenderSystem.h"
#include "Camera.h"
#include "GameObject.h"

UISpriteRenderer::UISpriteRenderer(GameObject* obj)
	: Renderer(obj)
{
	flipX_ = false;
	flipY_ = false;
}

UISpriteRenderer::~UISpriteRenderer()
{

}

void UISpriteRenderer::LoadBitmapImage(std::wstring fileName)
{
	bitmap_ = RenderSystem::LoadBitmapImage(fileName);
	size_ = RenderSystem::GetBitmapSize(bitmap_);
}

void UISpriteRenderer::SetFlipX(bool val)
{
	flipX_ = val;
}

void UISpriteRenderer::SetFlipY(bool val)
{
	flipY_ = val;
}

void UISpriteRenderer::SetSize(int width, int height)
{
	size_.x = width;
	size_.y = height;
}

void UISpriteRenderer::Render()
{
	if (!object_->IsActive())
	{
		return;
	}

	Matrix3x3 matrix = object_->transform.GetTransformMatrix() *
		Matrix3x3::Translation(offset_.x, offset_.y);
	Vector2D tmpSize;
	tmpSize.x = flipX_ ? -size_.x : size_.x;
	tmpSize.y = flipY_ ? -size_.y : size_.y;
	RenderSystem::DrawBitmap(bitmap_, tmpSize, matrix);
}
