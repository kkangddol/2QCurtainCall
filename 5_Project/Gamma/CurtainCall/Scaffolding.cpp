#include "GammaEngine.h"
#include "Scaffolding.h"
#include "Player.h"

Scaffolding::Scaffolding(GameObject* t) : Trigger(t)
{
	
}

void Scaffolding::Update()
{

	std::vector<std::string> tags;
	tags.push_back("player");
	tags.push_back("Box");
	auto res2 = Physics::Raycast(transform->position + vector2(-100, 0), transform->position + vector2::Up * 70, tags);
	auto res1 = Physics::Raycast(transform->position+vector2(100,0), transform->position + vector2::Up * 70, tags);
	if (res1.hit || res2.hit)
	{
		GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\scaffolding_pressed.png");
		progress = 1.0f;
	}
	else
	{
		GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\scaffolding_original.png");
		progress = 0.0f;
	}
	Trigger::Update();
}

void Scaffolding::OnCollisionEnter(CollisionResponse res)
{
	
}

void Scaffolding::OnCollisionExit(CollisionResponse res)
{
	progress = 0;
}