#pragma once

/// <summary>
/// 게임 엔진 class
/// </summary>

namespace GammaEngine
{
	class ObjectManager;
	class SceneManager;
	class GamepadManager;
	class Input;
	class Timer;
	class Debug;
	class GraphicSystem;
	class CollisionSystem;
	class LightSystem;
	class ParticleManager;
	class SoundSystem;

	class GammaEngineAPI Engine final : public Singleton<Engine>
	{
	public:
		Engine();
		~Engine();

	public:
		void Initialize();
		bool Frame();

	private:
		ObjectManager* objectManager_;
		SceneManager* sceneManager_;
		GamepadManager* gamepadManager_;
		Input* input_;
		Timer* timer_;
		Debug* debug_;
		GraphicSystem* graphic_;
		CollisionSystem* collisionSystem_;
		ParticleManager* particleManager_;
		LightSystem* lightSystem_;
		SoundSystem* soundSystem_;
	};
}
