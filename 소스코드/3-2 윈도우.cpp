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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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
	int r, g, b;
};
struct rect re[30];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {// 시간조절이 문제
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static int x, y;
	static int x1, y1;
	static BOOL Selection;
	int mx;
	static RECT rectView;
	static int cng = 0, cng1 = 0, cng2 = 0;
	static int i = 0;
	static int j = 0;
	static int k = 0;
	static int s = 0;
	static int cnt = 0, cnt1 = 0;
	static TCHAR check[20];
	switch (iMsg) {
	case WM_CREATE:
		x = 400; y = 530;
		x1 = 400; y1 = 490;
		Selection = FALSE;
		GetClientRect(hwnd, &rectView);
		for (int i = 0; i < 3; i++) {
			for (int g = 0; g < 10; g++) {
				re[k].x = 90 + 60 * g;
				re[k].x1 = 150 + 60 * g;
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
		hdc = BeginPaint(hwnd, &ps);
		if (Selection) {
			Rectangle(hdc, x - BSIZE, y - BSIZE / 2, x + BSIZE, y + BSIZE / 2);
		}
		hPen = CreatePen(PS_SOLID, 5, RGB(100, 100, 100));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Rectangle(hdc, x - BSIZE, y - BSIZE / 2, x + BSIZE, y + BSIZE / 2);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, x - BSIZE, y - BSIZE / 2, x + BSIZE, y + BSIZE / 2);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hPen = CreatePen(PS_SOLID, 5, RGB(100, 100, 100));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Ellipse(hdc, x1 - 20, y1 - 20, x1 + 20, y1 + 20);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, x1 - 20, y1 - 20, x1 + 20, y1 + 20);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		for (int h = 0; h < k; h++) {
			hBrush = CreateSolidBrush(RGB(re[h].r, re[h].g, re[h].b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[h].x, re[h].y, re[h].x1, re[h].y1);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (j == 1) {
			SetBkColor(hdc, RGB(255, 255, 255));
			wsprintf(check, L"색이 변한 벽돌의 수 : %d  없어진 벽돌의 수 : %d", cnt, cnt1);
			TextOut(hdc, 250, 300, check, lstrlen(check));
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		if (InRect(x, y, mx, y))
			Selection = TRUE;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		Selection = FALSE;
		x = 400;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		if (Selection) {
			x = mx;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == 's' || wParam == 'S') {
			SetTimer(hwnd, 1, 100 + i, NULL);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		else if (wParam == 'p' || wParam == 'P') {
			if (j == 0) {
				KillTimer(hwnd, 1);
				j++;
			}
			else if (j == 1) {
				SetTimer(hwnd, 1, 100 + i, NULL);
				j--;
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		else if (wParam == VK_F3) {
			i -= 10;
			if (i == -90) {
				i += 10;
			}
			SetTimer(hwnd, 1, 100 + i, NULL);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		else if (wParam == VK_F2) {
			i += 10;
			if (i == 90) {
				i -= 10;
			}
			SetTimer(hwnd, 1, 100 + i, NULL);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		else if (wParam == 'n' || wParam == 'N') {
			KillTimer(hwnd, 1);
			x1 = 400; y1 = 490;
			cng = 0;
			cng1 = 0;
			k = 0;
			for (int i = 0; i < 3; i++) {
				for (int g = 0; g < 10; g++) {
					re[k].x = 90 + 60 * g;
					re[k].x1 = 150 + 60 * g;
					re[k].y = 0 + 30 * i;
					re[k].y1 = 30 + 30 * i;
					re[k].r = rand() % 255;
					re[k].g = rand() % 255;
					re[k].b = rand() % 255;
					k++;
				}
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		else if (wParam == 'q' || wParam == 'Q') {
			KillTimer(hwnd, 1);
			PostQuitMessage(0);
		}
		break;
	case WM_TIMER:
		if (cng2 % 2 == 0) {
			for (int g = 0; g < 30; g++) {
				re[g].x += 20;
				re[g].x1 += 20;
			}
			if (re[9].x1 > 780) {
				cng2++;
			}
		}
		if (cng2 % 2 == 1) {
			for (int g = 0; g < 30; g++) {
				re[g].x -= 20;
				re[g].x1 -= 20;
			}
			if (re[0].x < 20) {
				cng2++;
			}
		}
		if (cng % 2 == 0) {
			x1 += 10;
		}
		else if (cng % 2 == 1) {
			x1 -= 10;
		}
		for (int h = 0; h < k; h++) {
			if (x1 - 20 == re[h].x1) {
				if (re[h].y + 10 < y1) {
					if (y1 < re[h].y1 + 10) {
						re[h].x += 10;
						re[h].x1 -= 10;
						re[h].y += 1.5;
						re[h].y1 -= 1.5;
						re[h].r = rand() % 255;
						re[h].g = rand() % 255;
						re[h].b = rand() % 255;
						cnt++;
						if (re[h].x == re[h].x1) {
							re[h].x = 0;
							re[h].x1 = 0;
							re[h].y = 0;
							re[h].y1 = 0;
							re[h].r = 0;
							re[h].g = 0;
							re[h].b = 0;
							cnt1++;
						}
						cng++;
					}
				}
			}
		}
		for (int h = 0; h < k; h++) {
			if (x1 + 20 == re[h].x) {
				if (re[h].y + 10 < y1) {
					if (y1 < re[h].y1 + 10) {
						re[h].x += 10;
						re[h].x1 -= 10;
						re[h].y += 1.5;
						re[h].y1 -= 1.5;
						re[h].r = rand() % 255;
						re[h].g = rand() % 255;
						re[h].b = rand() % 255;
						cnt++;
						if (re[h].x == re[h].x1) {
							re[h].x = 0;
							re[h].x1 = 0;
							re[h].y = 0;
							re[h].y1 = 0;
							re[h].r = 0;
							re[h].g = 0;
							re[h].b = 0;
							cnt1++;
						}
						cng++;
					}
				}
			}
		}
		if (x1 + 20 > rectView.right - 10) {
			cng++;
		}
		if (x1 - 20 < rectView.left + 10) {
			cng++;
		}
		if (cng1 % 2 == 0) {
			y1 -= 10;
		}
		else if (cng1 % 2 == 1) {
			y1 += 10;
		}
		for (int h = 0; h < k; h++) {
			if (y1 - 20 == re[h].y1) {
				if (re[h].x < x1) {
					if (x1 < re[h].x1) {
						re[h].x += 10;
						re[h].x1 -= 10;
						re[h].y += 1.5;
						re[h].y1 -= 1.5;
						re[h].r = rand() % 255;
						re[h].g = rand() % 255;
						re[h].b = rand() % 255;
						cnt++;
						if (re[h].x == re[h].x1) {
							re[h].x = 0;
							re[h].x1 = 0;
							re[h].y = 0;
							re[h].y1 = 0;
							re[h].r = 0;
							re[h].g = 0;
							re[h].b = 0;
							cnt1++;
						}
						cng1++;
					}
				}
			}
		}
		if (y1 - 20 < 10) {
			cng1++;
		}
		if (y1 + 20 > 500) {
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
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
