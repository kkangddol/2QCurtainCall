#pragma once
#include "Component.h"
class Box2Script : public Component
{
public:
	Box2Script(GameObject*);
	~Box2Script();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void OnCollisionEnter(CollisionResponse);
	virtual void OnCollisionExit(CollisionResponse);
private:

};

