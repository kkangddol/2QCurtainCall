#pragma once
#include "Component.h"
class Cam1Script : public Component
{
public:
	Cam1Script(GameObject*);
	~Cam1Script();
	virtual void Update();
private:
	float speed = 300;
};

