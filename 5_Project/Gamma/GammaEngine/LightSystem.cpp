#include "stdafx.h"
using namespace GammaEngine;

std::vector<Light*>* GammaEngine::LightSystem::lightList;
std::vector<LightAdapter*>* GammaEngine::LightSystem::lightAdapterList;

GammaEngine::LightSystem::LightSystem()
{
	lightList = new std::vector<Light*>();
	lightAdapterList = new std::vector<LightAdapter*>();
}

GammaEngine::LightSystem::~LightSystem()
{

}

void  GammaEngine::LightSystem::Add(Light* light)
{
	lightList->push_back(light);
}

void  GammaEngine::LightSystem::Remove(Light* light)
{
	lightList->erase(remove(lightList->begin(), lightList->end(), light), lightList->end());
}

void  GammaEngine::LightSystem::Add(LightAdapter* adapter)
{
	lightAdapterList->push_back(adapter);
}

void  GammaEngine::LightSystem::Remove(LightAdapter* adapter)
{
	lightAdapterList->erase(remove(lightAdapterList->begin(), lightAdapterList->end(),adapter),lightAdapterList->end());
}