#pragma once
///생성한 오브젝트와 속해있는 컴포넌트를 하나의 함수로 묶어서 그대로 쓸 수 있게 해두는 곳이다.

using namespace GammaEngine;

class MapDataLoader;
namespace Ingame {

	GameObject* CreateCamera(Scene* scene);

	//배경
	GameObject* CreateBackgroundLight(Scene* scene);
	
	//배경
	GameObject* CreateBackground(Scene* scene, float x, float y);

	GameObject* CreateStage(Scene* scene, float x, float y);
	//플랫폼
	GameObject* CreateBlock(Scene* scene, float x, float y, float sizeX, float sizeY);
	GameObject* CreateWall(Scene* scene, float x, float y, float sizeX, float sizeY);
	GameObject* CreateBox(Scene* scene, float x, float y);
	GameObject* CreateLadder(Scene* scene, float x, float y);
	GameObject* CreateLeftPlatform(Scene* scene, float x, float y);
	GameObject* CreateRightPlatform(Scene* scene, float x, float y);
	GameObject* CreateWaterTank(Scene* scene, float x, float y);
	GameObject* CreateArch(Scene* scene, float x, float y);
	GameObject* CreateElevator(Scene* scene, float x, float y);
	GameObject* CreateWheel(Scene* scene, float x, float y);
	GameObject* CreateScaffolding(Scene* scene, float x, float y);
	GameObject* CreateLever(Scene* scene, float x, float y);
	GameObject* CreateArchDisk(Scene* scene, float x, float y);
	GameObject* CreateControlBox(Scene* scene, float x, float y);
	GameObject* CreateMusicBox(Scene* scene, float x, float y);

	GameObject* CreatePointLight(Scene* scene, float x, float y, float magnitude);
	GameObject* CreateSpotLight(Scene* scene, float x, float y);
	GameObject* CreateDistantLight(Scene* scene, float azimuth, float elevation, float magnitude);
	GameObject* CreateTextAnimation(Scene* scene);

	//사운드
	GameObject* CreateIngameBGM(Scene*);
	GameObject* CreateTitleBGM(Scene* scene);
	GameObject* CreateTickTock(Scene* scene);
	GameObject* CreateDiscSound(Scene* scene);
	GameObject* CreateSwitchSound(Scene* scene);
	GameObject* CreatePulleySound(Scene* scene);
	GameObject* CreateArchSound(Scene* scene);
	GameObject* CreateElevatorSound(Scene* scene);
	GameObject* CreateRainingrSound(Scene* scene);

	//플레이어
	GameObject* CreatePlayer(Scene* scene, float x, float y, int id);
	GameObject* CreateFailEffect(Scene* scene, float x, float y);

	//파티클
	GameObject* CreateRainParticle(Scene* scene, float x, float y);
	GameObject* CreateRunningParticle(Scene* scene, float x, float y);
	GameObject* CreateFanfareParticle(Scene* scene, float x, float y);

	//UI
	GameObject* CreateScriptObj(Scene* scene, float x, float y);
	GameObject* CreateTimerObj(Scene* scene, float x, float y);
	GameObject* CreateStampObj(Scene* scene, float x, float y);
	GameObject* CreateLifeObj(Scene* scene, float x, float y);
	GameObject* CreatePauseUI(Scene* scene, float x, float y);
	GameObject* CreateHomeBtn(Scene* scene, float x, float y);
	GameObject* CreateRestartBtn(Scene* scene, float x, float y);
	GameObject* CreateOptionBtn(Scene* scene, float x, float y);
	GameObject* CreatePauseIcon(Scene* scene, float x, float y);
	GameObject* CreateClearUI(Scene* scene, float x, float y);
	GameObject* CreateContinueBtn(Scene* scene, float x, float y);

	struct CreateFunctor
	{
		virtual GameObject* operator()() { return nullptr; }
		virtual GameObject* operator()(Scene* scene, float x, float y) { return nullptr; }
	};

	struct BoxFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct LadderFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct LeftPlatformFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct RightPlatformFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct WaterTankFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct ArchFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct ElevatorFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct ControlBoxFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct MusicBoxFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct WheelFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct ScaffoldingFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct LeverFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};
	struct CycleFunctor : public CreateFunctor
	{
		virtual GameObject* operator()(Scene* scene, float x, float y) override;
	};

	void CreateFromData(Scene* scene, MapDataLoader* mapData);
}
