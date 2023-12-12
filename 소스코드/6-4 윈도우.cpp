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
BOOL CALLBACK ModelessDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static HWND hList;
	static double startX, startY, oldX, oldY;
	static BOOL Drag;
	int endX, endY;
	static int g = 0;
	static int draw = 0;
	static int size = 10;
	static int move = 0;
	static double x = -100, y = -100;
	static int speed = 0;
	switch (iMsg) {
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
		CheckRadioButton(hDlg, IDC_RADIO3, IDC_RADIO5, IDC_RADIO3);
		CheckRadioButton(hDlg, IDC_RADIO6, IDC_RADIO7, IDC_RADIO6);
		startX = oldX = 0;
		startY = oldY = 0;
		Drag = FALSE;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RADIO1:
			g = 0;
			InvalidateRect(hDlg, NULL, TRUE);
			break;
		case IDC_RADIO2:
			g = 1;
			InvalidateRect(hDlg, NULL, TRUE);
			break;
		case IDC_RADIO3:
			size = 5;
			InvalidateRect(hDlg, NULL, TRUE);
			break;
		case IDC_RADIO4:
			size = 10;
			InvalidateRect(hDlg, NULL, TRUE);
			break;
		case IDC_RADIO5:
			size = 15;
			InvalidateRect(hDlg, NULL, TRUE);
			break;
		case IDC_RADIO6:
			speed = 100;
			SetTimer(hDlg, 1, speed, NULL);
			InvalidateRect(hDlg, NULL, TRUE);
			break;
		case IDC_RADIO7:
			speed = 20;
			SetTimer(hDlg, 1, speed, NULL);
			InvalidateRect(hDlg, NULL, TRUE);
			break;
		case IDC_BUTTON4:
			if (draw == 0) {
				draw = 1;
			}
			else if (draw == 1) {
				draw = 0;
			}
			InvalidateRect(hDlg, NULL, TRUE);
			break;
		case IDC_BUTTON5:
			if (move == 0) {
				move = 1;
			}
			else if (move == 1) {
				move = 0;
			}
			InvalidateRect(hDlg, NULL, TRUE);
			break;
		case IDC_BUTTON6:
			PostQuitMessage(0);
			DestroyWindow(hDlg);
			hDlg = NULL;
			break;
		}
		break;
	case WM_LBUTTONUP:
		Drag = FALSE;
		break;
	case WM_LBUTTONDOWN:
		if (draw == 1) {
			startX = LOWORD(lParam);
			startY = HIWORD(lParam);
			x = startX;
			y = startY;
		}
		Drag = TRUE;
		InvalidateRect(hDlg, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hDlg);
		if (Drag){
			if (draw == 1) {
				SetROP2(hdc, R2_XORPEN);
				SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
				endX = LOWORD(lParam);
				endY = HIWORD(lParam);
				MoveToEx(hdc, startX, startY, NULL);
				LineTo(hdc, oldX, oldY);
				MoveToEx(hdc, startX, startY, NULL);
				LineTo(hdc, endX, endY);
				oldX = endX; oldY = endY;
			}
		}
		ReleaseDC(hDlg, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, oldX, oldY);
		if (g == 0) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, x - size, y - size, x + size, y + size);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (g == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, x - size, y - size, x + size, y + size);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		EndPaint(hDlg, &ps);
		break;
	case WM_TIMER:
		if (move == 1) {
			if (startX > oldX) {
				x -= 1;
			}
			else {
				x += 1;
			}
			y = ((startY - oldY) / (startX - oldX)) * (x - startX) + startY;
			if (oldX - 2 <= x && x <= oldX + 2) {
				if (oldY - 2 <= y && y <= oldY + 2) {
					move = 0;
				}
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
	int mx, my;
	switch (iMsg) {
	case WM_CREATE:
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

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_RBUTTONDOWN:
		hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, (DLGPROC)&ModelessDlgProc);
		ShowWindow(hDlg, SW_SHOW);
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		InvalidateRect(hwnd, NULL, FALSE);
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