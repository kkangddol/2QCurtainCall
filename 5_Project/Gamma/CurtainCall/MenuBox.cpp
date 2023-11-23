#include "GammaEngine.h"
#include "MenuBox.h"


GameObject* Menu::CreateCamera(Scene* scene)
{
	//Camera
	GameObject* camera = scene->CreateObject();
	camera->AddComponent<Camera>();
	return camera;
}

GameObject* Menu::CreateBackgroundLight(Scene* scene, float x, float y)
{
	//Platform
	GameObject* light_ = scene->CreateObject();
	light_->AddComponent<PointLight>();
	light_->GetComponent<PointLight>()->SetColor(vector3(0.7, 0.7, 0.5));
	//light_->GetComponent<PointLight>()->SetMagnitude(1500);
	//light_->GetComponent<PointLight>()->SetZ(1000);

	return light_;
}

GameObject* Menu::CreateBackground(Scene* scene, float x, float y)
{
	//Platform
	GameObject* back = scene->CreateObject();
	back->transform->position = vector2(x, y);

	back->AddComponent<BitmapRenderer>();
	back->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\intro_back.png");
	back->GetComponent<BitmapRenderer>()->order = -1;
	back->AddComponent<LightAdapter>();

	GameObject* front = scene->CreateObject();
	front->transform->position = vector2(x, y);
	front->AddComponent<BitmapRenderer>();
	front->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\intro_front.png");
	front->GetComponent<BitmapRenderer>()->order = 5;
	//front->AddComponent<LightSpecularAdapter>();
	//front->AddComponent<LightDiffuseAdapter>();

	GameObject* curtainL = scene->CreateObject();
	curtainL->transform->position = vector2(-480, y);
	curtainL->AddComponent<BitmapRenderer>();
	curtainL->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\introcurtain_l.png");
	curtainL->GetComponent<BitmapRenderer>()->order = 4;


	GameObject* curtainR = scene->CreateObject();
	curtainR->transform->position = vector2(480, y);
	curtainR->AddComponent<BitmapRenderer>();
	curtainR->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\introcurtain_r.png");
	curtainR->GetComponent<BitmapRenderer>()->order = 4;

	Tween::Animate(curtainL->transform->position.x, PLAYBACK::ONCE_FORWARD, -1500, EASING::INQUART, 2);
	Tween::Animate(curtainR->transform->position.x, PLAYBACK::ONCE_FORWARD, 1500, EASING::INQUART, 2);
	Tween::Animate(front->transform->scale, PLAYBACK::ONCE_FORWARD, vector2(2, 2), EASING::INQUART, 2);


	Timer::Delay(3, false, []() {
		SceneManager::LoadScene("gameScene");
	});
	return back;
}
