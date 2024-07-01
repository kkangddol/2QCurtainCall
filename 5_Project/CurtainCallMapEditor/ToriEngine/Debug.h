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
/// ����׿� ������ (�ݶ��̴�)�� ����ϱ� ���� Ŭ����
/// Core���� ȣ��ȴ�?
/// </summary>
class Debug
{
public:
	Debug();
	~Debug();

public:
	/// ObjectSystem�� ���� ���� ������Ʋ ����Ʈ�� �޾ƿ�
	/// �ݶ��̴� ������ �� ��
	/// ���� �ݶ��̴� ���¿� �°� �׸��°� ��û�Ѵ�.
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