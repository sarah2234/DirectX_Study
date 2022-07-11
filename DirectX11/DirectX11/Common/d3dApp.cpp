//***************************************************************************************
// d3dApp.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************
#include "stdafx.h"
#include "d3dApp.h"

namespace
{
	// This is just used to forward Windows messages from a global window
	// procedure to our member function window procedure because we cannot
	// assign a member function to WNDCLASS::lpfnWndProc.
	D3DApp* gd3dApp = 0;
}

// 창의 이벤트 처리 함수
// WPARAM: 키값이 눌러졌는지 상태 확인
// LPARAM: 좌표의 의미 포함. 총 4바이트로 이루어져 있으며 2바이트씩 잘라서 y, x 값 사용
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return gd3dApp->MsgProc(hwnd, msg, wParam, lParam);
}

D3DApp::D3DApp(HINSTANCE hInstance)
:	mhAppInst(hInstance),
	mMainWndCaption(L"D3D11 Application"),
	md3dDriverType(D3D_DRIVER_TYPE_HARDWARE), // D3Device will be created on hardware mode if the graphics card supports DX11 feature level
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

int D3DApp::Run()
{
	MSG msg = { 0 };

	mTimer.Reset();
	
	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{
			mTimer.Tick();

			if (!mAppPaused)
			{
				CalculateFrameStats();
				UpdateScene(mTimer.DeltaTime());
				DrawScene();
			}
			else
			{
				Sleep(100);
			}
		}
	}

	return (int)msg.wParam;
}


bool D3DApp::Init()
{
	if (!InitMainWindow())
		return false;
	
	if (!InitDirect3D())
		return false;

	return true;
}

void D3DApp::OnResize()
{
	assert(md3dImmediateContext);
	assert(md3dDevice);
	assert(mSwapChain);

	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.

	ReleaseCOM(mRenderTargetView);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mDepthStencilBuffer);


	// Resize the swap chain and recreate the render target view.

	HR(mSwapChain->ResizeBuffers(1, mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer; // manages texel data
	HR(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))); // Get information of a back buffer
	HR(md3dDevice->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView));
	ReleaseCOM(backBuffer);

	// Create the depth/stencil buffer and view.

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = mClientWidth;
	depthStencilDesc.Height = mClientHeight;
	depthStencilDesc.MipLevels = 1; // 밉맵: https://drehzr.tistory.com/666
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// Use 4X MSAA? --must match swap chain MSAA values.
	if (mEnable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4; // 멀티 샘플링 개수 지정
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1; // 품질 레벨
	}
	// No MSAA
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; // how the texture is to be read and written to
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; //flags for binding to pipeline stages
	depthStencilDesc.CPUAccessFlags = 0; // specify types of allowed CPU access (0 if CPU access is denied)
	depthStencilDesc.MiscFlags = 0; // identify other, less common resource options (0 if none of these apply)

	HR(md3dDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
	HR(md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));


	// Bind the render target view and depth/stencil view to the pipeline.

	md3dImmediateContext->OMSetRenderTargets(1, // the number of render targes to bind
		&mRenderTargetView,
		mDepthStencilView);


	// Set the viewport transform.

	mScreenViewport.TopLeftX = 0;
	mScreenViewport.TopLeftY = 0;
	mScreenViewport.Width = static_cast<float>(mClientWidth);
	mScreenViewport.Height = static_cast<float>(mClientHeight);
	mScreenViewport.MinDepth = 0.0f;
	mScreenViewport.MaxDepth = 1.0f;
	// bind viewports at the rasterizer stage of the pipeline
	md3dImmediateContext->RSSetViewports(1, // the number of viewports to bind
		&mScreenViewport); // an array of viewports to bind to the device
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
	WNDCLASS wc; // window class 
	wc.style = CS_HREDRAW | CS_VREDRAW; // 창 크기가 변경될 때 클라이언트 영역의 전체 콘텐츠 다시 그리기
	wc.lpfnWndProc = MainWndProc; // 함수 포인터 대입 => OS에서 발생하는 이벤트들이 발생할 때 알림
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mhAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION); // 아이콘 지정
	wc.hCursor = LoadCursor(0, IDC_ARROW); // 커서 지정 (여기선 화살표 모양으로 지정)
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // 윈도우의 배경색 지정 (default: WHITE_BRUSH)
	wc.lpszMenuName = 0; // 메뉴 리소스
	wc.lpszClassName = L"D3DWndClassName"; // 윈도우 클래스 이름

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

	mhMainWnd = CreateWindow(wc.lpszClassName, mMainWndCaption.c_str(),
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
	// Create the device and device context.

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = mClientWidth;
	sd.BufferDesc.Height = mClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Use 4X MSAA? 
	if (mEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	// No MSAA
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 백 버퍼의 용도 지정(현재 장면을 그려놓는 용도로 지정)
	sd.BufferCount = 1; // 사용할 백 버퍼 개수
	sd.OutputWindow = mhMainWnd; // 결과를 출력할 윈도우에 대한 핸들
	sd.Windowed = true; // 창 모드로 생성
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // 백 버퍼에서 프론트 버퍼로 가져올 형식 (discard: prevents overhead, the most effective one)
	sd.Flags = 0;

	D3D_FEATURE_LEVEL featureLevel;
	// D3D11CreateDeviceAndSwapChain: Create a device(그래픽 카드를 추상화한 객체) and a swap chain
	// * 아래의 인자들은 기본적으로 많이 쓰이므로 앞으로도 아래와 같이 쓰면 됨
	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr, // 디스플레이 디바이스(비디오 카드) 지정 (nullptr: 최초로 발견한 디바이스 사용)
		D3D_DRIVER_TYPE_HARDWARE, // 생성할 DX11 디바이스 종류 지정 (D3Device will be created on hardware mode if the graphics card supports DX11 feature level)
		nullptr, // A handle to a DLL that implements a software rasterizer
		0, // runtime layers
		nullptr, // determine the order of feature levels to attempt to create
		0, // the number of elements in pFeatureLevels
		D3D11_SDK_VERSION, // SDK version
		&sd, // a pointer to a swap chain description
		&mSwapChain, // an address of a pointer to the IDXGISwapChain object
		&md3dDevice, // an address of a pointer to an ID3D11Device object that represents the device created
		&featureLevel, // a pointer to a D3D_FEATURE_LEVEL (지정 안 하면 NULL)
		&md3dImmediateContext // an address of a pointer to an ID3D11DeviceContext object
	);
	
	// 디바이스와 스왑 체인이 성공적으로 만들어졌는지 확인
	if (FAILED(result))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.
	// 확인용...
	HR(md3dDevice->CheckMultisampleQualityLevels( // get the number of quality levels available during multisampling
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality));
	assert(m4xMsaaQuality > 0);

	/* 여기는 왜 device와 swap chain을 따로 만들었지?
	// 1. Device 만들기
	HRESULT hr = D3D11CreateDevice(
		0,                 // default adapter
		md3dDriverType,
		0,                 // no software device
		createDeviceFlags,
		0, 0,              // default feature level array
		D3D11_SDK_VERSION,
		&md3dDevice,
		&featureLevel,
		&md3dImmediateContext);


	// 2. Swap Chain 만들기
	// To correctly create the swap chain, we must use the IDXGIFactory that was
	// used to create the device.  If we tried to use a different IDXGIFactory instance
	// (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain: 
	// This function is being called with a device from a different IDXGIFactory."

	// 아래의 자료형에 대한 추가 메소드: p.153

	IDXGIDevice* dxgiDevice = 0;
	HR(md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(md3dDevice, &sd, &mSwapChain));
	// CreateSwapChain 호출 후 아래의 코드에 DXGI_MWA_NO_WINDOW_CHANGES를 인자로 넣으면
	// Alt+Enter로 창 모드 <-> 전체화면 모드 전환 금지
	dxgiFactory->MakeWindowAssociation(mhMainWnd, DXGI_MWA_NO_WINDOW_CHANGES);

	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);
	*/

	// The remaining steps that need to be carried out for d3d creation
	// also need to be executed every time the window is resized.  So
	// just call the OnResize method here to avoid code duplication.
	OnResize();

	return true;
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


