#include "WinAPI.h"

// WinMain: entry-point function (in Console, main function is the entry-point function)
// hInstance: handle to an instance => identify the executable when loaded in memory (ex: �������̳� ��Ʈ�� �ε�)
// hPrevInstance: always NULL in WIN32 (used in 16-bit Windows) => ȣȯ���� ���� �����ϴ� �μ��̹Ƿ� �Ű� x
// pCmdLine: command-line arguments as a Unicode string
// nCmdShow: a flag to identify whether the main application window will be minimized/maximized/shown normally
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	// window handle: ���ø����̼��� ���𰡸� �ĺ��ϱ� ���� ����ϴ� ����

	if (Device::InitializeWindow(hInstance, 1280, 800, nCmdShow, L"Win32 API ����") == false)
		exit(-1);

	MSG msg = {};
	ZeroMemory(&msg, sizeof(msg));
	// Run the message loop (message: information of change made by the user's input / internal operation of the system)
	// PeekMessage: �޼��� ť���� �޼����� ���� (GetMessage�� �ٸ��� �޼��� ť�� ����� �� ������ ��ٸ��� ����)
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // translate the message
			DispatchMessage(&msg); // transfer the message to WindowProc and WindowProc determines the next move.
		}
		else
		{
			// Later work
		}
	}
}