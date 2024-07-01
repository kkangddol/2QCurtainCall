#include "stdafx.h"
#include "Cam1.h"
#include "Cam1Script.h"
Cam1::Cam1()
{
	AddComponent<Camera>();
	AddComponent<Cam1Script>();
}