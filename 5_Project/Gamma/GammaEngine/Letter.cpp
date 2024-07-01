#include "stdafx.h"

Letter::Letter(wchar_t value) :
	value(value) { 
	material = Material(vector4(0, 0, 0, 0), vector4(0, 0, 0, 0), 1);
}

Letter::~Letter()
{
}