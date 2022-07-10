#pragma once
#include "stdafx.h"
#include "Common/d3dApp.h"

class InitDirect3DApp :public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();
};

// WinMain: entry-point function (in Console, main function is the entry-point function)
// hInstance: handle to an instance => identify the executable when loaded in memory (ex: 아이콘이나 비트맵 로드)
// hPrevInstance: always NULL in WIN32 (used in 16-bit Windows) => 호환성을 위해 존재하는 인수이므로 신경 x
// pCmdLine: command-line arguments as a Unicode string
// nCmdShow: a flag to identify whether the main application window will be minimized/maximized/shown normally
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// 디버그 빌드의 경우 실행시점 메모리 점검 기능을 켠다.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	
	InitDirect3DApp theApp(hInstance);
	

	if (!theApp.Init())
		return 0;
	
	return theApp.Run();
}

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
}

InitDirect3DApp::~InitDirect3DApp()
{
}

bool InitDirect3DApp::Init()
{
	if (!D3DApp::Init())
		return false;

	return true;
}

void InitDirect3DApp::OnResize()
{
	D3DApp::OnResize();
}

void InitDirect3DApp::UpdateScene(float dt)
{

}

void InitDirect3DApp::DrawScene()
{
	// assert: 표현식을 인수로 받아 이 인수가 참인지 점검 => false일 때 에러 메세지 출력 후 프로그램 강제 종료
	assert(md3dImmediateContext);
	assert(mSwapChain);

	// 후면 버퍼를 파란색으로 지운다. Colors::Blue는 d3dUtil.h에 정의되어 있다.
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, 
		reinterpret_cast<const float*>(&Colors::Blue));
	// 깊이 버퍼를 1.0f로, 스텐실 버퍼를 0으로 지운다.
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// 후면 버퍼를 화면에 제시
	// (0, 0): Present as fast as possible
	// (1, 0): Lock presentation to screen refresh rate
	HR(mSwapChain->Present(0, 0));
}