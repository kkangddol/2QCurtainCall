#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "Vector2D.h"

class GameObject;

/// <summary>
/// 클라이언트의 UIManager
/// UI 오브젝트들을 관리한다. 어떻게?
/// 2023.01.23 강석원 집
/// </summary>
class UIManager : public Component
{
public:
	UIManager(GameObject* object);

	virtual void Update() override;

private:
	void PrintDebug();
	void SetDynamicPosition();
	int GetSlotIndex() const;

private:
	Vector2D slotPos_[8];
	Vector2D slotSize_;

public:
	static void SpreadUI();
	static void FoldUI();
	static void OnLeftButton();
	static void OnRightButton();
	static bool CheckDestroy();

public:
	static GameObject* trashCan;
	static GameObject* saveButton;
	static GameObject* loadButton;

	static GameObject* spreadButton;

	static GameObject* foldButton;
	static GameObject* backBoard;
	static GameObject* leftButton;
	static GameObject* rightButton;

	static GameObject* boxSlot;
	static GameObject* ladderSlot;
	static GameObject* leftPlatformSlot;
	static GameObject* rightPlatformSlot;
	static GameObject* waterTankSlot;
	static GameObject* archSlot;
	static GameObject* elevatorSlot;
	static GameObject* weatherSlot;

	static GameObject* soundSlot;

private:
	static int slotPage_;
	static bool isSpread_;		// 현재 UI가 펼쳐져 있는지
	static std::vector<GameObject**> spreadObjects_;
	static std::vector<std::vector<GameObject**>> slots_;
	static Vector2D trashCanSize_;
};

