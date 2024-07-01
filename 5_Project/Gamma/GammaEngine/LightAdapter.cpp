#include "stdafx.h"

using namespace  GammaEngine;

GammaEngine::LightAdapter::LightAdapter(GameObject* t) : Component(t)
{
	LightSystem::Add(this);
}

GammaEngine::LightAdapter::~LightAdapter()
{
	LightSystem::Remove(this);
}


void GammaEngine::LightAdapter::Start()
{
	for (auto light : *LightSystem::lightList)
	{
		IEffect* effect = nullptr;
		if (dynamic_cast<PointLight*>(light))
		{
			effect = new PointLightEffect();
		}
		else if (dynamic_cast<DistantLight*>(light))
		{
			effect = new DistantLightEffect();
		}
		else if (dynamic_cast<SpotLight*>(light))
		{
			effect = new SpotLightEffect();
		}
		effectList[light] = effect;
		if (GetComponent<BitmapRenderer>())
		{
			GetComponent<BitmapRenderer>()->AddEffect(effect);
		}
		else if (GetComponent<SpineRenderer>())
		{
			GetComponent<SpineRenderer>()->AddEffet(effect);
		}
	}
}

void GammaEngine::LightAdapter::Update()
{
	for (auto light : *LightSystem::lightList)
	{
		if (dynamic_cast<PointLight*>(light))
		{
			auto effect = dynamic_cast<PointLightEffect*>(effectList[light]);
			auto light_ = dynamic_cast<PointLight*>(light);
			vector2 lightPos2D = light_->transform->position;
			lightPos2D = (lightPos2D.ToMatrix1x3() * Camera::main->Projection()).tovector2();
			vector3 lightPos = vector3(lightPos2D.x, lightPos2D.y, light_->z);
			effect->SetLightPosition(lightPos);
			effect->SetDiffuseConstant(light_->GetMagnitude());
			effect->SetSpecularConstant(light_->GetMagnitude());
			effect->SetSpecularExponent(20);
			effect->SetColor(light_->GetColor());
		}
		else if (dynamic_cast<DistantLight*>(light))
		{
			auto effect = dynamic_cast<DistantLightEffect*>(effectList[light]);
			auto light_ = dynamic_cast<DistantLight*>(light);
			effect->SetAzimuth(light_->GetAzimuth());
			effect->SetElevation(light_->GetElvation());
			effect->SetDiffuseConstant(light_->GetMagnitude());
			effect->SetSpecularConstant(light_->GetMagnitude());
			effect->SetSpecularExponent(20);
			effect->SetColor(light_->GetColor());
		}
		else if (dynamic_cast<SpotLight*>(light))
		{
			auto effect = dynamic_cast<SpotLightEffect*>(effectList[light]);
			auto light_ = dynamic_cast<SpotLight*>(light);
			vector2 lightPos2D = light_->transform->position;
			lightPos2D = (lightPos2D.ToMatrix1x3() * Camera::main->Projection()).tovector2();
			vector3 lightPos = vector3(lightPos2D.x, lightPos2D.y, light_->z);
			effect->SetLightPosition(lightPos);

			vector3 lightAt = light_->GetAt();
			vector2 lightAt2D = (vector2(lightAt.x, lightAt.y).ToMatrix1x3() * Camera::main->Projection()).tovector2();
			lightAt = vector3(lightAt2D.x, lightAt2D.y, lightAt.z);

			effect->SetPointsAt(lightAt);
			effect->SetFocus(light_->GetFocus());
			effect->SetLimitingConeAngle(light_->GetConeAngle());
			effect->SetDiffuseConstant(light_->GetMagnitude());
			effect->SetSpecularConstant(light_->GetMagnitude());
			effect->SetSpecularExponent(20);
			effect->SetColor(light_->GetColor());
		}

	}
}

void GammaEngine::LightAdapter::AddLight(Light* light)
{
	IEffect* effect = nullptr;
	if (dynamic_cast<PointLight*>(light))
	{
		effect = new PointLightEffect();
	}
	else if (dynamic_cast<DistantLight*>(light))
	{
		effect = new DistantLightEffect();
	}
	else if (dynamic_cast<SpotLight*>(light))
	{
		effect = new SpotLightEffect();
	}
	if (GetComponent<BitmapRenderer>())
	{
		GetComponent<BitmapRenderer>()->AddEffect(effect);
	}
	else if (GetComponent<SpineRenderer>())
	{
		GetComponent<SpineRenderer>()->AddEffet(effect);
	}
}

