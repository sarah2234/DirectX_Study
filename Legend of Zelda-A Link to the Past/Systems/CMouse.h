#pragma once

class CMouse
{
public:
	CMouse(HWND handle);
	~CMouse();

	void WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam);

	void Update();

	D3DXVECTOR2 Position() { return position; }

private:
	enum class Button
	{
		None, Down, Up, Press, DoubleClick,
	};

public:
	bool Down(UINT button)
	{
		return buttonMap[button] == Button::Down;
	}

	bool Up(UINT button)
	{
		return buttonMap[button] == Button::Up;
	}

	bool Press(UINT button)
	{
		return buttonMap[button] == Button::Press;
	}

	bool DoubleClick(UINT button)
	{
		return buttonMap[button] == Button::DoubleClick;
	}

	float Wheel() { return wheelMoveValue; }


private:
	HWND handle;

	D3DXVECTOR2 position;

	byte buttonStatus[8];
	byte buttonPrevStatus[8];
	Button buttonMap[8];

	float wheelValue;
	float wheelPrevValue;
	float wheelMoveValue;

	DWORD doubleClickTime;
	DWORD startDoubleClickTime[8];
	int buttonCount[8];
};