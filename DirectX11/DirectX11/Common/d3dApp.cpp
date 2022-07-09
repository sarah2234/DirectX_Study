//***************************************************************************************
// d3dApp.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "d3dApp.h"
#include <WindowsX.h>
#include <sstream>

namespace
{
	// This is just used to forward Windows messages from a global window
	// procedure to our member function window procedure because we cannot
	// assign a member function to WNDCLASS::lpfnWndProc.
	D3DApp* gd3dApp = 0;
}

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return gd3dApp->MsgProc(hwnd, msg, wParam, lParam);
}

D3DApp::D3DApp(HINSTANCE hInstance)
:	mhAppInst(hInstance),
	mMainWndCaption(L"D3D11 Application"),
	md3dDriverType(D3D_DRIVER_TYPE_HARDWARE),
	mClientWidth(800),
	mClientHeight(600),
	mEnable4xMsaa(false),
	mhMainWnd(0),
	mAppPaused(false),
	mMinimized(false),
	mMaximized(false),
	mResizing(false),
	m4xMsaaQuality(0),
 
	md3dDevice(0),
	md3dImmediateContext(0),
	mSwapChain(0),
	mDepthStencilBuffer(0),
	mRenderTargetView(0),
	mDepthStencilView(0)
{
	ZeroMemory(&mScreenViewport, sizeof(D3D11_VIEWPORT));

	// Get a pointer to the application object so we can forward 
	// Windows messages to the object's window procedure through
	// the global window procedure.
	gd3dApp = this;
}

D3DApp::~D3DApp()
{
	ReleaseCOM(mRenderTargetView);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mSwapChain);
	ReleaseCOM(mDepthStencilBuffer);

	// Restore all default settings.
	if( md3dImmediateContext )
		md3dImmediateContext->ClearState();

	ReleaseCOM(md3dImmediateContext);
	ReleaseCOM(md3dDevice);
}

HINSTANCE D3DApp::AppInst()const
{
	return mhAppInst;
}

HWND D3DApp::MainWnd()const
{
	return mhMainWnd;
}

float D3DApp::AspectRatio()const
{
	return static_cast<float>(mClientWidth) / mClientHeight;
}

// WPARAM: Ű���� ���������� ���� Ȯ��
// LPARAM: ��ǥ�� �ǹ� ����. �� 4����Ʈ�� �̷���� ������ 2����Ʈ�� �߶� y, x �� ���
// HIWORD: y�� ��
// LOWORD: x�� ��
LRESULT D3DApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated
		// Pause the game when the window is deactivated
		// Unpause the game when it becomes active
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			mAppPaused = true;
			mTimer.Stop();
		}
		else
		{
			mAppPaused = false;
			mTimer.Start();
		}
		return 0;

		// WM_SIZE is sent when the user resizes the window
	case WM_SIZE:
		// Save the new client area dimensions
		mClientHeight = HIWORD(lParam); // y
		mClientWidth = LOWORD(lParam); // x
		if (md3dDevice)
		{
			if (wParam == SIZE_MINIMIZED)
			{
				mAppPaused = true;
				mMinimized = true;
				mMaximized = false;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				mAppPaused = false;
				mMinimized = false;
				mMaximized = true;
				OnResize();
			}
			else if (wParam == SIZE_RESTORED)
			{
				// Restoring from minimized state
				if (mMinimized)
				{
					mAppPaused = false;
					mMinimized = false;
					OnResize();
				}
				// Restoring from maximized state
				else if (mMaximized)
				{
					mAppPaused = false;
					mMaximized = false;
					OnResize();
				}
				else if (mResizing)
				{
					/*
					If user is dragging the resize bar, we do not resize
					the buffers here because as the user continuously
					drags the resize bars, a stream of WM_SIZE messages are
					sent to the window, and it would be pointless (and slow)
					to resize for each WM_SIZE message received from dragging
					the resize bars. Instead, we reset buffers after the user
					is done resizing the window and releases the resize bars,
					which sends a WM_EXITSIZEMOVE message.
					*/
				}
				else // API call such as SetWindowPos or mSwapChain->SetFullScreenState
				{
					OnResize();
				}
			}
		}
		return 0;

		// WM_ENTERSIZEMOVE�� ����ڰ� ũ�� ���� �׵θ��� ������ ���޵ȴ�.
	case WM_ENTERSIZEMOVE:
		mAppPaused = true;
		mResizing = true;
		mTimer.Stop();
		return 0;

		// WM_EXITSIZEMOVE�� ����ڰ� ũ�� ���� �׵θ��� ������ ���޵ȴ�.
		// ���⼭ â�� �� ũ�⿡ �°� ��� ���� �缳����
	case WM_EXITSIZEMOVE:
		mAppPaused = false;
		mResizing = true;
		mTimer.Start();
		OnResize();
		return 0;

		// WM_DESTROY�� â�� �ı��Ƿ� �� �� ���޵�
	case WM_DESTROY:
		PostQuitMessage(0); // �޼��� ť�� WM_QUIT �޼���(���� ���α׷� ���� ��û)�� ���� => GetMessage �Լ��� 0 ����
		return 0;

		// WM_MENUCHAR�� �޴��� Ȱ��ȭ�Ǿ ����ڰ� Ű�� �������� �� Ű��
		// �� � �ϸ��(mnemonic)�̳� ����Ű���� �ش����� ���� �� ����
	case WM_MENUCHAR:
		// Alt-Enter�� ������ �� �� �Ҹ��� ���� �ʰ� ��
		return MAKELRESULT(0, MNC_CLOSE);

		// �� �޼����� �߻��� ��� â�� �ʹ� �۾����� �ʵ��� ��
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool D3DApp::InitMainWindow()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mhAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"D3DWndClassName";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, mClientWidth, mClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	mhMainWnd = CreateWindow(L"D3DWndClassName", mMainWndCaption.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mhAppInst, 0);
	if (!mhMainWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);

	return true;
}

bool D3DApp::InitDirect3D()
{
	return false;
}

void D3DApp::CalculateFrameStats()
{
	// ��� FSP ���
	// �ϳ��� �������� �������ϴ� �� �ɸ��� ��� �ð� ���
	// �� �� ���ġ���� â�� �����ٿ� �߰�
	static int frameCnt = 0;
	static float timeElapsed = 0;

	frameCnt++;

	// 1�� ������ ��� ������ �� ���
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		// FPS���� ������ �ð�(�� �������� �������ϴ� �� �ɸ� ��� �ð�)�� �� �����ϰ� ������
		// stringstream: �־��� ���ڿ����� �ʿ��� �ڷ����� �´� ������ ���� �� ���� (#include <sstream>)
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps; // �и��� ����
		std::wostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << L"   "
			<< L"FPS: " << fps << L"   "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// ���� ����� ���� �ٽ� �ʱ�ȭ
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}


