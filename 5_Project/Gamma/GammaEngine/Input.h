#pragma once

namespace GammaEngine
{
	/// <summary>
	/// Ű�� ���¸� ǥ���ϴ� enum Ÿ��
	/// </summary>
	enum class GammaEngineAPI KeyState {
		pressed,
		released,
		pressing,
		none
	};

	/// <summary>
	/// Ű���� �� ���콺 �Է��� ����ϴ� class
	/// </summary>
	class GammaEngineAPI Input : public Singleton<Input>
	{
	public:
		Input();
		~Input();

	public:
		void Initialize(HWND hwnd);
		void Frame();

	public:
		static bool GetKey(int key);//Ű�� ������ ���� true�� ��ȯ�ϴ� �Լ�
		static bool GetKeyDown(int key);//Ű�� �������� true�� ��ȯ�ϴ� �Լ�
		static bool GetKeyUp(int key);//Ű�� ���������� true�� ��ȯ�ϴ� �Լ�
		static bool GetMouseButton(int mouseBtn);//���콺�� ������ ���� true�� ��ȯ�ϴ� �Լ�
		static bool GetMouseButtonDown(int mouseBtn);//���콺�� �������� true�� ��ȯ�ϴ� �Լ�
		static bool GetMouseButtonUp(int mouseBtn);//���콺�� ���������� true�� ��ȯ�ϴ� �Լ�
		static vector2 GetMousePosition();//���콺�� ��ǥ�� ��ȯ�ϴ� �Լ�
		
	public:
		static HWND hWnd;
		static KeyState key[256];//���� Ű�� ���¸� ��ȯ�ϴ� ����
		static int mouse[3];
		static short mouseScrollDelta;
	};


}
