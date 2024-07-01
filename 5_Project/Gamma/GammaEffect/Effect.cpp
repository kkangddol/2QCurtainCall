#include "Effect.h"


void Effect::SetSourceImage(std::wstring val)
{
	source = new std::wstring(val);
}

EffectId Effect::GetId()
{
	return id;
};