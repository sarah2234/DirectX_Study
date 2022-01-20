#pragma once
#include <Windows.h>
#include <string>

class WinAPI
{
public:
	static bool InitializeWindow(HINSTANCE hInstance, int width, int height, int nCmdShow, std::wstring windowName);
};