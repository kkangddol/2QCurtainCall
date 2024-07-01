#pragma comment (lib, "user32.lib")
#pragma comment(lib, "dxgi.lib") 
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "dxguid.lib")


#include "Type.h"
#include "Render.h"
#include "Direct2DModule.h"
#include "Util.h"


using namespace D2D1;
using namespace Microsoft::WRL;

ID2D1DeviceContext* Direct2DModule::deviceContext = 0;
ComPtr<ID3D11DeviceContext>  Direct2DModule::context3D = 0;
ComPtr<ID3D11Device> Direct2DModule::device3D = 0;
ComPtr<IDXGISwapChain1> Direct2DModule::swapChain;


Direct2DModule::Direct2DModule()
{
	factory = 0;
	writeFactory = 0;
	imageFactory = 0;
	textFormatDictionary = new std::unordered_map<std::wstring, IDWriteTextFormat*>();
	bitmapDictionary = new std::unordered_map<std::wstring, ID2D1Bitmap*>();
	polygonDictionary = new std::unordered_map<std::wstring, ID2D1PathGeometry*>();
	brushDictionary = new std::unordered_map<vector4, ID2D1SolidColorBrush*>();
	pixelShaderDictionary = new std::unordered_map<std::wstring, ID3D11PixelShader*>();
	mixBlendMode = D2D1_BLEND_MODE_COLOR;
	lightBlendMode = D2D1_BLEND_MODE_COLOR_DODGE;


	//mixBlendMode = D2D1_BLEND_MODE_SOFT_LIGHT;
	//mixBlendMode = D2D1_BLEND_MODE_OVERLAY;
	//mixBlendMode = D2D1_BLEND_MODE_COLOR;
	// 
	//lightBlendMode = D2D1_BLEND_MODE_SOFT_LIGHT;
}

Direct2DModule::~Direct2DModule()
{

}

RenderModule* CreateRenderModule()
{
	return new Direct2DModule();
}

HRESULT Direct2DModule::Initialize(HWND hWnd)
{

	if (S_OK == D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory))
	{
		// This flag adds support for surfaces with a different color channel ordering than the API default.
		// You need it for compatibility with Direct2D.
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		// This array defines the set of DirectX hardware feature levels this app  supports.
		// The ordering is important and you should  preserve it.
		// Don't forget to declare your app's minimum required feature level in its
		// description.  All apps are assumed to support 9.1 unless otherwise stated.
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		// Create the DX11 API device object, and get a corresponding context.



		D3D11CreateDevice(
			nullptr,                    // specify null to use the default adapter
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,              // optionally set debug and Direct2D compatibility flags
			featureLevels,              // list of feature levels this app can support
			ARRAYSIZE(featureLevels),   // number of possible feature levels
			D3D11_SDK_VERSION,
			&device3D,                    // returns the Direct3D device created
			nullptr,            // returns feature level of device created
			&context3D                   // returns the device immediate context
		);

		ComPtr<IDXGIDevice> dxgiDevice;

		device3D.As(&dxgiDevice);

		factory->CreateDevice(dxgiDevice.Get(), &device2D);


		device2D->CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&deviceContext
		);
		// Allocate a descriptor.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		swapChainDesc.Width = 0;                           // use automatic sizing
		swapChainDesc.Height = 0;
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // this is the most common swapchain format
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;                // don't use multi-sampling
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;                     // use double buffering to enable flip
		swapChainDesc.Scaling = DXGI_SCALING_NONE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all apps must use this SwapEffect
		swapChainDesc.Flags = 0;
		// Identify the physical adapter (GPU or card) this device is runs on.
		ComPtr<IDXGIAdapter> dxgiAdapter;

		dxgiDevice->GetAdapter(&dxgiAdapter);

		// Get the factory object that created the DXGI device.
		ComPtr<IDXGIFactory2> dxgiFactory;
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
		IUnknown* _window = nullptr;
		// Get the final swap chain for this window from the DXGI factory.

		HRESULT hr = dxgiFactory->CreateSwapChainForHwnd(
			device3D.Get(),
			hWnd,
			&swapChainDesc,
			NULL,
			nullptr,    // allow on all displays
			&swapChain
		);

		// Ensure that DXGI doesn't queue more than one frame at a time.
		//dxgiDevice->SetMaximumFrameLatency(1);


		// Get the backbuffer for this window which is be the final 3D render target.
		ID3D11Texture2D* backBuffer;
		swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

		D2D1_BITMAP_PROPERTIES1 bitmapProperties =
			BitmapProperties1(
				D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
				PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
				1920,
				1080
			);

		// Direct2D needs the dxgi version of the backbuffer surface pointer.
		ComPtr<IDXGISurface> dxgiBackBuffer;
		ComPtr<ID2D1Bitmap1> targetBitmap;
		swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));

		// Get a D2D surface from the DXGI back buffer to use as the D2D render target.
		deviceContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer.Get(),
			&bitmapProperties,
			&targetBitmap
		);


		// Now we can set the Direct2D render target.
		deviceContext->SetTarget(targetBitmap.Get());

		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory5),
			reinterpret_cast<IUnknown**>(&pDWriteFactory)
		);
		// 
		// 		if (SUCCEEDED(hr))
		// 		{
		// 			hr = pDWriteFactory->CreateFontSetBuilder(&pFontSetBuilder);
		// 		}
		// 
		// 		std::wstring pFilePath = L"Resources\\Font\\¶¥½ººÎ´ëÂî°³OTF Bold.otf";
		// 
		// 		if (SUCCEEDED(hr))
		// 		{
		// 			hr = pDWriteFactory->CreateFontFileReference(L"Resources\\Font\\¶¥½ººÎ´ëÂî°³OTF Bold.otf", /* lastWriteTime*/ nullptr, &pFontFile);
		// 		}
		// 
		// 		hr = pFontSetBuilder->AddFontFile(pFontFile);
		// 
		// 		hr = pFontSetBuilder->CreateFontSet(&pFontSet);

		ComPtr<IDWriteFontFile> fontFileReference;

		pDWriteFactory->CreateFontFileReference(L"Resources\\Font\\¶¥½ººÎ´ëÂî°³OTF Bold.otf", nullptr, &fontFileReference);

		ComPtr<IDWriteFontSetBuilder1> fontSetBuilder;
		pDWriteFactory->CreateFontSetBuilder(&fontSetBuilder);

		fontSetBuilder->AddFontFile(fontFileReference.Get());

		ComPtr<IDWriteFontSet> customFontSet;
		fontSetBuilder->CreateFontSet(&customFontSet);

		pDWriteFactory->CreateFontCollectionFromFontSet(

			customFontSet.Get()

			, & m_pdwFontCollection

		);

		ComPtr<IDWriteFontFamily> fontFamily;
		ComPtr<IDWriteLocalizedStrings> localizedFontName;
		WCHAR c_styleFontName[65];

		m_pdwFontCollection->GetFontFamily(0, &fontFamily);
		fontFamily->GetFamilyNames(&localizedFontName);
		localizedFontName->GetString(0, c_styleFontName, 65);

		if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory)))
		{
			std::wstring font = (L"Ttangsbudaejjigae OTF");
			CreateTextFormat(font, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30);
		}

		if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory)))
		{
			std::wstring font = (L"Verdana");
			CreateTextFormat(font, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30);
		}
		if (S_OK == CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&imageFactory)))
		{

		}
	}
	return 0;
}

void Direct2DModule::BeginDraw()
{
	deviceContext->BeginDraw();
	deviceContext->Clear(ColorF(1, 1, 1));
}

void Direct2DModule::EndDraw()
{
	deviceContext->EndDraw();
	DXGI_PRESENT_PARAMETERS parameter = { 0, NULL, NULL, NULL };
	swapChain->Present1(1, 0, &parameter);
}

void Direct2DModule::CreateTextFormat(std::wstring fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, float fontSize)
{
	IDWriteTextFormat* result;

	writeFactory->CreateTextFormat(fontFamilyName.c_str(), NULL, fontWeight, fontStyle, fontStretch, fontSize, L"", &result);
	result->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	textFormatDictionary->insert(make_pair(fontFamilyName, result));
}

void Direct2DModule::Release()
{
	for (auto& textFormat : *textFormatDictionary)
	{
		if(textFormat.second)
			textFormat.second->Release();
	}

	for (auto& bitmap : *bitmapDictionary)
	{
		bitmap.second->Release();
	}

	for (auto& brush : *brushDictionary)
	{
		brush.second->Release();
	}
	textFormatDictionary->clear();
	brushDictionary->clear();
	bitmapDictionary->clear();
	writeFactory->Release();
	imageFactory->Release();
	factory->Release();
}

void Direct2DModule::Resize(int width, int height)
{
	UINT newBufferCount = 2;
	DXGI_MODE_DESC newBufferDesc;
	newBufferDesc.Width = width;
	newBufferDesc.Height = height;
	newBufferDesc.RefreshRate.Numerator = 60;
	newBufferDesc.RefreshRate.Denominator = 1;
	newBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	newBufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	newBufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	HRESULT hr = swapChain->ResizeBuffers(
		newBufferCount,
		newBufferDesc.Width,
		newBufferDesc.Height,
		newBufferDesc.Format,
		0
	);
	if (FAILED(hr))
		return;
}

std::wstring Direct2DModule::LoadBitmapImage(std::wstring filename)
{
	if ((*bitmapDictionary).find(filename) != (*bitmapDictionary).end())
	{
		return filename;
	}
	HRESULT hr;
	ID2D1Bitmap* bitmap;
	IWICBitmapDecoder* decoder = 0;
	IWICBitmapFrameDecode* frameDecode = 0;
	IWICFormatConverter* converter = 0;

	hr = imageFactory->CreateDecoderFromFilename(filename.c_str(), 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

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


	hr = imageFactory->CreateFormatConverter(&converter);

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


	hr = deviceContext->CreateBitmapFromWicBitmap(converter, 0, &bitmap);

	bitmapDictionary->insert(make_pair(filename, bitmap));

	decoder->Release();
	frameDecode->Release();
	converter->Release();
	return filename;
}

void Direct2DModule::AddBrush(vector4 color)
{
	ID2D1SolidColorBrush* brush;
	deviceContext->CreateSolidColorBrush(ColorF(color.x, color.y, color.z, color.w), (ID2D1SolidColorBrush**)&brush);
	brushDictionary->insert(std::make_pair(color, brush));
}

ID2D1SolidColorBrush* Direct2DModule::UseBrush(vector4 color)
{
	if (brushDictionary->find(color) == brushDictionary->end())
	{
		AddBrush(color);
	}
	ID2D1SolidColorBrush* brush = (*brushDictionary)[color];
	return brush;
}


vector2 Direct2DModule::GetBitmapSize(std::wstring filename)
{
	ID2D1Bitmap* bitmap = (*bitmapDictionary)[filename];
	D2D1_SIZE_F size;
	size.width = 0;
	size.height = 0;
	if (bitmap)
	{
		size = bitmap->GetSize();
	}

	return vector2(size.width, size.height);
}

std::wstring Direct2DModule::MakePolygon(std::wstring name, std::vector<vector2> points)
{
	ID2D1PathGeometry* polygon;
	ID2D1GeometrySink* pSink = NULL;
	HRESULT hr = factory->CreatePathGeometry(&polygon);
	std::vector<D2D1_POINT_2F> p;
	for (auto iter = points.begin(); iter != points.end(); iter++)
	{
		p.push_back({ (*iter).x,(*iter).y });
	}

	if (SUCCEEDED(hr))
	{
		hr = polygon->Open(&pSink);
		if (SUCCEEDED(hr))
		{
			pSink->BeginFigure(
				p[0],
				D2D1_FIGURE_BEGIN_FILLED
			);
			for (int i = 1; i < p.size(); i++)
			{
				pSink->AddLine(p[i]);
			}

			pSink->AddLine(p[0]);

			pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

			hr = pSink->Close();
		}
		pSink->Release();
		(*polygonDictionary).insert(make_pair(name, polygon));
	}
	return name;
}

std::wstring Direct2DModule::LoadPixelShader(std::wstring name)
{
	ComPtr<ID3DBlob> pShaderBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;

	TCHAR buffer[MAX_PATH];
	DWORD length = GetCurrentDirectory(MAX_PATH, buffer);
	const D3D_SHADER_MACRO defines[] =
	{
		"EXAMPLE_DEFINE", "1",
		NULL, NULL
	};


	HRESULT hr = D3DCompileFromFile(name.c_str(), nullptr, nullptr, "main", "ps_5_0", D3DCOMPILE_DEBUG, 0, &pShaderBlob, &errorBlob);

	if (FAILED(hr))
	{
		if (errorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
			errorBlob->Release();
		}
		return std::wstring();
	}
	// Create pixel shader
	ID3D11PixelShader* pPixelShader;
	device3D->CreatePixelShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), NULL, &pPixelShader);
	(*pixelShaderDictionary).insert(make_pair(name, pPixelShader));
	return name;
}

void Direct2DModule::DrawRectangle(vector2 size, Matrix3x3 matrix, Material* material)
{
	D2D1_RECT_F rectangle;
	rectangle.left = -size.x / 2;
	rectangle.top = -size.y / 2;
	rectangle.right = size.x / 2;
	rectangle.bottom = size.y / 2;
	Matrix3x2F t = Matrix3x2F(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]);
	deviceContext->SetTransform(t);

	deviceContext->DrawRectangle(rectangle, UseBrush(material->pen), material->thickness);
	deviceContext->FillRectangle(rectangle, UseBrush(material->brush));
	deviceContext->SetTransform(Matrix3x2F::Identity());
}

void Direct2DModule::DrawPolygon(std::wstring name, Matrix3x3 matrix, Material* material)
{
	Matrix3x2F t = Matrix3x2F(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]);
	deviceContext->SetTransform(t);
	deviceContext->DrawGeometry((*polygonDictionary)[name], UseBrush(material->pen), material->thickness);
	deviceContext->FillGeometry((*polygonDictionary)[name], UseBrush(material->brush));
	deviceContext->SetTransform(Matrix3x2F::Identity());
}

void Direct2DModule::DrawEllipse(vector2 size, Matrix3x3 matrix, Material* material)
{
	D2D1_ELLIPSE ellipse;

	ellipse.radiusX = size.x / 2;
	ellipse.radiusY = size.y / 2;
	ellipse.point.x = 0;
	ellipse.point.y = 0;

	Matrix3x2F t = Matrix3x2F(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]);
	deviceContext->SetTransform(t);

	deviceContext->DrawEllipse(ellipse, UseBrush(material->pen), material->thickness);
	deviceContext->FillEllipse(ellipse, UseBrush(material->brush));
	deviceContext->SetTransform(Matrix3x2F::Identity());
}

void Direct2DModule::DrawLine(vector2 start, vector2 end, Matrix3x3 matrix, Material* material)
{
	Matrix3x2F t = Matrix3x2F(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]);
	deviceContext->SetTransform(t);
	deviceContext->DrawLine(
		Point2F(start.x, start.y),
		Point2F(end.x, end.y),
		UseBrush(material->pen),
		material->thickness,
		nullptr
	);
	deviceContext->SetTransform(Matrix3x2F::Identity());
}

void Direct2DModule::DrawTextBox(vector2 size, Matrix3x3 matrix, std::wstring text, std::wstring fontFamily, Material* material)
{
	Matrix3x2F t = Matrix3x2F::Translation(-size.x / 2, -size.y / 2) * Matrix3x2F(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]);
	deviceContext->SetTransform(t);

	if ((*textFormatDictionary)[fontFamily])
	{
		deviceContext->DrawText(text.c_str(), (int)text.length(), (*textFormatDictionary)[fontFamily], RectF(0, 0, size.x, size.y), UseBrush(material->pen));
	}
	else
	{
		deviceContext->DrawText(text.c_str(), (int)text.length(), (*textFormatDictionary)[L"Verdana"], RectF(0, 0, size.x, size.y), UseBrush(material->pen));

	}
	deviceContext->SetTransform(Matrix3x2F::Identity());
	//IDWriteTextLayout* pTextLayout = nullptr;
	//writeFactory->CreateTextLayout(text.c_str(), (int)text.size(), (*textFormatDictionary)[fontFamily], 1000.0f, 1000.0f, &pTextLayout);
	//Matrix3x2F t = Matrix3x2F(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]);
	//deviceContext->SetTransform(t);
	//deviceContext->DrawTextLayout(Point2F(size.x / 2, size.y / 2), pTextLayout, (*brushDictionary)[material->brush]);
	//deviceContext->SetTransform(Matrix3x2F::Identity());
}

void Direct2DModule::DrawBitmap(std::wstring bitmap, vector2 size, Matrix3x3 matrix, Material* material, std::vector<IEffect*>* appliedEffect)
{
	vector2 orignalSize = GetBitmapSize(bitmap);
	ComPtr<ID2D1Effect> affineTransformEffect;
	Matrix3x2F t = Matrix3x2F::Scale(size.x / orignalSize.x, size.y / orignalSize.y) * Matrix3x2F::Translation(-size.x / 2, -size.y / 2) * Matrix3x2F(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]);
	deviceContext->CreateEffect(CLSID_D2D12DAffineTransform, &affineTransformEffect);
	affineTransformEffect->SetInput(0, (*bitmapDictionary)[bitmap]);
	affineTransformEffect->SetValue(D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX, t);


	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, affineTransformEffect.Get());


	ApplyAllEffect(bitmap, appliedEffect);

	deviceContext->DrawImage(combine.Get());
}


void Direct2DModule::DrawBitmap(std::wstring bitmap, vector2 size, vector2 originalSize, vector2 offset, Matrix3x3 matrix, Material* material, std::vector<IEffect*>* appliedEffect)
{
	D2D1_RECT_F srcRectangle;

	srcRectangle.left = offset.x;
	srcRectangle.top = offset.y;
	srcRectangle.right = offset.x + originalSize.x;
	srcRectangle.bottom = offset.y + originalSize.y;

	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInput(0, (*bitmapDictionary)[bitmap]);

	ComPtr<ID2D1Effect> cropEffect;
	deviceContext->CreateEffect(CLSID_D2D1Crop, &cropEffect);
	cropEffect->SetInputEffect(0, combine.Get());
	cropEffect->SetValue(D2D1_CROP_PROP_RECT, srcRectangle);

	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, cropEffect.Get());

	ComPtr<ID2D1Effect> affineTransformEffect;
	Matrix3x2F t = Matrix3x2F::Translation(-size.x / 2 - offset.x, -size.y / 2 - offset.y) * Matrix3x2F(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]);
	deviceContext->CreateEffect(CLSID_D2D12DAffineTransform, &affineTransformEffect);
	affineTransformEffect->SetInputEffect(0, combine.Get());
	affineTransformEffect->SetValue(D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX, t);

	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, affineTransformEffect.Get());

	ApplyAllEffect(bitmap, appliedEffect);

	deviceContext->DrawImage(combine.Get());
	//context3D->PSSetShader(NULL, NULL, 0);
}

void Direct2DModule::ApplyAllEffect(std::wstring bitmap, std::vector<IEffect*>* appliedEffect)
{
	if (appliedEffect->size() != 0)
	{
		for (auto iter = appliedEffect->begin(); iter < appliedEffect->end(); iter++)
		{
			if ((*iter)->GetId() == EffectId::ColorMatrixEffect)
				ApplyColorMatrixEffect(static_cast<ColorMatrixEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::AlphaMaskEffect)
				ApplyAlphaMaskEffect(static_cast<AlphaMaskEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::ConvolveMatrixEffect)
				ApplyConvolveMatrixEffect(static_cast<ConvolveMatrixEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::CrossFadeEffect)
				ApplyCrossFadeEffect(static_cast<CrossFadeEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::ArithmeticCompositeEffect)
				ApplyArithmeticCompositeEffect(static_cast<ArithmeticCompositeEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::DiscreteTransferEffect)
				ApplyDiscreteTransferEffect(static_cast<DiscreteTransferEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::LinearTransferEffect)
				ApplyLinearTransferEffect(static_cast<LinearTransferEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::PremultiplyEffect)
				ApplyPremultiplyEffect(static_cast<PremultiplyEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::UnPremultiplyEffect)
				ApplyUnPremultiplyEffect(static_cast<UnPremultiplyEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::DirectionalBlurEffect)
				ApplyDirectionalBlurEffect(static_cast<DirectionalBlurEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::DisplacementMapEffect)
				ApplyDisplacementMapEffect(static_cast<DisplacementMapEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::CompositeEffect)
				ApplyCompositeEffect(static_cast<CompositeEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::DistantLightEffect)
				ApplyDistantLightEffect(static_cast<DistantLightEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::PointLightEffect)
				ApplyPointLightEffect(static_cast<PointLightEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::SpotLightEffect)
				ApplySpotLightEffect(static_cast<SpotLightEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::TintEffect)
				ApplyTintEffect(static_cast<TintEffect*>(*iter));
			else if ((*iter)->GetId() == EffectId::HighLightEffect)
				ApplyHighLightEffect(static_cast<HighLightEffect*>(*iter));
		}
	}
}

void Direct2DModule::ApplyColorMatrixEffect(ColorMatrixEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	Matrix5x5 matrix = effect->matrix;
	Matrix5x4F t = Matrix5x4F(matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3], matrix[0][4],
		matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3], matrix[1][4],
		matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3], matrix[2][4],
		matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3], matrix[3][4]);

	newEffect->SetValue(0, t);
	newEffect->SetValue(1, effect->alphaMode);
	newEffect->SetValue(2, effect->clampOutput);

	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}

void Direct2DModule::ApplyAlphaMaskEffect(AlphaMaskEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1AlphaMask, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	newEffect->SetInput(1, (*bitmapDictionary)[*(effect->maskImage)]);
	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}
void Direct2DModule::ApplyConvolveMatrixEffect(ConvolveMatrixEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1ConvolveMatrix, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue

	newEffect->SetValue(0, effect->kernelUnitLength);
	newEffect->SetValue(1, effect->scaleMode);
	newEffect->SetValue(2, effect->kernelSizeX);
	newEffect->SetValue(3, effect->kernelSizeY);
	Matrix3x3 matrix = effect->kernelMatrix;
	float t[9] = { matrix[0][0],matrix[0][1],matrix[0][2],matrix[1][0],matrix[1][1],matrix[1][2],matrix[2][0],matrix[2][1],matrix[2][2] };
	newEffect->SetValue(4, t);
	newEffect->SetValue(5, effect->divisor);
	newEffect->SetValue(6, effect->bias);
	newEffect->SetValue(7, effect->kernelOffset);
	newEffect->SetValue(8, effect->preserveAlpha);
	newEffect->SetValue(9, effect->borderMode);
	newEffect->SetValue(10, effect->clampOutput);

	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ConvolveMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}
void Direct2DModule::ApplyCrossFadeEffect(CrossFadeEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1CrossFade, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	newEffect->SetInput(1, (*bitmapDictionary)[*(effect->other)]);
	newEffect->SetValue(0, effect->progress);
	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}

void Direct2DModule::ApplyArithmeticCompositeEffect(ArithmeticCompositeEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1ArithmeticComposite, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	newEffect->SetInput(1, (*bitmapDictionary)[*(effect->other)]);
	newEffect->SetValue(0, effect->coefficient);
	newEffect->SetValue(1, effect->clampOutput);
	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}
void Direct2DModule::ApplyDiscreteTransferEffect(DiscreteTransferEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1DiscreteTransfer, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	newEffect->SetValue(0, effect->redTable);
	newEffect->SetValue(1, effect->disableRed);
	newEffect->SetValue(2, effect->greenTable);
	newEffect->SetValue(3, effect->disableGreen);
	newEffect->SetValue(4, effect->blueTable);
	newEffect->SetValue(5, effect->disableBlue);
	newEffect->SetValue(6, effect->alphaTable);
	newEffect->SetValue(7, effect->disableAlpha);
	newEffect->SetValue(8, effect->clampOutput);
	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}

void Direct2DModule::ApplyLinearTransferEffect(LinearTransferEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1LinearTransfer, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValueredTable
	newEffect->SetValue(0, effect->intercept.x);
	newEffect->SetValue(1, effect->slope.x);
	newEffect->SetValue(2, effect->disableRed);
	newEffect->SetValue(3, effect->intercept.y);
	newEffect->SetValue(4, effect->slope.y);
	newEffect->SetValue(5, effect->disableGreen);
	newEffect->SetValue(6, effect->intercept.z);
	newEffect->SetValue(7, effect->slope.z);
	newEffect->SetValue(8, effect->disableBlue);
	newEffect->SetValue(9, effect->intercept.w);
	newEffect->SetValue(10, effect->slope.w);
	newEffect->SetValue(11, effect->disableAlpha);
	newEffect->SetValue(12, effect->clampOutput);
	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}

void Direct2DModule::ApplyPremultiplyEffect(PremultiplyEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1Premultiply, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	// 
	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}
void Direct2DModule::ApplyUnPremultiplyEffect(UnPremultiplyEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1UnPremultiply, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	// 
	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}

void Direct2DModule::ApplyDirectionalBlurEffect(DirectionalBlurEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1DirectionalBlur, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	newEffect->SetValue(0, effect->standardDeviation);
	newEffect->SetValue(1, effect->angle);
	newEffect->SetValue(2, effect->optimization);
	newEffect->SetValue(3, effect->borderMode);
	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}

void Direct2DModule::ApplyDisplacementMapEffect(DisplacementMapEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1DirectionalBlur, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	newEffect->SetValue(0, effect->scale);
	newEffect->SetValue(1, effect->xChannelSelect);
	newEffect->SetValue(2, effect->yChannelSelect);
	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}

void Direct2DModule::ApplyCompositeEffect(CompositeEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1Composite, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	newEffect->SetInput(1, (*bitmapDictionary)[*(effect->other)]);
	newEffect->SetValue(0, effect->mode);

	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}

void Direct2DModule::ApplyDistantLightEffect(DistantLightEffect* effect)
{

	ComPtr<ID2D1Effect> diffuse;
	deviceContext->CreateEffect(CLSID_D2D1DistantDiffuse, &diffuse);
	diffuse->SetInputEffect(0, combine.Get());
	//setValue
	diffuse->SetValue(0, effect->azimuth);
	diffuse->SetValue(1, effect->elevation);
	diffuse->SetValue(2, effect->diffuseConstant);
	diffuse->SetValue(3, effect->surfaceScale);
	diffuse->SetValue(4, effect->color);
	diffuse->SetValue(5, effect->kernelUnitLength);
	diffuse->SetValue(6, effect->scaleMode);


	ComPtr<ID2D1Effect> specular;
	deviceContext->CreateEffect(CLSID_D2D1DistantSpecular, &specular);
	specular->SetInputEffect(0, combine.Get());
	//setValue
	specular->SetValue(0, effect->azimuth);
	specular->SetValue(1, effect->elevation);
	specular->SetValue(2, effect->specularExponent);
	specular->SetValue(3, effect->specularConstant);
	specular->SetValue(4, effect->surfaceScale);
	specular->SetValue(5, effect->color);
	specular->SetValue(6, effect->kernelUnitLength);
	specular->SetValue(7, effect->scaleMode);

	ComPtr<ID2D1Effect> lightBlend;
	deviceContext->CreateEffect(CLSID_D2D1Blend, &lightBlend);
	lightBlend->SetInputEffect(0, diffuse.Get());
	lightBlend->SetInputEffect(1, specular.Get());
	lightBlend->SetValue(D2D1_BLEND_PROP_MODE, mixBlendMode);

	ComPtr<ID2D1Effect> alphaMask;
	deviceContext->CreateEffect(CLSID_D2D1AlphaMask, &alphaMask);
	alphaMask->SetInputEffect(0, lightBlend.Get());
	alphaMask->SetInputEffect(1, combine.Get());

	//setValue
	ComPtr<ID2D1Effect> result;
	deviceContext->CreateEffect(CLSID_D2D1Blend, &result);
	result->SetInputEffect(0, combine.Get());
	result->SetInputEffect(1, alphaMask.Get());
	result->SetValue(D2D1_BLEND_PROP_MODE, lightBlendMode);

	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, result.Get());
}

void Direct2DModule::ApplyPointLightEffect(PointLightEffect* effect)
{
	ComPtr<ID2D1Effect> diffuse;
	deviceContext->CreateEffect(CLSID_D2D1PointDiffuse, &diffuse);
	diffuse->SetInputEffect(0, combine.Get());
	//setValue
	diffuse->SetValue(0, effect->lightPosition);
	diffuse->SetValue(1, effect->diffuseConstant);
	diffuse->SetValue(2, effect->surfaceScale);
	diffuse->SetValue(3, effect->color);
	diffuse->SetValue(4, effect->kernelUnitLength);
	diffuse->SetValue(5, effect->scaleMode);

	ComPtr<ID2D1Effect> specular;
	deviceContext->CreateEffect(CLSID_D2D1PointSpecular, &specular);
	specular->SetInputEffect(0, combine.Get());
	//setValue
	specular->SetValue(0, effect->lightPosition);
	specular->SetValue(1, effect->specularExponent);
	specular->SetValue(2, effect->specularConstant);
	specular->SetValue(3, effect->surfaceScale);
	specular->SetValue(4, effect->color);
	specular->SetValue(5, effect->kernelUnitLength);
	specular->SetValue(6, effect->scaleMode);


	ComPtr<ID2D1Effect> lightBlend;
	deviceContext->CreateEffect(CLSID_D2D1Blend, &lightBlend);
	lightBlend->SetInputEffect(0, diffuse.Get());
	lightBlend->SetInputEffect(1, specular.Get());
	lightBlend->SetValue(D2D1_BLEND_PROP_MODE, mixBlendMode);

	ComPtr<ID2D1Effect> alphaMask;
	deviceContext->CreateEffect(CLSID_D2D1AlphaMask, &alphaMask);
	alphaMask->SetInputEffect(0, lightBlend.Get());
	alphaMask->SetInputEffect(1, combine.Get());

	//setValue
	ComPtr<ID2D1Effect> result;
	deviceContext->CreateEffect(CLSID_D2D1Blend, &result);
	result->SetInputEffect(0, combine.Get());
	result->SetInputEffect(1, alphaMask.Get());
	result->SetValue(D2D1_BLEND_PROP_MODE, lightBlendMode);

	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, result.Get());

}

void Direct2DModule::ApplySpotLightEffect(SpotLightEffect* effect)
{

	ComPtr<ID2D1Effect> diffuse;
	deviceContext->CreateEffect(CLSID_D2D1SpotDiffuse, &diffuse);
	diffuse->SetInputEffect(0, combine.Get());
	diffuse->SetValue(0, effect->lightPosition);
	diffuse->SetValue(1, effect->pointsAt);
	diffuse->SetValue(2, effect->focus);
	diffuse->SetValue(3, effect->limitingConeAngle);
	diffuse->SetValue(4, effect->diffuseConstant);
	diffuse->SetValue(5, effect->surfaceScale);
	diffuse->SetValue(6, effect->color);
	diffuse->SetValue(7, effect->kernelUnitLength);
	diffuse->SetValue(8, effect->scaleMode);

	ComPtr<ID2D1Effect> specular;
	deviceContext->CreateEffect(CLSID_D2D1SpotSpecular, &specular);
	specular->SetInputEffect(0, combine.Get());
	specular->SetValue(0, effect->lightPosition);
	specular->SetValue(1, effect->pointsAt);
	specular->SetValue(2, effect->focus);
	specular->SetValue(3, effect->limitingConeAngle);
	specular->SetValue(4, effect->specularExponent);
	specular->SetValue(5, effect->specularConstant);
	specular->SetValue(6, effect->surfaceScale);
	specular->SetValue(7, effect->color);
	specular->SetValue(8, effect->kernelUnitLength);
	specular->SetValue(9, effect->scaleMode);


	ComPtr<ID2D1Effect> lightBlend;
	deviceContext->CreateEffect(CLSID_D2D1Blend, &lightBlend);
	lightBlend->SetInputEffect(0, diffuse.Get());
	lightBlend->SetInputEffect(1, specular.Get());
	lightBlend->SetValue(D2D1_BLEND_PROP_MODE, mixBlendMode);

	ComPtr<ID2D1Effect> alphaMask;
	deviceContext->CreateEffect(CLSID_D2D1AlphaMask, &alphaMask);
	alphaMask->SetInputEffect(0, lightBlend.Get());
	alphaMask->SetInputEffect(1, combine.Get());

	//setValue
	ComPtr<ID2D1Effect> result;
	deviceContext->CreateEffect(CLSID_D2D1Blend, &result);
	result->SetInputEffect(0, combine.Get());
	result->SetInputEffect(1, alphaMask.Get());
	result->SetValue(D2D1_BLEND_PROP_MODE, lightBlendMode);

	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, result.Get());
}

void Direct2DModule::ApplyTintEffect(TintEffect* effect)
{
	ComPtr<ID2D1Effect> newEffect;
	deviceContext->CreateEffect(CLSID_D2D1Tint, &newEffect);
	newEffect->SetInputEffect(0, combine.Get());
	//setValue
	newEffect->SetValue(D2D1_TINT_PROP_COLOR, effect->color);
	newEffect->SetValue(1, effect->clampOutput);
	//setValue
	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, newEffect.Get());
}

void Direct2DModule::ApplyHighLightEffect(HighLightEffect* effect)
{
	

	ComPtr<ID2D1Effect> specular;
	deviceContext->CreateEffect(CLSID_D2D1DistantSpecular, &specular);
	specular->SetInputEffect(0, combine.Get());
	//setValue
	specular->SetValue(0, 0);
	specular->SetValue(1, 0);
	specular->SetValue(4, 10.0f);

	
	specular->SetValue(5, effect->color);



	ComPtr<ID2D1Effect> edgeDetectionEffect;
	deviceContext->CreateEffect(CLSID_D2D1EdgeDetection, &edgeDetectionEffect);

	edgeDetectionEffect->SetInputEffect(0, specular.Get());
	edgeDetectionEffect->SetValue(D2D1_EDGEDETECTION_PROP_STRENGTH, 1.0f);
	edgeDetectionEffect->SetValue(D2D1_EDGEDETECTION_PROP_BLUR_RADIUS, 0.0f);
	edgeDetectionEffect->SetValue(D2D1_EDGEDETECTION_PROP_MODE, D2D1_EDGEDETECTION_MODE_SOBEL);
	edgeDetectionEffect->SetValue(D2D1_EDGEDETECTION_PROP_OVERLAY_EDGES, false);
	edgeDetectionEffect->SetValue(D2D1_EDGEDETECTION_PROP_ALPHA_MODE, D2D1_ALPHA_MODE_STRAIGHT);

	ComPtr<ID2D1Effect> morphologyEffect;
	deviceContext->CreateEffect(CLSID_D2D1Morphology, &morphologyEffect);

	morphologyEffect->SetInputEffect(0, edgeDetectionEffect.Get());

	morphologyEffect->SetValue(D2D1_MORPHOLOGY_PROP_MODE, D2D1_MORPHOLOGY_MODE_DILATE);
	morphologyEffect->SetValue(D2D1_MORPHOLOGY_PROP_WIDTH, 3);
	morphologyEffect->SetValue(D2D1_MORPHOLOGY_PROP_HEIGHT, 3);


	ComPtr<ID2D1Effect> chromakeyEffect;
	deviceContext->CreateEffect(CLSID_D2D1ChromaKey, &chromakeyEffect);
	D2D1_VECTOR_4F back = { 0.0f, 0.0f, 0.0f, 1.0f };
	chromakeyEffect->SetInputEffect(0, morphologyEffect.Get());
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, back);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.2f);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);

	ComPtr<ID2D1Effect> tint;
	deviceContext->CreateEffect(CLSID_D2D1Tint, &tint);
	tint->SetInputEffect(0, chromakeyEffect.Get());
	D2D1_VECTOR_4F tintColor = { 1,1,1,0.8 };
	tint->SetValue(D2D1_TINT_PROP_COLOR, tintColor);


	//setValue
	ComPtr<ID2D1Effect> result;
	deviceContext->CreateEffect(CLSID_D2D1Composite, &result);
	result->SetInputEffect(0, tint.Get());
	result->SetInputEffect(1, combine.Get());
	result->SetValue(D2D1_COMPOSITE_PROP_MODE, D2D1_COMPOSITE_MODE_DESTINATION_ATOP);


	deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &combine);
	combine->SetInputEffect(0, result.Get());
}