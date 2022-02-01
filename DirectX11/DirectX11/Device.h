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
	static bool InitializeDirectX();

private:
	static  HWND hwnd;
	static WNDCLASS wc;
	static int windowWidth;
	static int windowHeight;

	static  IDXGISwapChain* swapChain;
	static  ID3D11Device* device; // represents a virtual adapter (COM 객체) => 그래픽 카드에 접근하여 명령을 내릴 수 있도록 만들어주는 컴포넌트의 인터페이스 객체
	static  ID3D11DeviceContext* deviceContext; // 특정한 하나의 device에 대한 그래픽 정보를 담은 구조체 (폰트,	선 색깔, 굵기 등)
	static  ID3D11RenderTargetView* renderTargetView; // RTV: enables a scene to be rendered to a temporary intermediate buffer, instead of the back buffer
	static  D3D11_VIEWPORT viewport; // 화면

	Device();
	~Device();
};