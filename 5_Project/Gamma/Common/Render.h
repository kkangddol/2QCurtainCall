#pragma once
#include <windows.h>
#include <string>
#include "Type.h"
#include <unordered_map>

class Material {

public:
	vector4 pen;
	vector4 brush;
	float thickness;
public:
	Material(): pen(vector4(0, 0, 0, 1)), brush(vector4(0, 0, 0, 0)), thickness(1.f)
	{

	};

	Material(vector4 pen) : pen(pen), brush(vector4(0, 0, 0, 0)), thickness(1.f)
	{

	};

	Material(vector4 pen, vector4 brush, float thickness) : pen(pen), brush(brush), thickness(thickness)
	{

	};

};

enum class EffectId {
	ColorMatrixEffect,
	DiscreteTransferEffect,
	LinearTransferEffect,
	PremultiplyEffect,
	UnPremultiplyEffect,
	AlphaMaskEffect,
	ArithmeticCompositeEffect,
	ConvolveMatrixEffect,
	CrossFadeEffect,
	DirectionalBlurEffect,
	DisplacementMapEffect,
	CompositeEffect,
	DistantLightEffect,
	PointLightEffect,
	SpotLightEffect,
	BlendEffect,
	TintEffect,
	HighLightEffect
};

class IEffect
{
public:
	virtual EffectId GetId() abstract;
};

class RenderModule
{
public:
	virtual HRESULT Initialize(HWND hWnd) abstract;
	virtual void Release() abstract;
	virtual void BeginDraw() abstract;
	virtual void EndDraw() abstract;
public:
	virtual void Resize(int, int) abstract;
	virtual void DrawRectangle(vector2 size, Matrix3x3 matrix, Material* material) abstract;
	virtual void DrawPolygon(std::wstring name, Matrix3x3 matrix, Material* material) abstract;
	virtual void DrawEllipse(vector2 size, Matrix3x3 matrix, Material* material) abstract;
	virtual void DrawLine(vector2 start, vector2 end, Matrix3x3 matrix, Material* material) abstract;
	virtual void DrawTextBox(vector2 size, Matrix3x3 matrix, std::wstring text, std::wstring fontFamily, Material* material) abstract;
	virtual void DrawBitmap(std::wstring bitmap, vector2 size, Matrix3x3 matrix, Material* material, std::vector<IEffect*>* appliedEffect) abstract;
	virtual void DrawBitmap(std::wstring bitmap, vector2 originalSize, vector2 size, vector2 offset, Matrix3x3 matrix, Material* material, std::vector<IEffect*>* appliedEffect) abstract;
	virtual std::wstring LoadBitmapImage(std::wstring) abstract;
	virtual std::wstring MakePolygon(std::wstring, std::vector<vector2>) abstract;
	virtual vector2 GetBitmapSize(std::wstring) abstract;
};
