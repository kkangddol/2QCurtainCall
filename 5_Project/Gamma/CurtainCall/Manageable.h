#pragma once
class Manageable
{
public:
	Manageable();

	/// <summary>
	/// ������ ������Ʈ�� ������ ���¸� ��ȯ�ϴ� �Լ�
	/// </summary>
	virtual bool CheckStatus(int archIndex, int archDown, int archUp,
		int sound, int rainRatio, int skyIndex, int skyAppear,
		int actorDown, int actorUp, int actressDown, int actressUp) abstract;
};

