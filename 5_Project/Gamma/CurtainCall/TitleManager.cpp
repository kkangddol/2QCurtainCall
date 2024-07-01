#include "GammaEngine.h"
#include "Player.h"
#include "TitleBoard.h"
#include "Information.h"
#include "TitleManager.h"
#include <windows.h>


const vector2 TitleManager::centerScale = vector2(0.8, 0.8);
const vector2 TitleManager::otherScale = vector2(0.5, 0.5);
const vector2 TitleManager::leftPos = vector2(-800, -300);
const vector2 TitleManager::centerPos = vector2(0, -200);
const vector2 TitleManager::rightPos = vector2(800, -300);
TitleBoard* TitleManager::currentBoard;
TitleState TitleManager::state=CURTAIN;
Player* TitleManager::player[2];
GammaEngine::Transform* TitleManager::ticket1;
GammaEngine::Transform* TitleManager::ticket2;
GammaEngine::Transform* TitleManager::ticket3;
GameObject* TitleManager::cutSceneObj = nullptr;
GameObject* TitleManager::creditObj = nullptr;

TitleManager::TitleManager(GameObject* t) :Component(t)
{
	player[0] = nullptr;
	player[1] = nullptr;
}

TitleManager::~TitleManager()
{

}

void TitleManager::RegistPlayer(Player* p)
{
	player[p->id] = p;
}

void TitleManager::UnRegistPlayer(Player* p)
{
	player[p->id] = nullptr;
}

void TitleManager::Next()
{
	currentBoard = currentBoard->next;
	currentBoard->GetComponent<BitmapRenderer>()->order = 3;
	currentBoard->next->GetComponent<BitmapRenderer>()->order = 2;
	currentBoard->previous->GetComponent<BitmapRenderer>()->order = 2.5;

	Tween::Animate(currentBoard->transform->position, PLAYBACK::ONCE_FORWARD, centerPos, EASING::INSINE, 1);
	Tween::Animate(currentBoard->transform->scale, PLAYBACK::ONCE_FORWARD, centerScale, EASING::INSINE, 1);
	Tween::Animate(currentBoard->next->transform->position, PLAYBACK::ONCE_FORWARD, rightPos, EASING::INSINE, 1);
	Tween::Animate(currentBoard->next->transform->scale, PLAYBACK::ONCE_FORWARD, otherScale, EASING::INSINE, 1);
	Tween::Animate(currentBoard->previous->transform->position, PLAYBACK::ONCE_FORWARD, leftPos, EASING::INSINE, 1);
	Tween::Animate(currentBoard->previous->transform->scale, PLAYBACK::ONCE_FORWARD, otherScale, EASING::INSINE, 1);
}

void TitleManager::Previous()
{
	currentBoard = currentBoard->previous;
	currentBoard->GetComponent<BitmapRenderer>()->order = 3;
	currentBoard->previous->GetComponent<BitmapRenderer>()->order = 2;
	currentBoard->next->GetComponent<BitmapRenderer>()->order = 2.5;
	Tween::Animate(currentBoard->transform->position, PLAYBACK::ONCE_FORWARD, centerPos, EASING::INSINE, 1);
	Tween::Animate(currentBoard->transform->scale, PLAYBACK::ONCE_FORWARD, centerScale, EASING::INSINE, 1);
	Tween::Animate(currentBoard->next->transform->position, PLAYBACK::ONCE_FORWARD, rightPos, EASING::INSINE, 1);
	Tween::Animate(currentBoard->next->transform->scale, PLAYBACK::ONCE_FORWARD, otherScale, EASING::INSINE, 1);
	Tween::Animate(currentBoard->previous->transform->position, PLAYBACK::ONCE_FORWARD, leftPos, EASING::INSINE, 1);
	Tween::Animate(currentBoard->previous->transform->scale, PLAYBACK::ONCE_FORWARD, otherScale, EASING::INSINE, 1);
}


void TitleManager::ShowMenu()
{
	Tween::Animate(currentBoard->transform->position.y, PLAYBACK::ONCE_FORWARD, centerPos.y, EASING::INSINE, 1);
	Tween::Animate(currentBoard->next->transform->position.y, PLAYBACK::ONCE_FORWARD, leftPos.y, EASING::INSINE, 1);
	Tween::Animate(currentBoard->previous->transform->position.y, PLAYBACK::ONCE_FORWARD, rightPos.y, EASING::INSINE, 1);

	Tween::Animate(ticket1->position.x, PLAYBACK::ONCE_FORWARD, ticket1->position.x+1500, EASING::INSINE, 1);
	Tween::Animate(ticket2->position.x, PLAYBACK::ONCE_FORWARD, ticket2->position.x + 1500, EASING::INSINE, 1);
	Tween::Animate(ticket3->position.x, PLAYBACK::ONCE_FORWARD, ticket3->position.x + 1500, EASING::INSINE, 1);


}

void TitleManager::ShowStage()
{
	state = STAGE;
	Tween::Animate(currentBoard->transform->position.y, PLAYBACK::ONCE_FORWARD, -900, EASING::INSINE, 1);
	Tween::Animate(currentBoard->next->transform->position.y, PLAYBACK::ONCE_FORWARD, -900, EASING::INSINE, 1);
	Tween::Animate(currentBoard->previous->transform->position.y, PLAYBACK::ONCE_FORWARD, -900, EASING::INSINE, 1);

	Tween::Animate(ticket1->position, PLAYBACK::ONCE_FORWARD, centerPos, EASING::INSINE, 1);
	Tween::Animate(ticket2->position, PLAYBACK::ONCE_FORWARD, centerPos+vector2(500,0), EASING::INSINE, 1);
	Tween::Animate(ticket3->position, PLAYBACK::ONCE_FORWARD, centerPos + vector2(1000, 0), EASING::INSINE, 1);

}

void TitleManager::ShowCredit()
{
	creditObj->Enable();
	creditObj->transform->scale = vector2(0.7f, 0.7f);
	Tween::Animate(creditObj->transform->scale, PLAYBACK::ONCE_BACKWARD, vector2(0.1f, 0.1f), EASING::INEXPO, 0.5f, 0);
}

void TitleManager::ExitCredit()
{
	creditObj->transform->scale = vector2(0.7f, 0.7f);
	Tween::Animate(creditObj->transform->scale, PLAYBACK::ONCE_FORWARD, vector2(0.1f, 0.1f), EASING::INEXPO, 0.5f, 0);
	Timer::Delay(0.5f, false, []() {creditObj->Disable(); });
}
	

void TitleManager::ExitGame()
{
	WindowSystem::Instance()->ShutDown();
}



void TitleManager::StartCutScene()
{
	cutSceneObj->Enable();
	cutSceneObj->GetComponent<Animator>()->Play(L"cutScene", PLAYBACK::ONCE_FORWARD);
}

void TitleManager::Start()
{
	//Tween::Animate(signboard->scale, PLAYBACK::LOOP_PINGPONG, signboard->scale * 1.2, EASING::INSINE, 1);
	signboard->rotation = -10;

	infoX1 = Information::Create(L"x");
	infoX2 = Information::Create(L"x");
	infoArrowLeft = Information::Create(L"left_arrow");
	infoArrowRight = Information::Create(L"right_arrow");
	infoX1->transform->parent = curtainL;
	infoX2->transform->parent = curtainR;
	infoArrowLeft->transform->parent = curtainL;
	infoArrowRight->transform->parent = curtainR;

	infoX1->transform->position = vector2(480,300);
	infoX2->transform->position = vector2(-480, 300);
	infoArrowLeft->transform->position = vector2(380, 300);
	infoArrowRight->transform->position = vector2(-380, 300);
	infoArrowLeft->transform->scale = vector2(0.7, 0.7);
	infoArrowRight->transform->scale = vector2(0.7, 0.7);



	
	Tween::Animate(infoX1->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(infoX2->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	//Tween::Animate(infoArrowLeft->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(0.5, 0.5), INBACK, 1);
	//Tween::Animate(infoArrowRight->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(0.5, 0.5), INBACK, 1);

	Tween::Animate(infoArrowLeft->transform->position.x, PLAYBACK::LOOP_PINGPONG, infoArrowLeft->transform->position.x - 10, INBACK, 1);
	Tween::Animate(infoArrowRight->transform->position.x, PLAYBACK::LOOP_PINGPONG, infoArrowRight->transform->position.x + 10, INBACK, 1);


	infoX1->isEnabled = true;
	infoX2->isEnabled = true;
	infoArrowLeft->isEnabled = true;
	infoArrowRight->isEnabled = true;

	Tween::Animate(explain3->rotation, PLAYBACK::LOOP_PINGPONG, 3, EASING::INSINE, 7, 2);
	Tween::Animate(explain4->rotation, PLAYBACK::LOOP_PINGPONG, 4, EASING::INSINE, 7, 1);
	Tween::Animate(explain1->rotation, PLAYBACK::LOOP_PINGPONG, 5, EASING::INCIRC, 7, 3);
	Tween::Animate(explain2->rotation, PLAYBACK::LOOP_PINGPONG, 6, EASING::INSINE, 7, 5);

	Tween::Animate(signboard->position.y, PLAYBACK::ONCE_BACKWARD, signboard->position.y - 900, EASING::INOUTBOUNCE, 2);
	Tween::Animate(signboard->rotation, PLAYBACK::ONCE_FORWARD, 0, EASING::INOUTBOUNCE, 1, 0.5);




	state = CURTAIN;
	player[0]->state = Player::UI;
	player[1]->state = Player::UI; //타이틀 전용 상태 필요
	titleSubject.Where([this](TitleState x) {
		return x == CURTAIN;
		}).Where([this](TitleState x) {
			return player1Open >= 3 && player2Open >= 3;
			}).Subscribe([this](TitleState x) {
				state = MENU;
				infoX1->isEnabled = false;
				infoX2->isEnabled = false;
				infoArrowLeft->isEnabled = false;
				infoArrowRight->isEnabled = false;
				player[0]->state = Player::IDLE;
				player[1]->state = Player::IDLE;
				Tween::CancelAnimate(signboard->scale);
				Tween::Animate(signboard->position.y, PLAYBACK::ONCE_FORWARD, signboard->position.y - 900, EASING::INSINE, 1);
				Tween::Animate(currentBoard->transform->position, PLAYBACK::ONCE_FORWARD, centerPos, EASING::INSINE, 1);
				Tween::Animate(currentBoard->transform->scale, PLAYBACK::ONCE_FORWARD, centerScale, EASING::INSINE, 1);
				Tween::Animate(currentBoard->next->transform->position, PLAYBACK::ONCE_FORWARD, rightPos, EASING::INSINE, 1);
				Tween::Animate(currentBoard->next->transform->scale, PLAYBACK::ONCE_FORWARD, otherScale, EASING::INSINE, 1);
				Tween::Animate(currentBoard->previous->transform->position, PLAYBACK::ONCE_FORWARD, leftPos, EASING::INSINE, 1);
				Tween::Animate(currentBoard->previous->transform->scale, PLAYBACK::ONCE_FORWARD, otherScale, EASING::INSINE, 1);
			});

			player[0]->actionSubject.Where([this](PlayerAction x) {
				return state == CURTAIN;
				}).Where([](PlayerAction x) {
					return x.buttonX == KeyState::pressing;
					}).Throttle(1).Subscribe([this](auto x) {
						if (player1Open < 3)
						{
							player1Open++;
							Tween::Animate(curtainL->position.x, PLAYBACK::ONCE_FORWARD, curtainL->position.x - 300, EASING::INOUTBOUNCE, 0.3);
							

							Tween::Animate(curtainL->rotation, PLAYBACK::ONCE_PINGPONG, -5, EASING::INCUBIC, 0.1);
							

							titleSubject.OnNext(state);
							Tween::Animate(signboard->position.y, PLAYBACK::ONCE_PINGPONG, signboard->position.y - 10, EASING::INOUTBOUNCE, 0.3,0.1);
							Tween::Animate(signboard->rotation, PLAYBACK::ONCE_PINGPONG, 2, EASING::INOUTBOUNCE, 0.4, 0.1);
						}
					});
			player[1]->actionSubject.Where([this](PlayerAction x) {
						return state == CURTAIN;
						}).Where([](PlayerAction x) {
							return x.buttonX == KeyState::pressing;
							}).Throttle(1).Subscribe([this](auto x) {
								if (player2Open < 3)
								{
									player2Open++;
									
									Tween::Animate(curtainR->position.x, PLAYBACK::ONCE_FORWARD, curtainR->position.x + 300, EASING::INOUTBOUNCE, 0.3);

									Tween::Animate(curtainR->rotation, PLAYBACK::ONCE_PINGPONG, 5, EASING::INCUBIC, 0.1);


									titleSubject.OnNext(state);
									Tween::Animate(signboard->position.y, PLAYBACK::ONCE_PINGPONG, signboard->position.y - 10, EASING::INOUTBOUNCE, 0.3, 0.1);
									Tween::Animate(signboard->rotation, PLAYBACK::ONCE_PINGPONG, 2, EASING::INOUTBOUNCE, 0.4, 0.1);
								}
								});
				

}

void TitleManager::Update()
{
	if (Input::GetKeyDown(VK_F1))
	{
		Debug::SetDebugMode();
	}
}

