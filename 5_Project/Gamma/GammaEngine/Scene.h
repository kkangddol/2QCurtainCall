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
	/// ���� ���� class
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
		void Add(GameObject* gameObject);		// ���� �߰�
		void Remove(GameObject* gameObject);	// ������ ����


		/// <summary>
		/// CreateObject() ������ ������Ʈ�� �����޶�� ��û�Ѵ�.
		/// Initialize() ���� �ʱ�ȭ �ϴ� callable�� ȣ���Ѵ�.
		/// SetInitializer() ���� �ʱ�ȭ�ϴ� callable�� ����Ѵ�.
		/// 
		/// 2023/02/06 ������ �����
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
		void Hold(GameObject* obj);				// GameObject�� ��ӹ޴� ��ü�� ���� �����
		std::vector<GameObject*>* holdList;
#pragma endregion
	};

	
}
