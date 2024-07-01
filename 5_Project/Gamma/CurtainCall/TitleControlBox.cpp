#include "GammaEngine.h"
#include "GRX.h"
#include "TitleBoard.h"
#include "TitleManager.h"
#include "Information.h"
#include "Player.h"
#include "TitleControlBox.h"

TitleControlBox::TitleControlBox(GameObject* t) : Trigger(t)
{
	
}

void TitleControlBox::Start()
{
	Trigger::Start();
	infoUp = Information::Create(L"up_arrow");
	infoLeft = Information::Create(L"right_arrow");
	infoRight = Information::Create(L"left_arrow");
	infoDown = Information::Create(L"down_arrow");
	infoStick = Information::Create(L"L_shake");
	Tween::Animate(infoUp->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(infoLeft->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(infoRight->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(infoDown->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(infoStick->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(infoStick->transform->position.x, PLAYBACK::LOOP_PINGPONG, infoStick->transform->position.x+5, INOUTELASTIC, 1);
}



void TitleControlBox::ShowInfo()
{
	Information::DisableAll();
	if (TitleManager::state == TitleState::MENU)
	{
		infoUp->isEnabled = true;
		infoUp->transform->parent = transform;
		infoUp->transform->position = vector2();
		Tween::Animate(infoUp->transform->position, PLAYBACK::ONCE_FORWARD, vector2(0, -200), OUTBACK, 1);


		infoLeft->isEnabled = true;
		infoLeft->transform->parent = transform;
		infoLeft->transform->position = vector2();
		Tween::Animate(infoLeft->transform->position, PLAYBACK::ONCE_FORWARD, vector2(150, -100), OUTBACK, 1);


		infoRight->isEnabled = true;
		infoRight->transform->parent = transform;
		infoRight->transform->position = vector2();
		Tween::Animate(infoRight->transform->position, PLAYBACK::ONCE_FORWARD, vector2(-150, -100), OUTBACK, 1);
	}
	else if (TitleManager::state == TitleState::STAGE)
	{
		infoUp->isEnabled = true;
		infoUp->transform->parent = transform;
		infoUp->transform->position = vector2();
		Tween::Animate(infoUp->transform->position, PLAYBACK::ONCE_FORWARD, vector2(0, -300), OUTBACK, 1);

		infoDown->isEnabled = true;
		infoDown->transform->parent = transform;
		infoDown->transform->position = vector2();
		Tween::Animate(infoDown->transform->position, PLAYBACK::ONCE_FORWARD, vector2(0, -100), OUTBACK, 1);

		infoStick->isEnabled = true;
		infoStick->transform->parent = transform;
		infoStick->transform->position = vector2();
		Tween::Animate(infoStick->transform->position, PLAYBACK::ONCE_FORWARD, vector2(0, -200), OUTBACK, 1);
	}
}

void TitleControlBox::Use(Player* p)
{
	Trigger::RegistPlayer(p);
	Trigger::Hold();
	user->info->isEnabled = false;
	Tween::Animate(p->transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x, EASING::LINEAR, 1);

	ShowInfo();
	
	user->actionSubject.Where([](PlayerAction x) {
		return  TitleManager::state == STAGE && x.buttonDown == KeyState::pressed;
		}).Throttle(1).Subscribe([this](PlayerAction x) {
			TitleManager::state = MENU;
			SoundSystem::Instance()->PathPlay(L"Resources/Music/buttonclick.mp3", 4);
			TitleManager::ShowMenu();
			ShowInfo();
		});

		user->actionSubject.Where([](PlayerAction x) {
			return  TitleManager::state == CREDIT && x.buttonDown == KeyState::pressed;
			}).Throttle(1).Subscribe([this](PlayerAction x) {
				TitleManager::state = MENU;
				SoundSystem::Instance()->PathPlay(L"Resources/Music/buttonclick.mp3", 4);
			TitleManager::ShowMenu();
			TitleManager::ExitCredit();
			ShowInfo();
			});

	user->actionSubject.Where([](PlayerAction x) {
		return  TitleManager::state == STAGE && x.buttonUp == KeyState::pressed;
		}).Subscribe([this](PlayerAction x) {
			TitleManager::state = CUTSCENE;
			SoundSystem::Instance()->PathPlay(L"Resources/Music/buttonclick.mp3", 4);
			Timer::Delay(8, false, []()
				{
					SceneManager::LoadScene("gameScene");
					TitleManager::cutSceneObj->Disable();
				});
			TitleManager::StartCutScene();
		});


	user->actionSubject.Where([](PlayerAction x) {
		return  TitleManager::state == MENU && x.buttonUp == KeyState::pressed;
		}).Select<int>([this](PlayerAction x) {
			return TitleManager::currentBoard->index;
		}).Subscribe([this](int x) {
			switch (x)
			{
			case 0:
				TitleManager::ShowStage();
				SoundSystem::Instance()->PathPlay(L"Resources/Music/buttonclick.mp3", 4);
				ShowInfo();
				break;
			case 1:
				SoundSystem::Instance()->PathPlay(L"Resources/Music/buttonclick.mp3", 4);
				Timer::Delay(1, false, []() {TitleManager::ExitGame(); });
				break;
			case 2:
				TitleManager::ShowCredit();
				TitleManager::state = CREDIT;
				SoundSystem::Instance()->PathPlay(L"Resources/Music/buttonclick.mp3", 4);

				break;
			}
		});
	user->actionSubject.Where([](PlayerAction x) {
			return  TitleManager::state == STAGE;
			}).Select<float>([this](PlayerAction x) {
				return x.ThumbLX;
			}).Subscribe([](float x) {
				if (x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					TitleManager::ticket1->position.x += 30;
					TitleManager::ticket2->position.x += 30;
					TitleManager::ticket3->position.x += 30;
				}
				else if (x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					TitleManager::ticket1->position.x -= 30;
					TitleManager::ticket2->position.x -= 30;
					TitleManager::ticket3->position.x -= 30;
				}

				if (TitleManager::ticket1->position.x < -1000)
				{
					TitleManager::ticket1->position.x = -1000;
					TitleManager::ticket2->position.x = -500;
					TitleManager::ticket3->position.x = -0;
				}
				else if (TitleManager::ticket1->position.x > 1000)
				{
					TitleManager::ticket1->position.x = 1000;
					TitleManager::ticket2->position.x = 1500;
					TitleManager::ticket3->position.x = 2000;
				}
			});

	user->actionSubject.Where([](PlayerAction x) {
		return  TitleManager::state == MENU && x.buttonRight == KeyState::pressing;
		}).Throttle(1).Subscribe([](PlayerAction x) {
			SoundSystem::Instance()->PathPlay(L"Resources/Music/buttonchoice.mp3", 3);
			TitleManager::Next();
		});

		user->actionSubject.Where([](PlayerAction x) {
			return TitleManager::state == MENU && x.buttonLeft == KeyState::pressing;
		}).Throttle(1).Subscribe([](PlayerAction x) {
				SoundSystem::Instance()->PathPlay(L"Resources/Music/buttonchoice.mp3", 3);
				TitleManager::Previous();
		});
}

