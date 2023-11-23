#pragma once
#include "GRX.h"
using namespace GammaEngine;

/// <summary>
/// 전체적인 타이틀 시스템을 관리하는 GameManager
/// </summary>

class Player;

enum TitleState
{
	CURTAIN,
	MENU,
	STAGE,
	CREDIT,
	CUTSCENE
};
class TitleBoard;

class TitleManager : public GammaEngine::Component
{
public:
	TitleManager(GameObject*);
	virtual ~TitleManager();
	static void RegistPlayer(Player*);
	static void UnRegistPlayer(Player* p);
	static void Next();
	static void Previous();
	static void ShowStage();
	static void ShowMenu();
	static void ShowCredit();
	static void ExitCredit();
	static void ExitGame();
	static void StartCutScene();
	virtual void Start() override;
	virtual void Update() override;
public:
	static Player* player[2];
	static TitleState state;
	Subject<TitleState> titleSubject;
	GammaEngine::Transform* curtainL;
	GammaEngine::Transform* curtainR;
	GammaEngine::Transform* signboard;
	static GammaEngine::Transform* ticket1;
	static GammaEngine::Transform* ticket2;
	static GammaEngine::Transform* ticket3;
	GammaEngine::Transform* explain1;
	GammaEngine::Transform* explain2;
	GammaEngine::Transform* explain3;
	GammaEngine::Transform* explain4;
	static TitleBoard* currentBoard;

	const static vector2 centerScale;
	const static vector2 otherScale;
	const static vector2 leftPos;
	const static vector2 centerPos;
	const static vector2 rightPos;

	GameObject* infoX1;
	GameObject* infoX2;
	GameObject* infoArrowLeft;
	GameObject* infoArrowRight;
	GameObject* infoOpenText;
	TweenData* signbordHandler;
	static GameObject* cutSceneObj;
	static GameObject* creditObj;
private:
	int player1Open = 0;
	int player2Open = 0;

};

