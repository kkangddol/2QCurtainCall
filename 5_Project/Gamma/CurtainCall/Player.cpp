#include "GammaEngine.h"
#include "IInteractable.h"
#include "Trigger.h"
#include "Ladder.h"
#include "GameManager.h"
#include "TitleManager.h"
#include "HighLighter.h"
#include "Information.h"
#include "Player.h"


using namespace GammaEngine;

Player::Player(GameObject* t) : Component(t)
{
}

Player::~Player()
{
	TitleManager::UnRegistPlayer(this);
	GameManager::UnRegistPlayer(this);
}

void Player::Start()
{
	info = Information::Create(L"b");
	Tween::Animate(info->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	spineRenderer = GetComponent<SpineRenderer>();
	rigidbody = GetComponent<Rigidbody>();
	
	SetAnimationStateFront();
	spineRenderer->model->animationState->setAnimation(0, "standby", true);
	GameManager::RegistPlayer(this);
	TitleManager::RegistPlayer(this);

	
	//Tween::Animate(transform->rotation, PLAYBACK::LOOP_FORWARD, 360, EASING::LINEAR, 5);
}

void Player::Move(vector2 v)
{
	gameObject->GetComponent<Rigidbody>()->AddForce(v, Rigidbody::ForceMode::Force);  
	//SoundSystem::Instance()->PathPlay(L"Resources/Music/walk.mp3", 8);
}

void Player::Jump(float v)
{
	state = JUMP;
	spineRenderer->model->animationState->setAnimation(0, "jump", false);
	spineRenderer->model->animationState->setTimeScale(1);
	gameObject->GetComponent<Rigidbody>()->velocity.y = 0;
	gameObject->GetComponent<Rigidbody>()->AddForce(vector2(0, -v), Rigidbody::ForceMode::Impulse);
	SoundSystem::Instance()->PathPlay(L"Resources/Music/jump.mp3", 11);
}

void Player::Jump(float v, vector2 dir)
{
	gameObject->GetComponent<Rigidbody>()->velocity.y = 0;
	gameObject->GetComponent<Rigidbody>()->AddForce(vector2::Normalize(dir) * v, Rigidbody::ForceMode::Impulse);
	state = JUMP;
	spineRenderer->model->animationState->setAnimation(0, "jump", false);
	spineRenderer->model->animationState->setTimeScale(1);
}

void Player::Interact()
{
	Trigger* trigger = dynamic_cast<Trigger*>(interactTarget);
	if ( trigger && !trigger->user)
	{
		state = INTERACT;
		info->isEnabled = false;
		spineRenderer->model->animationState->setAnimation(0, "standby", false);
		interactTarget->Use(this);
		
	}
	
}

void Player::CheckJumpable()
{
	std::vector<std::string> tagList;
	tagList.push_back(std::string("Reactant"));
	tagList.push_back(std::string("Obstacle"));
	tagList.push_back(std::string("Box"));
	RaycastResponse res1 = Physics::Raycast(transform->position+ stride, transform->position + stride + vector2::Down * 120, tagList);
	RaycastResponse res2 = Physics::Raycast(transform->position- stride, transform->position - stride + vector2::Down * 120, tagList);
	if (res1.hit || res2.hit)
	{
		jumpable_ = true;
	}
	else
	{
		jumpable_ = false;
	}
}

void Player::SetEmitter(std::vector<ParticleEmitter*>* emitters)
{
	emitters_ = *emitters;
}

void Player::AddEmitter(ParticleEmitter* emitter)
{
	emitters_.push_back(emitter);
}

void Player::SetAnimator(GameObject* animator)
{
	animator_ = animator;
}

void Player::UIInput()
{
	PlayerAction action;
	action.id = id;
	action.buttonY = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_Y];
	action.buttonX = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_X];
	action.buttonA = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_A];
	action.buttonB = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_B];
	action.buttonBack = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_BACK];
	action.buttonStart = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_START];
	action.buttonLeft = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_DPAD_LEFT];
	action.buttonRight = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_DPAD_RIGHT];
	action.buttonUp = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_DPAD_UP];
	action.buttonDown = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_DPAD_DOWN];
	action.LeftShoulder = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_LEFT_SHOULDER];
	action.RightShoulder = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_RIGHT_SHOULDER];
	action.LeftThumb = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_LEFT_THUMB];
	action.RightThumb = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_RIGHT_THUMB];
	action.LeftTrigger = GamepadManager::GetPad(id)->GetTriggerValue(0);
	action.RightTrigger = GamepadManager::GetPad(id)->GetTriggerValue(1);
	action.ThumbLX = GamepadManager::GetPad(id)->GetStickValue(0);
	action.ThumbLY = GamepadManager::GetPad(id)->GetStickValue(1);
	action.ThumbRX = GamepadManager::GetPad(id)->GetStickValue(2);
	action.ThumbRY = GamepadManager::GetPad(id)->GetStickValue(3);
	action.ThumbLAngle = GamepadManager::GetPad(id)->GetStickRotation(0);
	action.ThumbRAngle = GamepadManager::GetPad(id)->GetStickRotation(1);
	actionSubject.OnNext(action);
}
void Player::CommonInput()
{
	//조이패드
	if (state != INTERACT && state != CLIMB && state != STOP)
	{

		if (GamepadManager::GetPad(id)->GetTriggerValue(0) < 200 && GamepadManager::GetPad(id)->GetTriggerValue(1) < 200)
		{
			runnable =true;
		}

		if (runnable && (GamepadManager::GetPad(id)->GetTriggerValue(0) > 200 || GamepadManager::GetPad(id)->GetTriggerValue(1) > 200))
		{
			run = true;
		}
		else
		{
			run = false;
		}

		if(run)
		{
			if (GamepadManager::GetPad(id)->GetStickValue(0) > deadZone)
				Move(runSpeed * vector2::Right);

			if (GamepadManager::GetPad(id)->GetStickValue(0) < -deadZone)
				Move(runSpeed * vector2::Left);
		}
		else
		{
			if (GamepadManager::GetPad(id)->GetStickValue(0) > deadZone)
				Move(walkSpeed * vector2::Right);

			if (GamepadManager::GetPad(id)->GetStickValue(0) < -deadZone)
				Move(walkSpeed * vector2::Left);
		}

		if (GamepadManager::GetPad(id)->GetStickValue(1) > deadZone * 2 || GamepadManager::GetPad(id)->GetStickValue(1) < -deadZone * 2)
		{
			Ladder* ladder = dynamic_cast<Ladder*>(interactTarget);
			if (ladder)
			{
				state = CLIMB;
				SetAnimationStateBack();
				spineRenderer->model->animationState->setAnimation(0, "climbing", true);
				GetComponent<Rigidbody>()->useGravity = false;
				GetComponent<Rigidbody>()->velocity = vector2();
				GetComponent<BoxCollider>()->isTrigger = true;
				interactTarget->Use(this);

			}
		}

		if (GamepadManager::GetPad(id)->GetWbuttonDown(interactButton))
		{
			Interact();	
		}

		if (GamepadManager::GetPad(id)->GetWbuttonDown(jumpButton) && jumpable_)
		{
			Jump(jumpForce);
			jumpable_ = false;
			
		}



		if (id == 0)
		{
			if (Input::GetKey('J'))
			{
				//키보드
				if (Input::GetKey('A'))
					Move(runSpeed * vector2::Left);

				if (Input::GetKey('D'))
					Move(runSpeed * vector2::Right);
			}
			else
			{
				//키보드
				if (Input::GetKey('A'))
					Move(walkSpeed * vector2::Left);
				if (Input::GetKeyDown('A'))
					SoundSystem::Instance()->PathPlay(L"Resources/Music/walk.mp3", 9);
				if (Input::GetKeyUp('A'))
					SoundSystem::Instance()->PathStop(L"Resources/Music/walk.mp3", 9);
				if (Input::GetKey('D'))
					Move(walkSpeed * vector2::Right);
				if (Input::GetKeyDown('D'))
					SoundSystem::Instance()->PathPlay(L"Resources/Music/walk.mp3", 9);
				if (Input::GetKeyUp('D'))
					SoundSystem::Instance()->PathStop(L"Resources/Music/walk.mp3", 9);
			}

			if (Input::GetKeyDown('H'))
				Jump(jumpForce);
		}
		else
		{
			//키보드
			if (Input::GetKey(VK_NUMPAD3))
			{
				if (Input::GetKey(VK_LEFT))
					Move(runSpeed * vector2::Left);

				if (Input::GetKey(VK_RIGHT))
					Move(runSpeed * vector2::Right);
			}
			else
			{
				if (Input::GetKey(VK_LEFT))
					Move(walkSpeed * vector2::Left);

				if (Input::GetKey(VK_RIGHT))
					Move(walkSpeed * vector2::Right);
			}

			if (Input::GetKeyDown(VK_NUMPAD2))
				Jump(jumpForce);
		}
	}
	CheckJumpable();
}
void Player::SetAnimationStateFront()
{
	std::string str = "player";
	str.append(std::to_string(id+1));
	str.append("_front");
	spineRenderer->model = (*SpineModel::spineModelMap)[str];	
}

void Player::SetAnimationStateBack()
{
	std::string str = "player";
	str.append(std::to_string(id+1));
	str.append("_back");
	spineRenderer->model = (*SpineModel::spineModelMap)[str];

}


void Player::Pause()
{
	isPaused_ = true;
	pausedVelocity_ = rigidbody->velocity;
}

void Player::Resume()
{
	isPaused_ = false;
	rigidbody->velocity = pausedVelocity_;
	pausedVelocity_ = vector2(0, 0);
}

void Player::Fail()
{
	animator_->Enable();
	//animator_->Play(L"fail", PLAYBACK::LOOP_FORWARD);
}

void Player::FailEnd()
{
	animator_->Disable();
	//animator_->isEnabled = false;
}

void Player::ClimbInput()
{
	Ladder* ladder = dynamic_cast<Ladder*>(interactTarget);
	

	if (GamepadManager::GetPad(id)->GetStickValue(1) > deadZone && ladder)
	{
		Move(walkSpeed * vector2::Up);
	}

	if (GamepadManager::GetPad(id)->GetStickValue(1) < -deadZone && ladder && transform->position.y <= ladder->bottom)
	{
		Move(walkSpeed * vector2::Down);
	}

	if (GamepadManager::GetPad(id)->GetStickValue(0) > deadZone && GamepadManager::GetPad(id)->GetWbuttonDown(XINPUT_GAMEPAD_A))
	{
		GetComponent<Rigidbody>()->useGravity = true;
		SetAnimationStateFront();
		Jump(jumpForce, vector2(1, -1));
	}

	if (GamepadManager::GetPad(id)->GetStickValue(0) < -deadZone && GamepadManager::GetPad(id)->GetWbuttonDown(XINPUT_GAMEPAD_A))
	{
		GetComponent<Rigidbody>()->useGravity = true;
		SetAnimationStateFront();
		Jump(jumpForce, vector2(-1, -1));
	}
}

void Player::InteractInput()
{
	PlayerAction action;
	action.id = id;
	action.buttonY = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_Y];
	action.buttonX = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_X];
	action.buttonA = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_A];
	action.buttonB = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_B];
	action.buttonBack = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_BACK];
	action.buttonStart = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_START];
	action.buttonLeft = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_DPAD_LEFT];
	action.buttonRight = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_DPAD_RIGHT];
	action.buttonUp = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_DPAD_UP];
	action.buttonDown = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_DPAD_DOWN];
	action.LeftShoulder = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_LEFT_SHOULDER];
	action.RightShoulder = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_RIGHT_SHOULDER];
	action.LeftThumb = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_LEFT_THUMB];
	action.RightThumb = (*GamepadManager::GetPad(id)->wbuttonMap)[XINPUT_GAMEPAD_RIGHT_THUMB];
	action.LeftTrigger = GamepadManager::GetPad(id)->GetTriggerValue(0);
	action.RightTrigger = GamepadManager::GetPad(id)->GetTriggerValue(1);
	action.ThumbLX = GamepadManager::GetPad(id)->GetStickValue(0);
	action.ThumbLY = GamepadManager::GetPad(id)->GetStickValue(1);
	action.ThumbRX = GamepadManager::GetPad(id)->GetStickValue(2);
	action.ThumbRY = GamepadManager::GetPad(id)->GetStickValue(3);
	action.ThumbLAngle = GamepadManager::GetPad(id)->GetStickRotation(0);
	action.ThumbRAngle = GamepadManager::GetPad(id)->GetStickRotation(1);
	actionSubject.OnNext(action);

}
void Player::TranslateAnimation()
{
	if (state == CLIMB)
	{
		if(abs(rigidbody->velocity.y) > 10)
			spineRenderer->model->animationState->setTimeScale(1);
		else
			spineRenderer->model->animationState->setTimeScale(0);
	}

	if (state == CLIMB)
	{
		if (rigidbody->velocity.x > 0)
		{
			spineRenderer->SetFlipX(true);
		}
		else
		{
			spineRenderer->SetFlipX(false);
		}

	}

	if (state!= UI && state != INTERACT && state != JUMP && state != CLIMB && state != STOP && state != GRAB)
	{
		SetAnimationStateFront();
		if (rigidbody->velocity.x > 0)
		{
			spineRenderer->SetFlipX(true);
		}
		else
		{
			spineRenderer->SetFlipX(false);
		}

		if (state != IDLE)
		{
			//spineRenderer->model->animationState->setTimeScale(abs(rigidbody->velocity.x) / 200);
		}


		if (state != RUN && run && abs(rigidbody->velocity.x) > 100 && (GamepadManager::GetPad(id)->GetTriggerValue(0) > 200 || GamepadManager::GetPad(id)->GetTriggerValue(1) > 200))
		{
			spineRenderer->model->animationState->setAnimation(0, "run", true);
			state = RUN;
		}
		else if (state == RUN && rigidbody->velocity.x > 100 && GamepadManager::GetPad(id)->GetStickValue(0) < -deadZone )
		{
			spineRenderer->model->animationState->setAnimation(0, "stop", false);
			state = STOP;
			runnable = false;
			 Timer::Delay(1, false, [this]() {
				 if (state == STOP)
				 {
					 state = IDLE;
					 SetAnimationStateFront();
					 spineRenderer->model->animationState->setAnimation(0, "standby", false);
					 
				 }
			});
		}
		else if (state == RUN && rigidbody->velocity.x < -100 && GamepadManager::GetPad(id)->GetStickValue(0) > deadZone)
		{
			spineRenderer->model->animationState->setAnimation(0, "stop", false);
			state = STOP;
			runnable = false;
			Timer::Delay(1, false, [this]() {
				if (state == STOP)
				{
					state = IDLE;
					SetAnimationStateFront();
					spineRenderer->model->animationState->setAnimation(0, "standby", false);
				}
			});
		}
		else if (state != WALK && !run && abs(rigidbody->velocity.x) > 100 )
		{
			spineRenderer->model->animationState->setAnimation(0, "walk", true);
			
			state = WALK;
		}
		else if (state != IDLE && abs(rigidbody->velocity.x) <= 50 && (GamepadManager::GetPad(id)->GetStickValue(0) < deadZone && GamepadManager::GetPad(id)->GetStickValue(0) > -deadZone))
		{
			spineRenderer->model->animationState->setAnimation(0, "standby", true);
			spineRenderer->model->animationState->setTimeScale(1);
			state = IDLE;
		}
	}

	std::wstring str;
	switch (state)
	{
	case Player::IDLE:
		//GetComponent<AudioSource>()->Stop(3);
		str.append(L"IDLE : ");
		break;
	case Player::WALK:
		str.append(L"WALK : ");
		break;
	case Player::RUN:
		str.append(L"RUN : ");
		break;
	case Player::JUMP:
		str.append(L"JUMP : ");
		break;
	case Player::STOP:
		str.append(L"STOP : ");
		break;
	case Player::CLIMB:
		str.append(L"CLIMB : ");
		break;
	case Player::GRAB:
		str.append(L"GRAB : ");
		break;
	case Player::INTERACT:
		str.append(L"INTERACT : ");
		break;
	default:
		break;
	}


	str.append(std::to_wstring(abs(rigidbody->velocity.x)));
	Debug::DrawTextToWorld(vector2(100, 100), transform->position, str, L"Verdana", vector4(1, 0, 1, 1));
}

void Player::GrabInput()
{
	if (GamepadManager::GetPad(id)->GetWbuttonUp(XINPUT_GAMEPAD_B))
	{
		state = IDLE;
		grab->SetParent(nullptr, true);
		//grab->GetComponent<Rigidbody>()->isEnabled = true;
		grab->GetComponent<BoxCollider>()->isEnabled = true;
		grab = nullptr;
		SetAnimationStateFront();
		spineRenderer->offset.x = 0;
		spineRenderer->model->animationState->setAnimation(0, "standby", true);
		GetComponent<Rigidbody>()->RemoveIgnore("Box");
	}

	if (GamepadManager::GetPad(id)->GetStickValue(0) > deadZone)
		Move(grabSpeed * vector2::Right);

	if (GamepadManager::GetPad(id)->GetStickValue(0) < -deadZone)
		Move(grabSpeed * vector2::Left);
}

void Player::Update()
{
	if (isPaused_)
	{
		return;
	}

	if (state == INTERACT)
	{
		InteractInput();
	}
	else if (state == CLIMB)
	{
		ClimbInput();
	}
	else if (state == GRAB)
	{
		GrabInput();
	}
	else if (state == UI)
	{
		UIInput();
	}
	else
	{
		actionSubject.OnComplete();
		CommonInput();
	}
	emitters_[0]->SetActive(false);
	emitters_[1]->SetActive(false);
	emitters_[2]->SetActive(false);
	emitters_[3]->SetActive(false);
	emitters_[4]->SetActive(false);

	float currentSpeed = rigidbody->velocity.Length();
	if (150 <= currentSpeed && (state == WALK || state == RUN))
	{
		emitters_[0]->SetActive(true);
		emitters_[1]->SetActive(true);
		emitters_[2]->SetActive(true);
	}

	if (350 <= currentSpeed && (state == WALK || state == RUN))
	{
		emitters_[3]->SetActive(true);
		emitters_[4]->SetActive(true);
	}

	for (auto p : GetComponent<BoxCollider>()->ComputePoints())
	{
		Debug::DrawRectangle(vector2(5, 5), p, transform->rotation, vector4(1, 0, 0, 1));
	}

	TranslateAnimation();

	spineRenderer->order = 1 - 0.00001f * transform->position.x;
}

void Player::OnCollisionEnter(CollisionResponse res)
{
	if (res.other->CompareTag("Trigger"))
	{
		interactTarget = res.other->GetComponent<IInteractable>();
		if (interactTarget)
		{
			auto trigger = dynamic_cast<Trigger*>(interactTarget);
			trigger->GetComponent<HighLighter>()->On();
			info->isEnabled = true;
			info->transform->parent = trigger->transform;
			info->transform->position = vector2(0, 0);
			Tween::Animate(info->transform->position, PLAYBACK::ONCE_FORWARD, vector2(100, -100), OUTBACK, 1);
			//Tween::Animate(info->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
		}
	}
	if ((res.other->CompareTag("Obstacle") || res.other->CompareTag("Elevator") || res.other->CompareTag("Box") || res.other->CompareTag("Reactant")) && res.normal.y >= 0.7)
	{
		if (state == JUMP || state == CLIMB)
		{
			GetComponent<BoxCollider>()->isTrigger = false;
			SetAnimationStateFront();
			spineRenderer->model->animationState->setAnimation(0, "standby", true);
			state = IDLE;
		}
	}

	if (rigidbody->impulse.Length() > responsiveness)
	{
		GamepadManager::GetPad(id)->Vibrate(rigidbody->impulse.Length() * 10000, rigidbody->impulse.Length() * 10000, rigidbody->impulse.Length() / 5000);
	}
	

}
void Player::OnCollisionStay(CollisionResponse res)
{
	if (res.other->CompareTag("Trigger"))
	{
		interactTarget = res.other->GetComponent<IInteractable>();
	}
	if (res.other->CompareTag("Ladder"))
	{
		interactTarget = res.other->GetComponent<IInteractable>();
	}
	if (res.other->CompareTag("Elevator"))
	{
		if (abs(res.normal.y) > 0.7)
			GetComponent<Rigidbody>()->SetIgnore("Obstacle");
	}
	


	if (res.other->CompareTag("Box"))
	{
		if (res.normal.y < 0.2)
		{
			info->isEnabled = true;
			info->transform->parent = res.other->transform;
			info->transform->position = vector2(0, -50);
		}
		
		
		if (state != GRAB && res.normal.y < 0.2 && GamepadManager::GetPad(id)->GetWbutton(XINPUT_GAMEPAD_B))
		{
			info->isEnabled = false;
			state = GRAB;
			transform->position -= res.normal * 10;
			grab = res.other->transform;
			grab->SetParent(this->transform,true);
			SetAnimationStateFront();
			spineRenderer->model->animationState->setAnimation(0, "grab", false);
			grab->GetComponent<Rigidbody>()->isEnabled = false;
			
		}
	}
}

void Player::OnCollisionExit(CollisionResponse res)
{
	if (res.other->CompareTag("Elevator"))
	{
		GetComponent<Rigidbody>()->RemoveIgnore("Obstacle");
	}
	if (res.other->CompareTag("Box"))
	{
		info->isEnabled = false;
	}

	if (res.other->CompareTag("Trigger"))
	{
		dynamic_cast<Trigger*>(interactTarget)->GetComponent<HighLighter>()->Off();
		interactTarget = nullptr;
		info->isEnabled = false;
	}

	if (res.other->CompareTag("Ladder"))
	{
		interactTarget = nullptr;
		rigidbody->useGravity = true;
	}

}