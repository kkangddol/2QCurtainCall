#pragma once

/// <summary>
/// 게임 엔진 class
/// </summary>

namespace GammaEngine
{
	class GammaEngineAPI SceneManager final
	{
	public: 
		friend class Engine;
		friend class ObjectManager;

	public:
		SceneManager();
		~SceneManager();

	public:
		void Initialize();
		void Update();
		static void AddScene(Scene* scene);
		static void LoadScene(std::string sceneName);
	
		static Scene* CreateScene(std::string);
		static Scene* GetCurrentScene();

	private:
		static std::unordered_map<std::string, Scene*>* sceneList;

	private:
		static Scene* currentScene;
		static Scene* nextScene;
	};
}
