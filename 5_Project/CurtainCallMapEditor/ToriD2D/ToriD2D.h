#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "Dwrite")
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#include <string>
#include <unordered_map>

#include "Matrix.h"
#include "Vector2D.h"

/// <summary>
/// D2D ������ Ŭ����
/// 
/// 2022.12.13 ������ ��
/// </summary>
class ToriD2D
{
public:
	ToriD2D();
	~ToriD2D();

	static ToriD2D& Instance()
	{
		static ToriD2D instance;
		return instance;
	}

	void Initialize(const HWND& _hWnd);	// hWnd�� ���޹޾� D2D�� �ʱ�ȭ
	void Finalize();

	void Resize(int width, int height);

	void BeginDraw();				// �������� �����ϱ����� ȣ���Ͽ� BeginDraw()�� Clear()�� ȣ��
	void EndDraw();					// �������� ������ ȣ���Ͽ� EndDraw()�� ȣ��

#pragma region PrimitiveDrawWithSetTransformInD2D
	void DrawRectST(float left, float top, float right, float bottom,
		float posX, float posY, float eulerAngle, float scaleX, float scaleY);
	void DrawRect(Vector2D size, Matrix3x3 matrix);
	void DrawCircleST(float radius, float posX, float posY, float eulerAngle, float scaleX, float scaleY);
	void DrawLineST(float startX, float startY, float endX, float endY,
		float posX, float posY, float eulerAngle, float scaleX, float scaleY);
#pragma endregion PrimitiveDrawWithSetTransformInD2D

#pragma region PrimitiveDraw
//	void DrawCircle(float centerX, float centerY, float rotation, float scaleX, float scaleY, float radius, int colorCode);
	void DrawCircle(float centerX, float centerY, float rotation, float scaleX, float scaleY, float radius);
	void DrawCircle(float centerX, float centerY, float radius);
	void DrawText2D(const char* str, float left, float top, float r, float g, float b, float a);
	void DrawText2D(const char* str,  float left, float top);
// 	void DrawText2D(const char* str, float sizeX, float sizeY, Matrix3x3 matrix, float r, float g, float b, float a);
// 	void DrawText2D(const char* str, float sizeX, float sizeY, Matrix3x3 matrix);
	void DrawText2D(const WCHAR* str,  float left, float top);
	void DrawText2D(const WCHAR* str, float left, float top, float right, float bottom);
	void DrawText2D(std::wstring str, float sizeX, float sizeY, Matrix3x3 matrix, float r, float g, float b, float a);
	void DrawText2D(std::wstring str, float sizeX, float sizeY, Matrix3x3 matrix);
	void DrawLine(float startX, float startY, float endX, float endY);
#pragma endregion PrimitiveDraw

	void DrawBitmap(std::wstring bitmap, Vector2D size, Matrix3x3 matrix);
	void DrawBitmap(std::wstring bitmap, Vector2D originalSize, Vector2D size, Vector2D offset, Matrix3x3 matrix);

	Vector2D GetBitmapSize(std::wstring fileName);

	std::wstring LoadBitmapImage(std::wstring fileName);


#pragma region NowBrush
	void SetBrushColor(float r, float g, float b, float a);
#pragma endregion NowBrush

private:
	HWND hWnd_;
	ID2D1Factory* D2DFactory_;
	ID2D1HwndRenderTarget* renderTarget_;
	IDWriteFactory* DWriteFactory_;
	IDWriteTextFormat* textFormat_;
	IDWriteFactory* writeFactory_;
	IWICImagingFactory* imageFactory_;

	ID2D1SolidColorBrush* nowBrush_ = nullptr; 
	ID2D1SolidColorBrush* textBrush_ = nullptr;

	float nowR_;
	float nowG_;
	float nowB_;
	float nowA_;

	RECT windowRect_;

	HRESULT CreateDeviceResources();

private:
	std::unordered_map<std::wstring, ID2D1Bitmap*> bitmapDictionary;

	template <class T> void SafeRelease(T** ppT);
};

template<class T>
inline void ToriD2D::SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}
