#include "SpriteRenderer.h"

#include "Matrix.h"
#include "RenderSystem.h"
#include "Camera.h"
#include "GameObject.h"

SpriteRenderer::SpriteRenderer(GameObject* obj)
	: Renderer(obj)
{
	flipX_ = false;
	flipY_ = false;
}

SpriteRenderer::~SpriteRenderer()
{

}

void SpriteRenderer::LoadBitmapImage(std::wstring fileName)
{
	bitmap_ = RenderSystem::LoadBitmapImage(fileName);
	size_ = RenderSystem::GetBitmapSize(bitmap_);
}

void SpriteRenderer::SetFlipX(bool val)
{
	flipX_ = val;
}

void SpriteRenderer::SetFlipY(bool val)
{
	flipY_ = val;
}

Vector2D SpriteRenderer::GetSize() const
{
	return size_;
}

void SpriteRenderer::SetSize(Vector2D size)
{
	size_ = size;
}

void SpriteRenderer::SetSize(float x, float y)
{
	size_.x = x;
	size_.y = y;
}

void SpriteRenderer::SetOffset(float x, float y)
{
	offset_.x = x;
	offset_.y = y;
}

void SpriteRenderer::SetOffset(Vector2D offset)
{
	offset_ = offset;
}

void SpriteRenderer::Render()
{
	if (!object_->IsActive())
	{
		return;
	}

	Matrix3x3 matrix = object_->transform.GetTransformMatrix() *
		Matrix3x3::Translation(offset_.x, offset_.y) * 
		Camera::main->Projection();
	Vector2D tmpSize;
	tmpSize.x = flipX_ ? -size_.x : size_.x;
	tmpSize.y = flipY_ ? -size_.y : size_.y;
	RenderSystem::DrawBitmap(bitmap_, tmpSize, matrix);
}
