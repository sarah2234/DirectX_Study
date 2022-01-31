#include "WinAPI.h"

// â�� �̺�Ʈ ó�� �Լ�
// wParam, lParam: specific interpretations depending on the message
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN: // Ű������ Ű�� ������ ���� ��
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(
				NULL,
				TEXT("�����Ͻðڽ��ϱ�?"),
				TEXT("����"),
				MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				// â ����.
				DestroyWindow(hwnd);
			}
		}
		return 0;

	case WM_DESTROY: // â�� �Ҹ�� ��
		PostQuitMessage(0); // �޼��� ť�� WM_QUIT �޼���(���� ���α׷� ���� ��û)�� ���� => GetMessage �Լ��� 0 ����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam); // ������ ����Ʈ ������ ���� ó�� ��û
}

// window class + window handle ����, ȭ�鿡 â ����
bool Device::InitializeWindow(HINSTANCE hInstance, int width, int height, int nCmdShow, std::wstring windowName)
{
	// window class ����
	WNDCLASS wc = {};

	// ��� 0���� �ʱ�ȭ
	ZeroMemory(&wc, sizeof(wc));

	wc.hInstance = hInstance;
	wc.lpszClassName = L"Window Class";
	wc.lpfnWndProc = WindowProc; // �Լ� ������ => OS���� �߻��ϴ� �̺�Ʈ���� �߻��� �� �˸�
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // ������ ����
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW); // Ŀ�� ���� (ȭ��ǥ ������� ����)
	wc.style = CS_HREDRAW | CS_VREDRAW; // â ũ�Ⱑ ����� �� Ŭ���̾�Ʈ ������ ��ü ������ �ٽ� �׸���
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // �������� ���� ���� (default: WHITE_BRUSH)
	wc.hCursor = LoadCursor(NULL, IDC_CROSS); // Ŀ�� ����

	if (RegisterClass(&wc) == false) // window class ����ü�� �ּҸ� �μ��� ���� => window class ���
		exit(-1);

	// �����쿡 ���� ��� ������ �޸𸮿� ���� �� ������ �ڵ� ����
	HWND hwnd = CreateWindow(wc.lpszClassName, // �����ϰ��� �ϴ� �������� Ŭ������ �����ϴ� ���ڿ�
		windowName.c_str(), // �������� Ÿ��Ʋ �ٿ� ��Ÿ���� ���ڿ�
		WS_OVERLAPPEDWINDOW | WS_HSCROLL, // ������� �ϴ� �������� ���� ����
		0, 0, // x�� y ��ǥ(��ġ), CW_USERDEFAULT�� �ڵ����� ũ�� ���� ���� => ���� �������� ��� ��ü ȭ���� ����, ���ϵ� ������� �θ� �������� �»���� �������� ��
		width, height, // ũ��
		NULL, // �θ� �����찡 ���� ��� �θ� �������� �ڵ� ���� (�θ� �����찡 �����Ƿ� NULL)
		NULL, // �����쿡�� ����� �޴��� �ڵ� ���� (window class���� ������ �޴��� ����ϹǷ� NULL)
		hInstance, // ���α׷��� �ڵ� ����
		NULL); // Additional application data (NULL in most of the time)

	if (hwnd == NULL)
		exit(-1);

	// �޸𸮿� ������� �����츦 ȭ�鿡 ���
	// hwnd: ȭ������ ����ϰ��� �ϴ� ������ �ڵ�
	// nCmdShow: �����츦 ȭ�鿡 ����ϴ� ���(��ũ�� ������� ������ nCmdshow �ѱ�� ��)
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
}

