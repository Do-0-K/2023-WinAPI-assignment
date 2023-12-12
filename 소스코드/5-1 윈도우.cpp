#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include "resource2.h"
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Program 2";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
int wsprintf(LPTSTR lpOut, LPCTSTR lpFmt);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR IpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	srand(time(NULL));
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 650, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc , memdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static BOOL Selection;
	static HBITMAP hbitmap;
	static int a = 0, r = 0, p = 0;
	static int x = 0, y = 0;
	int mx = 0, my = 0;
	static int chose = 0;
	static int k = 0, k1 = 0, k2 = 0, k3 = 0;
	static int cnt = 0;
	switch (iMsg) {
	case WM_CREATE:
		Selection = FALSE;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hbitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		memdc = CreateCompatibleDC(hdc);
		SelectObject(memdc, (HBITMAP)hbitmap);
		if (p == 0) {
			if (a == 0) {
				if (r == 0) {
					StretchBlt(hdc, 0, 0, 300, 300, memdc, 0, 0,650,400,SRCCOPY);
				}
				if (r == 1) {
					StretchBlt(hdc, 0, 0, 300, 300, memdc, 0, 0,650,400, NOTSRCCOPY);
				}
			}
			if (a == 1) {
				if (r == 0) {
					StretchBlt(hdc, 0, 0, 800, 650, memdc, 0, 0, 650, 400, SRCCOPY);
				}
				if (r == 1) {
					StretchBlt(hdc, 0, 0, 800, 650, memdc, 0, 0, 650, 400, NOTSRCCOPY);
				}
			}
		}
		if (p == 1) {
			if (a == 0) {
				if (r == 0) {
					StretchBlt(hdc, 0 + k, 0, 300 + x + k, 300 + y, memdc, 0, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 0 , 0, k, 300 + y, memdc, 650-k, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 300 + x + k, 0, -k, 300 + y, memdc, 0, 0, 650, 400, SRCCOPY);

					StretchBlt(hdc, 300 + x + k1, 0, 800 - (300 + x) + k1, 300 + y, memdc, 0, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 300 + x, 0, k1, 300 + y, memdc, 650 - k1, 0, 550, 400, SRCCOPY);
					StretchBlt(hdc, 800 + k1, 0, -k1, 300 + y, memdc, 0, 0, 650, 400, SRCCOPY);

					StretchBlt(hdc, 0 + k2, 300 + y, 300 + x + k2, 650 - (300 + y), memdc, 0, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 0, 300 + y, k2, 300 + y, memdc, 650 - k2, 0, 550, 400, SRCCOPY);
					StretchBlt(hdc, 300 + x + k2, 300 + y, -k2, 650 - (300 + y), memdc, 0, 0, 650, 400, SRCCOPY);

					StretchBlt(hdc, 300 + x + k3, 300 + y, 800 - (300 + x) + k3, 650 - (300 + y), memdc, 0, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 300 + x, 300 + y, k3, 300 + y, memdc, 650 - k3, 0, 550, 400, SRCCOPY);
					StretchBlt(hdc, 800 + k3 , 300 + y, -k3, 650 - (300 + y), memdc, 0, 0, 650, 400, SRCCOPY);
					if (chose == 1) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 0, 0, NULL);
						LineTo(hdc, 300+x, 0);
						MoveToEx(hdc, 300+x, 0, NULL);
						LineTo(hdc, 300 + x, 300+y);
						MoveToEx(hdc, 0, 0, NULL);
						LineTo(hdc, 0, 300+y);
						MoveToEx(hdc, 0, 300+y, NULL);
						LineTo(hdc, 300+x, 300+y);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 2) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 300+x, 0, NULL);
						LineTo(hdc, 800, 0);
						MoveToEx(hdc, 800, 0, NULL);
						LineTo(hdc, 800 , 300 + y);
						MoveToEx(hdc, 300+x, 0, NULL);
						LineTo(hdc, 300+x, 300 + y);
						MoveToEx(hdc, 300+x, 300 + y, NULL);
						LineTo(hdc, 800, 300 + y);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 3) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 0, 300+y, NULL);
						LineTo(hdc, 300 + x, 300+y);
						MoveToEx(hdc, 300 + x, 300+y, NULL);
						LineTo(hdc, 300 + x, 650);
						MoveToEx(hdc, 0, 300+y, NULL);
						LineTo(hdc, 0, 650);
						MoveToEx(hdc, 0, 650, NULL);
						LineTo(hdc, 300 + x, 650);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 4) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 300+x, 300+y, NULL);
						LineTo(hdc, 800, 300+y);
						MoveToEx(hdc, 800, 300+y, NULL);
						LineTo(hdc, 800, 650);
						MoveToEx(hdc, 300+x, 300+y, NULL);
						LineTo(hdc, 300+x, 650);
						MoveToEx(hdc, 300+x, 650, NULL);
						LineTo(hdc, 800, 650);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
				}
				if (r == 1) {
					StretchBlt(hdc, 0 + k, 0, 300 + x + k, 300 + y, memdc, 0, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 0, 0, k, 300 + y, memdc, 650 - k, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 300 + x + k, 0, -k, 300 + y, memdc, 0, 0, 650, 400, NOTSRCCOPY);

					StretchBlt(hdc, 300 + x + k1, 0, 800 - (300 + x) + k1, 300 + y, memdc, 0, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 300 + x, 0, k1, 300 + y, memdc, 650 - k1, 0, 550, 400, NOTSRCCOPY);
					StretchBlt(hdc, 800 + x + k1, 0, -k1, 300 + y, memdc, 0, 0, 650, 400, NOTSRCCOPY);

					StretchBlt(hdc, 0 + k2, 300 + y, 300 + x + k2, 650 - (300 + y), memdc, 0, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 0, 300 + y, k2, 300 + y, memdc, 650 - k2, 0, 550, 400, NOTSRCCOPY);
					StretchBlt(hdc, 300 + x + k2, 300 + y, -k2, 650 - (300 + y), memdc, 0, 0, 650, 400, NOTSRCCOPY);

					StretchBlt(hdc, 300 + x + k3, 300 + y, 800 - (300 + x) + k3, 650 - (300 + y), memdc, 0, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 300 + x, 300 + y, k3, 300 + y, memdc, 650 - k3, 0, 550, 400, NOTSRCCOPY);
					StretchBlt(hdc, 800 + k3, 300 + y, -k3, 650 - (300 + y), memdc, 0, 0, 650, 400, NOTSRCCOPY);
					if (chose == 1) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 0, 0, NULL);
						LineTo(hdc, 300 + x, 0);
						MoveToEx(hdc, 300 + x, 0, NULL);
						LineTo(hdc, 300 + x, 300 + y);
						MoveToEx(hdc, 0, 0, NULL);
						LineTo(hdc, 0, 300 + y);
						MoveToEx(hdc, 0, 300 + y, NULL);
						LineTo(hdc, 300 + x, 300 + y);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 2) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 300 + x, 0, NULL);
						LineTo(hdc, 800, 0);
						MoveToEx(hdc, 800, 0, NULL);
						LineTo(hdc, 800, 300 + y);
						MoveToEx(hdc, 300 + x, 0, NULL);
						LineTo(hdc, 300 + x, 300 + y);
						MoveToEx(hdc, 300 + x, 300 + y, NULL);
						LineTo(hdc, 800, 300 + y);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 3) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 0, 300 + y, NULL);
						LineTo(hdc, 300 + x, 300 + y);
						MoveToEx(hdc, 300 + x, 300 + y, NULL);
						LineTo(hdc, 300 + x, 650);
						MoveToEx(hdc, 0, 300 + y, NULL);
						LineTo(hdc, 0, 650);
						MoveToEx(hdc, 0, 650, NULL);
						LineTo(hdc, 300 + x, 650);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 4) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 300 + x, 300 + y, NULL);
						LineTo(hdc, 800, 300 + y);
						MoveToEx(hdc, 800, 300 + y, NULL);
						LineTo(hdc, 800, 650);
						MoveToEx(hdc, 300 + x, 300 + y, NULL);
						LineTo(hdc, 300 + x, 650);
						MoveToEx(hdc, 300 + x, 650, NULL);
						LineTo(hdc, 800, 650);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
				}
			}
			if (a == 1) {
				if (r == 0) {
					StretchBlt(hdc, 0 + k, 0, 800 + x + k, 650 + y, memdc, 0, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 0, 0, k, 650 + y, memdc, 550 - k, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 800 + x + k, 0,  -k, 650 + y, memdc, 0, 0,  650, 400, SRCCOPY);

					StretchBlt(hdc, 800 + x + k1, 0, 800 - (800 + x) + k1, 650 + y, memdc, 0, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 800 + x, 0, k1, 650 + y, memdc, 650 - k1, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 800 + k1, 0, -k1, 650 + y, memdc, 0, 0, 650, 400, SRCCOPY);

					StretchBlt(hdc, 0 + k2, 650 + y, 800 + x + k2, 650 - (650 + y), memdc, 0, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 0, 650 + y, k2, 650 + y, memdc, 650 - k2, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 800 + x + k2, 650 + y, -k2, 650 - (650 + y), memdc, 0, 0, 650, 400, SRCCOPY);

					StretchBlt(hdc, 800 + x + k3, 650 + y, 800 - (800 + x) + k3, 650 - (650 + y), memdc, 0, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 800 + x, 650 + y, k3, 650 + y, memdc, 650 - k3, 0, 650, 400, SRCCOPY);
					StretchBlt(hdc, 800 +k3, 650+y, -k3, 650-(650 + y), memdc, 0, 0, 650, 400, SRCCOPY);
					if (chose == 1) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 0, 0, NULL);
						LineTo(hdc, 800 + x, 0);
						MoveToEx(hdc, 800 + x, 0, NULL);
						LineTo(hdc, 800 + x, 650 + y);
						MoveToEx(hdc, 0, 0, NULL);
						LineTo(hdc, 0, 650 + y);
						MoveToEx(hdc, 0, 650 + y, NULL);
						LineTo(hdc, 800 + x, 650 + y);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 2) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 800 + x, 0, NULL);
						LineTo(hdc, 800, 0);
						MoveToEx(hdc, 800, 0, NULL);
						LineTo(hdc, 800, 650 + y);
						MoveToEx(hdc, 800 + x, 0, NULL);
						LineTo(hdc, 800 + x, 650 + y);
						MoveToEx(hdc, 800 + x, 650 + y, NULL);
						LineTo(hdc, 800, 650 + y);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 3) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 0, 650 + y, NULL);
						LineTo(hdc, 800 + x, 650 + y);
						MoveToEx(hdc, 800 + x, 650 + y, NULL);
						LineTo(hdc, 800 + x, 650);
						MoveToEx(hdc, 0, 650 + y, NULL);
						LineTo(hdc, 0, 650);
						MoveToEx(hdc, 0, 650, NULL);
						LineTo(hdc, 800 + x, 650);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 4) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 800 + x, 650 + y, NULL);
						LineTo(hdc, 800, 650 + y);
						MoveToEx(hdc, 800, 650 + y, NULL);
						LineTo(hdc, 800, 650);
						MoveToEx(hdc, 800 + x, 650 + y, NULL);
						LineTo(hdc, 800 + x, 650);
						MoveToEx(hdc, 800 + x, 650, NULL);
						LineTo(hdc, 800, 650);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
				}
				if (r == 1) {
					StretchBlt(hdc, 0 + k, 0, 800 + x + k, 650 + y, memdc, 0, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 0, 0, k, 650 + y, memdc, 550 - k, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 800 + x + k, 0, -k, 650 + y, memdc, 0, 0, 650, 400, NOTSRCCOPY);

					StretchBlt(hdc, 800 + x + k1, 0, 800 - (800 + x) + k1, 650 + y, memdc, 0, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 800 + x, 0, k1, 650 + y, memdc, 650 - k1, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 800 + k1, 0, -k1, 650 + y, memdc, 0, 0, 650, 400, NOTSRCCOPY);

					StretchBlt(hdc, 0 + k2, 650 + y, 800 + x + k2, 650 - (650 + y), memdc, 0, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 0, 650 + y, k2, 650 + y, memdc, 650 - k2, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 800 + x + k2, 650 + y, -k2, 650 - (650 + y), memdc, 0, 0, 650, 400, NOTSRCCOPY);

					StretchBlt(hdc, 800 + x + k3, 650 + y, 800 - (800 + x) + k3, 650 - (650 + y), memdc, 0, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 800 + x, 650 + y, k3, 650 + y, memdc, 650 - k3, 0, 650, 400, NOTSRCCOPY);
					StretchBlt(hdc, 800 + k3, 650 + y, -k3, 650 - (650 + y), memdc, 0, 0, 650, 400, NOTSRCCOPY);
					if (chose == 1) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 0, 0, NULL);
						LineTo(hdc, 800 + x, 0);
						MoveToEx(hdc, 800 + x, 0, NULL);
						LineTo(hdc, 800 + x, 650 + y);
						MoveToEx(hdc, 0, 0, NULL);
						LineTo(hdc, 0, 650 + y);
						MoveToEx(hdc, 0, 650 + y, NULL);
						LineTo(hdc, 800 + x, 650 + y);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 2) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 800 + x, 0, NULL);
						LineTo(hdc, 800, 0);
						MoveToEx(hdc, 800, 0, NULL);
						LineTo(hdc, 800, 650 + y);
						MoveToEx(hdc, 800 + x, 0, NULL);
						LineTo(hdc, 800 + x, 650 + y);
						MoveToEx(hdc, 800 + x, 650 + y, NULL);
						LineTo(hdc, 800, 650 + y);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 3) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 0, 650 + y, NULL);
						LineTo(hdc, 800 + x, 650 + y);
						MoveToEx(hdc, 800 + x, 650 + y, NULL);
						LineTo(hdc, 800 + x, 650);
						MoveToEx(hdc, 0, 650 + y, NULL);
						LineTo(hdc, 0, 650);
						MoveToEx(hdc, 0, 650, NULL);
						LineTo(hdc, 800 + x, 650);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
					if (chose == 4) {
						hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						MoveToEx(hdc, 800 + x, 650 + y, NULL);
						LineTo(hdc, 800, 650 + y);
						MoveToEx(hdc, 800, 650 + y, NULL);
						LineTo(hdc, 800, 650);
						MoveToEx(hdc, 800 + x, 650 + y, NULL);
						LineTo(hdc, 800 + x, 650);
						MoveToEx(hdc, 800 + x, 650, NULL);
						LineTo(hdc, 800, 650);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
					}
				}
			}
		}
		DeleteDC(memdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (p == 1) {
			if (a == 0) {
				if (0 < mx && mx < 300 + x) {
					if (0 < my && my < 300 + y) {
						chose = 1;
						k1 = 0;k2 = 0;k3 = 0;
					}
				}
				if (300+x < mx && mx < 800) {
					if (0 < my && my < 300 + y) {
						chose = 2;
						k = 0;k2 = 0;k3 = 0;
					}
				}
				if (0 < mx && mx < 300 + x) {
					if (300+y < my && my < 650) {
						chose = 3;
						k = 0;k1 = 0;k3 = 0;
					}
				}
				if (300+x < mx && mx < 800) {
					if (300+y < my && my < 650) {
						chose = 4;
						k = 0;k1 = 0;k2 = 0;
					}
				}
			}
			if (a == 1) {
				if (0 < mx && mx < 800 + x) {
					if (0 < my && my < 650 + y) {
						chose = 1;
					}
				}
				if (800 + x < mx && mx < 800) {
					if (0 < my && my < 650 + y) {
						chose = 2;
					}
				}
				if (0 < mx && mx < 800 + x) {
					if (650 + y < my && my < 650) {
						chose = 3;
					}
				}
				if (800 + x < mx && mx < 800) {
					if (650 + y < my && my < 650) {
						chose = 4;
					}
				}
			}
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == VK_LEFT) {
			if (chose == 1) {
				k -= 10;
				k1 = 0;
				k2 = 0;
				k3 = 0;
				if (a == 0) {
					if (300 + x + k == 0) {
						k = 0;
					}
				}
				if (a == 1) {
					if (800 + x + k == 0) {
						k = 0;
					}
				}
			}
			if (chose == 2) {
				k1 -= 10;
				k = 0;
				k2 = 0;
				k3 = 0;
				if (a == 0) {
					if (800 - (300 + x) + k1 == 0) {
						k1 = 0;
					}
				}
				if (a == 1) {
					if (800 - (800 + x) + k1 == 0) {
						k1 = 0;
					}
				}
			}
			if (chose == 3) {
				k2 -= 10;
				k1 = 0;
				k = 0;
				k3 = 0;
				if (a == 0) {
					if (300 + x + k2==0) {
						k2 = 0;
					}
				}
				if (a == 1) {
					if (800 + x + k2 == 0) {
						k2 = 0;
					}
				}
			}
			if (chose == 4) {
				k3 -= 10;
				k1 = 0;
				k2 = 0;
				k = 0;
				if (a == 0) {
					if (800 - (300 + x) + k3 == 0) {
						k3 = 0;
					}
				}
				if (a == 1) {
					if (800 - (800 + x) + k3 == 0) {
						k3 = 0;
					}
				}
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (wParam == VK_RIGHT) {
			if (chose == 1) {
				k += 10;
				k1 = 0;
				k2 = 0;
				k3 = 0;
				if (a == 0) {
					if (k == 300 + x) {
						k = 0;
					}
				}
				if (a == 1) {
					if (k == 800 + x) {
						k = 0;
					}
				}
			}
			if (chose == 2) {
				k1 += 10;
				k = 0;
				k2 = 0;
				k3 = 0;
				if (a == 0) {
					if (300 + x + k1 == 800 - (300 + x)) {
						k1 = 0;
					}
				}
				if (a == 1) {
					if (800 + x + k1 == 800 - (800 + x)) {
						k1 = 0;
					}
				}
			}
			if (chose == 3) {
				k2 += 10;
				k1 = 0;
				k = 0;
				k3 = 0;
				if (a == 0) {
					if (k2 == 300 + x) {
						k2 = 0;
					}
				}
				if (a == 1) {
					if (k2 == 800 + x) {
						k2 = 0;
					}
				}
			}
			if (chose == 4) {
				k3 += 10;
				k1 = 0;
				k2 = 0;
				k = 0;
				if (a == 0) {
					if (300 + x + k3 == 800 - (300 + x)) {
						k3 = 0;
					}
				}
				if (a == 1) {
					if (800 + x + k3 == 800 - (800 + x)) {
						k3 = 0;
					}
				}
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == 'a' || wParam == 'A') {
			a++;
			p = 0;
			x = 0;y = 0;
			if (a > 1) {
				a = 0;
			}
		}
		if (wParam == 'r' || wParam == 'R') {
			r++;
			p = 0;
			x = 0;y = 0;
			if (r > 1) {
				r = 0;
			}
		}
		if (wParam == '-') {
			p = 1;
			x -= 50;
			y -= 50;
		}
		if (wParam == '+') {
			p = 1;
			x += 50;
			y += 50;
		}
		if (wParam == 'S' || wParam == 's') {
			p = 0;
			x = 0;
			y = 0;
			r = 0;
			a = 0;
		}
		if (wParam == 'q' || wParam == 'Q') {
			KillTimer(hwnd, 1);
			PostQuitMessage(0);
		}
		if (wParam == 'p' || wParam == 'P') {
			if (cnt % 2 == 0) {
				k = 0, k1 = 0, k2 = 0, k3 = 0;
				SetTimer(hwnd, 1, 100, NULL);
			}
			if (cnt % 2 == 1) {
				k = 0, k1 = 0, k2 = 0, k3 = 0;
				KillTimer(hwnd, 1);
			}
			cnt++;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_TIMER:
		k += 10;
		k1 += 10;
		k2 += 10;
		k3 += 10;
		if (a == 0) {
			if (k == 300 + x) {
				k = 0;
			}
			if (300 + x + k1 == 800 - (300 + x)) {
				k1 = 0;
			}
			if (k2 == 300 + x) {
				k2 = 0;
			}
			if (300 + x + k3 == 800 - (300 + x)) {
				k3 = 0;
			}
		}
		if (a == 1) {
			if (k == 800 + x) {
				k = 0;
			}
			if (800 + x + k1 == 800 - (800 + x)) {
				k1 = 0;
			}
			if (k2 == 800 + x) {
				k2 = 0;
			}
			if (800 + x + k3 == 800 - (800 + x)) {
				k3 = 0;
			}
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		DeleteObject(hbitmap);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}