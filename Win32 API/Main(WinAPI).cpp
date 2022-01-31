#include "WinAPI.h"

// WinMain: entry-point function (in Console, main function is the entry-point function)
// hInstance: handle to an instance => identify the executable when loaded in memory (ex: 아이콘이나 비트맵 로드)
// hPrevInstance: always NULL in WIN32 (used in 16-bit Windows) => 호환성을 위해 존재하는 인수이므로 신경 x
// pCmdLine: command-line arguments as a Unicode string
// nCmdShow: a flag to identify whether the main application window will be minimized/maximized/shown normally
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	// window handle: 애플리케이션이 무언가를 식별하기 위해 사용하는 숫자

	if (Device::InitializeWindow(hInstance, 1280, 800, nCmdShow, L"Win32 API 공부") == false)
		exit(-1);

	MSG msg = {};
	ZeroMemory(&msg, sizeof(msg));
	// Run the message loop (message: information of change made by the user's input / internal operation of the system)
	// PeekMessage: 메세지 큐에서 메세지를 읽음 (GetMessage와 다르게 메세지 큐가 비었을 때 무작정 기다리지 않음)
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