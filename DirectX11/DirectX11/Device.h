#pragma once
#include <Windows.h>
#include <string>
#include <d3d11.h>
#include <assert.h>

// �̱��� �������� ������ �ʿ�� ����?
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
	ID3D11Device* device; // d3d ��ġ
	ID3D11DeviceContext* deviceContext;
};