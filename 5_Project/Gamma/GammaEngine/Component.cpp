#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::Component::Component(GameObject* g):componentList((* g->componentList))
{
	gameObject = g;
	transform = g->transform;
	isEnabled = true;
}

GammaEngine::Component::~Component()
{

}


void GammaEngine::Component::Start()
{
	
}

void GammaEngine::Component::Update()
{
	
}
void GammaEngine::Component::LateUpdate()
{

}

void GammaEngine::Component::OnDestroy()
{
	
}

void GammaEngine::Component::OnDisable()
{
	
}

void GammaEngine::Component::OnEnable()
{

}

void GammaEngine::Component::OnCollisionEnter(CollisionResponse response)
{

}

void GammaEngine::Component::OnCollisionStay(CollisionResponse response)
{

}

void GammaEngine::Component::OnCollisionExit(CollisionResponse response)
{

}