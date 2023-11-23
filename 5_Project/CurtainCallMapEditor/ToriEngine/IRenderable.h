#pragma once

/// <summary>
/// 모든 화면에 그려질 녀석들이 기본적으로 상속받을 인터페이스
/// 
/// 2022.12.13 강석원 집
/// </summary>
class IRenderable
{
public:
	virtual void Render() abstract;		// Render 함수
};
