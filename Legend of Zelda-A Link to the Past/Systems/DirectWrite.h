#pragma once

class DirectWrite
{
public:
	static void Create();
	static void Delete();

	static DirectWrite* Get();
	static ID2D1DeviceContext* GetDC() { return deviceContext; }

	static void CreateBackBuffer(); //2D�� backbuffer ���� �Լ�
	static void DeleteBackBuffer();

	static void RenderText(wstring& text, RECT& rect); //���ڸ� �׷��ִ� �Լ�

private:
	static DirectWrite* instance; //2D backbuffer�� �ϳ� ������ְ� 2D backbuffer�� ��������ִٸ� ���̻� ������ ����

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

	//��Ʈ
	static ID2D1SolidColorBrush* brush;
	static IDWriteTextFormat* format;
};