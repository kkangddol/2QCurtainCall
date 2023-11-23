#pragma once
#include <vector>
#include <string>
#include <unordered_map>

using namespace GammaEngine;

class Information
{
public:
	Information();
	~Information();
	static GameObject* Create(std::wstring);
	static GameObject* CreateText(std::wstring str);
	static void DisableAll();
	static void RemoveAll();
private:
	static std::vector<GameObject*>* instanceList;
	static std::unordered_map<std::wstring,std::wstring>* infoMap;
};

