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
	/// ���� ������Ʈ class
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
		bool CompareTag(std::string tag);//�±װ� ��ġ�ϸ� true ��ȯ
		bool CompareTag(char* tag);//�±װ� ��ġ�ϸ� true ��ȯ
		bool CompareTags(std::vector<std::string> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ
		bool CompareTags(std::vector<char*> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ

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
		T* GetComponent(); //������Ʈ�� �ִ� ������Ʈ�� ������ ��ȯ
		template<typename T>
		void AddComponent(); //������Ʈ�� ���� �߰�
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
