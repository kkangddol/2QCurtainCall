#pragma once
#include <vector>
#include <string>

class RenderModule;
class Material;
class IEffect;

namespace GammaEngine
{
	class Renderer;
	/// <summary>
	/// Direct2D의 기본적인 기능을 포함하는 class
	/// </summary>
	class GammaEngineAPI GraphicSystem : public Singleton<GraphicSystem>
	{
	public:
		GraphicSystem();
		~GraphicSystem();

	public:
		void Initialize(HWND);
		void Frame();
		void Release();

	public:
		void Resize(int width, int height);

	public:
		static void DrawRectangle(vector2 size, Matrix3x3 matrix, Material* material);
		static void DrawPolygon(std::wstring name, Matrix3x3 matrix, Material* material);
		static void DrawEllipse(vector2 size, Matrix3x3 matrix, Material* material);
		static void DrawLine(vector2 start, vector2 end,Matrix3x3 matrix, Material* material);
		static void DrawTextBox(vector2 size, Matrix3x3 matrix, std::wstring text, std::wstring fontFamily, Material* material);
		static void DrawBitmap(std::wstring bitmap,vector2 size, Matrix3x3 matrix, Material* material, std::vector<IEffect*>* appliedEffects);
		static void DrawBitmap(std::wstring bitmap, vector2 originalSize, vector2 size, vector2 offset, Matrix3x3 matrix, Material* material, std::vector<IEffect*>* appliedEffects);
		static std::wstring LoadBitmapImage(std::wstring);
		static std::wstring MakePolygon(std::wstring, std::vector<vector2>);
		static vector2 GetBitmapSize(std::wstring);

	public:
		static RenderModule* render;

	public:
		std::vector<Renderer*>* renderComponentList;
	};
}


