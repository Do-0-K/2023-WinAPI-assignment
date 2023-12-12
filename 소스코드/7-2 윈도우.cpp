#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include "resource2.h"
#define IDC_LISTBOX 100
#define IDC_BUTTON41 123
#define IDC_BUTTON42 124
#define IDC_BUTTON43 125
#define IDC_BUTTON44 126
#define IDC_BUTTON45 127
#define IDC_BUTTON46 128
#define IDC_EDIT 129
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 750, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
static int Selection[10];
static int chose[10];
static HBITMAP hbm[6];
static int t = 0;
static int move = 0;
static TCHAR ba[10][10] = { {L"1 page"},{L"2 page"},{L"3 page"},{L"4 page"},{L"5 page"}, {L"6 page"},{L"7 page"}, {L"8 page"},{L"9 page"},  {L"10 page"} };
static int x = 500*t;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) { //옆으로 미는 부분을 어떻게 해야할까
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	static HWND child_hWnd;
	static HWND list{};
	static TCHAR Items1[8] = L"1-Image";
	static TCHAR Items2[8] = L"2-Image";
	static TCHAR Items3[8] = L"3-Image";
	static TCHAR Items4[8] = L"4-Image";
	static TCHAR Items5[8] = L"5-Image";
	static TCHAR Items6[8] = L"6-Image";
	HBITMAP hbmt[2];
	HWND b1, b2,b3,b4,b5,b6;
	HWND hEdit;
	switch (iMsg) {
	case WM_CREATE:
		child_hWnd = CreateWindow(L"ChildClass", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, 120, 120, 500, 500, hwnd, NULL, g_hInst, NULL);
		list = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_STANDARD, 760, 30, 200, 300, hwnd, (HMENU)IDC_LISTBOX, g_hInst, NULL);
		SendMessage(list, LB_ADDSTRING, 0, (LPARAM)Items1);
		SendMessage(list, LB_ADDSTRING, 0, (LPARAM)Items2);
		SendMessage(list, LB_ADDSTRING, 0, (LPARAM)Items3);
		SendMessage(list, LB_ADDSTRING, 0, (LPARAM)Items4);
		SendMessage(list, LB_ADDSTRING, 0, (LPARAM)Items5);
		SendMessage(list, LB_ADDSTRING, 0, (LPARAM)Items6);
		hbm[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP21));
		hbm[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP22));
		hbm[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP23));
		hbm[3] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP24));
		hbm[4] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP25));
		hbm[5] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP26));
		b1 = CreateWindow(L"button", L"1-이동", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 10, 300, 80, 80, hwnd,(HMENU)IDC_BUTTON41, g_hInst, NULL);
		hbmt[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
		SendMessage(b1, BM_SETIMAGE, 0 , (LPARAM)hbmt[0]);
		b2 = CreateWindow(L"button", L"1-이동", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 650, 300, 80, 80, hwnd, (HMENU)IDC_BUTTON42, g_hInst, NULL);
		hbmt[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP27));
		SendMessage(b2, BM_SETIMAGE, 0, (LPARAM)hbmt[1]);
		b3 = CreateWindow(L"button", L"Select", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 760, 400, 200, 40, hwnd, (HMENU)IDC_BUTTON43, g_hInst, NULL);
		b4 = CreateWindow(L"button", L"Move", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 760, 450, 200, 40, hwnd, (HMENU)IDC_BUTTON44, g_hInst, NULL);
		b5 = CreateWindow(L"button", L"Stop", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 760, 500, 200, 40, hwnd, (HMENU)IDC_BUTTON45, g_hInst, NULL);
		b5 = CreateWindow(L"button", L"Finish", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 760, 550, 200, 40, hwnd, (HMENU)IDC_BUTTON46, g_hInst, NULL);
		hEdit = CreateWindow(L"edit", ba[t], WS_CHILD | WS_VISIBLE | WS_BORDER, 280, 30, 160, 60, hwnd, (HMENU)IDC_EDIT, g_hInst, NULL);
		Selection[0] = -1;
		Selection[1] = -1;
		Selection[2] = -1;
		Selection[3] = -1;
		Selection[4] = -1;
		Selection[5] = -1;
		Selection[6] = -1;
		Selection[7] = -1;
		Selection[8] = -1;
		Selection[9] = -1;
		chose[0] = -1;
		chose[1] = -1;
		chose[2] = -1;
		chose[3] = -1;
		chose[4] = -1;
		chose[5] = -1;
		chose[6] = -1;
		chose[7] = -1;
		chose[8] = -1;
		chose[9] = -1;
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LISTBOX:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				if (chose[t] == -1) {
					Selection[t] = SendMessage(list, LB_GETCURSEL, 0, 0);
				}
			}
			break;
		case IDC_BUTTON41:
			t--;
			if (t < 0) {
				t++;
			}
			if (chose[t] == -1) {
				Selection[t] = -1;
			}
			x = 500 * t;
			SetDlgItemText(hwnd, IDC_EDIT, ba[t]);
			break;
		case IDC_BUTTON42:
			t++;
			if (t > 9) {
				t--;
			}
			if (chose[t] == -1) {
				Selection[t] = -1;
			}
			x = 500 * t;
			SetDlgItemText(hwnd, IDC_EDIT, ba[t]);
			break;
		case IDC_BUTTON43:
			if (chose[t] == -1) {
				chose[t] = 0;
			}
			break;
		case IDC_BUTTON44:
			if (move == 0) {
				move = 1;
			}
			else if (move == 1) {
				move = 0;
			}
			break;
		case IDC_BUTTON45:
			move = 0;
			break;
		case IDC_BUTTON46:
			for (int i = 0;i < t;i++) {
				chose[i] = 0;
			}
			break;
		}
		InvalidateRect(child_hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
LRESULT CALLBACK ChildProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc ,kdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap[10];
	HBITMAP oldbit[2];
	HBITMAP hbit;
	RECT rt{};
	static int x1 = 0, x2 = -500;
	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		SetTimer(hwnd, 1, 50, NULL);
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		kdc = CreateCompatibleDC(hdc);
		mdc = CreateCompatibleDC(kdc);
		hbit = CreateCompatibleBitmap(hdc, 5500, rt.bottom);
		oldbit[0] = (HBITMAP)SelectObject(kdc,hbit);
		for (int i = 0;i < 10;i++) {
			if (chose[i] == 0) {
				oldbit[1] = (HBITMAP)SelectObject(mdc, hBitmap[i]);
				SelectObject(mdc, (HBITMAP)hbm[Selection[i]]);
				StretchBlt(kdc, 500 * i, 0, 500, 500, mdc, 0, 0, 500, 500, SRCCOPY);
			}
		}
		StretchBlt(hdc, 0, 0, rt.right, rt.bottom, kdc, x, 0, rt.right, rt.bottom, SRCCOPY);
		if (x1 == 1) {
			StretchBlt(hdc, 0, 0, rt.right, rt.bottom, kdc, x2, 0, rt.right, rt.bottom, SRCCOPY);
		}
		SelectObject(kdc, oldbit[0]);
		DeleteDC(mdc);
		DeleteDC(kdc);
		DeleteObject(hBitmap[t]);
		EndPaint(hwnd, &ps);
		break;
	case WM_TIMER:
		if (move == 1) {
			x += 10;
			if (x >= 4500) {
				x1 = 1;
				x2 += 10;
			}
			if (x == 5000) {
				x1 = 0;
				x = 0;
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