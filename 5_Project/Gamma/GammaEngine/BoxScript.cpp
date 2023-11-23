#include "GammaEngine.h"
#include "BoxScript.h"
using namespace GammaEngine;

BoxScript::BoxScript(GameObject* t) :Component(t)
{

}

BoxScript::~BoxScript()
{

}

void BoxScript::Start()
{

}

void BoxScript::Update()
{
	
    correction = vector2();
}

void BoxScript::OnCollisionEnter(CollisionResponse response)
{

}

void BoxScript::OnCollisionStay(CollisionResponse response)
{

}

void BoxScript::OnCollisionExit(CollisionResponse response)
{

}