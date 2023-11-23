using namespace GammaEngine;

class Player : public GammaEngine::Component
{
public:
	Player(GameObject* t);
	~Player();
public:
	virtual void Start();
	virtual void Update();
	float speed = 10;
};



