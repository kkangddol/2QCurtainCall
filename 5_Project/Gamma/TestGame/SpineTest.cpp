#include "GammaEngine.h"
#include "SpineTest.h"
#include "Subject.h"


using namespace GammaEngine;

SpineTest::SpineTest(GameObject* t) : Component(t)
{

}

SpineTest::~SpineTest()
{

}

void SpineTest::Start()
{
	GetComponent<SpineRenderer>()->LoadSpineModel("dragon", "dragon/dragon.atlas", "dragon/dragon-ess.json");
	GetComponent<SpineRenderer>()->model->animationState->setAnimation(0, "flying", true);
	Tween::Animate(transform->position.x, PLAYBACK::LOOP_PINGPONG, transform->position.x + 100, EASING::LINEAR, 1);
}

void SpineTest::Update()
{
	Subject<int> m;
// 	m.Select<float>([](int a){
// 		return 3.0f;
// 		});
}
