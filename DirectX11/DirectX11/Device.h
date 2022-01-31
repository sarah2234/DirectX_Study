#pragma once
#include <Windows.h>
#include <string>
#include <d3d11.h>
#include <assert.h>

// 싱글톤 패턴으로 생성할 필요는 없나?
class Device
{
public:
	static bool InitializeWindow(HINSTANCE hInstance, int width, int height, int nCmdShow, std::wstring windowName);
	bool InitializeDirectX();

private:
	static HWND hwnd;
	static WNDCLASS wc;
	static int windowWidth;
	static int windowHeight;
	IDXGISwapChain* swapChain;
	ID3D11Device* device; // d3d 장치
	ID3D11DeviceContext* deviceContext;
};