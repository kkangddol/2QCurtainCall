#include "MapEditorScene.h"

#include "SceneSystem.h"

#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"

#include "MainCamera.h"

#include "SpriteRenderer.h"
#include "UISpriteRenderer.h"
#include "Dragable.h"
#include "UIManager.h"
#include "EditorManager.h"

#include "Button.h"

#define SCENENAME "MapEditorScene"

void MapEditorScene::Initialize()
{
	Scene& mapEditorScene = SceneSystem::Instance().CreateScene(SCENENAME);
	SceneSystem::Instance().SetCurrentScene(SCENENAME);

	GameObject& uiManager = mapEditorScene.CreateObject();
	uiManager.AddComponent<UIManager>();

	GameObject& editorManager = mapEditorScene.CreateObject();
	editorManager.AddComponent<EditorManager>();

	EditorManager::SetScene(&mapEditorScene);

	GameObject& trashCan = mapEditorScene.CreateObject();
	trashCan.AddComponent<UISpriteRenderer>();
	trashCan.GetComponent<UISpriteRenderer>()->LoadBitmapImage(L"Resources\\UI\\TrashCan.png");
	trashCan.GetComponent<UISpriteRenderer>()->SetSize(100, 100);
	trashCan.GetComponent<UISpriteRenderer>()->SetOrder(4);
	UIManager::trashCan = &trashCan;

	GameObject& saveButton = mapEditorScene.CreateObject();
	UISpriteRenderer* saveSprite = saveButton.AddComponent<UISpriteRenderer>();
	saveSprite->LoadBitmapImage(L"Resources\\UI\\Save-icon.png");
	saveSprite->SetSize(50, 50);
	saveSprite->SetOrder(4);
	Button* saveBtn = saveButton.AddComponent<Button>();
	saveBtn->SetOnLeftClickEvent(EditorManager::SaveAllData);
	saveBtn->SetButtonSize(50, 50);
	UIManager::saveButton = &saveButton;

	GameObject& loadButton = mapEditorScene.CreateObject();
	UISpriteRenderer* loadSprite = loadButton.AddComponent<UISpriteRenderer>();
	loadSprite->LoadBitmapImage(L"Resources\\UI\\Load-icon.png");
	loadSprite->SetSize(50, 50);
	loadSprite->SetOrder(4);
	Button* loadBtn = loadButton.AddComponent<Button>();
	loadBtn->SetOnLeftClickEvent(EditorManager::LoadAllData);
	loadBtn->SetButtonSize(50, 50);
	UIManager::loadButton = &loadButton;

	//Camera
	GameObject& camera = mapEditorScene.CreateObject();
	camera.AddComponent<Camera>();
	camera.AddComponent<MainCamera>();

	GameObject& background = mapEditorScene.CreateObject();
	background.AddComponent<SpriteRenderer>();
	background.GetComponent<SpriteRenderer>()->LoadBitmapImage(L"Resources\\Background\\curtaincall_behind.png");
	background.GetComponent<SpriteRenderer>()->SetOrder(-5);

	GameObject& stage = mapEditorScene.CreateObject();
	stage.transform.SetLocalPosition(0, 30);
	SpriteRenderer* stageSprite = stage.AddComponent<SpriteRenderer>();
	stageSprite->LoadBitmapImage(L"Resources\\Background\\curtaincall_theaterframe.png");
	stageSprite->SetOrder(-3);

	GameObject& spreadButton = mapEditorScene.CreateObject();
	UISpriteRenderer* sBtnSprite = spreadButton.AddComponent<UISpriteRenderer>();
	sBtnSprite->LoadBitmapImage(L"Resources\\UI\\Left.png");
	sBtnSprite->SetSize(100, 100);
	sBtnSprite->SetOrder(10);
	Button* sBtn = spreadButton.AddComponent<Button>();
	sBtn->SetOnLeftClickEvent(UIManager::SpreadUI);
	UIManager::spreadButton = &spreadButton;

	GameObject& foldButton = mapEditorScene.CreateObject();
	UISpriteRenderer* fBtnSprite = foldButton.AddComponent<UISpriteRenderer>();
	fBtnSprite->LoadBitmapImage(L"Resources\\UI\\Right.png");
	fBtnSprite->SetSize(100, 100);
	fBtnSprite->SetOrder(10);
	Button* fBtn = foldButton.AddComponent<Button>();
	fBtn->SetOnLeftClickEvent(UIManager::FoldUI);
	UIManager::foldButton = &foldButton;
	foldButton.Disable();

	GameObject& backBoard = mapEditorScene.CreateObject();
	UISpriteRenderer* backSprite = backBoard.AddComponent<UISpriteRenderer>();
	backSprite->LoadBitmapImage(L"Resources\\UI\\BackBoard.png");
	backSprite->SetSize(500, 1000);
	backSprite->SetOrder(3);
	UIManager::backBoard = &backBoard;
	backBoard.Disable();

	GameObject& leftButton = mapEditorScene.CreateObject();
	UISpriteRenderer* leftArrowSprite = leftButton.AddComponent<UISpriteRenderer>();
	leftArrowSprite->LoadBitmapImage(L"Resources\\UI\\LeftArrow.png");
	leftArrowSprite->SetSize(50, 50);
	leftArrowSprite->SetOrder(10);
	Button* lBtn = leftButton.AddComponent<Button>();
	lBtn->SetOnLeftClickEvent(UIManager::OnLeftButton);
	lBtn->SetButtonSize(50, 50);
	UIManager::leftButton = &leftButton;
	leftButton.Disable();

	GameObject& rightButton = mapEditorScene.CreateObject();
	UISpriteRenderer* rightArrowSprite = rightButton.AddComponent<UISpriteRenderer>();
	rightArrowSprite->LoadBitmapImage(L"Resources\\UI\\RightArrow.png");
	rightArrowSprite->SetSize(50, 50);
	rightArrowSprite->SetOrder(10);
	Button* rBtn = rightButton.AddComponent<Button>();
	rBtn->SetOnLeftClickEvent(UIManager::OnRightButton);
	rBtn->SetButtonSize(50, 50);
	UIManager::rightButton = &rightButton;
	rightButton.Disable();

	GameObject& boxSlot = mapEditorScene.CreateObject();
	UISpriteRenderer* boxSlotSprite = boxSlot.AddComponent<UISpriteRenderer>();
	boxSlotSprite->LoadBitmapImage(L"Resources\\Object\\box_front.png");
	boxSlotSprite->SetSize(200, 200);
	boxSlotSprite->SetOrder(5);
	UIManager::boxSlot = &boxSlot;
	boxSlot.Disable();

	GameObject& ladderSlot = mapEditorScene.CreateObject();
	UISpriteRenderer* ladderSlotSprite = ladderSlot.AddComponent<UISpriteRenderer>();
	ladderSlotSprite->LoadBitmapImage(L"Resources\\Object\\ladder_Front.png");
	ladderSlotSprite->SetSize(70, 200);
	ladderSlotSprite->SetOrder(5);
	UIManager::ladderSlot = &ladderSlot;
	ladderSlot.Disable();

	GameObject& leftPlatformSlot = mapEditorScene.CreateObject();
	UISpriteRenderer* leftPlatformSlotSprite = leftPlatformSlot.AddComponent<UISpriteRenderer>();
	leftPlatformSlotSprite->LoadBitmapImage(L"Resources\\Object\\secondfloor_L.png");
	leftPlatformSlotSprite->SetSize(200, 50);
	leftPlatformSlotSprite->SetOrder(5);
	UIManager::leftPlatformSlot = &leftPlatformSlot;
	leftPlatformSlot.Disable();

	GameObject& rightPlatformSlot = mapEditorScene.CreateObject();
	UISpriteRenderer* rightPlatformSlotSprite = rightPlatformSlot.AddComponent<UISpriteRenderer>();
	rightPlatformSlotSprite->LoadBitmapImage(L"Resources\\Object\\secondfloor_R.png");
	rightPlatformSlotSprite->SetSize(200, 50);
	rightPlatformSlotSprite->SetOrder(5);
	UIManager::rightPlatformSlot = &rightPlatformSlot;
	rightPlatformSlot.Disable();

	GameObject& waterTankSlot = mapEditorScene.CreateObject();
	UISpriteRenderer* waterTankSlotSprite = waterTankSlot.AddComponent<UISpriteRenderer>();
	waterTankSlotSprite->LoadBitmapImage(L"Resources\\Object\\watertank.png");
	waterTankSlotSprite->SetSize(200, 200);
	waterTankSlotSprite->SetOrder(5);
	UIManager::waterTankSlot = &waterTankSlot;
	waterTankSlot.Disable();

	GameObject& archSlot = mapEditorScene.CreateObject();
	UISpriteRenderer* archSlotSprite = archSlot.AddComponent<UISpriteRenderer>();
	archSlotSprite->LoadBitmapImage(L"Resources\\Object\\cycle_back.png");
	archSlotSprite->SetSize(200, 200);
	archSlotSprite->SetOrder(5);
	UIManager::archSlot = &archSlot;
	archSlot.Disable();

	GameObject& elevatorSlot = mapEditorScene.CreateObject();
	UISpriteRenderer* elevatorSlotSprite = elevatorSlot.AddComponent<UISpriteRenderer>();
	elevatorSlotSprite->LoadBitmapImage(L"Resources\\Object\\elevator_cart.png");
	elevatorSlotSprite->SetSize(60, 200);
	elevatorSlotSprite->SetOrder(5);
	UIManager::elevatorSlot = &elevatorSlot;
	elevatorSlot.Disable();

	GameObject& weatherSlot = mapEditorScene.CreateObject();
	UISpriteRenderer* weatherSlotSprite = weatherSlot.AddComponent<UISpriteRenderer>();
	weatherSlotSprite->LoadBitmapImage(L"Resources\\Object\\theatercontrolbox.png");
	weatherSlotSprite->SetSize(200, 200);
	weatherSlotSprite->SetOrder(5);
	UIManager::weatherSlot = &weatherSlot;
	weatherSlot.Disable();

	GameObject& soundSlot = mapEditorScene.CreateObject();
	UISpriteRenderer* soundSlotSprite = soundSlot.AddComponent<UISpriteRenderer>();
	soundSlotSprite->LoadBitmapImage(L"Resources\\Object\\musiccontrolbox.png");
	soundSlotSprite->SetSize(200, 200);
	soundSlotSprite->SetOrder(5);
	UIManager::soundSlot = &soundSlot;
	soundSlot.Disable();

// 	GameObject& leverSlot = mapEditorScene.CreateObject();
// 	UISpriteRenderer* leverSlotSprite = leverSlot.AddComponent<UISpriteRenderer>();
// 	leverSlotSprite->LoadBitmapImage(L"Resources\\Object\\lever_gear.png");
// 	leverSlotSprite->SetSize(200, 200);
// 	leverSlotSprite->SetOrder(5);
// 	UISpriteRenderer* leverSlotSprite2 = leverSlot.AddComponent<UISpriteRenderer>();
// 	leverSlotSprite2->LoadBitmapImage(L"Resources\\Object\\lever_stick.png");
// 	leverSlotSprite2->SetSize(200, 200);
// 	leverSlotSprite2->SetOrder(6);
// 	UIManager::elevatorSlot = &leverSlot;
// 	leverSlot.Disable();
// 
// 	GameObject& steeringSlot = mapEditorScene.CreateObject();
// 	UISpriteRenderer* steeringSlotSprite = steeringSlot.AddComponent<UISpriteRenderer>();
// 	steeringSlotSprite->LoadBitmapImage(L"Resources\\Object\\wheel.png");
// 	steeringSlotSprite->SetSize(200, 200);
// 	steeringSlotSprite->SetOrder(5);
// 	UIManager::elevatorSlot = &steeringSlot;
// 	steeringSlot.Disable();
}
