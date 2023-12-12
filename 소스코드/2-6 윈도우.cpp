#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
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
	RECT rect[100]{};
	int x, y, z;
	int x1, y1, z1;
	int s = 0, f = 0;
	s = rand() % 9 + 2;
	f = rand() % 9 + 2;
	int t = 0, g = 0;
	int i = 0, ran = 0;
	TCHAR shape[20] = L"               ";
	TCHAR shape1[20]=L"\n               ";
	TCHAR shape2[20] = L"\n\n               ";
	TCHAR shape3[20] = L"\n\n\n               ";
	TCHAR shape4[20] = L"\n\n\n\n               ";
	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int j = 0; j < s; j++) {
			for (int k = 0; k < f; k++) {
				t = 800 / s;
				g = 600 / f;
				rect[i].left = t * j;
				rect[i].top = 0 + k * g;
				rect[i].right = t * (j + 1);
				rect[i].bottom = g + g * k;
				i++;
			}
		}
		for (int i = 0; i < s * f; i++) {
			x = rand() % 255; y = rand() % 255; z = rand() % 255;
			x1 = rand() % 255; y1 = rand() % 255; z1 = rand() % 255;
			SetTextColor(hDC, RGB(x1, y1, z1));
			SetBkColor(hDC, RGB(x, y, z));
			wsprintf(shape, L"               ");
			wsprintf(shape1, L"\n               ");
			wsprintf(shape2, L"\n\n               ");
			wsprintf(shape3, L"\n\n\n               ");
			wsprintf(shape4, L"\n\n\n\n               ");
			DrawText(hDC,shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
			DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
			DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
			DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
			DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
			ran = rand()%6;
			switch (ran) {
			case 0:
				SetTextColor(hDC, RGB(255, 255, 255));
				SetBkColor(hDC, RGB(255, 255, 255));
				wsprintf(shape , L"           ");
				wsprintf(shape1, L"\n       ");
				wsprintf(shape2, L"\n\n   ");
				wsprintf(shape3, L"\n\n\n       ");
				wsprintf(shape4, L"\n\n\n\n           ");
				DrawText(hDC, shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
				break;
			case 1:
				SetTextColor(hDC, RGB(255, 255, 255));
				SetBkColor(hDC, RGB(255, 255, 255));
				wsprintf(shape1, L"\n           ");
				wsprintf(shape2, L"\n\n           ");
				wsprintf(shape3, L"\n\n\n           ");
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				SetTextColor(hDC, RGB(x1, y1, z1));
				SetBkColor(hDC, RGB(x, y, z));
				wsprintf(shape, L"   ");
				wsprintf(shape1, L"\n   ");
				wsprintf(shape2, L"\n\n   ");
				wsprintf(shape3, L"\n\n\n   ");
				wsprintf(shape4, L"\n\n\n\n    ");
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				break;
			case 2:
				SetTextColor(hDC, RGB(255, 255, 255));
				SetBkColor(hDC, RGB(255, 255, 255));
				wsprintf(shape, L"               ");
				wsprintf(shape1, L"\n               ");
				wsprintf(shape2, L"\n\n               ");
				wsprintf(shape3, L"\n\n\n               ");
				wsprintf(shape4, L"\n\n\n\n               ");
				DrawText(hDC, shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
				SetTextColor(hDC, RGB(x1, y1, z1));
				SetBkColor(hDC, RGB(x, y, z));
				wsprintf(shape, L"           ");
				wsprintf(shape1, L"\n       ");
				wsprintf(shape2, L"\n\n   ");
				wsprintf(shape3, L"\n\n\n       ");
				wsprintf(shape4, L"\n\n\n\n           ");
				DrawText(hDC, shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
				SetTextColor(hDC, RGB(255, 255, 255));
				SetBkColor(hDC, RGB(255, 255, 255));
				wsprintf(shape, L"        ");
				wsprintf(shape1, L"\n    ");
				wsprintf(shape2, L"\n\n");
				wsprintf(shape3, L"\n\n\n    ");
				wsprintf(shape4, L"\n\n\n\n        ");
				DrawText(hDC, shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
				break;
			case 3:
				SetTextColor(hDC, RGB(255, 255, 255));
				SetBkColor(hDC, RGB(255, 255, 255));
				wsprintf(shape, L"               ");
				wsprintf(shape1, L"\n               ");
				wsprintf(shape2, L"\n\n               ");
				wsprintf(shape3, L"\n\n\n               ");
				wsprintf(shape4, L"\n\n\n\n               ");
				DrawText(hDC, shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
				SetTextColor(hDC, RGB(x1, y1, z1));
				SetBkColor(hDC, RGB(x, y, z));
				wsprintf(shape, L"           ");
				wsprintf(shape1, L"\n       ");
				wsprintf(shape2, L"\n\n   ");
				wsprintf(shape3, L"\n\n\n       ");
				wsprintf(shape4, L"\n\n\n\n           ");
				DrawText(hDC, shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
				break;
			case 4:
				SetTextColor(hDC, RGB(255, 255, 255));
				SetBkColor(hDC, RGB(255, 255, 255));
				wsprintf(shape, L"               ");
				wsprintf(shape1, L"\n               ");
				wsprintf(shape2, L"\n\n               ");
				wsprintf(shape3, L"\n\n\n               ");
				wsprintf(shape4, L"\n\n\n\n               ");
				DrawText(hDC, shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
				SetTextColor(hDC, RGB(x1, y1, z1));
				SetBkColor(hDC, RGB(x, y, z));
				wsprintf(shape, L"             ");
				wsprintf(shape1, L"\n          ");
				wsprintf(shape2, L"\n\n       ");
				wsprintf(shape3, L"\n\n\n     ");
				wsprintf(shape4, L"\n\n\n\n   ");
				DrawText(hDC, shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
				break;
			case 5:
				SetTextColor(hDC, RGB(255, 255, 255));
				SetBkColor(hDC, RGB(255, 255, 255));
				wsprintf(shape, L"               ");
				wsprintf(shape1, L"\n               ");
				wsprintf(shape2, L"\n\n               ");
				wsprintf(shape3, L"\n\n\n               ");
				wsprintf(shape4, L"\n\n\n\n               ");
				DrawText(hDC, shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
				SetTextColor(hDC, RGB(x1, y1, z1));
				SetBkColor(hDC, RGB(x, y, z));
				wsprintf(shape, L"   ");
				wsprintf(shape1, L"\n       ");
				wsprintf(shape2, L"\n\n            ");
				wsprintf(shape3, L"\n\n\n       ");
				wsprintf(shape4, L"\n\n\n\n    ");
				DrawText(hDC, shape, lstrlen(shape), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_WORDBREAK | DT_CENTER);
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i], DT_WORDBREAK | DT_CENTER);
				break;
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}