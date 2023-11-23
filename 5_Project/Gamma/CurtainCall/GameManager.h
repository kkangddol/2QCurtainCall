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
/// ��ü���� �ΰ��� �ý����� �����ϴ� GameManager
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
	static bool isPaused_;							// ���� �Ͻ�����
	static MusicControlBox* musicControl;

public:
	void GameStart();
	void GameEnd();
	void GameForceEnd();
	//�����̳� �̺�Ʈ�� ������ �ð�
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
	int life_;								// ���� ����
	float playTime_;						// �÷��� Ÿ��
	bool isGameOver_;						// ���� ����
	int stageIndex_;						// �������� �ε���
	int eventIndex_;						// �̺�Ʈ �ε���
	float eventDeadLine_;					// �̺�Ʈ �������
	float waitTime_;						// ��� Update�� ���� �ʰ� ��ٸ� �ð� (����� �����ϰ� ��� ���ҽ�Ŵ)
	float checkInterval_;					// �̺�Ʈ Ŭ��� üũ�� ����
	float interval_;						// ����� �����ϰ� ��� ���ҽ�Ŵ
	EventData* currentEvent_;				// ���� �̺�Ʈ�� �ּ�
	std::vector<std::vector<EventData>> stageEvents_;


	// UI ���� ���
private:
	GameObject* textObj_;					// ��ũ��Ʈ ������Ʈ
	GameObject* timerObj_;					// ���� �ð� Ÿ�̸� ������Ʈ
	GameObject* stampObj_;					// ������ ������Ʈ
	GameObject* lifeObj_;		// ������ ������Ʈ
	GameObject* fanfareObj_;				// ������ ������Ʈ
	std::vector<GameObject*> pauseUIs_;		// �Ͻ����� UI ������Ʈ��
	std::vector<GameObject*> clearUIs_;		// ���ӿ���,Ŭ���� UI ������Ʈ��


public:
	void FreeOwner();

	// �޴� ��ǲ ����
private:
	std::vector<bool> keyInput_;			// �޴� Ű ��ǲ üũ�ϱ� ����
	int menuOwner_;							// �޴� Ű ���� ��� �����ΰ�
	WORD menuButton_ = XINPUT_GAMEPAD_START;
	WORD aButton_ = XINPUT_GAMEPAD_A;
	WORD bButton_ = XINPUT_GAMEPAD_B;
	const float DEADZONE_ = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	float MENUINTERVAL_ = 0.2f;
	float menuInterval_;
};
