#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

namespace GammaEngine
{
	class GameObject;

	/// <summary>
	/// 씬에 대한 class
	/// </summary>
	class GammaEngineAPI Scene final
	{
	public:
		Scene(std::string sceneName);
		~Scene();

	public:
		void Start();
		void Frame();
		void OnDestroy();
		void OnDisable();
		void OnEnable();
		void Enable();
		void Disable();
		void Add(GameObject* gameObject);		// 씬에 추가
		void Remove(GameObject* gameObject);	// 씬에서 제거


		/// <summary>
		/// CreateObject() 씬에게 오브젝트를 만들어달라고 요청한다.
		/// Initialize() 씬을 초기화 하는 callable을 호출한다.
		/// SetInitializer() 씬을 초기화하는 callable을 등록한다.
		/// 
		/// 2023/02/06 강석원 인재원
		/// </summary>
		GameObject* CreateObject();
		void Initialize();
		void SetInitializer(std::function<void()> initializer);
		std::string GetSceneName() const;

	private:
		std::function<void()>* initializer_;
		std::vector<GameObject*>* gameObjectList_;
		std::string* sceneName_;


#pragma region Deprecated
	public:
		void Hold(GameObject* obj);				// GameObject를 상속받는 개체를 씬에 묶어둠
		std::vector<GameObject*>* holdList;
#pragma endregion
	};

	
}
