#pragma once
#include "Effect.h"
#include "HighLightEffect.h"


HighLightEffect::HighLightEffect()
{
	id = EffectId::HighLightEffect;
	color = vector3(1, 1, 1);
	position = vector3(0.0f, 0.0f, 0.0f);
	
}

void HighLightEffect::SetColor(vector3 val)
{
	color = val;
}

void HighLightEffect::SetPosition(vector3 val)
{
	position = val;
}


