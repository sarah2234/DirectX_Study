#include "stdafx.h"
#include "CMouse.h"

CMouse::CMouse(HWND handle)
	: handle(handle)
	, position(0, 0)
	, wheelValue(0), wheelPrevValue(0), wheelMoveValue(0)
{
	//ZeroMemory: �޸� ������ 0x00���� ä��� ��ũ��(�Լ�x)
	//����: ZeroMemory(0���� ä�� �޸� ���� ���� �ּ�, 0���� ä�� ũ��)
	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonPrevStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);
	
	ZeroMemory(buttonCount, sizeof(int) * 8);


	doubleClickTime = GetDoubleClickTime(); //Window API �Լ�, ������-���콺���� ������ ����Ŭ�� �ð� �ҷ���
	startDoubleClickTime[0] = GetTickCount(); //OS�� ���õ� �������� ��������� �ð�(ms)

	for (int i = 1; i < 8; i++)
		startDoubleClickTime[i] = startDoubleClickTime[0];
}

CMouse::~CMouse()
{

}

void CMouse::WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (iMessage == WM_MOUSEMOVE) //WM_MOUSEMOVE �޼���: ���콺�� ������ �� �߻�
		//lParam: ���콺 ��ġ ���
		//wParam: Ű ���� ���� ���
	{
		position.x = (float)LOWORD(lParam); //LOWORD: X�� ��
		position.y = (float)HIWORD(lParam); //HIWORD: Y�� ��
	}

	if (iMessage == WM_MOUSEWHEEL) //WM_MOUSEWHEEL �޼���: ���콺 ���� ������ �� �߻�
	{
		short temp = (short)HIWORD(wParam);

		wheelPrevValue = wheelValue; //���� �ٿ� ���� ���� wheelPrevValue�� ����
		wheelValue += (float)temp; //wheelValue�� ���� �ٿ� ���� ���� ����
	}
}

void CMouse::Update()
{
	memcpy(buttonPrevStatus, buttonStatus, sizeof(byte) * 8); //���� ���콺 ��ư ���¸� ���� ���콺 ��ư ���·� ����

	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);

	//GetAsyncKeyState(): ���� ���� Ű �Է��� ���ÿ� ���� �� �ִ� �Լ�
	//VK_LBUTTON: ���콺 ���� ��ư
	//VK_RBUTTON: ���콺 ������ ��ư
	//VK_MBUTTON: ���콺 ��� ��ư
	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0; //���콺 ���� ��ư ������ ���� ���� ����
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0; //���콺 ������ ��ư ������ ���� ���� ����
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0; //���콺 ��� ��ư ������ ���� ���� ����

	for (UINT i = 0; i < 8; i++)
	{
		byte prevStatus = buttonPrevStatus[i]; //���� ���콺 ��ư ����
		byte status = buttonStatus[i]; //���� ���콺 ��ư ����

		if (prevStatus == 0 && status == 1)
			buttonMap[i] = Button::Down; //������ ���� ���¿��� ��ư�� ������ ��
		else if (prevStatus == 1 && status == 0)
			buttonMap[i] = Button::Up; //���� ���¿��� ��ư�� �׸� ������ ��
		else if (prevStatus == 1 && status == 1)
			buttonMap[i] = Button::Press; //��ư�� ��� ������ ���� ��
		else
			buttonMap[i] = Button::None; //��ư�� ��� �� ������ ���� ��
	}


	UINT buttonStatus = GetTickCount(); //OS�� ���õ� �������� ��������� �ð�(ms)
	for (UINT i = 0; i < 8; i++)
	{
		if (buttonMap[i] == Button::Down)
		{
			if (buttonCount[i] == 1) //��ư ���� ����
			{
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					//���� Ŭ�� ���� (���� �ð� - ���� Ŭ�� ���� �ð�) >= (���� Ŭ������ �������ִ� �ð� ĿƮ����)
					buttonCount[i] = 0;
			}
			buttonCount[i]++;

			if (buttonCount[i] == 1)
				startDoubleClickTime[i] = buttonStatus; //���� Ŭ�� �ð��� �����ϱ� ���� ���� �ð��� startDoubleClickTime�� ���
		}

		if (buttonMap[i] == Button::Up) //��ư �����ٰ� �� ����
		{
			if (buttonCount[i] == 1)
			{
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					//���� Ŭ�� ����
					buttonCount[i] = 0;
			}
			else if (buttonCount[i] == 2)
			{
				if (buttonStatus - startDoubleClickTime[i] <= doubleClickTime)
					//doubleClickTime���� ª�� �ð� ���� ���� Ŭ���ϸ� '���� Ŭ��'���� ����
					buttonMap[i] = Button::DoubleClick;

				buttonCount[i] = 0;
			}
		}
	}

	POINT point;
	GetCursorPos(&point); //OS ���콺�� ��ġ ��������
	ScreenToClient(handle, &point); //ScreenToClient: ��ü ȭ�� ������ Ŀ���� ��ǥ�� �ش� Ŭ���̾�Ʈ(������) �������� ��ǥ�� ��ȯ���ִ� �Լ�

	wheelPrevValue = wheelValue; //���� �ٿ� ���� ���� wheelPrevValue�� ����
	wheelMoveValue = wheelValue - wheelPrevValue; //���콺 ���� ������ ��ŭ ����
}