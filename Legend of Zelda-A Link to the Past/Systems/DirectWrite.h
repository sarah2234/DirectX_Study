#pragma once

class DirectWrite
{
public:
	static void Create();
	static void Delete();

	static DirectWrite* Get();
	static ID2D1DeviceContext* GetDC() { return deviceContext; }

	static void CreateBackBuffer(); //2D용 backbuffer 관리 함수
	static void DeleteBackBuffer();

	static void RenderText(wstring& text, RECT& rect); //글자를 그려주는 함수

private:
	static DirectWrite* instance; //2D backbuffer를 하나 만들어주고 2D backbuffer가 만들어져있다면 더이상 만들지 않음

private:
	DirectWrite();
	~DirectWrite();

private:
	ID2D1Factory1* factory;
	static IDWriteFactory* writeFactory;

	ID2D1Device* device;
	static ID2D1DeviceContext* deviceContext;

	static ID2D1Bitmap1* bitmap;
	static IDXGISurface* surface;

	//폰트
	static ID2D1SolidColorBrush* brush;
	static IDWriteTextFormat* format;
};