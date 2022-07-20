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
	
	int Run(); // ���� ���α׷� �޼��� ���� ����. Windows �޼����� ���� ���� ������ ������ ���� ó��
 
	// Framework methods.  Derived client class overrides these methods to 
	// implement specific application requirements.

	virtual bool Init(); // ���� ���α׷� ������ �ʱ�ȭ
	virtual void OnResize(); // WM_SIZE �޼����� �߻����� �� Ŭ���̾�Ʈ ������ ũ�⿡ �����ϴ� Direct3D�� �Ӽ� ����(�ĸ� ����, ���� ���ٽ� ���� ��)
	virtual void UpdateScene(float dt) = 0; // �� �����Ӹ��� ȣ���Ͽ� �ð��� �帧�� ���� ���� ���α׷� ����
	virtual void DrawScene() = 0; // �� �����Ӹ��� ȣ���Ͽ� ���� �������� �ĸ� ���ۿ� ������ �׸��� ���� ������ ��� ����
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // ���� ���α׷� �� â�� �޼��� ó�� ���

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y){ }
	virtual void OnMouseUp(WPARAM btnState, int x, int y)  { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y){ }

protected:
	bool InitMainWindow(); // ���� ���α׷� �� â �ʱ�ȭ
	bool InitDirect3D(); // Direct3D �ʱ�ȭ

	void CalculateFrameStats(); // ��� �ʴ� ������ ��(FPS)�� ��� �����Ӵ� �и��� ���

protected:
	HINSTANCE mhAppInst; // ���� ���α׷� �ν��Ͻ� �ڵ�(HINSTANCE: identify the executable when loaded in memory)
	HWND      mhMainWnd; // �� â �ڵ� (window handle: �̸� ����Ͽ� ������ ����)
	bool      mAppPaused; // ���� ���α׷��� �Ͻ� ������ ��������
	bool      mMinimized; // ���� ���α׷��� �ּ�ȭ�� ��������
	bool      mMaximized; // ���� ���α׷��� �ִ�ȭ�� ��������
	bool      mResizing; // ����ڰ� ũ�� ������ �׵θ��� ���� �ִ� ��������
	UINT      m4xMsaaQuality; // 4X MSAA(multisampling anti-aliasing) ǰ�� ����

	GameTimer mTimer;

	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dImmediateContext;
	IDXGISwapChain* mSwapChain;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mScreenViewport;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption; // â�� ����
	D3D_DRIVER_TYPE md3dDriverType; // ������ DX11 ����̽� ����
	int mClientWidth; // â �ʺ�
	int mClientHeight; // â ����
	bool mEnable4xMsaa; // 4X MSAA�� ����� �� true
};

#endif // D3DAPP_H