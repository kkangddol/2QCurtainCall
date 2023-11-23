#pragma once
#include <vector>
#include <string>

using namespace GammaEngine;

struct EventData
{
	EventData(int pNumber, std::string pScript, float pTimeLimit, int pArchIndex, int pArchDown, int pArchUp,
		int pSound, int pRainRatio, int pSkyIndex, int pSkyAppear,
		int pActorDown, int pActorUp, int pActressDown, int pActressUp)
		: number(pNumber), script(pScript), timeLimit(pTimeLimit),
		archIndex(pArchIndex), archDown(pArchDown), archUp(pArchUp),
		sound(pSound), rainRatio(pRainRatio), skyIndex(pSkyIndex), skyAppear(pSkyAppear),
		actorDown(pActorDown), actorUp(pActorUp), actressDown(pActressDown), actressUp(pActressUp)
	{

	}

	int number;
	std::string script;
	float timeLimit;
	int archIndex;
	int archDown;
	int archUp;
	int sound;
	int rainRatio;
	int skyIndex;
	int skyAppear;
	int actorDown;
	int actorUp;
	int actressDown;
	int actressUp;
};

class Player;
class Manageable;
class GameEvent;
class IngameUI;
class MusicControlBox;
class GameEvent;

/// <summary>
/// 전체적인 인게임 시스템을 관리하는 GameManager
/// </summary>
class GameManager : public GammaEngine::Component
{
public:
	GameManager(GammaEngine::GameObject* obj);

	virtual void Start() override;
	virtual void Update() override;

public:
	static void RegistPlayer(Player*);
	static void UnRegistPlayer(Player* p);
	static void RegistManageable(Manageable* manageable);
	static bool IsPaused();
	static void SetMusicControl(MusicControlBox* box);

public:
	static Player* player[2];
	static std::vector<Manageable*> reactantList_;
	static bool isPaused_;							// 게임 일시정지
	static MusicControlBox* musicControl;

public:
	void GameStart();
	void GameEnd();
	void GameForceEnd();
	//게임이나 이벤트가 끝나는 시간
	float endTime;
	std::vector<GameEvent*> eventList;
	std::vector<GammaEngine::TimerHandler*> eventHandlerList;
	GammaEngine::TimerHandler* handler;

public:
	void SetTextObj(GameObject* textObj);
	void SetTimerObj(GameObject* timerObj);
	void SetStampObj(GameObject* stampObj);
	void SetLifeObj(GameObject* lifeObj);
	void SetFanfare(GameObject* fanfareObj);
	void SetPauseUI(std::vector<GameObject*>& pauseUI);
	void SetClearUI(std::vector<GameObject*>& clearUI);
	void PauseGame();
	void ResumeGame();
	void ControlUI(IngameUI* ingameUI);
	void PauseIn();
	void PauseOut();
	void ClearIn();

private:
	enum class InputKey
	{
		LEFT,
		UP,
		RIGHT,
		DOWN,
		A,
		B,
		Count
	};

	void TimeFlow();
	bool IsStageClear();
	void StartEvent();
	bool IsEventClear();
	void ReduceLife();
	void FireFanfare();
	void CommonInput();

private:
	int life_;								// 남은 생명
	float playTime_;						// 플레이 타임
	bool isGameOver_;						// 게임 오버
	int stageIndex_;						// 스테이지 인덱스
	int eventIndex_;						// 이벤트 인덱스
	float eventDeadLine_;					// 이벤트 데드라인
	float waitTime_;						// 잠시 Update를 하지 않고 기다릴 시간 (여기다 대입하고 계속 감소시킴)
	float checkInterval_;					// 이벤트 클리어를 체크할 간격
	float interval_;						// 여기다 대입하고 계속 감소시킴
	EventData* currentEvent_;				// 현재 이벤트의 주소
	std::vector<std::vector<EventData>> stageEvents_;


	// UI 관련 멤버
private:
	GameObject* textObj_;					// 스크립트 오브젝트
	GameObject* timerObj_;					// 남은 시간 타이머 오브젝트
	GameObject* stampObj_;					// 스탬프 오브젝트
	GameObject* lifeObj_;		// 라이프 오브젝트
	GameObject* fanfareObj_;				// 빵빠레 오브젝트
	std::vector<GameObject*> pauseUIs_;		// 일시정지 UI 오브젝트들
	std::vector<GameObject*> clearUIs_;		// 게임오버,클리어 UI 오브젝트들


public:
	void FreeOwner();

	// 메뉴 인풋 관련
private:
	std::vector<bool> keyInput_;			// 메뉴 키 인풋 체크하기 위함
	int menuOwner_;							// 메뉴 키 누른 사람 누구인가
	WORD menuButton_ = XINPUT_GAMEPAD_START;
	WORD aButton_ = XINPUT_GAMEPAD_A;
	WORD bButton_ = XINPUT_GAMEPAD_B;
	const float DEADZONE_ = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	float MENUINTERVAL_ = 0.2f;
	float menuInterval_;
};
