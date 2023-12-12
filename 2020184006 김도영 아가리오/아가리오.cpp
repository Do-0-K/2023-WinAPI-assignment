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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU6);
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 800, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
struct rect {
	int x = -100, y = -100;
	int r = 0, g = 0, b = 0;
	int xdirect = 0, ydirect = 0;
	int move_x = 0, move_y = 0;
	int ime = 0;
};
struct re {
	int x = -100, y = -100;
	int r = 255, g = 0, b = 0;
	int size = 10;
	int live = 0;
	int hide = 0;
	int div = 0;
};
struct ra {
	int x = -100, y = 50;
	int r = 0, g = 255, b = 0;
	int size = 0;
	int live = 0;
	int cng = 0, cng1 = 0;
};
struct rect re[300];
struct re enemy[20][2];
struct ra trap[10];
struct ra redzone[50];
struct star {
	int x = 400, y = 300;
	int r = 0, g = 105, b = 0;
	int mx = 400, my = 300;
	int size = 20;
	int hide = 0;
	int div = 0;
};
struct star s[2];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) { //분할 해야함
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	static RECT rectView;
	static BOOL Selection;
	static int t = 30;
	static int t1 = 0;
	static int num = 1;
	static int trap_num = 5;
	int mx, my, mx1, my1;
	static TCHAR str[10];
	static int tim = 0;
	static double dist = 0;
	static int x = 0;
	static int x1 = 0;
	static TCHAR lose[25] = L"YOU LOSE";
	static TCHAR size[10];
	static int end = 0;
	int mdist = 800;
	int s1 = 0;
	int v = 0;
	static int camera = 2;
	static int x2 = 0, y2 = 0, time = 0;
	static int p = 0;
	static int who = 0;
	static int zone = 0;
	static int trap_cnt = 5;
	static int we = 0;
	switch (iMsg) {
	case WM_CREATE:
		Selection = TRUE;
		x = 0;
		for (int i = 0;i < 10;i++) {
			str[i] = NULL;
		}
		for (int i = 0;i < 30;i++) {
			re[i].x = rand() % 1000;
			re[i].y = rand() % 800;
			re[i].r = rand() % 255;
			re[i].g = rand() % 255;
			re[i].b = rand() % 255;
		}
		enemy[0][0].x = 30;
		enemy[0][0].y = 30;
		enemy[0][0].r = 255;
		enemy[0][0].g = 0;
		enemy[0][0].b = 0;
		enemy[0][0].size = 10;
		enemy[0][1].x = 30;
		enemy[0][1].y = 30;
		enemy[0][1].r = 255;
		enemy[0][1].g = 0;
		enemy[0][1].b = 0;
		enemy[0][1].size = 10;
		we = 0;
		trap[0].x =100;
		trap[0].y = 40;
		trap[1].x = 400;
		trap[1].y = 40;
		trap[2].x = 100;
		trap[2].y = 760;
		trap[3].x = 400;
		trap[3].y = 760;
		trap[4].x = 50;
		trap[4].y = 350;
		for (int i = 0;i < 50;i++) {
			redzone[i].size = 0;
			redzone[i].r = 0;
			redzone[i].g = 0;
			redzone[i].b = 0;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, 1000, 800);
		SelectObject(mdc, (HBITMAP)hBitmap);
		Rectangle(mdc, 0, 0, 1000, 800);
		if (s[0].div == 0) {
			hBrush = CreateSolidBrush(RGB(s[0].r, s[0].g, s[0].b));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, s[0].x - s[0].size, s[0].y - s[0].size, s[0].x + s[0].size, s[0].y + s[0].size);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (s[0].div == 1) {
			hBrush = CreateSolidBrush(RGB(s[0].r, s[0].g, s[0].b));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, s[0].x - s[0].size, s[0].y - s[0].size/2, s[0].x, s[0].y+s[0].size/2);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
			hBrush = CreateSolidBrush(RGB(s[1].r, s[1].g, s[1].b));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, s[1].x, s[1].y - s[1].size / 2, s[1].x + s[1].size, s[1].y + s[1].size/2);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
		}
		for (int i = t1; i < t; i++) {
			hBrush = CreateSolidBrush(RGB(re[i].r, re[i].g, re[i].b));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, re[i].x - 5, re[i].y - 5, re[i].x + 5, re[i].y + 5);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
		}
		for (int j = 0; j < num; j++) {
			if (enemy[j][0].live == 0) {
				if (enemy[j][0].div == 0) {
					hBrush = CreateSolidBrush(RGB(enemy[j][0].r, enemy[j][0].g, enemy[j][0].b));
					oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
					Ellipse(mdc, enemy[j][0].x - enemy[j][0].size, enemy[j][0].y - enemy[j][0].size, enemy[j][0].x + enemy[j][0].size, enemy[j][0].y + enemy[j][0].size);
					SelectObject(mdc, oldBrush);
					DeleteObject(hBrush);
				}
				else if (enemy[j][0].div == 1) {
					hBrush = CreateSolidBrush(RGB(enemy[j][0].r, enemy[j][0].g, enemy[j][0].b));
					oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
					Ellipse(mdc, enemy[j][0].x - enemy[j][0].size, enemy[j][0].y - enemy[j][0].size / 2, enemy[j][0].x, enemy[j][0].y + enemy[j][0].size / 2);
					SelectObject(mdc, oldBrush);
					DeleteObject(hBrush);
					hBrush = CreateSolidBrush(RGB(enemy[j][1].r, enemy[j][1].g, enemy[j][1].b));
					oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
					Ellipse(mdc, enemy[j][1].x, enemy[j][1].y - enemy[j][1].size / 2, enemy[j][1].x + enemy[j][1].size, enemy[j][1].y + enemy[j][1].size / 2);
					SelectObject(mdc, oldBrush);
					DeleteObject(hBrush);
				}
			}
		}
		for (int i = 0; i < trap_num; i++) {
			if (trap[i].live == 0) {
				hBrush = CreateSolidBrush(RGB(trap[i].r, trap[i].g, trap[i].b));
				oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
				Ellipse(mdc, trap[i].x - trap[i].size, trap[i].y - trap[i].size, trap[i].x + trap[i].size, trap[i].y + trap[i].size);
				SelectObject(mdc, oldBrush);
				DeleteObject(hBrush);
			}
		}
		for (int i = 0;i < zone;i++) {
			if (redzone[i].live == 0) {
				hBrush = CreateSolidBrush(RGB(redzone[i].r, redzone[i].g, redzone[i].b));
				oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
				Ellipse(mdc, redzone[i].x - redzone[i].size, redzone[i].y - redzone[i].size, redzone[i].x + redzone[i].size, redzone[i].y + redzone[i].size);
				SelectObject(mdc, oldBrush);
				DeleteObject(hBrush);
			}
		}
		TextOut(mdc, 2, 2, str, lstrlen(str));
		wsprintf(size, L"사이즈 : %d", s[0].size);
		TextOut(mdc, 60, 2, size, lstrlen(size));
		if (camera == 1) {
			if (end > 0) {
				TextOut(mdc, 400, 300, lose, lstrlen(lose));
				TextOut(mdc, 400, 350, str, lstrlen(str));
				wsprintf(size, L"사이즈 : %d", s[0].size);
				TextOut(mdc, 400, 400, size, lstrlen(size));
			}
			StretchBlt(hdc, 0, 0, 1000, 800, mdc, 0, 0, 1000,800,SRCCOPY);
		}
		else if (camera == 2) {
			if (end > 0) {
				TextOut(mdc, 400 - x2, 300 - y2, lose, lstrlen(lose));
				TextOut(mdc, 400 - x2, 350 - y2, str, lstrlen(str));
				wsprintf(size, L"사이즈 : %d", s[0].size);
				TextOut(mdc, 400 - x2, 400 - y2, size, lstrlen(size));
			}
			StretchBlt(hdc, 0, 0, 1000, 800, mdc, 0 - x2, 0 - y2, 800, 600 , SRCCOPY);
		}
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		s[0].mx = mx - x2;
		s[0].my = my - y2;
		break;
	case WM_LBUTTONDOWN:
		if (s[0].size > 50) {
			s[0].div = 1;
			s[1].size = s[0].size;
			s[1].x = s[0].x;
			s[1].y = s[0].y;
			SetTimer(hwnd, 4, x / 2, NULL);
			SetTimer(hwnd, 8, 5000, NULL);
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (s[0].size > 10) {
			p = t;
			re[p].move_x = mx;
			re[p].move_y = my;
			if (s[0].x < re[p].move_x) {
				re[p].xdirect = 1;
			}
			if (s[0].x > re[p].move_x) {
				re[p].xdirect = 2;
			}
			if (s[0].y < re[p].move_y) {
				re[p].ydirect = 1;
			}
			if (s[0].y > re[p].move_y) {
				re[p].ydirect = 2;
			}
			if (re[p].xdirect == 1 && re[p].ydirect == 1) {
				re[p].x = s[0].x + s[0].size + 5;
				re[p].y = s[0].y + s[0].size + 5;
			}
			if (re[p].xdirect == 1 && re[p].ydirect == 2) {
				re[p].x = s[0].x + s[0].size + 5;
				re[p].y = s[0].y - s[0].size - 5;
			}
			if (re[p].xdirect == 2 && re[p].ydirect == 1) {
				re[p].x = s[0].x - s[0].size - 5;
				re[p].y = s[0].y + s[0].size + 5;
			}
			if (re[p].xdirect == 2 && re[p].ydirect == 2) {
				re[p].x = s[0].x - s[0].size - 5;
				re[p].y = s[0].y - s[0].size - 5;
			}
			re[p].r = rand() % 255;
			re[p].g = rand() % 255;
			re[p].b = rand() % 255;
			t++;
			if (s[0].div == 0) {
				s[0].size -= 1;
			}
			if (s[0].div == 1) {
				s[0].size -= 0.5;
				s[1].size -= 0.5;
			}
			if (x < 2) {
				SetTimer(hwnd, 4, 0, NULL);
			}
			else {
				x -= 2;
				SetTimer(hwnd, 4, x, NULL);
			}
			SetTimer(hwnd, 9, 10, NULL);
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_40067:
			camera = 1;
			break;
		case ID_40068:
			camera = 2;
			break;
		case ID_40069:
			SetTimer(hwnd, 1, 1000, NULL);
			SetTimer(hwnd, 2, 0, NULL);
			SetTimer(hwnd, 3, 1000, NULL);
			SetTimer(hwnd, 4, 0, NULL);
			SetTimer(hwnd, 5, 15000, NULL);
			SetTimer(hwnd, 6, 0, NULL);
			SetTimer(hwnd, 13,30000, NULL);
			SetTimer(hwnd, 14, 500, NULL);
			break;
		case ID_40070:
			t = 30;
			tim = 0;
			num = 1;
			t1 = 0;
			for (int i = 0;i < 30;i++) {
				re[i].x = rand() % 1000;
				re[i].y = rand() % 800;
				re[i].r = rand() % 255;
				re[i].g = rand() % 255;
				re[i].b = rand() % 255;
			}
			s[0].size = 20;
			enemy[0][0].x = 0;
			enemy[0][0].y = 0;
			enemy[0][0].r = 255;
			enemy[0][0].g = 0;
			enemy[0][0].b = 0;
			enemy[0][0].size = 10;
			enemy[0][1].x = 0;
			enemy[0][1].y = 0;
			enemy[0][1].r = 255;
			enemy[0][1].g = 0;
			enemy[0][1].b = 0;
			enemy[0][1].size = 10;
			trap[0].x = 100;
			trap[0].y = 40;
			trap[1].x = 400;
			trap[1].y = 40;
			trap[2].x = 100;
			trap[2].y = 760;
			trap[3].x = 400;
			trap[3].y = 760;
			trap[4].x = 50;
			trap[4].y = 350;
			s[0].x = 400;
			s[0].y = 300;
			s[1].x = 400;
			s[1].y = 300;
			end = 0;
			x = 0;
			x1 = 0;
			x2 = 0, y2 = 0;
			mdist = 800;
			who = 0;time = 0;
			zone = 0;
			we = 0;
			for (int i = 0;i < 5;i++) {
				trap[i].size = 0;
			}
			trap_num = 5;
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 4);
			KillTimer(hwnd, 5);
			KillTimer(hwnd, 6);
			KillTimer(hwnd, 7);
			KillTimer(hwnd, 8);
			KillTimer(hwnd, 9);
			KillTimer(hwnd, 10);
			KillTimer(hwnd, 11);
			KillTimer(hwnd, 12);
			KillTimer(hwnd, 13);
			break;
		case ID_40071:
			t = 30;
			tim = 0;
			num = 1;
			t1 = 0;
			trap_num = 5;
			for (int i = 0;i < 30;i++) {
				re[i].x = rand() % 1000;
				re[i].y = rand() % 800;
				re[i].r = rand() % 255;
				re[i].g = rand() % 255;
				re[i].b = rand() % 255;
			}
			s[0].size = 20;
			enemy[0][0].x = 0;
			enemy[0][0].y = 0;
			enemy[0][0].r = 255;
			enemy[0][0].g = 0;
			enemy[0][0].b = 0;
			enemy[0][0].size = 10;
			enemy[0][1].x = 0;
			enemy[0][1].y = 0;
			enemy[0][1].r = 255;
			enemy[0][1].g = 0;
			enemy[0][1].b = 0;
			enemy[0][1].size = 10;
			trap[0].x = 100;
			trap[0].y = 40;
			trap[1].x = 400;
			trap[1].y = 40;
			trap[2].x = 100;
			trap[2].y = 760;
			trap[3].x = 400;
			trap[3].y = 760;
			trap[4].x = 50;
			trap[4].y = 350;
			s[0].x = 400;
			s[0].y = 300;
			s[1].x = 400;
			s[1].y = 300;
			end = 0;
			we = 0;
			x = 0;
			x1 = 0;
			x2 = 0, y2 = 0;
			mdist = 800;
			who = 0;time = 0;
			zone = 0;
			for (int i = 0;i < 5;i++) {
				trap[i].size = 0;
			}
			trap_num = 5;
			KillTimer(hwnd, 7);
			SetTimer(hwnd, 1, 1000, NULL);
			SetTimer(hwnd, 2, 0, NULL);
			SetTimer(hwnd, 3, 1000, NULL);
			SetTimer(hwnd, 4, 0, NULL);
			SetTimer(hwnd, 5, 15000, NULL);
			SetTimer(hwnd, 6, 0, NULL);
			SetTimer(hwnd, 13, 30000, NULL);
			SetTimer(hwnd, 14, 500, NULL);
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			re[t].x = rand() % 1000;
			re[t].y = rand() % 800;
			re[t].r = rand() % 255;
			re[t].g = rand() % 255;
			re[t].b = rand() % 255;
			t++;
			t1++;
			break;
		case 2:
			wsprintf(str, L"time : %d", tim);
			break;
		case 3:
			tim++;
			break;
		case 4:
			if (camera == 1) {
				if (s[0].x < s[0].mx) {
					if (s[0].y < s[0].my) {
						s[0].y += 1;
						s[0].y += 1;
						s[0].x += 1;
						s[0].x += 1;
						s[1].y += 1;
						s[1].y += 1;
						s[1].x += 1;
						s[1].x += 1;
					}
					else if (s[0].y == s[0].my) {
						s[0].x += 1;
						s[0].x += 1;
						s[1].x += 1;
						s[1].x += 1;
					}
					else {
						s[0].x += 1;
						s[0].x += 1;
						s[0].y -= 1;
						s[0].y -= 1;
						s[1].x += 1;
						s[1].x += 1;
						s[1].y -= 1;
						s[1].y -= 1;
					}
				}
				if (s[0].x > s[0].mx) {
					if (s[0].y < s[0].my) {
						s[0].y += 1;
						s[0].y += 1;
						s[0].x -= 1;
						s[0].x -= 1;
						s[1].y += 1;
						s[1].y += 1;
						s[1].x -= 1;
						s[1].x -= 1;
					}
					else if (s[0].y == s[0].my) {
						s[0].x -= 1;
						s[0].x -= 1;
						s[1].x -= 1;
						s[1].x -= 1;
					}
					else {
						s[0].x -= 1;
						s[0].x -= 1;
						s[0].y -= 1;
						s[0].y -= 1;
						s[1].x -= 1;
						s[1].x -= 1;
						s[1].y -= 1;
						s[1].y -= 1;
					}
				}
				if (s[0].x == s[0].mx) {
					if (s[0].y < s[0].my) {
						s[0].y += 1;
						s[0].y += 1;
						s[1].y += 1;
						s[1].y += 1;

					}
					else {
						s[0].y -= 1;
						s[0].y -= 1;
						s[1].y -= 1;
						s[1].y -= 1;
					}
				}
			}
			if (camera == 2) {
				if (s[0].x < s[0].mx) {
					if (s[0].y < s[0].my) {
						s[0].y += 1;
						s[0].y += 1;
						s[0].x += 1;
						s[0].x += 1;
						s[1].y += 1;
						s[1].y += 1;
						s[1].x += 1;
						s[1].x += 1;
						x2 -= 1;
						y2 -= 1;
					}
					else if (s[0].y == s[0].my) {
						s[0].x += 1;
						s[0].x += 1;
						s[1].x += 1;
						s[1].x += 1;
						x2 -= 1;
					}
					else {
						s[0].x += 1;
						s[0].x += 1;
						s[0].y -= 1;
						s[0].y -= 1;
						s[1].x += 1;
						s[1].x += 1;
						s[1].y -= 1;
						s[1].y -= 1;
						x2 -= 1;
						y2 += 1;
					}
				}
				if (s[0].x > s[0].mx) {
					if (s[0].y < s[0].my) {
						s[0].y += 1;
						s[0].y += 1;
						s[0].x -= 1;
						s[0].x -= 1;
						s[1].y += 1;
						s[1].y += 1;
						s[1].x -= 1;
						s[1].x -= 1;
						y2 -= 1;
						x2 += 1;
					}
					else if (s[0].y == s[0].my) {
						s[0].x -= 1;
						s[0].x -= 1;
						s[1].x -= 1;
						s[1].x -= 1;
						x2 += 1;
					}
					else {
						s[0].x -= 1;
						s[0].x -= 1;
						s[0].y -= 1;
						s[0].y -= 1;
						s[1].x -= 1;
						s[1].x -= 1;
						s[1].y -= 1;
						s[1].y -= 1;
						x2 += 1;
						y2 += 1;
					}
				}
				if (s[0].x == s[0].mx) {
					if (s[0].y < s[0].my) {
						s[0].y += 1;
						s[0].y += 1;
						s[1].y += 1;
						s[1].y += 1;
						y2 -= 1;
					}
					else {
						s[0].y -= 1;
						s[0].y -= 1;
						s[1].y -= 1;
						s[1].y -= 1;
						y2 += 1;
					}
				}
				if (x2 >= 400) {
					x2 += 1;
				}
			}
			if (s[0].x + s[0].size >= 1000) {
				s[0].x -= 2;
				s[1].x -= 2;
			}
			if (s[0].x - s[0].size <= 0) {
				s[0].x += 2;
				s[1].x += 2;
			}
			if (s[0].y + s[0].size >= 800) {
				s[0].y -= 2;
				s[1].y -= 2;
			}
			if (s[0].y - s[0].size <= 0) {
				s[0].y += 2;
				s[1].y += 2;
			}
			if (x2 > 0) {
				x2 -= 1;
			}
			if (y2 > 0) {
				y2 -= 1;
			}
			if (x2 <= -200) {
				x2 += 1;
			}
			if (y2 <= -200) {
				y2 += 1;
			}
			break;
		case 5:
			enemy[num][0].x = rand() % 600;
			enemy[num][0].y = 0;
			num++;
			break;
		case 6:
			for (int j = 0;j < num;j++) {
				for (int i = t1;i < t;i++) {
					dist = sqrt((enemy[j][0].x - re[i].x) * (enemy[j][0].x - re[i].x) + (enemy[j][0].y - re[i].y) * (enemy[j][0].y - re[i].y));
					if (mdist >= dist) {
						mdist = dist;
						s1 = i;
						v = -1;
					}
				}
				dist = sqrt((enemy[j][0].x - s[0].x) * (enemy[j][0].x - s[0].x) + (enemy[j][0].y - s[0].y) * (enemy[j][0].y - s[0].y));
				if (s[0].hide == 0) {
					if (mdist >= dist) {
						mdist = dist;
						if (s[0].size < enemy[j][0].size) {
							v = 1;
						}
						else {
							v = 0;
						}
					}
				}
			}
			for (int i = 0;i < num;i++) {
				if (enemy[i][0].live == 0) {
					if (v == 1) {
						if (enemy[i][0].x < s[0].x) {
							if (enemy[i][0].y < s[0].y) {
								enemy[i][0].y += 1;
								enemy[i][0].y += 1;
								enemy[i][0].x += 1;
								enemy[i][0].x += 1;
								enemy[i][1].y += 1;
								enemy[i][1].y += 1;
								enemy[i][1].x += 1;
								enemy[i][1].x += 1;
							}
							else if (enemy[i][0].y == s[0].y) {
								enemy[i][0].x += 1;
								enemy[i][0].x += 1;
								enemy[i][1].x += 1;
								enemy[i][1].x += 1;
							}
							else {
								enemy[i][0].x += 1;
								enemy[i][0].x += 1;
								enemy[i][0].y -= 1;
								enemy[i][0].y -= 1;
								enemy[i][1].x += 1;
								enemy[i][1].x += 1;
								enemy[i][1].y -= 1;
								enemy[i][1].y -= 1;
							}
						}
						if (enemy[i][0].x > s[0].x) {
							if (enemy[i][0].y < s[0].y) {
								enemy[i][0].y += 1;
								enemy[i][0].y += 1;
								enemy[i][0].x -= 1;
								enemy[i][0].x -= 1;
								enemy[i][1].y += 1;
								enemy[i][1].y += 1;
								enemy[i][1].x -= 1;
								enemy[i][1].x -= 1;
							}
							else if (enemy[i][0].y == s[0].y) {
								enemy[i][0].x -= 1;
								enemy[i][0].x -= 1;
								enemy[i][1].x -= 1;
								enemy[i][1].x -= 1;
							}
							else {
								enemy[i][0].x -= 1;
								enemy[i][0].x -= 1;
								enemy[i][0].y -= 1;
								enemy[i][0].y -= 1;
								enemy[i][1].x -= 1;
								enemy[i][1].x -= 1;
								enemy[i][1].y -= 1;
								enemy[i][1].y -= 1;
							}
						}
						if (enemy[i][0].x == s[0].x) {
							if (enemy[i][0].y < s[0].y) {
								enemy[i][0].y += 1;
								enemy[i][0].y += 1;
								enemy[i][1].y += 1;
								enemy[i][1].y += 1;

							}
							else {
								enemy[i][0].y -= 1;
								enemy[i][0].y -= 1;
								enemy[i][1].y -= 1;
								enemy[i][1].y -= 1;
							}
						}
					}
					else if (v == 0) {
						if (enemy[i][0].x < s[0].x) {
							if (enemy[i][0].y < s[0].y) {
								enemy[i][0].y -= 1;
								enemy[i][0].y -= 1;
								enemy[i][0].x -= 1;
								enemy[i][0].x -= 1;
								enemy[i][1].y -= 1;
								enemy[i][1].y -= 1;
								enemy[i][1].x -= 1;
								enemy[i][1].x -= 1;
							}
							else if (enemy[i][0].y == s[0].y) {
								enemy[i][0].x -= 1;
								enemy[i][0].x -= 1;
								enemy[i][1].x -= 1;
								enemy[i][1].x -= 1;
							}
							else {
								enemy[i][0].x -= 1;
								enemy[i][0].x -= 1;
								enemy[i][0].y += 1;
								enemy[i][0].y += 1;
								enemy[i][1].x -= 1;
								enemy[i][1].x -= 1;
								enemy[i][1].y += 1;
								enemy[i][1].y += 1;
							}
						}
						if (enemy[i][0].x > s[0].x) {
							if (enemy[i][0].y < s[0].y) {
								enemy[i][0].y -= 1;
								enemy[i][0].y -= 1;
								enemy[i][0].x += 1;
								enemy[i][0].x += 1;
								enemy[i][1].y -= 1;
								enemy[i][1].y -= 1;
								enemy[i][1].x += 1;
								enemy[i][1].x += 1;
							}
							else if (enemy[i][0].y == s[0].y) {
								enemy[i][0].x += 1;
								enemy[i][0].x += 1;
								enemy[i][1].x += 1;
								enemy[i][1].x += 1;
							}
							else {
								enemy[i][0].x += 1;
								enemy[i][0].x += 1;
								enemy[i][0].y += 1;
								enemy[i][0].y += 1;
								enemy[i][1].x += 1;
								enemy[i][1].x += 1;
								enemy[i][1].y += 1;
								enemy[i][1].y += 1;
							}
						}
						if (enemy[i][0].x == s[0].x) {
							if (enemy[i][0].y < s[0].y) {
								enemy[i][0].y -= 1;
								enemy[i][0].y -= 1;
								enemy[i][1].y -= 1;
								enemy[i][1].y -= 1;

							}
							else {
								enemy[i][0].y += 1;
								enemy[i][0].y += 1;
								enemy[i][1].y += 1;
								enemy[i][1].y += 1;
							}
						}
					}
					else {
						if (enemy[i][0].x < re[s1].x) {
							if (enemy[i][0].y < re[s1].y) {
								enemy[i][0].y += 1;
								enemy[i][0].y += 1;
								enemy[i][0].x += 1;
								enemy[i][0].x += 1;
								enemy[i][1].y += 1;
								enemy[i][1].y += 1;
								enemy[i][1].x += 1;
								enemy[i][1].x += 1;
							}
							else if (enemy[i][0].y == re[s1].y) {
								enemy[i][0].x += 1;
								enemy[i][0].x += 1;
								enemy[i][1].x += 1;
								enemy[i][1].x += 1;
							}
							else {
								enemy[i][0].x += 1;
								enemy[i][0].x += 1;
								enemy[i][0].y -= 1;
								enemy[i][0].y -= 1;
							}
						}
						if (enemy[i][0].x > re[s1].x) {
							if (enemy[i][0].y < re[s1].y) {
								enemy[i][0].y += 1;
								enemy[i][0].y += 1;
								enemy[i][0].x -= 1;
								enemy[i][0].x -= 1;
								enemy[i][1].y += 1;
								enemy[i][1].y += 1;
								enemy[i][1].x -= 1;
								enemy[i][1].x -= 1;
							}
							else if (enemy[i][0].y == re[s1].y) {
								enemy[i][0].x -= 1;
								enemy[i][0].x -= 1;
								enemy[i][1].x -= 1;
								enemy[i][1].x -= 1;
							}
							else {
								enemy[i][0].x -= 1;
								enemy[i][0].x -= 1;
								enemy[i][0].y -= 1;
								enemy[i][0].y -= 1;
								enemy[i][1].x -= 1;
								enemy[i][1].x -= 1;
								enemy[i][1].y -= 1;
								enemy[i][1].y -= 1;
							}
						}
						if (enemy[i][0].x == re[s1].x) {
							if (enemy[i][0].y < re[s1].y) {
								enemy[i][0].y += 1;
								enemy[i][0].y += 1;
								enemy[i][1].y += 1;
								enemy[i][1].y += 1;

							}
							else {
								enemy[i][0].y -= 1;
								enemy[i][0].y -= 1;
								enemy[i][1].y -= 1;
								enemy[i][1].y -= 1;
							}
						}
					}
				}
			}
			for (int j = 0;j < num;j++) {
				for (int i = t1;i < t;i++) {
					dist = sqrt((enemy[j][0].x - re[i].x) * (enemy[j][0].x - re[i].x) + (enemy[j][0].y - re[i].y) * (enemy[j][0].y - re[i].y));
					if (dist <= enemy[j][0].size + 5) {
						re[i].x = rand() % 1000;
						re[i].y = rand() % 800;
						re[i].r = rand() % 255;
						re[i].g = rand() % 255;
						re[i].b = rand() % 255;
						enemy[j][0].size += 1;
						enemy[j][1].size += 1;
						if (enemy[j][0].size % 30 == 0) {
							x1 += 10;
							SetTimer(hwnd, 6, x1, NULL);
						}
					}
				}
			}
			for (int j = 0;j < num;j++) {
				if (enemy[j][0].x + enemy[j][0].size >= 1000) {
					enemy[j][0].x -= 2;
					enemy[j][1].x -= 2;
				}
				if (enemy[j][0].x - enemy[j][0].size <= 0) {
					enemy[j][0].x += 2;
					enemy[j][1].x += 2;
				}
				if (enemy[j][0].y + enemy[j][0].size >= 800) {
					enemy[j][0].y -= 2;
					enemy[j][1].y -= 2;
				}
				if (enemy[j][0].y - enemy[j][0].size <= 0) {
					enemy[j][0].y += 2;
					enemy[j][1].y += 2;
				}
			}
			break;
		case 7:
			for (int i = 0;i < trap_num;i++) {
				if (trap[i].cng % 2 == 0) {
					trap[i].x += 1;
				}
				if (trap[i].cng % 2 == 1) {
					trap[i].x -= 1;
				}
				if (trap[i].x + trap[i].size > 1000) {
					trap[i].cng++;
				}
				if (trap[i].x - trap[i].size < 10) {
					trap[i].cng++;
				}
				if (trap[i].cng1 % 2 == 0) {
					trap[i].y += 1;
				}
				if (trap[i].cng1 % 2 == 1) {
					trap[i].y -= 1;
				}
				if (trap[i].y - trap[i].size < 0) {
					trap[i].cng1++;
				}
				if (trap[i].y + trap[i].size > 800) {
					trap[i].cng1++;
				}
			}
			break;
		case 8:
			s[0].div = 0;
			SetTimer(hwnd, 4, x, NULL);
			KillTimer(hwnd, 8);
			break;
		case 9:
			if (re[p].xdirect == 1 && re[p].ydirect == 1) {
				re[p].x += 7;
				re[p].y += 7;
			}
			if (re[p].xdirect == 1 && re[p].ydirect == 2) {
				re[p].x += 7;
				re[p].y -= 7;
			}
			if (re[p].xdirect == 2 && re[p].ydirect == 1) {
				re[p].x -= 7;
				re[p].y += 7;
			}
			if (re[p].xdirect == 2 && re[p].ydirect == 2) {
				re[p].x -= 7;
				re[p].y -= 7;
			}
			re[p].ime++;
			if (re[p].ime == 5) {
				time = 0;
				KillTimer(hwnd, 9);
			}
			break;
		case 10:
			for (int i = 0;i < num;i++) {
				if (enemy[i][0].div == 1) {
					enemy[i][0].div = 0;
				}
			}
			KillTimer(hwnd, 10);
			break;
		case 11:
			redzone[zone-1].size += 5;
			if (redzone[zone-1].size == 50) {
				redzone[zone-1].r = 255;
				SetTimer(hwnd, 12, 100, NULL);
			}
			if (redzone[zone-1].size >= 55) {
				redzone[zone-1].size -= 5;
			}
			break;
		case 12:
			for (int j = 0;j < zone;j++) {
				if (redzone[j].live == 0) {
					for (int i = 0;i < num;i++) {
						dist = sqrt((redzone[j].x - enemy[i][0].x) * (redzone[j].x - enemy[i][0].x) + (redzone[j].y - enemy[i][0].y) * (redzone[j].y - enemy[i][0].y));
						if (dist <= redzone[j].size + enemy[i][0].size) {
							enemy[i][0].x = -100;
							enemy[i][0].y = -100;
							enemy[i][0].live = 1;
							enemy[i][0].size = 0;
						}
					}
					for (int k = 0;k < trap_num;k++) {
						dist = sqrt((redzone[j].x - trap[k].x) * (redzone[j].x - trap[k].x) + (redzone[j].y - trap[k].y) * (redzone[j].y - trap[k].y));
						if (dist <= redzone[j].size + trap[k].size) {
							trap[k].x = rand() % 500 + 50;
							trap[k].y = 40;
							trap[k].live = 0;
						}
					}
					for (int n = 0;n < t;n++) {
						dist = sqrt((redzone[j].x - re[n].x) * (redzone[j].x - re[n].x) + (redzone[j].y - re[n].y) * (redzone[j].y - re[n].y));
						if (dist <= redzone[j].size + 5) {
							re[n].x = rand() % 1000;
							re[n].y = rand() % 800;
							re[n].r = rand() % 255;
							re[n].g = rand() % 255;
							re[n].b = rand() % 255;
						}
					}
					dist = sqrt((redzone[j].x - s[0].x) * (redzone[j].x - s[0].x) + (redzone[j].y - s[0].y) * (redzone[j].y - s[0].y));
					if (dist <= redzone[j].size + s[0].size) {
						if (s[0].div == 0) {
							if (s[0].hide != 1) {
								s[0].size = 0;
								end++;
								KillTimer(hwnd, 1);
								KillTimer(hwnd, 2);
								KillTimer(hwnd, 3);
								KillTimer(hwnd, 4);
								KillTimer(hwnd, 5);
								KillTimer(hwnd, 6);
								KillTimer(hwnd, 7);
								KillTimer(hwnd, 13);
							}
						}
					}
					dist = sqrt((redzone[j].x - s[1].x) * (redzone[j].x - s[1].x) + (redzone[j].y - s[1].y) * (redzone[j].y - s[1].y));
					if (dist <= redzone[j].size + s[1].size) {
						if (s[0].div == 1) {
							s[1].x = -100;
							s[1].y = -100;
							s[0].size = s[0].size / 2;
							s[0].div = 0;
						}
					}
				}
			}
			redzone[zone - 1].live = 1;
			redzone[zone - 1].size = 0;
			KillTimer(hwnd, 12);
			KillTimer(hwnd, 11);
			break;
		case 13:
			redzone[zone].x = rand() % 800;
			redzone[zone].y = rand() % 800;
			redzone[zone].live = 0;
			zone++;
			SetTimer(hwnd, 11, 1000, NULL);
			break;
		case 14:
			if (we == 0) {
				trap[0].size += 10;
				trap[1].size += 10;
				trap[2].size += 10;
				trap[3].size += 10;
				trap[4].size += 10;
				if (trap[0].size == 40) {
					SetTimer(hwnd, 7, 0, NULL);
					KillTimer(hwnd, 14);
					we++;
				}
			}
			trap[trap_num].size += 10;
			if (trap[trap_num].size == 40) {
				SetTimer(hwnd, 7, 0, NULL);
				trap_num++;
				KillTimer(hwnd, 14);
			}
			break;
		}
		for (int i = 0;i < num;i++) {
				if (enemy[i][0].live == 0) {
					dist = sqrt((s[0].x - enemy[i][0].x) * (s[0].x - enemy[i][0].x) + (s[0].y - enemy[i][0].y) * (s[0].y - enemy[i][0].y));
					if (s[0].div == 0) {
						if (dist <= s[0].size + enemy[i][0].size) {
							if (s[0].size > enemy[i][0].size) {
								if (enemy[i][0].hide == 0) {
									if (enemy[i][0].div == 0) {
										s[0].size += enemy[i][0].size / 4;
										s[1].size += enemy[i][0].size / 4;
										enemy[i][0].x = -100;
										enemy[i][0].y = -100;
										enemy[i][0].live = 1;
										enemy[i][0].hide = 0;
									}
									else if (enemy[i][0].div == 1) {
										if (s[0].size > enemy[i][0].size/2) {
											if (enemy[i][0].hide == 0) {
												enemy[i][1].x = -100;
												enemy[i][1].y = -100;
												enemy[i][0].size = enemy[i][0].size / 2;
												enemy[i][0].div = 0;
												s[0].size += enemy[i][0].size / 2;
											}
										}
										else {
											if (s[0].hide != 1) {
												end++;
												KillTimer(hwnd, 1);
												KillTimer(hwnd, 2);
												KillTimer(hwnd, 3);
												KillTimer(hwnd, 4);
												KillTimer(hwnd, 5);
												KillTimer(hwnd, 6);
												KillTimer(hwnd, 7);
											}
										}
									}
								}
							}
							else {
								if (s[0].hide != 1) {
									end++;
									KillTimer(hwnd, 1);
									KillTimer(hwnd, 2);
									KillTimer(hwnd, 3);
									KillTimer(hwnd, 4);
									KillTimer(hwnd, 5);
									KillTimer(hwnd, 6);
									KillTimer(hwnd, 7);
								}
							}
						}
					}
					else {
						if (dist <= s[0].size + enemy[i][0].size) {
							if (s[0].size / 2 > enemy[i][0].size) {
								if (enemy[i][0].hide == 0) {
									if (enemy[i][0].div == 0) {
										s[0].size += enemy[i][0].size / 2;
										s[1].size += enemy[i][0].size / 2;
										enemy[i][0].x = -100;
										enemy[i][0].y = -100;
										enemy[i][0].live = 1;
										enemy[i][0].hide = 0;
									}
									else if (enemy[i][0].div == 1) {
										if (s[0].size / 2 > enemy[i][0].size / 2) {
											if (enemy[i][0].hide == 0) {
												enemy[i][1].x = -100;
												enemy[i][1].y = -100;
												enemy[i][0].size = enemy[i][0].size / 2;
												enemy[i][0].div = 0;
												s[0].size += enemy[i][0].size / 2;
											}
										}
										else {
											if (s[0].hide != 1) {
												s[1].x = -100;
												s[1].y = -100;
												s[0].size = s[0].size / 2;
												s[0].div = 0;
												enemy[i][0].size += s[0].size / 2;
											}
										}
									}
								}
							}
							else {
								if (s[0].hide != 1) {
									s[1].x = -100;
									s[1].y = -100;
									s[0].size = s[0].size / 2;
									s[0].div = 0;
									enemy[i][0].size += s[0].size / 2;
								}
							}
						}
					}
				}
		}
		for (int i = 0;i < trap_num;i++) {
			if (trap[i].live == 0) {
				dist = sqrt((s[0].x - trap[i].x) * (s[0].x - trap[i].x) + (s[0].y - trap[i].y) * (s[0].y - trap[i].y));
				if (s[0].div == 0) {
					if (dist <= s[0].size + trap[i].size) {
						if (s[0].size < trap[i].size) {
							s[0].hide = 1;
						}
						else {
							s[0].hide = 0;
							s[0].div = 1;
							s[1].size = s[0].size;
							s[1].x = s[0].x;
							s[1].y = s[0].y;
							trap[i].x = -100;
							trap[i].y = -100;
							trap[i].live = 1;
							trap[trap_num].x = rand() % 400 + 50;
							trap[trap_num].y = 40;
							trap[trap_num].live = 0;
							trap[trap_num].size = 0;
							SetTimer(hwnd, 14, 500, NULL);
						}
					}
					else {
						s[0].hide = 0;
					}
				}
				else {
					if (dist <= s[0].size/2 + trap[i].size) {
						if (s[0].size/2 < trap[i].size) {
							s[0].hide = 1;
						}
						else {
							s[0].hide = 0;
							trap[i].x = -100;
							trap[i].y = -100;
							trap[i].live = 1;
							trap[trap_num].x = rand() % 400 + 50;
							trap[trap_num].y = 40;
							trap[trap_num].live = 0;
							trap[trap_num].size = 0;
							SetTimer(hwnd, 14, 500, NULL);
						}
					}
					else {
						s[0].hide = 0;
					}
				}
			}
		}
		for (int i = 0;i < trap_num;i++) {
			for(int j=0;j<num;j++){
				if (trap[i].live == 0) {
					dist = sqrt((enemy[j][0].x - trap[i].x) * (enemy[j][0].x - trap[i].x) + (enemy[j][0].y - trap[i].y) * (enemy[j][0].y - trap[i].y));
					if (enemy[j][0].div == 0) {
						if (dist <= enemy[j][0].size + trap[i].size) {
							if (enemy[j][0].size < trap[i].size) {
								enemy[j][0].hide = 1;
							}
							else {
								enemy[j][0].hide = 0;
								enemy[j][0].div = 1;
								enemy[j][1].size = enemy[j][0].size;
								enemy[j][1].x = enemy[j][0].x;
								enemy[j][1].y = enemy[j][0].y;
								trap[i].x = -100;
								trap[i].y = -100;
								trap[i].live = 1;
								trap[trap_num].x = rand() % 400 + 50;
								trap[trap_num].y = 40;
								trap[trap_num].live = 0;
								trap[trap_num].size = 0;
								SetTimer(hwnd, 14, 500, NULL);
							}
						}
						else {
							enemy[j][0].hide = 0;
						}
					}
					else {
						if (dist <= enemy[j][0].size / 2 + trap[i].size) {
							if (enemy[j][0].size / 2 < trap[i].size) {
								enemy[j][0].hide = 1;
							}
							else {
								enemy[j][0].hide = 0;
								trap[i].x = -100;
								trap[i].y = -100;
								trap[i].live = 1;
								trap[trap_num].x = rand() % 400 + 50;
								trap[trap_num].y = 40;
								trap[trap_num].live = 0;
								trap[trap_num].size = 0;
								SetTimer(hwnd, 14, 500, NULL);
							}
						}
						else {
							enemy[j][0].hide = 0;
						}
					}
				}
			}
		}
		for (int i = 0;i < t;i++) {
			dist = sqrt((s[0].x - re[i].x) * (s[0].x - re[i].x) + (s[0].y - re[i].y) * (s[0].y - re[i].y));
			if (dist <= s[0].size + 5) {
				re[i].x = rand() % 1000;
				re[i].y = rand() % 800;
				re[i].r = rand() % 255;
				re[i].g = rand() % 255;
				re[i].b = rand() % 255;
				s[0].size += 1;
				s[1].size += 1;
				if (s[0].size % 30 == 0) {
					x += 10;
					SetTimer(hwnd, 4, x, NULL);
				}
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		KillTimer(hwnd, 2);
		KillTimer(hwnd, 3);
		KillTimer(hwnd, 4);
		KillTimer(hwnd, 5);
		KillTimer(hwnd, 6);
		KillTimer(hwnd, 7);
		KillTimer(hwnd, 8);
		KillTimer(hwnd, 9);
		KillTimer(hwnd, 13);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}