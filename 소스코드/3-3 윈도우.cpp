#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<string.h>
#include<math.h>
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
	WndClass.lpszMenuName = NULL;
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
	static int h = 0, h2 = 0, h3 = 0, h4 = 0, h5 = 0, h6 = 0, h7 = 0, h8 = 0;
	static int ran = -1;
	static int cng1 = 0;
	static int tr = 0, tg = 0, tb = 0;
	static int t = 0, a = 0, tur = 0;
	switch (iMsg) {
	case WM_CREATE:
		re[0].x = 80;
		re[0].y = 290;
		re[0].x1 = 150;
		re[0].y1 = 320;
		re[0].x2 = 0;
		re[0].y2 = 290;
		re[0].x3 = 0;
		re[0].y3 = 320;

		re[4].x = 0;
		re[4].y = 330;
		re[4].x1 = 70;
		re[4].y1 = 360;
		re[4].x2 = 0;
		re[4].y2 = 330;
		re[4].x3 = 0;
		re[4].y3 = 360;

		re[1].x = 850;
		re[1].y = 440;
		re[1].x1 = 920;
		re[1].y1 = 470;
		re[1].x2 = 1000;
		re[1].y2 = 440;
		re[1].x3 = 1000;
		re[1].y3 = 470;

		re[5].x = 930;
		re[5].y = 480;
		re[5].x1 = 1000;
		re[5].y1 = 510;
		re[5].x2 = 1000;
		re[5].y2 = 480;
		re[5].x3 = 1000;
		re[5].y3 = 510;

		re[2].x = 370;
		re[2].y = 0;
		re[2].x1 = 400;
		re[2].y1 = 70;
		re[2].x2 = 370;
		re[2].y2 = 0;
		re[2].x3 = 400;
		re[2].y3 = 0;

		re[6].x = 410;
		re[6].y = 80;
		re[6].x1 = 440;
		re[6].y1 = 150;
		re[6].x2 = 410;
		re[6].y2 = 0;
		re[6].x3 = 440;
		re[6].y3 = 0;

		re[3].x = 520;
		re[3].y = 700;
		re[3].x1 = 550;
		re[3].y1 = 770;
		re[3].x2 = 520;
		re[3].y2 = 850;
		re[3].x3 = 550;
		re[3].y3 = 850;

		re[7].x = 560;
		re[7].y = 780;
		re[7].x1 = 590;
		re[7].y1 = 850;
		re[7].x2 = 560;
		re[7].y2 = 850;
		re[7].x3 = 590;
		re[7].y3 = 850;

		GetClientRect(hwnd, &rectView);
		a = 0;
		SetTimer(hwnd, 1, 100, NULL);
		SetTimer(hwnd, 2, 5000 - cng1, NULL);
		SetTimer(hwnd, 3, 1000, NULL);
		SetTimer(hwnd, 4, 150, NULL);
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
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[4].x, re[4].y, re[4].x1, re[4].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		if (h == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[0].x2, re[0].y2, re[0].x3, re[0].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (h5 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[4].x2, re[4].y2, re[4].x3, re[4].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[1].x, re[1].y, re[1].x1, re[1].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[5].x, re[5].y, re[5].x1, re[5].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		if (h2 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[1].x2, re[1].y2, re[1].x3, re[1].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (h6 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[5].x2, re[5].y2, re[5].x3, re[5].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[2].x, re[2].y, re[2].x1, re[2].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[6].x, re[6].y, re[6].x1, re[6].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		if (h3 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[2].x2, re[2].y2, re[2].x3, re[2].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (h7 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[6].x2, re[6].y2, re[6].x3, re[6].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[3].x, re[3].y, re[3].x1, re[3].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, re[7].x, re[7].y, re[7].x1, re[7].y1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		if (h4 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[3].x2, re[3].y2, re[3].x3, re[3].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (h8 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[7].x2, re[7].y2, re[7].x3, re[7].y3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		tur = Selection;
		if (Circle(mx, my) == 1 && a == 0) {
			Selection = 1;
			tr = 10;
			tg = 1;
			tb = 1;
		}
		else if (Circle(mx, my) == 2 && a == 0) {
			Selection = 2;
			tr = 1;
			tg = 10;
			tb = 1;
		}
		else if (Circle(mx, my) == 3 && a == 0) {
			Selection = 3;
			tr = 1;
			tg = 1;
			tb = 10;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == 'a' || wParam == 'A') {
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
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (wParam == 'q' || wParam == 'Q') {	
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 4);
			PostQuitMessage(0);
		}
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == '+') {
			i -= 10;
			if (i == -90) {
				i += 10;
			}
			SetTimer(hwnd, 1, 100 + i, NULL);
			SetTimer(hwnd, 4, 150 + i, NULL);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (wParam == '-') {
			i += 10;
			if (i == 90) {
				i -= 10;
			}
			SetTimer(hwnd, 1, 100 + i, NULL);
			SetTimer(hwnd, 4, 150 + i, NULL);
			InvalidateRect(hwnd, NULL, TRUE);
		}
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
			if (a == 1 && Selection == 0) {
				if (ran == 0) {
					if (re[4].x1 < 1000) {
						re[4].x += 20;
						re[4].x1 += 20;
						h5 = 0;
					}
					if (re[4].x1 >= 1000) {
						h5 = 1;
						re[4].x1 += 20;
						re[4].x += 20;
						re[4].x3 += 20;
						if (re[4].x >= 1000) {
							re[4].x1 = re[4].x3;
							re[4].x = re[4].x2;
							re[4].x3 = 0;
							re[4].x2 = 0;
							h5 = 0;
						}
					}
					if (re[5].x > 0) {
						re[5].x -= 20;
						re[5].x1 -= 20;
						h6 = 0;
					}
					if (re[5].x <= 0) {
						h6 = 1;
						re[5].x -= 20;
						re[5].x1 -= 20;
						re[5].x2 -= 20;
						if (re[5].x1 <= 0) {
							re[5].x1 = re[5].x3;
							re[5].x = re[5].x2;
							re[5].x3 = 1000;
							re[5].x2 = 1000;
							h6 = 0;
						}
					}
					if (re[6].y1 >= 300) {
						re[6].y1 += 20;
						re[6].y += 20;
						if (re[6].y1 >= 850) {
							h7 = 1;
							re[6].y1 += 20;
							re[6].y3 += 20;
							if (re[6].y >= 850) {
								re[6].y1 = re[6].y3;
								re[6].y = re[6].y2;
								re[6].y3 = 0;
								re[6].y2 = 0;
								h7 = 0;
							}
						}
					}
					if (300 > re[6].y1 && re[6].y1 > 250) {
						re[6].y1 -= 20;
						re[6].y -= 20;
					}
					if (re[6].y < 80) {
						re[6].y1 += 20;
						re[6].y += 20;
					}
					if (re[7].y < 530) {
						re[7].y1 -= 20;
						re[7].y -= 20;
						if (re[7].y <= 0) {
							h8 = 1;
							re[7].y -= 20;
							re[7].y2 -= 20;
							if (re[7].y1 <= 0) {
								re[7].y1 = re[7].y3;
								re[7].y = re[7].y2;
								re[7].y3 = 850;
								re[7].y2 = 850;
								h8 = 0;
							}
						}
					}
					if (re[7].y1 > 600) {
						re[7].y1 -= 20;
						re[7].y -= 20;
					}
					if (530 < re[7].y && re[7].y < 570) {
						re[7].y1 += 20;
						re[7].y += 20;
					}
				}
				if (ran == 1) {
					if (t == 0) {
						if (re[4].x1 < 1000) {
							re[4].x += 20;
							re[4].x1 += 20;
							h5 = 0;
						}
						if (re[4].x1 >= 1000) {
							h5 = 1;
							re[4].x1 += 20;
							re[4].x += 20;
							re[4].x3 += 20;
							if (re[4].x >= 1000) {
								re[4].x1 = re[4].x3;
								re[4].x = re[4].x2;
								re[4].x3 = 0;
								re[4].x2 = 0;
								h5 = 0;
							}
						}
						if (re[5].x > 0) {
							re[5].x -= 20;
							re[5].x1 -= 20;
							h6 = 0;
						}
						if (re[4].x <= 0) {
							h6 = 1;
							re[5].x -= 20;
							re[5].x1 -= 20;
							re[5].x2 -= 20;
							if (re[5].x1 <= 0) {
								re[5].x1 = re[5].x3;
								re[5].x = re[5].x2;
								re[5].x3 = 1000;
								re[5].x2 = 1000;
								h6 = 0;
							}
						}
					}
					if (t == 1) {
						if (re[6].y1 < 850) {
							re[6].y += 20;
							re[6].y1 += 20;
							h7 = 0;
						}
						if (re[6].y1 >= 850) {
							h7 = 1;
							re[6].y1 += 20;
							re[6].y += 20;
							re[6].y3 += 20;
							if (re[6].y >= 850) {
								re[6].y1 = re[6].y3;
								re[6].y = re[6].y2;
								re[6].y3 = 0;
								re[6].y2 = 0;
								h7 = 0;
							}
						}
						if (re[7].y > 0) {
							re[7].y -= 20;
							re[7].y1 -= 20;
							h8 = 0;
						}
						if (re[7].y <= 0) {
							h8 = 1;
							re[7].y -= 20;
							re[7].y1 -= 20;
							re[7].y2 -= 20;
							if (re[7].y1 <= 0) {
								re[7].y1 = re[7].y3;
								re[7].y = re[7].y2;
								re[7].y3 = 850;
								re[7].y2 = 850;
								h8 = 0;
							}
						}
					}
				}
				if (ran == 2) {
					if (re[6].y1 < 850) {
						re[6].y += 20;
						re[6].y1 += 20;
						h7 = 0;
					}
					if (re[6].y1 >= 850) {
						h7 = 1;
						re[6].y1 += 20;
						re[6].y += 20;
						re[6].y3 += 20;
						if (re[6].y >= 850) {
							re[6].y1 = re[6].y3;
							re[6].y = re[6].y2;
							re[6].y3 = 0;
							re[6].y2 = 0;
							h7 = 0;
						}
					}
					if (re[7].y > 0) {
						re[7].y -= 20;
						re[7].y1 -= 20;
						h8 = 0;
					}
					if (re[7].y <= 0) {
						h8 = 1;
						re[7].y -= 20;
						re[7].y1 -= 20;
						re[7].y2 -= 20;
						if (re[7].y1 <= 0) {
							re[7].y1 = re[7].y3;
							re[7].y = re[7].y2;
							re[7].y3 = 850;
							re[7].y2 = 850;
							h8 = 0;
						}
					}
					if (re[4].x1 > 370) {
						re[4].x1 += 20;
						re[4].x += 20;
						if (re[4].x1 >= 1000) {
							h5 = 1;
							re[4].x1 += 20;
							re[4].x3 += 20;
							if (re[4].x >= 1000) {
								re[4].x1 = re[4].x3;
								re[4].x = re[4].x2;
								re[4].x3 = 0;
								re[4].x2 = 0;
								h5 = 0;
							}
						}
					}
					if (360 > re[4].x1 && re[4].x1 > 310) {
						re[4].x1 -= 20;
						re[4].x -= 20;
					}
					if (re[4].x < 150) {
						re[4].x1 += 20;
						re[4].x += 20;
					}
					if (re[5].x < 630) {
						re[5].x1 -= 20;
						re[5].x -= 20;
						if (re[5].x <= 0) {
							h6 = 1;
							re[5].x -= 20;
							re[5].x2 -= 20;
							if (re[5].x1 <= 0) {
								re[5].x1 = re[5].x3;
								re[5].x = re[5].x2;
								re[5].x3 = 1000;
								re[5].x2 = 1000;
								h6 = 0;
							}
						}
					}
					if (680 > re[5].x && re[5].x > 630) {
						re[5].x1 += 20;
						re[5].x += 20;
					}
					if (re[5].x1 > 800) {
						re[5].x1 -= 20;
						re[5].x -= 20;
					}
				}
			}
			else {
				if (Selection == 1) {
					if (re[4].x1 < 1000) {
						re[4].x += 20;
						re[4].x1 += 20;
						h5 = 0;
					}
					if (re[4].x1 >= 1000) {
						h5 = 1;
						re[4].x1 += 20;
						re[4].x += 20;
						re[4].x3 += 20;
						if (re[4].x >= 1000) {
							re[4].x1 = re[4].x3;
							re[4].x = re[4].x2;
							re[4].x3 = 0;
							re[4].x2 = 0;
							h5 = 0;
						}
					}
					if (re[5].x > 0) {
						re[5].x -= 20;
						re[5].x1 -= 20;
						h6 = 0;
					}
					if (re[5].x <= 0) {
						h6 = 1;
						re[5].x -= 20;
						re[5].x1 -= 20;
						re[5].x2 -= 20;
						if (re[5].x1 <= 0) {
							re[5].x1 = re[5].x3;
							re[5].x = re[5].x2;
							re[5].x3 = 1000;
							re[5].x2 = 1000;
							h6 = 0;
						}
					}
					if (re[6].y1 >= 300) {
						re[6].y1 += 20;
						re[6].y += 20;
						if (re[6].y1 >= 850) {
							h7 = 1;
							re[6].y1 += 20;
							re[6].y3 += 20;
							if (re[6].y >= 850) {
								re[6].y1 = re[6].y3;
								re[6].y = re[6].y2;
								re[6].y3 = 0;
								re[6].y2 = 0;
								h7 = 0;
							}
						}
					}
					if (300 > re[6].y1 && re[6].y1 > 250) {
						re[6].y1 -= 20;
						re[6].y -= 20;
					}
					if (re[6].y < 80) {
						re[6].y1 += 20;
						re[6].y += 20;
					}
					if (re[7].y < 530) {
						re[7].y1 -= 20;
						re[7].y -= 20;
						if (re[7].y <= 0) {
							h8 = 1;
							re[7].y -= 20;
							re[7].y2 -= 20;
							if (re[7].y1 <= 0) {
								re[7].y1 = re[7].y3;
								re[7].y = re[7].y2;
								re[7].y3 = 850;
								re[7].y2 = 850;
								h8 = 0;
							}
						}
					}
					if (re[7].y1 > 600) {
						re[7].y1 -= 20;
						re[7].y -= 20;
					}
					if (530 < re[7].y && re[7].y < 570) {
						re[7].y1 += 20;
						re[7].y += 20;
					}
				}
				if (Selection == 2) {
					if (tur == 1) {
						if (re[4].x1 < 1000) {
							re[4].x += 20;
							re[4].x1 += 20;
							h5 = 0;
						}
						if (re[4].x1 >= 1000) {
							h5 = 1;
							re[4].x1 += 20;
							re[4].x += 20;
							re[4].x3 += 20;
							if (re[4].x >= 1000) {
								re[4].x1 = re[4].x3;
								re[4].x = re[4].x2;
								re[4].x3 = 0;
								re[4].x2 = 0;
								h5 = 0;
							}
						}
						if (re[5].x > 0) {
							re[5].x -= 20;
							re[5].x1 -= 20;
							h6 = 0;
						}
						if (re[5].x <= 0) {
							h6 = 1;
							re[5].x -= 20;
							re[5].x1 -= 20;
							re[5].x2 -= 20;
							if (re[5].x1 <= 0) {
								re[5].x1 = re[5].x3;
								re[5].x = re[5].x2;
								re[5].x3 = 1000;
								re[5].x2 = 1000;
								h6 = 0;
							}
						}
						if (re[6].y1 >= 300) {
							re[6].y1 += 20;
							re[6].y += 20;
							if (re[6].y1 >= 850) {
								h7 = 1;
								re[6].y1 += 20;
								re[6].y3 += 20;
								if (re[6].y >= 850) {
									re[6].y1 = re[6].y3;
									re[6].y = re[6].y2;
									re[6].y3 = 0;
									re[6].y2 = 0;
									h7 = 0;
								}
							}
						}
						if (300 > re[6].y1 && re[6].y1 > 250) {
							re[6].y1 -= 20;
							re[6].y -= 20;
						}
						if (re[6].y < 80) {
							re[6].y1 += 20;
							re[6].y += 20;
						}
						if (re[7].y < 530) {
							re[7].y1 -= 20;
							re[7].y -= 20;
							if (re[7].y <= 0) {
								h8 = 1;
								re[7].y -= 20;
								re[7].y2 -= 20;
								if (re[7].y1 <= 0) {
									re[7].y1 = re[7].y3;
									re[7].y = re[7].y2;
									re[7].y3 = 850;
									re[7].y2 = 850;
									h8 = 0;
								}
							}
						}
						if (re[7].y1 > 600) {
							re[7].y1 -= 20;
							re[7].y -= 20;
						}
						if (530 < re[7].y && re[7].y < 570) {
							re[7].y1 += 20;
							re[7].y += 20;
						}
					}
					if (tur == 3) {
						if (re[6].y1 < 850) {
							re[6].y += 20;
							re[6].y1 += 20;
							h7 = 0;
						}
						if (re[6].y1 >= 850) {
							h7 = 1;
							re[6].y1 += 20;
							re[6].y += 20;
							re[6].y3 += 20;
							if (re[6].y >= 850) {
								re[6].y1 = re[6].y3;
								re[6].y = re[6].y2;
								re[6].y3 = 0;
								re[6].y2 = 0;
								h7 = 0;
							}
						}
						if (re[7].y > 0) {
							re[7].y -= 20;
							re[7].y1 -= 20;
							h8 = 0;
						}
						if (re[7].y <= 0) {
							h8 = 1;
							re[7].y = -20;
							re[7].y1 -= 20;
							re[7].y2 -= 20;
							if (re[7].y1 <= 0) {
								re[7].y1 = re[7].y3;
								re[7].y = re[7].y2;
								re[7].y3 = 850;
								re[7].y2 = 850;
								h8 = 0;
							}
						}
						if (re[4].x1 > 370) {
							re[4].x1 += 20;
							re[4].x += 20;
							if (re[4].x1 >= 1000) {
								h5 = 1;
								re[4].x1 += 20;
								re[4].x3 += 20;
								if (re[4].x >= 1000) {
									re[4].x1 = re[4].x3;
									re[4].x = re[4].x2;
									re[4].x3 = 0;
									re[4].x2 = 0;
									h5 = 0;
								}
							}
						}
						if (360 > re[4].x1 && re[4].x1 > 310) {
							re[4].x1 -= 20;
							re[4].x -= 20;
						}
						if (re[4].x < 150) {
							re[4].x1 += 20;
							re[4].x += 20;
						}
						if (re[5].x < 630) {
							re[5].x1 -= 20;
							re[5].x -= 20;
							if (re[5].x <= 0) {
								h6 = 1;
								re[5].x -= 20;
								re[5].x2 -= 20;
								if (re[5].x1 <= 0) {
									re[5].x1 = re[5].x3;
									re[5].x = re[5].x2;
									re[5].x3 = 1000;
									re[5].x2 = 1000;
									h6 = 0;
								}
							}
						}
						if (680 > re[5].x && re[5].x > 630) {
							re[5].x1 += 20;
							re[5].x += 20;
						}
						if (re[5].x1 > 800) {
							re[5].x1 -= 20;
							re[5].x -= 20;
						}
					}
				}
				if (Selection == 3) {
					if (re[6].y1 < 850) {
						re[6].y += 20;
						re[6].y1 += 20;
						h7 = 0;
					}
					if (re[6].y1 >= 850) {
						h7 = 1;
						re[6].y1 += 20;
						re[6].y += 20;
						re[6].y3 += 20;
						if (re[6].y >= 850) {
							re[6].y1 = re[6].y3;
							re[6].y = re[6].y2;
							re[6].y3 = 0;
							re[6].y2 = 0;
							h7 = 0;
						}
					}
					if (re[7].y > 0) {
						re[7].y -= 20;
						re[7].y1 -= 20;
						h8 = 0;
					}
					if (re[7].y <= 0) {
						h8 = 1;
						re[7].y = -20;
						re[7].y1 -= 20;
						re[7].y2 -= 20;
						if (re[7].y1 <= 0) {
							re[7].y1 = re[7].y3;
							re[7].y = re[7].y2;
							re[7].y3 = 850;
							re[7].y2 = 850;
							h8 = 0;
						}
					}
					if (re[4].x1 > 370) {
						re[4].x1 += 20;
						re[4].x += 20;
						if (re[4].x1 >= 1000) {
							h5 = 1;
							re[4].x1 += 20;
							re[4].x3 += 20;
							if (re[4].x >= 1000) {
								re[4].x1 = re[4].x3;
								re[4].x = re[4].x2;
								re[4].x3 = 0;
								re[4].x2 = 0;
								h5 = 0;
							}
						}
					}
					if (360 > re[4].x1 && re[4].x1 > 310) {
						re[4].x1 -= 20;
						re[4].x -= 20;
					}
					if (re[4].x < 150) {
						re[4].x1 += 20;
						re[4].x += 20;
					}
					if (re[5].x < 630) {
						re[5].x1 -= 20;
						re[5].x -= 20;
						if (re[5].x <= 0) {
							h6 = 1;
							re[5].x -= 20;
							re[5].x2 -= 20;
							if (re[5].x1 <= 0) {
								re[5].x1 = re[5].x3;
								re[5].x = re[5].x2;
								re[5].x3 = 1000;
								re[5].x2 = 1000;
								h6 = 0;
							}
						}
					}
					if (680 > re[5].x && re[5].x > 630) {
						re[5].x1 += 20;
						re[5].x += 20;
					}
					if (re[5].x1 > 800) {
						re[5].x1 -= 20;
						re[5].x -= 20;
					}
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
