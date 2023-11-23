#pragma once
class Manageable
{
public:
	Manageable();

	/// <summary>
	/// 각각의 리액턴트의 본인의 상태를 반환하는 함수
	/// </summary>
	virtual bool CheckStatus(int archIndex, int archDown, int archUp,
		int sound, int rainRatio, int skyIndex, int skyAppear,
		int actorDown, int actorUp, int actressDown, int actressUp) abstract;
};

