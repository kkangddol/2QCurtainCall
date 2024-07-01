#pragma once

/// <summary>
/// 게임 엔진 class
/// </summary>

namespace GammaEngine
{
	class GammaEngineAPI ObjectManager
	{
	public:
		friend class Engine;
	public:
		ObjectManager();
		~ObjectManager();

	public:
		static void Frame();

	public:
		static void Instantiate(GameObject* obj);//현재 씬에 새로운 오브젝트를 생성하는 함수
		static void Destroy(GameObject* obj);//현재 씬에 있는 오브젝트를 제거하는 함수

	private:
		static std::vector<GameObject*>* addBuffer;//오브젝트 생성을 위한 버퍼
		static std::vector<GameObject*>* removeBuffer;//제거될 오브젝트를 담은 버퍼
	};


	GammaEngineAPI void Instantiate(GameObject* obj);//현재 씬에 새로운 오브젝트를 생성하는 함수
	GammaEngineAPI void Destroy(GameObject* obj);//현재 씬에 있는 오브젝트를 제거하는 함수
	GammaEngineAPI bool CompareTag(GameObject* gameObject, std::string tag);//태그가 일치하면 true 반환
	GammaEngineAPI bool CompareTag(GameObject* gameObject, char* tag);//태그가 일치하면 true 반환
	GammaEngineAPI bool CompareTags(GameObject* gameObject, std::vector<std::string> tags);//태그가 하나라도 일치하면 true 반환
	GammaEngineAPI bool CompareTags(GameObject* gameObject, std::vector<char*> tags);//태그가 하나라도 일치하면 true 반환
}
