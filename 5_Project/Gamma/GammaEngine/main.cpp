// GammaEngine.cpp : 애플리케이션에 대한 진입점을 정의합니다.
#include "stdafx.h"
#include "Scene1.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    WindowSystem* system = WindowSystem::Instance();
    if (!system)
    {
        return -1;
    }
    Engine* engine = Engine::Instance();
    Screen* screen = Screen::Instance();
    system->Initialize(Screen::width, Screen::height);
    engine->Initialize(new Scene1());
    system->Run(engine);

    return 0;
}
