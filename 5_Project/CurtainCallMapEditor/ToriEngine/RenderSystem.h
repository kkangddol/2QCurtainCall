#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <map>

#include "Vector2D.h"

class ToriD2D;
class Renderer;
class Scene;
class Matrix3x3;

/// <summary>
/// Render클래스들을 실행시킬 System 클래스
///
/// 
/// 22.12.27 강석원 인재원
/// </summary>
class RenderSystem
{
public:
	~RenderSystem() {};

	static RenderSystem& Instance()
	{
		static RenderSystem instance;
		return instance;
	}

private:
	RenderSystem();

public:
	void Initialize(const HWND& hWnd);
	void Finalize();

public:
	void Render(Scene* currentScene, Scene* UIScene);
	void AddList(Scene* nowScene, Renderer* const val);
	void RemoveList(Scene* nowScene, Renderer* const val);
	void Resize(int width, int height);

private:
	void RenderScene(Scene* scene);

public:
	static void SetBrushColor(float r, float g, float b, float a);

public:
	static void DrawRect(Vector2D size, Matrix3x3 matrix);
	static void DrawCircle(float centerX, float centerY, float radius);
	static void DrawText2D(const char* str, float left, float top, float r, float g, float b, float a);
	static void DrawText2D(std::wstring str, float sizeX, float sizeY, Matrix3x3 matrix);
	static void DrawLine(float startX, float startY, float endX, float endY);
	static void DrawBitmap(std::wstring bitmap, Vector2D size, Matrix3x3 matrix);
	static void DrawBitmap(std::wstring bitmap, Vector2D originalSize, Vector2D size, Vector2D offset, Matrix3x3 matrix);
	static std::wstring LoadBitmapImage(std::wstring fileName);
	static Vector2D GetBitmapSize(std::wstring fileName);

public:
	ToriD2D* GetGraphicModule();

private:
	static ToriD2D* graphicModule_;
	std::map<Scene*, std::vector<Renderer*>> renderList_;
};

