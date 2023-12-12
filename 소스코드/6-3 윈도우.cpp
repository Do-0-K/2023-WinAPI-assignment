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
BOOL CALLBACK ModelessDlgProc(HWND, UINT, WPARAM, LPARAM);
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
int jum = 0;
struct jum {
	double x = 0, y = 0;
};
struct jum j[7];
int x = 0;
struct won {
	double x = 0, y = 0;
};
struct won circle[1];
struct rect {
	double x = 0, y = 0;
};
struct rect rect[1];
int won = 0;
int nemo = 0;
int r = 0, g = 0, b = 0;
int X1 = 0;
int reverse = 0;
int Selection=-1;
int cha = 0;
static TCHAR text[20] = L"winple";
static TCHAR text1[20] = L"skull";
static TCHAR text2[20] = L"ye~ye~";
static int s = 0;
BOOL CALLBACK ModelessDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static HWND hList;
	static int x2 = 0, y = 150;
	static int g1 = 0, cng = 0;
	static int t = 0;
	switch (iMsg) {
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST1);
		if (lstrcmp(text, L""))
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)text);
		if (lstrcmp(text1, L""))
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)text1);
		if (lstrcmp(text2, L""))
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)text2);
		SetTimer(hDlg, 1, 50, NULL);
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
		CheckRadioButton(hDlg, IDC_RADIO3, IDC_RADIO5, IDC_RADIO3);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
			if (HIWORD(wParam) == LBN_SELCHANGE)
				Selection = SendMessage(hList, LB_GETCURSEL, 0, 0);
			break;
		case IDC_RADIO1:
			won = 1;
			nemo = 0;
			circle[0].x = j[0].x;
			circle[0].y = j[0].y;
			break;
		case IDC_RADIO2:
			won = 0;
			nemo = 1;
			rect[0].x = j[0].x;
			rect[0].y = j[0].y;
			break;
		case IDC_RADIO3:
			r = 255;
			g = 0;
			b = 0;
			break;
		case IDC_RADIO4:
			r = 0;
			g = 255;
			b = 0;
			break;
		case IDC_RADIO5:
			r = 0;
			g = 0;
			b = 255;
			break;
		case IDC_BUTTON2:
			jum = 1;
			break;
		case IDC_BUTTON3:
			X1 = 1;
			reverse = 0;
			break;
		case IDC_BUTTON4:
			x = 0;
			jum = 1;
			break;
		case IDC_BUTTON5:
			g1 = 1;
			y = 260;
			t++;;
			break;
		case IDC_BUTTON6:
			reverse = 1;
			X1 = 0;
			s++;
			break;
		case IDC_BUTTON7:
			X1 = 0;
			reverse = 0;
			break;
		case IDC_BUTTON24:
			PostQuitMessage(0);
			DestroyWindow(hDlg);
			hDlg = NULL;
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		if (g1 == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, x2 - 15, y - 15, x2 + 15, y + 15);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		EndPaint(hDlg, &ps);
		break;
	case WM_TIMER:
		if (t % 2 == 1) {
			if (cng % 2 == 0) {
				x2 += 10;
			}
			if (cng % 2 == 1) {
				x2 -= 10;
			}
			if (x2 > 430) {
				y -= 10;
				cng++;
			}
			if (x2 < 10) {
				y += 10;
				cng++;
			}
		}
		InvalidateRect(hDlg, NULL, TRUE);
		break;
	case WM_CLOSE:
		DestroyWindow(hDlg);
		hDlg = NULL;
		break;
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	HWND hDlg = NULL;
	int mx,my;
	static int size_x = 0, size_y = 0;
	switch (iMsg) {
	case WM_CREATE:
		SetTimer(hwnd, 1, 40, NULL);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		Rectangle(mdc, 0, 0, rt.right, rt.bottom);
		hPen = CreatePen(PS_SOLID, 5, RGB(185, 73, 162));
		oldPen = (HPEN)SelectObject(mdc, hPen);
		if (x > 1) {
			MoveToEx(mdc, j[0].x, j[0].y, NULL);
			LineTo(mdc, j[1].x, j[1].y);
		}
		if (x > 2) {
			MoveToEx(mdc, j[1].x, j[1].y, NULL);
			LineTo(mdc, j[2].x, j[2].y);
		}
		if (x > 3) {
			MoveToEx(mdc, j[2].x, j[2].y, NULL);
			LineTo(mdc, j[3].x, j[3].y);
		}
		if (x > 4) {
			MoveToEx(mdc, j[3].x, j[3].y, NULL);
			LineTo(mdc, j[4].x, j[4].y);
		}
		if (x > 5) {
			MoveToEx(mdc, j[4].x, j[4].y, NULL);
			LineTo(mdc, j[5].x, j[5].y);
		}
		if (x > 6) {
			MoveToEx(mdc, j[5].x, j[5].y, NULL);
			LineTo(mdc, j[6].x, j[6].y);
			MoveToEx(mdc, j[6].x, j[6].y, NULL);
			LineTo(mdc, j[0].x, j[0].y);
		}
		SelectObject(mdc, oldPen);
		DeleteObject(hPen);
		if (won == 1) {
			hBrush = CreateSolidBrush(RGB(r, g, b));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, circle[0].x - 25, circle[0].y - 25, circle[0].x + 25, circle[0].y + 25);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
			if (Selection == 0) {
				TextOut(mdc, circle[0].x, circle[0].y - 30, text1, lstrlen(text1));
			}
			if (Selection == 1) {
				TextOut(mdc, circle[0].x, circle[0].y - 30, text, lstrlen(text));
			}
			if (Selection == 2) {
				TextOut(mdc, circle[0].x, circle[0].y - 30, text2, lstrlen(text2));
			}
		}
		if (nemo == 1) {
			hBrush = CreateSolidBrush(RGB(r, g, b));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Rectangle(mdc, rect[0].x - 25, rect[0].y - 25, rect[0].x + 25, rect[0].y + 25);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
			if (Selection == 0) {
				TextOut(mdc, rect[0].x, rect[0].y - 30, text1, lstrlen(text1));
			}
			if (Selection == 1) {
				TextOut(mdc, rect[0].x, rect[0].y - 30, text, lstrlen(text));
			}
			if (Selection == 2) {
				TextOut(mdc, rect[0].x, rect[0].y - 30, text2, lstrlen(text2));
			}
		}
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_RBUTTONDOWN:
		hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG3), hwnd, (DLGPROC)&ModelessDlgProc);
		ShowWindow(hDlg, SW_SHOW);
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (jum == 1) {
			j[x].x = mx;
			j[x].y = my;
			x++;
		}
		if (x == 7) {
			jum = 0;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		break;
	case WM_TIMER:
		if (won == 1) {
			if (X1 == 1) {
				if (s == 6) {
					if (j[6].x > j[0].x) {
						circle[0].x -= 1;
					}
					else {
						circle[0].x += 1;
					}
					circle[0].y = ((j[6].y - j[0].y) / (j[6].x - j[0].x)) * (circle[0].x - (((j[6].x - j[0].x) / (j[6].y - j[0].y)) + j[0].x)) + j[0].y;
					if (j[0].x - 2 <= circle[0].x && circle[0].x <= j[0].x + 2) {
						if (j[0].y - 2 <= circle[0].y && circle[0].y <= j[0].y + 2) {
							s = 0;
						}
					}
				}
				else {
					if (j[s].x > j[s + 1].x) {
						circle[0].x -= 1;
					}
					else {
						circle[0].x += 1;
					}
					circle[0].y = ((j[s + 1].y - j[s].y) / (j[s + 1].x - j[s].x)) * (circle[0].x - (((j[s + 1].x - j[s].x) / (j[s + 1].y - j[s].y)) + j[s].x)) + j[s].y;
					if (j[s + 1].x - 2 <= circle[0].x && circle[0].x <= j[s + 1].x + 2) {
						if (j[s + 1].y - 2 <= circle[0].y && circle[0].y <= j[s + 1].y + 2) {
							s++;
						}
					}
				}
			}
			if (reverse == 1) {
				if (s == 0) {
					if (j[6].x > j[0].x) {
						circle[0].x += 1;
					}
					else {
						circle[0].x -= 1;
					}
					circle[0].y = ((j[6].y - j[0].y) / (j[6].x - j[0].x)) * (circle[0].x - (((j[6].x - j[0].x) / (j[6].y - j[0].y)) + j[0].x)) + j[0].y;
					if (j[6].x - 2 <= circle[0].x && circle[0].x <= j[6].x + 2) {
						if (j[6].y - 2 <= circle[0].y && circle[0].y <= j[6].y + 2) {
							s = 6;
						}
					}
				}
				else {
					if (j[s - 1].x > j[s].x) {
						circle[0].x += 1;
					}
					else {
						circle[0].x -= 1;
					}
					circle[0].y = ((j[s].y - j[s - 1].y) / (j[s].x - j[s - 1].x)) * (circle[0].x - (((j[s].x - j[s - 1].x) / (j[s].y - j[s - 1].y)) + j[s - 1].x)) + j[s - 1].y;
					if (j[s - 1].x - 2 <= circle[0].x && circle[0].x <= j[s - 1].x + 2) {
						if (j[s - 1].y - 2 <= circle[0].y && circle[0].y <= j[s - 1].y + 2) {
							s--;
							if (s == -1) {
								s = 6;
							}
						}
					}
				}
			}
		}
		if (nemo == 1) {
			if (X1 == 1) {
				if (j[s].x > j[s + 1].x) {
					rect[0].x -= 2;
				}
				else {
					rect[0].x += 2;
				}
				rect[0].y = ((j[s + 1].y - j[s].y) / (j[s + 1].x - j[s].x)) * (rect[0].x - (((j[s + 1].x - j[s].x) / (j[s + 1].y - j[s].y)) + j[s].x)) + j[s].y;
				if (j[s + 1].x - 2 <= rect[0].x && rect[0].x <= j[s + 1].x + 2) {
					if (j[s + 1].y - 2 <= rect[0].y && rect[0].y <= j[s + 1].y + 2) {
						s++;
						if (s == 7) {
							s = 0;
						}
					}
				}
			}
			if (reverse == 1) {
				if (s == 0) {
					if (j[6].x > j[0].x) {
						rect[0].x += 2;
					}
					else {
						rect[0].x -= 2;
					}
					rect[0].y = ((j[6].y - j[0].y) / (j[6].x - j[0].x)) * (rect[0].x - (((j[6].x - j[0].x) / (j[6].y - j[0].y)) + j[0].x)) + j[0].y;
					if (j[6].x - 2 <= rect[0].x && rect[0].x <= j[6].x + 2) {
						if (j[6].y - 2 <= rect[0].y && rect[0].y <= j[6].y + 2) {
							s = 6;
						}
					}
				}
				else {
					if (j[s - 1].x > j[s].x) {
						rect[0].x += 2;
					}
					else {
						rect[0].x -= 2;
					}
					rect[0].y = ((j[s].y - j[s - 1].y) / (j[s].x - j[s - 1].x)) * (rect[0].x - (((j[s].x - j[s - 1].x) / (j[s].y - j[s - 1].y)) + j[s - 1].x)) + j[s - 1].y;
					if (j[s - 1].x - 2 <= rect[0].x && rect[0].x <= j[s - 1].x + 2) {
						if (j[s - 1].y - 2 <= rect[0].y && rect[0].y <= j[s - 1].y + 2) {
							s--;
							if (s == -1) {
								s = 6;
							}
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
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}