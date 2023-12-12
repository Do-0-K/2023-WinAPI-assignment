#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<string.h>
#include<math.h>
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
	int cat = 0;
	int move = -100;
	int cng1 = 0;
	int cng2 = 0;
	int cng3 = 0;
	int cng4 = 0;
};
struct rect re[60];
struct head {
	int x = -100, y = -100;
	int r = 0, g = 0, b = 0;
	int direct = 0;
};
struct head he[20];
struct wall {
	int x = -100, y = -100;
};
struct wall wa[20];
float LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
BOOL InCircle(int x1, int y1, int x2, int y2) {
	if (LengthPts(x1, y1, x2, y2) < 20)
		return TRUE;
	else
		return FALSE;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc{};
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static BOOL Selection;
	static BOOL Selection1;
	static int x, y;
	static int x1, y1;
	int mx = 0, my = 0;
	static RECT rectView;
	static int cng = 0;
	static int i = 0;
	static int j = 0;
	static int k = 0, k1 = 0;
	static int  l = 0;
	static int p = 0, p1 = 0;
	static int n = 1, n1 = 1;
	static int end = 0;
	static int g = 0, v = 0, v1 = 0;
	static int temp = 1;
	static int jum = 0, t = 0, t1 = 0, t2 = 0;
	static int move = 0;
	static int r = 0, g1 = 0, b = 0;
	static TCHAR lose[25] = L"GAME OVER";
	static TCHAR ballcheck[25];
	static TCHAR rule[25] = L"¸öÅë¿¡ ´êÀ¸¸é Á×´Â´Ù.";
	switch (iMsg) {
	case WM_CREATE:
		he[0].x = 10; he[0].y = 30;
		GetClientRect(hwnd, &rectView);
		for (int i = 0; i < 20; i++) {
			re[i].x = 10 + rand() % 40 * 20;
			re[i].y = 30 + rand() % 40 * 20;
			re[i].r = rand() % 255;
			re[i].g = rand() % 255;
			re[i].b = rand() % 255;
		}
		he[0].r = rand() % 255;
		he[0].g = rand() % 255;
		he[0].b = rand() % 255;
		end = 0;
		Selection = FALSE;
		Selection1 = FALSE;
		k1 = 0;
		p1 = 0;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
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
		for (int i = 0; i < 60; i++) {
			if (re[i].cat < 2) {
				if (re[i].cat == 0) {
					hBrush = CreateSolidBrush(RGB(re[i].r, re[i].g, re[i].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, re[i].x - 5, re[i].y - 5, re[i].x + 5, re[i].y + 5);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				if (re[i].cat == 1) {
					hBrush = CreateSolidBrush(RGB(re[i].r, re[i].g, re[i].b));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Ellipse(hdc, re[i].x - 10, re[i].y - 10, re[i].x + 10, re[i].y + 10);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
			}
		}
		for (int i = 0; i < 20; i++) {
			hBrush = CreateSolidBrush(RGB(he[i].r, he[i].g, he[i].b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, he[i].x - 10, he[i].y - 10, he[i].x + 10, he[i].y + 10);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (t2 >= 1) {
			for (int i = 0; i < 20; i++) {
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, wa[i].x - 10, wa[i].y - 10, wa[i].x + 10, wa[i].y + 10);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
			}
		}
		if (Selection) {
			hBrush = CreateSolidBrush(RGB(he[0].r, he[0].g, he[0].b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, he[0].x - 80, he[0].y - 80, he[0].x + 80, he[0].y + 80);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		wsprintf(ballcheck, L"°ø °³¼ö : %d", n);
		TextOut(hdc, 830, 100, ballcheck, lstrlen(ballcheck));
		TextOut(hdc, 810, 150, rule, lstrlen(rule));
		if (end == 2) {
			SetBkColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, 830, 200, lose, lstrlen(lose));
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (InCircle(he[0].x, he[0].y, mx, my)) {
			Selection = TRUE;
			break;
		}
		else {
			if (he[0].x <= mx) {
				if (he[0].y <= my) {
					cng = 0;
					temp = (abs(mx - he[0].x)) > (abs(my - he[0].y)) ? 1 : 4;
				}
				if (he[0].y >= my) {
					cng = 0;
					temp = (abs(mx - he[0].x)) > (abs(my - he[0].y)) ? 1 : 3;
				}
			}
			else if (he[0].x >= mx) {
				if (he[0].y <= my) {
					cng = 0;
					temp = (abs(mx - he[0].x)) > (abs(my - he[0].y)) ? 2 : 4;
				}
				if (he[0].y >= my) {
					cng = 0;
					temp = (abs(mx - he[0].x)) > (abs(my - he[0].y)) ? 2 : 3;
				}
			}
		}
		for (int i = 1; i <= n - 1; i++) {
			if (InCircle(he[i].x, he[i].y, mx, my)) {
				p1 = i;
				break;
			}
		}
		for (int i = p1; i < n; i++) {
			re[20 + k1].x = he[i].x;
			re[20 + k1].y = he[i].y;
			re[20 + k1].r = he[i].r;
			re[20 + k1].g = he[i].g;
			re[20 + k1].b = he[i].b;
			re[20 + k1].cat = 1;
			re[20 + k1].cng1 = 0;
			re[20 + k1].cng2 = 0;
			re[20 + k1].cng3 = 0;
			re[20 + k1].cng4 = 0;
			re[20 + k1].move = rand() % 4;
			he[i] = he[n];
			k1++;
		}
		n = p1;
		l = 0; j = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		x1 = mx;
		y1 = my;
		Selection = FALSE;
		Selection1 = FALSE;
		l = 0; j = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_RBUTTONDOWN:
		if (t2 > 17) {
			for (int i = 0; i < t2; i++) {
				wa[i] = wa[i + 1];
			}
		}
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		x1 = mx;
		v = x1 / 20;
		wa[t2].x = (0 + 20 * v + 20 + 20 * v) / 2;
		y1 = my;
		v = y1 / 20;
		wa[t2].y = (0 + 20 * v + 20 + 20 * v) / 2;
		t2++;
		l = 0; j = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == 's' || wParam == 'S') {
			SetTimer(hwnd, 1, 100, NULL);
			l = 0; j = 0;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (wParam == VK_F3) {
			i -= 10;
			if (i == -90) {
				i += 10;
			}
			j = 0;
			SetTimer(hwnd, 1, 100 + i, NULL);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (wParam == VK_F2) {
			i += 10;
			if (i == 90) {
				i -= 10;
			}
			j = 0;
			SetTimer(hwnd, 1, 100 + i, NULL);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (wParam == 'q' || wParam == 'Q') {
			KillTimer(hwnd, 1);
			PostQuitMessage(0);
		}
		else if (wParam == 'j' || wParam == 'J') {
			jum++;
			l = 0; j = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
		}
		else if (wParam == 't' || wParam == 'T') {
			x1 = he[0].x;
			y1 = he[0].y;
			r = he[0].r;
			g1 = he[0].g;
			b = he[0].b;
			for (int i = 1; i <= n - 1; i++) {
				he[i - 1].x = he[i].x;
				he[i - 1].y = he[i].y;
				he[i - 1].r = he[i].r;
				he[i - 1].g = he[i].g;
				he[i - 1].b = he[i].b;
			}
			he[n - 1].x = x1;
			he[n - 1].y = y1;
			he[n - 1].r = r;
			he[n - 1].g = g1;
			he[n - 1].b = b;
			l = 0; j = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
		}
		else if (wParam == VK_RIGHT) {
			temp = 1;
			cng = 0;
			l = 0; j = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
		}
		else if (wParam == VK_LEFT) {
			temp = 2;
			cng = 0;
			l = 0; j = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
		}
		else if (wParam == VK_UP) {
			temp = 3;
			cng = 0;
			l = 0; j = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
		}
		else if (wParam == VK_DOWN) {
			temp = 4;
			cng = 0;
			l = 0; j = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
		}
		break;
	case WM_TIMER:
		if (temp == 1) {
			if (jum == 0) {
				if (cng % 2 == 0) {
					p = he[0].x;
					g = he[0].y;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].x += 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					for (int i = 1; i < n; i++) {
						if (he[0].x == he[i].x && he[0].y == he[i].y) {
							end++;
						}
					}
					for (int i = 0; i < 20; i++) {
						if (he[0].y == wa[i].y && he[0].x == wa[i].x) {
							he[0].x -= 20;
							temp = rand() % 2 + 3;
						}
					}
					l = 0; j = 0;
				}
				else if (cng % 2 == 1) {
					p = he[0].x;
					g = he[0].y;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].x -= 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					for (int i = 1; i < n; i++) {
						if (he[0].x == he[i].x && he[0].y == he[i].y) {
							end++;
						}
					}
					for (int i = 0; i < 20; i++) {
						if (he[0].y == wa[i].y && he[0].x == wa[i].x) {
							he[0].x += 20;
							temp = rand() % 2 + 3;
						}
					}
					l = 0; j = 0;
				}
				if (he[0].x + 10 > 810) {
					cng++;
					p = he[0].x;
					g = he[0].y;
					he[0].x -= 20;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].y += 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					l = 0; j = 0;
				}
				if (he[0].x - 10 < -10) {
					cng++;
					p = he[0].x;
					g = he[0].y;
					he[0].x += 20;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].y += 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					l = 0; j = 0;
				}
			}
			if (jum > 0) {
				p = he[0].x;
				g = he[0].y;
				for (int i = n - 1; i >= 1; i--) {
					he[i].x = he[i - 1].x;
					he[i].y = he[i - 1].y;
				}
				if (cng % 2 == 0) {
					if (0 <= t) {
						if (t <= 1) {
							he[0].y -= 20;
							t++;
							l = 0; j = 0;
						}
					}
					if (t == 2) {
						he[0].x += 20;
						t1++;
						if (t1 == 2) {
							t = 3;
							t1 = 0;
						}
						l = 0; j = 0;
					}
					if (t == 3) {
						he[0].y += 20;
						t1++;
						if (t1 == 2) {
							t = 0;
							t1 = 0;
							jum = 0;
						}
						l = 0; j = 0;
					}
				}
				if (cng % 2 == 1) {
					if (0 <= t) {
						if (t <= 1) {
							he[0].y -= 20;
							t++;
							l = 0; j = 0;
						}
					}
					if (t == 2) {
						he[0].x -= 20;
						t1++;
						if (t1 == 2) {
							t = 3;
							t1 = 0;
						}
						l = 0; j = 0;
					}
					if (t == 3) {
						he[0].y += 20;
						t1++;
						if (t1 == 2) {
							t = 0;
							t1 = 0;
							jum = 0;
						}
						l = 0; j = 0;
					}
				}
				for (int i = 0; i < 60; i++) {
					if (he[0].x == re[i].x && he[0].y == re[i].y) {
						re[i].move = rand() % 4;
						re[i].cat++;
						if (re[i].cat == 2) {
							he[n].r = re[i].r;
							he[n].g = re[i].g;
							he[n].b = re[i].b;
							he[n].x = p;
							he[n].y = g;
							n++;
						}
					}
				}
				l = 0; j = 0;
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (temp == 2) {
			if (jum == 0) {
				if (cng % 2 == 0) {
					p = he[0].x;
					g = he[0].y;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].x -= 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					for (int i = 1; i < n; i++) {
						if (he[0].x == he[i].x && he[0].y == he[i].y) {
							end++;
						}
					}
					for (int i = 0; i < 20; i++) {
						if (he[0].y == wa[i].y && he[0].x == wa[i].x) {
							he[0].x += 20;
							temp = rand() % 2 + 3;
						}
					}
					l = 0; j = 0;
				}
				else if (cng % 2 == 1) {
					p = he[0].x;
					g = he[0].y;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].x += 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					for (int i = 1; i < n; i++) {
						if (he[0].x == he[i].x && he[0].y == he[i].y) {
							end++;
						}
					}
					for (int i = 0; i < 20; i++) {
						if (he[0].y == wa[i].y && he[0].x == wa[i].x) {
							he[0].x -= 20;
							temp = rand() % 2 + 3;
						}
					}
					l = 0; j = 0;
				}
				if (he[0].x + 10 > 810) {
					cng++;
					p = he[0].x;
					g = he[0].y;
					he[0].x -= 20;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].y -= 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					l = 0; j = 0;
				}
				if (he[0].x - 10 < -10) {
					cng++;
					p = he[0].x;
					g = he[0].y;
					he[0].x += 20;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].y -= 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					l = 0; j = 0;
				}
			}
			if (jum > 0) {
				p = he[0].x;
				g = he[0].y;
				for (int i = n - 1; i >= 1; i--) {
					he[i].x = he[i - 1].x;
					he[i].y = he[i - 1].y;
				}
				if (cng % 2 == 0) {
					if (0 <= t) {
						if (t <= 1) {
							he[0].y -= 20;
							t++;
							l = 0; j = 0;
						}
					}
					if (t == 2) {
						he[0].x -= 20;
						t1++;
						if (t1 == 2) {
							t = 3;
							t1 = 0;
						}
						l = 0; j = 0;
					}
					if (t == 3) {
						he[0].y += 20;
						t1++;
						if (t1 == 2) {
							t = 0;
							t1 = 0;
							jum = 0;
						}
						l = 0; j = 0;
					}
				}
				if (cng % 2 == 1) {
					if (0 <= t) {
						if (t <= 1) {
							he[0].y -= 20;
							t++;
							l = 0; j = 0;
						}
					}
					if (t == 2) {
						he[0].x += 20;
						t1++;
						if (t1 == 2) {
							t = 3;
							t1 = 0;
						}
						l = 0; j = 0;
					}
					if (t == 3) {
						he[0].y += 20;
						t1++;
						if (t1 == 2) {
							t = 0;
							t1 = 0;
							jum = 0;
						}
						l = 0; j = 0;
					}
				}
				for (int i = 0; i < 60; i++) {
					if (he[0].x == re[i].x && he[0].y == re[i].y) {
						re[i].move = rand() % 4;
						re[i].cat++;
						if (re[i].cat == 2) {
							he[n].r = re[i].r;
							he[n].g = re[i].g;
							he[n].b = re[i].b;
							he[n].x = p;
							he[n].y = g;
							n++;
						}
					}
				}
				l = 0; j = 0;
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (temp == 3) {
			if (jum == 0) {
				if (cng % 2 == 0) {
					p = he[0].x;
					g = he[0].y;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].y -= 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					for (int i = 1; i < n; i++) {
						if (he[0].x == he[i].x && he[0].y == he[i].y) {
							end++;
						}
					}
					for (int i = 0; i < 20; i++) {
						if (he[0].y == wa[i].y && he[0].x == wa[i].x) {
							he[0].y += 20;
							temp = rand() % 2 + 1;
						}
					}
					l = 0; j = 0;
				}
				else if (cng % 2 == 1) {
					p = he[0].x;
					g = he[0].y;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].y += 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					for (int i = 1; i < n; i++) {
						if (he[0].x == he[i].x && he[0].y == he[i].y) {
							end++;
						}
					}
					for (int i = 0; i < 20; i++) {
						if (he[0].y == wa[i].y && he[0].x == wa[i].x) {
							he[0].y -= 20;
							temp = rand() % 2 + 1;
						}
					}
					l = 0; j = 0;
				}
				if (he[0].y + 10 > 820) {
					cng++;
					p = he[0].x;
					g = he[0].y;
					he[0].y -= 20;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].x -= 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					l = 0; j = 0;
				}
				if (he[0].y - 10 < 10) {
					cng++;
					p = he[0].x;
					g = he[0].y;
					he[0].y += 20;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].x -= 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					l = 0; j = 0;
				}
			}
			if (jum > 0) {
				p = he[0].x;
				g = he[0].y;
				for (int i = n - 1; i >= 1; i--) {
					he[i].x = he[i - 1].x;
					he[i].y = he[i - 1].y;
				}
				if (cng % 2 == 0) {
					if (0 <= t) {
						if (t <= 1) {
							he[0].x -= 20;
							t++;
							l = 0; j = 0;
						}
					}
					if (t == 2) {
						he[0].y -= 20;
						t1++;
						if (t1 == 2) {
							t = 3;
							t1 = 0;
						}
						l = 0; j = 0;
					}
					if (t == 3) {
						he[0].x += 20;
						t1++;
						if (t1 == 2) {
							t = 0;
							t1 = 0;
							jum = 0;
						}
						l = 0; j = 0;
					}
				}
				if (cng % 2 == 1) {
					if (0 <= t) {
						if (t <= 1) {
							he[0].x += 20;
							t++;
							l = 0; j = 0;
						}
					}
					if (t == 2) {
						he[0].y += 20;
						t1++;
						if (t1 == 2) {
							t = 3;
							t1 = 0;
						}
						l = 0; j = 0;
					}
					if (t == 3) {
						he[0].x -= 20;
						t1++;
						if (t1 == 2) {
							t = 0;
							t1 = 0;
							jum = 0;
						}
						l = 0; j = 0;
					}
				}
				for (int i = 0; i < 60; i++) {
					if (he[0].x == re[i].x && he[0].y == re[i].y) {
						re[i].move = rand() % 4;
						re[i].cat++;
						if (re[i].cat == 2) {
							he[n].r = re[i].r;
							he[n].g = re[i].g;
							he[n].b = re[i].b;
							he[n].x = p;
							he[n].y = g;
							n++;
						}
					}
				}
				l = 0; j = 0;
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (temp == 4) {
			if (jum == 0) {
				if (cng % 2 == 0) {
					p = he[0].x;
					g = he[0].y;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].y += 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					for (int i = 1; i < n; i++) {
						if (he[0].x == he[i].x && he[0].y == he[i].y) {
							end++;
						}
					}
					for (int i = 0; i < 20; i++) {
						if (he[0].y == wa[i].y && he[0].x == wa[i].x) {
							he[0].y -= 20;
							temp = rand() % 2 + 1;
						}
					}
					l = 0; j = 0;
				}
				else if (cng % 2 == 1) {
					p = he[0].x;
					g = he[0].y;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].y -= 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					for (int i = 1; i < n; i++) {
						if (he[0].x == he[i].x && he[0].y == he[i].y) {
							end++;
						}
					}
					for (int i = 0; i < 20; i++) {
						if (he[0].y == wa[i].y && he[0].x == wa[i].x) {
							he[0].y += 20;
							temp = rand() % 2 + 1;
						}
					}
					l = 0; j = 0;
				}
				if (he[0].y + 10 > 820) {
					cng++;
					p = he[0].x;
					g = he[0].y;
					he[0].y -= 20;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].x += 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					l = 0; j = 0;
				}
				if (he[0].y - 10 < 10) {
					cng++;
					p = he[0].x;
					g = he[0].y;
					he[0].y += 20;
					for (int i = n - 1; i >= 1; i--) {
						he[i].x = he[i - 1].x;
						he[i].y = he[i - 1].y;
					}
					he[0].x += 20;
					for (int i = 0; i < 60; i++) {
						if (he[0].x == re[i].x && he[0].y == re[i].y) {
							re[i].move = rand() % 4;
							re[i].cat++;
							if (re[i].cat == 2) {
								he[n].r = re[i].r;
								he[n].g = re[i].g;
								he[n].b = re[i].b;
								he[n].x = p;
								he[n].y = g;
								n++;
							}
						}
					}
					l = 0; j = 0;
				}
			}
			if (jum > 0) {
				p = he[0].x;
				g = he[0].y;
				for (int i = n - 1; i >= 1; i--) {
					he[i].x = he[i - 1].x;
					he[i].y = he[i - 1].y;
				}
				if (cng % 2 == 0) {
					if (0 <= t) {
						if (t <= 1) {
							he[0].x += 20;
							t++;
							l = 0; j = 0;
						}
					}
					if (t == 2) {
						he[0].y += 20;
						t1++;
						if (t1 == 2) {
							t = 3;
							t1 = 0;
						}
						l = 0; j = 0;
					}
					if (t == 3) {
						he[0].x -= 20;
						t1++;
						if (t1 == 2) {
							t = 0;
							t1 = 0;
							jum = 0;
						}
						l = 0; j = 0;
					}
				}
				if (cng % 2 == 1) {
					if (0 <= t) {
						if (t <= 1) {
							he[0].x -= 20;
							t++;
							l = 0; j = 0;
						}
					}
					if (t == 2) {
						he[0].y -= 20;
						t1++;
						if (t1 == 2) {
							t = 3;
							t1 = 0;
						}
						l = 0; j = 0;
					}
					if (t == 3) {
						he[0].x += 20;
						t1++;
						if (t1 == 2) {
							t = 0;
							t1 = 0;
							jum = 0;
						}
						l = 0; j = 0;
					}
				}
				for (int i = 0; i < 60; i++) {
					if (he[0].x == re[i].x && he[0].y == re[i].y) {
						re[i].move = rand() % 4;
						re[i].cat++;
						if (re[i].cat == 2) {
							he[n].r = re[i].r;
							he[n].g = re[i].g;
							he[n].b = re[i].b;
							he[n].x = p;
							he[n].y = g;
							n++;
						}
					}
				}
				l = 0; j = 0;
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (end == 2) {
			KillTimer(hwnd, 1);
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		for (int i = 0; i < 60; i++) {
			if (re[i].move == 0) {
				if (re[i].cat == 1) {
					p = re[i].x;
					g = re[i].y;
					re[i].x = re[i].x;
					re[i].y = re[i].y;
					for (int j = 0; j < 60; j++) {
						if (i != j) {
							if (re[i].x == re[j].x && re[i].y == re[j].y) {
								if (re[j].move >= re[i].move) {
									re[j].x = p;
									re[j].y = g;
									re[i].move = re[j].move;
									re[i].cng1 = re[j].cng1;
									re[i].cng2 = re[j].cng2;
									re[i].cng3 = re[j].cng3;
									re[i].cng4 = re[j].cng4;
								}
							}
						}
					}
				}
				l = 0; j = 0;
				InvalidateRect(hwnd, NULL, TRUE);
			}
			else if (re[i].move == 1) {
				if (re[i].cat == 1) {
					p = re[i].x;
					g = re[i].y;
					if (re[i].cng2 % 2 == 0) {
						re[i].y -= 20;
					}
					if (re[i].cng2 % 2 == 1) {
						re[i].y += 20;
					}
					if (re[i].y + 10 > 820) {
						re[i].cng2++;
						re[i].y -= 20;
					}
					if (re[i].y - 10 < 20) {
						re[i].cng2++;
						re[i].y += 20;
					}
					for (int j = 0; j < 60; j++) {
						if (i != j) {
							if (re[i].x == re[j].x && re[i].y == re[j].y) {
								if (re[j].move >= re[i].move) {
									re[i].x = p;
									re[i].y = g;
									re[i].move = re[j].move;
									re[i].cng1 = re[j].cng1;
									re[i].cng2 = re[j].cng2;
									re[i].cng3 = re[j].cng3;
									re[i].cng4 = re[j].cng4;
								}
								else if (re[j].move == 0) {
									re[j].x = p;
									re[j].y = g;
									re[j].move = re[i].move;
									re[j].cng1 = re[i].cng1;
									re[j].cng2 = re[i].cng2;
									re[j].cng3 = re[i].cng3;
									re[j].cng4 = re[i].cng4;
								}
							}
						}
					}
				}
				l = 0; j = 0;
				InvalidateRect(hwnd, NULL, TRUE);
			}
			else if (re[i].move == 2) {
				if (re[i].cat == 1) {
					p = re[i].x;
					g = re[i].y;
					if (re[i].cng1 % 2 == 0) {
						re[i].x -= 20;
					}
					if (re[i].cng1 % 2 == 1) {
						re[i].x += 20;
					}
					if (re[i].x + 10 > 810) {
						re[i].cng1++;
						re[i].x -= 20;
					}
					if (re[i].x - 10 < 0) {
						re[i].cng1++;
						re[i].x += 20;
					}
					for (int j = 0; j < 60; j++) {
						if (i != j) {
							if (re[i].x == re[j].x && re[i].y == re[j].y) {
								if (re[j].move >= re[i].move) {
									re[i].x = p;
									re[i].y = g;
									re[i].move = re[j].move;
									re[i].cng1 = re[j].cng1;
									re[i].cng2 = re[j].cng2;
									re[i].cng3 = re[j].cng3;
									re[i].cng4 = re[j].cng4;
								}
								else if (re[j].move == 0 || re[j].move == 1) {
									re[j].x = p;
									re[j].y = g;
									re[j].move = re[i].move;
									re[j].cng1 = re[i].cng1;
									re[j].cng2 = re[i].cng2;
									re[j].cng3 = re[i].cng3;
									re[j].cng4 = re[i].cng4;
								}
							}
						}
					}
				}
				l = 0; j = 0;
				InvalidateRect(hwnd, NULL, TRUE);
			}
			else if (re[i].move == 3) {
				if (re[i].cat == 1) {
					p = re[i].x;
					g = re[i].y;
					if (re[i].cng3 % 2 == 0) {
						re[i].y -= 20;
					}
					if (re[i].cng3 % 2 == 1) {
						re[i].y += 20;
					}
					if (re[i].cng4 % 2 == 0) {
						re[i].x += 20;
					}
					if (re[i].cng4 % 2 == 1) {
						re[i].x -= 20;
					}
					if (re[i].y + 10 > 820) {
						re[i].cng3++;
						re[i].y -= 20;
					}
					if (re[i].y - 10 < 20) {
						re[i].cng3++;
						re[i].y += 20;
					}
					if (re[i].x + 10 > 810) {
						re[i].cng4++;
						re[i].x -= 20;
					}
					if (re[i].x - 10 < 0) {
						re[i].cng4++;
						re[i].x += 20;
					}
					for (int j = 0; j < 60; j++) {
						if (i != j) {
							if (re[i].x == re[j].x && re[i].y == re[j].y) {
								if (re[j].move >= re[i].move) {
									re[i].x = p;
									re[i].y = g;
									re[i].move = re[j].move;
									re[i].cng1 = re[j].cng1;
									re[i].cng2 = re[j].cng2;
									re[i].cng3 = re[j].cng3;
									re[i].cng4 = re[j].cng4;
								}
								else if (re[j].move == 0 || re[j].move == 1 || re[j].move == 2) {
									re[j].x = p;
									re[j].y = g;
									re[j].move = re[i].move;
									re[j].cng1 = re[i].cng1;
									re[j].cng2 = re[i].cng2;
									re[j].cng3 = re[i].cng3;
									re[j].cng4 = re[i].cng4;
								}
							}
						}
					}
				}
				l = 0; j = 0;
				InvalidateRect(hwnd, NULL, TRUE);
			}
		}
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
