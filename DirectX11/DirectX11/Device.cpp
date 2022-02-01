#include "Device.h"

HWND Device::hwnd = NULL; // static ������ Ŭ���� ������� ������
WNDCLASS Device::wc;
int Device::windowWidth;
int Device::windowHeight;

IDXGISwapChain* Device::swapChain;
ID3D11Device* Device::device = nullptr;
ID3D11DeviceContext* Device::deviceContext;
ID3D11RenderTargetView* Device::renderTargetView;
D3D11_VIEWPORT Device::viewport;

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

Device::Device()
{
}

Device::~Device()
{
}

bool Device::InitializeWindow(HINSTANCE hInstance, int width, int height, int nCmdShow, std::wstring windowName)
{
	if (hwnd != NULL)
		return false;

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

	return true;
}

bool Device::InitializeDirectX()
{
	if (device != nullptr)
		return false;

	// 1. Describe a swap chain
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
	
	// HRESULT: 32-bit value to describe an error or warning (variable 'result' is used for checking in this code)
	
	// 2. Create a device(creating resources/enumerating the capabilities of a display adapter) and a swap chain
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

	// 3. Get information of a back buffer
	ID3D11Texture2D* pBackBuffer; // manages texel data
	result = swapChain->GetBuffer( // find a back buffer in the swap chain
		NULL, // zero-based buffer index (swap effect is 'DXGI_SWAP_EFFECT_DISCARD' => access the first buffer)
		__uuidof(ID3D11Texture2D), // the type of interface used to manipulate the buffer (__uuidof: retrieves the guid attached to the expression)
		(void**)(&pBackBuffer) // a pointer to a back buffer interface (void => gets address regardless of type)
	);
	assert(SUCCEEDED(result));

	// 4. Creates a render target view for accessing resource data
	result = device->CreateRenderTargetView(
		pBackBuffer, // a pointer that represents a render target
		nullptr, // represents a render-target view description (NULL => creates a view that accesses
		&renderTargetView // address of a pointer to an ID3D11RenderTargetView
	);
	assert(SUCCEEDED(result));

	// 5. Release the back buffer
	pBackBuffer->Release(); // similar to 'delete' keyword, but decreases the reference count of the specified interface

	// 6. Bind render targets and depth-stencil buffer to the OM(output-merger) stage
	// OM stage: generates the final rendered pixel color (using a combination of pipeline state, the pixel data generated by the pixel shaders, the contents of the render targets, and the contents of the depth/stencil buffers)
	deviceContext->OMSetRenderTargets(
		1, // number of render targets to bind
		&renderTargetView, // pointer to an array of the render targets to bind to the device
		nullptr // pointerto a depth-stencil view to bind to the device
	);

	// 7. Set viewports
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)windowWidth;
	viewport.Height = (float)windowHeight;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	deviceContext->RSSetViewports( // bind viewports to the rasterizer stage of the pipeline
		1, // number of viewports to bind
		&viewport // an array of viewports to bind to the device
	);

	return true;
}
