#include "ToriD2D.h"

#define _USE_MATH_DEFINES
#include <math.h>

ToriD2D::ToriD2D()
	:hWnd_(NULL), D2DFactory_(nullptr), renderTarget_(nullptr), windowRect_(RECT()),
	DWriteFactory_(nullptr), textFormat_(nullptr),
	nowR_(-1), nowG_(-1), nowB_(-1), nowA_(-1)
{

}

ToriD2D::~ToriD2D()
{
}

/// <summary>
/// Direct2D 렌더러 초기화 함수
/// ClientRect 사이즈 받고,
/// Factory 만들고,
/// RenderTarget 생성한다.
/// 
/// 2022.12.12 강석원 집
/// </summary>
/// <param name="_hWnd"></param>
void ToriD2D::Initialize(const HWND& _hWnd)
{
	hWnd_ = _hWnd;
	HRESULT hr = S_OK;

	GetClientRect(hWnd_, &windowRect_);

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory_);
	if (SUCCEEDED(hr))
	{
		hr = CreateDeviceResources();
	}

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&imageFactory_));
	}

	if (SUCCEEDED(hr))
	{
		// 문자열 출력을 위한 Factory 객체를 생성한다.
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(DWriteFactory_),
			reinterpret_cast<IUnknown**>(&DWriteFactory_));
	}

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = DWriteFactory_->CreateTextFormat(
			L"Verdana",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15,
			L"", //locale
			&textFormat_
		);
	}

	//if (SUCCEEDED(hr))
	//{
	//	// Center the text horizontally and vertically.
	//	TextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	//	TextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	//}

	//문자열 색 지정
	renderTarget_->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f), &textBrush_);
}

void ToriD2D::Finalize()
{
	SafeRelease<ID2D1HwndRenderTarget>(&renderTarget_);
	SafeRelease<ID2D1Factory>(&D2DFactory_);
	SafeRelease<ID2D1SolidColorBrush>(&nowBrush_);
	SafeRelease<ID2D1SolidColorBrush>(&textBrush_);
}

void ToriD2D::Resize(int width, int height)
{
	HRESULT hr = renderTarget_->Resize(D2D1::SizeU(width, height));
	if (FAILED(hr))
		return;
}

void ToriD2D::BeginDraw()
{
	renderTarget_->BeginDraw();
	renderTarget_->Clear();
	//renderTarget_->Clear(D2D1::ColorF(D2D1::ColorF::Black));
}

void ToriD2D::EndDraw()
{
	HRESULT hr;
	hr = renderTarget_->EndDraw();
}

/// <summary>
/// 사각형을 그리는 함수
/// 사각형의 각 꼭짓점의 좌표를 받아서 D2D SetTransform을 활용해 그린다
/// 
/// 22.12.14 강석원 인재원
/// </summary>
void ToriD2D::DrawRectST(float left, float top, float right, float bottom,
	float posX, float posY, float eulerAngle, float scaleX, float scaleY)
{
	D2D1_RECT_F rectangle = D2D1::Rect(left, top, right, bottom);

	D2D1_SIZE_F scale;
	scale.height = scaleY;
	scale.width = scaleX;

	renderTarget_->SetTransform(
		D2D1::Matrix3x2F::Scale(scale) *
		D2D1::Matrix3x2F::Rotation(eulerAngle) *
		D2D1::Matrix3x2F::Translation(posX, posY)
	);

	renderTarget_->DrawRectangle(rectangle, nowBrush_);

	renderTarget_->SetTransform(D2D1::Matrix3x2F::Identity());
}

void ToriD2D::DrawRect(Vector2D size, Matrix3x3 matrix)
{
	D2D1_RECT_F rectangle;
	rectangle.left = -size.x / 2;
	rectangle.top = -size.y / 2;
	rectangle.right = size.x / 2;
	rectangle.bottom = size.y / 2;

	D2D1::Matrix3x2F t = D2D1::Matrix3x2F(matrix.m11, matrix.m12, matrix.m21, matrix.m22, matrix.m31, matrix.m32);
	renderTarget_->SetTransform(t);

	renderTarget_->DrawRectangle(rectangle, nowBrush_);

	renderTarget_->SetTransform(D2D1::Matrix3x2F::Identity());
}

/// <summary>
/// 원을 그리는 함수
/// 원의 반지름 및 중점을 받아서 D2D SetTransform을 활용해 그린다
/// 
/// 22.12.14 강석원 인재원
/// </summary>
void ToriD2D::DrawCircleST(float radius, float posX, float posY, float eulerAngle, float scaleX, float scaleY)
{
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(posX, posY), radius, radius);

	D2D1_SIZE_F scale;
	scale.height = scaleY;
	scale.width = scaleX;

	renderTarget_->SetTransform(
		D2D1::Matrix3x2F::Scale(scale) *
		D2D1::Matrix3x2F::Rotation(eulerAngle) *
		D2D1::Matrix3x2F::Translation(posX, posY)
	);

	renderTarget_->DrawEllipse(ellipse, nowBrush_);

	renderTarget_->SetTransform(D2D1::Matrix3x2F::Identity());
}

/// <summary>
/// 선을 그리는 함수
/// 선의 시작점 끝점 중점을 받아서 D2D SetTransform을 활용해 그린다
/// 
/// 22.12.14 강석원 인재원
/// </summary>
void ToriD2D::DrawLineST(float startX, float startY, float endX, float endY,
	float posX, float posY, float eulerAngle, float scaleX, float scaleY)
{
	D2D1_SIZE_F scale;
	scale.height = scaleY;
	scale.width = scaleX;

	renderTarget_->SetTransform(
		D2D1::Matrix3x2F::Scale(scale) *
		D2D1::Matrix3x2F::Rotation(eulerAngle) *
		D2D1::Matrix3x2F::Translation(posX, posY)
	);

	renderTarget_->DrawLine(
		D2D1::Point2F(startX, startY),
		D2D1::Point2F(endX, endY),
		nowBrush_
	);

	renderTarget_->SetTransform(D2D1::Matrix3x2F::Identity());
}

//void ToriD2D::DrawCircle(float centerX, float centerY, float rotation, float scaleX, float scaleY, float radius, int colorCode)
//{
//	HRESULT hr = S_OK;
//
//	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(centerX, centerY), radius, radius);
//
//	switch (colorCode)
//	{
//		case D2D1::ColorF::Green :
//		{
//			renderTarget_->DrawEllipse(ellipse, greenBrush_);
//		}
//		break;
//
//		case D2D1::ColorF::Red :
//		{
//			renderTarget_->DrawEllipse(ellipse, redBrush_);
//		}
//		break;
//
//		default:
//			break;
//	}
//
//	//D2D1_SIZE_F scale;
//	//scale.width = scaleX;
//	//scale.height = scaleY;
//
//	//RenderTarget_->SetTransform(
//	//	D2D1::Matrix3x2F::Scale(
//	//		scale,
//	//		D2D1::Point2F(centerX, centerY)) *
//	//	D2D1::Matrix3x2F::Rotation(
//	//		(float)(rotation * 180.0f / M_PI),
//	//		D2D1::Point2F(centerX, centerY))
//	//);
//
//	//RenderTarget_->DrawEllipse(ellipse, YellowBrush);
//
//	//RenderTarget_->SetTransform(D2D1::Matrix3x2F::Identity());
//}

void ToriD2D::DrawCircle(float centerX, float centerY, float rotation, float scaleX, float scaleY, float radius)
{
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(centerX, centerY), radius * scaleX, radius * scaleY);

	renderTarget_->DrawEllipse(ellipse, nowBrush_);
}

void ToriD2D::DrawCircle(float centerX, float centerY, float radius)
{
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(centerX, centerY), radius, radius);

	renderTarget_->DrawEllipse(ellipse, nowBrush_);
}

void ToriD2D::DrawText2D(const char* str, float left, float top, float r, float g, float b, float a)
{
	SafeRelease(&nowBrush_);
	renderTarget_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &textBrush_);

	wchar_t* wStr;
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	wStr = new WCHAR[strSize];
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wStr, strSize);

	renderTarget_->DrawTextW(wStr, lstrlen(wStr), textFormat_,
		D2D1::RectF(left, top, renderTarget_->GetSize().width, renderTarget_->GetSize().height), textBrush_);

	SafeRelease(&nowBrush_);
	renderTarget_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f)), &textBrush_);

	delete[] wStr;
}


void ToriD2D::DrawText2D(const char* str, float left, float top)
{
	wchar_t* wStr;
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	wStr = new WCHAR[strSize];
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wStr, strSize);

	renderTarget_->DrawTextW(wStr, lstrlen(wStr), textFormat_,
		D2D1::RectF(left, top, renderTarget_->GetSize().width, renderTarget_->GetSize().height), textBrush_);

	delete[] wStr;
}

// void ToriD2D::DrawText2D(const char* str, float sizeX, float sizeY, Matrix3x3 matrix, float r, float g, float b, float a)
// 	SafeRelease(&nowBrush_);
// {
// 	renderTarget_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &textBrush_);
// 
// 	wchar_t* wStr;
// 	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
// 	wStr = new WCHAR[strSize];
// 	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wStr, strSize);
// 
// 	D2D1::Matrix3x2F D2DMatrix(matrix.m11, matrix.m12, matrix.m21, matrix.m22, matrix.m31, matrix.m32);
// 	renderTarget_->SetTransform(D2DMatrix);
// 	renderTarget_->DrawTextW(wStr, lstrlen(wStr), textFormat_,
// 		D2D1::RectF(0, 0, sizeX, sizeY), textBrush_);
// 
// 	SafeRelease(&nowBrush_);
// 	renderTarget_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f)), &textBrush_);
// 
// 	delete[] wStr;
// }
// 
// void ToriD2D::DrawText2D(const char* str, float sizeX, float sizeY, Matrix3x3 matrix)
// {
// 	wchar_t* wStr;
// 	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
// 	wStr = new WCHAR[strSize];
// 	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wStr, strSize);
// 
// 	D2D1::Matrix3x2F D2DMatrix(matrix.m11, matrix.m12, matrix.m21, matrix.m22, matrix.m31, matrix.m32);
// 	renderTarget_->SetTransform(D2DMatrix);
// 	renderTarget_->DrawTextW(wStr, lstrlen(wStr), textFormat_,
// 		D2D1::RectF(0, 0, sizeX, sizeY), textBrush_);
// 
// 	SafeRelease(&nowBrush_);
// 	renderTarget_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f)), &textBrush_);
// 
// 	delete[] wStr;
// }

void ToriD2D::DrawText2D(const WCHAR* str, float left, float top)
{
	renderTarget_->DrawTextW(str, lstrlen(str), textFormat_,
		D2D1::RectF(left, top, renderTarget_->GetSize().width, renderTarget_->GetSize().height), textBrush_);
}

void ToriD2D::DrawText2D(const WCHAR* str, float left, float top, float right, float bottom)
{
	renderTarget_->DrawTextW(str, lstrlen(str), textFormat_,
		D2D1::RectF(left, top, right, bottom), textBrush_);
}

void ToriD2D::DrawText2D(std::wstring str, float sizeX, float sizeY, Matrix3x3 matrix, float r, float g, float b, float a)
{
	SafeRelease(&textBrush_);
	renderTarget_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &textBrush_);

	D2D1::Matrix3x2F D2DMatrix(matrix.m11, matrix.m12, matrix.m21, matrix.m22, matrix.m31, matrix.m32);
	renderTarget_->SetTransform(D2DMatrix);
	renderTarget_->DrawTextW(str.c_str(), str.length(), textFormat_,
		D2D1::RectF(0, 0, sizeX, sizeY), textBrush_);

	SafeRelease(&textBrush_);
	renderTarget_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f)), &textBrush_);
}

void ToriD2D::DrawText2D(std::wstring str, float sizeX, float sizeY, Matrix3x3 matrix)
{
	D2D1::Matrix3x2F D2DMatrix(matrix.m11, matrix.m12, matrix.m21, matrix.m22, matrix.m31, matrix.m32);
	renderTarget_->SetTransform(D2DMatrix);
	renderTarget_->DrawTextW(str.c_str(), str.length(), textFormat_,
		D2D1::RectF(0, 0, sizeX, sizeY), textBrush_);

	SafeRelease(&textBrush_);
	renderTarget_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f)), &textBrush_);
}

void ToriD2D::DrawLine(float startX, float startY, float endX, float endY)
{
	renderTarget_->DrawLine(D2D1::Point2F(startX, startY), D2D1::Point2F(endX, endY), nowBrush_);
}

void ToriD2D::DrawBitmap(std::wstring bitmap, Vector2D size, Matrix3x3 matrix)
{
	if (bitmapDictionary.find(bitmap) == bitmapDictionary.end())
	{
		return;
	}

	Vector2D orignalSize = GetBitmapSize(bitmap);
	D2D1::Matrix3x2F transformMatrix = D2D1::Matrix3x2F::Scale(size.x / orignalSize.x, size.y / orignalSize.y) * 
		D2D1::Matrix3x2F::Translation(-size.x / 2, -size.y / 2) * 
		D2D1::Matrix3x2F(matrix.m11, matrix.m12, matrix.m21, matrix.m22, matrix.m31, matrix.m32);

	renderTarget_->SetTransform(transformMatrix);
	renderTarget_->DrawBitmap(bitmapDictionary.at(bitmap));
	renderTarget_->SetTransform(D2D1::Matrix3x2F::Identity());
}

void ToriD2D::DrawBitmap(std::wstring bitmap, Vector2D originalSize, Vector2D size, Vector2D offset, Matrix3x3 matrix)
{
	D2D1_RECT_F srcRectangle;

	srcRectangle.left = offset.x;
	srcRectangle.top = offset.y;
	srcRectangle.right = offset.x + originalSize.x;
	srcRectangle.bottom = offset.y + originalSize.y;

	D2D1::Matrix3x2F transformMatrix = D2D1::Matrix3x2F::Translation(-size.x / 2 - offset.x, -size.y / 2 - offset.y) * 
		D2D1::Matrix3x2F(matrix.m11, matrix.m12, matrix.m21, matrix.m22, matrix.m31, matrix.m32);

	renderTarget_->SetTransform(transformMatrix);
	renderTarget_->DrawBitmap(bitmapDictionary.at(bitmap));
}

Vector2D ToriD2D::GetBitmapSize(std::wstring fileName)
{
	ID2D1Bitmap* bitmap = bitmapDictionary[fileName];
	D2D1_SIZE_F size;
	size.width = 0;
	size.height = 0;
	if (bitmapDictionary.find(fileName) != bitmapDictionary.end())
	{
		size = bitmap->GetSize();
	}

	return Vector2D(size.width, size.height);
}

std::wstring ToriD2D::LoadBitmapImage(std::wstring fileName)
{
	if (bitmapDictionary.find(fileName) != bitmapDictionary.end())
	{
		return fileName;
	}

	HRESULT hr;
	ID2D1Bitmap* bitmap;
	IWICBitmapDecoder* decoder = 0;
	IWICBitmapFrameDecode* frameDecode = 0;
	IWICFormatConverter* converter = 0;

	hr = imageFactory_->CreateDecoderFromFilename(fileName.c_str(), 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

	if (FAILED(hr))
	{
		return std::wstring();
	}


	hr = decoder->GetFrame(0, &frameDecode);

	if (FAILED(hr))
	{
		decoder->Release();
		return std::wstring();
	}


	hr = imageFactory_->CreateFormatConverter(&converter);

	if (FAILED(hr))
	{
		decoder->Release();
		return std::wstring();
	}

	hr = converter->Initialize(
		frameDecode,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		0, 0.0, WICBitmapPaletteTypeCustom
	);

	if (FAILED(hr))
	{
		decoder->Release();
		frameDecode->Release();
		converter->Release();
		return std::wstring();
	}

	hr = renderTarget_->CreateBitmapFromWicBitmap(converter, 0, &bitmap);
	//hr = deviceContext->CreateBitmapFromWicBitmap(converter, 0, &bitmap);

	bitmapDictionary.insert(make_pair(fileName, bitmap));

	decoder->Release();
	frameDecode->Release();
	converter->Release();
	return fileName;
}

void ToriD2D::SetBrushColor(float r, float g, float b, float a)
{
	if (nowR_ == r && nowG_ == g && nowB_ == b && nowA_ == a)
	{
		return;
	}

	SafeRelease(&nowBrush_);

	renderTarget_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &nowBrush_);
}

/// <summary>
/// Direct2D RenderTarget을 생성하는 함수
/// 
/// 2022.12.11 강석원 집
/// </summary>
HRESULT ToriD2D::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	hr = D2DFactory_->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd_,
			D2D1::SizeU(
				windowRect_.right - windowRect_.left,
				windowRect_.bottom - windowRect_.top)
			//D2D1_PRESENT_OPTIONS_IMMEDIATELY
		),
		&renderTarget_
	);
	return hr;
}
