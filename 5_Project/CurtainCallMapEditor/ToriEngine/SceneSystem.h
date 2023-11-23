#pragma once
#include <unordered_map>
#include <string>

class Scene;

/// <summary>
/// ���� �����ϰ� �����ڷ� �̸��� �ٿ� ����
/// 
/// 2022.12.13 ������ ��
/// </summary>
class SceneSystem
{
public:
	~SceneSystem();

	// �̱���
	static SceneSystem& Instance()
	{
		static SceneSystem instance;
		return instance;
	}

	void Initialize();							// SceneManager�� �ʱ�ȭ
	void Finalize();

	Scene& CreateScene(const std::string& sceneName);	// ���ο� Scene�� �����ϰ� �̸��� �ο��մϴ�.

	/// EventSystem���� ������ �ñ�� �Լ���.


	/// �ǽð����� �ٷ� �����Ű�� �Լ���.
	Scene* GetCurrentScene() const;					// ���� Scene�� �ּҸ� ��ȯ�մϴ�.
	Scene* SetCurrentScene(const std::string& sceneName);	// ���� Scene�� ���ڷ� �Ѿ�� �̸��� Scene���� �����մϴ�.
	Scene* SetCurrentScene(Scene* scene);				// ���� Scene�� ���ڷ� �Ѿ�� Scene���� �����մϴ�.

	Scene* GetUIScene() const;
	Scene* SetUIScene(const std::string& sceneName);
	Scene* SetUIScene(Scene* scene);

private:
	SceneSystem();
	SceneSystem(const SceneSystem&) = delete;
	SceneSystem& operator=(const SceneSystem&) = delete;

	Scene* currentScene_;				// ���� Scene
	Scene* UIScene_;					// UI Scene

	std::unordered_map<std::string, Scene*> sceneMap_;	// Scene Map
};

