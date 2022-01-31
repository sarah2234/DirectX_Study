#include "WinAPI.h"

// 창의 이벤트 처리 함수
// wParam, lParam: specific interpretations depending on the message
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN: // 키보드의 키를 누르고 있을 때
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(
				NULL,
				TEXT("종료하시겠습니까?"),
				TEXT("종료"),
				MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				// 창 삭제.
				DestroyWindow(hwnd);
			}
		}
		return 0;

	case WM_DESTROY: // 창이 소멸될 때
		PostQuitMessage(0); // 메세지 큐에 WM_QUIT 메세지(응용 프로그램 종료 요청)를 붙임 => GetMessage 함수가 0 리턴
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam); // 윈도우 디폴트 설정에 의해 처리 요청
}

// window class + window handle 생성, 화면에 창 띄우기
bool Device::InitializeWindow(HINSTANCE hInstance, int width, int height, int nCmdShow, std::wstring windowName)
{
	// window class 선언
	WNDCLASS wc = {};

	// 모두 0으로 초기화
	ZeroMemory(&wc, sizeof(wc));

	wc.hInstance = hInstance;
	wc.lpszClassName = L"Window Class";
	wc.lpfnWndProc = WindowProc; // 함수 포인터 => OS에서 발생하는 이벤트들이 발생할 때 알림
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // 아이콘 지정
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW); // 커서 지정 (화살표 모양으로 지정)
	wc.style = CS_HREDRAW | CS_VREDRAW; // 창 크기가 변경될 때 클라이언트 영역의 전체 콘텐츠 다시 그리기
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // 윈도우의 배경색 지정 (default: WHITE_BRUSH)
	wc.hCursor = LoadCursor(NULL, IDC_CROSS); // 커서 지정

	if (RegisterClass(&wc) == false) // window class 구조체의 주소를 인수로 받음 => window class 등록
		exit(-1);

	// 윈도우에 관한 모든 정보를 메모리에 만든 후 윈도우 핸들 리턴
	HWND hwnd = CreateWindow(wc.lpszClassName, // 생성하고자 하는 윈도우의 클래스를 지정하는 문자열
		windowName.c_str(), // 윈도우의 타이틀 바에 나타나는 문자열
		WS_OVERLAPPEDWINDOW | WS_HSCROLL, // 만들고자 하는 윈도우의 형태 지정
		0, 0, // x와 y 좌표(위치), CW_USERDEFAULT로 자동으로 크기 지정 가능 => 메인 윈도우의 경우 전체 화면을 기준, 차일드 윈도우는 부모 윈도우의 좌상단을 기준으로 함
		width, height, // 크기
		NULL, // 부모 윈도우가 있을 경우 부모 윈도우의 핸들 지정 (부모 윈도우가 없으므로 NULL)
		NULL, // 윈도우에서 사용할 메뉴의 핸들 지정 (window class에서 지정한 메뉴를 사용하므로 NULL)
		hInstance, // 프로그램의 핸들 지정
		NULL); // Additional application data (NULL in most of the time)

	if (hwnd == NULL)
		exit(-1);

	// 메모리에 만들어진 윈도우를 화면에 출력
	// hwnd: 화면으로 출력하고자 하는 윈도우 핸들
	// nCmdShow: 윈도우를 화면에 출력하는 방법(매크로 상수들이 있지만 nCmdshow 넘기면 됨)
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
}

