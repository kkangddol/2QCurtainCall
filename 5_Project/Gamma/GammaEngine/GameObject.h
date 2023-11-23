#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif



namespace GammaEngine 
{
	class Component;

	/// <summary>
	/// 게임 오브젝트 class
	/// </summary>
	class GammaEngineAPI GameObject
	{
	public:
		GameObject();
		GameObject(const GameObject& obj);
		~GameObject();

	public:
		void Start();
		void Update();
		void LateUpdate();
		void OnDestroy();
		void OnDisable();
		void OnEnable();
		void OnCollisionEnter(CollisionResponse response);
		void OnCollisionStay(CollisionResponse response);
		void OnCollisionExit(CollisionResponse response);
		bool CompareTag(std::string tag);//태그가 일치하면 true 반환
		bool CompareTag(char* tag);//태그가 일치하면 true 반환
		bool CompareTags(std::vector<std::string> tags);//태그가 하나라도 일치하면 true 반환
		bool CompareTags(std::vector<char*> tags);//태그가 하나라도 일치하면 true 반환

		void Enable();
		void Disable();

	public:
		Transform* transform;
		std::string* tag;
		bool isStarted = false;
		bool isEnabled = true;

	public:
		std::vector<Component*>* componentList;

	public:
		template<typename T>
		T* GetComponent(); //오브젝트에 있는 컴포넌트의 참조를 반환
		template<typename T>
		void AddComponent(); //오브젝트를 새로 추가
	};

	template<typename T>
	T* GameObject::GetComponent()
	{
		for (auto& comp : *componentList)
		{
			T* result = dynamic_cast<T*>(comp);
			auto name1 = typeid(T*).name();
			auto name2 = typeid(result).name();
			if (result && strcmp(name1, name2) == 0)
			{
				return result;
			}
		}
		return nullptr;
	}

	template<typename T>
	void GameObject::AddComponent()
	{
		T* newComponent = new T(this);
		componentList->push_back(newComponent);
	}
}
