#include "GammaEngine.h"
#include "ArchDisk.h"
#include "Arch.h"
using namespace GammaEngine;

Arch::Arch(GameObject* t) : Component(t)
{

}

Arch::~Arch()
{

}

void Arch::Start()
{
	image[0] = GraphicSystem::LoadBitmapImage(L"Resources\\Object\\arch_castle.png");
	image[1] = GraphicSystem::LoadBitmapImage(L"Resources\\Object\\arch_forest.png");
	image[2] = GraphicSystem::LoadBitmapImage(L"Resources\\Object\\arch_wave.png");
	initialHeight = transform->position.y;
	if (trigger_)
	{
		trigger_->updateSubject.Select<float>([](Trigger* x) {
			return x->progress;
		}).Where([this](float x) {
			return x >= 1;
		}).Subscribe([this](float y) {
			if (transform->position.y < initialHeight + minHeight)
			{
				transform->position.y += speed * Time::deltaTime;
				isUp_ = false;
				isDown_ = false;
			}
			else
			{
				isDown_ = true;
			}
		});

		trigger_->updateSubject.Select<float>([](Trigger* x) {
			return x->progress;
		}).Where([this](float x) {
			return x <= 0;
		}).Subscribe([this](float y) {
			if (initialHeight < transform->position.y)
			{
				transform->position.y -= speed * Time::deltaTime;
				isUp_ = false;
				isDown_ = false;
			}
			else
			{
				isUp_ = true;
			}
		});
	}
	if (disk)
	{
		disk->updateSubject.Select<int>([](auto x)
		{
			return x->progress*2;
		}).Subscribe([this](int x) {
			auto renderer = GetComponent<BitmapRenderer>();
			renderer->LoadBitmapImage(image[x]);
			imageIndex_ = x;
		});
	}
}

void Arch::Update()
{

}

bool Arch::CheckStatus(int archIndex, int archDown, int archUp,
	int sound, int rainRatio, int skyIndex, int skyAppear,
	int actorDown, int actorUp, int actressDown, int actressUp)
{
	int temp = 1;

	if (archIndex != -1)
	{
		temp *= (imageIndex_ == archIndex);
	}

	if (archDown != -1)
	{
		temp *= (isDown_ == archDown);
	}

	if (archUp != -1)
	{
		temp *= (isUp_ == archUp);
	}

	return temp;
}
