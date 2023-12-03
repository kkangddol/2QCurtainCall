#pragma once
#include "GammaEngine.h"
#include "IngameBox.h"
#include "MainCamera.h"
#include "fps.h"
#include "Player.h"
#include "Lever.h"
#include "Ladder.h"
#include "Box.h"
#include "Wheel.h"
#include "Scaffolding.h"
#include "Elevator.h"
#include "Arch.h"
#include "ArchDisk.h"
#include "MapDataLoader.h"
#include "WaterTank.h"
#include "ControlBox.h"
#include "MusicControlBox.h"
#include "SkyObject.h"
#include "Gondola.h"
#include "HighLighter.h"
#include "IngameUI.h"
#include "Actor.h"
#include "FileDataApplier.h"
#include "GameManager.h"
#include <format>
///생성한 오브젝트와 속해있는 컴포넌트를 하나의 함수로 묶어서 그대로 쓸 수 있게 해두는 곳이다.

using namespace GammaEngine;

Ingame::CreateFunctor* g_ingameFactory[20] =
{
	new Ingame::BoxFunctor(),
	new Ingame::LadderFunctor(),
	new Ingame::LeftPlatformFunctor(),
	new Ingame::RightPlatformFunctor(),
	new Ingame::WaterTankFunctor(),
	new Ingame::ArchFunctor(),
	new Ingame::ElevatorFunctor(),
	new Ingame::ControlBoxFunctor(),
	new Ingame::MusicBoxFunctor(),
	new Ingame::WheelFunctor(),
	new Ingame::ScaffoldingFunctor(),
	new Ingame::LeverFunctor(),
	new Ingame::CycleFunctor()
};

//카메라
GameObject* Ingame::CreateCamera(Scene* scene)
{
	//Camera
	GameObject* camera = scene->CreateObject();
	camera->AddComponent<Camera>();
	camera->AddComponent<MainCamera>();
	return camera;
}

//도입 라이트
GameObject* Ingame::CreateBackgroundLight(Scene* scene)
{
	//Platform
	GameObject* light_ = scene->CreateObject();
	light_->transform->position = vector2(0, 0);
	//light_->AddComponent<PointLight>();
	//light_->GetComponent<PointLight>()->SetColor(vector3(0.7, 0.7, 0.5));
	//light_->GetComponent<PointLight>()->SetMagnitude(1);
	//light_->GetComponent<PointLight>()->SetZ(1500);

	//light_->AddComponent<DistantLight>();
	//light_->GetComponent<DistantLight>()->SetColor(vector3(1, 1, 1));
	//light_->GetComponent<DistantLight>()->SetMagnitude(1);

	//Tween::Animate(light_->GetComponent<PointLight>()->z, PLAYBACK::ONCE_FORWARD, 5, EASING::OUTBACK, 3);
	return light_;
}

GameObject* Ingame::CreateBackground(Scene* scene, float x, float y)
{
	//Platform
	GameObject* bakground_ = scene->CreateObject();
	bakground_->transform->position = vector2(x, y);

	bakground_->AddComponent<BitmapRenderer>();
	bakground_->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\Background.png");
	bakground_->GetComponent<BitmapRenderer>()->order = -1;
	bakground_->AddComponent<LightAdapter>();
	return bakground_;
}

GameObject* Ingame::CreateStage(Scene* scene, float x, float y)
{
	//Platform
	GameObject* bakground_ = scene->CreateObject();
	bakground_->transform->position = vector2(x, y);

	bakground_->AddComponent<BitmapRenderer>();
	bakground_->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Background\\Stage.png");
	bakground_->GetComponent<BitmapRenderer>()->order = 3;
	bakground_->AddComponent<LightAdapter>();

	return bakground_;
}

//플레이어
GameObject* Ingame::CreatePlayer(Scene* scene, float x, float y, int id)
{
	//Player
	GameObject* player = scene->CreateObject();
	player->transform->position = vector2(x, y);
	//player->transform->scale = vector2(0.7f, 0.7f);

	player->AddComponent<SpineRenderer>();
	player->GetComponent<SpineRenderer>()->offset=vector2(0, 80);

	player->AddComponent<LightAdapter>();

	player->AddComponent<BoxCollider>();
	player->GetComponent<BoxCollider>()->SetBounds(vector2(100,180));

	player->AddComponent<FPS>();

	player->AddComponent<Rigidbody>();
	player->GetComponent<Rigidbody>()->useGravity = true;
	player->GetComponent<Rigidbody>()->mass = 0.5;
	player->GetComponent<Rigidbody>()->restitution = 0.3f;
	player->GetComponent<Rigidbody>()->SetIgnore(std::string("player"));

	player->AddComponent<Player>();
	player->GetComponent<Player>()->id = id;
	player->tag = new std::string("player");

	SoundSystem::Instance()->CreateReverbSound("Resources/Music/walk.mp3", true);
	SoundSystem::Instance()->CreateReverbSound("Resources/Music/jump.mp3", false);
	SoundSystem::Instance()->CreateReverbSound("Resources/Music/ladder.wav", true);

	GameObject* particle = Ingame::CreateRunningParticle(scene, 0, 80);
	particle->transform->SetParent(player->transform);
	player->GetComponent<Player>()->SetEmitter(particle->GetComponent<ParticleSystem>()->GetEmitters());

	GameObject* failEffect = Ingame::CreateFailEffect(scene, 0, -120);
	failEffect->transform->SetParent(player->transform);
	player->GetComponent<Player>()->SetAnimator(failEffect);

	std::string filename = std::format("Resources/Data/player.ini", id);
	FileDataApplier applier(filename);
	applier.SetProperty("runSpeed", player->GetComponent<Player>()->runSpeed);
	applier.SetProperty("walkSpeed", player->GetComponent<Player>()->walkSpeed);
	applier.SetProperty("grabSpeed", player->GetComponent<Player>()->grabSpeed);
	applier.SetProperty("climbSpeed", player->GetComponent<Player>()->climbSpeed);
	applier.SetProperty("jumpForce", player->GetComponent<Player>()->jumpForce);
	applier.SetProperty("pushForce", player->GetComponent<Player>()->pushForce);
	applier.SetProperty("responsiveness", player->GetComponent<Player>()->responsiveness);
	applier.Apply();
	return player;
}

GammaEngine::GameObject* Ingame::CreateFailEffect(Scene* scene, float x, float y)
{
	GameObject* obj = scene->CreateObject();
	obj->transform->position = vector2(x, y);
	obj->AddComponent<BitmapRenderer>();
	BitmapRenderer* bitmap = obj->GetComponent<BitmapRenderer>();
	bitmap->LoadBitmapImage(L"Resources\\Particles\\particle_fail.png");
	bitmap->order = 3;
	bitmap->size = vector2(150,130);
	obj->AddComponent<Animator>();
	Animator* animator = obj->GetComponent<Animator>();
	Animation* anim = new Animation();
	anim->SetFPS(0.3f);
	anim->AddFrame(L"Resources\\Particles\\particle_fail.png");
	anim->AddFrame(L"Resources\\Particles\\particle_fail_02.png");
	anim->AddFrame(L"Resources\\Particles\\particle_fail_03.png");

	animator->AddAnimation(L"fail", anim);
	animator->Play(L"fail", PLAYBACK::LOOP_FORWARD);

	obj->Disable();

	return obj;
}

GammaEngine::GameObject* Ingame::CreateRainParticle(Scene* scene, float x, float y)
{
	const float GRAVITY = 0.6f;
	const float LIFETIME = 1.2f;
	const vector2 DROPSIZE(8, 30);
	const float RAINALPHA = 0.9f;
	const float INTERVAL = 0.01f;

	GameObject* rainObj = scene->CreateObject();
	rainObj->transform->position = vector2(x, y);

	rainObj->AddComponent<ParticleSystem>();
	ParticleSystem* particleSystem = rainObj->GetComponent<ParticleSystem>();
	
	ParticleEmitter* emitter1 = particleSystem->CreateEmitter(50, L"Resources\\Particles\\raindrop_L_01.png",2);
	emitter1->transform.Rotate(0);
	emitter1->SetShape(ParticleEmitter::Shape::RECT);
	emitter1->SetActive(false);
	emitter1->SetGravity(GRAVITY);
	emitter1->SetLifeTime(LIFETIME, LIFETIME, 0.2f);
	emitter1->SetWorldEmit(true);
	emitter1->SetWidth(800);
	emitter1->SetHeight(100);
	emitter1->SetSpeed(0, 0, 0);
	emitter1->SetTintOverLifeTime(vector4(1, 1, 1, RAINALPHA), vector4(1, 1, 1, RAINALPHA));
	emitter1->SetSizeOverLifeTime(DROPSIZE, DROPSIZE);
	emitter1->SetInterval(INTERVAL, INTERVAL, 0);

	ParticleEmitter* emitter2 = particleSystem->CreateEmitter(50, L"Resources\\Particles\\raindrop_L_02.png",2);
	emitter2->transform.Rotate(0);
	emitter2->SetShape(ParticleEmitter::Shape::RECT);
	emitter2->SetActive(false);
	emitter2->SetGravity(GRAVITY);
	emitter2->SetLifeTime(LIFETIME, LIFETIME, 0.2f);
	emitter2->SetWorldEmit(true);
	emitter2->SetWidth(800);
	emitter2->SetHeight(100);
	emitter2->SetSpeed(0, 0, 0);
	emitter2->SetTintOverLifeTime(vector4(1, 1, 1, RAINALPHA), vector4(1, 1, 1, RAINALPHA));
	emitter2->SetSizeOverLifeTime(DROPSIZE, DROPSIZE);
	emitter2->SetInterval(INTERVAL, INTERVAL, 0);


	ParticleEmitter* emitter3 = particleSystem->CreateEmitter(50, L"Resources\\Particles\\raindrop_S_01.png",2);
	emitter3->transform.Rotate(0);
	emitter3->SetShape(ParticleEmitter::Shape::RECT);
	emitter3->SetActive(false);
	emitter3->SetGravity(GRAVITY);
	emitter3->SetLifeTime(LIFETIME, LIFETIME, 0.2f);
	emitter3->SetWorldEmit(true);
	emitter3->SetWidth(800);
	emitter3->SetHeight(100);
	emitter3->SetSpeed(0, 0, 0);
	emitter3->SetTintOverLifeTime(vector4(1, 1, 1, RAINALPHA), vector4(1, 1, 1, RAINALPHA));
	emitter3->SetSizeOverLifeTime(DROPSIZE, DROPSIZE);
	emitter3->SetInterval(INTERVAL, INTERVAL, 0);

	ParticleEmitter* emitter4 = particleSystem->CreateEmitter(50, L"Resources\\Particles\\raindrop_S_02.png",2);
	emitter4->transform.Rotate(0);
	emitter4->SetShape(ParticleEmitter::Shape::RECT);
	emitter4->SetActive(false);
	emitter4->SetGravity(GRAVITY);
	emitter4->SetLifeTime(LIFETIME, LIFETIME, 0.2f);
	emitter4->SetWorldEmit(true);
	emitter4->SetWidth(800);
	emitter4->SetHeight(100);
	emitter4->SetSpeed(0, 0, 0);
	emitter4->SetTintOverLifeTime(vector4(1, 1, 1, RAINALPHA), vector4(1, 1, 1, RAINALPHA));
	emitter4->SetSizeOverLifeTime(DROPSIZE, DROPSIZE);
	emitter4->SetInterval(INTERVAL, INTERVAL, 0);

	return rainObj;
}

GammaEngine::GameObject* Ingame::CreateRunningParticle(Scene* scene, float x, float y)
{
	const bool ACTIVE = false;
	const float DRAG = 0.1f;
	const float LIFETIME = 0.5f;
	const vector2 DUSTSIZESTART(0, 0);
	const vector2 DUSTSIZEEND(100, 100);
	const float INTERVAL = 0.15f;
	const float INTERVALRANGE = 0.15f;
	const float SPEED = 3;

	GameObject* particleObj = scene->CreateObject();
	particleObj->transform->position = vector2(x, y);

	particleObj->AddComponent<ParticleSystem>();
	ParticleSystem* particleSystem = particleObj->GetComponent<ParticleSystem>();

	ParticleEmitter* emitter1 = particleSystem->CreateEmitter(10, L"Resources\\Particles\\dust_S_01.png",2);
	emitter1->SetActive(ACTIVE);
	emitter1->StartWithRandomAngle(true);
	emitter1->SetShape(ParticleEmitter::Shape::RECT);
	emitter1->SetInterval(INTERVAL, INTERVAL, INTERVALRANGE);
	emitter1->SetWidth(50);
	emitter1->SetHeight(50);
	emitter1->SetDrag(DRAG);
	emitter1->SetLifeTime(LIFETIME, LIFETIME, 0.2f);
	emitter1->SetWorldEmit(true);
	emitter1->SetSpeed(SPEED, SPEED, 0.5f);
	emitter1->SetTintOverLifeTime(vector4(1, 1, 1, 0.5), vector4(1, 1, 1, 0.01));
	emitter1->SetSizeOverLifeTime(DUSTSIZESTART, DUSTSIZEEND);

	ParticleEmitter* emitter2 = particleSystem->CreateEmitter(10, L"Resources\\Particles\\dust_S_02.png",2);
	emitter2->SetActive(ACTIVE);
	emitter2->StartWithRandomAngle(true);
	emitter2->SetShape(ParticleEmitter::Shape::RECT);
	emitter2->SetInterval(INTERVAL, INTERVAL, INTERVALRANGE);
	emitter2->SetWidth(50);
	emitter2->SetHeight(50);
	emitter2->SetDrag(DRAG);
	emitter2->SetLifeTime(LIFETIME, LIFETIME, 0.2f);
	emitter2->SetWorldEmit(true);
	emitter2->SetSpeed(SPEED, SPEED, 0.5f);
	emitter2->SetTintOverLifeTime(vector4(1, 1, 1, 0.5), vector4(1, 1, 1, 0.01));
	emitter2->SetSizeOverLifeTime(DUSTSIZESTART, DUSTSIZEEND);

	ParticleEmitter* emitter3 = particleSystem->CreateEmitter(10, L"Resources\\Particles\\dust_S_03.png",2);
	emitter3->SetActive(ACTIVE);
	emitter3->StartWithRandomAngle(true);
	emitter3->SetShape(ParticleEmitter::Shape::RECT);
	emitter3->SetInterval(INTERVAL, INTERVAL, INTERVALRANGE);
	emitter3->SetWidth(50);
	emitter3->SetHeight(50);
	emitter3->SetDrag(DRAG);
	emitter3->SetLifeTime(LIFETIME, LIFETIME, 0.2f);
	emitter3->SetWorldEmit(true);
	emitter3->SetSpeed(SPEED, SPEED, 0.5f);
	emitter3->SetTintOverLifeTime(vector4(1, 1, 1, 0.5), vector4(1, 1, 1, 0.01));
	emitter3->SetSizeOverLifeTime(DUSTSIZESTART, DUSTSIZEEND);

	ParticleEmitter* emitter4 = particleSystem->CreateEmitter(10, L"Resources\\Particles\\dust_L_01.png",2);
	emitter4->SetActive(ACTIVE);
	emitter4->StartWithRandomAngle(true);
	emitter4->SetShape(ParticleEmitter::Shape::RECT);
	emitter4->SetInterval(INTERVAL, INTERVAL, INTERVALRANGE);
	emitter4->SetWidth(50);
	emitter4->SetHeight(50);
	emitter4->SetDrag(DRAG);
	emitter4->SetLifeTime(LIFETIME, LIFETIME, 0.2f);
	emitter4->SetWorldEmit(true);
	emitter4->SetSpeed(SPEED, SPEED, 0.5f);
	emitter4->SetTintOverLifeTime(vector4(1, 1, 1, 0.5), vector4(1, 1, 1, 0.01));
	emitter4->SetSizeOverLifeTime(DUSTSIZESTART, DUSTSIZEEND);

	ParticleEmitter* emitter5 = particleSystem->CreateEmitter(10, L"Resources\\Particles\\dust_L_02.png",2);
	emitter5->SetActive(ACTIVE);
	emitter5->StartWithRandomAngle(true);
	emitter5->SetShape(ParticleEmitter::Shape::RECT);
	emitter5->SetInterval(INTERVAL, INTERVAL, INTERVALRANGE);
	emitter5->SetWidth(50);
	emitter5->SetHeight(50);
	emitter5->SetDrag(DRAG);
	emitter5->SetLifeTime(LIFETIME, LIFETIME, 0.2f);
	emitter5->SetWorldEmit(true);
	emitter5->SetSpeed(SPEED, SPEED, 0.5f);
	emitter5->SetTintOverLifeTime(vector4(1, 1, 1, 0.5), vector4(1, 1, 1, 0.01));
	emitter5->SetSizeOverLifeTime(DUSTSIZESTART, DUSTSIZEEND);

	return particleObj;
}

GammaEngine::GameObject* Ingame::CreateFanfareParticle(Scene* scene, float x, float y)
{
	const bool ACTIVE = false;
	const bool LOOP = false;
	const float ARCANGLE = 120;
	const float DRAG = 0.1f;
	const float GRAVITY = 1;
	const float LIFETIME = 10;
	const vector2 DUSTSIZESTART(100, 100);
	const vector2 DUSTSIZEEND(100, 100);
	const float INTERVAL = 0.5f;
	const float INTERVALRANGE = 0;
	const float SPEED = 130;
	const float SPEEDRANGE = 30;
	const int EMITCOUNT = 5;
	const int MAXCOUNT = 6;
	const float DELTAROTATERANGE = 3;

	GameObject* particleObj = scene->CreateObject();
	particleObj->transform->position = vector2(x, y);

	particleObj->AddComponent<ParticleSystem>();
	ParticleSystem* particleSystem = particleObj->GetComponent<ParticleSystem>();

	ParticleEmitter* emitter1 = particleSystem->CreateEmitter(10, L"Resources\\Particles\\particle_pass_01.png",15);
	emitter1->SetActive(ACTIVE);
	emitter1->SetLoop(LOOP);
	emitter1->SetArcAngle(ARCANGLE);
	emitter1->SetRadius(1, 1);
	emitter1->StartWithRandomAngle(true);
	emitter1->SetDeltaRotate(0,0, DELTAROTATERANGE);
	emitter1->SetInterval(INTERVAL, INTERVAL, INTERVALRANGE);
	emitter1->SetDrag(DRAG);
	emitter1->SetGravity(GRAVITY);
	emitter1->SetLifeTime(LIFETIME, LIFETIME, 0);
	emitter1->SetWorldEmit(true);
	emitter1->SetSpeed(SPEED, SPEED, SPEEDRANGE);
	emitter1->SetTintOverLifeTime(vector4(1, 1, 1, 1), vector4(1, 1, 1, 1));
	emitter1->SetSizeOverLifeTime(DUSTSIZESTART, DUSTSIZEEND);
	emitter1->SetCountPerEmit(EMITCOUNT, EMITCOUNT,0);

	ParticleEmitter* emitter2 = particleSystem->CreateEmitter(10, L"Resources\\Particles\\particle_pass_02.png",15);
	emitter2->SetActive(ACTIVE);
	emitter2->SetLoop(LOOP);
	emitter2->SetArcAngle(ARCANGLE);
	emitter2->SetRadius(1, 1);
	emitter2->StartWithRandomAngle(true);
	emitter2->SetDeltaRotate(0, 0, DELTAROTATERANGE);
	emitter2->SetInterval(INTERVAL, INTERVAL, INTERVALRANGE);
	emitter2->SetDrag(DRAG);
	emitter2->SetGravity(GRAVITY);
	emitter2->SetLifeTime(LIFETIME, LIFETIME, 0);
	emitter2->SetWorldEmit(true);
	emitter2->SetSpeed(SPEED, SPEED, SPEEDRANGE);
	emitter2->SetTintOverLifeTime(vector4(1, 1, 1, 1), vector4(1, 1, 1, 1));
	emitter2->SetSizeOverLifeTime(DUSTSIZESTART, DUSTSIZEEND);
	emitter2->SetCountPerEmit(EMITCOUNT, EMITCOUNT, 0);

	ParticleEmitter* emitter3 = particleSystem->CreateEmitter(10, L"Resources\\Particles\\particle_pass_04.png",15);
	emitter3->SetActive(ACTIVE);
	emitter3->SetLoop(LOOP);
	emitter3->SetArcAngle(ARCANGLE);
	emitter3->SetRadius(1, 1);
	emitter3->StartWithRandomAngle(true);
	emitter3->SetDeltaRotate(0, 0, DELTAROTATERANGE);
	emitter3->SetInterval(INTERVAL, INTERVAL, INTERVALRANGE);
	emitter3->SetDrag(DRAG);
	emitter3->SetGravity(GRAVITY);
	emitter3->SetLifeTime(LIFETIME, LIFETIME, 0);
	emitter3->SetWorldEmit(true);
	emitter3->SetSpeed(SPEED, SPEED, SPEEDRANGE);
	emitter3->SetTintOverLifeTime(vector4(1, 1, 1, 1), vector4(1, 1, 1, 1));
	emitter3->SetSizeOverLifeTime(DUSTSIZESTART, DUSTSIZEEND);
	emitter3->SetCountPerEmit(EMITCOUNT, EMITCOUNT, 0);

	ParticleEmitter* emitter4 = particleSystem->CreateEmitter(10, L"Resources\\Particles\\particle_pass_05.png",15);
	emitter4->SetActive(ACTIVE);
	emitter4->SetLoop(LOOP);
	emitter4->SetArcAngle(ARCANGLE);
	emitter4->SetRadius(1, 1);
	emitter4->StartWithRandomAngle(true);
	emitter4->SetDeltaRotate(0, 0, DELTAROTATERANGE);
	emitter4->SetInterval(INTERVAL, INTERVAL, INTERVALRANGE);
	emitter4->SetDrag(DRAG);
	emitter4->SetGravity(GRAVITY);
	emitter4->SetLifeTime(LIFETIME, LIFETIME, 0);
	emitter4->SetWorldEmit(true);
	emitter4->SetSpeed(SPEED, SPEED, SPEEDRANGE);
	emitter4->SetTintOverLifeTime(vector4(1, 1, 1, 1), vector4(1, 1, 1, 1));
	emitter4->SetSizeOverLifeTime(DUSTSIZESTART, DUSTSIZEEND);
	emitter4->SetCountPerEmit(EMITCOUNT, EMITCOUNT, 0);

	ParticleEmitter* emitter5 = particleSystem->CreateEmitter(10, L"Resources\\Particles\\particle_pass_02.png",15);
	emitter5->SetActive(ACTIVE);
	emitter5->SetLoop(LOOP);
	emitter5->SetArcAngle(ARCANGLE);
	emitter5->SetRadius(1, 1);
	emitter5->StartWithRandomAngle(true);
	emitter5->SetDeltaRotate(0, 0, DELTAROTATERANGE);
	emitter5->SetInterval(INTERVAL, INTERVAL, INTERVALRANGE);
	emitter5->SetDrag(DRAG);
	emitter5->SetGravity(GRAVITY);
	emitter5->SetLifeTime(LIFETIME, LIFETIME, 0);
	emitter5->SetWorldEmit(true);
	emitter5->SetSpeed(SPEED, SPEED, SPEEDRANGE);
	emitter5->SetTintOverLifeTime(vector4(1, 1, 1, 1), vector4(1, 1, 1, 1));
	emitter5->SetSizeOverLifeTime(DUSTSIZESTART, DUSTSIZEEND);
	emitter5->SetCountPerEmit(EMITCOUNT, EMITCOUNT, 0);

	return particleObj;
}

GammaEngine::GameObject* Ingame::CreateScriptObj(Scene* scene, float x, float y)
{
	GameObject* textObj = scene->CreateObject();
	textObj->transform->position = vector2(x, y);
	textObj->AddComponent<BitmapRenderer>();
	BitmapRenderer* textBitmap = textObj->GetComponent<BitmapRenderer>();
	textBitmap->LoadBitmapImage(L"Resources\\UI\\uppertext.png");
	textBitmap->order = 10;
	textBitmap->isScreen = true;
	textBitmap->size = vector2(1000, 120);
	textObj->AddComponent<TextAnimationRenderer>();
	textObj->AddComponent<TextAnimator>();
	TextAnimationRenderer* textRender = textObj->GetComponent<TextAnimationRenderer>();
	textRender->order = 11;
	textRender->isScreen = true;
	textRender->size = vector2(1000, 120);
	textRender->offset = vector2(-250,-10);

	return textObj;
}

GammaEngine::GameObject* Ingame::CreateTimerObj(Scene* scene, float x, float y)
{
	GameObject* timerObj = scene->CreateObject();
	timerObj->transform->position = vector2(x, y);
	timerObj->AddComponent<BitmapRenderer>();
	BitmapRenderer* timerBitmap = timerObj->GetComponent<BitmapRenderer>();
	timerBitmap->LoadBitmapImage(L"Resources\\UI\\ui_timel.png");
	timerBitmap->order = 11;
	timerBitmap->isScreen = true;
	timerBitmap->size = vector2(150,130);
	timerObj->AddComponent<TextRenderer>();
	TextRenderer* timerRender = timerObj->GetComponent<TextRenderer>();
	timerRender->order = 12;
	timerRender->isScreen = true;
	timerRender->size = vector2(180, 156);
	timerRender->offset = vector2(3, 75);

	return timerObj;
}

GammaEngine::GameObject* Ingame::CreateStampObj(Scene* scene, float x, float y)
{
	GameObject* stampObj = scene->CreateObject();
	stampObj->transform->position = vector2(x, y);
	stampObj->transform->scale = vector2(2, 2);
	stampObj->AddComponent<BitmapRenderer>();
	BitmapRenderer* stampBitmap = stampObj->GetComponent<BitmapRenderer>();
	stampBitmap->LoadBitmapImage(L"Resources\\UI\\stamp.png");
	stampBitmap->order = 11;
	stampBitmap->isScreen = true;
	stampBitmap->isEnabled = false;

	return stampObj;
}

GammaEngine::GameObject* Ingame::CreateLifeObj(Scene* scene, float x, float y)
{
	GameObject* board = scene->CreateObject();
	board->transform->position = vector2(x, y);
	board->AddComponent<BitmapRenderer>();
	BitmapRenderer* boardBitmap = board->GetComponent<BitmapRenderer>();
	boardBitmap->LoadBitmapImage(L"Resources\\UI\\lifepannal.png");
	//boardBitmap->size = vector2(90, 90);
	boardBitmap->order = 10;
	boardBitmap->isScreen = true;
	boardBitmap->offset = vector2(0, -66);
	board->AddComponent<TextRenderer>();
	TextRenderer* text = board->GetComponent<TextRenderer>();
	text->order = 11;
	text->isScreen = true;
	text->size = vector2(100, 100);
	text->offset = vector2(33, 35);
	text->SetText(L"x3");

	GameObject* coin = scene->CreateObject();
	coin->transform->parent = board->transform;
	coin->transform->position = vector2(-30, 0);
	coin->AddComponent<BitmapRenderer>();
	BitmapRenderer* coinBitmap = coin->GetComponent<BitmapRenderer>();
	coinBitmap->LoadBitmapImage(L"Resources\\UI\\coin.png");
	coinBitmap->size = vector2(60, 60);
	coinBitmap->order = 11;
	coinBitmap->isScreen = true;

	return board;
}

GammaEngine::GameObject* Ingame::CreatePauseUI(Scene* scene, float x, float y)
{
	GameObject* pauseUI = scene->CreateObject();
	pauseUI->transform->position = vector2(x, y);
	pauseUI->AddComponent<IngameUI>();
	pauseUI->AddComponent<BitmapRenderer>();
	BitmapRenderer* pauseUIBitmap = pauseUI->GetComponent<BitmapRenderer>();
	pauseUIBitmap->LoadBitmapImage(L"Resources\\UI\\Menu_blank.png");
	pauseUIBitmap->order = 15;
	pauseUIBitmap->isScreen = true;

	GameObject* selector = scene->CreateObject();
	selector->transform->parent = pauseUI->transform;
	selector->AddComponent<BitmapRenderer>();
	BitmapRenderer* selectorBitmap = selector->GetComponent<BitmapRenderer>();
	selectorBitmap->LoadBitmapImage(L"Resources\\UI\\stamp.png");
	selectorBitmap->order = 17;
	selectorBitmap->isScreen = true;
	selectorBitmap->size = vector2(100, 100);

	pauseUI->GetComponent<IngameUI>()->SetSelector(selector);
	pauseUI->GetComponent<IngameUI>()->SetType(IngameUI::UIType::PAUSE);

	pauseUI->Disable();

	return pauseUI;
}

GammaEngine::GameObject* Ingame::CreateHomeBtn(Scene* scene, float x, float y)
{
	GameObject* obj = scene->CreateObject();
	obj->transform->position = vector2(x, y);
	obj->AddComponent<BitmapRenderer>();
	BitmapRenderer* bitmap = obj->GetComponent<BitmapRenderer>();
	bitmap->LoadBitmapImage(L"Resources\\UI\\Home.png");
	bitmap->order = 16;
	bitmap->isScreen = true;
	bitmap->size = vector2(150, 150);

	obj->Disable();

	return obj;
}

GammaEngine::GameObject* Ingame::CreateRestartBtn(Scene* scene, float x, float y)
{
	GameObject* obj = scene->CreateObject();
	obj->transform->position = vector2(x, y);
	obj->AddComponent<BitmapRenderer>();
	BitmapRenderer* bitmap = obj->GetComponent<BitmapRenderer>();
	bitmap->LoadBitmapImage(L"Resources\\UI\\Retrun.png");
	bitmap->order = 16;
	bitmap->isScreen = true;
	bitmap->size = vector2(150, 150);

	obj->Disable();

	return obj;
}

GammaEngine::GameObject* Ingame::CreateOptionBtn(Scene* scene, float x, float y)
{
	GameObject* obj = scene->CreateObject();
	obj->transform->position = vector2(x, y);
	obj->AddComponent<BitmapRenderer>();
	BitmapRenderer* bitmap = obj->GetComponent<BitmapRenderer>();
	bitmap->LoadBitmapImage(L"Resources\\UI\\Option.png");
	bitmap->order = 16;
	bitmap->isScreen = true;
	bitmap->size = vector2(150, 150);

	obj->Disable();

	return obj;
}

GammaEngine::GameObject* Ingame::CreatePauseIcon(Scene* scene, float x, float y)
{
	GameObject* obj = scene->CreateObject();
	obj->transform->position = vector2(x, y);
	obj->AddComponent<BitmapRenderer>();
	BitmapRenderer* bitmap = obj->GetComponent<BitmapRenderer>();
	bitmap->LoadBitmapImage(L"Resources\\UI\\Pause.png");
	bitmap->order = 16;
	bitmap->isScreen = true;
	bitmap->size = vector2(150, 150);

	obj->Disable();

	return obj;
}

GammaEngine::GameObject* Ingame::CreateClearUI(Scene* scene, float x, float y)
{
	GameObject* clearUI = scene->CreateObject();
	clearUI->transform->position = vector2(x, y);
	clearUI->AddComponent<IngameUI>();
	clearUI->AddComponent<BitmapRenderer>();
	BitmapRenderer* pauseUIBitmap = clearUI->GetComponent<BitmapRenderer>();
	pauseUIBitmap->LoadBitmapImage(L"Resources\\UI\\Fin.png");
	pauseUIBitmap->order = 15;
	pauseUIBitmap->isScreen = true;
	pauseUIBitmap->size = vector2(902.3, 562.8);

	GameObject* score1 = scene->CreateObject();
	score1->transform->parent = clearUI->transform;
	score1->transform->position = vector2(-200, -140);
	score1->AddComponent<BitmapRenderer>();
	BitmapRenderer* score1Bitmap = score1->GetComponent<BitmapRenderer>();
	score1Bitmap->LoadBitmapImage(L"Resources\\UI\\Score.png");
	score1Bitmap->order = 16;
	score1Bitmap->isScreen = true;
	score1Bitmap->size = vector2(150, 150);

	GameObject* score2 = scene->CreateObject();
	score2->transform->parent = clearUI->transform;
	score2->transform->position = vector2(0, -140);
	score2->AddComponent<BitmapRenderer>();
	BitmapRenderer* score2Bitmap = score2->GetComponent<BitmapRenderer>();
	score2Bitmap->LoadBitmapImage(L"Resources\\UI\\Score.png");
	score2Bitmap->order = 16;
	score2Bitmap->isScreen = true;
	score2Bitmap->size = vector2(150, 150);

	GameObject* score3 = scene->CreateObject();
	score3->transform->parent = clearUI->transform;
	score3->transform->position = vector2(200, -140);
	score3->AddComponent<BitmapRenderer>();
	BitmapRenderer* score3Bitmap = score3->GetComponent<BitmapRenderer>();
	score3Bitmap->LoadBitmapImage(L"Resources\\UI\\Score.png");
	score3Bitmap->order = 16;
	score3Bitmap->isScreen = true;
	score3Bitmap->size = vector2(150, 150);

	GameObject* selector = scene->CreateObject();
	selector->transform->parent = clearUI->transform;
	selector->AddComponent<BitmapRenderer>();
	BitmapRenderer* selectorBitmap = selector->GetComponent<BitmapRenderer>();
	selectorBitmap->LoadBitmapImage(L"Resources\\UI\\stamp.png");
	selectorBitmap->order = 17;
	selectorBitmap->isScreen = true;
	selectorBitmap->size = vector2(100, 100);

	IngameUI* ingame = clearUI->GetComponent<IngameUI>();
	ingame->SetSelector(selector);
	ingame->SetType(IngameUI::UIType::CLEAR);
	ingame->AddScore(score1);
	ingame->AddScore(score2);
	ingame->AddScore(score3);

	clearUI->Disable();

	return clearUI;
}

GammaEngine::GameObject* Ingame::CreateContinueBtn(Scene* scene, float x, float y)
{
	GameObject* obj = scene->CreateObject();
	obj->transform->position = vector2(x, y);
	obj->AddComponent<BitmapRenderer>();
	BitmapRenderer* bitmap = obj->GetComponent<BitmapRenderer>();
	bitmap->LoadBitmapImage(L"Resources\\UI\\paly.png");
	bitmap->order = 16;
	bitmap->isScreen = true;
	bitmap->size = vector2(150, 150);

	obj->Disable();

	return obj;
}

GameObject* Ingame::CreateWall(Scene* scene, float x, float y, float sizeX, float sizeY)
{
	//Platform
	GameObject* platform_ = scene->CreateObject();
	platform_->transform->position = vector2(x, y);

	//Debug::DrawRectangle(vector2(sizeX, sizeY), vector2(x, y), 0);

	platform_->AddComponent<BoxCollider>();
	platform_->GetComponent<BoxCollider>()->SetBounds(vector2(sizeX, sizeY));

	platform_->AddComponent<Rigidbody>();
	platform_->GetComponent<Rigidbody>()->useGravity = false;
	platform_->GetComponent<Rigidbody>()->mass = 0;

	platform_->tag = new std::string("Wall");

	return platform_;
}

//플랫폼
GameObject* Ingame::CreateBlock(Scene* scene, float x, float y, float sizeX, float sizeY)
{
	//Platform
	GameObject* platform_ = scene->CreateObject();
	platform_->transform->position = vector2(x, y);

	//Debug::DrawRectangle(vector2(sizeX, sizeY), vector2(x, y), 0);

	platform_->AddComponent<BoxCollider>();
	platform_->GetComponent<BoxCollider>()->SetBounds(vector2(sizeX, sizeY));

	platform_->AddComponent<Rigidbody>();
	platform_->GetComponent<Rigidbody>()->useGravity = false;
	platform_->GetComponent<Rigidbody>()->mass = 0;

	platform_->tag = new std::string("Obstacle");

	return platform_;
}

GameObject* Ingame::CreateLever(Scene* scene, float x, float y)
{
	//Platform
	GameObject* lever_ = scene->CreateObject();
	lever_->transform->position = vector2(x, y);

	lever_->AddComponent<BitmapRenderer>();
	lever_->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\lever_gear.png");
	lever_->GetComponent<BitmapRenderer>()->order = 2;

	lever_->AddComponent<BoxCollider>();
	lever_->GetComponent<BoxCollider>()->SetBounds(vector2(100, 100));
	lever_->GetComponent<BoxCollider>()->isTrigger = true;

	lever_->AddComponent<Lever>();

	lever_->AddComponent<AudioSource>();
	lever_->GetComponent<AudioSource>()->CreateReverbSound("Resources/Music/leveronce.ogg", false);

	lever_->tag = new std::string("Trigger");

	//Platform
	GameObject* leverStick = scene->CreateObject();
	leverStick->transform->parent = lever_->transform;
	leverStick->transform->position = vector2(0,20);

	leverStick->AddComponent<BitmapRenderer>();
	leverStick->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\lever_stick.png");
	leverStick->GetComponent<BitmapRenderer>()->order = 1.9;
	leverStick->GetComponent<BitmapRenderer>()->offset = vector2(0,-30);
	leverStick->AddComponent<HighLighter>();

	

	leverStick->tag = new std::string("Trigger");


	lever_->GetComponent<Lever>()->stick=leverStick->transform;

	return lever_;
}

GameObject* Ingame::CreateWheel(Scene* scene, float x, float y)
{
	//Platform
	GameObject* lever_ = scene->CreateObject();
	lever_->transform->position = vector2(x, y);

// 	lever_->AddComponent<BitmapRenderer>();
// 	lever_->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\wheel.png");
// 	lever_->GetComponent<BitmapRenderer>()->size = vector2(100, 100);
// 	lever_->GetComponent<BitmapRenderer>()->order = 2;
// 	lever_->AddComponent<BoxCollider>();
// 	lever_->GetComponent<BoxCollider>()->SetBounds(vector2(100, 100));
// 	lever_->GetComponent<BoxCollider>()->isTrigger = true;
// 
// 	lever_->AddComponent<Wheel>();
// 
// 	lever_->tag = new std::string("Trigger");

/*	lever_->AddComponent<Wheel>();*/

	lever_->AddComponent<AudioSource>();
	lever_->GetComponent<AudioSource>()->CreateReverbSound("Resources/Music/wheelonce.ogg", false);

	lever_->tag = new std::string("Trigger");

	return lever_;
}

GameObject* Ingame::CreateArchDisk(Scene* scene, float x, float y)
{
	//Platform
	GameObject* disk = scene->CreateObject();
	disk->transform->position = vector2(x, y);

	disk->AddComponent<BitmapRenderer>();
	disk->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\cycle_back.png");
	disk->GetComponent<BitmapRenderer>()->order = 0;

	disk->AddComponent<BoxCollider>();
	disk->GetComponent<BoxCollider>()->SetBounds(vector2(100, 100));
	disk->GetComponent<BoxCollider>()->isTrigger = true;

	disk->AddComponent<ArchDisk>();
	disk->tag = new std::string("Trigger");

	return disk;
}


GammaEngine::GameObject* Ingame::CreateControlBox(Scene* scene, float x, float y)
{
	GameObject* controlBox = scene->CreateObject();
	controlBox->transform->position = vector2(x, y);
	controlBox->transform->scale = vector2(0.8, 0.8);
	controlBox->AddComponent<BitmapRenderer>();
	controlBox->AddComponent<ControlBox>();
	controlBox->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\theatercontrolbox.png");
	//controlBox->GetComponent<BitmapRenderer>()->offset = vector2(0, 50);
	controlBox->GetComponent<BitmapRenderer>()->order = 3;

	controlBox->AddComponent<BoxCollider>();
	controlBox->GetComponent<BoxCollider>()->SetBounds(vector2(100, 100));
	controlBox->GetComponent<BoxCollider>()->isTrigger = true;
	controlBox->tag = new std::string("Trigger");

	GameObject* dummy = scene->CreateObject();
	dummy->transform->position = vector2(300, -180);
	dummy->AddComponent<SkyObject>();
	dummy->GetComponent<SkyObject>()->index = -1;
	dummy->GetComponent<SkyObject>()->AttachTrigger(controlBox->GetComponent<Trigger>());

	GameObject* sun = scene->CreateObject();
	sun->transform->position = vector2(300, -180);
	sun->AddComponent<SkyObject>();
	sun->GetComponent<SkyObject>()->index = 0;
	sun->AddComponent<BitmapRenderer>();
	sun->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\sun.png");
	sun->GetComponent<BitmapRenderer>()->order = 0;

	sun->GetComponent<SkyObject>()->AttachTrigger(controlBox->GetComponent<Trigger>());

	GameObject* moon = scene->CreateObject();
	moon->transform->position = vector2(300, -180);
	moon->AddComponent<SkyObject>();
	moon->GetComponent<SkyObject>()->index = 1;
	moon->AddComponent<BitmapRenderer>();
	moon->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\moon.png");
	moon->GetComponent<BitmapRenderer>()->order = 0;
	
	moon->GetComponent<SkyObject>()->AttachTrigger(controlBox->GetComponent<Trigger>());

	GameObject* cloud = scene->CreateObject();
	cloud->transform->position = vector2(300, -180);
	cloud->AddComponent<SkyObject>();
	cloud->GetComponent<SkyObject>()->index = 2;
	cloud->AddComponent<BitmapRenderer>();
	cloud->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\cloud.png");
	cloud->GetComponent<BitmapRenderer>()->order = 0;

	GameObject* actorFloor = scene->CreateObject();
	actorFloor->transform->position = vector2(-200, 0);
	actorFloor->AddComponent<Gondola>();
	actorFloor->AddComponent<BitmapRenderer>();
	actorFloor->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\gondola.png");
	actorFloor->GetComponent<BitmapRenderer>()->order = 2;
	actorFloor->GetComponent<Gondola>()->AttachTrigger(controlBox->GetComponent<Trigger>());
	actorFloor->GetComponent<Gondola>()->index = 1;


	GameObject* actor = scene->CreateObject();
	actor->transform->SetParent(actorFloor->transform);
	actor->AddComponent<SpineRenderer>();
	actor->AddComponent<Actor>();
	actor->GetComponent<SpineRenderer>()->model=(*SpineModel::spineModelMap)["actorA"];
	actor->GetComponent<SpineRenderer>()->model->animationState->setAnimation(0,"animation",true);
	actor->AddComponent<LightAdapter>();





	GameObject* actressFloor = scene->CreateObject();
	actressFloor->transform->position = vector2(200, -180);
	actressFloor->AddComponent<Gondola>();
	actressFloor->AddComponent<BitmapRenderer>();
	actressFloor->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\gondola.png");
	actressFloor->GetComponent<BitmapRenderer>()->order = 2;
	actressFloor->GetComponent<Gondola>()->AttachTrigger(controlBox->GetComponent<Trigger>());
	actressFloor->GetComponent<Gondola>()->index = 2;


	GameObject* actress = scene->CreateObject();
	actress->transform->SetParent(actressFloor->transform);
	actress->AddComponent<SpineRenderer>();
	actress->AddComponent<Actor>();
	actress->GetComponent<SpineRenderer>()->model = (*SpineModel::spineModelMap)["actorB"];
	actress->GetComponent<SpineRenderer>()->model->animationState->setAnimation(0,"animation",true);
	actress->AddComponent<LightAdapter>();

	cloud->GetComponent<SkyObject>()->AttachTrigger(controlBox->GetComponent<Trigger>());
	dummy->GetComponent<SkyObject>()->next = sun->GetComponent<SkyObject>();
	sun->GetComponent<SkyObject>()->next = moon->GetComponent<SkyObject>();
	moon->GetComponent<SkyObject>()->next = cloud->GetComponent<SkyObject>();
	cloud->GetComponent<SkyObject>()->next = dummy->GetComponent<SkyObject>();

	dummy->GetComponent<SkyObject>()->previous = cloud->GetComponent<SkyObject>();
	sun->GetComponent<SkyObject>()->previous = dummy->GetComponent<SkyObject>();
	moon->GetComponent<SkyObject>()->previous = sun->GetComponent<SkyObject>();
	cloud->GetComponent<SkyObject>()->previous = moon->GetComponent<SkyObject>();

	controlBox->GetComponent<ControlBox>()->currentSky = dummy->GetComponent<SkyObject>();
	return controlBox;
}

GammaEngine::GameObject* Ingame::CreateMusicBox(Scene* scene, float x, float y)
{
	GameObject* musicBox = scene->CreateObject();
	musicBox->transform->position = vector2(x, y);
	musicBox->transform->scale = vector2(0.8,0.8);

	musicBox->AddComponent<BitmapRenderer>();
	musicBox->AddComponent<MusicControlBox>();
	musicBox->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\musiccontrolbox.png");
	musicBox->GetComponent<BitmapRenderer>()->order = 3;

	musicBox->AddComponent<BoxCollider>();
	musicBox->GetComponent<BoxCollider>()->SetBounds(vector2(100, 100));
	musicBox->GetComponent<BoxCollider>()->isTrigger = true;
	musicBox->tag = new std::string("Trigger");

	SoundSystem::Instance()->CreateReverbSound("Resources/Music/bird.wav", true);
	SoundSystem::Instance()->CreateReverbSound("Resources/Music/wave.wav", true);
	
	return musicBox;
}

GameObject* Ingame::CreateElevator(Scene* scene, float x, float y)
{
	//Platform
	GameObject* elevator_ = scene->CreateObject();
	elevator_->transform->position = vector2(x, y);

	elevator_->AddComponent<BitmapRenderer>();
	elevator_->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\elevator_cart.png");
	elevator_->GetComponent<BitmapRenderer>()->offset = vector2(0,20-elevator_->GetComponent<BitmapRenderer>()->size.y / 2);
	elevator_->GetComponent<BitmapRenderer>()->order = 3;

	elevator_->AddComponent<RectangleRenderer>();
	elevator_->GetComponent<RectangleRenderer>()->size = vector2(200, 20);
	elevator_->GetComponent<RectangleRenderer>()->order = 1;

	elevator_->AddComponent<BoxCollider>();
	elevator_->GetComponent<BoxCollider>()->SetBounds(vector2(200, 20));
	elevator_->AddComponent<Elevator>();

	elevator_->AddComponent<AudioSource>();
	elevator_->GetComponent<AudioSource>()->CreateSound("Resources/Music/elevatoronce.ogg", false);
	elevator_->GetComponent<AudioSource>()->SetVolume(2, 0.5f);
	
	elevator_->tag = new std::string("Elevator");

	GameObject* elevator_area = scene->CreateObject();
	elevator_area->transform->parent = elevator_->transform;
	elevator_area->transform->position = vector2(0, -50);

	elevator_area->AddComponent<BoxCollider>();
	elevator_area->GetComponent<BoxCollider>()->SetBounds(vector2(200, 200));
	elevator_area->GetComponent<BoxCollider>()->isTrigger=true;
	elevator_area->tag = new std::string("Elevator");


	GameObject* elevatorPile = scene->CreateObject();
	elevatorPile->transform->position = vector2(x, y);

	elevatorPile->AddComponent<BitmapRenderer>();
	elevatorPile->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\elevator_fail.png");
	elevatorPile->GetComponent<BitmapRenderer>()->offset = vector2(0, 20 - elevator_->GetComponent<BitmapRenderer>()->size.y / 2);
	elevatorPile->GetComponent<BitmapRenderer>()->order = 0;

// 	elevator_->AddComponent<BitmapRenderer>();
// 	elevator_->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\elevator_fail.png");
// 	elevator_->GetComponent<BitmapRenderer>()->offset = vector2(0, 20 - elevator_->GetComponent<BitmapRenderer>()->size.y / 2);
// 	elevator_->GetComponent<BitmapRenderer>()->order = 2;

	return elevator_;
}

GameObject* Ingame::CreateScaffolding(Scene* scene, float x, float y)
{
	//button
	GameObject* scaffolding = scene->CreateObject();
	scaffolding->transform->position = vector2(x, y);


	scaffolding->AddComponent<BitmapRenderer>();
	scaffolding->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\scaffolding_original.png");
	scaffolding->GetComponent<BitmapRenderer>()->offset = vector2(0, -scaffolding->GetComponent<BitmapRenderer>()->size.y);
	scaffolding->GetComponent<BitmapRenderer>()->order = 1;

	scaffolding->AddComponent<BoxCollider>();
	scaffolding->GetComponent<BoxCollider>()->SetBounds(scaffolding->GetComponent<BitmapRenderer>()->size);
	scaffolding->GetComponent<BoxCollider>()->isTrigger = true;
	scaffolding->AddComponent<Scaffolding>();

	return scaffolding;
}

GameObject* Ingame::CreateLadder(Scene* scene, float x, float y)
{
	//button
	GameObject* ladder = scene->CreateObject();
	ladder->transform->position = vector2(x, y);

	ladder->AddComponent<BitmapRenderer>();
	ladder->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\ladder.png");
	ladder->GetComponent<BitmapRenderer>()->order = 0;


	ladder->AddComponent<BoxCollider>();
	ladder->GetComponent<BoxCollider>()->SetBounds(vector2(10,ladder->GetComponent<BitmapRenderer>()->size.y));
	ladder->GetComponent<BoxCollider>()->isTrigger=true;

	ladder->AddComponent<Ladder>();

	ladder->tag = new std::string("Ladder");

	return ladder;
}

GammaEngine::GameObject* Ingame::CreateLeftPlatform(Scene* scene, float x, float y)
{
	//Platform
	GameObject* platform_ = scene->CreateObject();
	platform_->transform->position = vector2(x, y);

	platform_->AddComponent<BitmapRenderer>();
	platform_->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\secondfloor_L.png");
	platform_->GetComponent<BitmapRenderer>()->order = 0;

	//Debug::DrawRectangle(vector2(1020, 50), vector2(x, y), 0);

	platform_->AddComponent<BoxCollider>();
	platform_->GetComponent<BoxCollider>()->SetBounds(vector2(1020, 50));

	platform_->AddComponent<Rigidbody>();
	platform_->GetComponent<Rigidbody>()->useGravity = false;
	platform_->GetComponent<Rigidbody>()->mass = 0;

	platform_->tag = new std::string("Obstacle");

	return platform_;
}

GammaEngine::GameObject* Ingame::CreateRightPlatform(Scene* scene, float x, float y)
{
	//Platform
	GameObject* platform_ = scene->CreateObject();
	platform_->transform->position = vector2(x, y);

	platform_->AddComponent<BitmapRenderer>();
	platform_->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\secondfloor_R.png");
	platform_->GetComponent<BitmapRenderer>()->order = 0;

	//Debug::DrawRectangle(vector2(1020, 50), vector2(x, y), 0);

	platform_->AddComponent<BoxCollider>();
	platform_->GetComponent<BoxCollider>()->SetBounds(vector2(1020, 50));

	platform_->AddComponent<Rigidbody>();
	platform_->GetComponent<Rigidbody>()->useGravity = false;
	platform_->GetComponent<Rigidbody>()->mass = 0;

	platform_->tag = new std::string("Obstacle");

	return platform_;
}

GameObject* Ingame::CreateWaterTank(Scene* scene, float x, float y)
{
	GameObject* rainSystem = CreateRainParticle(scene, 0, -250);

	GameObject* waterTank = scene->CreateObject();
	waterTank->transform->position = vector2(x, y);

	waterTank->AddComponent<BitmapRenderer>();
	waterTank->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\watertank.png");
	waterTank->GetComponent<BitmapRenderer>()->order = 0.9f;
	waterTank->AddComponent<BoxCollider>();
	waterTank->GetComponent<BoxCollider>()->SetBounds(vector2(100, 100));
	waterTank->GetComponent<BoxCollider>()->isTrigger = true;
	waterTank->AddComponent<Wheel>();
	waterTank->AddComponent<WaterTank>();

	waterTank->AddComponent<AudioSource>();
	waterTank->GetComponent<AudioSource>()->CreateReverbSound("Resources/Music/wheelonce.ogg", false);

	waterTank->tag = new std::string("Reactant");

	waterTank->tag = new std::string("Trigger");
	
	GameObject* wheel = scene->CreateObject();
	wheel->transform->SetParent(waterTank->transform);

	wheel->AddComponent<BitmapRenderer>();
	wheel->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\wheel.png");
	wheel->GetComponent<BitmapRenderer>()->size = vector2(100, 100);
	wheel->GetComponent<BitmapRenderer>()->order = 0.95f;
	wheel->AddComponent<HighLighter>();

	waterTank->GetComponent<Wheel>()->wheel = wheel->transform;



	wheel->tag = new std::string("Trigger");


	for (auto& emitter : *(rainSystem->GetComponent<ParticleSystem>()->GetEmitters()))
	{
		waterTank->GetComponent<WaterTank>()->AddRainEmitter(emitter);
	}

	waterTank->GetComponent<Reactant>()->AttachTrigger(waterTank->GetComponent<Trigger>());

	return waterTank;
}

GameObject* Ingame::CreateBox(Scene* scene, float x, float y)
{
	//button
	GameObject* box = scene->CreateObject();
	box->transform->position = vector2(x, y);

	box->AddComponent<BitmapRenderer>();
	box->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\box_front.png");
	box->GetComponent<BitmapRenderer>()->order = 2;

	box->AddComponent<Rigidbody>();
	box->GetComponent<Rigidbody>()->useGravity = true;
	//box->GetComponent<Rigidbody>()->mass = 5;//끌때
	box->GetComponent<Rigidbody>()->mass = 15;
	box->GetComponent<Rigidbody>()->restitution = 0;
	box->GetComponent<Rigidbody>()->dynamicFriction = 1.0f;

	box->AddComponent<BoxCollider>();
	box->GetComponent<BoxCollider>()->SetBounds(box->GetComponent<BitmapRenderer>()->size);

	box->AddComponent<Box>();

	box->tag = new std::string("Box");

	return box;
}

GameObject* Ingame::CreateArch(Scene* scene, float x, float y)
{
	//Platform
	GameObject* arch = scene->CreateObject();
	arch->transform->position = vector2(x, y);

	arch->AddComponent<BitmapRenderer>();
	arch->GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Resources\\Object\\arch_castle.png");
	arch->GetComponent<BitmapRenderer>()->order = 4;

	arch->AddComponent<Arch>();
	arch->AddComponent<LightAdapter>();

	arch->tag = new std::string("Reactant");
	return arch;
}


GameObject* Ingame::CreatePointLight(Scene* scene, float x, float y, float magnitude)
{
	//Platform
	GameObject* light_ = scene->CreateObject();
	light_->transform->position = vector2(x, y);
	light_->AddComponent<PointLight>();
	light_->GetComponent<PointLight>()->SetColor(vector3(0.3,0.3, 1));
	light_->GetComponent<PointLight>()->SetMagnitude(magnitude);
	return light_;
}

GameObject* Ingame::CreateSpotLight(Scene* scene, float x, float y)
{
	//Platform
	GameObject* light_ = scene->CreateObject();
	light_->transform->position = vector2(x, y);
	light_->AddComponent<SpotLight>();
	light_->GetComponent<SpotLight>()->SetColor(vector3(1, 1, 1));
	light_->GetComponent<SpotLight>()->SetConeAngle(120.0f);
	light_->GetComponent<SpotLight>()->SetAt(vector3(0, 400,0));
	light_->GetComponent<SpotLight>()->SetFocus(1.0f);
	light_->GetComponent<SpotLight>()->SetMagnitude(2);
	//Tween::Animate(light_->GetComponent<SpotLight>()->z, PLAYBACK::LOOP_PINGPONG, 500, EASING::INBACK, 5);
	//Tween::Animate(light_->GetComponent<SpotLight>()->focus, PLAYBACK::LOOP_PINGPONG,100, EASING::INBACK, 5);
	return light_;
}

GameObject* Ingame::CreateDistantLight(Scene* scene, float azimuth, float elevation, float magnitude)
{
	//Platform
	GameObject* light_ = scene->CreateObject();
	light_->AddComponent<DistantLight>();

	light_->GetComponent<DistantLight>()->SetColor(vector3(0, 1, 1));
	light_->GetComponent<DistantLight>()->SetAzimuth(azimuth);
	light_->GetComponent<DistantLight>()->SetElvation(elevation);
	light_->GetComponent<DistantLight>()->SetMagnitude(magnitude);

	return light_;
}

GameObject* Ingame::CreateTextAnimation(Scene* scene)
{
	//Platform
	GameObject* text = scene->CreateObject();
	text->AddComponent<TextAnimationRenderer>();
	text->GetComponent<TextAnimationRenderer>()->SetText(L"안녕하세요");
	text->AddComponent<TextAnimator>();
	text->GetComponent<TextAnimator>()->Play();


	return text;
}

GameObject* Ingame::CreateTitleBGM(Scene* scene)
{
	GameObject* titleBgm = new GameObject();
	titleBgm->AddComponent<AudioSource>();
	titleBgm->GetComponent<AudioSource>()->CreateReverbSound("Resources/Music/TitleBGM.mp3", true);
	titleBgm->GetComponent<AudioSource>()->PlayReverb(0);
	titleBgm->GetComponent<AudioSource>()->SetVolume(0, 0.6f);
	return titleBgm;
}

GameObject* Ingame::CreateIngameBGM(Scene* scene)
{
	GameObject* ingameBgm = new GameObject();
	ingameBgm->AddComponent<AudioSource>();
	ingameBgm->GetComponent<AudioSource>()->CreateReverbSound("Resources/Music/Ingame.mp3", true);
	ingameBgm->GetComponent<AudioSource>()->PlayReverb(1); 
	ingameBgm->GetComponent<AudioSource>()->SetVolume(1, 0.4f);
	return ingameBgm;
}

GameObject* Ingame::CreateTickTock(Scene* scene)
{
	GameObject* tickTock = new GameObject();

	tickTock->AddComponent<AudioSource>();
	tickTock->GetComponent<AudioSource>()->CreateReverbSound("Resources/Music/ladder.wav", true);
	tickTock->GetComponent<AudioSource>()->Play(2);
	tickTock->GetComponent<AudioSource>()->SetVolume(2, 0.4f);

	return tickTock;
}

GameObject* Ingame::CreateDiscSound(Scene* scene)
{
	GameObject* disc = new GameObject();

	disc->AddComponent<AudioSource>();
	disc->GetComponent<AudioSource>()->CreateSound("tick_tock.wav", true);

	return nullptr;
}

GameObject* Ingame::CreateSwitchSound(Scene* scene)
{
	GameObject* Switch = new GameObject();

	Switch->AddComponent<AudioSource>();
	Switch->GetComponent<AudioSource>()->CreateSound("tick_tock.wav", true);

	return Switch;
}

GameObject* Ingame::CreatePulleySound(Scene* scene)
{
	GameObject* pulley = new GameObject();

	pulley->AddComponent<AudioSource>();
	pulley->GetComponent<AudioSource>()->CreateSound("tick_tock.wav", true);

	return pulley;
}

GameObject* Ingame::CreateArchSound(Scene* scene)
{
	GameObject* arch = new GameObject();

	arch->AddComponent<AudioSource>();
	arch->GetComponent<AudioSource>()->CreateSound("tick_tock.wav", true);

	return arch;
}

GameObject* Ingame::CreateElevatorSound(Scene* scene)
{
	GameObject* elevator = new GameObject();

	elevator->AddComponent<AudioSource>();
	elevator->GetComponent<AudioSource>()->CreateSound("Resources/Music/elevator.ogg", false);
	elevator->GetComponent<AudioSource>()->SetVolume(21, 0.5f);

	return elevator;
}

GameObject* Ingame::CreateRainingrSound(Scene* scene)
{
	GameObject* rain = new GameObject();

	rain->AddComponent<AudioSource>();
	rain->GetComponent<AudioSource>()->CreateSound("tick_tock.wav", true);

	return rain;
}


void Ingame::CreateFromData(Scene* scene, MapDataLoader* mapData)
{
	std::vector<GameObject*> objList;
	std::vector<Data>& datas = mapData->GetMapData(0);
	for (auto& data : datas)
	{
		objList.push_back((*g_ingameFactory[data.objectID])(scene, data.x, data.y));
	}

	for (int i = 0; i < datas.size(); ++i)
	{
		switch ((MapDataLoader::eObject)datas[i].objectID)
		{
// 			case MapDataLoader::eObject::WATERTANK:
// 			{
// 				for (auto& emitter : *(rainSystem->GetComponent<ParticleSystem>()->GetEmitters()))
// 				{
// 					objList[i]->GetComponent<WaterTank>()->AddRainEmitter(emitter);
// 				}
// 
// 				for (int j = 0; j < datas.size(); ++j)
// 				{
// 					if (datas[j].objectID == (int)MapDataLoader::eObject::WHEEL)
// 					{
// 						objList[i]->GetComponent<Reactant>()->AttachTrigger(objList[j]->GetComponent<Trigger>());
// 						break;
// 					}
// 				}
// 			}
// 			break;

			case MapDataLoader::eObject::ARCH:
			{
				for (int j = 0; j < datas.size(); ++j)
				{
					if (datas[j].objectID == (int)MapDataLoader::eObject::LEVER)
					{
						objList[i]->GetComponent<Reactant>()->AttachTrigger(objList[j]->GetComponent<Trigger>());
						break;
					}
				}
			}
			break;

			case MapDataLoader::eObject::ELEVATOR:
			{
				for (int j = 0; j < datas.size(); ++j)
				{
					if (datas[j].objectID == (int)MapDataLoader::eObject::SCAFFOLDING)
					{
						objList[i]->GetComponent<Reactant>()->AttachTrigger(objList[j]->GetComponent<Trigger>());
						break;
					}
				}
			}
			break;

			case MapDataLoader::eObject::CYCLE:
			{
				for (int j = 0; j < datas.size(); ++j)
				{
					if (datas[j].objectID == (int)MapDataLoader::eObject::ARCH)
					{
						objList[i]->GetComponent<ArchDisk>()->AttachArch(objList[j]->GetComponent<Arch>());
						break;
					}
				}
			}
			break;

			case MapDataLoader::eObject::MUSIC:
			{
				for (int j = 0; j < datas.size(); ++j)
				{
					if (datas[j].objectID == (int)MapDataLoader::eObject::MUSIC)
					{
						GameManager::SetMusicControl(objList[i]->GetComponent<MusicControlBox>());
						break;
					}
				}
			}
			break;

			default:
				break;
		}
	}
}

GammaEngine::GameObject* Ingame::BoxFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateBox(scene, x, y);
}

GammaEngine::GameObject* Ingame::LadderFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateLadder(scene, x, y);
}

GammaEngine::GameObject* Ingame::LeftPlatformFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateLeftPlatform(scene, x, y);
}

GammaEngine::GameObject* Ingame::RightPlatformFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateRightPlatform(scene, x, y);
}

GammaEngine::GameObject* Ingame::WaterTankFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateWaterTank(scene, x, y);
}

GammaEngine::GameObject* Ingame::ArchFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateArch(scene, 0, -700);
}

GammaEngine::GameObject* Ingame::ElevatorFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateElevator(scene, x, y);
}

GammaEngine::GameObject* Ingame::ControlBoxFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateControlBox(scene, x, y);
}

GammaEngine::GameObject* Ingame::MusicBoxFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateMusicBox(scene, x, y);
}

GammaEngine::GameObject* Ingame::WheelFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateWheel(scene, x, y);
}

GammaEngine::GameObject* Ingame::ScaffoldingFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateScaffolding(scene, x, y);
}

GammaEngine::GameObject* Ingame::LeverFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateLever(scene, x, y);
}

GammaEngine::GameObject* Ingame::CycleFunctor::operator()(Scene* scene, float x, float y)
{
	return Ingame::CreateArchDisk(scene, x, y);
}