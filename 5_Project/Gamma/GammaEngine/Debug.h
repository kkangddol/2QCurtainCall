#pragma once
#include <vector>

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

class RenderModule;
class Material;

namespace GammaEngine
{
	struct DebugShape
	{
		Material* material;
		DebugShape(Material*  material) : material(material)
		{

		}
	};

	struct DebugText : public DebugShape
	{
		vector2 size;
		Matrix3x3 matrix;
		std::wstring text;
		std::wstring fontFamily;

		DebugText(vector2 size, Matrix3x3 matrix, std::wstring text, std::wstring fontFamily, Material* material) :
			DebugShape(material),
			size(size),
			matrix(matrix),
			text(text),
			fontFamily(fontFamily) {};
	};

	struct DebugRect : public DebugShape
	{
		vector2 size;
		Matrix3x3 matrix;
		DebugRect( vector2 size, Matrix3x3 matrix, Material* material) :
			DebugShape(material),
			size(size),
			matrix(matrix) { };
	};

	struct DebugEllipse : public DebugShape
	{
		vector2 size;
		Matrix3x3 matrix;
		DebugEllipse(vector2 pos, Matrix3x3 matrix,  Material* material): 
			DebugShape(material),
			size(size),
			matrix(matrix) { };
	};

	struct DebugLine: public DebugShape
	{
		vector2 start;
		vector2 end;
		Matrix3x3 matrix;
		DebugLine(vector2 start, vector2 end,Matrix3x3 matrix, Material* material):
			DebugShape(material),
			start(start),
			end(end),
			matrix(matrix) { };
	};

	/// <summary>
	/// 디버그용 클래스
	/// </summary>
	/// 
	/// #ifdef GammaEngineAPI_Exporting
	class GammaEngineAPI Debug
	{
	public:
		friend class GraphicSystem;

	public:
		Debug();
		~Debug();

	private:
		static void Render();

	public:
		static void DrawRectangle(vector2 size, vector2 pos, float rotation, vector4 color = vector4(0, 0, 0, 1));
		static void DrawEllipse(vector2 size, vector2 pos, float rotation, vector4 color = vector4(0, 0, 0, 1));
		static void DrawLine(vector2 start, vector2 end, Matrix3x3 matrix, vector4 color);
		static void DrawTextToWorld(vector2 size, vector2 pos, std::wstring text, std::wstring fontFamily, vector4 color = vector4(0,0,0,1));
		static void DrawTextToScreen(vector2 size, vector2 pos, std::wstring text, std::wstring fontFamily, vector4 color = vector4(0, 0, 0, 1));
		static Material* GetMaterial(vector4 color);
	public:
		static std::unordered_map<vector4,Material*>* material;
		static std::vector<DebugRect*>* rect;
		static std::vector<DebugEllipse*>* ellipse;
		static std::vector<DebugLine*>* line;
		static std::vector<DebugText*>* textBox;

	public:
		static void SetDebugMode(bool mode);
		static void SetDebugMode();

	private:
		static bool isDebugMode_;
	};
}