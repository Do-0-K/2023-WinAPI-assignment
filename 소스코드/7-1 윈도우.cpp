#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<string.h>
#include<math.h>
#define _USE_MATH_DEFINES
#define M_PI 3.141592
#define IDC_RADIO1 100
#define IDC_RADIO2 200
#define IDC_RADIO3 300
#define IDC_RADIO4 400
#define IDC_RADIO5 500
#define IDC_RADIO6 600
#define IDC_CHECK1 101
#define IDC_CHECK2 201
#define IDC_CHECK3 301
#define IDC_EDIT 111
#define IDC_BUTTON1 121
#define IDC_BUTTON2 122
#define IDC_BUTTON3 123
#define IDC_BUTTON4 124
#define IDC_BUTTON5 125
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Program 2";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
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
	WndClass.hCursor = LoadCursor(NULL, IDC_HELP);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszClassName = L"ChildClass";
	WndClass.lpfnWndProc = ChildProc;
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
static int shape = 0;
static int t = 0;
struct rect {
	double x = 0, y = 0;
};
struct rect re[4];
struct won {
	double x = 250, y = 250;
	int size = 200;
	double angle = 0;
};
struct won w[1];
struct won c[1];
struct tri {
	double x = 0, y = 0;
};
struct tri tr[3];
struct ba {
	int x = 400, y = 10;
	TCHAR str[20];
};
struct ba ba[10];
static int move = 0;
static int r = 0, g = 0, b = 0;
static int speed = 100;
static int s = 0;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	static BOOL Selection;
	static int x = 0;
	int mx;
	HWND child_hWnd;
	HWND box1, box2;
	HWND r1, r2, r3;
	HWND d1, d2, d3;
	HWND f1, f2, f3;
	HWND hEdit;
	HWND b1, b2, b3, b4, b5;
	static int cng = 0, cng1 = 0, cng2 = 0;
	switch (iMsg) {
	case WM_CREATE:
		Selection = FALSE;
		child_hWnd = CreateWindow(L"ChildClass", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, 30, 30, 500, 500, hwnd, NULL, g_hInst, NULL);
		box1 = CreateWindow(L"button", L"Shape", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 580, 30, 140, 120, hwnd, (HMENU)IDC_RADIO1, g_hInst, NULL);
		r1 = CreateWindow(L"button", L"Rectangle", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 600, 50, 100, 30, hwnd, (HMENU)IDC_RADIO1, g_hInst, NULL);
		r2 = CreateWindow(L"button", L"Ellipse", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 600, 80, 100, 30, hwnd, (HMENU)IDC_RADIO2, g_hInst, NULL);
		r3 = CreateWindow(L"button", L"Triangle", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 600, 110, 100, 30, hwnd, (HMENU)IDC_RADIO3, g_hInst, NULL);
		CheckRadioButton(hwnd, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
		box2 = CreateWindow(L"button", L"Size", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 580, 160, 140, 120, hwnd, (HMENU)IDC_RADIO4, g_hInst, NULL);
		d1 = CreateWindow(L"button", L"Small", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 600, 180, 100, 30, hwnd, (HMENU)IDC_RADIO4, g_hInst, NULL);
		d2 = CreateWindow(L"button", L"Medium", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 600, 210, 100, 30, hwnd, (HMENU)IDC_RADIO5, g_hInst, NULL);
		d3 = CreateWindow(L"button", L"Large", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 600, 240, 100, 30, hwnd, (HMENU)IDC_RADIO6, g_hInst, NULL);
		CheckRadioButton(hwnd, IDC_RADIO4, IDC_RADIO6, IDC_RADIO5);
		f1 = CreateWindow(L"button", L"Red", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 600, 300, 100, 25, hwnd, (HMENU)IDC_CHECK1, g_hInst, NULL);
		f2 = CreateWindow(L"button", L"Green", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 600, 330, 100, 25, hwnd, (HMENU)IDC_CHECK2, g_hInst, NULL);
		f3 = CreateWindow(L"button", L"Blue", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 600, 360, 100, 25, hwnd, (HMENU)IDC_CHECK3, g_hInst, NULL);
		hEdit = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 570, 400, 160, 60, hwnd, (HMENU)IDC_EDIT, g_hInst, NULL);
		b1 = CreateWindow(L"button", L"Chatting", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 610, 480, 80, 25, hwnd, (HMENU)IDC_BUTTON1, g_hInst, NULL);
		b2 = CreateWindow(L"button", L"Move", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 550, 510, 80, 25, hwnd, (HMENU)IDC_BUTTON2, g_hInst, NULL);
		b3 = CreateWindow(L"button", L"Stop", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 670, 510, 80, 25, hwnd, (HMENU)IDC_BUTTON3, g_hInst, NULL);
		b4 = CreateWindow(L"button", L"+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 550, 540, 80, 25, hwnd, (HMENU)IDC_BUTTON4, g_hInst, NULL);
		b5 = CreateWindow(L"button", L"-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 670, 540, 80, 25, hwnd, (HMENU)IDC_BUTTON5, g_hInst, NULL);
		re[0].x = 80;
		re[0].y = 80;
		re[1].x = 420;
		re[1].y = 80;
		re[3].x = 80;
		re[3].y = 420;
		re[2].x = 420;
		re[2].y = 420;
		tr[0].x = 250;
		tr[0].y = 80;
		tr[1].x = 80;
		tr[1].y = 375;
		tr[2].x = 420;
		tr[2].y = 375;
		c[0].x = -100;
		c[0].y = -100;
		c[0].size = 20;
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		hBrush = CreateSolidBrush(RGB(100, 100, 100));
		oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
		Rectangle(mdc, 0, 0, rt.right, rt.bottom);
		SelectObject(mdc, oldBrush);
		DeleteObject(hBrush);

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RADIO1:
			shape = 1;
			c[0].x = re[0].x;
			c[0].y = re[0].y;
			s = 0;
			break;
		case IDC_RADIO2:
			shape = 2;
			c[0].x = w[0].x;
			c[0].y = w[0].y - w[0].size;
			s = 0;
			break;
		case IDC_RADIO3:
			shape = 3;
			c[0].x = tr[0].x;
			c[0].y = tr[0].y;
			s = 0;
			break;
		case IDC_RADIO4:
			c[0].size = 10;
			break;
		case IDC_RADIO5:
			c[0].size = 20;
			break;
		case IDC_RADIO6:
			c[0].size = 30;
			break;
		case IDC_CHECK1:
			if (cng % 2 == 0) {
				r += 255;
			}
			if (cng % 2 == 1) {
				r -= 255;
			}
			if (r > 255) {
				r = 255;
			}
			if (g > 255) {
				g = 255;
			}
			if (b > 255) {
				b = 255;
			}
			cng++;
			break;
		case IDC_CHECK2:
			if (cng1 % 2 == 0) {
				g += 255;
			}
			if (cng1 % 2 == 1) {
				g -= 255;
			}
			if (r > 255) {
				r = 255;
			}
			if (g > 255) {
				g = 255;
			}
			if (b > 255) {
				b = 255;
			}
			cng1++;
			break;
		case IDC_CHECK3:
			if (cng2 % 2 == 0) {
				b += 255;
			}
			if (cng2 % 2 == 1) {
				b -= 255;
			}
			if (r > 255) {
				r = 255;
			}
			if (g > 255) {
				g = 255;
			}
			if (b > 255) {
				b = 255;
			}
			cng2++;
			break;
		case IDC_BUTTON1:
			GetDlgItemText(hwnd, IDC_EDIT, ba[t].str, 20);
			hdc = GetDC(hwnd);
			TextOut(hdc, ba[t].x, ba[t].y + 30 * t, ba[t].str, lstrlen(ba[t].str));
			ReleaseDC(hwnd, hdc);
			t++;
			break;
		case IDC_BUTTON2:
			move = 1;
			break;
		case IDC_BUTTON3:
			move = 0;
			break;
		case IDC_BUTTON4:
			speed -= 50;
			if (speed < 0) {
				speed += 50;
			}
			break;
		case IDC_BUTTON5:
			speed += 50;
			if (speed > 400) {
				speed -= 50;
			}
			break;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		Selection = FALSE;
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
		break;
	case WM_TIMER:
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
LRESULT CALLBACK ChildProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		SetTimer(hwnd, 1, speed, NULL);
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		Rectangle(mdc, 0, 0, rt.right, rt.bottom);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(mdc, hPen);
		if (shape == 1) {
			MoveToEx(mdc, re[0].x, re[0].y, NULL);
			LineTo(mdc, re[1].x, re[1].y);
			MoveToEx(mdc, re[1].x, re[1].y, NULL);
			LineTo(mdc, re[2].x, re[2].y);
			MoveToEx(mdc, re[2].x, re[2].y, NULL);
			LineTo(mdc, re[3].x, re[3].y);
			MoveToEx(mdc, re[3].x, re[3].y, NULL);
			LineTo(mdc, re[0].x, re[0].y);
		}
		if (shape == 2) {
			Ellipse(mdc, w[0].x - w[0].size, w[0].y - w[0].size, w[0].x + w[0].size, w[0].y + w[0].size);
		}
		if (shape == 3) {
			MoveToEx(mdc, tr[0].x, tr[0].y, NULL);
			LineTo(mdc, tr[1].x, tr[1].y);
			MoveToEx(mdc, tr[1].x, tr[1].y, NULL);
			LineTo(mdc, tr[2].x, tr[2].y);
			MoveToEx(mdc, tr[2].x, tr[2].y, NULL);
			LineTo(mdc, tr[0].x, tr[0].y);
		}
		for (int i = 0;i < t;i++) {
			TextOut(mdc, 400, 10 + i*15, ba[i].str, lstrlen(ba[i].str));
		}
		MoveToEx(mdc, 0, 250, NULL);
		LineTo(mdc, 500, 250);
		MoveToEx(mdc, 250, 0, NULL);
		LineTo(mdc, 250, 500);
		SelectObject(mdc, oldPen);
		DeleteObject(hPen);
		hBrush = CreateSolidBrush(RGB(r, g, b));
		oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
		Ellipse(mdc, c[0].x - c[0].size, c[0].y - c[0].size, c[0].x + c[0].size, c[0].y + c[0].size);
		SelectObject(mdc, oldBrush);
		DeleteObject(hBrush);
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_TIMER:
		if (move == 1) {
			if (shape == 1) {
				if (s == 0) {
					c[0].x += 10;
					if (re[1].x == c[0].x) {
						s++;
					}
				}
				if (s == 1) {
					c[0].y += 10;
					if (re[2].y == c[0].y) {
						s++;
					}
				}
				if (s == 2) {
					c[0].x -= 10;
					if (re[3].x == c[0].x) {
						s++;
					}
				}
				if (s == 3) {
					c[0].y -= 10;
					if (re[0].y == c[0].y) {
						s = 0;
					}
				}
			}
			if (shape == 2) {
				w[0].angle += (M_PI / 180);
				c[0].x = w[0].x + w[0].size * sin(w[0].angle + M_PI);
				c[0].y = w[0].y + w[0].size * cos(w[0].angle + M_PI);
			}
			if (shape == 3) {
				if (s == 2) {
					c[0].x -= 2;
					c[0].y = ((tr[0].y - tr[2].y) / (tr[0].x - tr[2].x)) * (c[0].x - (((tr[0].x - tr[2].x) / (tr[0].y - tr[2].y)) + tr[2].x)) + tr[2].y;
					if (tr[0].x - 2 <= c[0].x && c[0].x <= tr[0].x + 2) {
						if (tr[0].y - 2 <= c[0].y && c[0].y <= tr[0].y + 2) {
							s = 0;
						}
					}
				}
				else {
					if (s == 0) {
						c[0].x -= 2;
					}
					if (s == 1) {
						c[0].x += 2;
					}
					c[0].y = ((tr[s+1].y - tr[s].y) / (tr[s+1].x - tr[s].x)) * (c[0].x - tr[s].x) + tr[s].y;
					if (tr[s + 1].x - 2 <= c[0].x && c[0].x <= tr[s + 1].x + 2) {
						if (tr[s + 1].y - 2 <= c[0].y && c[0].y <= tr[s + 1].y + 2) {
							s++;
						}
					}
				}
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}