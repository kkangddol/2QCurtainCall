#pragma once
#include <string>
#include "../Common/vector2.h"
#include "../Common/vector3.h"
#include "../Common/vector4.h"
#include "../Common/Matrix.h"
#include "../Common/Render.h"

class Effect : public IEffect
{
public:
	EffectId id;
	std::wstring* source;

public:
	virtual EffectId GetId();

	void SetSourceImage(std::wstring);
};
