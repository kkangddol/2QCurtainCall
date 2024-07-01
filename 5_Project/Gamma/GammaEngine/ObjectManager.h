#pragma once

/// <summary>
/// ���� ���� class
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
		static void Instantiate(GameObject* obj);//���� ���� ���ο� ������Ʈ�� �����ϴ� �Լ�
		static void Destroy(GameObject* obj);//���� ���� �ִ� ������Ʈ�� �����ϴ� �Լ�

	private:
		static std::vector<GameObject*>* addBuffer;//������Ʈ ������ ���� ����
		static std::vector<GameObject*>* removeBuffer;//���ŵ� ������Ʈ�� ���� ����
	};


	GammaEngineAPI void Instantiate(GameObject* obj);//���� ���� ���ο� ������Ʈ�� �����ϴ� �Լ�
	GammaEngineAPI void Destroy(GameObject* obj);//���� ���� �ִ� ������Ʈ�� �����ϴ� �Լ�
	GammaEngineAPI bool CompareTag(GameObject* gameObject, std::string tag);//�±װ� ��ġ�ϸ� true ��ȯ
	GammaEngineAPI bool CompareTag(GameObject* gameObject, char* tag);//�±װ� ��ġ�ϸ� true ��ȯ
	GammaEngineAPI bool CompareTags(GameObject* gameObject, std::vector<std::string> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ
	GammaEngineAPI bool CompareTags(GameObject* gameObject, std::vector<char*> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ
}
