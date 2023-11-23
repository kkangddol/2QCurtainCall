// GammaEngine.cpp : 애플리케이션에 대한 진입점을 정의합니다.
#include "GammaEngine.h"
#include "WorkSpace.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GammaEngine::WindowSystem* system = GammaEngine::WindowSystem::Instance();
    GammaEngine::Screen* screen = GammaEngine::Screen::Instance();
    GammaEngine::Engine* engine = GammaEngine::Engine::Instance();
    system->Initialize(GammaEngine::Screen::width, GammaEngine::Screen::height);
    engine->Initialize();

    //workspaces
    WorkSpace* workspace = new WorkSpace();

    system->Run(engine);
    return 0;
}
