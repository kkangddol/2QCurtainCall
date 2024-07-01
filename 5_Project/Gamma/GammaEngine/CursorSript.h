#pragma once
#include "Component.h"
enum CreateMode
{
	box,
	circle
};

class CursorSript : public Component
{
public:
	CursorSript(GameObject*);
	~CursorSript();
	virtual void Start();
	virtual void Update();
	virtual void OnCollisionStay(CollisionResponse response);
// 	virtual void OnCollisionEnter(CollisionResponse response);
// 	virtual void OnCollisionExit(CollisionResponse response);
private:
	CreateMode mode= CreateMode::box;
	GameObject* hover = NULL;
	GameObject* target = NULL;
	float targetSpeed = 500;
	float targetRotateSpeed = 30;

};

