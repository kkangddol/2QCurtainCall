#include "stdafx.h"
#include <string>
#include "vector2.h"
#include "Matrix.h"
#include "Particle.h"

GammaEngine::Particle::Particle()
	: emitter_(),
	transform(0, 0, 0, 1, 1),
	lifeTime_(0),
	velocity_(0, 0),
	acceleration_(0, 0),
	deltaAngle_(0),
	size_(),
	material_(new Material(vector4(0, 0, 0, 1), vector4(1, 1, 1, 1), 1)),
	order_(0)
{
	bitmap_ = new wstring();
	appliedEffect_ = new std::vector<IEffect*>();
}

GammaEngine::Particle::Particle(ParticleEmitter* emitter, std::wstring bitmap, vector2 size)
	: emitter_(emitter),
	transform(0, 0, 0, 1, 1),
	lifeTime_(0),
	velocity_(0, 0),
	acceleration_(0, 0),
	deltaAngle_(0),
	size_(size),
	material_(new Material(vector4(0, 0, 0, 1), vector4(1, 1, 1, 1), 1)),
	order_(0)
{
	bitmap_ = new wstring();
	appliedEffect_ = new std::vector<IEffect*>();
	tint = new TintEffect();
	appliedEffect_->push_back(tint);
	*bitmap_ = bitmap;
}

void GammaEngine::Particle::Initialize(float x, float y, float eulerAngle, float scaleX, float scaleY, float lifeTime, float velocityX, float velocityY, float AccelX, float AccelY, float deltaAngle)
{
	transform.SetTransform(x, y, eulerAngle, scaleX, scaleY);
	SetLifeTime(lifeTime);
	SetVelocity(velocityX, velocityY);
	SetAccel(AccelX, AccelY);
	SetDeltaAngle(deltaAngle);
	currentTime_ = 0;
}

void GammaEngine::Particle::Finalize()
{
	emitter_->returnBuffer->push_back(this);
}

void GammaEngine::Particle::Update()
{
	if (lifeTime_ <= currentTime_)
	{
		Finalize();
		return;
	}

	size_ = emitter_->GetSizeStart() +
		(emitter_->GetSizeEnd() - emitter_->GetSizeStart()) *
		emitter_->GetSizeEase()(currentTime_ / lifeTime_);

	material_->brush = emitter_->GetTintStart() +
		(emitter_->GetTintEnd() - emitter_->GetTintStart()) *
		emitter_->GetTintEase()(currentTime_ / lifeTime_);

	currentTime_ += Time::deltaTime;

	velocity_.x += acceleration_.x;
	velocity_.y += acceleration_.y;

	velocity_.x -= velocity_.x * emitter_->GetDrag();
	velocity_.y -= velocity_.y * emitter_->GetDrag();

	velocity_.y += emitter_->GetGravity();

	if (emitter_->GetIsWorldEmit())
	{
		transform.Translate(velocity_.x, velocity_.y);
	}
	else
	{
		vector2 velocityWolrdToLocal(velocity_.x, velocity_.y);

		velocityWolrdToLocal = (velocityWolrdToLocal.ToMatrix1x3() *
			(Matrix3x3::Rotate(emitter_->transform.rotation) *
				Matrix3x3::Rotate(emitter_->particleSystem->transform->rotation)).Inverse()).tovector2();
		
		transform.Translate(velocityWolrdToLocal.x, velocityWolrdToLocal.y);
	}
	transform.Rotate(deltaAngle_);

	//tint color
	tint->SetColor(material_->brush);
}

void GammaEngine::Particle::Render()
{
	Matrix3x3 matrix;

	if (emitter_->GetIsWorldEmit())
	{
		matrix = transform.GetLocalMatrix() * Camera::main->Projection();
	}
	else
	{
		matrix = transform.GetLocalMatrix() *
			emitter_->transform.GetLocalMatrix() *
			emitter_->particleSystem->transform->GetWorldMatrix() *
			Camera::main->Projection();
	}

	GraphicSystem::DrawBitmap(
		*bitmap_,
		size_,
		matrix,
		material_,
		appliedEffect_);
}

void GammaEngine::Particle::SetLifeTime(float lifeTime)
{
	lifeTime_ = lifeTime;
}

void GammaEngine::Particle::SetVelocity(float x, float y)
{
	velocity_.x = x;
	velocity_.y = y;
}

void GammaEngine::Particle::SetAccel(float x, float y)
{
	acceleration_.x = x;
	acceleration_.y = y;
}

void GammaEngine::Particle::SetDeltaAngle(float deltaAngle)
{
	deltaAngle_ = deltaAngle;
}

void GammaEngine::Particle::SetBitmap(std::wstring bitmap, vector2 size)
{
	*bitmap_ = bitmap;
	size_ = size;
}

float GammaEngine::Particle::GetOrder() const
{
	return order_;
}

void GammaEngine::Particle::SetOrder(float order)
{
	order_ = order;
}
