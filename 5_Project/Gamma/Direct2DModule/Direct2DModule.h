#pragma once

#if Direct2DModuleAPI_Exporting
#define Direct2DModuleAPI __declspec(dllexport)
#else
#define Direct2DModuleAPI __declspec(dllimport)
#endif
#include <windows.h>
#include <vector>
#include <string>
#include <d2d1.h>
#include <dxgi.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>
#include <dxgi1_2.h>
//#include <dwrite.h>
#include <dwrite_3.h>
#include <wincodec.h>
#include <wrl.h>
#include <d2d1effectauthor.h>
#include <d2d1effects_2.h>
#include <d2d1_2.h>
#include <d2d1_3.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <fstream>
#include <DirectXMath.h>

#include "GammaEffect.h"

using namespace DirectX;
using namespace D2D1;
using namespace Microsoft::WRL;


class Direct2DModuleAPI Direct2DModule : public RenderModule
{
public:
	Direct2DModule();
	~Direct2DModule();



public:
	virtual HRESULT Initialize(HWND hWnd);
	virtual void Release();
	virtual void BeginDraw();
	virtual void EndDraw();
	void CreateTextFormat(std::wstring fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, float fontSize);//새로운 폰트를 생성하는 함수
	virtual void Resize(int, int);
	virtual void DrawRectangle(vector2 size, Matrix3x3 matrix, Material* material);
	virtual void DrawPolygon(std::wstring name, Matrix3x3 matrix, Material* material);
	virtual void DrawEllipse(vector2 size, Matrix3x3 matrix, Material* material) ;
	virtual void DrawLine(vector2 start, vector2 end, Matrix3x3 matrix, Material* material);
	virtual void DrawTextBox(vector2 size, Matrix3x3 matrix, std::wstring text, std::wstring fontFamily, Material* material);
	virtual void DrawBitmap(std::wstring bitmap,vector2 size, Matrix3x3 matrix, Material* material, std::vector<IEffect*>* appliedEffect);
	virtual void DrawBitmap(std::wstring bitmap, vector2 originalSize,vector2 size, vector2 offset, Matrix3x3 matrix, Material* material, std::vector<IEffect*>* appliedEffect);
	virtual vector2 GetBitmapSize(std::wstring);
	


	virtual std::wstring LoadBitmapImage(std::wstring);
	virtual std::wstring LoadPixelShader(std::wstring);
	virtual std::wstring MakePolygon(std::wstring, std::vector<vector2>);

	void AddBrush(vector4);
	ID2D1SolidColorBrush* UseBrush(vector4);

	void ApplyAllEffect(std::wstring bitmap, std::vector<IEffect*>* appliedEffect);
	void ApplyColorMatrixEffect(ColorMatrixEffect*);
	void ApplyAlphaMaskEffect(AlphaMaskEffect*);
	void ApplyConvolveMatrixEffect(ConvolveMatrixEffect*);
	void ApplyCrossFadeEffect(CrossFadeEffect*);
	void ApplyArithmeticCompositeEffect(ArithmeticCompositeEffect*);
	void ApplyDiscreteTransferEffect(DiscreteTransferEffect*);
	void ApplyLinearTransferEffect(LinearTransferEffect*);
	void ApplyPremultiplyEffect(PremultiplyEffect*);
	void ApplyUnPremultiplyEffect(UnPremultiplyEffect*);
	void ApplyDirectionalBlurEffect(DirectionalBlurEffect*);
	void ApplyDisplacementMapEffect(DisplacementMapEffect*);
	void ApplyCompositeEffect(CompositeEffect*);

	void ApplyDistantLightEffect(DistantLightEffect*);
	void ApplyPointLightEffect(PointLightEffect*);
	void ApplySpotLightEffect(SpotLightEffect*);
	void ApplyHighLightEffect(HighLightEffect*);
	void ApplyTintEffect(TintEffect*);

public:
	ID2D1Factory2* factory;
	IDWriteFactory* writeFactory;
	IDWriteFactory5* pDWriteFactory;
	IDWriteFontSetBuilder1* pFontSetBuilder;
	IDWriteFontFile* pFontFile;
	IDWriteFontSet* pFontSet;
	IDWriteFontCollection1* m_pdwFontCollection;
	IWICImagingFactory* imageFactory;
	static ID2D1DeviceContext* deviceContext;
	static ComPtr<ID3D11Device> device3D;
	static ComPtr<ID3D11DeviceContext> context3D;
	static ComPtr<IDXGISwapChain1> swapChain;
	ComPtr<ID2D1Device> device2D;
public:
	std::unordered_map<std::wstring, IDWriteTextFormat*>* textFormatDictionary;
	std::unordered_map<std::wstring, ID2D1Bitmap*>* bitmapDictionary;
	std::unordered_map<std::wstring, ID2D1PathGeometry*>* polygonDictionary;
	std::unordered_map<std::wstring, ID3D11PixelShader*>* pixelShaderDictionary;
	std::unordered_map<vector4, ID2D1SolidColorBrush*>* brushDictionary;

public:
	ComPtr<ID2D1Effect> combine;
	int lightBlendMode;
	int mixBlendMode;
};


extern "C" Direct2DModuleAPI RenderModule*  CreateRenderModule();