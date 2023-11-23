#include "GammaEngine.h"
#include "TitleBox.h"
#include "TitleControlBox.h"
#include "TitleBoard.h"
#include "TitleManager.h"



GameObject* Title::CreateCamera(Scene* scene)
{
	//Camera
	GameObject* camera = scene->CreateObject();
	camera->AddComponent<Camera>();
	return camera;
}

GameObject* Title::CreateBackgroundLight(Scene* scene, float x, float y)
{
	//Platform
	GameObject* light_ = scene->CreateObject();
	light_->AddComponent<PointLight>();
	light_->GetComponent<PointLight>()->SetColor(vector3(0.5, 0.5, 0.2));
	light_->GetComponent<PointLight>()->SetMagnitude(10);
	light_->GetComponent<PointLight>()->SetZ(1000);
	return light_;
}

GameObject* Title::CreateBackground(Scene* scene, float x, float y)
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
	front->GetComponent<BitmapRenderer>()->order = 10;
	//front->AddComponent<LightSpecularAdapter>();
	//front->AddComponent<LightDiffuseAdapter>();

	return back;
}

GameObject* Title::CreateBlock(Scene* scene, float x, float y, float sizeX, float sizeY)
{
	//Platform
	GameObject* platform_ = scene->CreateObject();
	platform_->transform->position = vector2(x, y);

	platform_->AddComponent<BitmapRenderer>();
	platform_->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\secondfloor_L.png");
	platform_->GetComponent<BitmapRenderer>()->size = vector2(sizeX, sizeY);

	platform_->AddComponent<BoxCollider>();
	platform_->GetComponent<BoxCollider>()->SetBounds(vector2(sizeX, sizeY));

	platform_->AddComponent<Rigidbody>();
	platform_->GetComponent<Rigidbody>()->useGravity = false;
	platform_->GetComponent<Rigidbody>()->mass = 0;

	platform_->tag = new std::string("Obstacle");

	return platform_;
}

GameObject* Title::CreateControlBox(Scene* scene, float x, float y)
{
	GameObject* controlBox = scene->CreateObject();
	controlBox->transform->position = vector2(x,y);
	controlBox->transform->scale = vector2(0.8, 0.8);
	controlBox->AddComponent<BitmapRenderer>();
	controlBox->GetComponent<BitmapRenderer>()->order=3;
	controlBox->AddComponent<BoxCollider>();
	controlBox->GetComponent<BoxCollider>()->SetBounds(vector2(100, 100));
	controlBox->GetComponent<BoxCollider>()->isTrigger = true;
	controlBox->AddComponent<TitleControlBox>();
	controlBox->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\theatercontrolbox.png");
	controlBox->tag = new std::string("Trigger");
	return controlBox;
}

GameObject* Title::CreateManager(Scene* scene, float x, float y)
{

	GameObject* explain1 = scene->CreateObject();
	explain1->transform->position = vector2(-230, 50);
	explain1->AddComponent<BitmapRenderer>();
	explain1->GetComponent<BitmapRenderer>()->order=0.1;
	explain1->GetComponent<BitmapRenderer>()->offset = vector2(-5, 200);
	explain1->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\wallpaper_interact.png");


	GameObject* explain2 = scene->CreateObject();
	explain2->transform->position = vector2(700, 70);
	explain2->AddComponent<BitmapRenderer>();
	explain2->GetComponent<BitmapRenderer>()->order=0.1;
	explain2->GetComponent<BitmapRenderer>()->offset = vector2(0,200);
	explain2->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\wallpaper_jump.png");
	

	GameObject* explain3 = scene->CreateObject();
	explain3->transform->position = vector2(200, 100);
	explain3->AddComponent<BitmapRenderer>();
	explain3->GetComponent<BitmapRenderer>()->order = 0.1;
	explain3->GetComponent<BitmapRenderer>()->offset = vector2(5, 200);
	explain3->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\wallpaper_move.png");
	

	GameObject* explain4 = scene->CreateObject();
	explain4->transform->position = vector2(-700, 0);
	explain4->AddComponent<BitmapRenderer>();
	explain4->GetComponent<BitmapRenderer>()->order = 0.1;
	explain4->GetComponent<BitmapRenderer>()->offset = vector2(10, 200);
	explain4->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\wallpaper_run.png");
	



	GameObject* curtainL = scene->CreateObject();
	curtainL->transform->position = vector2(-480, 0);
	curtainL->AddComponent<BitmapRenderer>();
	curtainL->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\introcurtain_l.png");
	curtainL->GetComponent<BitmapRenderer>()->order = 4;
	
	GameObject* curtainR = scene->CreateObject();
	curtainR->transform->position = vector2(480, 0);
	curtainR->AddComponent<BitmapRenderer>();
	curtainR->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\introcurtain_r.png");
	curtainR->GetComponent<BitmapRenderer>()->order = 4;
	
	GameObject* signboard = scene->CreateObject();
	signboard->transform->position = vector2(0, 0);
	signboard->AddComponent<BitmapRenderer>();
	signboard->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\UI\\title.png");
	signboard->GetComponent<BitmapRenderer>()->order = 5;


	GameObject* rope1 = scene->CreateObject();
	rope1->transform->parent = signboard->transform;
	rope1->transform->position = vector2(-200, -1000);
	rope1->AddComponent<BitmapRenderer>();
	rope1->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\UI\\rope.png");
	rope1->GetComponent<BitmapRenderer>()->order = 4.6;


	GameObject* rope2 = scene->CreateObject();
	rope2->transform->parent = signboard->transform;
	rope2->transform->position = vector2(200, -1000);
	rope2->AddComponent<BitmapRenderer>();
	rope2->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\UI\\rope.png");
	rope2->GetComponent<BitmapRenderer>()->order = 4.6;

	


	GameObject* startboard = scene->CreateObject();
	startboard->transform->position = vector2(0, -900);
	startboard->transform->scale = vector2(0.8, 0.8);
	startboard->AddComponent<BitmapRenderer>();
	startboard->AddComponent<TitleBoard>();
	startboard->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\UI\\title_start.png");
	startboard->GetComponent<BitmapRenderer>()->order = 3;

	startboard->AddComponent<AudioSource>();
	startboard->GetComponent<AudioSource>()->CreateReverbSound("Resources/Music/buttonchoice.mp3", false);
	startboard->GetComponent<AudioSource>()->PlayReverb(3);

	GameObject* exitboard = scene->CreateObject();
	exitboard->transform->position = vector2(0, -900);
	exitboard->transform->scale = vector2(0.8, 0.8);
	exitboard->AddComponent<BitmapRenderer>();
	exitboard->AddComponent<TitleBoard>();
	exitboard->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\UI\\title_exit.png");
	exitboard->GetComponent<BitmapRenderer>()->order = 3;

	GameObject* creditboard = scene->CreateObject();
	creditboard->transform->position = vector2(0, -900);
	creditboard->transform->scale = vector2(0.8, 0.8);
	creditboard->AddComponent<BitmapRenderer>();
	creditboard->AddComponent<TitleBoard>();
	creditboard->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\UI\\title_credit.png");
	creditboard->GetComponent<BitmapRenderer>()->order = 3;


	GameObject* ticket1 = scene->CreateObject();
	ticket1->transform->position = vector2(1500, -200);
	ticket1->transform->scale = vector2(0.5, 0.5);
	ticket1->AddComponent<BitmapRenderer>();
	ticket1->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\UI\\stage1.png");
	ticket1->GetComponent<BitmapRenderer>()->order = 3;

	GameObject* ticket2 = scene->CreateObject();
	ticket2->transform->position = vector2(2000, -200);
	ticket2->transform->scale = vector2(0.5, 0.5);
	ticket2->AddComponent<BitmapRenderer>();
	ticket2->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\UI\\stage2.png");
	ticket2->GetComponent<BitmapRenderer>()->order = 3;

	GameObject* ticket3 = scene->CreateObject();
	ticket3->transform->position = vector2(2500, -200);
	ticket3->transform->scale = vector2(0.5, 0.5);
	ticket3->AddComponent<BitmapRenderer>();
	ticket3->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\UI\\stage3.png");
	ticket3->GetComponent<BitmapRenderer>()->order = 3;




	GameObject* manager = scene->CreateObject();
	manager->AddComponent<TitleManager>();
	manager->GetComponent<TitleManager>()->curtainL = curtainL->transform;
	manager->GetComponent<TitleManager>()->curtainR = curtainR->transform;
	manager->GetComponent<TitleManager>()->signboard = signboard->transform;
	manager->GetComponent<TitleManager>()->ticket1 = ticket1->transform;
	manager->GetComponent<TitleManager>()->ticket2 = ticket2->transform;
	manager->GetComponent<TitleManager>()->ticket3 = ticket3->transform;
	manager->GetComponent<TitleManager>()->explain1 = explain1->transform;
	manager->GetComponent<TitleManager>()->explain2 = explain2->transform;
	manager->GetComponent<TitleManager>()->explain3 = explain3->transform;
	manager->GetComponent<TitleManager>()->explain4 = explain4->transform;


	startboard->GetComponent<TitleBoard>()->next = exitboard->GetComponent<TitleBoard>();
	startboard->GetComponent<TitleBoard>()->previous = creditboard->GetComponent<TitleBoard>();
	

	exitboard->GetComponent<TitleBoard>()->next = creditboard->GetComponent<TitleBoard>();
	exitboard->GetComponent<TitleBoard>()->previous = startboard->GetComponent<TitleBoard>();

	creditboard->GetComponent<TitleBoard>()->next = startboard->GetComponent<TitleBoard>();
	creditboard->GetComponent<TitleBoard>()->previous = exitboard->GetComponent<TitleBoard>();

	startboard->GetComponent<TitleBoard>()->index = 0;
	exitboard->GetComponent<TitleBoard>()->index = 1;
	creditboard->GetComponent<TitleBoard>()->index = 2;

	manager->GetComponent<TitleManager>()->currentBoard = startboard->GetComponent<TitleBoard>();


	return manager;
}

