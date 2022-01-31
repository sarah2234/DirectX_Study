#include "Device.h"

HWND Device::hwnd; // static 변수는 클래스 기반으로 생성됨
WNDCLASS Device::wc;
int Device::windowWidth;
int Device::windowHeight;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(
				NULL,
				TEXT("종료하시겠습니까?"),
				TEXT("종료"),
				MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DestroyWindow(hwnd);
			}
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Device::InitializeWindow(HINSTANCE hInstance, int width, int height, int nCmdShow, std::wstring windowName)
{
	wc = {};

	ZeroMemory(&wc, sizeof(wc));

	wc.hInstance = hInstance;
	wc.lpszClassName = L"Window Class";
	wc.lpfnWndProc = WindowProc;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (RegisterClass(&wc) == false)
		exit(-1);

	hwnd = CreateWindow(wc.lpszClassName,
		windowName.c_str(),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (hwnd == NULL)
		exit(-1);

	windowWidth = width;
	windowHeight = height;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
}

bool Device::InitializeDirectX()
{
	// swap chain: a collection of buffers used for displaying frames => 전면 버퍼 포인터와 후면 버퍼 포인터를 서로 맞바꾸는 flipping 사용
	// prevent 'screen flickering' & 'screen tearing'
	DXGI_SWAP_CHAIN_DESC swapChainDesc; // used to describe a swap chain
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1; // 사용할 백 버퍼(후면 버퍼)의 개수
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 백 버퍼의 용도 지정 (현재 장면을 그려넣는 용도로 지정함)
	swapChainDesc.OutputWindow = hwnd; // 결과를 출력할 윈도우에 대한 핸들
	swapChainDesc.Windowed = true; // 창 모드로 생성
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // 백 버퍼에서 프론트 버퍼로 가져올 형식 (prevents overhead, the most effective swap effect)
	
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 출력 형식 지정 (red, green, blue, alpha가 각각 8 비트 사용) (unorm: 정규화)
	swapChainDesc.BufferDesc.Width = windowWidth; // 버퍼의 너비
	swapChainDesc.BufferDesc.Height = windowHeight; // 버퍼의 높이

	// Anti Aliasing 기법들
	// 1) Super Sampling: 해상도를 늘린 후의 픽셀(원래 늘리기 전의 픽셀 크기의 1/4 픽셀, 즉 서브 픽셀)의 평균을 사용하여 원래 해상도로 출력 => 큰 비용
	// 2) Multi Sampling: 픽셀 당 몇 개의 샘플을 가지고, 각각의 샘플에 대해 bound checking -> bound 내에 있는 샘플만 원래 서브 픽셀로 나눠지기 전 중앙에 있던 픽셀의 색 공유
	swapChainDesc.SampleDesc.Count = 1; // 멀티 샘플링 개수 지정 => 멀티 샘플링 사용 x
	swapChainDesc.SampleDesc.Quality = 0; // 품질 레벨 => 멀티 샘플링 사용 x
	
	// HRESULT: 32-bit value to describe an error or warning
	// D3D11CreateDeviceAndSwapChain: Create a device(creating resources/enumerating the capabilities of a display adapter) and a swap chain
	// * 아래의 인자들은 기본적으로 많이 쓰이므로 앞으로도 아래와 같이 쓰면 됨
	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr, // 디스플레이 디바이스(비디오 카드) 지정 (nullptr: 최초로 발견한 디바이스 사용)
		D3D_DRIVER_TYPE_HARDWARE, // 생성할 DX11 디바이스 종류 지정 (D3Device will be created on hardware mode if the graphics card supports DX11 feature level)
		nullptr, // A handle to a DLL that implements a software rasterizer
		0, // runtime layers
		nullptr, // determine the order of feature levels to attempt to create
		0, // the number of elements in pFeatureLevels
		D3D11_SDK_VERSION, // SDK version
		&swapChainDesc, // a pointer to a swap chain description
		&swapChain, // an address of a pointer to the IDXGISwapChain object
		&device, // an address of a pointer to an ID3D11Device object that represents the device created
		NULL, // a pointer to a D3D_FEATURE_LEVEL (did not determine which feature level to support in this case)
		&deviceContext // an address of a pointer to an ID3D11DeviceContext object
	);
	assert(SUCCEEDED(result));// 디바이스와 스왑 체인이 성공적으로 만들어졌는지 확인

	// DXApp.cpp 75번째 라인부터 시작

	return false;
}
