#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include "resource2.h"
#define BSIZE 40
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU4);
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 900, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
struct rect {
	int x, y;
	int x1, y1;
	int x2, y2;
	int x3, y3;
};
struct rect re[8];
struct human {
	int x = 0, y = 0;
};
struct human hu[1];
BOOL Circle(int x1, int y1) {
	if (x1 > 710 && x1 < 760 && y1 > 45 && y1 < 95) {
		return 1;
	}
	else if (x1 > 780 && x1 < 830 && y1 > 45 && y1 < 95) {
		return 2;
	}
	else if (x1 > 850 && x1 < 900 && y1 > 45 && y1 < 95) {
		return 3;
	}
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc{};
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static BOOL Selection;
	int mx = 0, my = 0;
	static RECT rectView;
	static int cng = 0;
	static int i = 0;
	static int j = 0;
	static int k = 0;
	static int h = 0, h2 = 0, h3 = 0, h4 = 0;
	static int ran = -1;
	static int cng1 = 0;
	static int tr = 0, tg = 0, tb = 0;
	static int t = 0, a = 0, tur = 0;
	static int start = 0, start1 = 0;
	static int direct = 0;
	static int ra = 0;
	switch (iMsg) {
	case WM_CREATE:
		hu[0].x = 250;
		hu[0].y = 560;

		re[0].x = 0;
		re[0].y = 290;
		re[0].x1 = 150;
		re[0].y1 = 360;
		re[0].x2 = 0;
		re[0].y2 = 290;
		re[0].x3 = 0;
		re[0].y3 = 360;

		re[1].x = 850;
		re[1].y = 440;
		re[1].x1 = 1000;
		re[1].y1 = 510;
		re[1].x2 = 1000;
		re[1].y2 = 440;
		re[1].x3 = 1000;
		re[1].y3 = 510;

		re[2].x = 370;
		re[2].y = 0;
		re[2].x1 = 440;
		re[2].y1 = 150;
		re[2].x2 = 370;
		re[2].y2 = 0;
		re[2].x3 = 440;
		re[2].y3 = 0;

		re[3].x = 520;
		re[3].y = 700;
		re[3].x1 = 590;
		re[3].y1 = 850;
		re[3].x2 = 590;
		re[3].y2 = 850;
		re[3].x3 = 590;
		re[3].y3 = 850;

		GetClientRect(hwnd, &rectView);
		a = 0;
		SetTimer(hwnd, 1, 100, NULL);
		SetTimer(hwnd, 2, 5000 - cng1, NULL);
		SetTimer(hwnd, 3, 1000, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 0, 250, NULL);
		LineTo(hdc, 330, 250);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 330, 250, NULL);
		LineTo(hdc, 630, 250);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 630, 250, NULL);
		LineTo(hdc, 1000, 250);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(155, 155, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 0, 400, NULL);
		LineTo(hdc, 330, 400);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_DOT, 1, RGB(155, 155, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 330, 400, NULL);
		LineTo(hdc, 630, 400);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(155, 155, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 630, 400, NULL);
		LineTo(hdc, 1000, 400);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 0, 550, NULL);
		LineTo(hdc, 330, 550);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 330, 550, NULL);
		LineTo(hdc, 630, 550);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 630, 550, NULL);
		LineTo(hdc, 1000, 550);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 330, 0, NULL);
		LineTo(hdc, 330, 250);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 330, 250, NULL);
		LineTo(hdc, 330, 550);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 630, 0, NULL);
		LineTo(hdc, 630, 250);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 630, 250, NULL);
		LineTo(hdc, 630, 550);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 330, 550, NULL);
		LineTo(hdc, 330, 900);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 630, 550, NULL);
		LineTo(hdc, 630, 900);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(155, 155, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 480, 0, NULL);
		LineTo(hdc, 480, 250);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_DOT, 1, RGB(155, 155, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 480, 250, NULL);
		LineTo(hdc, 480, 550);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(155, 155, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 480, 550, NULL);
		LineTo(hdc, 480, 900);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Rectangle(hdc, 680, 20, 930, 120);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		if (ran == 0) {
			hPen = CreatePen(PS_SOLID, 10, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Ellipse(hdc, 710, 45, 760, 95);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		if (ran == -1) {
			hPen = CreatePen(PS_SOLID, tr, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Ellipse(hdc, 710, 45, 760, 95);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, 710, 45, 760, 95);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		if (ran == -1) {
			hPen = CreatePen(PS_SOLID, tg, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Ellipse(hdc, 780, 45, 830, 95);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		if (ran == 1) {
			hPen = CreatePen(PS_SOLID, 10, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Ellipse(hdc, 780, 45, 830, 95);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		if (ran == -1) {
			hPen = CreatePen(PS_SOLID, tb, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Ellipse(hdc, 850, 45, 900, 95);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, 780, 45, 830, 95);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		if (ran == 2) {
			hPen = CreatePen(PS_SOLID, 10, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Ellipse(hdc, 850, 45, 900, 95);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, 850, 45, 900, 95);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[0].x, re[0].y, re[0].x1, re[0].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		if (h == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[0].x2, re[0].y2, re[0].x3, re[0].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[1].x, re[1].y, re[1].x1, re[1].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		if (h2 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[1].x2, re[1].y2, re[1].x3, re[1].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[2].x, re[2].y, re[2].x1, re[2].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		if (h3 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[2].x2, re[2].y2, re[2].x3, re[2].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[3].x, re[3].y, re[3].x1, re[3].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		if (h4 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[3].x2, re[3].y2, re[3].x3, re[3].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, hu[0].x, hu[0].y, hu[0].x+70, hu[0].y+70);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_GAME_START40046:
			Selection = 1;
			tur = Selection;
			start = 0;
			start1 = 0;
			break;
		case ID_GAME_END40047:
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 4);
			KillTimer(hwnd, 5);
			PostQuitMessage(0);
			break;
		case ID_SPEED_PLUS:
			i = -50;
			if (start == 0 && start1 == 0) {
				SetTimer(hwnd, 1, 100 + i, NULL);
				break;
			}
			if (start == 1 && start1 == 1) {
				SetTimer(hwnd, 4, 100 + i, NULL);
				SetTimer(hwnd, 5, 100 + i, NULL);
				break;
			}
			if (start == 1) {
				SetTimer(hwnd, 5, 100 + i, NULL);
				break;
			}
			if (start1 == 1) {
				SetTimer(hwnd, 4, 100 + i, NULL);
				break;
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case ID_SPEED_MINUS:
			i = 50;
			if (start == 0 && start1 == 0) {
				SetTimer(hwnd, 1, 100 + i, NULL);
				break;
			}
			if (start == 1 && start1 == 1) {
				SetTimer(hwnd, 4, 100 + i, NULL);
				SetTimer(hwnd, 5, 100 + i, NULL);
				break;
			}
			if (start == 1) {
				SetTimer(hwnd, 5, 100 + i, NULL);
				break;
			}
			if (start1 == 1) {
				SetTimer(hwnd, 4, 100 + i, NULL);
				break;
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case ID_DIRECTION_UPDOWN:
			start = 1;
			start1 = 0;
			SetTimer(hwnd, 5, 100, NULL);
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 4);
			break;
		case ID_DIRECTION_LR:
			start1 = 1;
			start = 0;
			SetTimer(hwnd, 4, 100, NULL);
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 5);
			break;
		case ID_DIRECTION_EVERYONE:
			start = 1;
			start1 = 1;
			SetTimer(hwnd, 4, 100, NULL);
			SetTimer(hwnd, 5, 100, NULL);
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			break;
		case ID_TRAFFIC_RED:
			KillTimer(hwnd, 4);
			KillTimer(hwnd, 5);
			start = 0;
			start1 = 0;
			tur = Selection;
			Selection = 1;
			tr = 10;
			tg = 1;
			tb = 1;
			SetTimer(hwnd, 1, 100 + i, NULL);
			break;
		case ID_TRAFFIC_BLUE:
			KillTimer(hwnd, 4);
			KillTimer(hwnd, 5);
			start = 0;
			start1 = 0;
			tur = Selection;
			Selection = 3;
			tr = 1;
			tg = 1;
			tb = 10;
			SetTimer(hwnd, 1, 100 + i, NULL);
			break;
		case ID_TRAFFIC_YELLOW:
			KillTimer(hwnd, 4);
			KillTimer(hwnd, 5);
			start = 0;
			start1 = 0;
			tur = Selection;
			Selection = 2;
			tr = 1;
			tg = 10;
			tb = 1;
			SetTimer(hwnd, 1, 100 + i, NULL);
			break;
		case ID_TRAFFIC_AUTO:
			KillTimer(hwnd, 4);
			KillTimer(hwnd, 5);
			start = 0;
			start1 = 0;
			a++;
			Selection = 0;
			tr = 1;
			tg = 1;
			tb = 1;
			ran = 0;
			if (a > 1) {
				a = 0;
				Selection = 0;
			}
			SetTimer(hwnd, 1, 100 + i, NULL);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case ID_CROSS_CROSS:
			ra = rand()%3;
			switch (ra) {
			case 0:
				if (hu[0].x == 250&&hu[0].y==560) {
					direct = 0;
				}
				if (hu[0].x == 650 && hu[0].y == 560) {
					direct = 3;
				}
				if (hu[0].x == 250 && hu[0].y == 160) {
					direct = 6;
				}
				if (hu[0].x == 650 && hu[0].y == 160) {
					direct = 9;
				}
				break;
			case 1:
				if (hu[0].x == 250 && hu[0].y == 560) {
					direct = 1;
				}
				if (hu[0].x == 650 && hu[0].y == 560) {
					direct = 4;
				}
				if (hu[0].x == 250 && hu[0].y == 160) {
					direct = 7;
				}
				if (hu[0].x == 650 && hu[0].y == 160) {
					direct = 10;
				}
				break;
			case 2:
				if (hu[0].x == 250 && hu[0].y == 560) {
					direct = 2;
				}
				if (hu[0].x == 650 && hu[0].y == 560) {
					direct = 5;
				}
				if (hu[0].x == 250 && hu[0].y == 160) {
					direct = 8;
				}
				if (hu[0].x == 650 && hu[0].y == 160) {
					direct = 11;
				}
				break;
			}
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 4);
			KillTimer(hwnd, 5);
			SetTimer(hwnd, 6, 50, NULL);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			if (a == 1 && Selection == 0) {
				if (ran == 0) {
					if (re[0].x1 < 1000) {
						re[0].x += 20;
						re[0].x1 += 20;
						h = 0;
					}
					if (re[0].x1 >= 1000) {
						h = 1;
						re[0].x1 += 20;
						re[0].x += 20;
						re[0].x3 += 20;
						if (re[0].x >= 1000) {
							re[0].x1 = re[0].x3;
							re[0].x = re[0].x2;
							re[0].x3 = 0;
							re[0].x2 = 0;
							h = 0;
						}
					}
					if (re[1].x > 0) {
						re[1].x -= 20;
						re[1].x1 -= 20;
						h2 = 0;
					}
					if (re[1].x <= 0) {
						h2 = 1;
						re[1].x -= 20;
						re[1].x1 -= 20;
						re[1].x2 -= 20;
						if (re[1].x1 <= 0) {
							re[1].x1 = re[1].x3;
							re[1].x = re[1].x2;
							re[1].x3 = 1000;
							re[1].x2 = 1000;
							h2 = 0;
						}
					}
					if (re[2].y1 >= 300) {
						re[2].y1 += 20;
						re[2].y += 20;
						if (re[2].y1 >= 850) {
							h3 = 1;
							re[2].y1 += 20;
							re[2].y3 += 20;
							if (re[2].y >= 850) {
								re[2].y1 = re[2].y3;
								re[2].y = re[2].y2;
								re[2].y3 = 0;
								re[2].y2 = 0;
								h3 = 0;
							}
						}
					}
					if (300 > re[2].y1 && re[2].y1 > 250) {
						re[2].y1 -= 20;
						re[2].y -= 20;
					}
					if (re[2].y < 80) {
						re[2].y1 += 20;
						re[2].y += 20;
					}
					if (re[3].y < 530) {
						re[3].y1 -= 20;
						re[3].y -= 20;
						if (re[3].y <= 0) {
							h4 = 1;
							re[3].y -= 20;
							re[3].y2 -= 20;
							if (re[3].y1 <= 0) {
								re[3].y1 = re[3].y3;
								re[3].y = re[3].y2;
								re[3].y3 = 850;
								re[3].y2 = 850;
								h4 = 0;
							}
						}
					}
					if (re[3].y1 > 600) {
						re[3].y1 -= 20;
						re[3].y -= 20;
					}
					if (530 < re[3].y && re[3].y < 570) {
						re[3].y1 += 20;
						re[3].y += 20;
					}
				}
				if (ran == 1) {
					if (t == 0) {
						if (re[0].x1 < 1000) {
							re[0].x += 20;
							re[0].x1 += 20;
							h = 0;
						}
						if (re[0].x1 >= 1000) {
							h = 1;
							re[0].x1 += 20;
							re[0].x += 20;
							re[0].x3 += 20;
							if (re[0].x >= 1000) {
								re[0].x1 = re[0].x3;
								re[0].x = re[0].x2;
								re[0].x3 = 0;
								re[0].x2 = 0;
								h = 0;
							}
						}
						if (re[1].x > 0) {
							re[1].x -= 20;
							re[1].x1 -= 20;
							h2 = 0;
						}
						if (re[1].x <= 0) {
							h2 = 1;
							re[1].x -= 20;
							re[1].x1 -= 20;
							re[1].x2 -= 20;
							if (re[1].x1 <= 0) {
								re[1].x1 = re[1].x3;
								re[1].x = re[1].x2;
								re[1].x3 = 1000;
								re[1].x2 = 1000;
								h2 = 0;
							}
						}
					}
					if (t == 1) {
						if (re[2].y1 < 850) {
							re[2].y += 20;
							re[2].y1 += 20;
							h3 = 0;
						}
						if (re[2].y1 >= 850) {
							h3 = 1;
							re[2].y1 += 20;
							re[2].y += 20;
							re[2].y3 += 20;
							if (re[2].y >= 850) {
								re[2].y1 = re[2].y3;
								re[2].y = re[2].y2;
								re[2].y3 = 0;
								re[2].y2 = 0;
								h3 = 0;
							}
						}
						if (re[3].y > 0) {
							re[3].y -= 20;
							re[3].y1 -= 20;
							h4 = 0;
						}
						if (re[3].y <= 0) {
							h4 = 1;
							re[3].y -= 20;
							re[3].y1 -= 20;
							re[3].y2 -= 20;
							if (re[3].y1 <= 0) {
								re[3].y1 = re[3].y3;
								re[3].y = re[3].y2;
								re[3].y3 = 850;
								re[3].y2 = 850;
								h4 = 0;
							}
						}
					}
				}
				if (ran == 2) {
					if (re[2].y1 < 850) {
						re[2].y += 20;
						re[2].y1 += 20;
						h3 = 0;
					}
					if (re[2].y1 >= 850) {
						h3 = 1;
						re[2].y1 += 20;
						re[2].y += 20;
						re[2].y3 += 20;
						if (re[2].y >= 850) {
							re[2].y1 = re[2].y3;
							re[2].y = re[2].y2;
							re[2].y3 = 0;
							re[2].y2 = 0;
							h3 = 0;
						}
					}
					if (re[3].y > 0) {
						re[3].y -= 20;
						re[3].y1 -= 20;
						h4 = 0;
					}
					if (re[3].y <= 0) {
						h4 = 1;
						re[3].y -= 20;
						re[3].y1 -= 20;
						re[3].y2 -= 20;
						if (re[3].y1 <= 0) {
							re[3].y1 = re[3].y3;
							re[3].y = re[3].y2;
							re[3].y3 = 850;
							re[3].y2 = 850;
							h4 = 0;
						}
					}
					if (re[0].x1 > 370) {
						re[0].x1 += 20;
						re[0].x += 20;
						if (re[0].x1 >= 1000) {
							h = 1;
							re[0].x1 += 20;
							re[0].x3 += 20;
							if (re[0].x >= 1000) {
								re[0].x1 = re[0].x3;
								re[0].x = re[0].x2;
								re[0].x3 = 0;
								re[0].x2 = 0;
								h = 0;
							}
						}
					}
					if (360 > re[0].x1 && re[0].x1 > 310) {
						re[0].x1 -= 20;
						re[0].x -= 20;
					}
					if (re[0].x < 150) {
						re[0].x1 += 20;
						re[0].x += 20;
					}
					if (re[1].x < 630) {
						re[1].x1 -= 20;
						re[1].x -= 20;
						if (re[1].x <= 0) {
							h2 = 1;
							re[1].x -= 20;
							re[1].x2 -= 20;
							if (re[1].x1 <= 0) {
								re[1].x1 = re[1].x3;
								re[1].x = re[1].x2;
								re[1].x3 = 1000;
								re[1].x2 = 1000;
								h2 = 0;
							}
						}
					}
					if (680 > re[1].x && re[1].x > 630) {
						re[1].x1 += 20;
						re[1].x += 20;
					}
					if (re[1].x1 > 800) {
						re[1].x1 -= 20;
						re[1].x -= 20;
					}
				}
			}
			else {
				if (Selection == 1) {
					if (re[0].x1 < 1000) {
						re[0].x += 20;
						re[0].x1 += 20;
						h = 0;
					}
					if (re[0].x1 >= 1000) {
						h = 1;
						re[0].x1 += 20;
						re[0].x += 20;
						re[0].x3 += 20;
						if (re[0].x >= 1000) {
							re[0].x1 = re[0].x3;
							re[0].x = re[0].x2;
							re[0].x3 = 0;
							re[0].x2 = 0;
							h = 0;
						}
					}
					if (re[1].x > 0) {
						re[1].x -= 20;
						re[1].x1 -= 20;
						h2 = 0;
					}
					if (re[1].x <= 0) {
						h2 = 1;
						re[1].x -= 20;
						re[1].x1 -= 20;
						re[1].x2 -= 20;
						if (re[1].x1 <= 0) {
							re[1].x1 = re[1].x3;
							re[1].x = re[1].x2;
							re[1].x3 = 1000;
							re[1].x2 = 1000;
							h2 = 0;
						}
					}
					if (re[2].y1 >= 300) {
						re[2].y1 += 20;
						re[2].y += 20;
						if (re[2].y1 >= 850) {
							h3 = 1;
							re[2].y1 += 20;
							re[2].y3 += 20;
							if (re[2].y >= 850) {
								re[2].y1 = re[2].y3;
								re[2].y = re[2].y2;
								re[2].y3 = 0;
								re[2].y2 = 0;
								h3 = 0;
							}
						}
					}
					if (300 > re[2].y1 && re[2].y1 > 250) {
						re[2].y1 -= 20;
						re[2].y -= 20;
					}
					if (re[2].y < 80) {
						re[2].y1 += 20;
						re[2].y += 20;
					}
					if (re[3].y < 530) {
						re[3].y1 -= 20;
						re[3].y -= 20;
						if (re[3].y <= 0) {
							h4 = 1;
							re[3].y -= 20;
							re[3].y2 -= 20;
							if (re[3].y1 <= 0) {
								re[3].y1 = re[3].y3;
								re[3].y = re[3].y2;
								re[3].y3 = 850;
								re[3].y2 = 850;
								h4 = 0;
							}
						}
					}
					if (re[3].y1 > 600) {
						re[3].y1 -= 20;
						re[3].y -= 20;
					}
					if (530 < re[3].y && re[3].y < 570) {
						re[3].y1 += 20;
						re[3].y += 20;
					}
				}
				if (Selection == 2) {
					if (tur == 1) {
						if (re[0].x1 < 1000) {
							re[0].x += 20;
							re[0].x1 += 20;
							h = 0;
						}
						if (re[0].x1 >= 1000) {
							h = 1;
							re[0].x1 += 20;
							re[0].x += 20;
							re[0].x3 += 20;
							if (re[0].x >= 1000) {
								re[0].x1 = re[0].x3;
								re[0].x = re[0].x2;
								re[0].x3 = 0;
								re[0].x2 = 0;
								h = 0;
							}
						}
						if (re[1].x > 0) {
							re[1].x -= 20;
							re[1].x1 -= 20;
							h2 = 0;
						}
						if (re[1].x <= 0) {
							h2 = 1;
							re[1].x -= 20;
							re[1].x1 -= 20;
							re[1].x2 -= 20;
							if (re[1].x1 <= 0) {
								re[1].x1 = re[1].x3;
								re[1].x = re[1].x2;
								re[1].x3 = 1000;
								re[1].x2 = 1000;
								h2 = 0;
							}
						}
						if (re[2].y1 >= 300) {
							re[2].y1 += 20;
							re[2].y += 20;
							if (re[2].y1 >= 850) {
								h3 = 1;
								re[2].y1 += 20;
								re[2].y3 += 20;
								if (re[2].y >= 850) {
									re[2].y1 = re[2].y3;
									re[2].y = re[2].y2;
									re[2].y3 = 0;
									re[2].y2 = 0;
									h3 = 0;
								}
							}
						}
						if (300 > re[2].y1 && re[2].y1 > 250) {
							re[2].y1 -= 20;
							re[2].y -= 20;
						}
						if (re[2].y < 80) {
							re[2].y1 += 20;
							re[2].y += 20;
						}
						if (re[3].y < 530) {
							re[3].y1 -= 20;
							re[3].y -= 20;
							if (re[3].y <= 0) {
								h4 = 1;
								re[3].y -= 20;
								re[3].y2 -= 20;
								if (re[3].y1 <= 0) {
									re[3].y1 = re[3].y3;
									re[3].y = re[3].y2;
									re[3].y3 = 850;
									re[3].y2 = 850;
									h4 = 0;
								}
							}
						}
						if (re[3].y1 > 600) {
							re[3].y1 -= 20;
							re[3].y -= 20;
						}
						if (530 < re[3].y && re[3].y < 570) {
							re[3].y1 += 20;
							re[3].y += 20;
						}
					}
					if (tur == 3) {
						if (re[2].y1 < 850) {
							re[2].y += 20;
							re[2].y1 += 20;
							h3 = 0;
						}
						if (re[2].y1 >= 850) {
							h3 = 1;
							re[2].y1 += 20;
							re[2].y += 20;
							re[2].y3 += 20;
							if (re[2].y >= 850) {
								re[2].y1 = re[2].y3;
								re[2].y = re[2].y2;
								re[2].y3 = 0;
								re[2].y2 = 0;
								h3 = 0;
							}
						}
						if (re[3].y > 0) {
							re[3].y -= 20;
							re[3].y1 -= 20;
							h4 = 0;
						}
						if (re[3].y <= 0) {
							h4 = 1;
							re[3].y = -20;
							re[3].y1 -= 20;
							re[3].y2 -= 20;
							if (re[3].y1 <= 0) {
								re[3].y1 = re[3].y3;
								re[3].y = re[3].y2;
								re[3].y3 = 850;
								re[3].y2 = 850;
								h4 = 0;
							}
						}
						if (re[0].x1 > 370) {
							re[0].x1 += 20;
							re[0].x += 20;
							if (re[0].x1 >= 1000) {
								h = 1;
								re[0].x1 += 20;
								re[0].x3 += 20;
								if (re[0].x >= 1000) {
									re[0].x1 = re[0].x3;
									re[0].x = re[0].x2;
									re[0].x3 = 0;
									re[0].x2 = 0;
									h = 0;
								}
							}
						}
						if (360 > re[0].x1 && re[0].x1 > 310) {
							re[0].x1 -= 20;
							re[0].x -= 20;
						}
						if (re[0].x < 150) {
							re[0].x1 += 20;
							re[0].x += 20;
						}
						if (re[1].x < 630) {
							re[1].x1 -= 20;
							re[1].x -= 20;
							if (re[1].x <= 0) {
								h2 = 1;
								re[1].x -= 20;
								re[1].x2 -= 20;
								if (re[1].x1 <= 0) {
									re[1].x1 = re[1].x3;
									re[1].x = re[1].x2;
									re[1].x3 = 1000;
									re[1].x2 = 1000;
									h2 = 0;
								}
							}
						}
						if (680 > re[1].x && re[1].x > 630) {
							re[1].x1 += 20;
							re[1].x += 20;
						}
						if (re[1].x1 > 800) {
							re[1].x1 -= 20;
							re[1].x -= 20;
						}
					}
				}
				if (Selection == 3) {
					if (re[2].y1 < 850) {
						re[2].y += 20;
						re[2].y1 += 20;
						h3 = 0;
					}
					if (re[2].y1 >= 850) {
						h3 = 1;
						re[2].y1 += 20;
						re[2].y += 20;
						re[2].y3 += 20;
						if (re[2].y >= 850) {
							re[2].y1 = re[2].y3;
							re[2].y = re[2].y2;
							re[2].y3 = 0;
							re[2].y2 = 0;
							h3 = 0;
						}
					}
					if (re[3].y > 0) {
						re[3].y -= 20;
						re[3].y1 -= 20;
						h4 = 0;
					}
					if (re[3].y <= 0) {
						h4 = 1;
						re[3].y = -20;
						re[3].y1 -= 20;
						re[3].y2 -= 20;
						if (re[3].y1 <= 0) {
							re[3].y1 = re[3].y3;
							re[3].y = re[3].y2;
							re[3].y3 = 850;
							re[3].y2 = 850;
							h4 = 0;
						}
					}
					if (re[0].x1 > 370) {
						re[0].x1 += 20;
						re[0].x += 20;
						if (re[0].x1 >= 1000) {
							h = 1;
							re[0].x1 += 20;
							re[0].x3 += 20;
							if (re[0].x >= 1000) {
								re[0].x1 = re[0].x3;
								re[0].x = re[0].x2;
								re[0].x3 = 0;
								re[0].x2 = 0;
								h = 0;
							}
						}
					}
					if (360 > re[0].x1 && re[0].x1 > 310) {
						re[0].x1 -= 20;
						re[0].x -= 20;
					}
					if (re[0].x < 150) {
						re[0].x1 += 20;
						re[0].x += 20;
					}
					if (re[1].x < 630) {
						re[1].x1 -= 20;
						re[1].x -= 20;
						if (re[1].x <= 0) {
							h2 = 1;
							re[1].x -= 20;
							re[1].x2 -= 20;
							if (re[1].x1 <= 0) {
								re[1].x1 = re[1].x3;
								re[1].x = re[1].x2;
								re[1].x3 = 1000;
								re[1].x2 = 1000;
								h2 = 0;
							}
						}
					}
					if (680 > re[1].x && re[1].x > 630) {
						re[1].x1 += 20;
						re[1].x += 20;
					}
					if (re[1].x1 > 800) {
						re[1].x1 -= 20;
						re[1].x -= 20;
					}
				}
			}
			break;
		case 2:
			if (a == 1) {
				if (t == 0) {
					ran++;
					if (ran == 1) {
						cng1 = 4000;
						i = -70;
						SetTimer(hwnd, 1, 100 + i, NULL);
						SetTimer(hwnd, 2, 5000 - cng1, NULL);
						SetTimer(hwnd, 4, 150 + i, NULL);
					}
					else {
						i = 0;
						cng1 = 0;
						SetTimer(hwnd, 1, 100 + i, NULL);
						SetTimer(hwnd, 2, 5000 - cng1, NULL);
						SetTimer(hwnd, 4, 150 + i, NULL);
					}
					if (ran > 2) {
						ran--;
						t = 1;
					}
				}
				if (t == 1) {
					ran--;
					if (ran == 1) {
						cng1 = 4000;
						i = -70;
						SetTimer(hwnd, 1, 100 + i, NULL);
						SetTimer(hwnd, 2, 5000 - cng1, NULL);
						SetTimer(hwnd, 4, 150 + i, NULL);
					}
					else {
						cng1 = 0;
						i = 0;
						SetTimer(hwnd, 1, 100 + i, NULL);
						SetTimer(hwnd, 2, 5000 - cng1, NULL);
						SetTimer(hwnd, 4, 150 + i, NULL);
					}
					if (ran < 0) {
						ran = 1;
						cng1 = 4000;
						i = -70;
						SetTimer(hwnd, 1, 100 + i, NULL);
						SetTimer(hwnd, 2, 5000 - cng1, NULL);
						SetTimer(hwnd, 4, 150 + i, NULL);
						cng = 0;
						t = 0;
					}
				}
			}
			break;
		case 3:
			if (Selection == 2) {
				if (tur == 1) {
					tr = 1;
					tg = 1;
					tb = 10;
					Selection = 3;
				}
				else if (tur == 3) {
					tr = 10;
					tg = 1;
					tb = 1;
					Selection = 1;
				}
			}
			break;
		case 4:
			if (re[0].x1 < 1000) {
				re[0].x += 20;
				re[0].x1 += 20;
				h = 0;
			}
			if (re[0].x1 >= 1000) {
				h = 1;
				re[0].x1 += 20;
				re[0].x += 20;
				re[0].x3 += 20;
				if (re[0].x >= 1000) {
					re[0].x1 = re[0].x3;
					re[0].x = re[0].x2;
					re[0].x3 = 0;
					re[0].x2 = 0;
					h = 0;
				}
			}
			if (re[1].x > 0) {
				re[1].x -= 20;
				re[1].x1 -= 20;
				h2 = 0;
			}
			if (re[1].x <= 0) {
				h2 = 1;
				re[1].x -= 20;
				re[1].x1 -= 20;
				re[1].x2 -= 20;
				if (re[1].x1 <= 0) {
					re[1].x1 = re[1].x3;
					re[1].x = re[1].x2;
					re[1].x3 = 1000;
					re[1].x2 = 1000;
					h2 = 0;
				}
			}
			break;
		case 5:
			if (re[2].y1 < 850) {
				re[2].y += 20;
				re[2].y1 += 20;
				h3 = 0;
			}
			if (re[2].y1 >= 850) {
				h3 = 1;
				re[2].y1 += 20;
				re[2].y += 20;
				re[2].y3 += 20;
				if (re[2].y >= 850) {
					re[2].y1 = re[2].y3;
					re[2].y = re[2].y2;
					re[2].y3 = 0;
					re[2].y2 = 0;
					h3 = 0;
				}
			}
			if (re[3].y > 0) {
				re[3].y -= 20;
				re[3].y1 -= 20;
				h4 = 0;
			}
			if (re[3].y <= 0) {
				h4 = 1;
				re[3].y -= 20;
				re[3].y1 -= 20;
				re[3].y2 -= 20;
				if (re[3].y1 <= 0) {
					re[3].y1 = re[3].y3;
					re[3].y = re[3].y2;
					re[3].y3 = 850;
					re[3].y2 = 850;
					h4 = 0;
				}
			}
			break;
		case 6:
			if (direct == 0) {
				hu[0].x += 10;
				if (hu[0].x == 650) {
					direct = -1;
				}
			}
			if (direct == 1) {
				hu[0].x += 10;
				hu[0].y -= 10;
				if (hu[0].x == 650) {
					direct = -1;
				}
			}
			if (direct == 2) {
				hu[0].y -= 10;
				if (hu[0].y == 160) {
					direct = -1;
				}
			}
			if (direct == 3) {
				hu[0].x -= 10;
				if (hu[0].x == 250) {
					direct = -1;
				}
			}
			if (direct == 4) {
				hu[0].x -= 10;
				hu[0].y -= 10;
				if (hu[0].x == 250) {
					direct = -1;
				}
			}
			if (direct == 5) {
				hu[0].y -= 10;
				if (hu[0].y == 160) {
					direct = -1;
				}
			}
			if (direct == 6) {
				hu[0].x += 10;
				if (hu[0].x == 650) {
					direct = -1;
				}
			}
			if (direct == 7) {
				hu[0].x += 10;
				hu[0].y += 10;
				if (hu[0].x == 650) {
					direct = -1;
				}
			}
			if (direct == 8) {
				hu[0].y += 10;
				if (hu[0].y == 560) {
					direct = -1;
				}
			}
			if (direct == 9) {
				hu[0].x -= 10;
				if (hu[0].x == 250) {
					direct = -1;
				}
			}
			if (direct == 10) {
				hu[0].x -= 10;
				hu[0].y += 10;
				if (hu[0].x == 250) {
					direct = -1;
				}
			}
			if (direct == 11) {
				hu[0].y += 10;
				if (hu[0].y == 560) {
					direct = -1;
				}
			}
			break;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
