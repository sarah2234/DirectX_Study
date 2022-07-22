#pragma once

class ErrorLogger
{
public:
	static void Log(string message);
	static void Log(HRESULT hr, string message);
};
