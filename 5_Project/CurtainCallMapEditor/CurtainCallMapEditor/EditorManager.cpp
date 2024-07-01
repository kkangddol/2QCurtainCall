// #include <algorithm>
#include <vector>
#include <fstream>

#include "EditorManager.h"
#include "EditorObject.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "UIManager.h"
#include "Scene.h"
#include "Dragable.h"
#include "Camera.h"
#include "InputSystem.h"


std::list<GameObject*> EditorManager::objectList_;
GameObject* EditorManager::draggingObject_ = nullptr;
GameObject* EditorManager::bindingObject_ = nullptr;
Scene* EditorManager::currentScene_ = nullptr;
int EditorManager::objectIndex_ = 0;

EditorManager::EditorManager(GameObject* obj)
	: Component(obj)
{
}

EditorManager::~EditorManager()
{
	for (auto obj : objectList_)
	{
		delete obj;
	}
}

void EditorManager::AddToList(GameObject* obj)
{
	objectList_.push_back(obj);
}

void EditorManager::RemoveFromList(GameObject* obj)
{
	objectList_.remove(obj);
}

GameObject* EditorManager::GetDragObject()
{
	return draggingObject_;
}

void EditorManager::SetDragObject(GameObject* obj)
{
	draggingObject_ = obj;
	std::vector<SpriteRenderer*> temp = draggingObject_->GetComponents<SpriteRenderer>();
	
	int order = 5;
	for (auto& renderer : temp)
	{
		renderer->SetOrder(order++);
	}
}

void EditorManager::EndDrag()
{
	std::vector<SpriteRenderer*> temp = draggingObject_->GetComponents<SpriteRenderer>();

	for (auto& renderer : temp)
	{
		renderer->SetOrder(0);
	}

	if (UIManager::CheckDestroy())
	{
		//Unbind(draggingObject_);
		objectList_.remove(draggingObject_);
		draggingObject_->Destroy();

		EditorObject* temp = draggingObject_->GetComponent<EditorObject>()->GetLinkedComponent();
		if (temp)
		{
			GameObject* linkedObj = temp->GetObj();
			objectList_.remove(linkedObj);
			linkedObj->Destroy();
		}
	}

	draggingObject_ = nullptr;
}

void EditorManager::EndDrag(bool justChangeToNullptr)
{
	if (justChangeToNullptr)
	{
		draggingObject_ = nullptr;
	}
}

void EditorManager::RightClick(GameObject* obj)
{
	if (!bindingObject_)
	{
		bindingObject_ = obj;
		return;
	}

	if (bindingObject_ == obj)
	{
		bindingObject_ = nullptr;
		return;
	}

	Unbind(bindingObject_);
	Unbind(obj);

	Bind(bindingObject_, obj);

	bindingObject_ = nullptr;
}

bool EditorManager::SaveAllData()
{
	std::ofstream fout("Map\\map01.txt");
	if (fout.fail())
	{
		return false;
	}

	for (auto object : objectList_)
	{
		Vector2D pos = object->transform.GetLocalPosition();
		EditorObject* data = object->GetComponent<EditorObject>();

		fout << data->objectID << " " << data->triggerID << " " << data->reactantID << " " <<
			data->index << "  " << data->linkedIndex << " " << pos.x << " " << pos.y << "\n";
	}

	fout.close();
	return true;
}

bool EditorManager::LoadAllData()
{
	std::ifstream fin("Map\\map01.txt");
	if (fin.fail())
	{
		return false;
	}

	// Clear the existing object list
	for (auto& object : objectList_)
	{
		object->Destroy();
	}

	objectList_.clear();

	// Read data from the file and create EditorObject instances
	int id, triggerID, reactantID, index, linkedIndex;
	float x, y;
	while (fin >> id >> triggerID >> reactantID >> index >> linkedIndex >> x >> y)
	{
		// Create a new EditorObject instance and add it to the object list
		GameObject* obj = Instantiate((eObject)id, true);
		EditorObject* editorObject = obj->GetComponent<EditorObject>();
		editorObject->objectID = id;
		editorObject->triggerID = triggerID;
		editorObject->reactantID = reactantID;
		editorObject->index = index;
		editorObject->linkedIndex = linkedIndex;
		obj->transform.SetLocalPosition(Vector2D(x, y));

		if (linkedIndex < objectList_.size())
		{
			std::list<GameObject*>::iterator iter = objectList_.begin();
			for (int i = 0; i < linkedIndex; ++i)
			{
				++iter;
			}

			Bind(obj, *iter);
		}
	}

	fin.close();

	objectIndex_ = objectList_.size();

	return true;
}

GameObject* EditorManager::Instantiate(eObject objEnum)
{
	if (EditorManager::GetDragObject())
	{
		return nullptr;
	}

	if (!currentScene_)
	{
		return nullptr;
	}

	GameObject& newObject = currentScene_->CreateObject();
	EditorManager::AddToList(&newObject);
	newObject.transform.SetLocalPosition(Camera::main->ScreenToWorldPoint(InputSystem::GetMousePosition()));
	Dragable* dragable = newObject.AddComponent<Dragable>();
	SpriteRenderer* renderer = newObject.AddComponent<SpriteRenderer>();
	EditorObject* info = newObject.AddComponent<EditorObject>();
	info->index = objectIndex_++;

	switch (objEnum)
	{
		case eObject::BOX:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\box_front.png");
			info->objectID = (int)eObject::BOX;
		}
		break;

		case eObject::LADDER:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\ladder_Front.png");
			info->objectID = (int)eObject::LADDER;
		}
		break;

		case eObject::LEFTPLATFORM:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\secondfloor_L.png");
			info->objectID = (int)eObject::LEFTPLATFORM;
		}
		break;

		case eObject::RIGHTPLATFORM:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\secondfloor_R.png");
			info->objectID = (int)eObject::RIGHTPLATFORM;
		}
		break;

		case eObject::WATERTANK:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\wheel.png");
			info->objectID = (int)eObject::WHEEL;
			info->reactantID = (int)eObject::WATERTANK;

			GameObject& waterTank = currentScene_->CreateObject();
			EditorManager::AddToList(&waterTank);
			waterTank.transform.SetLocalPosition(Vector2D(0,0));
			Dragable* wtDragable = waterTank.AddComponent<Dragable>();
			EditorObject* wtInfo = waterTank.AddComponent<EditorObject>();
			SpriteRenderer* wtRenderer = waterTank.AddComponent<SpriteRenderer>();

			wtRenderer->LoadBitmapImage(L"Resources\\Object\\watertank.png");
			wtInfo->objectID = (int)eObject::WATERTANK;
			wtInfo->triggerID = (int)eObject::WHEEL;
			wtInfo->index = objectIndex_++;

			Bind(&newObject, &waterTank);
		}
		break;

		case eObject::ARCH:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\lever_gear.png");
			SpriteRenderer* stickSprite = newObject.AddComponent<SpriteRenderer>();
			stickSprite->LoadBitmapImage(L"Resources\\Object\\lever_stick.png");
			info->objectID = (int)eObject::LEVER;
			info->reactantID = (int)eObject::ARCH;

			GameObject& Cycle = currentScene_->CreateObject();
			EditorManager::AddToList(&Cycle);
			Cycle.transform.SetLocalPosition(Vector2D(0, 0));
			Dragable* cDragable = Cycle.AddComponent<Dragable>();
			EditorObject* cInfo = Cycle.AddComponent<EditorObject>();
			SpriteRenderer* cRenderer = Cycle.AddComponent<SpriteRenderer>();

			cRenderer->LoadBitmapImage(L"Resources\\Object\\cycle_back.png");
			cInfo->objectID = (int)eObject::CYCLE;
			cInfo->reactantID = (int)eObject::ARCH;
			cInfo->index = objectIndex_++;

			GameObject& arch = currentScene_->CreateObject();
			EditorManager::AddToList(&arch);
			arch.transform.SetLocalPosition(Vector2D(0, -700));
			EditorObject* aInfo = arch.AddComponent<EditorObject>();

			aInfo->objectID = (int)eObject::ARCH;
			aInfo->triggerID = (int)eObject::LEVER;
			aInfo->index = objectIndex_++;

			Bind(&newObject, &Cycle);
		}
		break;

		case eObject::ELEVATOR:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\scaffolding_original.png");
			renderer->SetOffset(Vector2D(0, -renderer->GetSize().y));
			info->objectID = (int)eObject::SCAFFOLDING;
			info->reactantID = (int)eObject::ELEVATOR;

			GameObject& elevator = currentScene_->CreateObject();
			EditorManager::AddToList(&elevator);
			elevator.transform.SetLocalPosition(Vector2D(0, 0));
			Dragable* eDragable = elevator.AddComponent<Dragable>();
			EditorObject* eInfo = elevator.AddComponent<EditorObject>();
			SpriteRenderer* eRenderer = elevator.AddComponent<SpriteRenderer>();

			eRenderer->LoadBitmapImage(L"Resources\\Object\\elevator_cart.png");
			eRenderer->SetOffset(Vector2D(0, 20 - eRenderer->GetSize().y / 2));

			eInfo->objectID = (int)eObject::ELEVATOR;
			eInfo->triggerID = (int)eObject::SCAFFOLDING;
			eInfo->index = objectIndex_++;

			Bind(&newObject, &elevator);
		}
		break;

		case eObject::CONTROL:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\theatercontrolbox.png");
			renderer->SetOffset(Vector2D(0, -50));
			info->objectID = (int)eObject::CONTROL;
			info->reactantID = (int)eObject::CONTROL;
		}
		break;

		case eObject::MUSIC:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\musiccontrolbox.png");
			info->objectID = (int)eObject::MUSIC;
			info->reactantID = (int)eObject::MUSIC;
		}
		break;

		default:
		{

		}
		break;
	}

	return &newObject;
}

GameObject* EditorManager::Instantiate(eObject objEnum, bool dataLoad)
{
	if (EditorManager::GetDragObject())
	{
		return nullptr;
	}

	if (!currentScene_)
	{
		return nullptr;
	}

	GameObject& newObject = currentScene_->CreateObject();
	EditorManager::AddToList(&newObject);
	Dragable* dragable = newObject.AddComponent<Dragable>();
	SpriteRenderer* renderer = newObject.AddComponent<SpriteRenderer>();
	EditorObject* info = newObject.AddComponent<EditorObject>();

	switch (objEnum)
	{
		case eObject::BOX:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\box_front.png");
			info->objectID = (int)eObject::BOX;
		}
		break;

		case eObject::LADDER:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\ladder_Front.png");
			info->objectID = (int)eObject::LADDER;
		}
		break;

		case eObject::LEFTPLATFORM:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\secondfloor_L.png");
			info->objectID = (int)eObject::LEFTPLATFORM;
		}
		break;

		case eObject::RIGHTPLATFORM:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\secondfloor_R.png");
			info->objectID = (int)eObject::RIGHTPLATFORM;
		}
		break;

		case eObject::WATERTANK:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\watertank.png");
			info->objectID = (int)eObject::WATERTANK;
		}
		break;

		case eObject::ELEVATOR:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\elevator_cart.png");
			renderer->SetOffset(Vector2D(0, 20 - renderer->GetSize().y / 2));
			info->objectID = (int)eObject::ELEVATOR;
		}
		break;

		case eObject::CONTROL:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\theatercontrolbox.png");
			info->objectID = (int)eObject::CONTROL;
		}
		break;

		case eObject::MUSIC:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\musiccontrolbox.png");
			info->objectID = (int)eObject::MUSIC;
		}
		break;

		case eObject::LEVER:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\lever_gear.png");
			SpriteRenderer* stickSprite = newObject.AddComponent<SpriteRenderer>();
			stickSprite->LoadBitmapImage(L"Resources\\Object\\lever_stick.png");
			info->objectID = (int)eObject::LEVER;
		}
		break;

		case eObject::CYCLE:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\cycle_back.png");
			info->objectID = (int)eObject::CYCLE;
		}
		break;

		case eObject::WHEEL:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\wheel.png");
			info->objectID = (int)eObject::WHEEL;
		}
		break;

		case eObject::SCAFFOLDING:
		{
			renderer->LoadBitmapImage(L"Resources\\Object\\scaffolding_original.png");
			renderer->SetOffset(Vector2D(0, -renderer->GetSize().y));
			info->objectID = (int)eObject::SCAFFOLDING;
		}
		break;

		case eObject::ARCH:
		{
			newObject.transform.SetLocalPosition(Vector2D(0, -700));
			info->objectID = (int)eObject::ARCH;
		}
		break;

		default:
		{
			newObject.Destroy();
			objectList_.remove(&newObject);
		}
		break;
	}

	return &newObject;
}

void EditorManager::SetScene(Scene* scene)
{
	currentScene_ = scene;
}

int EditorManager::GetObjectCount()
{
	return objectList_.size();
}

void EditorManager::Unbind(GameObject* obj)
{
	EditorObject* editorObject = obj->GetComponent<EditorObject>();

	if (editorObject->GetLinkedComponent() != nullptr)
	{
		editorObject->GetLinkedComponent()->linkedIndex = -1;
		editorObject->GetLinkedComponent()->linkedObject = nullptr;
	}

	editorObject->linkedIndex = -1;
	editorObject->linkedObject = nullptr;
}

void EditorManager::Bind(GameObject* lhs, GameObject* rhs)
{
	EditorObject* lhsComp = lhs->GetComponent<EditorObject>();
	EditorObject* rhsComp = rhs->GetComponent<EditorObject>();

	lhsComp->linkedIndex = rhsComp->index;
	lhsComp->linkedObject = rhs;

	rhsComp->linkedIndex = lhsComp->index;
	rhsComp->linkedObject = lhs;
}
