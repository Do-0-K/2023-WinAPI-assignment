#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
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
	int shape;
	int x, y;
	int x1, y1;
	int r, g, b;
	int m, n;
};
struct rect re[900];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static int k = 0, j = 0, l = 0;
	static int w = 0, p = 0;
	switch (iMsg) {
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == 's' || wParam == 'S') {
			w = 3;
			l = 0; j = 0; k = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'm' || wParam == 'M') {
			w = 4;
			l = 0; j = 0; k = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'l' || wParam == 'L') {
			w = 5;
			l = 0; j = 0; k = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'e' || wParam == 'E') {
			if (k > 9) {
				for (int i = 0; i < k; i++) {
					re[i] = re[i + 1];
				}
			}
			re[k].shape = 1;
			re[k].r = rand() % 255;
			re[k].g = rand() % 255;
			re[k].b = rand() % 255;
			re[k].x = rand() % 29 + 1;
			re[k].y = rand() % 29 + 1;
			re[k].m = 0;
			re[k].n = 0;
			k++;
			l = 0; j = 0; p = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 't' || wParam == 'T') {
			if (k > 9) {
				for (int i = 0; i < k; i++) {
					re[i] = re[i + 1];
				}
			}
			re[k].shape = 2;
			re[k].r = rand() % 255;
			re[k].g = rand() % 255;
			re[k].b = rand() % 255;
			re[k].x = rand() % 29 + 1;
			re[k].y = rand() % 29 + 1;
			re[k].m = 0;
			re[k].n = 0;
			k++;
			l = 0; j = 0; p = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'R' || wParam == 'r') {
			if (k > 9) {
				for (int i = 0; i < k; i++) {
					re[i] = re[i + 1];
				}
			}
			re[k].shape = 3;
			re[k].r = rand() % 255;
			re[k].g = rand() % 255;
			re[k].b = rand() % 255;
			re[k].x = rand() % 29 + 1;
			re[k].y = rand() % 29 + 1;
			re[k].m = 0;
			re[k].n = 0;
			k++;
			l = 0; j = 0; p = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_RIGHT) {
			re[p].x++;
			j = 0; l = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_LEFT) {
			re[p].x--;
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_UP) {
			re[p].y--;
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_DOWN) {
			re[p].y++;
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'c' || wParam == 'C') {
			int z = 0;
			z = re[p].shape;
			re[p].r = rand() % 255;
			re[p].g = rand() % 255;
			re[p].b = rand() % 255;
			for (int i = 0; i < k; i++) {
				if (re[i].shape == z) {
					re[i].r = re[p].r;
					re[i].g = re[p].g;
					re[i].b = re[p].b;
				}
			}
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'd' || wParam == 'D') {
			re[p].shape = 0;
			int z = 0;
			for (int i = 0; i < k; i++) {
				if (re[i].shape == 0) {
					z = i;
				}
			}
			for (int i = z; i < k; i++) {
				re[i] = re[i+1];
			}
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'p' || wParam == 'P') {
			k = 0; p = 0; j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == '+') {
			re[p].m++;
			re[p].n++;
			if (re[p].m > 5 && re[p].n > 5) {
				re[p].m--;
				re[p].n--;
			}
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '-') {
			re[p].m--;
			re[p].n--;
			if (re[p].m < 0 && re[p].n < 0) {
				re[p].m++;
				re[p].n++;
			}
			j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '1') {
			p = 1-1;j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '2') {
			p = 2-1;j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '3') {
			p = 3-1;j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '4') {
			p = 4-1;j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '5') {
			p = 5-1;j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '6') {
			p = 6-1;j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '7') {
			p = 7-1;j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '8') {
			p = 8-1;j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '9') {
			p = 9-1;j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		if (wParam == '0') {
			p = 10 - 1;j = 0; l = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		if (w == 3) {
			for (int i = 0; i < 900; i++) {
				if (i % 30 == 0) {
					l = 0;
					j++;
				}
				POINT point0[8] = { {0 + l * 25,0 + j * 25},{25 + l * 25,0 + j * 25}, {25 + l * 25, 25 + j * 25} ,{0 + l * 25, 25 + j * 25} };
				hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				oldPen = (HPEN)SelectObject(hdc, hPen);
				Polygon(hdc, point0, 4);
				SelectObject(hdc, oldPen);
				DeleteObject(hPen);
				l++;
			}
			for (int g = 0; g < k; g++) {
				if (re[g].shape == 1) {
					hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Ellipse(hdc, 0 + re[g].x * 25 + re[g].m, 0 + re[g].y * 25 + re[g].n, 25 + re[g].x * 25 - re[g].m, 25 + re[g].y * 25 - re[g].n);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				if (re[g].shape == 2) {
					POINT point0[6] = { {0 + re[g].x * 25 + re[g].m,25 + re[g].y * 25 - re[g].n},{25 + re[g].x * 25 - re[g].m,25 + re[g].y * 25 - re[g].n}, {12.5 + re[g].x * 25, 0 + re[g].y * 25 + re[g].n} };
					hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Polygon(hdc, point0, 3);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				if (re[g].shape == 3) {
					hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, 0 + re[g].x * 25 + re[g].m, 0 + re[g].y * 25 + re[g].n, 25 + re[g].x * 25 - re[g].m, 25 + re[g].y * 25 - re[g].n);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
			}
			for (int g = 0; g < k; g++) {
				if (g == p) {
					if (re[g].shape == 1) {
						hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						Ellipse(hdc, 0 + re[g].x * 25 + re[g].m, 0 + re[g].y * 25 + re[g].n, 25 + re[g].x * 25 - re[g].m, 25 + re[g].y * 25 - re[g].n);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
						hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						Ellipse(hdc, 0 + re[g].x * 25 + re[g].m, 0 + re[g].y * 25 + re[g].n, 25 + re[g].x * 25 - re[g].m, 25 + re[g].y * 25 - re[g].n);
						SelectObject(hdc, oldBrush);
						DeleteObject(hBrush);
					}
					if (re[g].shape == 2) {
						POINT point0[6] = { {0 + re[g].x * 25 + re[g].m,25 + re[g].y * 25 - re[g].n},{25 + re[g].x * 25 - re[g].m,25 + re[g].y * 25 - re[g].n}, {12.5 + re[g].x * 25, 0 + re[g].y * 25 + re[g].n} };
						hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						Polygon(hdc, point0, 3);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
						hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						Polygon(hdc, point0, 3);
						SelectObject(hdc, oldBrush);
						DeleteObject(hBrush);
					}
					if (re[g].shape == 3) {
						hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						Rectangle(hdc, 0 + re[g].x * 25 + re[g].m, 0 + re[g].y * 25 + re[g].n, 25 + re[g].x * 25 - re[g].m, 25 + re[g].y * 25 - re[g].n);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
						hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						Rectangle(hdc, 0 + re[g].x * 25 + re[g].m, 0 + re[g].y * 25 + re[g].n, 25 + re[g].x * 25 - re[g].m, 25 + re[g].y * 25 - re[g].n);
						SelectObject(hdc, oldBrush);
						DeleteObject(hBrush);
					}
				}
			}
		}
		if (w == 4) {
			for (int i = 0; i < 1600; i++) {
				if (i % 40 == 0) {
					l = 0;
					j++;
				}
				POINT point0[8] = { {0 + l * 20,0 + j * 20},{20 + l * 20,0 + j * 20}, {20 + l * 20, 20 + j * 20} ,{0 + l * 20, 20 + j * 20} };
				hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				oldPen = (HPEN)SelectObject(hdc, hPen);
				Polygon(hdc, point0, 4);
				SelectObject(hdc, oldPen);
				DeleteObject(hPen);
				l++;
			}
			for (int g = 0; g < k; g++) {
				if (re[g].shape == 1) {
					hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Ellipse(hdc, 0 + re[g].x * 20 + re[g].m, 0 + re[g].y * 20 + re[g].n, 20 + re[g].x * 20 - re[g].m, 20 + re[g].y * 20 - re[g].n);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				if (re[g].shape == 2) {
					POINT point0[6] = { {0 + re[g].x * 20 + re[g].m,20 + re[g].y * 20 - re[g].n},{20 + re[g].x * 20 - re[g].m,20 + re[g].y * 20 - re[g].n}, {10 + re[g].x * 20, 0 + re[g].y * 20 + re[g].n} };
					hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Polygon(hdc, point0, 3);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				if (re[g].shape == 3) {
					hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, 0 + re[g].x * 20 + re[g].m, 0 + re[g].y * 20 + re[g].n, 20 + re[g].x * 20 - re[g].m, 20 + re[g].y * 20 - re[g].n);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
			}
			for (int g = 0; g < k; g++) {
				if (g == p) {
					if (re[g].shape == 1) {
						hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						Ellipse(hdc, 0 + re[g].x * 20 + re[g].m, 0 + re[g].y * 20 + re[g].n, 20 + re[g].x * 20 - re[g].m, 20 + re[g].y * 20 - re[g].n);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
						hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						Ellipse(hdc, 0 + re[g].x * 20 + re[g].m, 0 + re[g].y * 20 + re[g].n, 20 + re[g].x * 20 - re[g].m, 20 + re[g].y * 20 - re[g].n);
						SelectObject(hdc, oldBrush);
						DeleteObject(hBrush);
					}
					if (re[g].shape == 2) {
						POINT point0[6] = { {0 + re[g].x * 20 + re[g].m,20 + re[g].y * 20 - re[g].n},{20 + re[g].x * 20 - re[g].m,20 + re[g].y * 20 - re[g].n}, {10 + re[g].x * 20, 0 + re[g].y * 20 + re[g].n} };
						hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						Polygon(hdc, point0, 3);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
						hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						Polygon(hdc, point0, 3);
						SelectObject(hdc, oldBrush);
						DeleteObject(hBrush);
					}
					if (re[g].shape == 3) {
						hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						Rectangle(hdc, 0 + re[g].x * 20 + re[g].m, 0 + re[g].y * 20 + re[g].n, 20 + re[g].x * 20 - re[g].m, 20 + re[g].y * 20 - re[g].n);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
						hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						Rectangle(hdc, 0 + re[g].x * 20 + re[g].m, 0 + re[g].y * 20 + re[g].n, 20 + re[g].x * 20 - re[g].m, 20 + re[g].y * 20 - re[g].n);
						SelectObject(hdc, oldBrush);
						DeleteObject(hBrush);
					}
				}
			}
		}
		if (w == 5) {
			for (int i = 0; i < 2500; i++) {
				if (i % 50 == 0) {
					l = 0;
					j++;
				}
				POINT point0[8] = { {0 + l * 15,0 + j * 15},{15 + l * 15,0 + j * 15}, {15 + l * 15, 15 + j * 15} ,{0 + l * 15, 15 + j * 15} };
				hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				oldPen = (HPEN)SelectObject(hdc, hPen);
				Polygon(hdc, point0, 4);
				SelectObject(hdc, oldPen);
				DeleteObject(hPen);
				l++;
			}
			for (int g = 0; g < k; g++) {
				if (re[g].shape == 1) {
					hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Ellipse(hdc, 0 + re[g].x * 15 + re[g].m, 0 + re[g].y * 15 + re[g].n, 15 + re[g].x * 15 - re[g].m, 15 + re[g].y * 15 - re[g].n);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				if (re[g].shape == 2) {
					POINT point0[6] = { {0 + re[g].x * 15 + re[g].m,15 + re[g].y * 15 - re[g].n},{15 + re[g].x * 15 - re[g].m,15 + re[g].y * 15 - re[g].n}, {7.5 + re[g].x * 15, 0 + re[g].y * 15 + re[g].n} };
					hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Polygon(hdc, point0, 3);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				if (re[g].shape == 3) {
					hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, 0 + re[g].x * 15 + re[g].m, 0 + re[g].y * 15 + re[g].n, 15 + re[g].x * 15 - re[g].m, 15 + re[g].y * 15 - re[g].n);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
			}
			for (int g = 0; g < k; g++) {
				if (g == p) {
					if (re[g].shape == 1) {
						hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						Ellipse(hdc, 0 + re[g].x * 15 + re[g].m, 0 + re[g].y * 15 + re[g].n, 15 + re[g].x * 15 - re[g].m, 15 + re[g].y * 15 - re[g].n);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
						hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						Ellipse(hdc, 0 + re[g].x * 15 + re[g].m, 0 + re[g].y * 15 + re[g].n, 15 + re[g].x * 15 - re[g].m, 15 + re[g].y * 15 - re[g].n);
						SelectObject(hdc, oldBrush);
						DeleteObject(hBrush);
					}
					if (re[g].shape == 2) {
						POINT point0[6] = { {0 + re[g].x * 15 + re[g].m,15 + re[g].y * 15 - re[g].n},{15 + re[g].x * 15 - re[g].m,15 + re[g].y * 15 - re[g].n}, {7.5 + re[g].x * 15, 0 + re[g].y * 15 + re[g].n} };
						hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						Polygon(hdc, point0, 3);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
						hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						Polygon(hdc, point0, 3);
						SelectObject(hdc, oldBrush);
						DeleteObject(hBrush);
					}
					if (re[g].shape == 3) {
						hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
						Rectangle(hdc, 0 + re[g].x * 15 + re[g].m, 0 + re[g].y * 15 + re[g].n, 15 + re[g].x * 15 - re[g].m, 15 + re[g].y * 15 - re[g].n);
						SelectObject(hdc, oldPen);
						DeleteObject(hPen);
						hBrush = CreateSolidBrush(RGB(re[g].r, re[g].g, re[g].b));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						Rectangle(hdc, 0 + re[g].x * 15 + re[g].m, 0 + re[g].y * 15 + re[g].n, 15 + re[g].x * 15 - re[g].m, 15 + re[g].y * 15 - re[g].n);
						SelectObject(hdc, oldBrush);
						DeleteObject(hBrush);
					}
				}
			}
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}