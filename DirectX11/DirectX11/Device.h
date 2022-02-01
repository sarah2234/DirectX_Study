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
	static bool InitializeDirectX();

private:
	static  HWND hwnd;
	static WNDCLASS wc;
	static int windowWidth;
	static int windowHeight;

	static  IDXGISwapChain* swapChain;
	static  ID3D11Device* device; // represents a virtual adapter (COM ��ü) => �׷��� ī�忡 �����Ͽ� ����� ���� �� �ֵ��� ������ִ� ������Ʈ�� �������̽� ��ü
	static  ID3D11DeviceContext* deviceContext; // Ư���� �ϳ��� device�� ���� �׷��� ������ ���� ����ü (��Ʈ,	�� ����, ���� ��)
	static  ID3D11RenderTargetView* renderTargetView; // RTV: enables a scene to be rendered to a temporary intermediate buffer, instead of the back buffer
	static  D3D11_VIEWPORT viewport; // ȭ��

	Device();
	~Device();
};