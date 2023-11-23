#pragma once
#include "GRX.h"
#include "IInteractable.h"
using namespace GammaEngine;

struct PlayerAction
{
	int id;
	KeyState buttonA;
	KeyState buttonB;
	KeyState buttonX;
	KeyState buttonY;
	KeyState buttonLeft;
	KeyState buttonRight;
	KeyState buttonUp;
	KeyState buttonDown;
	KeyState LeftThumb;
	KeyState RightThumb;
	KeyState LeftShoulder;
	KeyState RightShoulder;
	KeyState buttonStart;
	KeyState buttonBack;
	float LeftTrigger;
	float RightTrigger;
	float ThumbLX;
	float ThumbLY;
	float ThumbRX;
	float ThumbRY;
	float ThumbLAngle;
	float ThumbRAngle;

};



class Trigger;
class Player : public GammaEngine::Component
{
public:
	enum PlayerState
	{
		IDLE,
		WALK,
		RUN,
		JUMP,
		GRAB,
		STOP,
		CLIMB,
		INTERACT,
		UI
	};


public:
	Player(GameObject* t);
	~Player();

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnCollisionEnter(CollisionResponse res) override;
	virtual void OnCollisionExit(CollisionResponse res) override;
	virtual void OnCollisionStay(CollisionResponse res) override;

public:
	void CommonInput();
	void InteractInput();
	void ClimbInput();
	void GrabInput();
	void UIInput();
	void Move(vector2);
	void Jump(float v);
	void Jump(float v, vector2 dir);
	void Interact();
	void TranslateAnimation();
	void SetAnimationStateFront();
	void SetAnimationStateBack();
	void Pause();
	void Resume();
	void Fail();
	void FailEnd();

private:
	void CheckJumpable();

public:
	float runSpeed = 20;
	float walkSpeed = 7;
	float grabSpeed = 2;
	float climbSpeed = 5;
	float jumpForce = 17;
	float pushForce = 400;
	float responsiveness=50;
	WORD interactButton = XINPUT_GAMEPAD_B;
	WORD jumpButton = XINPUT_GAMEPAD_A;
	bool runnable = true;
	bool run = false;
	GammaEngine::Transform* grab = nullptr;

	int id = 0;
	IInteractable* interactTarget;
	PlayerState state = IDLE;
	Subject<PlayerAction> actionSubject;
	GameObject* info;

private:
	SpineRenderer* spineRenderer;
	Rigidbody* rigidbody;
	TimerHandler* vibrateHandler_=nullptr;
	bool jumpable_=false;
	bool interectable =true;
	float interectCool = 0.5;
	float landingDelay_ =0.5f;
	const float deadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	bool isPaused_ = false;
	vector2 pausedVelocity_;
	vector2 stride = vector2(30, 0);
public:
	void SetEmitter(std::vector<ParticleEmitter*>* emitters);
	void AddEmitter(ParticleEmitter* emitter);
	void SetAnimator(GameObject* animator);
private:
	std::vector<ParticleEmitter*> emitters_;
	GameObject* animator_;
};

