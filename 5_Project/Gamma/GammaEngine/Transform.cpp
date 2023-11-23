#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::Transform::Transform(GameObject* t) :Component(t)
{
	position = vector2();
	rotation = 0;
	scale = vector2(1.0f, 1.0f);
	parent = nullptr;
}

GammaEngine::Transform::~Transform()
{

}

void GammaEngine::Transform::SetParent(Transform* t, bool keep)
{
	vector2 pos = GetWorldPosition();
	vector2 scale = GetWorldScale();
	parent = t;
	if (keep)
	{
		SetWorldScale(scale);
		SetWorldPosition(vector2(pos.x, pos.y));
	}
}

vector2 GammaEngine::Transform::GetWorldPosition()
{
	if (parent)
	{
		return (position.ToMatrix1x3()  * parent->GetWorldMatrix()).tovector2();
	}
	else
	{
		return position;
	}
}

Matrix3x3 GammaEngine::Transform::GetWorldMatrix()
{
	Matrix3x3 localMatrix;
	localMatrix = Matrix3x3::Scale(scale.x, scale.y) * Matrix3x3::Rotate(rotation) * Matrix3x3::Translation(position.x, position.y);

	if (parent)
	{
		return localMatrix * parent->GetWorldMatrix();
	}
	else
	{
		return localMatrix;
	}
}

vector2 GammaEngine::Transform::GetWorldScale()
{
	if (parent)
	{
		vector2 result;
		vector2 p = parent->GetWorldScale();
		result.x = scale.x * p.x;
		result.y = scale.y * p.y;
		return result;
	}
	else
	{
		return scale;
	}
}

void GammaEngine::Transform::SetWorldPosition(vector2 v)
{
	if(parent)
		position = v - parent->GetWorldPosition();
	else
		position = v;
}

void GammaEngine::Transform::SetWorldScale(vector2 v)
{
	if (parent)
	{
		vector2 p = parent->GetWorldScale();
		scale.x = v.x / p.x;
		scale.y = v.y / p.y;
	}
	else
	{
		scale = v;
	}
	
}