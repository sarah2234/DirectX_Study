#include "stdafx.h"
#include "CMouse.h"

CMouse::CMouse(HWND handle)
	: handle(handle)
	, position(0, 0)
	, wheelValue(0), wheelPrevValue(0), wheelMoveValue(0)
{
	//ZeroMemory: 메모리 영역을 0x00으로 채우는 매크로(함수x)
	//사용법: ZeroMemory(0으로 채울 메모리 블럭의 시작 주소, 0으로 채울 크기)
	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonPrevStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);
	
	ZeroMemory(buttonCount, sizeof(int) * 8);


	doubleClickTime = GetDoubleClickTime(); //Window API 함수, 제어판-마우스에서 설정한 더블클릭 시간 불러옴
	startDoubleClickTime[0] = GetTickCount(); //OS가 부팅된 시점부터 현재까지의 시간(ms)

	for (int i = 1; i < 8; i++)
		startDoubleClickTime[i] = startDoubleClickTime[0];
}

CMouse::~CMouse()
{

}

void CMouse::WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (iMessage == WM_MOUSEMOVE) //WM_MOUSEMOVE 메세지: 마우스가 움직일 때 발생
		//lParam: 마우스 위치 기록
		//wParam: 키 상태 정보 기록
	{
		position.x = (float)LOWORD(lParam); //LOWORD: X의 값
		position.y = (float)HIWORD(lParam); //HIWORD: Y의 값
	}

	if (iMessage == WM_MOUSEWHEEL) //WM_MOUSEWHEEL 메세지: 마우스 휠이 움직일 때 발생
	{
		short temp = (short)HIWORD(wParam);

		wheelPrevValue = wheelValue; //현재 휠에 대한 값을 wheelPrevValue에 저장
		wheelValue += (float)temp; //wheelValue에 현재 휠에 대한 정보 저장
	}
}

void CMouse::Update()
{
	memcpy(buttonPrevStatus, buttonStatus, sizeof(byte) * 8); //현재 마우스 버튼 상태를 과거 마우스 버튼 상태로 저장

	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);

	//GetAsyncKeyState(): 여러 개의 키 입력을 동시에 받을 수 있는 함수
	//VK_LBUTTON: 마우스 왼쪽 버튼
	//VK_RBUTTON: 마우스 오른쪽 버튼
	//VK_MBUTTON: 마우스 가운데 버튼
	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0; //마우스 왼쪽 버튼 누름에 대한 정보 저장
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0; //마우스 오른쪽 버튼 누름에 대한 정보 저장
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0; //마우스 가운데 버튼 누름에 대한 정보 저장

	for (UINT i = 0; i < 8; i++)
	{
		byte prevStatus = buttonPrevStatus[i]; //과거 마우스 버튼 상태
		byte status = buttonStatus[i]; //현재 마우스 버튼 상태

		if (prevStatus == 0 && status == 1)
			buttonMap[i] = Button::Down; //눌리지 않은 상태에서 버튼을 눌렀을 때
		else if (prevStatus == 1 && status == 0)
			buttonMap[i] = Button::Up; //눌린 상태에서 버튼을 그만 눌렀을 때
		else if (prevStatus == 1 && status == 1)
			buttonMap[i] = Button::Press; //버튼을 계속 누르고 있을 때
		else
			buttonMap[i] = Button::None; //버튼을 계속 안 누르고 있을 때
	}


	UINT buttonStatus = GetTickCount(); //OS가 부팅된 시점부터 현재까지의 시간(ms)
	for (UINT i = 0; i < 8; i++)
	{
		if (buttonMap[i] == Button::Down)
		{
			if (buttonCount[i] == 1) //버튼 누른 상태
			{
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					//더블 클릭 실패 (현재 시각 - 더블 클릭 시작 시각) >= (더블 클릭으로 인정해주는 시간 커트라인)
					buttonCount[i] = 0;
			}
			buttonCount[i]++;

			if (buttonCount[i] == 1)
				startDoubleClickTime[i] = buttonStatus; //더블 클릭 시간을 측정하기 위해 현재 시각을 startDoubleClickTime에 기록
		}

		if (buttonMap[i] == Button::Up) //버튼 눌렀다가 뗀 상태
		{
			if (buttonCount[i] == 1)
			{
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					//더블 클릭 실패
					buttonCount[i] = 0;
			}
			else if (buttonCount[i] == 2)
			{
				if (buttonStatus - startDoubleClickTime[i] <= doubleClickTime)
					//doubleClickTime보다 짧은 시간 내에 더블 클릭하면 '더블 클릭'으로 인정
					buttonMap[i] = Button::DoubleClick;

				buttonCount[i] = 0;
			}
		}
	}

	POINT point;
	GetCursorPos(&point); //OS 마우스의 위치 가져오기
	ScreenToClient(handle, &point); //ScreenToClient: 전체 화면 기준인 커서의 좌표를 해당 클라이언트(윈도우) 기준으로 좌표를 변환해주는 함수

	wheelPrevValue = wheelValue; //현재 휠에 대한 값을 wheelPrevValue에 저장
	wheelMoveValue = wheelValue - wheelPrevValue; //마우스 휠이 움직인 만큼 저장
}