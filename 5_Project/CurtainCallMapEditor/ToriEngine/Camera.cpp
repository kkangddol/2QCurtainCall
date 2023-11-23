#include "Camera.h"
#include "Core.h"
#include "GameObject.h"

Camera* Camera::main = nullptr;

Camera::Camera(GameObject* obj)
	: Component(obj)
{
	if (main == nullptr)
	{
		main = this;
	}
}

Camera::~Camera()
{
	if (main == this)
		main = nullptr;
}

Vector2D Camera::ScreenToWorldPoint(Vector2D screenToWorld)
{
	Vector2D center = Vector2D((float)Core::screenWidth / 2, (float)Core::screenHeight / 2);
	Vector2D result = screenToWorld *
		Matrix3x3::Translation(-center.x, -center.y) *
		Matrix3x3::Scale(orthoScale, orthoScale) *
		Matrix3x3::Translation(object_->transform.GetLocalPosition().x, object_->transform.GetLocalPosition().y);
	return result;
}

Vector2D Camera::WorldToScreenPoint(Vector2D worldToScreen)
{
	POINT point = { (LONG)worldToScreen.x, (LONG)worldToScreen.y };
	Vector2D temp = Vector2D((float)point.x, (float)point.y);
	Vector2D result = temp * Projection();
	return result;
}

Vector2D Camera::ScreenToWorldScale(Vector2D scale)
{
	return scale * orthoScale;
}

Matrix3x3 Camera::Projection()
{
	Vector2D size = Vector2D(1 / Camera::main->orthoScale, 1 / Camera::main->orthoScale);
	Vector2D center = Vector2D((float)Core::screenWidth / 2, (float)Core::screenHeight / 2);
	return  Matrix3x3::Translation(-object_->transform.GetLocalPosition().x, -object_->transform.GetLocalPosition().y) *
		Matrix3x3::Scale(size.x, size.y) * 
		Matrix3x3::Translation(center.x, center.y);
}