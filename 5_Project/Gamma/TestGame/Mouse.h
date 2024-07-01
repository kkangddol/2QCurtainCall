using namespace GammaEngine;

class Mouse : public GammaEngine::Component
{
public:
	Mouse(GameObject* t);
	~Mouse();
public:
	virtual void Start();
	virtual void Update();
	virtual void OnCollisionEnter(CollisionResponse res);
	virtual void OnCollisionExit(CollisionResponse res);
	bool drag = false;

public:

private:
	vector2 startpoint;
	vector2 endpoint;
	vector2 altpoint;
	bool alt = false;
	
};


	
