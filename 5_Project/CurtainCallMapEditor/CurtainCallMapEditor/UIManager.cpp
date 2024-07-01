#include "UIManager.h"

#include "InputSystem.h"
#include "SceneSystem.h"

#include "Debug.h"
#include "GameObject.h"
#include "Core.h"
#include "EditorManager.h"
#include "AABB.h"

#include "SpriteRenderer.h"

#include "EditorObject.h"

GameObject* UIManager::trashCan = nullptr;
GameObject* UIManager::saveButton = nullptr;
GameObject* UIManager::loadButton = nullptr;

GameObject* UIManager::spreadButton = nullptr;

GameObject* UIManager::foldButton = nullptr;
GameObject* UIManager::backBoard = nullptr;
GameObject* UIManager::leftButton = nullptr;
GameObject* UIManager::rightButton = nullptr;

GameObject* UIManager::boxSlot = nullptr;
GameObject* UIManager::ladderSlot = nullptr;
GameObject* UIManager::leftPlatformSlot = nullptr;
GameObject* UIManager::rightPlatformSlot = nullptr;
GameObject* UIManager::waterTankSlot = nullptr;
GameObject* UIManager::archSlot = nullptr;
GameObject* UIManager::elevatorSlot = nullptr;
GameObject* UIManager::weatherSlot = nullptr;

GameObject* UIManager::soundSlot = nullptr;

std::vector<GameObject**> UIManager::spreadObjects_;
std::vector<std::vector<GameObject**>> UIManager::slots_;
Vector2D UIManager::trashCanSize_(100, 100);

int UIManager::slotPage_ = 0;
bool UIManager::isSpread_ = false;

UIManager::UIManager(GameObject* object)
	:Component(object),
	slotSize_(200,200)
{
	slots_.push_back(std::vector<GameObject**>());
	slots_.push_back(std::vector<GameObject**>());

	spreadObjects_.push_back(&foldButton);
	spreadObjects_.push_back(&backBoard);
	spreadObjects_.push_back(&leftButton);
	spreadObjects_.push_back(&rightButton);

	slots_[0].push_back(&boxSlot);
	slots_[0].push_back(&ladderSlot);
	slots_[0].push_back(&leftPlatformSlot);
	slots_[0].push_back(&rightPlatformSlot);
	slots_[0].push_back(&waterTankSlot);
	slots_[0].push_back(&archSlot);
	slots_[0].push_back(&elevatorSlot);
	slots_[0].push_back(&weatherSlot);

	slots_[1].push_back(&soundSlot);
}

void UIManager::Update()
{
	SetDynamicPosition();

	PrintDebug();

	if (!isSpread_)
	{
		return;
	}

	int slotIndex = GetSlotIndex();

	if (slotIndex == -1)
	{
		return;
	}
	
	if (slotIndex < 9)
	{
		EditorManager::Instantiate((EditorManager::eObject)slotIndex);
	}
}

void UIManager::PrintDebug()
{
	Debug::DrawRectangleScreen(trashCanSize_, trashCan->transform.GetLocalPosition(), 0, 1, 0, 0, 1);

	std::wstring trashPos;
	trashPos.append(L"trashX : ");
	trashPos.append(std::to_wstring(object_->transform.GetLocalPosition().x));
	trashPos.append(L"\n");
	trashPos.append(L"trashY : ");
	trashPos.append(std::to_wstring(object_->transform.GetLocalPosition().y));
	Debug::DrawTextToScreen(trashPos, Vector2D(400, 200), Vector2D(0, 500));

	std::wstring mousePos;
	mousePos.append(L"mouseScreenX : ");
	mousePos.append(std::to_wstring((InputSystem::GetMousePosition()).x));
	mousePos.append(L"\n");
	mousePos.append(L"mouseScreenY : ");
	mousePos.append(std::to_wstring((InputSystem::GetMousePosition()).y));
	Debug::DrawTextToScreen(mousePos, Vector2D(400, 200), Vector2D(0, 400));

	std::wstring objectCount;
	objectCount.append(L"objectCount : ");
	objectCount.append(std::to_wstring(EditorManager::GetObjectCount()));
	Debug::DrawTextToScreen(objectCount, Vector2D(400, 200), Vector2D(200, 0));

	if (isSpread_)
	{
		Vector2D mouseScreenPos = InputSystem::GetMousePosition();
		for (int i = 0; i < 8; i++)
		{
			Debug::DrawRectangleScreen(slotSize_, slotPos_[i], 0, 1, 0, 1, 1);
		}

		for (int i = 0; i < 8; i++)
		{
			if (DetectAABB(slotPos_[i].x - slotSize_.x / 2, slotPos_[i].y - slotSize_.y / 2, slotPos_[i].x + slotSize_.x / 2, slotPos_[i].y + slotSize_.y / 2,
				mouseScreenPos.x, mouseScreenPos.y, mouseScreenPos.x, mouseScreenPos.y))
			{
				Debug::DrawRectangleScreen(slotSize_, slotPos_[i], 0, 0, 1, 0, 1);
			}
		}
	}
}

void UIManager::SetDynamicPosition()
{
	slotPos_[0] = Vector2D(Core::screenWidth - 350, Core::screenHeight / 2 - 350);
	slotPos_[1] = Vector2D(Core::screenWidth - 150, Core::screenHeight / 2 - 350);
	slotPos_[2] = Vector2D(Core::screenWidth - 350, Core::screenHeight / 2 - 150);
	slotPos_[3] = Vector2D(Core::screenWidth - 150, Core::screenHeight / 2 - 150);
	slotPos_[4] = Vector2D(Core::screenWidth - 350, Core::screenHeight / 2 + 50);
	slotPos_[5] = Vector2D(Core::screenWidth - 150, Core::screenHeight / 2 + 50);
	slotPos_[6] = Vector2D(Core::screenWidth - 350, Core::screenHeight / 2 + 250);
	slotPos_[7] = Vector2D(Core::screenWidth - 150, Core::screenHeight / 2 + 250);

	boxSlot->transform.SetLocalPosition(slotPos_[0]);
	ladderSlot->transform.SetLocalPosition(slotPos_[1]);
	leftPlatformSlot->transform.SetLocalPosition(slotPos_[2]);
	rightPlatformSlot->transform.SetLocalPosition(slotPos_[3]);
	waterTankSlot->transform.SetLocalPosition(slotPos_[4]);
	archSlot->transform.SetLocalPosition(slotPos_[5]);
	elevatorSlot->transform.SetLocalPosition(slotPos_[6]);
	weatherSlot->transform.SetLocalPosition(slotPos_[7]);

	soundSlot->transform.SetLocalPosition(slotPos_[0]);

	if (spreadButton)
	{
		spreadButton->transform.SetLocalPosition(Vector2D(Core::screenWidth - 50, Core::screenHeight / 2));
	}

	if (foldButton)
	{
		foldButton->transform.SetLocalPosition(Vector2D(Core::screenWidth - 550, Core::screenHeight / 2));
	}

	if (backBoard)
	{
		backBoard->transform.SetLocalPosition(Vector2D(Core::screenWidth - 250, Core::screenHeight / 2));
	}

	if (trashCan)
	{
		trashCan->transform.SetLocalPosition(Vector2D(75, Core::screenHeight - 75));
	}

	if (saveButton)
	{
		saveButton->transform.SetLocalPosition(Vector2D(50, 50));
	}

	if (loadButton)
	{
		loadButton->transform.SetLocalPosition(Vector2D(100, 50));
	}

	if (leftButton)
	{
		leftButton->transform.SetLocalPosition(Vector2D(Core::screenWidth - 350, Core::screenHeight - 75));
	}

	if (rightButton)
	{
		rightButton->transform.SetLocalPosition(Vector2D(Core::screenWidth - 150, Core::screenHeight - 75));
	}
}

int UIManager::GetSlotIndex() const
{
	if (InputSystem::GetMouseButtonHold(VK_LBUTTON))
	{
		Vector2D dragablePos = object_->transform.GetLocalPosition();
		Vector2D mouseScreenPos = InputSystem::GetMousePosition();
		for (int i = 0; i < 8; ++i)
		{
			if (DetectAABB(slotPos_[i].x - slotSize_.x / 2, slotPos_[i].y - slotSize_.y / 2, slotPos_[i].x + slotSize_.x / 2, slotPos_[i].y + slotSize_.y / 2,
				mouseScreenPos.x, mouseScreenPos.y, mouseScreenPos.x, mouseScreenPos.y))
			{
				return i + 8 * slotPage_;
			}
		}
	}

	return -1;
}

void UIManager::SpreadUI()
{
	if (isSpread_)
	{
		return;
	}

	isSpread_ = true;

	if (spreadButton)
	{
		spreadButton->Disable();
	}

	for (auto object : spreadObjects_)
	{
		if (*object)
		{
			(*object)->Enable();
		}
	}

	for (auto slot : slots_[slotPage_])
	{
		if (*slot)
		{
			(*slot)->Enable();
		}
	}
}

void UIManager::FoldUI()
{
	if (!isSpread_)
	{
		return;
	}

	isSpread_ = false;


	if (spreadButton)
	{
		spreadButton->Enable();
	}

	for (auto object : spreadObjects_)
	{
		if (*object)
		{
			(*object)->Disable();
		}
	}

	for (auto slot : slots_[slotPage_])
	{
		if (*slot)
		{
			(*slot)->Disable();
		}
	}
}

void UIManager::OnLeftButton()
{
	--slotPage_;

	if (slotPage_ < 0)
	{
		slotPage_ = 0;
	}

	for (auto& vec : slots_)
	{
		for (auto& slot : vec)
		{
			if (*slot)
			{
				(*slot)->Disable();
			}
		}
	}

	for (auto& slot : slots_[slotPage_])
	{
		(*slot)->Enable();
	}
}

void UIManager::OnRightButton()
{
	++slotPage_;

	if (slotPage_ > 1)
	{
		slotPage_ = 1;
	}

	for (auto& vec : slots_)
	{
		for (auto& slot : vec)
		{
			if (*slot)
			{
				(*slot)->Disable();
			}
		}
	}

	for (auto& slot : slots_[slotPage_])
	{
		(*slot)->Enable();
	}
}

bool UIManager::CheckDestroy()
{
	Vector2D mouseScreenPos = InputSystem::GetMousePosition();
	Vector2D trashCanPos = trashCan->transform.GetLocalPosition();
	if (DetectAABB(trashCanPos.x - trashCanSize_.x / 2, trashCanPos.y - trashCanSize_.y / 2, trashCanPos.x + trashCanSize_.x / 2, trashCanPos.y + trashCanSize_.y / 2,
		mouseScreenPos.x, mouseScreenPos.y, mouseScreenPos.x, mouseScreenPos.y))
	{
		return true;
	}

	return false;
}
