#pragma once
#include <unordered_map>
#include <string>

class Scene;

/// <summary>
/// 씬을 생성하고 생성자로 이름을 붙여 관리
/// 
/// 2022.12.13 강석원 집
/// </summary>
class SceneSystem
{
public:
	~SceneSystem();

	// 싱글턴
	static SceneSystem& Instance()
	{
		static SceneSystem instance;
		return instance;
	}

	void Initialize();							// SceneManager를 초기화
	void Finalize();

	Scene& CreateScene(const std::string& sceneName);	// 새로운 Scene을 생성하고 이름을 부여합니다.

	/// EventSystem에게 적용을 맡기는 함수들.


	/// 실시간으로 바로 적용시키는 함수들.
	Scene* GetCurrentScene() const;					// 현재 Scene의 주소를 반환합니다.
	Scene* SetCurrentScene(const std::string& sceneName);	// 현재 Scene을 인자로 넘어온 이름의 Scene으로 변경합니다.
	Scene* SetCurrentScene(Scene* scene);				// 현재 Scene을 인자로 넘어온 Scene으로 변경합니다.

	Scene* GetUIScene() const;
	Scene* SetUIScene(const std::string& sceneName);
	Scene* SetUIScene(Scene* scene);

private:
	SceneSystem();
	SceneSystem(const SceneSystem&) = delete;
	SceneSystem& operator=(const SceneSystem&) = delete;

	Scene* currentScene_;				// 현재 Scene
	Scene* UIScene_;					// UI Scene

	std::unordered_map<std::string, Scene*> sceneMap_;	// Scene Map
};

