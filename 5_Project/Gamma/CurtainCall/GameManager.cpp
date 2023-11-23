#include <fstream>
#include <sstream>
#include <locale>
#include "GammaEngine.h"
#include "Player.h"
#include "GameEvent.h"
#include "Manageable.h"
#include "MusicControlBox.h"
#include "GameManager.h"
#include "IngameUI.h"

using namespace GammaEngine;

std::wstring s2w(const std::string& var)
{
	static std::locale loc("");
	auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
	return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).from_bytes(var);
}


Player* GameManager::player[2];
std::vector<Manageable*> GameManager::reactantList_;
bool GameManager::isPaused_ = false;
MusicControlBox* GameManager::musicControl = nullptr;

GameManager::GameManager(GameObject* obj)
	: Component(obj),
	life_(3),
	playTime_(0),
	isGameOver_(false),
	stageIndex_(0),
	eventIndex_(0),
	eventDeadLine_(0),
	currentEvent_(nullptr),
	waitTime_(20),
	checkInterval_(0.1f),
	interval_(0),
	textObj_(nullptr),
	timerObj_(nullptr),
	stampObj_(nullptr)
{
	player[0] = nullptr;
	player[1] = nullptr;

	stageEvents_.push_back(std::vector<EventData>());
	stageEvents_.push_back(std::vector<EventData>());
	stageEvents_.push_back(std::vector<EventData>());

	//setlocale(LC_ALL, "ko-KR");

	std::ifstream fin("Map\\event01.txt");
	fin.imbue(std::locale("kor"));
	if (fin.fail())
	{
		return;
	}

	int pNumber;
	std::string pScript;
	float pTimeLimit;
	int pArchIndex, pArchDown, pArchUp;
	int pSound;
	int pRainRatio;
	int pSkyIndex, pSkyAppear;
	int pActorDown, pActorUp, pActressDown, pActressUp;

	while (fin >> pNumber >> pScript >> pTimeLimit >> pArchIndex >> pArchDown >> pArchUp >> pSound >> pRainRatio >> pSkyIndex >> pSkyAppear >>
		pActorDown >> pActorUp >> pActressDown >> pActressUp)
	{
		stageEvents_[0].push_back(EventData(pNumber, pScript, pTimeLimit, pArchIndex, pArchDown, pArchUp,
			pSound, pRainRatio, pSkyIndex, pSkyAppear,
			pActorDown, pActorUp, pActressDown, pActressUp));
	}

	fin.close();

	keyInput_.push_back(false);
	keyInput_.push_back(false);
	keyInput_.push_back(false);
	keyInput_.push_back(false);
	keyInput_.push_back(false);
	keyInput_.push_back(false);
}

void GameManager::Start()
{
	SoundSystem::Instance()->PathPlay(L"Resources/Music/tick_tock.wav", 6);
	Timer::Delay(20, false, []() {SoundSystem::Instance()->PathStop(L"Resources/Music/tick_tock.wav", 6); });
	StartEvent();
}

void GameManager::RegistPlayer(Player* p)
{
	player[p->id] = p;
}

void GameManager::UnRegistPlayer(Player* p)
{
	player[p->id] = nullptr;
}

void GameManager::RegistManageable(Manageable* manageable)
{
	reactantList_.push_back(manageable);
}

bool GameManager::IsPaused()
{
	return isPaused_;
}

void GameManager::SetMusicControl(MusicControlBox* box)
{
	musicControl = box;
}

void GameManager::GameStart()
{
	//게임이 시작될 때 자신이 어느시점에 GameEnd를 호출할 지 알게 된다
	handler = Timer::Delay(endTime, false, [this]() {
		GameEnd();
		});

	for (auto iter : eventList)
	{
		TimerHandler* eventTimer = Timer::Delay(iter->stratTime, false, [this,iter, eventTimer]() {
		iter->EventStart(); 
		eventHandlerList.erase(remove(eventHandlerList.begin(), eventHandlerList.end(),
			eventTimer), eventHandlerList.end());
		});
		eventHandlerList.push_back(eventTimer);
	}
}

void GameManager::Update()
{
	if (Input::GetKeyDown(VK_F1))
	{
		Debug::SetDebugMode();
	}

	TimeFlow();

	CommonInput();

	if (0 < waitTime_)
	{
		return;
	}

	if (isGameOver_)
	{
		// 클리어 메뉴
		ControlUI(clearUIs_[0]->GetComponent<IngameUI>());

		return;
	}

	if (IsStageClear())
	{
		// 스테이지 클리어!
		// 결과 UI 띄워주자
		isGameOver_ = true;
		ClearIn();
		clearUIs_[0]->GetComponent<IngameUI>()->StartClear(life_);
		FireFanfare();
		PauseGame();
		return;
	}

	if (life_ <= 0)
	{
		// 스테이지 실패!
		// 결과 UI 띄워주자
		isGameOver_ = true;
		ClearIn();
		clearUIs_[0]->GetComponent<IngameUI>()->StartClear(life_);
		PauseGame();
		return;
	}

	if (isPaused_)
	{
		ControlUI(pauseUIs_[0]->GetComponent<IngameUI>());
		return;
	}

	if (interval_ <= 0 && currentEvent_ != nullptr)
	{
		interval_ = checkInterval_;

		if (IsEventClear())
		{
			// 이벤트 클리어!
			SoundSystem::Instance()->PathPlay(L"Resources/Music/stamp.ogg", 25);
			SoundSystem::Instance()->SetVolume(25, 1.0f);
			stampObj_->transform->scale = vector2(2, 2);
			stampObj_->GetComponent<BitmapRenderer>()->isEnabled = true;
			Tween::Animate(stampObj_->transform->scale, PLAYBACK::ONCE_FORWARD, vector2(1, 1), EASING::INOUTEXPO, 0.5f, 0.15f);
			waitTime_ = 3;
			currentEvent_ = nullptr;
			return;
		}
	}

	player[0]->FailEnd();
	player[1]->FailEnd();

	if (currentEvent_ != nullptr && eventDeadLine_ <= 0)
	{
		// 이벤트 실패!
		// 목숨깎고
		// 3초뒤에 새로운 이벤트 설정!
		player[0]->Fail();
		player[1]->Fail();

		ReduceLife();
		waitTime_ = 3;
		currentEvent_ = nullptr;

		return;
	}

	if (currentEvent_ == nullptr)
	{
		stampObj_->GetComponent<BitmapRenderer>()->isEnabled = false;
		StartEvent();
	}
}

void GameManager::GameEnd()
{
	// TimerHandler의 벡터가 0이 된다
	eventHandlerList.clear();
}

void GameManager::GameForceEnd()
{
	// 강제종료 했을 떄 Timer와 handler를 모두 초기화한다
	for (auto iter : eventHandlerList)
	{
		Timer::Cancel(iter);
	}
	eventHandlerList.clear();
	Timer::Cancel(handler);
	handler = nullptr;
}

void GameManager::SetTextObj(GameObject* textObj)
{
	textObj_ = textObj;
}

void GameManager::SetTimerObj(GameObject* timerObj)
{
	timerObj_ = timerObj;
}

void GameManager::SetStampObj(GameObject* stampObj)
{
	stampObj_ = stampObj;
}

void GameManager::SetLifeObj(GameObject* lifeObj)
{
	lifeObj_ = lifeObj;
}

void GameManager::SetFanfare(GameObject* fanfareObj)
{
	fanfareObj_ = fanfareObj;
}

void GameManager::SetPauseUI(std::vector<GameObject*>& pauseUI)
{
	pauseUIs_ = pauseUI;
}

void GameManager::SetClearUI(std::vector<GameObject*>& clearUI)
{
	clearUIs_ = clearUI;
}

void GameManager::PauseGame()
{
	Time::SetTimeScale(0);
	isPaused_ = true;
	player[0]->Pause();
	player[1]->Pause();
}

void GameManager::ResumeGame()
{
	Time::SetTimeScale(1);
	PauseOut();
	isPaused_ = false;
	player[0]->Resume();
	player[1]->Resume();
}

void GameManager::ControlUI(IngameUI* ingameUI)
{
	if (keyInput_[(int)InputKey::LEFT])
	{
		ingameUI->OnLeftInput();
	}

	if (keyInput_[(int)InputKey::RIGHT])
	{
		ingameUI->OnRighttInput();
	}

	if (keyInput_[(int)InputKey::A])
	{
		ingameUI->OnSelectInput();
	}
}

void GameManager::PauseIn()
{
	for (auto& obj : pauseUIs_)
	{
		obj->Enable();
	}
}

void GameManager::PauseOut()
{
	for (auto& obj : pauseUIs_)
	{
		obj->Disable();
	}
}

void GameManager::ClearIn()
{
	for (auto& obj : clearUIs_)
	{
		obj->Enable();
	}
}

void GameManager::TimeFlow()
{
	float deltaTime = GammaEngine::Time::deltaTime;
	playTime_ += deltaTime;

	if (0 < waitTime_)
	{
		waitTime_ -= deltaTime;

		if (waitTime_ <= 0)
		{
			waitTime_ = 0;
		}
	}

	if (0 < interval_)
	{
		interval_ -= deltaTime;
	}

	if (0 < eventDeadLine_)
	{
		eventDeadLine_ -= deltaTime;

		if (eventDeadLine_ <= 0)
		{
			eventDeadLine_ = 0;
		}
	}

	if (0 < menuInterval_)
	{
		menuInterval_ -= Time::GetForceDelta();

		if (menuInterval_ <= 0)
		{
			menuInterval_ = 0;
		}
	}

	if (timerObj_ != nullptr)
	{
		std::wstring str;
// 		std::ostringstream out;
// 		out.precision(2);
// 		out << std::fixed << eventDeadLine_;
// 		std::string temp = out.str();
// 		str.assign(temp.begin(), temp.end());
		str.append(std::to_wstring((int)eventDeadLine_));
		timerObj_->GetComponent<TextRenderer>()->SetText(str);
	}
}

bool GameManager::IsStageClear()
{
	return (stageEvents_[stageIndex_].size() <= eventIndex_) && (0 < life_) && (currentEvent_ == nullptr);
}

void GameManager::StartEvent()
{
	if (currentEvent_ != nullptr)
	{
		return;
	}

	if (stageEvents_[stageIndex_].size() <= eventIndex_)
	{
		return;
	}

	currentEvent_ = &stageEvents_[stageIndex_][eventIndex_];
	eventDeadLine_ = currentEvent_->timeLimit;
	std::wstring temp = s2w(currentEvent_->script);
	textObj_->GetComponent<TextAnimationRenderer>()->SetText(temp);
	textObj_->GetComponent<TextAnimator>()->Play();

	if (currentEvent_->sound != -1)
	{
		musicControl->InitSuccess();
	}

	++eventIndex_;
}

bool GameManager::IsEventClear()
{
	bool result = true;

	for (auto& reactant : reactantList_)
	{
		result *= reactant->CheckStatus(currentEvent_->archIndex, currentEvent_->archDown, currentEvent_->archUp,
			currentEvent_->sound, currentEvent_->rainRatio, currentEvent_->skyIndex, currentEvent_->skyAppear,
			currentEvent_->actorDown, currentEvent_->actorUp, currentEvent_->actressDown, currentEvent_->actressUp);
	}

	return result;
}

void GameManager::ReduceLife()
{
	--life_;
	std::wstring temp = L"x";
	temp.append(std::to_wstring(life_));
	lifeObj_->GetComponent<TextRenderer>()->SetText(temp);
// 	float& lifeAlpha = lifeObjs_[life_]->GetComponent<BitmapRenderer>()->material->brush.w;
// 	Tween::Animate(lifeObjs_[life_]->transform->position, PLAYBACK::ONCE_FORWARD, lifeObjs_[life_]->transform->position + vector2(0, -500), EASING::INBACK, 1.0f, 0.1f);
// 	Tween::Animate(lifeAlpha, PLAYBACK::ONCE_FORWARD, 0, EASING::INOUTEXPO, 1.0f, 0.1f);
}

void GameManager::FireFanfare()
{
	for (auto& emitter : *(fanfareObj_->GetComponent<ParticleSystem>()->GetEmitters()))
	{
		emitter->SetActive(true);
	}
	SoundSystem::Instance()->PathPlay(L"Resources/Music/fanfare.ogg", 5);

}

void GameManager::CommonInput()
{
	for (int i = 0; i < (int)InputKey::Count; ++i)
	{
		keyInput_[i] = false;
	}

	if (0 < menuInterval_)
	{
		return;
	}

	if (isGameOver_)
	{
		if (GamepadManager::GetPad(0)->GetWbuttonDown(aButton_) ||
			GamepadManager::GetPad(1)->GetWbuttonDown(aButton_))
		{
			keyInput_[(int)InputKey::A] = true;
			menuInterval_ = MENUINTERVAL_;
		}

		if (GamepadManager::GetPad(0)->GetWbuttonDown(bButton_) ||
			GamepadManager::GetPad(1)->GetWbuttonDown(bButton_))
		{
			keyInput_[(int)InputKey::B] = true;
			menuInterval_ = MENUINTERVAL_;
		}

		if (GamepadManager::GetPad(0)->GetStickValue(0) > DEADZONE_ * 2 ||
			GamepadManager::GetPad(1)->GetStickValue(0) > DEADZONE_ * 2)
		{
			keyInput_[(int)InputKey::RIGHT] = true;
			menuInterval_ = MENUINTERVAL_;
		}

		if (GamepadManager::GetPad(0)->GetStickValue(0) < -DEADZONE_ * 2 ||
			GamepadManager::GetPad(1)->GetStickValue(0) < -DEADZONE_ * 2)
		{
			keyInput_[(int)InputKey::LEFT] = true;
			menuInterval_ = MENUINTERVAL_;
		}

		if (GamepadManager::GetPad(0)->GetStickValue(1) > DEADZONE_ * 2 ||
			GamepadManager::GetPad(1)->GetStickValue(1) > DEADZONE_ * 2)
		{
			keyInput_[(int)InputKey::UP] = true;
			menuInterval_ = MENUINTERVAL_;
		}

		if (GamepadManager::GetPad(0)->GetStickValue(1) < -DEADZONE_ * 2 ||
			GamepadManager::GetPad(1)->GetStickValue(1) < -DEADZONE_ * 2)
		{
			keyInput_[(int)InputKey::DOWN] = true;
			menuInterval_ = MENUINTERVAL_;
		}
	}

	if (isPaused_ && menuOwner_ != -1 && !isGameOver_)
	{
		if (GamepadManager::GetPad(menuOwner_)->GetWbuttonDown(menuButton_))
		{
			ResumeGame();
			FreeOwner();
			menuInterval_ = MENUINTERVAL_;
			return;
		}
	}

	if (GamepadManager::GetPad(0)->GetWbuttonDown(menuButton_) && !isPaused_)
	{
		menuOwner_ = 0;
		PauseGame();
		PauseIn();
		menuInterval_ = MENUINTERVAL_;
	}
	else if (GamepadManager::GetPad(1)->GetWbuttonDown(menuButton_) && !isPaused_)
	{
		menuOwner_ = 1;
		PauseGame();
		PauseIn();
		menuInterval_ = MENUINTERVAL_;
	}

	if (menuOwner_ == -1)
	{
		return;
	}

	if (GamepadManager::GetPad(menuOwner_)->GetWbuttonDown(aButton_))
	{
		keyInput_[(int)InputKey::A] = true;
		menuInterval_ = MENUINTERVAL_;
	}

	if (GamepadManager::GetPad(menuOwner_)->GetWbuttonDown(bButton_))
	{
		keyInput_[(int)InputKey::B] = true;
		menuInterval_ = MENUINTERVAL_;
	}

	if (GamepadManager::GetPad(menuOwner_)->GetStickValue(0) > DEADZONE_ * 2)
	{
		keyInput_[(int)InputKey::RIGHT] = true;
		menuInterval_ = MENUINTERVAL_;
	}

	if (GamepadManager::GetPad(menuOwner_)->GetStickValue(0) < -DEADZONE_ * 2)
	{
		keyInput_[(int)InputKey::LEFT] = true;
		menuInterval_ = MENUINTERVAL_;
	}

	if (GamepadManager::GetPad(menuOwner_)->GetStickValue(1) > DEADZONE_ * 2)
	{
		keyInput_[(int)InputKey::UP] = true;
		menuInterval_ = MENUINTERVAL_;
	}

	if (GamepadManager::GetPad(menuOwner_)->GetStickValue(1) < -DEADZONE_ * 2)
	{
		keyInput_[(int)InputKey::DOWN] = true;
		menuInterval_ = MENUINTERVAL_;
	}
}

void GameManager::FreeOwner()
{
	menuOwner_ = -1;
}
