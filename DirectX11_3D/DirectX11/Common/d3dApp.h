//***************************************************************************************
// d3dApp.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Simple Direct3D demo application class.  
// Make sure you link: d3d11.lib d3dx11d.lib D3DCompiler.lib D3DX11EffectsD.lib 
//                     dxerr.lib dxgi.lib dxguid.lib.
// Link d3dx11.lib and D3DX11Effects.lib for release mode builds instead
//   of d3dx11d.lib and D3DX11EffectsD.lib.
//***************************************************************************************

#ifndef D3DAPP_H
#define D3DAPP_H

#include "d3dUtil.h"
#include "GameTimer.h"
#include <string>

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();
	
	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	float     AspectRatio()const;
	
	int Run(); // 응용 프로그램 메세지 루프 포함. Windows 메세지가 전혀 없을 때에도 게임의 로직 처리
 
	// Framework methods.  Derived client class overrides these methods to 
	// implement specific application requirements.

	virtual bool Init(); // 응용 프로그램 고유의 초기화
	virtual void OnResize(); // WM_SIZE 메세지가 발생했을 때 클라이언트 영역의 크기에 의존하는 Direct3D의 속성 갱신(후면 버퍼, 깊이 스텐실 버퍼 등)
	virtual void UpdateScene(float dt) = 0; // 매 프레임마다 호출하여 시간의 흐름에 따라 응용 프로그램 갱신
	virtual void DrawScene() = 0; // 매 프레임마다 호출하여 현재 프레임을 후면 버퍼에 실제로 그리기 위한 렌더링 명령 제출
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // 응용 프로그램 주 창의 메세지 처리 기능

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y){ }
	virtual void OnMouseUp(WPARAM btnState, int x, int y)  { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y){ }

protected:
	bool InitMainWindow(); // 응용 프로그램 주 창 초기화
	bool InitDirect3D(); // Direct3D 초기화

	void CalculateFrameStats(); // 평균 초당 프레임 수(FPS)와 평균 프레임당 밀리초 계산

protected:
	HINSTANCE mhAppInst; // 응용 프로그램 인스턴스 핸들(HINSTANCE: identify the executable when loaded in memory)
	HWND      mhMainWnd; // 주 창 핸들 (window handle: 이를 사용하여 윈도우 접근)
	bool      mAppPaused; // 응용 프로그램이 일시 정지된 상태인지
	bool      mMinimized; // 응용 프로그램이 최소화된 상태인지
	bool      mMaximized; // 응용 프로그램이 최대화된 상태인지
	bool      mResizing; // 사용자가 크기 조정용 테두리를 끌고 있는 상태인지
	UINT      m4xMsaaQuality; // 4X MSAA(multisampling anti-aliasing) 품질 수준

	GameTimer mTimer;

	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dImmediateContext;
	IDXGISwapChain* mSwapChain;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mScreenViewport;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption; // 창의 제목
	D3D_DRIVER_TYPE md3dDriverType; // 생성할 DX11 디바이스 종류
	int mClientWidth; // 창 너비
	int mClientHeight; // 창 높이
	bool mEnable4xMsaa; // 4X MSAA를 사용할 때 true
};

#endif // D3DAPP_H