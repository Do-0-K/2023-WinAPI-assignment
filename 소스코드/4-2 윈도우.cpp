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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);
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
	int x = 0, y = 0;
	int x1 = 0, y1 = 0;
	int r = 0, g = 0, b = 0;
	int mx = 0, my = 0;
	int ner = 0, nop = 0;
	RECT rd{};
};
struct rect re[5];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) { //충동체크 조금 더 세밀하게 확인해봐야할 듯
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	RECT ra[20]{};
	int mx, my, mx1, my1;
	int x1, y1;
	static int l = 0, j = 0;
	static int pen = 0, th = 0;
	static int t = 0, v = 0, p = 0, v1 = 0;
	static int r = 0, g = 0, b = 0;
	static int startX, startY, oldX, oldY;
	static BOOL Drag;
	static BOOL Drag1;
	int endX, endY;
	static int num = 0;
	switch (iMsg) {
	case WM_CREATE:
		pen = 0;
		Drag = FALSE;
		Drag1 = FALSE;
		startX = oldX = 0;
		startY = oldY = 0;
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		Rectangle(mdc, 0, 0, rt.right, rt.bottom);
		for (int i = 0; i < 1600; i++) {
			if (i > 0) {
				if (i % 40 == 0) {
					l = 0;
					j++;
				}
			}
			POINT point0[8] = { {0 + l * 20,0 + j * 20},{20 + l * 20,0 + j * 20}, {20 + l * 20, 20 + j * 20} ,{0 + l * 20, 20 + j * 20} };
			if (pen == 0) {
				hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				oldPen = (HPEN)SelectObject(mdc, hPen);
				Polygon(mdc, point0, 4);
				SelectObject(mdc, oldPen);
				DeleteObject(hPen);
			}
			else if (pen == 1) {
				hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
				oldPen = (HPEN)SelectObject(mdc, hPen);
				Polygon(mdc, point0, 4);
				SelectObject(mdc, oldPen);
				DeleteObject(hPen);
			}
			l++;
		}
		for (int i = 0; i < t; i++) {
			if (pen == 0) {
				if (th == 1) {
					hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
					oldPen = (HPEN)SelectObject(mdc, hPen);
					Rectangle(mdc, re[i].x, re[i].y, re[i].x1, re[i].y1);
					SelectObject(mdc, oldPen);
					DeleteObject(hPen);
				}
				if (p == i) {
					hPen = CreatePen(PS_SOLID, 10, RGB(100, 100, 100));
					oldPen = (HPEN)SelectObject(mdc, hPen);
					Rectangle(mdc, re[i].x, re[i].y, re[i].x1, re[i].y1);
					SelectObject(mdc, oldPen);
					DeleteObject(hPen);
				}
				hBrush = CreateSolidBrush(RGB(re[i].r, re[i].g, re[i].b));
				oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
				Rectangle(mdc, re[i].x, re[i].y, re[i].x1, re[i].y1);
				SelectObject(mdc, oldBrush);
				DeleteObject(hBrush);
			}
			else if (pen == 1) {
				if (th == 1) {
					hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
					oldPen = (HPEN)SelectObject(mdc, hPen);
					Rectangle(mdc, re[i].x, re[i].y, re[i].x1, re[i].y1);
					SelectObject(mdc, oldPen);
					DeleteObject(hPen);
				}
				if (p == i) {
					hPen = CreatePen(PS_SOLID, 10, RGB(100, 100, 100));
					oldPen = (HPEN)SelectObject(mdc, hPen);
					Rectangle(mdc, re[i].x, re[i].y, re[i].x1, re[i].y1);
					SelectObject(mdc, oldPen);
					DeleteObject(hPen);
				}
				hBrush = CreateSolidBrush(RGB(re[i].r, re[i].g, re[i].b));
				oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
				Rectangle(mdc, re[i].x, re[i].y, re[i].x1, re[i].y1);
				SelectObject(mdc, oldBrush);
				DeleteObject(hBrush);
			}
		}
		for (int i = 0; i < t; i++) {
			for (int j = i+1;j < t;j++) {
				if (IntersectRect(&ra[num], &re[i].rd, &re[j].rd)) {
					hBrush = CreateSolidBrush(RGB(re[i].r + re[j].r, re[i].g + re[j].g, re[i].b + re[j].b));
					oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
					Rectangle(mdc, ra[num].left, ra[num].top, ra[num].right, ra[num].bottom);
					SelectObject(mdc, oldBrush);
					DeleteObject(hBrush);
					if (num < 18) {
						num++;
					}
				}
			}
		}
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_GRID_DOT:
			pen = 1;
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_GRID_SOLID:
			pen = 0;
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_COLOR_RED:
			re[t].r = 255;
			re[t].g = 0;
			re[t].b = 0;
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_COLOR_YELLOW40019:
			re[t].r = 255;
			re[t].g = 255;
			re[t].b = 0;
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_COLOR_ORANGE:
			re[t].r = 255;
			re[t].g = 127;
			re[t].b = 0;
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_COLOR_GREEN40021:
			re[t].r = 0;
			re[t].g = 255;
			re[t].b = 0;
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_COLOR_BLUE:
			re[t].r = 0;
			re[t].g = 0;
			re[t].b = 255;
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_COLOR_PURPLE40023:
			r = 255;
			g = 0;
			b = 255;
			re[t].r = 255;
			re[t].g = 0;
			re[t].b = 255;
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_BORDER_ON:
			th = 1;
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_BORDER_OFF:
			th = 0;
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		oldX = startX = mx = LOWORD(lParam);
		oldY = startY = my = HIWORD(lParam);
		if (t > 4) {
			t = 0;
		}
		v = mx / 20;
		re[t].x = 0 + 20 * v;
		v = my / 20;
		re[t].y = 0 + 20 * v;
		Drag = TRUE;
		l = 0; j = 0;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		v = mx / 20;
		re[t].x1 = 20 + 20 * v;
		v = my / 20;
		re[t].y1 = 20 + 20 * v;
		re[t].ner = re[t].x1 - re[t].x;
		re[t].nop = re[t].y1 - re[t].y;
		re[t].rd.left = re[t].x;
		re[t].rd.top = re[t].y;
		re[t].rd.right = re[t].x1;
		re[t].rd.bottom = re[t].y1;
		t++;
		Drag = FALSE;
		l = 0; j = 0;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		hdc = GetDC(hwnd);
		if (Drag) {
			SetROP2(hdc, R2_BLACK);
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
			SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);
			Rectangle(hdc, re[t].x, re[t].y, oldX, oldY);
			Rectangle(hdc, re[t].x, re[t].y, endX, endY);
			oldX = endX; oldY = endY;
		}
		if (Drag1) {
			mx1 = LOWORD(lParam);
			my1 = HIWORD(lParam);
			if (re[p].mx < mx1) {
				if (re[p].my < my1) {
					re[p].y += 5;
					re[p].y1 += 5;
					if (re[p].y1 > 800) {
						re[p].y -= 5;
						re[p].y1 -= 5;
					}
					re[p].x += 5;
					re[p].x1 += 5;
					if (re[p].x1 > 800) {
						re[p].x -= 5;
						re[p].x1 -= 5;
					}
				}
				else if (re[p].my == my1) {
					re[p].x += 5;
					re[p].x1 += 5;
					if (re[p].x1 > 800) {
						re[p].x -= 5;
						re[p].x1 -= 5;
					}
				}
				else {
					re[p].x += 5;
					re[p].x1 += 5;
					if (re[p].x1 > 800) {
						re[p].x -= 5;
						re[p].x1 -= 5;
					}
					re[p].y -= 5;
					re[p].y1 -= 5;
					if (re[p].y < 0) {
						re[p].y += 5;
						re[p].y1 += 5;
					}
				}
			}
			if (re[p].mx > mx1) {
				if (re[p].my < my1) {
					re[p].y += 5;
					re[p].y1 += 5;
					if (re[p].y1 > 800) {
						re[p].y -= 5;
						re[p].y1 -= 5;
					}
					re[p].x -= 5;
					re[p].x1 -= 5;
					if (re[p].x < 0) {
						re[p].x += 5;
						re[p].x1 += 5;
					}
				}
				else if (re[p].my == my1) {
					re[p].x -= 5;
					re[p].x1 -= 5;
					if (re[p].x < 0) {
						re[p].x += 5;
						re[p].x1 += 5;
					}
				}
				else {
					re[p].x -= 5;
					re[p].x1 -= 5;
					if (re[p].x < 0) {
						re[p].x += 5;
						re[p].x1 += 5;
					}
					re[p].y -= 5;
					re[p].y1 -= 5;
					if (re[p].y < 0) {
						re[p].y += 5;
						re[p].y1 += 5;
					}
				}
			}
			if (re[p].mx == mx1) {
				if (re[p].my < my1) {
					re[p].y += 5;
					re[p].y1 += 5;
					if (re[p].y1 > 800) {
						re[p].y -= 5;
						re[p].y1 -= 5;
					}
				}
				else {
					re[p].y -= 5;
					re[p].y1 -= 5;
					if (re[p].y < 0) {
						re[p].y += 5;
						re[p].y1 += 5;
					}
				}
			}
			re[p].mx = mx1;
			re[p].my = my1;
			InvalidateRect(hwnd, NULL, FALSE);
			l = 0; j = 0;
			break;
		}
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, FALSE);
		l = 0; j = 0;
		break;
	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		for (int i = 0; i < t; i++) {
			if (re[i].x <= mx && mx <= re[i].x1) {
				if (re[i].y <= my && my <= re[i].y1) {
					p = i;
					re[p].mx = my;
					re[p].my = my;
				}
			}
		}
		Drag1 = TRUE;
		l = 0; j = 0;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_RBUTTONUP:
		v = re[p].x / 20;
		v1 = re[p].y / 20;
		re[p].x = 0 + 20 * v;
		re[p].y = 0 + 20 * v1;
		re[p].x1 = re[p].x + re[p].ner;
		re[p].y1 = re[p].y + re[p].nop;
		Drag1 = FALSE;
		l = 0; j = 0;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == '1') {
			p = 1 - 1; j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == '2') {
			p = 2 - 1; j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == '3') {
			p = 3 - 1; j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == '4') {
			p = 4 - 1; j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == '5') {
			p = 5 - 1; j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_UP) {
			re[p].y -= 20;
			re[p].y1 -= 20;
			if (re[p].y < 0) {
				re[p].y += 20;
				re[p].y1 += 20;
			}
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_DOWN) {
			re[p].y += 20;
			re[p].y1 += 20;
			if (re[p].y1 > 800) {
				re[p].y -= 20;
				re[p].y1 -= 20;
			}
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_LEFT) {
			re[p].x -= 20;
			re[p].x1 -= 20;
			if (re[p].x < 0) {
				re[p].x += 20;
				re[p].x1 += 20;
			}
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_RIGHT) {
			re[p].x += 20;
			re[p].x1 += 20;
			if (re[p].x1 > 800) {
				re[p].x -= 20;
				re[p].x1 -= 20;
			}
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
