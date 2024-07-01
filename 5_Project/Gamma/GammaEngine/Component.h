#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif
#include <vector>

namespace GammaEngine {
	class GameObject;
	class Transform;
	struct CollisionResponse;

	/// <summary>
	/// ÄÄÆ÷³ÍÆ® class
	/// </summary>
	class GammaEngineAPI Component
	{
	public:
		Component(GameObject* g);
		virtual ~Component();

	public:
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		virtual void OnDestroy();
		virtual void OnDisable();
		virtual void OnEnable();
		virtual void OnCollisionEnter(CollisionResponse response);
		virtual void OnCollisionStay(CollisionResponse response);
		virtual void OnCollisionExit(CollisionResponse response);
	public:
		template<typename T>
		T* GetComponent();
		template<typename T>
		void AddComponent();

	private:
		std::vector<Component*>& componentList;

	public:
		GameObject* gameObject;
		Transform* transform;
		bool isEnabled;
	};

	template<typename T>
	T* Component::GetComponent()
	{

		for (auto& comp : componentList)
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
	void Component::AddComponent()
	{
		T* newComponent = new T(this->gameObject);
		componentList.push_back(newComponent);
	}

}
