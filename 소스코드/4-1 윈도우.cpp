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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
BOOL InRect(int x1, int y1, int x2, int y2)
{
	if (360 < x2 < 440) {
		if (510 < y2 < 530) {
			return TRUE;
		}
	}
	else {
		return FALSE;
	}
}
struct rect {
	int x, y;
	int x1, y1;
	int x2 = 0, x3 = 0;
	int r, g, b;
};
struct rect re[50];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	static int x, y;
	static double dist = 0, dist1 = 0;
	static int x1, y1;
	static BOOL Selection;
	int mx;
	static RECT rectView;
	static int cng = 0, cng1 = 0, cng2 = 0;
	static int i = 0;
	static int j = 0;
	static int k = 0;
	static int s = 0, answer = 0;
	static int cnt = 0, cnt1 = 0;
	static int size = 0, len = 0, le = 0;
	static TCHAR check[20];
	switch (iMsg) {
	case WM_CREATE:
		x = 400; y = 530;
		x1 = 400; y1 = 490;
		Selection = FALSE;
		len = 3;
		le = 10;
		GetClientRect(hwnd, &rectView);
		for (int i = 0; i < len; i++) {
			for (int g = 0; g < le; g++) {
				re[k].x = 90 + 60 * g;
				re[k].x3 = re[k].x;
				re[k].x1 = 150 + 60 * g;
				re[k].x2 = re[k].x1;
				re[k].y = 0 + 30 * i;
				re[k].y1 = 30 + 30 * i;
				re[k].r = rand() % 255;
				re[k].g = rand() % 255;
				re[k].b = rand() % 255;
				k++;
			}
		}
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		Rectangle(mdc, 0, 0, rt.right, rt.bottom);
		if (Selection) {
			Rectangle(mdc, x - BSIZE, y - BSIZE / 2, x + BSIZE, y + BSIZE / 2);
		}
		hPen = CreatePen(PS_SOLID, 5, RGB(100, 100, 100));
		oldPen = (HPEN)SelectObject(mdc, hPen);
		Rectangle(mdc, x - BSIZE, y - BSIZE / 2, x + BSIZE, y + BSIZE / 2);
		SelectObject(mdc, oldPen);
		DeleteObject(hPen);
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
		Rectangle(mdc, x - BSIZE, y - BSIZE / 2, x + BSIZE, y + BSIZE / 2);
		SelectObject(mdc, oldBrush);
		DeleteObject(hBrush);
		hPen = CreatePen(PS_SOLID, 5, RGB(100, 100, 100));
		oldPen = (HPEN)SelectObject(mdc, hPen);
		Ellipse(mdc, x1 - 20 - size, y1 - 20 - size, x1 + 20 + size, y1 + 20 + size);
		SelectObject(mdc, oldPen);
		DeleteObject(hPen);
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
		Ellipse(mdc, x1 - 20 - size, y1 - 20 - size, x1 + 20 + size, y1 + 20 + size);
		SelectObject(mdc, oldBrush);
		DeleteObject(hBrush);
		for (int h = 0; h < k; h++) {
			hBrush = CreateSolidBrush(RGB(re[h].r, re[h].g, re[h].b));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Rectangle(mdc, re[h].x, re[h].y, re[h].x1, re[h].y1);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (j == 1) {
			SetBkColor(mdc, RGB(255, 255, 255));
			wsprintf(check, L"색이 변한 벽돌의 수 : %d  없어진 벽돌의 수 : %d", cnt, cnt1);
			TextOut(mdc, 250, 300, check, lstrlen(check));
		}
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_GAME_START:
			answer = MessageBox(hwnd, L"시작하시겠습니까?", L"벽돌깨기 게임", MB_YESNO);
			if (answer == IDYES) {
				SetTimer(hwnd, 1, 100 + i, NULL);
				InvalidateRect(hwnd, NULL, FALSE);
			}
			answer = 0;
			break;
		case ID_GAME_RESET:
			answer = MessageBox(hwnd, L"다시시작하시겠습니까?", L"벽돌깨기 게임", MB_YESNO);
			if (answer == IDYES) {
				KillTimer(hwnd, 1);
				x1 = 400; y1 = 490;
				cng = 0;
				cng1 = 0;
				k = 0;
				for (int i = 0; i < len; i++) {
					for (int g = 0; g < le; g++) {
						re[k].x = 90 + 60 * g;
						re[k].x3 = re[k].x;
						re[k].x1 = 150 + 60 * g;
						re[k].x2 = re[k].x1;
						re[k].y = 0 + 30 * i;
						re[k].y1 = 30 + 30 * i;
						re[k].r = rand() % 255;
						re[k].g = rand() % 255;
						re[k].b = rand() % 255;
						k++;
					}
				}
				SetTimer(hwnd, 1, 100 + i, NULL);
				InvalidateRect(hwnd, NULL, FALSE);
			}
			answer = 0;
			break;
		case ID_GAME_END:
			KillTimer(hwnd, 1);
			PostQuitMessage(0);
			break;
		case ID_SPEED_FAST:
			i = -70;
			SetTimer(hwnd, 1, 100 + i, NULL);
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_SPEED_MEDIUM:
			i = 0;
			SetTimer(hwnd, 1, 100 + i, NULL);
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_SPEED_SLOW:
			i = 30;
			SetTimer(hwnd, 1, 100 + i, NULL);
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_COLOR_GREEN:
			k = 0;
			for (int i = 0; i < len; i++) {
				for (int g = 0; g < le; g++) {
					re[k].r = 0;
					re[k].g = 255;
					re[k].b = 0;
					k++;
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_COLOR_PURPLE:
			k = 0;
			for (int i = 0; i < len; i++) {
				for (int g = 0; g < le; g++) {
					re[k].r = 255;
					re[k].g = 0;
					re[k].b = 255;
					k++;
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_COLOR_YELLOW:
			k = 0;
			for (int i = 0; i < len; i++) {
				for (int g = 0; g < le; g++) {
					re[k].r = 255;
					re[k].g = 255;
					re[k].b = 0;
					k++;
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_COLOR_RANDOM:
			k = 0;
			for (int i = 0; i < len; i++) {
				for (int g = 0; g < le; g++) {
					re[k].r = rand() % 255;
					re[k].g = rand() % 255;
					re[k].b = rand() % 255;
					k++;
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_SIZE_BIG:
			size = 10;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_SIZE_SMALL:
			size = -10;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_LINE_3:
			len = 3;
			k = 0;
			for (int i = 0; i < len; i++) {
				for (int g = 0; g < le; g++) {
					re[k].x = 90 + 60 * g;
					re[k].x3 = re[k].x;
					re[k].x1 = 150 + 60 * g;
					re[k].x2 = re[k].x1;
					re[k].y = 0 + 30 * i;
					re[k].y1 = 30 + 30 * i;
					re[k].r = rand() % 255;
					re[k].g = rand() % 255;
					re[k].b = rand() % 255;
					k++;
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_LINE_4:
			len = 4;
			k = 0;
			for (int i = 0; i < len; i++) {
				for (int g = 0; g < le; g++) {
					re[k].x = 90 + 60 * g;
					re[k].x3 = re[k].x;
					re[k].x1 = 150 + 60 * g;
					re[k].x2 = re[k].x1;
					re[k].y = 0 + 30 * i;
					re[k].y1 = 30 + 30 * i;
					re[k].r = rand() % 255;
					re[k].g = rand() % 255;
					re[k].b = rand() % 255;
					k++;
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case ID_LINE_5:
			len = 5;
			k = 0;
			for (int i = 0; i < len; i++) {
				for (int g = 0; g < le; g++) {
					re[k].x = 90 + 60 * g;
					re[k].x3 = re[k].x;
					re[k].x1 = 150 + 60 * g;
					re[k].x2 = re[k].x1;
					re[k].y = 0 + 30 * i;
					re[k].y1 = 30 + 30 * i;
					re[k].r = rand() % 255;
					re[k].g = rand() % 255;
					re[k].b = rand() % 255;
					k++;
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		if (InRect(x, y, mx, y))
			Selection = TRUE;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		Selection = FALSE;
		x = 400;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		if (Selection) {
			x = mx;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == 'p' || wParam == 'P') {
			if (j == 0) {
				KillTimer(hwnd, 1);
				j++;
			}
			else if (j == 1) {
				SetTimer(hwnd, 1, 100 + i, NULL);
				j--;
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		break;
	case WM_TIMER:
		if (cng2 % 2 == 0) {
			for (int g = 0; g < le * len; g++) {
				re[g].x += 20;
				re[g].x1 += 20;
				re[g].x2 += 20;
				re[g].x3 += 20;
			}
			if (re[9].x2 > 780) {
				cng2++;
			}
		}
		if (cng2 % 2 == 1) {
			for (int g = 0; g < le * len; g++) {
				re[g].x -= 20;
				re[g].x1 -= 20;
				re[g].x2 -= 20;
				re[g].x3 -= 20;
			}
			if (re[0].x3 < 20) {
				cng2++;
			}
		}
		for (int h = k - 1; h > -1; h--) {
			if (re[h].x1 <= x1 && x1 <= re[h].x1 + 20 + size) {
				if (re[h].y <= y1 && y1 <= re[h].y1) {
					re[h].x += 10;
					re[h].x1 -= 10;
					re[h].y += 1.5;
					re[h].y1 -= 1.5;
					re[h].r = rand() % 255;
					re[h].g = rand() % 255;
					re[h].b = rand() % 255;
					cnt++;
					if (re[h].x == re[h].x1) {
						re[h].x = -100;
						re[h].x1 = -100;
						re[h].y = -100;
						re[h].y1 = -100;
						re[h].r = 0;
						re[h].g = 0;
						re[h].b = 0;
						cnt1++;
					}
					cng++;
					continue;
				}
				dist = sqrt((x1 - re[h].x1) * (x1 - re[h].x1) - (y1 - re[h].y) * (y1 - re[h].y));
				if (dist <= 20 + size) {
					re[h].x += 10;
					re[h].x1 -= 10;
					re[h].y += 1.5;
					re[h].y1 -= 1.5;
					re[h].r = rand() % 255;
					re[h].g = rand() % 255;
					re[h].b = rand() % 255;
					cnt++;
					if (re[h].x == re[h].x1) {
						re[h].x = -100;
						re[h].x1 = -100;
						re[h].y = -100;
						re[h].y1 = -100;
						re[h].r = 0;
						re[h].g = 0;
						re[h].b = 0;
						cnt1++;
					}
					cng1++;
					continue;
				}
				dist1 = sqrt((x1 - re[h].x1) * (x1 - re[h].x1) - (y1 - re[h].y1) * (y1 - re[h].y1));
				if (dist1 <= 20 + size) {
					re[h].x += 10;
					re[h].x1 -= 10;
					re[h].y += 1.5;
					re[h].y1 -= 1.5;
					re[h].r = rand() % 255;
					re[h].g = rand() % 255;
					re[h].b = rand() % 255;
					cnt++;
					if (re[h].x == re[h].x1) {
						re[h].x = -100;
						re[h].x1 = -100;
						re[h].y = -100;
						re[h].y1 = -100;
						re[h].r = 0;
						re[h].g = 0;
						re[h].b = 0;
						cnt1++;
					}
					cng1++;
					continue;
				}
			}
		}
		for (int h = k - 1; h > -1; h--) {
			if (re[h].x - 20 - size <= x1 && x1 <= re[h].x) {
				if (re[h].y <= y1 && y1 <= re[h].y1) {
					re[h].x += 10;
					re[h].x1 -= 10;
					re[h].y += 1.5;
					re[h].y1 -= 1.5;
					re[h].r = rand() % 255;
					re[h].g = rand() % 255;
					re[h].b = rand() % 255;
					cnt++;
					if (re[h].x == re[h].x1) {
						re[h].x = -100;
						re[h].x1 = -100;
						re[h].y = -100;
						re[h].y1 = -100;
						re[h].r = 0;
						re[h].g = 0;
						re[h].b = 0;
						cnt1++;
					}
					cng++;
					continue;
				}
				dist = sqrt((x1 - re[h].x) * (x1 - re[h].x) - (y1 - re[h].y) * (y1 - re[h].y));
				if (dist <= 20 + size) {
					re[h].x += 10;
					re[h].x1 -= 10;
					re[h].y += 1.5;
					re[h].y1 -= 1.5;
					re[h].r = rand() % 255;
					re[h].g = rand() % 255;
					re[h].b = rand() % 255;
					cnt++;
					if (re[h].x == re[h].x1) {
						re[h].x = -100;
						re[h].x1 = -100;
						re[h].y = -100;
						re[h].y1 = -100;
						re[h].r = 0;
						re[h].g = 0;
						re[h].b = 0;
						cnt1++;
					}
					cng1++;
					continue;
				}
				dist1 = sqrt((x1 - re[h].x) * (x1 - re[h].x) - (y1 - re[h].y1) * (y1 - re[h].y1));
				if (dist1 <= 20 + size) {
					re[h].x += 10;
					re[h].x1 -= 10;
					re[h].y += 1.5;
					re[h].y1 -= 1.5;
					re[h].r = rand() % 255;
					re[h].g = rand() % 255;
					re[h].b = rand() % 255;
					cnt++;
					if (re[h].x == re[h].x1) {
						re[h].x = -100;
						re[h].x1 = -100;
						re[h].y = -100;
						re[h].y1 = -100;
						re[h].r = 0;
						re[h].g = 0;
						re[h].b = 0;
						cnt1++;
					}
					cng1++;
					continue;
				}
			}
		}
		for (int h = k - 1; h > -1; h--) {
			if (re[h].y1 <= y1 && y1 <= re[h].y1 + 20 + size) {
				if (re[h].x <= x1 && x1 <= re[h].x1) {
					re[h].x += 10;
					re[h].x1 -= 10;
					re[h].y += 1.5;
					re[h].y1 -= 1.5;
					re[h].r = rand() % 255;
					re[h].g = rand() % 255;
					re[h].b = rand() % 255;
					cnt++;
					if (re[h].x == re[h].x1) {
						re[h].x = -100;
						re[h].x1 = -100;
						re[h].y = -100;
						re[h].y1 = -100;
						re[h].r = 0;
						re[h].g = 0;
						re[h].b = 0;
						cnt1++;
					}
					cng1++;
					continue;
				}
			}
		}
		for (int h = k - 1; h > -1; h--) {
			if (re[h].y - 20 - size <= y1 && y1 <= re[h].y) {
				if (re[h].x <= x1 && x1 <= re[h].x1) {
					re[h].x += 10;
					re[h].x1 -= 10;
					re[h].y += 1.5;
					re[h].y1 -= 1.5;
					re[h].r = rand() % 255;
					re[h].g = rand() % 255;
					re[h].b = rand() % 255;
					cnt++;
					if (re[h].x == re[h].x1) {
						re[h].x = -100;
						re[h].x1 = -100;
						re[h].y = -100;
						re[h].y1 = -100;
						re[h].r = 0;
						re[h].g = 0;
						re[h].b = 0;
						cnt1++;
					}
					cng1++;
					continue;
				}
			}
		}
		if (cng % 2 == 0) {
			x1 += 10;
		}
		else if (cng % 2 == 1) {
			x1 -= 10;
		}
		if (x1 + 20 + size > rectView.right - 10) {
			cng++;
		}
		if (x1 - 20 - size < rectView.left + 10) {
			cng++;
		}
		if (cng1 % 2 == 0) {
			y1 -= 10;
		}
		else if (cng1 % 2 == 1) {
			y1 += 10;
		}
		if (y1 - 20 - size < 10) {
			cng1++;
		}
		if (y1 + 20 + size > 500) {
			if (x - 40 <= x1) {
				if (x1 <= x + 40) {
					cng1++;
				}
			}
		}
		if (y1 - 20 > rectView.bottom) {
			x1 = x;
			y1 = 490;
			cng1++;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
