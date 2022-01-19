#include "stdafx.h"
#include "DirectWrite.h"

//초기화
DirectWrite* DirectWrite::instance = NULL;

IDWriteFactory* DirectWrite::writeFactory = NULL;
ID2D1DeviceContext* DirectWrite::deviceContext = NULL;
ID2D1Bitmap1* DirectWrite::bitmap = NULL;
IDXGISurface* DirectWrite::surface = NULL;

ID2D1SolidColorBrush* DirectWrite::brush = NULL;
IDWriteTextFormat* DirectWrite::format = NULL;

void DirectWrite::Create()
{
	assert(instance == NULL);

	instance = new DirectWrite(); //2D backbuffer가 만들어져있다면 더이상 만들지 않음 (instance가 NULL일 때 메모리 할당)
}

void DirectWrite::Delete()
{
	SAFE_DELETE(instance);
}

DirectWrite* DirectWrite::Get()
{
	return instance;
}

DirectWrite::DirectWrite()
{
	HRESULT hr;

	hr = DWriteCreateFactory // DirectWrite factory 생성
	(
		//3D 자원을 호환
		DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown **)&writeFactory
	);
	assert(SUCCEEDED(hr));

	D2D1_FACTORY_OPTIONS option;
	option.debugLevel = D2D1_DEBUG_LEVEL_WARNING;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
	assert(SUCCEEDED(hr));


	IDXGIDevice* dxgiDevice;
	hr = Device->QueryInterface(&dxgiDevice);
	assert(SUCCEEDED(hr));

	hr = factory->CreateDevice(dxgiDevice, &device);
	assert(SUCCEEDED(hr));

	hr = device->CreateDeviceContext
	(
		//멀티 스레드 최적화
		D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &deviceContext
	);
	assert(SUCCEEDED(hr));

	CreateBackBuffer();
}

DirectWrite::~DirectWrite()
{
	DeleteBackBuffer();
}

void DirectWrite::CreateBackBuffer()
{
	HRESULT hr;

	hr = SwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void **)&surface);
	assert(SUCCEEDED(hr));


	D2D1_BITMAP_PROPERTIES1 bp; //DC 생성을 위한 옵션
	bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM; //0~1
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE; //알파 무시
	bp.dpiX = 96; //한 글자당 픽셀 (1/96 인치)
	bp.dpiY = 96; //한 글자당 픽셀 (1/96 인치)
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW; //외부에서 접근 금지 쓰기 전용
	bp.colorContext = NULL;

	hr = deviceContext->CreateBitmapFromDxgiSurface(surface, &bp, &bitmap);
	assert(SUCCEEDED(hr));

	deviceContext->SetTarget(bitmap);


	hr = deviceContext->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1), &brush);
	assert(SUCCEEDED(hr));

	writeFactory->CreateTextFormat
	(
		L"돋움체", NULL //글씨체
		, DWRITE_FONT_WEIGHT_SEMI_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL
		, 15, L"ko", &format
	);
}

void DirectWrite::DeleteBackBuffer()
{
	deviceContext->SetTarget(NULL);

	SAFE_RELEASE(brush); //text
	SAFE_RELEASE(format); //text

	SAFE_RELEASE(bitmap); //2d
	SAFE_RELEASE(surface); //2d
}

void DirectWrite::RenderText(wstring & text, RECT & rect) //글자를 그릴 위치
{
	D2D1_RECT_F temp;
	temp.left = (float)rect.left;
	temp.top = (float)rect.top;
	temp.right = (float)rect.right;
	temp.bottom = (float)rect.bottom;

	DirectWrite::GetDC()->DrawTextW(text.c_str(), text.size(), format, &temp, brush);
}
