#pragma once
using namespace GammaEngine;
class BoxScript : public GammaEngine::Component
{
public:
	BoxScript(GameObject*);
	~BoxScript();
	virtual void Start();
	virtual void Update();
	virtual void OnCollisionEnter(CollisionResponse);
	virtual void OnCollisionStay(CollisionResponse);
	virtual void OnCollisionExit(CollisionResponse);
public:
	vector2 gravity = vector2::Down;
	vector2 correction;
private:

};

