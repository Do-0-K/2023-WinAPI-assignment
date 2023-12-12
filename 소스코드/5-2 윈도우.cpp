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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU5);
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 900, 900, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
struct rect {
	int x = 0,y = 0;
	int m = 0, n = 0;
	int k = 0, v = 0;
};
struct rect re[30];
struct rect ra[30];
BOOL InRect(int x1, int y1, int x2, int y2,int g,int h)
{
	if (x1 <= x2 && x2<= x1+g) {
		if (y1 <= y2 && y2 <= y1+h) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	else {
		return FALSE;
	}
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc, memdc,mdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HBITMAP hBitmap;
	static BOOL Selection;
	static HBITMAP hbitmap1;
	static HBITMAP hbitmap2;
	static RECT rectView;
	RECT rt;
	static int t = 0, t1 = 0;
	int mx = 0, my = 0;
	static int chose = 0;
	static int banjun = 0;
	static int p = 1;
	static int s = 0;
	static int f = 0, w = 0;
	static int j = 0;
	static int move = 0;
	static int temp = 0;
	static int togle = 0;
	static int v = 0;
	static int time = 0, time1 = 0;
	static int lock = 0;
	switch (iMsg) {
	case WM_CREATE:
		Selection = FALSE;
		GetClientRect(hwnd, &rectView);
		break;
	case WM_COMMAND:
		switch ((LOWORD(wParam))) {
		case ID_40058:
			chose = 1;
			p = 1;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_40059:
			chose = 2;
			p = 1;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_40060:
			p = 1;
			w = 3;
			t = 0;
			t1 = 0;
			s = -1;
			if (chose == 1) {
				while (t != 9) {
					re[t].x = rand()% 3 * 300;
					re[t].y = rand()% 3 * 300;
					if (t > 0) {
						for (int i = 0;i < t;i++) {
							if (re[i].x == re[t].x && re[i].y == re[t].y) {
								re[t].x = rand() % 3 * 300;
								re[t].y = rand() % 3 * 300;
								i = -1;
							}
						}
					}
					t++;
				}
			}
			if (chose == 2) {
				while (t1 != 9) {
					ra[t1].x = rand() % 3 * 300;
					ra[t1].y = rand() % 3 * 300;
					if (t1 > 0) {
						for (int i = 0;i < t1;i++) {
							if (ra[i].x == ra[t1].x && ra[i].y == ra[t1].y) {
								ra[t1].x = rand() % 3 * 300;
								ra[t1].y = rand() % 3 * 300;
								i = -1;
							}
						}
					}
					t1++;
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_40061:
			w = 4;
			p = 1;
			t = 0;
			t1 = 0;
			s = -1;
			if (chose == 1) {
				while (t != 16) {
					re[t].x = rand() % 4 * 225;
					re[t].y = rand() % 4 * 225;
					if (t > 0) {
						for (int i = 0;i < t;i++) {
							if (re[i].x == re[t].x && re[i].y == re[t].y) {
								re[t].x = rand() % 4 * 225;
								re[t].y = rand() % 4 * 225;
								i = -1;
							}
						}
					}
					t++;
				}
			}
			if (chose == 2) {
				while (t1 != 16) {
					ra[t1].x = rand() % 4 * 225;
					ra[t1].y = rand() % 4 * 225;
					if (t1 > 0) {
						for (int i = 0;i < t1;i++) {
							if (ra[i].x == ra[t1].x && ra[i].y == ra[t1].y) {
								ra[t1].x = rand() % 4 * 225;
								ra[t1].y = rand() % 4 * 225;
								i = -1;
							}
						}
					}
					t1++;
				} 
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_40062:
			w = 5;
			p = 1;
			t = 0;
			t1 = 0;
			s = -1;
			if (chose == 1) {
				while (t != 25) {
					re[t].x = rand() % 5 * 180;
					re[t].y = rand() % 5 * 180;
					if (t > 0) {
						for (int i = 0;i < t;i++) {
							if (re[i].x == re[t].x && re[i].y == re[t].y) {
								re[t].x = rand() % 5 * 180;
								re[t].y = rand() % 5 * 180;
								i = -1;
							}
						}
					}
					t++;
				}
			}
			if (chose == 2) {
				while (t1 != 25) {
					ra[t1].x = rand() % 5 * 180;
					ra[t1].y = rand() % 5 * 180;
					if (t1 > 0) {
						for (int i = 0;i < t1;i++) {
							if (ra[i].x == ra[t1].x && ra[i].y == ra[t1].y) {
								ra[t1].x = rand() % 5 * 180;
								ra[t1].y = rand() % 5 * 180;
								i = -1;
							}
						}
					}
					t1++;
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_40063:
			p = 0;
			s = 0;
			SetTimer(hwnd, 1, 500, NULL);
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_40064:
			f = 1;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_40065:
			p = 0;
			s = rand()%3+1;
			SetTimer(hwnd, 2, 800, NULL);
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_40066:
			DeleteObject(hbitmap1);
			DeleteObject(hbitmap2);
			PostQuitMessage(0);
			break;
		}
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		Rectangle(mdc, 0, 0, 900, 900);
		if (chose == 1) {
			hbitmap1 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
			memdc = CreateCompatibleDC(hdc);
			SelectObject(memdc, (HBITMAP)hbitmap1);
			if (p == 0) {
				if (s == 0) {
					StretchBlt(mdc, 0, 0, 900, 900, memdc, 0, 0, 300, 300, SRCCOPY);
				}
				if (s == 1) {
					StretchBlt(mdc, 0, 0, 900, 900, memdc, 0, 0, 300, 300, NOTSRCCOPY);
				}
				if (s == 2) {
					StretchBlt(mdc, 900, 0, -900, 900, memdc, 0, 0, 300, 300, SRCCOPY);
				}
				if (s == 3) {
					StretchBlt(mdc, 900, 900, -900, -900, memdc, 0, 0, 300, 300, SRCCOPY);
				}
			}
			if (p == 1) {
				if (f == 1) {
					if (w == 3) {
						StretchBlt(mdc, re[0].x, re[0].y, 300, 300, memdc, 0, 0, 100, 100, SRCCOPY);
						StretchBlt(mdc, re[1].x, re[1].y, 300, 300, memdc, 100, 0, 100,100, SRCCOPY);
						StretchBlt(mdc, re[2].x, re[2].y, 300, 300, memdc, 200, 0, 100, 100, SRCCOPY);
						StretchBlt(mdc, re[3].x, re[3].y, 300, 300, memdc, 0, 100, 100, 100, SRCCOPY);
						StretchBlt(mdc, re[4].x, re[4].y, 300, 300, memdc, 100, 100, 100, 100, SRCCOPY);
						StretchBlt(mdc, re[5].x, re[5].y, 300, 300, memdc, 200, 100, 100, 100, SRCCOPY);
						StretchBlt(mdc, re[6].x, re[6].y, 300, 300, memdc, 0, 200, 100, 100, SRCCOPY);
						StretchBlt(mdc, re[7].x, re[7].y, 300, 300, memdc, 100, 200, 100, 100, SRCCOPY);
					}
					if (w == 4) {
						StretchBlt(mdc, re[0].x, re[0].y, 225, 225, memdc, 0, 0, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[1].x, re[1].y, 225, 225, memdc, 75, 0, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[2].x, re[2].y, 225, 225, memdc, 150, 0, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[3].x, re[3].y, 225, 225, memdc, 225, 0, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[4].x, re[4].y, 225, 225, memdc, 0, 75, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[5].x, re[5].y, 225, 225, memdc, 75, 75, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[6].x, re[6].y, 225, 225, memdc, 150, 75, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[7].x, re[7].y, 225, 225, memdc, 225, 75, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[8].x, re[8].y, 225, 225, memdc, 0, 150, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[9].x, re[9].y, 225, 225, memdc, 75, 150, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[10].x, re[10].y, 225, 225, memdc, 150, 150, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[11].x, re[11].y, 225, 225, memdc, 225, 150, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[12].x, re[12].y, 225, 225, memdc, 0, 225, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[13].x, re[13].y, 225, 225, memdc, 75, 225, 75, 75, SRCCOPY);
						StretchBlt(mdc, re[14].x, re[14].y, 225, 225, memdc, 150, 225, 75, 75, SRCCOPY);
					}
					if (w == 5) {
						StretchBlt(mdc, re[0].x, re[0].y, 180, 180, memdc, 0, 0, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[1].x, re[1].y, 180, 180, memdc, 60, 0, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[2].x, re[2].y, 180, 180, memdc, 120, 0, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[3].x, re[3].y, 180, 180, memdc, 180, 0, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[4].x, re[4].y, 180, 180, memdc, 240, 0, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[5].x, re[5].y, 180, 180, memdc, 0, 60, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[6].x, re[6].y, 180, 180, memdc, 60, 60, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[7].x, re[7].y, 180, 180, memdc, 120, 60, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[8].x, re[8].y, 180, 180, memdc, 180, 60, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[9].x, re[9].y, 180, 180, memdc, 240, 60, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[10].x, re[10].y, 180, 180, memdc, 0, 120, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[11].x, re[11].y, 180, 180, memdc, 60, 120, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[12].x, re[12].y, 180, 180, memdc, 120, 120, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[13].x, re[13].y, 180, 180, memdc, 180, 120, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[14].x, re[14].y, 180, 180, memdc, 240, 120, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[15].x, re[15].y, 180, 180, memdc, 0, 180, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[16].x, re[16].y, 180, 180, memdc, 60, 180, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[17].x, re[17].y, 180, 180, memdc, 120, 180, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[18].x, re[18].y, 180, 180, memdc, 180, 180, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[19].x, re[19].y, 180, 180, memdc, 240, 180, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[20].x, re[20].y, 180, 180, memdc, 0, 240, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[21].x, re[21].y, 180, 180, memdc, 60, 240, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[22].x, re[22].y, 180, 180, memdc, 120, 240, 60, 60, SRCCOPY);
						StretchBlt(mdc, re[23].x, re[23].y, 180, 180, memdc, 180, 240, 60, 60, SRCCOPY);
					}
				}
				if (f == 2) {
					if (w == 3) {
						StretchBlt(mdc, re[0].x, re[0].y, 300, 900, memdc, 0, 0, 100, 300, SRCCOPY);
						StretchBlt(mdc, re[1].x, re[1].y, 300, 900, memdc, 100, 0, 100, 300, SRCCOPY);
						StretchBlt(mdc, re[2].x, re[2].y, 300, 900, memdc, 200, 0, 100, 300, SRCCOPY);
					}
					if (w == 4) {
						StretchBlt(mdc, re[0].x, re[0].y, 225, 900, memdc, 0, 0, 75, 300, SRCCOPY);
						StretchBlt(mdc, re[1].x, re[1].y, 225, 900, memdc, 75, 0, 75, 300, SRCCOPY);
						StretchBlt(mdc, re[2].x, re[2].y, 225, 900, memdc, 150, 0, 75, 300, SRCCOPY);
						StretchBlt(mdc, re[3].x, re[3].y, 225, 900, memdc, 225, 0, 75, 300, SRCCOPY);
					}
					if (w == 5) {
						StretchBlt(mdc, re[0].x, re[0].y, 180, 900, memdc, 0, 0, 60, 300, SRCCOPY);
						StretchBlt(mdc, re[1].x, re[1].y, 180, 900, memdc, 60, 0, 60, 300, SRCCOPY);
						StretchBlt(mdc, re[2].x, re[2].y, 180, 900, memdc, 120, 0, 60, 300, SRCCOPY);
						StretchBlt(mdc, re[3].x, re[3].y, 180, 900, memdc, 180, 0, 60, 300, SRCCOPY);
						StretchBlt(mdc, re[4].x, re[4].y, 180, 900, memdc, 240, 0, 60, 300, SRCCOPY);
					}
				}
				if (f == 3) {
					if (w == 3) {
						StretchBlt(mdc, re[0].x, re[0].y, 900, 300, memdc, 0, 0, 300, 100, SRCCOPY);
						StretchBlt(mdc, re[1].x, re[1].y, 900, 300, memdc, 0, 100, 300, 100, SRCCOPY);
						StretchBlt(mdc, re[2].x, re[2].y, 900, 300, memdc, 0, 200, 300, 100, SRCCOPY);
					}
					if (w == 4) {
						StretchBlt(mdc, re[0].x, re[0].y, 900, 225, memdc, 0, 0, 300, 75, SRCCOPY);
						StretchBlt(mdc, re[1].x, re[1].y, 900, 225, memdc, 0, 75, 300, 75, SRCCOPY);
						StretchBlt(mdc, re[2].x, re[2].y, 900, 225, memdc, 0, 150, 300, 75, SRCCOPY);
						StretchBlt(mdc, re[3].x, re[3].y, 900, 225, memdc, 0, 225, 300, 75, SRCCOPY);
					}
					if (w == 5) {
						StretchBlt(mdc, re[0].x, re[0].y, 900, 180, memdc, 0, 0, 300, 60, SRCCOPY);
						StretchBlt(mdc, re[1].x, re[1].y, 900, 180, memdc, 0, 60, 300, 60, SRCCOPY);
						StretchBlt(mdc, re[2].x, re[2].y, 900, 180, memdc, 0, 120, 300, 60, SRCCOPY);
						StretchBlt(mdc, re[3].x, re[3].y, 900, 180, memdc, 0, 180, 300, 60, SRCCOPY);
						StretchBlt(mdc, re[4].x, re[4].y, 900, 180, memdc, 0, 240, 300, 60, SRCCOPY);
					}
				}
			}
			DeleteDC(memdc);
		}
		else if (chose == 2) {
			hbitmap2 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
			memdc = CreateCompatibleDC(hdc);
			SelectObject(memdc, (HBITMAP)hbitmap2);
			if (p == 0) {
				if (s == 0) {
					StretchBlt(mdc, 0, 0, 900, 900, memdc, 0, 0, 650, 400, SRCCOPY);
				}
				if (s == 1) {
					StretchBlt(mdc, 0, 0, 900, 900, memdc, 0, 0, 650, 400, NOTSRCCOPY);
				}
				if (s == 2) {
					StretchBlt(mdc, 900, 0, -900, 900, memdc, 0, 0, 650, 400, SRCCOPY);
				}
				if (s == 3) {
					StretchBlt(mdc, 900, 900, -900, -900, memdc, 0, 0, 650, 400, SRCCOPY);
				}
			}
			if (p == 1) {
				if (f == 1) {
					if (w == 3) {
						StretchBlt(mdc, ra[0].x, ra[0].y, 300, 300, memdc, 0, 0, 100, 100, SRCCOPY);
						StretchBlt(mdc, ra[1].x, ra[1].y, 300, 300, memdc, 100, 0, 100, 100, SRCCOPY);
						StretchBlt(mdc, ra[2].x, ra[2].y, 300, 300, memdc, 200, 0, 100, 100, SRCCOPY);
						StretchBlt(mdc, ra[3].x, ra[3].y, 300, 300, memdc, 0, 100, 100, 100, SRCCOPY);
						StretchBlt(mdc, ra[4].x, ra[4].y, 300, 300, memdc, 100, 100, 100, 100, SRCCOPY);
						StretchBlt(mdc, ra[5].x, ra[5].y, 300, 300, memdc, 200, 100, 100, 100, SRCCOPY);
						StretchBlt(mdc, ra[6].x, ra[6].y, 300, 300, memdc, 0, 200, 100, 100, SRCCOPY);
						StretchBlt(mdc, ra[7].x, ra[7].y, 300, 300, memdc, 100, 200, 100, 100, SRCCOPY);
					}
					if (w == 4) {
						StretchBlt(mdc, ra[0].x, ra[0].y, 225, 225, memdc, 0, 0, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[1].x, ra[1].y, 225, 225, memdc, 75, 0, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[2].x, ra[2].y, 225, 225, memdc, 150, 0, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[3].x, ra[3].y, 225, 225, memdc, 225, 0, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[4].x, ra[4].y, 225, 225, memdc, 0, 75, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[5].x, ra[5].y, 225, 225, memdc, 75, 75, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[6].x, ra[6].y, 225, 225, memdc, 150, 75, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[7].x, ra[7].y, 225, 225, memdc, 225, 75, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[8].x, ra[8].y, 225, 225, memdc, 0, 150, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[9].x, ra[9].y, 225, 225, memdc, 75, 150, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[10].x, ra[10].y, 225, 225, memdc, 150, 150, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[11].x, ra[11].y, 225, 225, memdc, 225, 150, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[12].x, ra[12].y, 225, 225, memdc, 0, 225, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[13].x, ra[13].y, 225, 225, memdc, 75, 225, 75, 75, SRCCOPY);
						StretchBlt(mdc, ra[14].x, ra[14].y, 225, 225, memdc, 150, 225, 75, 75, SRCCOPY);
					}
					if (w == 5) {
						StretchBlt(mdc, ra[0].x, ra[0].y, 180, 180, memdc, 0, 0, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[1].x, ra[1].y, 180, 180, memdc, 60, 0, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[2].x, ra[2].y, 180, 180, memdc, 120, 0, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[3].x, ra[3].y, 180, 180, memdc, 180, 0, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[4].x, ra[4].y, 180, 180, memdc, 240, 0, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[5].x, ra[5].y, 180, 180, memdc, 0, 60, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[6].x, ra[6].y, 180, 180, memdc, 60, 60, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[7].x, ra[7].y, 180, 180, memdc, 120, 60, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[8].x, ra[8].y, 180, 180, memdc, 180, 60, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[9].x, ra[9].y, 180, 180, memdc, 240, 60, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[10].x, ra[10].y, 180, 180, memdc, 0, 120, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[11].x, ra[11].y, 180, 180, memdc, 60, 120, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[12].x, ra[12].y, 180, 180, memdc, 120, 120, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[13].x, ra[13].y, 180, 180, memdc, 180, 120, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[14].x, ra[14].y, 180, 180, memdc, 240, 120, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[15].x, ra[15].y, 180, 180, memdc, 0, 180, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[16].x, ra[16].y, 180, 180, memdc, 60, 180, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[17].x, ra[17].y, 180, 180, memdc, 120, 180, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[18].x, ra[18].y, 180, 180, memdc, 180, 180, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[19].x, ra[19].y, 180, 180, memdc, 240, 180, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[20].x, ra[20].y, 180, 180, memdc, 0, 240, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[21].x, ra[21].y, 180, 180, memdc, 60, 240, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[22].x, ra[22].y, 180, 180, memdc, 120, 240, 60, 60, SRCCOPY);
						StretchBlt(mdc, ra[23].x, ra[23].y, 180, 180, memdc, 180, 240, 60, 60, SRCCOPY);
					}
				}
				if (f == 2) {
					if (w == 3) {
						StretchBlt(mdc, ra[0].x, ra[0].y, 300, 900, memdc, 0, 0, 100, 300, SRCCOPY);
						StretchBlt(mdc, ra[1].x, ra[1].y, 300, 900, memdc, 100, 0, 100, 300, SRCCOPY);
						StretchBlt(mdc, ra[2].x, ra[2].y, 300, 900, memdc, 200, 0, 100, 300, SRCCOPY);
					}
					if (w == 4) {
						StretchBlt(mdc, ra[0].x, ra[0].y, 225, 900, memdc, 0, 0, 75, 300, SRCCOPY);
						StretchBlt(mdc, ra[1].x, ra[1].y, 225, 900, memdc, 75, 0, 75, 300, SRCCOPY);
						StretchBlt(mdc, ra[2].x, ra[2].y, 225, 900, memdc, 150, 0, 75, 300, SRCCOPY);
						StretchBlt(mdc, ra[3].x, ra[3].y, 225, 900, memdc, 225, 0, 75, 300, SRCCOPY);
					}
					if (w == 5) {
						StretchBlt(mdc, ra[0].x, ra[0].y, 180, 900, memdc, 0, 0, 60, 300, SRCCOPY);
						StretchBlt(mdc, ra[1].x, ra[1].y, 180, 900, memdc, 60, 0, 60, 300, SRCCOPY);
						StretchBlt(mdc, ra[2].x, ra[2].y, 180, 900, memdc, 120, 0, 60, 300, SRCCOPY);
						StretchBlt(mdc, ra[3].x, ra[3].y, 180, 900, memdc, 180, 0, 60, 300, SRCCOPY);
						StretchBlt(mdc, ra[4].x, ra[4].y, 180, 900, memdc, 240, 0, 60, 300, SRCCOPY);
					}
				}
				if (f == 3) {
					if (w == 3) {
						StretchBlt(mdc, ra[0].x, ra[0].y, 900, 300, memdc, 0, 0, 300, 100, SRCCOPY);
						StretchBlt(mdc, ra[1].x, ra[1].y, 900, 300, memdc, 0, 100, 300, 100, SRCCOPY);
						StretchBlt(mdc, ra[2].x, ra[2].y, 900, 300, memdc, 0, 200, 300, 100, SRCCOPY);
					}
					if (w == 4) {
						StretchBlt(mdc, ra[0].x, ra[0].y, 900, 225, memdc, 0, 0, 300, 75, SRCCOPY);
						StretchBlt(mdc, ra[1].x, ra[1].y, 900, 225, memdc, 0, 75, 300, 75, SRCCOPY);
						StretchBlt(mdc, ra[2].x, ra[2].y, 900, 225, memdc, 0, 150, 300, 75, SRCCOPY);
						StretchBlt(mdc, ra[3].x, ra[3].y, 900, 225, memdc, 0, 225, 300, 75, SRCCOPY);
					}
					if (w == 5) {
						StretchBlt(mdc, ra[0].x, ra[0].y, 900, 180, memdc, 0, 0, 300, 60, SRCCOPY);
						StretchBlt(mdc, ra[1].x, ra[1].y, 900, 180, memdc, 0, 60, 300, 60, SRCCOPY);
						StretchBlt(mdc, ra[2].x, ra[2].y, 900, 180, memdc, 0, 120, 300, 60, SRCCOPY);
						StretchBlt(mdc, ra[3].x, ra[3].y, 900, 180, memdc, 0, 180, 300, 60, SRCCOPY);
						StretchBlt(mdc, ra[4].x, ra[4].y, 900, 180, memdc, 0, 240, 300, 60, SRCCOPY);
					}
				}
			}
			DeleteDC(memdc);
		}
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (lock == 0) {
			if (chose == 1) {
				if (p == 1) {
					if (f == 1) {
						if (w == 3) {
							for (int i = 0;i < t;i++) {
								if (InRect(re[i].x, re[i].y, mx, my, 300, 300)) {
									move = i;
									re[move].m = (re[i].x + re[i].x + 300) / 2;
									re[move].n = (re[i].y + re[i].y + 300) / 2;
									break;
								}
							}
						}
						if (w == 4) {
							for (int i = 0;i < t;i++) {
								if (InRect(re[i].x, re[i].y, mx, my, 225, 225)) {
									move = i;
									re[move].m = (re[i].x + re[i].x + 225) / 2;
									re[move].n = (re[i].y + re[i].y + 225) / 2;
									break;
								}
							}
						}
						if (w == 5) {
							for (int i = 0;i < t;i++) {
								if (InRect(re[i].x, re[i].y, mx, my, 180, 180)) {
									move = i;
									re[move].m = (re[i].x + re[i].x + 180) / 2;
									re[move].n = (re[i].y + re[i].y + 180) / 2;
									break;
								}
							}
						}
					}
					if (f == 2) {
						if (w == 3) {
							for (int i = 0;i < t;i++) {
								if (InRect(re[i].x, re[i].y, mx, my, 300, 900)) {
									move = i;
									re[move].m = (re[i].x + re[i].x + 300) / 2;
									re[move].n = 450;
									break;
								}
							}
						}
						if (w == 4) {
							for (int i = 0;i < t;i++) {
								if (InRect(re[i].x, re[i].y, mx, my, 225, 900)) {
									move = i;
									re[move].m = (re[i].x + re[i].x + 225) / 2;
									re[move].n = 450;
									break;
								}
							}
						}
						if (w == 5) {
							for (int i = 0;i < t;i++) {
								if (InRect(re[i].x, re[i].y, mx, my, 180, 900)) {
									move = i;
									re[move].m = (re[i].x + re[i].x + 180) / 2;
									re[move].n = 450;
									break;
								}
							}
						}
					}
					if (f == 3) {
						if (w == 3) {
							for (int i = 0;i < t;i++) {
								if (InRect(re[i].x, re[i].y, mx, my, 900, 300)) {
									move = i;
									re[move].m = 450;
									re[move].n = (re[i].y + re[i].y + 300) / 2;
									break;
								}
							}
						}
						if (w == 4) {
							for (int i = 0;i < t;i++) {
								if (InRect(re[i].x, re[i].y, mx, my, 900, 225)) {
									move = i;
									re[move].m = 450;
									re[move].n = (re[i].y + re[i].y + 300) / 2;
									break;
								}
							}
						}
						if (w == 5) {
							for (int i = 0;i < t;i++) {
								if (InRect(re[i].x, re[i].y, mx, my, 900, 180)) {
									move = i;
									re[move].m = 450;
									re[move].n = (re[i].y + re[i].y + 300) / 2;
									break;
								}
							}
						}
					}
				}
				togle = 1;
			}
			if (chose == 2) {
				if (p == 1) {
					if (f == 1) {
						if (w == 3) {
							for (int i = 0;i < t1;i++) {
								if (InRect(ra[i].x, ra[i].y, mx, my, 300, 300)) {
									move = i;
									ra[move].m = (ra[i].x + ra[i].x + 300) / 2;
									ra[move].n = (ra[i].y + ra[i].y + 300) / 2;
									break;
								}
							}
						}
						if (w == 4) {
							for (int i = 0;i < t1;i++) {
								if (InRect(ra[i].x, ra[i].y, mx, my, 225, 225)) {
									move = i;
									ra[move].m = (ra[i].x + ra[i].x + 225) / 2;
									ra[move].n = (ra[i].y + ra[i].y + 225) / 2;
									break;
								}
							}
						}
						if (w == 5) {
							for (int i = 0;i < t1;i++) {
								if (InRect(ra[i].x, ra[i].y, mx, my, 180, 180)) {
									move = i;
									ra[move].m = (ra[i].x + ra[i].x + 180) / 2;
									ra[move].n = (ra[i].y + ra[i].y + 180) / 2;
									break;
								}
							}
						}
					}
					if (f == 2) {
						if (w == 3) {
							for (int i = 0;i < t1;i++) {
								if (InRect(ra[i].x, ra[i].y, mx, my, 300, 900)) {
									move = i;
									ra[move].m = (ra[i].x + ra[i].x + 300) / 2;
									ra[move].n = 450;
									break;
								}
							}
						}
						if (w == 4) {
							for (int i = 0;i < t1;i++) {
								if (InRect(ra[i].x, ra[i].y, mx, my, 225, 900)) {
									move = i;
									ra[move].m = (ra[i].x + ra[i].x + 225) / 2;
									ra[move].n = 450;
									break;
								}
							}
						}
						if (w == 5) {
							for (int i = 0;i < t1;i++) {
								if (InRect(ra[i].x, ra[i].y, mx, my, 180, 900)) {
									move = i;
									ra[move].m = (ra[i].x + ra[i].x + 180) / 2;
									ra[move].n = 450;
									break;
								}
							}
						}
					}
					if (f == 3) {
						if (w == 3) {
							for (int i = 0;i < t1;i++) {
								if (InRect(ra[i].x, ra[i].y, mx, my, 900, 300)) {
									move = i;
									ra[move].m = 450;
									ra[move].n = (ra[i].y + ra[i].y + 300) / 2;
									break;
								}
							}
						}
						if (w == 4) {
							for (int i = 0;i < t1;i++) {
								if (InRect(ra[i].x, ra[i].y, mx, my, 900, 225)) {
									move = i;
									ra[move].m = 450;
									ra[move].n = (ra[i].y + ra[i].y + 225) / 2;
									break;
								}
							}
						}
						if (w == 5) {
							for (int i = 0;i < t1;i++) {
								if (InRect(ra[i].x, ra[i].y, mx, my, 900, 180)) {
									move = i;
									ra[move].m = 450;
									ra[move].n = (ra[i].y + ra[i].y + 180) / 2;
									break;
								}
							}
						}
					}
				}
				togle = 2;
			}
			lock++;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (lock == 1) {
			if (togle == 1) {
				if (re[move].m < mx && re[move].n < my) {
					if ((mx - re[move].m) > (my - re[move].n)) {
						temp = 1;
					}
					else {
						temp = 2;
					}
				}
				else if (re[move].m < mx && re[move].n > my) {
					if ((mx - re[move].m) > (re[move].n - my)) {
						temp = 1;
					}
					else {
						temp = 3;
					}
				}
				else if (re[move].m > mx && re[move].n < my) {
					if ((re[move].m - mx) > (my - re[move].n)) {
						temp = 4;
					}
					else {
						temp = 2;
					}
				}
				else if (re[move].m > mx && re[move].n > my) {
					if ((re[move].m - mx) > (re[move].n - my)) {
						temp = 4;
					}
					else {
						temp = 3;
					}
				}
				lock++;
				SetTimer(hwnd, 3, 70, NULL);
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			}
			if (togle == 2) {
				if (ra[move].m < mx && ra[move].n < my) {
					if ((mx - ra[move].m) > (my - ra[move].n)) {
						temp = 1;
					}
					else {
						temp = 2;
					}
				}
				else if (ra[move].m < mx && ra[move].n > my) {
					if ((mx - ra[move].m) > (ra[move].n - my)) {
						temp = 1;
					}
					else {
						temp = 3;
					}
				}
				else if (ra[move].m > mx && ra[move].n < my) {
					if ((ra[move].m - mx) > (my - ra[move].n)) {
						temp = 4;
					}
					else {
						temp = 2;
					}
				}
				else if (ra[move].m > mx && ra[move].n > my) {
					if ((ra[move].m - mx) > (ra[move].n - my)) {
						temp = 4;
					}
					else {
						temp = 3;
					}
				}
				lock++;
				SetTimer(hwnd, 4, 70, NULL);
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			}
		}
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == 'f' || wParam == 'F') {
			p = 0;
			SetTimer(hwnd, 1, 500, NULL);
		}
		if (wParam == 's' || wParam == 'S') {
			f = 1;
		}
		if (wParam == 'v' || wParam == 'V') {
			f = 2;
			t = 0;
			t1 = 0;
			if (chose == 1) {
				if (w == 3) {
					re[0].x = 0;
					re[0].y = 0;
					re[1].x = 300;
					re[1].y = 0;
					re[2].x = 600;
					re[2].y = 0;
					t = 3;
				}
				if (w == 4) {
					re[0].x = 0;
					re[0].y = 0;
					re[1].x = 225;
					re[1].y = 0;
					re[2].x = 450;
					re[2].y = 0;
					re[3].x = 675;
					re[3].y = 0;
					t = 4;
				}
				if (w == 5) {
					re[0].x = 0;
					re[0].y = 0;
					re[1].x = 180;
					re[1].y = 0;
					re[2].x = 360;
					re[2].y = 0;
					re[3].x = 540;
					re[3].y = 0;
					re[4].x = 720;
					re[4].y = 0;
					t = 5;
				}
			}
			if (chose == 2) {
				if (w == 3) {
					ra[0].x = 0;
					ra[0].y = 0;
					ra[1].x = 300;
					ra[1].y = 0;
					ra[2].x = 600;
					ra[2].y = 0;
					t1 = 3;
				}
				if (w == 4) {
					ra[0].x = 0;
					ra[0].y = 0;
					ra[1].x = 225;
					ra[1].y = 0;
					ra[2].x = 450;
					ra[2].y = 0;
					ra[3].x = 675;
					ra[3].y = 0;
					t1 = 4;
				}
				if (w == 5) {
					ra[0].x = 0;
					ra[0].y = 0;
					ra[1].x = 180;
					ra[1].y = 0;
					ra[2].x = 360;
					ra[2].y = 0;
					ra[3].x = 540;
					ra[3].y = 0;
					ra[4].x = 720;
					ra[4].y = 0;
					t1 = 5;
				}
			}
		}
		if (wParam == 'h' || wParam == 'H') {
			f = 3;
			t = 0;t1 = 0;
			if (chose == 1) {
				if (w == 3) {
					re[0].x = 0;
					re[0].y = 0;
					re[1].x = 0;
					re[1].y = 300;
					re[2].x = 0;
					re[2].y = 600;
					t = 3;
				}
				if (w == 4) {
					re[0].x = 0;
					re[0].y = 0;
					re[1].x = 0;
					re[1].y = 225;
					re[2].x = 0;
					re[2].y = 450;
					re[3].x = 0;
					re[3].y = 675;
					t = 4;
				}
				if (w == 5) {
					re[0].x = 0;
					re[0].y = 0;
					re[1].x = 0;
					re[1].y = 180;
					re[2].x = 0;
					re[2].y = 360;
					re[3].x = 0;
					re[3].y = 540;
					re[4].x = 0;
					re[4].y = 720;
					t = 5;
				}
			}
			if (chose == 2) {
				if (w == 3) {
					ra[0].x = 0;
					ra[0].y = 0;
					ra[1].x = 0;
					ra[1].y = 300;
					ra[2].x = 0;
					ra[2].y = 600;
					t1 = 3;
				}
				if (w == 4) {
					ra[0].x = 0;
					ra[0].y = 0;
					ra[1].x = 0;
					ra[1].y = 255;
					ra[2].x = 0;
					ra[2].y = 450;
					ra[3].x = 0;
					ra[3].y = 675;
					t1 = 4;
				}
				if (w == 5) {
					ra[0].x = 0;
					ra[0].y = 0;
					ra[1].x = 0;
					ra[1].y = 180;
					ra[2].x = 0;
					ra[2].y = 360;
					ra[3].x = 0;
					ra[3].y = 540;
					ra[4].x = 0;
					ra[4].y = 720;
					t1 = 5;
				}
			}
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
			p = 1;
			break;
		case 2:
			p = 1;
			s = 0;
			break;
		case 3:
			if (temp == 1) {
				if (lock == 1) {
					if (f == 1) {
						if (w == 3) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].y == re[move].y) {
									if (re[i].x == re[move].x + 300) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].x == 600) {
								time = 1;
							}
							if (time == 0) {
								re[move].x += 50;
							}
							if (re[move].x == 300 || re[move].x == 600) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].y == re[move].y) {
									if (re[i].x == re[move].x + 225) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].x == 675) {
								time = 1;
							}
							if (time == 0) {
								re[move].x += 25;
							}
							if (re[move].x == 225 || re[move].x == 450 || re[move].x == 675) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].y == re[move].y) {
									if (re[i].x == re[move].x + 180) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].x == 720) {
								time = 1;
							}
							if (time == 0) {
								re[move].x += 30;
							}
							if (re[move].x == 180 || re[move].x == 360 || re[move].x == 540 || re[move].x == 720) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
					if (f == 2) {
						if (w == 3) {
							if (time == 0) {
								if (re[move].x == 0) {
									for (int i = 0;i < 3;i++) {
										if (re[i].x == 300) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 300) {
									for (int i = 0;i < 3;i++) {
										if (re[i].x == 600) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].x == 600) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].x += 50;
								re[v].x -= 50;
							}
							if (re[move].x == 300 || re[move].x == 600) {
								time1 = 0;
								v = 0;
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							if (time == 0) {
								if (re[move].x == 0) {
									for (int i = 0;i < 4;i++) {
										if (re[i].x == 225) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 225) {
									for (int i = 0;i < 4;i++) {
										if (re[i].x == 450) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 450) {
									for (int i = 0;i < 4;i++) {
										if (re[i].x == 675) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].x == 675) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].x += 25;
								re[v].x -= 25;
							}
							if (re[move].x == 225 || re[move].x == 450 || re[move].x == 675) {
								time1 = 0;lock = 0;
								v = 0;
								time = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							if (time == 0) {
								if (re[move].x == 0) {
									for (int i = 0;i < 5;i++) {
										if (re[i].x == 180) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 180) {
									for (int i = 0;i < 5;i++) {
										if (re[i].x == 360) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 360) {
									for (int i = 0;i < 5;i++) {
										if (re[i].x == 540) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 540) {
									for (int i = 0;i < 5;i++) {
										if (re[i].x == 720) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].x == 720) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].x += 30;
								re[v].x -= 30;
							}
							if (re[move].x == 180 || re[move].x == 360 || re[move].x == 540 || re[move].x == 720) {
								time1 = 0;
								time = 0;lock = 0;
								v = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
				}
			}
			if (temp == 2) {
				if (lock == 1) {
					if (f == 1) {
						if (w == 3) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].x == re[move].x) {
									if (re[i].y == re[move].y + 300) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].y == 600) {
								time = 1;
							}
							if (time == 0) {
								re[move].y += 50;
							}
							if (re[move].y == 300 || re[move].y == 600) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].x == re[move].x) {
									if (re[i].y == re[move].y + 225) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].y == 675) {
								time = 1;
							}
							if (time == 0) {
								re[move].y += 25;
							}
							if (re[move].y == 225 || re[move].y == 450 || re[move].y == 675) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].x == re[move].x) {
									if (re[i].y == re[move].y + 180) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].y == 720) {
								time = 1;
							}
							if (time == 0) {
								re[move].y += 30;
							}
							if (re[move].y == 180 || re[move].y == 360 || re[move].y == 540 || re[move].y == 720) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
					if (f == 3) {
						if (w == 3) {
							if (time == 0) {
								if (re[move].y == 0) {
									for (int i = 0;i < 3;i++) {
										if (re[i].y == 300) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 300) {
									for (int i = 0;i < 3;i++) {
										if (re[i].y == 600) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].y == 600) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].y += 50;
								re[v].y -= 50;
							}
							if (re[move].y == 300 || re[move].y == 600) {
								v = 0;
								time = 0;lock = 0;
								time = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							if (time == 0) {
								if (re[move].y == 0) {
									for (int i = 0;i < 4;i++) {
										if (re[i].y == 225) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 225) {
									for (int i = 0;i < 4;i++) {
										if (re[i].y == 450) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 450) {
									for (int i = 0;i < 4;i++) {
										if (re[i].y == 675) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].y == 675) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].y += 25;
								re[v].y -= 25;
							}
							if (re[move].y == 225 || re[move].y == 450 || re[move].y == 675) {
								v = 0;
								time = 0;
								time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							if (time == 0) {
								if (re[move].y == 0) {
									for (int i = 0;i < 5;i++) {
										if (re[i].y == 180) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 180) {
									for (int i = 0;i < 5;i++) {
										if (re[i].y == 360) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 360) {
									for (int i = 0;i < 5;i++) {
										if (re[i].y == 540) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 540) {
									for (int i = 0;i < 5;i++) {
										if (re[i].y == 720) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].y == 720) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].y += 30;
								re[v].y -= 30;
							}
							if (re[move].y == 180 || re[move].y == 360 || re[move].y == 540 || re[move].y == 720) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
				}
			}
			if (temp == 3) {
				if (lock == 1) {
					if (f == 1) {
						if (w == 3) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].x == re[move].x) {
									if (re[i].y == re[move].y - 300) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].y == 0) {
								time = 1;
							}
							if (time == 0) {
								re[move].y -= 50;
							}
							if (re[move].y == 0 || re[move].y == 300) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].x == re[move].x) {
									if (re[i].y == re[move].y - 225) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].y == 0) {
								time = 1;
							}
							if (time == 0) {
								re[move].y -= 25;
							}
							if (re[move].y == 0 || re[move].y == 225 || re[move].y == 450) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].x == re[move].x) {
									if (re[i].y == re[move].y - 180) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].y == 0) {
								time = 1;
							}
							if (time == 0) {
								re[move].y -= 30;
							}
							if (re[move].y == 0 || re[move].y == 180 || re[move].y == 360 || re[move].y == 540) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
					if (f == 3) {
						if (w == 3) {
							if (time == 0) {
								if (re[move].y == 300) {
									for (int i = 0;i < 3;i++) {
										if (re[i].y == 0) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 600) {
									for (int i = 0;i < 3;i++) {
										if (re[i].y == 300) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].y == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].y -= 50;
								re[v].y += 50;
							}
							if (re[move].y == 0 || re[move].y == 300) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							if (time == 0) {
								if (re[move].y == 225) {
									for (int i = 0;i < 4;i++) {
										if (re[i].y == 0) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 450) {
									for (int i = 0;i < 4;i++) {
										if (re[i].y == 225) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 675) {
									for (int i = 0;i < 4;i++) {
										if (re[i].y == 450) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].y == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].y -= 25;
								re[v].y += 25;
							}
							if (re[move].y == 0 || re[move].y == 225 || re[move].y == 450) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							if (time == 0) {
								if (re[move].y == 180) {
									for (int i = 0;i < 5;i++) {
										if (re[i].y == 0) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 360) {
									for (int i = 0;i < 5;i++) {
										if (re[i].y == 180) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 540) {
									for (int i = 0;i < 5;i++) {
										if (re[i].y == 360) {
											v = i;
											break;
										}
									}
								}
								if (re[move].y == 720) {
									for (int i = 0;i < 5;i++) {
										if (re[i].y == 540) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].y == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].y -= 30;
								re[v].y += 30;
							}
							if (re[move].y == 0 || re[move].y == 180 || re[move].y == 360 || re[move].y == 540) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
				}
			}
			if (temp == 4) {
				if (lock == 1) {
					if (f == 1) {
						if (w == 3) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].y == re[move].y) {
									if (re[i].x == re[move].x - 300) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].x == 0) {
								time = 1;
							}
							if (time == 0) {
								re[move].x -= 50;
							}
							if (re[move].x == 0 || re[move].x == 300) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].y == re[move].y) {
									if (re[i].x == re[move].x - 225) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].x == 0) {
								time = 1;
							}
							if (time == 0) {
								re[move].x -= 25;
							}
							if (re[move].x == 0 || re[move].x == 225 || re[move].x == 450) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							for (int i = 0;i < t - 1;i++) {
								if (re[i].y == re[move].y) {
									if (re[i].x == re[move].x - 180) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (re[move].x == 0) {
								time = 1;
							}
							if (time == 0) {
								re[move].x -= 30;
							}
							if (re[move].x == 0 || re[move].x == 180 || re[move].x == 360 || re[move].x == 540) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
					if (f == 2) {
						if (w == 3) {
							if (time == 0) {
								if (re[move].x == 300) {
									for (int i = 0;i < 3;i++) {
										if (re[i].x == 0) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 600) {
									for (int i = 0;i < 3;i++) {
										if (re[i].x == 300) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].x == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].x -= 50;
								re[v].x += 50;
							}
							if (re[move].x == 0 || re[move].x == 300) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							if (time == 0) {
								if (re[move].x == 225) {
									for (int i = 0;i < 4;i++) {
										if (re[i].x == 0) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 450) {
									for (int i = 0;i < 4;i++) {
										if (re[i].x == 225) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 675) {
									for (int i = 0;i < 4;i++) {
										if (re[i].x == 450) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].x == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].x -= 25;
								re[v].x += 25;
							}
							if (re[move].x == 0 || re[move].x == 225 || re[move].x == 450) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							if (time == 0) {
								if (re[move].x == 180) {
									for (int i = 0;i < 5;i++) {
										if (re[i].x == 0) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 360) {
									for (int i = 0;i < 5;i++) {
										if (re[i].x == 180) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 540) {
									for (int i = 0;i < 5;i++) {
										if (re[i].x == 360) {
											v = i;
											break;
										}
									}
								}
								if (re[move].x == 720) {
									for (int i = 0;i < 5;i++) {
										if (re[i].x == 540) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (re[move].x == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								re[move].x -= 30;
								re[v].x += 30;
							}
							if (re[move].x == 0 || re[move].x == 180 || re[move].x == 360 || re[move].x == 540) {
								v = 0;time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
				}
			}
			break;
		case 4:
			if (temp == 1) {
				if (lock == 1) {
					if (f == 1) {
						if (w == 3) {
							for (int i = 0;i < t;i++) {
								if (ra[i].y == ra[move].y) {
									if (ra[i].x == ra[move].x + 300) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].x == 600) {
								time = 1;
							}
							if (time == 0) {
								ra[move].x += 50;
							}
							if (ra[move].x == 300 || ra[move].x == 600) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							for (int i = 0;i < t;i++) {
								if (ra[i].y == ra[move].y) {
									if (ra[i].x == ra[move].x + 225) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].x == 675) {
								time = 1;
							}
							if (time == 0) {
								ra[move].x += 25;
							}
							if (ra[move].x == 225 || ra[move].x == 450 || ra[move].x == 675) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							for (int i = 0;i < t;i++) {
								if (ra[i].y == ra[move].y) {
									if (ra[i].x == ra[move].x + 180) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].x == 720) {
								time = 1;
							}
							if (time == 0) {
								ra[move].x += 30;
							}
							if (ra[move].x == 180 || ra[move].x == 360 || ra[move].x == 540 || ra[move].x == 720) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
					if (f == 2) {
						if (w == 3) {
							if (time == 0) {
								if (ra[move].x == 0) {
									for (int i = 0;i < 3;i++) {
										if (ra[i].x == 300) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 300) {
									for (int i = 0;i < 3;i++) {
										if (ra[i].x == 600) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].x == 600) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].x += 50;
								ra[v].x -= 50;
							}
							if (ra[move].x == 300 || ra[move].x == 600) {
								time1 = 0;
								v = 0;lock = 0;
								time = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							if (time == 0) {
								if (ra[move].x == 0) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].x == 225) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 225) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].x == 450) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 450) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].x == 675) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].x == 675) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].x += 25;
								ra[v].x -= 25;
							}
							if (ra[move].x == 225 || ra[move].x == 450 || ra[move].x == 675) {
								time1 = 0;
								v = 0;lock = 0;
								time = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							if (time == 0) {
								if (ra[move].x == 0) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].x == 180) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 180) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].x == 360) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 360) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].x == 540) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 540) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].x == 720) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].x == 720) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].x += 30;
								ra[v].x -= 30;
							}
							if (ra[move].x == 180 || ra[move].x == 360 || ra[move].x == 540 || ra[move].x == 720) {
								time1 = 0;
								time = 0;
								v = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
				}
			}
			if (temp == 2) {
				if (lock == 1) {
					if (f == 1) {
						if (w == 3) {
							for (int i = 0;i < t;i++) {
								if (ra[i].x == ra[move].x) {
									if (ra[i].y == ra[move].y + 300) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].y == 600) {
								time = 1;
							}
							if (time == 0) {
								ra[move].y += 50;
							}
							if (ra[move].y == 300 || ra[move].y == 600) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							for (int i = 0;i < t;i++) {
								if (ra[i].x == ra[move].x) {
									if (ra[i].y == ra[move].y + 225) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].y == 675) {
								time = 1;
							}
							if (time == 0) {
								ra[move].y += 25;
							}
							if (ra[move].y == 225 || ra[move].y == 450 || ra[move].y == 675) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							for (int i = 0;i < t;i++) {
								if (ra[i].x == ra[move].x) {
									if (ra[i].y == ra[move].y + 180) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].y == 720) {
								time = 1;
							}
							if (time == 0) {
								ra[move].y += 30;
							}
							if (ra[move].y == 180 || ra[move].y == 360 || ra[move].y == 540 || ra[move].y == 720) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
					if (f == 3) {
						if (w == 3) {
							if (time == 0) {
								if (ra[move].y == 0) {
									for (int i = 0;i < 3;i++) {
										if (ra[i].y == 300) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 300) {
									for (int i = 0;i < 3;i++) {
										if (ra[i].y == 600) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].y == 600) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].y += 50;
								ra[v].y -= 50;
							}
							if (ra[move].y == 300 || ra[move].y == 600) {
								v = 0;
								time = 0;
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							if (time == 0) {
								if (ra[move].y == 0) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].y == 225) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 225) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].y == 450) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 450) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].y == 675) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].y == 675) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].y += 25;
								ra[v].y -= 25;
							}
							if (ra[move].y == 225 || ra[move].y == 450 || ra[move].y == 675) {
								v = 0;
								time = 0;
								time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							if (time == 0) {
								if (ra[move].y == 0) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].y == 180) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 180) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].y == 360) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 360) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].y == 540) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 540) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].y == 720) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].y == 720) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].y += 30;
								ra[v].y -= 30;
							}
							if (ra[move].y == 180 || ra[move].y == 360 || ra[move].y == 540 || ra[move].y == 720) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
				}
			}
			if (temp == 3) {
				if (lock == 1) {
					if (f == 1) {
						if (w == 3) {
							for (int i = 0;i < t;i++) {
								if (ra[i].x == ra[move].x) {
									if (ra[i].y == ra[move].y - 300) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].y == 0) {
								time = 1;
							}
							if (time == 0) {
								ra[move].y -= 50;
							}
							if (ra[move].y == 0 || ra[move].y == 300) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							for (int i = 0;i < t;i++) {
								if (ra[i].x == ra[move].x) {
									if (ra[i].y == ra[move].y - 225) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].y == 0) {
								time = 1;
							}
							if (time == 0) {
								ra[move].y -= 25;
							}
							if (ra[move].y == 0 || ra[move].y == 225 || ra[move].y == 450) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							for (int i = 0;i < t;i++) {
								if (ra[i].x == ra[move].x) {
									if (ra[i].y == ra[move].y - 180) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].y == 0) {
								time = 1;
							}
							if (time == 0) {
								ra[move].y -= 30;
							}
							if (ra[move].y == 0 || ra[move].y == 180 || ra[move].y == 360 || ra[move].y == 540) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
					if (f == 3) {
						if (w == 3) {
							if (time == 0) {
								if (ra[move].y == 300) {
									for (int i = 0;i < 3;i++) {
										if (ra[i].y == 0) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 600) {
									for (int i = 0;i < 3;i++) {
										if (ra[i].y == 300) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].y == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].y -= 50;
								ra[v].y += 50;
							}
							if (ra[move].y == 0 || ra[move].y == 300) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							if (time == 0) {
								if (ra[move].y == 225) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].y == 0) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 450) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].y == 225) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 675) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].y == 450) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].y == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].y -= 25;
								ra[v].y += 25;
							}
							if (ra[move].y == 0 || ra[move].y == 225 || ra[move].y == 450) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							if (time == 0) {
								if (ra[move].y == 180) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].y == 0) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 360) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].y == 180) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 540) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].y == 360) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].y == 720) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].y == 540) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].y == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].y -= 30;
								ra[v].y += 30;
							}
							if (ra[move].y == 0 || ra[move].y == 180 || ra[move].y == 360 || ra[move].y == 540) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
				}
			}
			if (temp == 4) {
				if (lock == 1) {
					if (f == 1) {
						if (w == 3) {
							for (int i = 0;i < t;i++) {
								if (ra[i].y == ra[move].y) {
									if (ra[i].x == ra[move].x - 300) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].x == 0) {
								time = 1;
							}
							if (time == 0) {
								ra[move].x -= 50;
							}
							if (ra[move].x == 0 || ra[move].x == 300) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							for (int i = 0;i < t;i++) {
								if (ra[i].y == ra[move].y) {
									if (ra[i].x == ra[move].x - 225) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].x == 0) {
								time = 1;
							}
							if (time == 0) {
								ra[move].x -= 25;
							}
							if (ra[move].x == 0 || ra[move].x == 225 || ra[move].x == 450) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							for (int i = 0;i < t;i++) {
								if (ra[i].y == ra[move].y) {
									if (ra[i].x == ra[move].x - 180) {
										if (i != move) {
											time++;
										}
										else {
											time = 0;
										}
									}
								}
							}
							if (ra[move].x == 0) {
								time = 1;
							}
							if (time == 0) {
								ra[move].x -= 30;
							}
							if (ra[move].x == 0 || ra[move].x == 180 || ra[move].x == 360 || ra[move].x == 540) {
								time = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
					if (f == 2) {
						if (w == 3) {
							if (time == 0) {
								if (ra[move].x == 300) {
									for (int i = 0;i < 3;i++) {
										if (ra[i].x == 0) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 600) {
									for (int i = 0;i < 3;i++) {
										if (ra[i].x == 300) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].x == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].x -= 50;
								ra[v].x += 50;
							}
							if (ra[move].x == 0 || ra[move].x == 300) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 4) {
							if (time == 0) {
								if (ra[move].x == 225) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].x == 0) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 450) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].x == 225) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 675) {
									for (int i = 0;i < 4;i++) {
										if (ra[i].x == 450) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].x == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].x -= 25;
								ra[v].x += 25;
							}
							if (ra[move].x == 0 || ra[move].x == 225 || ra[move].x == 450) {
								v = 0;
								time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
						if (w == 5) {
							if (time == 0) {
								if (ra[move].x == 180) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].x == 0) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 360) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].x == 180) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 540) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].x == 360) {
											v = i;
											break;
										}
									}
								}
								if (ra[move].x == 720) {
									for (int i = 0;i < 5;i++) {
										if (ra[i].x == 540) {
											v = i;
											break;
										}
									}
								}
								time++;
							}
							if (ra[move].x == 0) {
								time1 = 1;
							}
							if (time1 == 0) {
								ra[move].x -= 30;
								ra[v].x += 30;
							}
							if (ra[move].x == 0 || ra[move].x == 180 || ra[move].x == 360 || ra[move].x == 540) {
								v = 0;time = 0;time1 = 0;lock = 0;
								KillTimer(hwnd, 3);
							}
						}
					}
				}
			}
			break;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		KillTimer(hwnd, 2);
		KillTimer(hwnd, 3);
		KillTimer(hwnd, 4);
		DeleteObject(hbitmap1);
		DeleteObject(hbitmap2);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}