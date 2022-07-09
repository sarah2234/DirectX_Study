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

// WPARAM: 키값이 눌러졌는지 상태 확인
// LPARAM: 좌표의 의미 포함. 총 4바이트로 이루어져 있으며 2바이트씩 잘라서 y, x 값 사용
// HIWORD: y의 값
// LOWORD: x의 값
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

		// WM_ENTERSIZEMOVE는 사용자가 크기 변경 테두리를 잡으면 전달된다.
	case WM_ENTERSIZEMOVE:
		mAppPaused = true;
		mResizing = true;
		mTimer.Stop();
		return 0;

		// WM_EXITSIZEMOVE는 사용자가 크기 변경 테두리를 놓으면 전달된다.
		// 여기서 창의 새 크기에 맞게 모든 것을 재설정함
	case WM_EXITSIZEMOVE:
		mAppPaused = false;
		mResizing = true;
		mTimer.Start();
		OnResize();
		return 0;

		// WM_DESTROY는 창이 파괴되려 할 때 전달됨
	case WM_DESTROY:
		PostQuitMessage(0); // 메세지 큐에 WM_QUIT 메세지(응용 프로그램 종료 요청)를 붙임 => GetMessage 함수가 0 리턴
		return 0;

		// WM_MENUCHAR는 메뉴가 활성화되어서 사용자가 키를 눌렀으나 그 키가
		// 그 어떤 니모닉(mnemonic)이나 단축키에도 해당하지 않을 때 전달
	case WM_MENUCHAR:
		// Alt-Enter를 눌렀을 때 삐 소리가 나지 않게 함
		return MAKELRESULT(0, MNC_CLOSE);

		// 이 메세지가 발생한 경우 창이 너무 작아지지 않도록 함
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
	// 평균 FSP 계산
	// 하나의 프레임을 렌더링하는 데 걸리는 평균 시간 계산
	// 이 두 통계치들을 창의 제목줄에 추가
	static int frameCnt = 0;
	static float timeElapsed = 0;

	frameCnt++;

	// 1초 동안의 평균 프레임 수 계산
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		// FPS보다 프레임 시간(한 프레임을 렌더링하는 데 걸린 평균 시간)이 더 유용하고 직관적
		// stringstream: 주어진 문자열에서 필요한 자료형에 맞는 정보를 꺼낼 때 유용 (#include <sstream>)
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps; // 밀리초 단위
		std::wostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << L"   "
			<< L"FPS: " << fps << L"   "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// 다음 평균을 위해 다시 초기화
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}


