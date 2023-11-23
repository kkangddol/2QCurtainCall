#include "GammaEngine.h"
#include "HighLighter.h"

using namespace GammaEngine;

HighLighter::HighLighter(GameObject* t) : Component(t)
{
	effect = new HighLightEffect();
}

HighLighter::~HighLighter()
{

}

void HighLighter::On()
{
	if (!isOn)
	{
		GetComponent<BitmapRenderer>()->AddEffect(effect);
		isOn = true;
	}
}

void HighLighter::Off()
{
	if (isOn)
	{
		GetComponent<BitmapRenderer>()->RemoveEffect(effect);
		isOn = false;
	}
}

void HighLighter::Update()
{
	if (effect)
	{
		vector3 pos = vector3(transform->position.x, transform->position.y, 100);
		dynamic_cast<HighLightEffect*>(effect)->SetPosition(pos);
	}
	if (transform->parent)
	{
		if (transform->parent->GetComponent<HighLighter>())
		{
			if(transform->parent->GetComponent<HighLighter>()->isOn)
				transform->GetComponent<HighLighter>()->On();
			else
				transform->GetComponent<HighLighter>()->Off();
		}
	}
}