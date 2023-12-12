#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<stdlib.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Program 2";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
int wsprintf(LPTSTR lpOut, LPCTSTR lpFmt);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR IpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	srand(time(NULL));
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT ps;
	HDC hDC;
	TCHAR lpOut[100];
	int x, y, x1, y1, x2, y2, x3, y3, x4, y4;
	x = rand() % 600;x1 = rand() % 600;x2 = rand() % 600;x3 = rand() % 700;x4 = 400;
	y = rand() & 500;y1 = rand() & 500;y2 = rand() & 500;y3 = rand() & 500;y4 = 300;
	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		wsprintf(lpOut, L"1st sentence: (%d, %d)", x, y);
		TextOut(hDC, x, y, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, L"2st sentence: (%d, %d)", x1, y1);
		TextOut(hDC, x1, y1, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, L"3st sentence: (%d, %d)", x2, y2);
		TextOut(hDC, x2, y2, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, L"4st sentence: (%d, %d)", x3, y3);
		TextOut(hDC, x3, y3, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, L"center: (%d, %d)", x4, y4);
		TextOut(hDC, x4, y4, lpOut, lstrlen(lpOut));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}