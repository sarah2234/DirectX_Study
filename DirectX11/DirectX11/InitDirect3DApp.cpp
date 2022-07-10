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
// hInstance: handle to an instance => identify the executable when loaded in memory (ex: �������̳� ��Ʈ�� �ε�)
// hPrevInstance: always NULL in WIN32 (used in 16-bit Windows) => ȣȯ���� ���� �����ϴ� �μ��̹Ƿ� �Ű� x
// pCmdLine: command-line arguments as a Unicode string
// nCmdShow: a flag to identify whether the main application window will be minimized/maximized/shown normally
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// ����� ������ ��� ������� �޸� ���� ����� �Ҵ�.
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
	// assert: ǥ������ �μ��� �޾� �� �μ��� ������ ���� => false�� �� ���� �޼��� ��� �� ���α׷� ���� ����
	assert(md3dImmediateContext);
	assert(mSwapChain);

	// �ĸ� ���۸� �Ķ������� �����. Colors::Blue�� d3dUtil.h�� ���ǵǾ� �ִ�.
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, 
		reinterpret_cast<const float*>(&Colors::Blue));
	// ���� ���۸� 1.0f��, ���ٽ� ���۸� 0���� �����.
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// �ĸ� ���۸� ȭ�鿡 ����
	// (0, 0): Present as fast as possible
	// (1, 0): Lock presentation to screen refresh rate
	HR(mSwapChain->Present(0, 0));
}