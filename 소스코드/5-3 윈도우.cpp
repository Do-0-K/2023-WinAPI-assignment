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
struct rect {
	int x = -100;
	int y = -100;
	int x1 = -100;
	int y1 = -100;
	int mx = 0, my = 0;
};
struct rect re[1];
struct rect ra[5];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	static BOOL Selection;
	static BOOL Drag1;
	static HBITMAP hbitmap1;
	static HBITMAP hbitmap2;
	static RECT rectView;
	int mx = 0, my = 0;
	int mx1 = 0, my1 = 0;
	static int chose = 0;
	static int t = 1;
	static int startX, startY, oldX, oldY;
	int endX, endY;
	static int a = 0;
	static int b = 0;
	static int x = 0, y = 0, x1 = 0, y1 = 0;
	static int cng = 0, cng1 = 0;
	static int m = 0, ma = 0,full = 0;
	static int banjun = 0;
	switch (iMsg) {
	case WM_CREATE:
		Selection = FALSE;
		Drag1 = FALSE;
		startX = oldX = 0;
		startY = oldY = 0;
		GetClientRect(hwnd, &rectView);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		Rectangle(mdc, 0, 0, 780, 610);
		if (chose == 1) {
			hbitmap1 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
			memdc = CreateCompatibleDC(hdc);
			SelectObject(memdc, (HBITMAP)hbitmap1);
			StretchBlt(mdc, 0, 0, 780, 610, memdc, 0, 0, 300, 300, SRCCOPY);
			hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(mdc, hPen);
			MoveToEx(mdc, re[0].x, re[0].y, NULL);
			LineTo(mdc, re[0].x1, re[0].y);
			MoveToEx(mdc, re[0].x1, re[0].y, NULL);
			LineTo(mdc, re[0].x1, re[0].y1);
			MoveToEx(mdc, re[0].x, re[0].y1, NULL);
			LineTo(mdc, re[0].x1, re[0].y1);
			MoveToEx(mdc, re[0].x, re[0].y, NULL);
			LineTo(mdc, re[0].x, re[0].y1);
			SelectObject(mdc, oldPen);
			DeleteObject(hPen);
			StretchBlt(mdc, re[0].x, re[0].y, re[0].x1-re[0].x, re[0].y1-re[0].y, mdc, re[0].x, re[0].y, re[0].x1 - re[0].x+m, re[0].y1 - re[0].y+m, SRCCOPY);
			if (ma%2== 1) {
				for (int i = 1; i <= t; i++) {
					if (banjun == 0) {
						StretchBlt(mdc, ra[i].x, ra[i].y, ra[i].x1 - ra[i].x, ra[i].y1 - ra[i].y, mdc, re[0].x, re[0].y, re[0].x1 - re[0].x + m, re[0].y1 - re[0].y + m, SRCCOPY);
					}
					if (banjun == 1) {
						StretchBlt(mdc, ra[i].x1, ra[i].y, -(ra[i].x1 - ra[i].x), ra[i].y1 - ra[i].y, mdc, re[0].x, re[0].y, re[0].x1 - re[0].x + m, re[0].y1 - re[0].y + m, SRCCOPY);
					}
					if (banjun == 2) {
						StretchBlt(mdc, ra[i].x, ra[i].y1, ra[i].x1 - ra[i].x, -(ra[i].y1 - ra[i].y), mdc, re[0].x, re[0].y, re[0].x1 - re[0].x + m, re[0].y1 - re[0].y + m, SRCCOPY);
					}
				}
			}
			if (full == 1) {
				StretchBlt(mdc, 0, 0, 780, 610, mdc, re[0].x, re[0].y, re[0].x1 - re[0].x + m, re[0].y1 - re[0].y + m, SRCCOPY);
			}
			DeleteDC(memdc);
		}
		else if (chose == 2) {
			hbitmap2 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
			memdc = CreateCompatibleDC(mdc);
			SelectObject(memdc, (HBITMAP)hbitmap2);
			StretchBlt(mdc, 0, 0, 780, 610, memdc, 0, 0, 650, 400, SRCCOPY);
			hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(mdc, hPen);
			MoveToEx(mdc, re[0].x, re[0].y, NULL);
			LineTo(mdc, re[0].x1, re[0].y);
			MoveToEx(mdc, re[0].x1, re[0].y, NULL);
			LineTo(mdc, re[0].x1, re[0].y1);
			MoveToEx(mdc, re[0].x, re[0].y1, NULL);
			LineTo(mdc, re[0].x1, re[0].y1);
			MoveToEx(mdc, re[0].x, re[0].y, NULL);
			LineTo(mdc, re[0].x, re[0].y1);
			SelectObject(mdc, oldPen);
			DeleteObject(hPen);
			for (int i = 1; i <= t; i++) {
				
			}
			DeleteDC(memdc);
		}
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		oldX = startX = mx = LOWORD(lParam);
		oldY = startY = my = HIWORD(lParam);
		re[0].x = mx;
		re[0].y = my;
		re[0].x1 = mx;
		re[0].y1 = my;
		Selection = TRUE;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		re[0].x1 = mx;
		re[0].y1 = my;
		Selection = FALSE;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		hdc = GetDC(hwnd);
		if (Selection) {
			SetROP2(hdc, R2_MASKPEN);
			SelectObject(hdc, (HPEN)GetStockObject(BLACK_PEN));
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);
			Rectangle(hdc, re[0].x, re[0].y, oldX, oldY);
			Rectangle(hdc, re[0].x, re[0].y, endX, endY);
			oldX = endX; oldY = endY;
		}
		if (Drag1) {
			mx1 = LOWORD(lParam);
			my1 = HIWORD(lParam);
			if (re[0].mx < mx1) {
				if (re[0].my < my1) {
					re[0].y += 2;
					re[0].y1 += 2;
					if (re[0].y1 > 610) {
						re[0].y -= 2;
						re[0].y1 -= 2;
					}
					re[0].x += 2;
					re[0].x1 += 2;
					if (re[0].x1 > 780) {
						re[0].x -= 2;
						re[0].x1 -= 2;
					}
				}
				else if (re[0].my == my1) {
					re[0].x += 2;
					re[0].x1 += 2;
					if (re[0].x1 > 780) {
						re[0].x -= 2;
						re[0].x1 -= 2;
					}
				}
				else {
					re[0].x += 2;
					re[0].x1 += 2;
					if (re[0].x1 > 780) {
						re[0].x -= 2;
						re[0].x1 -= 2;
					}
					re[0].y -= 2;
					re[0].y1 -= 2;
					if (re[0].y < 0) {
						re[0].y += 2;
						re[0].y1 += 2;
					}
				}
			}
			if (re[0].mx > mx1) {
				if (re[0].my < my1) {
					re[0].y += 2;
					re[0].y1 += 2;
					if (re[0].y1 > 610) {
						re[0].y -= 2;
						re[0].y1 -= 2;
					}
					re[0].x -= 2;
					re[0].x1 -= 2;
					if (re[0].x < 0) {
						re[0].x += 2;
						re[0].x1 += 2;
					}
				}
				else if (re[0].my == my1) {
					re[0].x -= 2;
					re[0].x1 -= 2;
					if (re[0].x < 0) {
						re[0].x += 2;
						re[0].x1 += 2;
					}
				}
				else {
					re[0].x -= 2;
					re[0].x1 -= 2;
					if (re[0].x < 0) {
						re[0].x += 2;
						re[0].x1 += 2;
					}
					re[0].y -= 2;
					re[0].y1 -= 2;
					if (re[0].y < 0) {
						re[0].y += 2;
						re[0].y1 += 2;
					}
				}
			}
			if (re[0].mx == mx1) {
				if (re[0].my < my1) {
					re[0].y += 2;
					re[0].y1 += 2;
					if (re[0].y1 > 610) {
						re[0].y -= 2;
						re[0].y1 -= 2;
					}
				}
				else {
					re[0].y -= 2;
					re[0].y1 -= 2;
					if (re[0].y < 0) {
						re[0].y += 2;
						re[0].y1 += 2;
					}
				}
			}
			re[0].mx = mx1;
			re[0].my = my1;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (re[0].x <= mx && mx <= re[0].x1) {
			if (re[0].y <= my && my <= re[0].y1) {
				re[0].mx = my;
				re[0].my = my;
			}
		}
		Drag1 = TRUE;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_RBUTTONUP:
		Drag1 = FALSE;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == VK_LEFT) {
			re[0].x -= 2;
			re[0].x1 -= 2;
			if (re[0].x < 0) {
				re[0].x += 2;
				re[0].x1 += 2;
			}
		}
		if (wParam == VK_RIGHT) {
			re[0].x += 2;
			re[0].x1 += 2;
			if (re[0].x1 > 780) {
				re[0].x -= 2;
				re[0].x1 -= 2;
			}
		}
		if (wParam == VK_UP) {
			re[0].y -= 2;
			re[0].y1 -= 2;
			if (re[0].y < 0) {
				re[0].y += 2;
				re[0].y1 += 2;
			}
		}
		if (wParam == VK_DOWN) {
			re[0].y += 2;
			re[0].y1 += 2;
			if (re[0].y1 > 610) {
				re[0].y -= 2;
				re[0].y1 -= 2;
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == 'h' || wParam == 'H') {
			if (banjun == 0) {
				banjun++;
			}
			else {
				banjun = 0;
			}
		}
		if (wParam == 'V' || wParam == 'v') {
			if (banjun == 0) {
				banjun=2;
			}
			else {
				banjun = 0;
			}
		}
		if (wParam == 'e' || wParam == 'E') {
			m -= 10;
			if (m == -100) {
				m = 0;
			}
		}
		if (wParam == 's' || wParam == 'S') {
			m += 10;
			if (m == 100) {
				m = 0;
			}
		}
		if (wParam == '0') {
			m = 0;
		}
		if (wParam == 'c' || wParam == 'C') {
			if (ma % 2 == 0) {
				for (int i = 1;i < t;i++) {
					re[i].x = -100;
					re[i].y = -100;
					re[i].x1 = -100;
					re[i].y1 = -100;
				}
				t = 1;
			}
			ma++;
		}
		if (wParam == 'p' || wParam == 'P') {
			if (ma % 2 == 1) {
				ra[t].x = rand() % 500;
				ra[t].y = rand() % 500;
				ra[t].x1 = ra[t].x + (re[0].x1 - re[0].x);
				ra[t].y1 = ra[t].y + (re[0].y1 - re[0].y);
				t++;
				if (t > 5) {
					for (int i = 1;i < t;i++) {
						re[i].x = -100;
						re[i].y = -100;
						re[i].x1 = -100;
						re[i].y1 = -100;
					}
					t = 1;
				}
			}
		}
		if (wParam == 'f' || wParam == 'F') {
			if (full == 0) {
				full++;
			}
			else {
				full = 0;
			}
		}
		if (wParam == 'r' || wParam == 'R') {
			t = 1;
			re[0].x = -100;
			re[0].y = -100;
			re[0].x1 = -100;
			re[0].y1 = -100;
		}
		if (wParam == '1') {
			chose = 1;
			t = 1;
			re[0].x = -100;
			re[0].y = -100;
			re[0].x1 = -100;
			re[0].y1 = -100;
		}
		if (wParam == '2') {
			chose = 2;
			t = 1;
			re[0].x = -100;
			re[0].y = -100;
			re[0].x1 = -100;
			re[0].y1 = -100;
		}
		if (wParam == 'm' || wParam == 'M') {
			re[0].x -= 2;
			re[0].y -= 2;
			re[0].x1 += 2;
			re[0].y1 += 2;
		}
		if (wParam == 'n' || wParam == 'N') {
			re[0].x += 2;
			re[0].y += 2;
			re[0].x1 -= 2;
			re[0].y1 -= 2;
		}
		if (wParam == 'x') {
			re[0].x += 2;
			re[0].x1 -= 2;
		}
		if (wParam == 'X') {
			re[0].x -= 2;
			re[0].x1 += 2;
		}
		if (wParam == 'y') {
			re[0].y += 2;
			re[0].y1 -= 2;
		}
		if (wParam == 'Y') {
			re[0].y -= 2;
			re[0].y1 += 2;
		}
		if (wParam == 'a' || wParam == 'A') {
			if (a%2 == 0) {
				SetTimer(hwnd, 1, 50, NULL);
			}
			if (a%2 != 0) {
				KillTimer(hwnd, 1);
			}
			a++;
		}
		if (wParam == 'b' || wParam == 'B') {
			if (b%2 == 0) {
				x = re[0].x;
				y = re[0].y;
				x1 = re[0].x1;
				y1 = re[0].y1;
				SetTimer(hwnd, 2, 50, NULL);
			}
			if (b%2 != 0) {
				KillTimer(hwnd, 2);
				re[0].x = x;
				re[0].y = y;
				re[0].x1 = x1;
				re[0].y1 = y1;
			}
			b++;
		}
		if (wParam == 'Q' || wParam == 'q') {
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			DeleteObject(hbitmap1);
			DeleteObject(hbitmap2);
			PostQuitMessage(0);
		}
		InvalidateRect(hwnd, NULL, FALSE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			if (cng % 2 == 0) {
				re[0].x += 5;
				re[0].x1 += 5;
			}
			if (cng % 2 == 1) {
				re[0].x -= 5;
				re[0].x1 -= 5;
			}
			if (re[0].x < 1) {
				re[0].y += 100;
				re[0].y1 += 100;
				cng++;
			}
			if (re[0].x1 > 778) {
				re[0].y += 100;
				re[0].y1 += 100;
				cng++;
			}
			break;
		case 2:
			if (cng1 % 2 == 0) {
				re[0].x -= 5;
				re[0].x1 += 5;
				re[0].y -= 5;
				re[0].y1 += 5;
			}
			if (cng1 % 2 == 1) {
				re[0].x += 5;
				re[0].x1 -= 5;
				re[0].y += 5;
				re[0].y1 -= 5;
			}
			if (re[0].x < 1) {
				cng1++;
			}
			if (re[0].x1 > 778) {
				cng1++;
			}
			if (re[0].y1 > 605) {
				cng1++;
			}
			if (re[0].y < 2) {
				cng1++;
			}
			if (re[0].x+20 == re[0].x1) {
				cng1++;
			}
			if (re[0].y+20 == re[0].y1) {
				cng1++;
			}
			break;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		KillTimer(hwnd, 2);
		DeleteObject(hbitmap1);
		DeleteObject(hbitmap2);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}