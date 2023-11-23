#include "stdafx.h"
#include <list>

#include <random>
#include "ParticleEmitter.h"

std::function<float(float)> GammaEngine::ParticleEmitter::easingFuction[31] =
{
	GammaEngine::easeLinear,
	GammaEngine::easeInBack,
	GammaEngine::easeOutBack,
	GammaEngine::easeInOutBack,
	GammaEngine::easeInBounce,
	GammaEngine::easeOutBounce,
	GammaEngine::easeInOutBounce,
	GammaEngine::easeInElastic,
	GammaEngine::easeOutElastic,
	GammaEngine::easeInOutElastic,
	GammaEngine::easeInSine,
	GammaEngine::easeOutSine,
	GammaEngine::easeInOutSine,
	GammaEngine::easeInExpo,
	GammaEngine::easeOutExpo,
	GammaEngine::easeInOutExpo,
	GammaEngine::easeInCirc,
	GammaEngine::easeOutCirc,
	GammaEngine::easeInOutCirc,
	GammaEngine::easeInQuad,
	GammaEngine::easeOutQuad,
	GammaEngine::easeInOutQuad,
	GammaEngine::easeInCubic,
	GammaEngine::easeOutCubic,
	GammaEngine::easeInOutCubic,
	GammaEngine::easeInQuart,
	GammaEngine::easeOutQuart,
	GammaEngine::easeInOutQuart,
	GammaEngine::easeInQuint,
	GammaEngine::easeOutQuint,
	GammaEngine::easeInOutQuint
};

GammaEngine::ParticleEmitter::ParticleEmitter(unsigned int maxCount, std::wstring fileName, float order)
	: duration_(10), currentTime_(0), maxCount_(maxCount),
	isLoop_(true), isActive_(true),
	shape_(Shape::ARC),
	countPerEmit_(0), countPerEmitStart_(1), countPerEmitEnd_(1), countPerEmitRange_(0), countPerEmitEase_(Ease::LINEAR),
	emitInterval_(0), emitIntervalStart_(0.1f), emitIntervalEnd_(0.1f), emitIntervalRange_(0), emitIntervalEase_(Ease::LINEAR),
	isWorldEmit_(false),
	gravity_(0),
	drag_(0), arcAngle_(360),
	minRadius_(10), maxRadius_(10),
	width_(10), height_(10),
	bitmap_(nullptr), size_(),
	isStartWithRandomAngle_(false),
	lifeTimeStart_(1), lifeTimeEnd_(1), lifeTimeRange_(0), lifeTimeEase_(Ease::LINEAR),
	speed_(0), speedStart_(10), speedEnd_(10), speedRange_(0), speedEase_(Ease::LINEAR),
	acceleration_(0), accelStart_(0), accelEnd_(0), accelRange_(0), accelEase_(Ease::LINEAR),
	deltaAngle_(0), deltaAngleStart_(0), deltaAngleEnd_(0), deltaAngleRange_(0), deltaAngleEase_(Ease::LINEAR),
	sizeOverLifeTimeStart_(100,100), sizeOverLifeTimeEnd_(100,100), sizeOverLifeTimeEase_(Ease::LINEAR),
	tintOverLifeTimeStart_(1,1,1,1), tintOverLifeTimeEnd_(1,1,1,1), tintOverLifeTimeEase_(Ease::LINEAR)
{
	//particlePool = new ObjectPool<Particle>(maxCount);
	bitmap_ = new std::wstring();
	*bitmap_ = fileName;
	LoadBitmapImage(fileName);				// 2023.02.10 강석원 이거 엔트리포인트 순서 정리하면서 살려야함

	particlePool = new std::queue<Particle*>();
	runningParticles = new std::list<Particle*>();
	returnBuffer = new std::vector<Particle*>();

	rd_ = new std::random_device();
	mt_ = new std::mt19937((*rd_)());
	emitRangeDist_ = new std::uniform_int_distribution<int>(-countPerEmitRange_, countPerEmitRange_);
	intervalRangeDist_ = new std::uniform_real_distribution<float>(-emitIntervalRange_, emitIntervalRange_);

	lifeTimeRangeDist_ = new std::uniform_real_distribution<float>(-lifeTimeRange_, lifeTimeRange_);
	speedRangeDist_ = new std::uniform_real_distribution<float>(-speedRange_, speedRange_);
	accelRangeDist_ = new std::uniform_real_distribution<float>(-accelRange_, accelRange_);
	deltaAngleRangeDist_ = new std::uniform_real_distribution<float>(-deltaAngleRange_, deltaAngleRange_);
	randomAngleDist_ = new std::uniform_real_distribution<float>(-180.0f, 180.0f);
	minusOneToOne_ = new std::uniform_real_distribution<float>(-1.0f, 1.0f);
	arcRadius_ = new std::uniform_real_distribution<float>(minRadius_, maxRadius_);
	rectX_ = new std::uniform_real_distribution<float>(-width_/2 , width_/2);
	rectY_ = new std::uniform_real_distribution<float>(-height_/2 , height_/2);


	for (int i = 0; i < maxCount; ++i)
	{
		Particle* temp = new Particle(this, *bitmap_, size_);
		temp->SetOrder(order);
		particlePool->push(temp);
	}
}

GammaEngine::ParticleEmitter::~ParticleEmitter()
{
	delete bitmap_;
	delete particlePool;
	delete runningParticles;
	delete rd_;
	delete mt_;
	delete intervalRangeDist_;
	delete lifeTimeRangeDist_;
	delete speedRangeDist_;
	delete deltaAngleRangeDist_;
	delete randomAngleDist_;
	delete minusOneToOne_;
	delete arcRadius_;
	delete rectX_;
	delete rectY_;
}

void GammaEngine::ParticleEmitter::Update()
{
	if (!isActive_)
	{
		return;
	}

	EmitParticle();

	if (duration_ <= currentTime_)
	{
		currentTime_ = 0;

		if (!isLoop_)
		{
			isActive_ = false;
		}

		return;
	}

	currentTime_ += (float)Time::deltaTime;
}

std::list<Particle*>* GammaEngine::ParticleEmitter::GetRunningParticles()
{
	return runningParticles;
}

void GammaEngine::ParticleEmitter::ApplyEase()
{
	countPerEmit_ = countPerEmitStart_ +
		(countPerEmitEnd_ - countPerEmitStart_) *
		easingFuction[(int)countPerEmitEase_](currentTime_ / duration_) +
		(*emitRangeDist_)(*mt_);

	lifeTime_ = lifeTimeStart_ +
		(lifeTimeEnd_ - lifeTimeStart_) *
		easingFuction[(int)lifeTimeEase_](currentTime_ / duration_) +
		(*lifeTimeRangeDist_)(*mt_);

	speed_ = speedStart_ +
		(speedEnd_ - speedStart_) *
		easingFuction[(int)speedEase_](currentTime_ / duration_) +
		(*speedRangeDist_)(*mt_);

	acceleration_ = accelStart_ +
		(accelEnd_ - accelStart_) *
		easingFuction[(int)accelEase_](currentTime_ / duration_) +
		(*accelRangeDist_)(*mt_);

	deltaAngle_ = deltaAngleStart_ +
		(deltaAngleEnd_ - deltaAngleStart_) *
		easingFuction[(int)deltaAngleEase_](currentTime_ / duration_) +
		(*deltaAngleRangeDist_)(*mt_);
}

void GammaEngine::ParticleEmitter::EmitParticle()
{
	if (runningParticles->size() >= maxCount_)
	{
		return;
	}

	if (emitInterval_ > 0)
	{
		emitInterval_ -= Time::deltaTime;
		return;
	}

	emitInterval_ = emitIntervalStart_ +
		(emitIntervalEnd_ - emitIntervalStart_) *
		easingFuction[(int)emitIntervalEase_](currentTime_ / duration_);

	ApplyEase();

	for (int i = 0; i < countPerEmit_; ++i)
	{
		if (particlePool->empty())
		{
			return;
		}

		Particle& particle = GetParticle();

		float lifeTime = lifeTime_;
		float radius = (*arcRadius_)(*mt_);
		float x = 0;
		float y = 0;
		float speed = speed_;
		float accelValue = acceleration_;
		float particleAngle = 0;
		float deltaAngle = deltaAngle_;
		vector2 velocity;
		vector2 accel;

		if (shape_ == Shape::ARC)
		{
			while (true)
			{
				x = (*minusOneToOne_)(*mt_);
				y = (*minusOneToOne_)(*mt_);

				vector2 randomPos(x, y);
				randomPos = randomPos.Normalize();
				x = randomPos.x;
				y = randomPos.y;

				if (-y / randomPos.Length() >= cos((arcAngle_ / 2) * 3.141592 / 180))
				{
					break;
				}
			}

			x *= radius;
			y *= radius;

			velocity.x = x;
			velocity.y = y;
			velocity = velocity.Normalize();

			accel.x = x;
			accel.y = y;
			accel = accel.Normalize();

			vector2 XY(x, y);

			particleAngle = acos(-XY.y / XY.Length()) * 180 / 3.14159265358979;
			if (XY.x > 0)
			{
				particleAngle = -particleAngle;
			}

			velocity = (velocity.ToMatrix1x3() *
				Matrix3x3::Rotate(transform.rotation) *
				Matrix3x3::Rotate(particleSystem->transform->rotation)).tovector2();

			accel = (accel.ToMatrix1x3() *
				Matrix3x3::Rotate(transform.rotation) *
				Matrix3x3::Rotate(particleSystem->transform->rotation)).tovector2();

			if (isWorldEmit_)
			{

				XY = (XY.ToMatrix1x3() *
					Matrix3x3::Rotate(transform.rotation)).tovector2();

				particleAngle = acos(-XY.y / XY.Length()) * 180 / 3.14159265358979;
				if (XY.x > 0)
				{
					particleAngle = -particleAngle;
				}

				vector2 pos(x, y);
				pos = (pos.ToMatrix1x3() *
					transform.GetLocalMatrix() *
					particleSystem->transform->GetWorldMatrix()).tovector2();

				x = pos.x;
				y = pos.y;

			}

			velocity.x = velocity.x * speed;
			velocity.y = velocity.y * speed;

			accel.x = accel.x * accelValue;
			accel.y = accel.y * accelValue;

			if (isStartWithRandomAngle_)
			{
				particleAngle = (*randomAngleDist_)(*mt_);
			}
		}
		else if (shape_ == Shape::RECT)
		{
			x = (*rectX_)(*mt_);
			y = (*rectY_)(*mt_);

			velocity.x = 0;
			velocity.y = -1;

			accel.x = 0;
			accel.y = -1;

			velocity = (velocity.ToMatrix1x3() *
				Matrix3x3::Rotate(transform.rotation) *
				Matrix3x3::Rotate(particleSystem->transform->rotation)).tovector2();

			accel = (accel.ToMatrix1x3() *
				Matrix3x3::Rotate(transform.rotation) *
				Matrix3x3::Rotate(particleSystem->transform->rotation)).tovector2();

			velocity.x = velocity.x * speed;
			velocity.y = velocity.y * speed;

			accel.x = accel.x * accelValue;
			accel.y = accel.y * accelValue;

			if (isWorldEmit_)
			{
				vector2 pos(x, y);
				pos = (pos.ToMatrix1x3() *
					transform.GetLocalMatrix() *
					particleSystem->transform->GetWorldMatrix()).tovector2();

				x = pos.x;
				y = pos.y;


				particleAngle = transform.rotation;
			}

			if (isStartWithRandomAngle_)
			{
				particleAngle = (*randomAngleDist_)(*mt_);
			}

		}

		particle.Initialize(x, y, particleAngle, 1, 1,
			lifeTime, velocity.x, velocity.y, accel.x, accel.y, deltaAngle);
	}
}

GammaEngine::Particle& GammaEngine::ParticleEmitter::GetParticle()
{
	Particle& temp = *(particlePool->front());
	particlePool->pop();
	runningParticles->push_back(&temp);
	return temp;
}

void GammaEngine::ParticleEmitter::SetLoop(bool isLoop)
{
	isLoop_ = isLoop;
}

void GammaEngine::ParticleEmitter::SetActive(bool isActive)
{
	isActive_ = isActive;
}

void GammaEngine::ParticleEmitter::SetShape(Shape shape)
{
	shape_ = shape;
}

void GammaEngine::ParticleEmitter::SetMaxCount(unsigned int count)
{
	maxCount_ = count;
}

void GammaEngine::ParticleEmitter::SetWorldEmit(bool isWorldEmit)
{
	isWorldEmit_ = isWorldEmit;
}

void GammaEngine::ParticleEmitter::SetCountPerEmit(unsigned int start, unsigned int end, int range, Ease easing)
{
	if (emitRangeDist_)
	{
		delete emitRangeDist_;
	}

	countPerEmitStart_ = start;
	countPerEmitEnd_ = end;
	countPerEmitRange_ = range;
	countPerEmitEase_ = easing;

	emitRangeDist_ = new std::uniform_int_distribution<int>(-countPerEmitRange_, countPerEmitRange_);
}

void GammaEngine::ParticleEmitter::SetInterval(float start, float end, float range, Ease easing)
{
	if (intervalRangeDist_)
	{
		delete intervalRangeDist_;
	}
	emitIntervalStart_ = start;
	emitIntervalEnd_ = end;
	emitIntervalRange_ = range;
	emitIntervalEase_ = easing;

	intervalRangeDist_ = new std::uniform_real_distribution<float>(-emitIntervalRange_, emitIntervalRange_);

}

void GammaEngine::ParticleEmitter::SetArcAngle(float angle)
{
	arcAngle_ = angle;
	//minusOneToOne = new std::uniform_real_distribution<float>(-(sin(arcAngle_ / 2 * 3.141592 / 180) * maxRadius_), (sin(arcAngle_ / 2 * 3.141592 / 180) * maxRadius_));
}

void GammaEngine::ParticleEmitter::SetGravity(float value)
{
	gravity_ = value;
}

void GammaEngine::ParticleEmitter::SetDrag(float drag)
{
	drag_ = drag;
}

void GammaEngine::ParticleEmitter::SetRadius(float minRadius, float maxRadius)
{
	if (arcRadius_)
	{
		delete arcRadius_;
	}

	minRadius_ = minRadius;
	maxRadius_ = maxRadius;
	arcRadius_ = new std::uniform_real_distribution<float>(minRadius_, maxRadius_);
}

void GammaEngine::ParticleEmitter::SetWidth(float width)
{
	if (!rectX_)
	{
		delete rectX_;
	}

	width_ = width;
	rectX_ = new std::uniform_real_distribution<float>(-width_ / 2, width_ / 2);
}

void GammaEngine::ParticleEmitter::SetHeight(float height)
{
	if (rectY_)
	{
		delete rectY_;
	}

	height_ = height;
	rectY_ = new std::uniform_real_distribution<float>(-height_ / 2, height_ / 2);
}

void GammaEngine::ParticleEmitter::LoadBitmapImage(wstring filename)
{
	(*bitmap_) = GraphicSystem::LoadBitmapImage(filename);
	size_ = GraphicSystem::GetBitmapSize(*bitmap_);
}

float GammaEngine::ParticleEmitter::GetDrag() const
{
	return drag_;
}

float GammaEngine::ParticleEmitter::GetGravity() const
{
	return gravity_;
}

bool GammaEngine::ParticleEmitter::GetIsWorldEmit() const
{
	return isWorldEmit_;
}

vector2 GammaEngine::ParticleEmitter::GetSizeStart() const
{
	return sizeOverLifeTimeStart_;
}

vector2 GammaEngine::ParticleEmitter::GetSizeEnd() const
{
	return sizeOverLifeTimeEnd_;
}

std::function<float(float)> GammaEngine::ParticleEmitter::GetSizeEase() const
{
	return easingFuction[(int)sizeOverLifeTimeEase_];
}

vector4 GammaEngine::ParticleEmitter::GetTintStart() const
{
	return tintOverLifeTimeStart_;
}

vector4 GammaEngine::ParticleEmitter::GetTintEnd() const
{
	return tintOverLifeTimeEnd_;
}

std::function<float(float)> GammaEngine::ParticleEmitter::GetTintEase() const
{
	return easingFuction[(int)tintOverLifeTimeEase_];
}

void GammaEngine::ParticleEmitter::SetDuration(float duration)
{
	duration_ = duration;
}

void GammaEngine::ParticleEmitter::StartWithRandomAngle(bool isRandom)
{
	isStartWithRandomAngle_ = isRandom;
}

void GammaEngine::ParticleEmitter::SetLifeTime(float start, float end, float range, Ease easing)
{
	if (lifeTimeRangeDist_)
	{
		delete lifeTimeRangeDist_;
	}

	lifeTimeStart_ = start;
	lifeTimeEnd_ = end;
	lifeTimeRange_ = range;
	lifeTimeRangeDist_ = new std::uniform_real_distribution<float>(-lifeTimeRange_, lifeTimeRange_);
}

void GammaEngine::ParticleEmitter::SetSpeed(float start, float end, float range, Ease easing /*= Ease::LINEAR*/)
{
	if (speedRangeDist_)
	{
		delete speedRangeDist_;
	}

	speedStart_ = start;
	speedEnd_ = end;
	speedRange_ = range;
	speedEase_ = easing;
	speedRangeDist_ = new std::uniform_real_distribution<float>(-speedRange_, speedRange_);
}

void GammaEngine::ParticleEmitter::SetAcceleration(float start, float end, float range, Ease easing /*= Ease::LINEAR*/)
{
	if (accelRangeDist_)
	{
		delete accelRangeDist_;
	}

	accelStart_ = start;
	accelEnd_ = end;
	accelRange_ = range;
	accelEase_ = easing;
	accelRangeDist_ = new std::uniform_real_distribution<float>(-accelRange_, accelRange_);
}

void GammaEngine::ParticleEmitter::SetDeltaRotate(float start, float end, float range, Ease easing /*= Ease::LINEAR*/)
{
	if (deltaAngleRangeDist_)
	{
		delete deltaAngleRangeDist_;
	}

	deltaAngleStart_ = start;
	deltaAngleEnd_ = end;
	deltaAngleRange_ = range;
	deltaAngleEase_ = easing;
	deltaAngleRangeDist_ = new std::uniform_real_distribution<float>(-deltaAngleRange_, deltaAngleRange_);
}

void GammaEngine::ParticleEmitter::SetSizeOverLifeTime(vector2 start, vector2 end, Ease easing)
{
	sizeOverLifeTimeStart_ = start;
	sizeOverLifeTimeEnd_ = end;
	sizeOverLifeTimeEase_ = easing;
}

void GammaEngine::ParticleEmitter::SetTintOverLifeTime(vector4 start, vector4 end, Ease easing)
{
	tintOverLifeTimeStart_ = start;
	tintOverLifeTimeEnd_ = end;
	tintOverLifeTimeEase_ = easing;
}

float GammaEngine::easeInSine(float x)
{
	return (float)(1 - cos((x * PI) / 2));
}

float GammaEngine::easeOutSine(float x)
{
	return (float)(sin((x * PI) / 2));
}

float GammaEngine::easeInOutSine(float x)
{
	return (float)(-(cos(PI * x) - 1) / 2);
}

float GammaEngine::easeInCubic(float x)
{
	return x * x * x;
}

float GammaEngine::easeOutCubic(float x)
{
	return (float)(1 - pow(1 - x, 3));
}

float GammaEngine::easeInOutCubic(float x)
{
	return x < 0.5 ? 4 * x * x * x : (float)(1 - pow(-2 * x + 2, 3) / 2);
}

float GammaEngine::easeInQuint(float x)
{
	return x * x * x * x * x;
}

float GammaEngine::easeOutQuint(float x)
{
	return (float)(1 - pow(1 - x, 5));
}

float GammaEngine::easeInOutQuint(float x)
{
	return x < 0.5 ? 16 * x * x * x * x * x : (float)(1 - pow(-2 * x + 2, 5) / 2);
}

float GammaEngine::easeInCirc(float x)
{
	return (float)(1 - sqrt(1 - pow(x, 2)));
}

float GammaEngine::easeOutCirc(float x)
{
	return (float)(sqrt(1 - pow(x - 1, 2)));
}

float GammaEngine::easeInOutCirc(float x)
{
	return x < 0.5 ? (float)(1 - sqrt(1 - pow(2 * x, 2))) / 2 : (float)(sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
}


float GammaEngine::easeInElastic(float x)
{
	const float c4 = (float)((2 * PI) / 3);
	return x == 0 ? 0 : x == 1 ? 1 : (float)(-pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4));
}


float GammaEngine::easeOutElastic(float x)
{
	const float c4 = (float)((2 * PI) / 3);
	return x == 0 ? 0 : x == 1 ? 1 : (float)(pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1);
}

float GammaEngine::easeInOutElastic(float x)
{
	const float c5 = (float)((2 * PI) / 4.5);
	return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? (float)(-(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2) : (float)((pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1);
}

float GammaEngine::easeInQuad(float x)
{
	return x * x;
}

float GammaEngine::easeOutQuad(float x)
{
	return 1 - (1 - x) * (1 - x);
}

float GammaEngine::easeInOutQuad(float x)
{
	return x < 0.5 ? 2 * x * x : (float)(1 - pow(-2 * x + 2, 2) / 2);
}

float GammaEngine::easeInQuart(float x)
{
	return x * x * x * x;
}

float GammaEngine::easeOutQuart(float x)
{
	return (float)(1 - pow(1 - x, 4));
}

float GammaEngine::easeInOutQuart(float x)
{
	return x < 0.5 ? 8 * x * x * x * x : (float)(1 - pow(-2 * x + 2, 4) / 2);
}

float GammaEngine::easeInExpo(float x)
{
	return x == 0 ? 0 : (float)pow(2, 10 * x - 10);
}

float GammaEngine::easeOutExpo(float x)
{
	return x == 1 ? 1 : (float)(1 - pow(2, -10 * x));
}

float GammaEngine::easeInOutExpo(float x)
{
	return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? (float)(pow(2, 20 * x - 10) / 2) : (float)((2 - pow(2, -20 * x + 10)) / 2);
}

float GammaEngine::easeInBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;
	return c3 * x * x * x - c1 * x * x;
}

float GammaEngine::easeOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;
	return (float)(1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2));
}

float GammaEngine::easeInOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;
	return x < 0.5 ? (float)((pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2) : (float)((pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2);
}

float GammaEngine::easeOutBounce(float x)
{
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}

float GammaEngine::easeInBounce(float x)
{
	return 1 - easeOutBounce(1 - x);
}

float GammaEngine::easeInOutBounce(float x)
{
	return x < 0.5 ? (1 - easeOutBounce(1 - 2 * x)) / 2 : (1 + easeOutBounce(2 * x - 1)) / 2;
}

float GammaEngine::easeLinear(float x)
{
	return x;
}