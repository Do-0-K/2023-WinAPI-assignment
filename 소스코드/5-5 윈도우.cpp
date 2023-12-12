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
	int x = -100, y = -20;
	int speed = 0;
	int x1 = -100, y1 = -100;
	int st = 0;
};
struct rect r[30];
struct ject {
	int x = -100, y = -100;
	int speed = 0;
	int x1 = -100, y1 = -100;
	int mx = 0, my = 0;
};
struct ject re[1];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc, memdc, kdc;
	HPEN hPen, oldPen;
	PAINTSTRUCT ps;
	static HBITMAP hbitmap[4];
	static HBITMAP oldbit[3];
	static HBITMAP backhbit{};
	static HBITMAP hbit{};
	static RECT rt{};
	static int cnt;
	int mx = 0, my = 0;
	static BOOL Selection;
	static BOOL drag;
	static int startX = 0, startY = 0, oldX = 0, oldY = 0;
	int endX = 0, endY = 0;
	static int t = 0;
	static int w = 0;
	int mx1 = 0, my1 = 0;
	static int tempx = 0, tempy = 0, tempx1 = 0, tempy1 = 0;
	switch (iMsg) {
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rt);
		backhbit = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7));
		hbitmap[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		hbitmap[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		hbitmap[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
		hbitmap[3] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
		hbit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SetTimer(hwnd, 1, 200, NULL);
		for (int i = 0;i < 20;i++) {
			r[i].x = rand() % (rt.right - 80);
		}
		Selection = FALSE;
		drag = FALSE;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		oldbit[0] = (HBITMAP)SelectObject(memdc, hbit); //--- hBit: 이미지가 저장되어 있는 비트맵 전역 변수
		StretchBlt(hdc, 0, 0, rt.right, rt.bottom, memdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
		SelectObject(memdc, oldbit[0]);
		DeleteDC(memdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			hdc = GetDC(hwnd);
			memdc = CreateCompatibleDC(hdc); //--- 더블 버퍼로 사용 할 메모리 DC 생성
			kdc = CreateCompatibleDC(memdc); //--- 이미지를 저장 할 메모리 DC 생성
			oldbit[0] = (HBITMAP)SelectObject(memdc, hbit); //--- MemDC와 hBit 를 호환되게 선택함
			oldbit[1] = (HBITMAP)SelectObject(kdc, backhbit); //--- 배경 이미지
			StretchBlt(memdc, 0, 0, rt.right, rt.bottom, kdc, 0, 0, 500, 500, SRCCOPY);
			oldbit[2] = (HBITMAP)SelectObject(kdc, hbitmap[cnt]); //--- 애니메이션 이미지
			for (int i = 0;i < 30;i++) {
				TransparentBlt(memdc, r[i].x, r[i].y, 80, 80, kdc, 0, 0, 300, 300, RGB(255, 255, 255));
			}
			//--- MemDC에 배경과 애니메이션 저장  hBit 비트맵에 저장
			cnt++; //--- 애니메이션 이미지 순서
			if (cnt >= 3) {
				cnt = 0;
			}
			if (t == 0) {
				hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				oldPen = (HPEN)SelectObject(memdc, hPen);
				MoveToEx(memdc, re[0].x, re[0].y, NULL);
				LineTo(memdc, re[0].x1, re[0].y);
				MoveToEx(memdc, re[0].x1, re[0].y, NULL);
				LineTo(memdc, re[0].x1, re[0].y1);
				MoveToEx(memdc, re[0].x, re[0].y1, NULL);
				LineTo(memdc, re[0].x1, re[0].y1);
				MoveToEx(memdc, re[0].x, re[0].y, NULL);
				LineTo(memdc, re[0].x, re[0].y1);
				SelectObject(memdc, oldPen);
				DeleteObject(hPen);
			}
			DeleteDC(memdc);
			DeleteObject(kdc);
			ReleaseDC(hwnd, hdc);
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 2:
			for (int i = 0;i < 20;i++) {
				r[i].y += r[i].speed;
				if (r[i].y >= 570) {
					r[i].y = 0;
				}
				if (re[0].x < r[i].x && r[i].x + 80 < re[0].x1) {
					if (re[0].y1 >= r[i].y + 80 && r[i].y + 80 > re[0].y1 - 40) {
						r[i].y -= r[i].speed;
						r[i].st = 1;
					}
				}
			}
			break;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:
		oldX = startX = mx = LOWORD(lParam);
		oldY = startY = my = HIWORD(lParam);
		if (w == 0) {
			re[0].x = mx;
			re[0].y = my;
			re[0].x1 = mx;
			re[0].y1 = my;
			Selection = TRUE;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (w == 0) {
			re[0].x1 = mx;
			re[0].y1 = my;
			Selection = FALSE;
		}
		w++;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		re[0].mx = my;
		re[0].my = my;
		drag = TRUE;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_RBUTTONUP:
		drag = FALSE;
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
		if (drag) {
			mx1 = LOWORD(lParam);
			my1 = HIWORD(lParam);
			if (re[0].mx < mx1) {
				if (re[0].my < my1) {
					re[0].y += 2;
					re[0].y1 += 2;
					if (re[0].y1 > 800) {
						re[0].y -= 2;
						re[0].y1 -= 2;
					}
					re[0].x +=2;
					re[0].x1 += 2;
					if (re[0].x1 > 800) {
						re[0].x -= 2;
						re[0].x1 -= 2;
					}
					for (int i = 0;i < 20;i++) {
						if (r[i].st == 1) {
							r[i].x += 2;
							r[i].y += 2;
						}
					}
				}
				else if (re[0].my == my1) {
					re[0].x += 2;
					re[0].x1 += 2;
					if (re[0].x1 > 800) {
						re[0].x -= 2;
						re[0].x1 -= 2;
					}
					for (int i = 0;i < 20;i++) {
						if (r[i].st == 1) {
							r[i].x += 2;
						}
					}
				}
				else {
					re[0].x += 2;
					re[0].x1 += 2;
					if (re[0].x1 > 800) {
						re[0].x -= 2;
						re[0].x1 -= 2;
					}
					re[0].y -= 2;
					re[0].y1 -=2;
					if (re[0].y < 0) {
						re[0].y += 2;
						re[0].y1 += 2;
					}
					for (int i = 0;i < 20;i++) {
						if (r[i].st == 1) {
							r[i].x += 2;
							r[i].y -= 2;
						}
					}
				}
			}
			if (re[0].mx > mx1) {
				if (re[0].my < my1) {
					re[0].y += 2;
					re[0].y1 += 2;
					if (re[0].y1 > 800) {
						re[0].y -= 2;
						re[0].y1 -= 2;
					}
					re[0].x -= 2;
					re[0].x1 -= 2;
					if (re[0].x < 0) {
						re[0].x += 2;
						re[0].x1 += 2;
					}
					for (int i = 0;i < 20;i++) {
						if (r[i].st == 1) {
							r[i].x -= 2;
							r[i].y += 2;
						}
					}
				}
				else if (re[0].my == my1) {
					re[0].x -= 2;
					re[0].x1 -= 2;
					if (re[0].x < 0) {
						re[0].x += 2;
						re[0].x1 += 2;
					}
					for (int i = 0;i < 20;i++) {
						if (r[i].st == 1) {
							r[i].x -= 2;
						}
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
					for (int i = 0;i < 20;i++) {
						if (r[i].st == 1) {
							r[i].x -= 2;
							r[i].y -= 2;
						}
					}
				}
			}
			if (re[0].mx == mx1) {
				if (re[0].my < my1) {
					re[0].y += 2;
					re[0].y1 += 2;
					if (re[0].y1 > 800) {
						re[0].y -= 2;
						re[0].y1 -= 2;
					}
					for (int i = 0;i < 20;i++) {
						if (r[i].st == 1) {
							r[i].y += 2;
						}
					}
				}
				else {
					re[0].y -= 2;
					re[0].y1 -= 2;
					if (re[0].y < 0) {
						re[0].y += 2;
						re[0].y1 += 2;
					}
					for (int i = 0;i < 20;i++) {
						if (r[i].st == 1) {
							r[i].y -= 2;
						}
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
	case WM_KEYDOWN:
		if (wParam == 'p' || wParam == 'P') {
			for (int i = 0;i < 20;i++) {
				r[i].speed = rand() % 30 + 5;
			}
			SetTimer(hwnd, 2, 500, NULL);
		}
		if (wParam == 'd' || wParam == 'D') {
			if (t == 0) {
				tempx = re[0].x;
				tempy = re[0].y;
				tempx1 = re[0].x1;
				tempy1 = re[0].y1;
				re[0].x = -100;
				re[0].y = -100;
				re[0].x1 = -100;
				re[0].y1 = -100;
				for (int i = 0;i < 20;i++) {
					r[i].st = 0;
				}
				t = 1;
			}
			else if (t == 1) {
				re[0].x = tempx;
				re[0].y = tempy;
				re[0].x1 =tempx1;
				re[0].y1 = tempy1;
				t = 0;
			}
		}
		if (wParam == 'r' || wParam == 'R') {
			t = 0;
			re[0].x = -100;
			re[0].y = -100;
			re[0].x1 = -100;
			re[0].y1 = -100;
			for (int i = 0;i < 20;i++) {
				r[i].st = 0;
			}
			for (int i = 0;i < 20;i++) {
				r[i].x = rand() % (rt.right - 80);
				r[i].y = -20;
			}
			w = 0;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}