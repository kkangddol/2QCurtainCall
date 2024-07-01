#include "GammaEngine.h"
#include "IngameBox.h"
#include "WorkSpace.h"
#include "TitleBox.h"
#include "Trigger.h"
#include "Reactant.h"
#include "ArchDisk.h"
#include "Arch.h"
#include "Information.h"
#include "MapDataLoader.h"
#include "GameManager.h"
#include "Player.h"
#include "TitleManager.h"

using namespace GammaEngine;

void GameSceneInit()
{
	MapDataLoader* mapLoader = new MapDataLoader();

	Scene* gameScene = SceneManager::GetCurrentScene();
	GameObject* camera = Ingame::CreateCamera(gameScene);
	//GameObject* startLight = Ingame::CreateBackgroundLight(gameScene);

	GameObject* gameManagerObj = gameScene->CreateObject();
	gameManagerObj->AddComponent<GameManager>();
	GameManager* gameMgr = gameManagerObj->GetComponent<GameManager>();

	SoundSystem::Instance()->CreateReverbSound("Resources/Music/fanfare.ogg", false);
	SoundSystem::Instance()->CreateReverbSound("Resources/Music/stamp.ogg", false);
	SoundSystem::Instance()->CreateReverbSound("Resources/Music/tick_tock.wav", true);
	SoundSystem::Instance()->CreateReverbSound("Resources/Music/bird.ogg", false);

	GameObject* textObj = Ingame::CreateScriptObj(gameScene,Screen::width / 2, 100);
	gameMgr->SetTextObj(textObj);

	GameObject* timerObj = Ingame::CreateTimerObj(gameScene, Screen::width / 2 - 500, 75);
	gameMgr->SetTimerObj(timerObj);

	GameObject* stampObj = Ingame::CreateStampObj(gameScene, Screen::width / 2 + 400, 115);
	gameMgr->SetStampObj(stampObj);

	GameObject* lifeObj = Ingame::CreateLifeObj(gameScene, Screen::width / 2 - 800, 100);
	gameMgr->SetLifeObj(lifeObj);

	GameObject* fanfare = Ingame::CreateFanfareParticle(gameScene, 0, 500);
	gameMgr->SetFanfare(fanfare);

#pragma region pauseUI
	GameObject* pauseBackBoard = Ingame::CreatePauseUI(gameScene, Screen::width / 2, Screen::height / 2);
	GameObject* pauseHomeBtn = Ingame::CreateHomeBtn(gameScene, -200, 0);
	GameObject* pauseRestartBtn = Ingame::CreateRestartBtn(gameScene, 0, 0);
	GameObject* pauseOptionBtn = Ingame::CreateOptionBtn(gameScene, 200, 0);
	GameObject* pauseIcon = Ingame::CreatePauseIcon(gameScene, Screen::width - 50, 50);
	pauseHomeBtn->transform->parent = pauseBackBoard->transform;
	pauseRestartBtn->transform->parent = pauseBackBoard->transform;
	pauseOptionBtn->transform->parent = pauseBackBoard->transform;

	std::vector<GameObject*> pauseUIs;
	pauseUIs.push_back(pauseBackBoard);
	pauseUIs.push_back(pauseHomeBtn);
	pauseUIs.push_back(pauseRestartBtn);
	pauseUIs.push_back(pauseOptionBtn);
	pauseUIs.push_back(pauseIcon);

	gameMgr->SetPauseUI(pauseUIs);
#pragma endregion pauseUI

#pragma region ClearUI
	GameObject* clearBackBoard = Ingame::CreateClearUI(gameScene, Screen::width / 2, Screen::height / 2);
	GameObject* clearHomeBtn = Ingame::CreateHomeBtn(gameScene, -200, 150);
	GameObject* clearRestartBtn = Ingame::CreateRestartBtn(gameScene, 0, 150);
	GameObject* clearContinueBtn = Ingame::CreateContinueBtn(gameScene, 200, 150);
	clearHomeBtn->transform->parent = clearBackBoard->transform;
	clearRestartBtn->transform->parent = clearBackBoard->transform;
	clearContinueBtn->transform->parent = clearBackBoard->transform;

	std::vector<GameObject*> clearUIs;
	clearUIs.push_back(clearBackBoard);
	clearUIs.push_back(clearHomeBtn);
	clearUIs.push_back(clearRestartBtn);
	clearUIs.push_back(clearContinueBtn);

	gameMgr->SetClearUI(clearUIs);
#pragma endregion ClearUI

	GameObject* background = Ingame::CreateBackground(gameScene, 0, 0);
	GameObject* stage = Ingame::CreateStage(gameScene, 0, 30);
	GameObject* platform1 = Ingame::CreateBlock(gameScene, 0, 950, 4000, 100);
	GameObject* platform2 = Ingame::CreateBlock(gameScene, 50, 460, 2120, 50);
	GameObject* platformCeiling = Ingame::CreateBlock(gameScene, 0, -270, 4000, 50);
	GameObject* LeftWall = Ingame::CreateWall(gameScene, -2050, 0, 100, 4000);
	GameObject* RightWall = Ingame::CreateWall(gameScene, 2050, 0, 100, 4000);

 	GameObject* player1 = Ingame::CreatePlayer(gameScene, -200, 800, 0);
 	GameObject* player2 = Ingame::CreatePlayer(gameScene, 200, 800, 1);
	
	//GameObject* light = Ingame::CreateSpotLight(gameScene, -300, -240);
	//GameObject* text = Ingame::CreateTextAnimation(gameScene);
	GameObject* ingameBgm = Ingame::CreateIngameBGM(gameScene);
	ingameBgm->GetComponent<AudioSource>()->Stop(0);

	Ingame::CreateFromData(gameScene, mapLoader);
}

void TitleSceneInit()
{

	Scene* titleScene = SceneManager::GetCurrentScene();
	GameObject* camera = Title::CreateCamera(titleScene);
	//GameObject* light = Title::CreateBackgroundLight(titleScene, 0, 0);
	GameObject* background = Title::CreateBackground(titleScene, 0, 0);
	GameObject* platform1 = Ingame::CreateBlock(titleScene, 0, 540, 1920, 100);
	GameObject* LeftWall = Ingame::CreateBlock(titleScene, -980, 0, 40, 4000);
	GameObject* RightWall = Ingame::CreateBlock(titleScene, 980, 0, 40, 4000);
	GameObject* player1 = Ingame::CreatePlayer(titleScene, -200, 0, 0);
	GameObject* player2 = Ingame::CreatePlayer(titleScene, 200, 0, 1);
	GameObject* manager = Title::CreateManager(titleScene, 0, 0);
	GameObject* control = Title::CreateControlBox(titleScene, 0, 400);
	GameObject* titleBgm = Ingame::CreateTitleBGM(titleScene);
	SoundSystem::Instance()->CreateReverbSound("Resources/Music/buttonchoice.mp3", false);
	SoundSystem::Instance()->CreateReverbSound("Resources/Music/buttonclick.mp3", false);
	//SceneManager::LoadScene("gameScene");

	GameObject* cutScene = titleScene->CreateObject();
	cutScene->AddComponent<BitmapRenderer>();
	BitmapRenderer* csBitmap = cutScene->GetComponent<BitmapRenderer>();
	csBitmap->LoadBitmapImage(L"Resources\\CutScene\\all_0.png");
	csBitmap->order = 20;
	cutScene->AddComponent<Animator>();
	Animator* csAnimator = cutScene->GetComponent<Animator>();
	Animation* anim = new Animation();
	anim->SetFPS(7);
	std::wstring path;
	for (int i = 0; i < 180; ++i)
	{
		path = L"Resources\\CutScene\\all_";
		path.append(std::to_wstring(i));
		path.append(L".png");
		anim->AddFrame(path);
	}
	csAnimator->AddAnimation(L"cutScene", anim);
	cutScene->Disable();
	manager->GetComponent<TitleManager>()->cutSceneObj = cutScene;

	GameObject* credit = titleScene->CreateObject();
	credit->AddComponent<BitmapRenderer>();
	BitmapRenderer* creditBitmap = credit->GetComponent<BitmapRenderer>();
	creditBitmap->LoadBitmapImage(L"Resources\\UI\\credit.png");
	creditBitmap->order = 19;
	credit->Disable();
	manager->GetComponent<TitleManager>()->creditObj = credit;

}

WorkSpace::WorkSpace()
{

	Information();
	
	SpineModel::Initialize();

	SpineModel::Create("player1_front", "Resources/Character/Character1/char_main_start.atlas", "Resources/Character/Character1/char_main_start.json");
	SpineModel::Create("player1_back", "Resources/Character/Character1/char_back.atlas", "Resources/Character/Character1/char_back.json");
	SpineModel::Create("player2_front", "Resources/Character/Character2/char_main_start.atlas", "Resources/Character/Character2/char_main_start.json");
	SpineModel::Create("player2_back", "Resources/Character/Character2/char_back.atlas", "Resources/Character/Character2/char_back.json");

	SpineModel::Create("actorA", "Resources/Character/actorA/actorA.atlas", "Resources/Character/actorA/actorA.json");
	SpineModel::Create("actorB", "Resources/Character/actorB/actorB.atlas", "Resources/Character/actorB/actorB.json");
	


	//Create Scene
	Scene* titleScene = SceneManager::CreateScene("titleScene");
	titleScene->SetInitializer(TitleSceneInit);

	Scene* gameScene = SceneManager::CreateScene("gameScene");
	gameScene->SetInitializer(GameSceneInit);

	SceneManager::LoadScene("titleScene");
}
