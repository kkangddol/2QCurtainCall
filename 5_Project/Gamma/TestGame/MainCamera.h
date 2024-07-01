using namespace GammaEngine;

class MainCamera : public GammaEngine::Component
{
public:
	MainCamera(GameObject* t);
	~MainCamera();
public:
	virtual void Start();
	virtual void Update();
	float speed = 10;
};
