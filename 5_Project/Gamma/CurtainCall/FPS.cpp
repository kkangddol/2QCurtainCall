#include "GammaEngine.h"
#include "FPS.h"

FPS::FPS(GameObject* t) : Component(t)
{

}

void FPS::Start()
{

	Timer::Delay(1, true, [this]() {
		value = count;
		count = 0;
		});
}

void FPS::Update()
{
	TCHAR tmp[255];
	swprintf_s(tmp, 255, L"%d", value);
	
	Debug::DrawTextToScreen(vector2(100, 100), vector2(1700, 200), std::wstring(tmp), std::wstring(L"Verdana"), vector4(0, 0, 0, 1));
	count++;
}