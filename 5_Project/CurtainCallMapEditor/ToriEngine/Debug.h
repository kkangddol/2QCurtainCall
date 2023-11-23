#pragma once
#include <vector>
#include <string>

#include "Matrix.h"
#include "Vector2D.h"

struct DebugText
{
	DebugText(std::wstring pText, Vector2D pSize, Matrix3x3 pMatrix)
		: text(pText), size(pSize), matrix(pMatrix)
	{

	}

	std::wstring text;
	Vector2D size;
	Matrix3x3 matrix;
};

struct DebugRect
{
	DebugRect(Vector2D pSize, Matrix3x3 pMatrix, float r, float g, float b, float a)
		: size(pSize), matrix(pMatrix),
		r(r), g(g), b(b), a(a)
	{

	}

	Vector2D size;
	Matrix3x3 matrix;
	float r;
	float g;
	float b;
	float a;
};

/// <summary>
/// 디버그용 데이터 (콜라이더)를 출력하기 위한 클래스
/// Core에서 호출된다?
/// </summary>
class Debug
{
public:
	Debug();
	~Debug();

public:
	/// ObjectSystem에 현재 씬의 오브젝틀 리스트를 받아와
	/// 콜라이더 정보를 얻어낸 뒤
	/// 각각 콜라이더 형태에 맞게 그리는걸 요청한다.
	static void BruteRender();
	static void Render();

public:
	static void DrawTextToWorld(std::wstring text, Vector2D size, Vector2D pos);
	static void DrawTextToScreen(std::wstring text, Vector2D size, Vector2D pos);
	static void DrawRectangleWorld(Vector2D size, Vector2D pos, float rotation, float r, float g, float b, float a);
	static void DrawRectangleScreen(Vector2D size, Vector2D pos, float rotation, float r, float g, float b, float a);

	static void SetDebugMode(bool isDebug)
	{
		isDebugMode_ = isDebug;
	}

	static bool GetDebugMode()
	{
		return isDebugMode_;
	}

private:
	static bool isDebugMode_;
	static std::vector<DebugText*> textBoxes;
	static std::vector<DebugRect*> rects;
};