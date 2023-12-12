#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<stdlib.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Program 2";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
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
	RECT rect[6];
	int x, y, z;
	int x1, y1, z1;
	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 0;i < 6;i++) {
			rect[i].left = 250*i;
			rect[i].top = 0;
			rect[i].right = 250*(i+1);
			rect[i].bottom = 200;
			x = rand() % 255;y = rand() % 255;z = rand() % 255;
			x1 = rand() % 255;y1 = rand() % 255;z1 = rand() % 255;
			if (i > 2) {
				rect[i].left = 250 * (i-3);
				rect[i].top = 200;
				rect[i].right = 250 * (i-2);
				rect[i].bottom = 400;
			}
			SetTextColor(hDC, RGB(x1, y1, z1));
			SetBkColor(hDC, RGB(x, y, z));
			DrawText(hDC, L"abcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\nabcdefghijklmnopqrstuvwxyzzkjjfasew\n", 500, &rect[i], DT_WORDBREAK |DT_LEFT);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}