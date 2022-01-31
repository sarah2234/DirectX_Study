#include "Device.h"

HWND Device::hwnd; // static ������ Ŭ���� ������� ������
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
				TEXT("�����Ͻðڽ��ϱ�?"),
				TEXT("����"),
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
	// swap chain: a collection of buffers used for displaying frames => ���� ���� �����Ϳ� �ĸ� ���� �����͸� ���� �¹ٲٴ� flipping ���
	// prevent 'screen flickering' & 'screen tearing'
	DXGI_SWAP_CHAIN_DESC swapChainDesc; // used to describe a swap chain
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1; // ����� �� ����(�ĸ� ����)�� ����
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // �� ������ �뵵 ���� (���� ����� �׷��ִ� �뵵�� ������)
	swapChainDesc.OutputWindow = hwnd; // ����� ����� �����쿡 ���� �ڵ�
	swapChainDesc.Windowed = true; // â ���� ����
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // �� ���ۿ��� ����Ʈ ���۷� ������ ���� (prevents overhead, the most effective swap effect)
	
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ��� ���� ���� (red, green, blue, alpha�� ���� 8 ��Ʈ ���) (unorm: ����ȭ)
	swapChainDesc.BufferDesc.Width = windowWidth; // ������ �ʺ�
	swapChainDesc.BufferDesc.Height = windowHeight; // ������ ����

	// Anti Aliasing �����
	// 1) Super Sampling: �ػ󵵸� �ø� ���� �ȼ�(���� �ø��� ���� �ȼ� ũ���� 1/4 �ȼ�, �� ���� �ȼ�)�� ����� ����Ͽ� ���� �ػ󵵷� ��� => ū ���
	// 2) Multi Sampling: �ȼ� �� �� ���� ������ ������, ������ ���ÿ� ���� bound checking -> bound ���� �ִ� ���ø� ���� ���� �ȼ��� �������� �� �߾ӿ� �ִ� �ȼ��� �� ����
	swapChainDesc.SampleDesc.Count = 1; // ��Ƽ ���ø� ���� ���� => ��Ƽ ���ø� ��� x
	swapChainDesc.SampleDesc.Quality = 0; // ǰ�� ���� => ��Ƽ ���ø� ��� x
	
	// HRESULT: 32-bit value to describe an error or warning
	// D3D11CreateDeviceAndSwapChain: Create a device(creating resources/enumerating the capabilities of a display adapter) and a swap chain
	// * �Ʒ��� ���ڵ��� �⺻������ ���� ���̹Ƿ� �����ε� �Ʒ��� ���� ���� ��
	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr, // ���÷��� ����̽�(���� ī��) ���� (nullptr: ���ʷ� �߰��� ����̽� ���)
		D3D_DRIVER_TYPE_HARDWARE, // ������ DX11 ����̽� ���� ���� (D3Device will be created on hardware mode if the graphics card supports DX11 feature level)
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
	assert(SUCCEEDED(result));// ����̽��� ���� ü���� ���������� ����������� Ȯ��

	// DXApp.cpp 75��° ���κ��� ����

	return false;
}
