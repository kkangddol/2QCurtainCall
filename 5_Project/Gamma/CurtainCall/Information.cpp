#include "GammaEngine.h"
#include "Information.h"

using namespace GammaEngine;

std::vector<GameObject*>* Information::instanceList;
std::unordered_map<std::wstring, std::wstring>* Information::infoMap;

Information::Information()
{
	instanceList = new std::vector<GameObject*>();
	infoMap = new std::unordered_map<std::wstring, std::wstring>();
	infoMap->insert(std::make_pair(L"a",L"Resources\\Information\\a.png"));
	infoMap->insert(std::make_pair(L"b",L"Resources\\Information\\b.png"));
	infoMap->insert(std::make_pair(L"x",L"Resources\\Information\\x.png"));
	infoMap->insert(std::make_pair(L"y",L"Resources\\Information\\y.png"));
	infoMap->insert(std::make_pair(L"arow",L"Resources\\Information\\arow.png"));
	infoMap->insert(std::make_pair(L"display",L"Resources\\Information\\display.png"));
	infoMap->insert(std::make_pair(L"L_rotation",L"Resources\\Information\\L_rotation.png"));
	infoMap->insert(std::make_pair(L"L_shake",L"Resources\\Information\\L_shake.png"));
	infoMap->insert(std::make_pair(L"l_wheel",L"Resources\\Information\\l_wheel.png"));
	infoMap->insert(std::make_pair(L"lb",L"Resources\\Information\\lb.png"));
	infoMap->insert(std::make_pair(L"lt",L"Resources\\Information\\lt.png"));
	infoMap->insert(std::make_pair(L"option",L"Resources\\Information\\option.png"));
	infoMap->insert(std::make_pair(L"point_arrow",L"Resources\\Information\\point_arrow.png"));
	infoMap->insert(std::make_pair(L"press_a",L"Resources\\Information\\press_a.png"));
	infoMap->insert(std::make_pair(L"press_b",L"Resources\\Information\\press_b.png"));
	infoMap->insert(std::make_pair(L"press_lb",L"Resources\\Information\\press_lb.png"));
	infoMap->insert(std::make_pair(L"press_rb",L"Resources\\Information\\press_rb.png"));
	infoMap->insert(std::make_pair(L"press_x",L"Resources\\Information\\press_x.png"));
	infoMap->insert(std::make_pair(L"press_y",L"Resources\\Information\\press_y.png"));
	infoMap->insert(std::make_pair(L"r_horizontal",L"Resources\\Information\\r_horizontal.png"));
	infoMap->insert(std::make_pair(L"r_rotaion",L"Resources\\Information\\r_rotaion.png"));
	infoMap->insert(std::make_pair(L"r_wheel",L"Resources\\Information\\r_wheel.png"));
	infoMap->insert(std::make_pair(L"rb",L"Resources\\Information\\rb.png"));
	infoMap->insert(std::make_pair(L"rt",L"Resources\\Information\\rt.png"));
	infoMap->insert(std::make_pair(L"updown_L",L"Resources\\Information\\updown_L.png"));
	infoMap->insert(std::make_pair(L"updown_R",L"Resources\\Information\\updown_R.png"));
	infoMap->insert(std::make_pair(L"down_arrow",L"Resources\\Information\\down_arrow.png"));
	infoMap->insert(std::make_pair(L"left_arrow",L"Resources\\Information\\left_arrow.png"));
	infoMap->insert(std::make_pair(L"up_arrow",L"Resources\\Information\\up_arrow.png"));
	infoMap->insert(std::make_pair(L"right_arrow",L"Resources\\Information\\right_arrow.png"));
	infoMap->insert(std::make_pair(L"popupbubble",L"Resources\\Information\\popupbubble.png"));
	infoMap->insert(std::make_pair(L"popupbubble_arch_castle",L"Resources\\Information\\popupbubble_arch_castle.png"));
	infoMap->insert(std::make_pair(L"popupbubble_arch_forest",L"Resources\\Information\\popupbubble_arch_forest.png"));
	infoMap->insert(std::make_pair(L"popupbubble_arch_ocean",L"Resources\\Information\\popupbubble_arch_ocean.png"));
	infoMap->insert(std::make_pair(L"actorA",L"Resources\\Information\\actorA.png"));
	infoMap->insert(std::make_pair(L"actorB",L"Resources\\Information\\actorB.png"));
	infoMap->insert(std::make_pair(L"sun_moon_cloud",L"Resources\\Information\\sun_moon_cloud.png"));
}

Information::~Information()
{

}

GameObject* Information::Create(std::wstring str)
{
	GameObject* instance = new GameObject();
	instance->AddComponent<BitmapRenderer>();
	instance->GetComponent<BitmapRenderer>()->LoadBitmapImage((*infoMap)[str]);
	instance->GetComponent<BitmapRenderer>()->order=15;
	//instance->GetComponent<BitmapRenderer>()->size=vector2(70,70);
	instance->isEnabled = false;
	instanceList->push_back(instance);
	Instantiate(instance);
	return instance;
}

GameObject* Information::CreateText(std::wstring str)
{
	GameObject* instance = new GameObject();
	instance->isEnabled = false;
	instance->AddComponent<TextRenderer>();
	instance->GetComponent<TextRenderer>()->order = 15;
	instance->GetComponent<TextRenderer>()->size = vector2(100, 100);
	instance->GetComponent<TextRenderer>()->SetText(str);
	instanceList->push_back(instance);
	Instantiate(instance);
	return instance;
}

void Information::DisableAll()
{
	for (auto iter : *instanceList)
	{
		iter->isEnabled = false;
	}
}


void Information::RemoveAll()
{
	instanceList->clear();
}