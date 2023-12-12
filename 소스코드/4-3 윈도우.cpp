#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<string.h>
#define _USE_MATH_DEFINES
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU3);
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 900, 700, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
struct one {
	int x = 0;
	int y = 0;
	int size = 5;
	int r = 255, g = 255, b = 0;
	int lx = 0, ly = 0;
	int l2x = 0, l2y = 0;
	int l3x = 0, l3y = 0;
	int l4x = 0, l4y = 0;
	int lx1 = 0, ly1 = 0;
	int lx2 = 0, ly2 = 0;
	int lx3 = 0, ly3 = 0;
	int lx4 = 0, ly4 = 0;
	double angle = 0;
	int move = 0;
};
struct one on[100];
struct one we[100];
float LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
BOOL InCircle(int x1, int y1, int x2, int y2, int r) {
	if (LengthPts(x1, y1, x2, y2) < r)
		return TRUE;
	else
		return FALSE;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	static BOOL Selection;
	int mx, my;
	static int t = 10;
	static int ran = 0;
	static int cn = 0;
	static int cg = 0;
	static int sf = 0;
	static int t2 = 0;
	switch (iMsg) {
	case WM_CREATE:
		cn = 0;
		cg = 0;
		for (int i = 0; i < 10; i++) {
			on[i].x = rand() % 600 + 100;
			on[i].y = rand() % 500 + 100;
			on[i].size = rand() % 80 + 10;
			on[i].r = rand() % 255;
			on[i].g = rand() % 255;
			on[i].b = rand() % 255;
			on[i].lx = on[i].x + on[i].size * sin(on[i].angle);
			on[i].ly = on[i].y + on[i].size * cos(on[i].angle);
			on[i].lx1 = on[i].x + on[i].size * sin(on[i].angle + M_PI);
			on[i].ly1 = on[i].y + on[i].size * cos(on[i].angle + M_PI);
			on[i].l2y = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 1 / 4));
			on[i].ly2 = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 3 / 4));
			on[i].lx2 = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 3 / 4));
			on[i].l2x = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 1 / 4));
			on[i].l3y = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 1 / 2));
			on[i].l3x = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 1 / 2));
			on[i].ly3 = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 1 / 2));
			on[i].lx3 = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 1 / 2));
			on[i].l4y = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 1 / 4));
			on[i].l4x = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 1 / 4));
			on[i].ly4 = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 3 / 4));
			on[i].lx4 = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 3 / 4));
			we[i].x = on[i].x + (on[i].size + 2.5) * sin(we[i].angle + M_PI + (M_PI * 1 / 4));
			we[i].y = on[i].y + (on[i].size + 2.5) * cos(we[i].angle + M_PI + (M_PI * 1 / 4));
		}
		Selection = FALSE;
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		Rectangle(mdc, 0, 0, rt.right, rt.bottom);
		for (int i = 0; i < t; i++) {
			hBrush = CreateSolidBrush(RGB(on[i].r, on[i].g, on[i].b));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, on[i].x - on[i].size, on[i].y - on[i].size, on[i].x + on[i].size, on[i].y + on[i].size);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
			hBrush = CreateSolidBrush(RGB(we[i].r, we[i].g, we[i].b));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, we[i].x - we[i].size, we[i].y - we[i].size, we[i].x + we[i].size, we[i].y + we[i].size);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
			hPen = CreatePen(PS_SOLID, 10, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(mdc, on[i].lx, on[i].ly, NULL);
			LineTo(mdc, on[i].lx1, on[i].ly1);
			MoveToEx(mdc, on[i].l2x, on[i].l2y, NULL);
			LineTo(mdc, on[i].lx2, on[i].ly2);
			MoveToEx(mdc, on[i].l3x, on[i].l3y, NULL);
			LineTo(mdc, on[i].lx3, on[i].ly3);
			MoveToEx(mdc, on[i].l4x, on[i].l4y, NULL);
			LineTo(mdc, on[i].lx4, on[i].ly4);
			SelectObject(mdc, oldPen);
			DeleteObject(hPen);
		}
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
			case ID_MOVE_1:
				for (int i = 0; i < t;i++) {
					on[i].move = 0;
				}
				SetTimer(hwnd, 1, 100, NULL);
				cg = 1;
				KillTimer(hwnd, 2);
				KillTimer(hwnd, 3);
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			case ID_MOVE_2:
				cg = 2;
				for (int i = 0; i < t;i++) {
					on[i].move = 0;
				}
				SetTimer(hwnd, 2, 100, NULL);
				KillTimer(hwnd, 1);
				KillTimer(hwnd, 3);
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			case ID_MOVE_3:
				for (int i = 0; i < t;i++) {
					on[i].move = 0;
				}
				if (cn % 2 == 0) {
					KillTimer(hwnd, 1);
					KillTimer(hwnd, 2);
				}
				else if (cn % 2 == 1) {
					if (cg == 1) {
						SetTimer(hwnd, 1, 100, NULL);
					}
					else if (cg == 2) {
						SetTimer(hwnd, 2, 100, NULL);
					}
				}
				cn++;
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			case ID_CHANGE_C:
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			case ID_CHANGE_RED:
				for (int i = 0; i < t; i++) {
					on[i].r = 255;
					on[i].g = 0;
					on[i].b = 0;
				}
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			case ID_CHANGE_RANDOM:
				for (int i = 0; i < t; i++) {
					on[i].r = rand() % 255;
					on[i].g = rand() % 255;
					on[i].b = rand() % 255;
				}
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			case ID_CHANGE_GREEN:
				for (int i = 0; i < t; i++) {
					on[i].r = 0;
					on[i].g = 255;
					on[i].b = 0;
				}
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			case ID_CHANGE_BLUE:
				for (int i = 0; i < t; i++) {
					on[i].r = 0;
					on[i].g = 0;
					on[i].b = 255;
				}
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			case ID_GAME_RESET40044:
				t = 10;
				for (int i = 0; i < 10; i++) {
					on[i].x = rand() % 600 + 100;
					on[i].y = rand() % 500 + 100;
					on[i].size = rand() % 80 + 10;
					on[i].r = rand() % 255;
					on[i].g = rand() % 255;
					on[i].b = rand() % 255;
					on[i].lx = on[i].x + on[i].size * sin(on[i].angle);
					on[i].ly = on[i].y + on[i].size * cos(on[i].angle);
					on[i].lx1 = on[i].x + on[i].size * sin(on[i].angle + M_PI);
					on[i].ly1 = on[i].y + on[i].size * cos(on[i].angle + M_PI);
					on[i].l2y = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 1 / 4));
					on[i].ly2 = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 3 / 4));
					on[i].lx2 = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 3 / 4));
					on[i].l2x = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 1 / 4));
					on[i].l3y = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 1 / 2));
					on[i].l3x = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 1 / 2));
					on[i].ly3 = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 1 / 2));
					on[i].lx3 = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 1 / 2));
					on[i].l4y = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 1 / 4));
					on[i].l4x = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 1 / 4));
					on[i].ly4 = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 3 / 4));
					on[i].lx4 = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 3 / 4));
					we[i].x = on[i].x + (on[i].size + 2.5) * sin(we[i].angle + M_PI + (M_PI * 1 / 4));
					we[i].y = on[i].y + (on[i].size + 2.5) * cos(we[i].angle + M_PI + (M_PI * 1 / 4));
				}
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			case ID_GAME_QUIT:
				KillTimer(hwnd, 1);
				KillTimer(hwnd, 2);
				PostQuitMessage(0);
				break;
			}
			break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		for (int i = 0; i < t; i++) {
			if (InCircle(on[i].x, on[i].y, mx, my, on[i].size)) {
				on[i].move++;
				t2++;
				break;
			}
		}
		if (t2==0) {
			on[t].x = mx;
			on[t].y = my;
			on[t].size = rand() % 80 + 10;
			on[t].r = rand() % 255;
			on[t].g = rand() % 255;
			on[t].b = rand() % 255;
			on[t].lx = on[t].x + on[t].size * sin(on[t].angle);
			on[t].ly = on[t].y + on[t].size * cos(on[t].angle);
			on[t].lx1 = on[t].x + on[t].size * sin(on[t].angle + M_PI);
			on[t].ly1 = on[t].y + on[t].size * cos(on[t].angle + M_PI);
			on[t].l2y = on[t].y + on[t].size * cos(on[t].angle + M_PI + (M_PI * 1 / 4));
			on[t].ly2 = on[t].y + on[t].size * cos(on[t].angle + M_PI - (M_PI * 3 / 4));
			on[t].lx2 = on[t].x + on[t].size * sin(on[t].angle + M_PI - (M_PI * 3 / 4));
			on[t].l2x = on[t].x + on[t].size * sin(on[t].angle + M_PI + (M_PI * 1 / 4));
			on[t].l3y = on[t].y + on[t].size * cos(on[t].angle + M_PI - (M_PI * 1 / 2));
			on[t].l3x = on[t].x + on[t].size * sin(on[t].angle + M_PI - (M_PI * 1 / 2));
			on[t].ly3 = on[t].y + on[t].size * cos(on[t].angle + M_PI + (M_PI * 1 / 2));
			on[t].lx3 = on[t].x + on[t].size * sin(on[t].angle + M_PI + (M_PI * 1 / 2));
			on[t].l4y = on[t].y + on[t].size * cos(on[t].angle + M_PI - (M_PI * 1 / 4));
			on[t].l4x = on[t].x + on[t].size * sin(on[t].angle + M_PI - (M_PI * 1 / 4));
			on[t].ly4 = on[t].y + on[t].size * cos(on[t].angle + M_PI + (M_PI * 3 / 4));
			on[t].lx4 = on[t].x + on[t].size * sin(on[t].angle + M_PI + (M_PI * 3 / 4));
			we[t].x = on[t].x + (on[t].size + 2.5) * sin(we[t].angle + M_PI + (M_PI * 1 / 4));
			we[t].y = on[t].y + (on[t].size + 2.5) * cos(we[t].angle + M_PI + (M_PI * 1 / 4));
			t++;
		}
		t2 = 0;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			cg = 1;
			for (int i = 0; i < t; i++) {
				if (on[i].move == 0) {
					on[i].angle += (M_PI / 180);
					we[i].angle -= (M_PI / 180);
				}
				else {
					on[i].angle -= (M_PI / 180);
					we[i].angle += (M_PI / 180);
				}
				on[i].lx = on[i].x + on[i].size * sin(on[i].angle);
				on[i].ly = on[i].y + on[i].size * cos(on[i].angle);
				on[i].lx1 = on[i].x + on[i].size * sin(on[i].angle + M_PI);
				on[i].ly1 = on[i].y + on[i].size * cos(on[i].angle + M_PI);
				on[i].l2y = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 1 / 4));
				on[i].ly2 = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 3 / 4));
				on[i].lx2 = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 3 / 4));
				on[i].l2x = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 1 / 4));
				on[i].l3y = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 1 / 2));
				on[i].l3x = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 1 / 2));
				on[i].ly3 = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 1 / 2));
				on[i].lx3 = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 1 / 2));
				on[i].l4y = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 1 / 4));
				on[i].l4x = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 1 / 4));
				on[i].ly4 = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 3 / 4));
				on[i].lx4 = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 3 / 4));
				we[i].x = on[i].x + (on[i].size + 2.5) * sin(we[i].angle + M_PI + (M_PI * 1 / 4));
				we[i].y = on[i].y + (on[i].size + 2.5) * cos(we[i].angle + M_PI + (M_PI * 1 / 4));
			}
			break;
		case 2:
			cg = 2;
			for (int i = 0; i < t; i++) {
				if (on[i].move == 0) {
					on[i].angle -= (M_PI / 180);
					we[i].angle += (M_PI / 180);
				}
				else {
					on[i].angle += (M_PI / 180);
					we[i].angle -= (M_PI / 180);
				}
				on[i].lx = on[i].x + on[i].size * sin(on[i].angle);
				on[i].ly = on[i].y + on[i].size * cos(on[i].angle);
				on[i].lx1 = on[i].x + on[i].size * sin(on[i].angle + M_PI);
				on[i].ly1 = on[i].y + on[i].size * cos(on[i].angle + M_PI);
				on[i].l2y = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 1 / 4));
				on[i].ly2 = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 3 / 4));
				on[i].lx2 = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 3 / 4));
				on[i].l2x = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 1 / 4));
				on[i].l3y = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 1 / 2));
				on[i].l3x = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 1 / 2));
				on[i].ly3 = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 1 / 2));
				on[i].lx3 = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 1 / 2));
				on[i].l4y = on[i].y + on[i].size * cos(on[i].angle + M_PI - (M_PI * 1 / 4));
				on[i].l4x = on[i].x + on[i].size * sin(on[i].angle + M_PI - (M_PI * 1 / 4));
				on[i].ly4 = on[i].y + on[i].size * cos(on[i].angle + M_PI + (M_PI * 3 / 4));
				on[i].lx4 = on[i].x + on[i].size * sin(on[i].angle + M_PI + (M_PI * 3 / 4));
				we[i].x = on[i].x + (on[i].size + 2.5) * sin(we[i].angle + M_PI + (M_PI * 1 / 4));
				we[i].y = on[i].y + (on[i].size + 2.5) * cos(we[i].angle + M_PI + (M_PI * 1 / 4));
			}
			break;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		KillTimer(hwnd, 2);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
