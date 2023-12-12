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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 900, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	POINT point[10] = { {450,400}, {400,450}, {425,500}, {475, 500}, {500, 450} };
	POINT point0[8] = { {300,170},{300,370}, {600, 370} ,{600, 170} };
	POINT point1[6] = { {100,300}, {150,200}, {200,300}};
	POINT point2[10] = { {400,120}, {500, 120},{400,20}, {500, 20}, {450,75} };
	static int x = 200, y = 100, z = 20; //삼각형 색
	static int x1 = 76, y1 = 230, z1 = 180; //오각형 색
	static int x2 = 31, y2 = 17, z2 = 179; //파이 색
	static int x3 = 111, y3 = 7, z3 = 234; //모래시계 색
	static int turn = 0,turn1=0;
	static int i = 0;
	switch (iMsg) {
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == 's' || wParam == 'S') {
			if (turn1 == 0) {
				x3 = rand() % 255;
				y3 = rand() % 255;
				z3 = rand() % 255;
				turn = 2;
				turn1++;
			}
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 't' || wParam == 'T') {
			if (turn1 == 0) {
				x = rand() % 255;
				y = rand() % 255;
				z = rand() % 255;
				turn = 1;
				turn1++;
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'p' || wParam == 'P') {
			if (turn1 == 0) {
				x1 = rand() % 255;
				y1 = rand() % 255;
				z1 = rand() % 255;
				turn = 3;
				turn1++;
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'e' || wParam == 'E') {
			if (turn1 == 0) {
				x2 = rand() % 255;
				y2 = rand() % 255;
				z2 = rand() % 255;
				turn = 4;
				turn1++;
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		else if (wParam == VK_RIGHT) {
			if (turn1 == 0) {
				turn = 4;
				x2 = rand() % 255;
				y2 = rand() % 255;
				z2 = rand() % 255;
				i = 20;
				turn1++;
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_LEFT) {
			if (turn1 == 0) {
				turn = 1;
				x = rand() % 255;
				y = rand() % 255;
				z = rand() % 255;
				i = 20;
				turn1++;
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_UP) {
			if (turn1 == 0) {
				turn = 2;
				x3 = rand() % 255;
				y3 = rand() % 255;
				z3 = rand() % 255;
				i = 20;
				turn1++;
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_DOWN) {
			if (turn1 == 0) {
				turn = 3;
				x1 = rand() % 255;
				y1 = rand() % 255;
				z1 = rand() % 255;
				i = 20;
				turn1++;
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
			break;
		}
	case WM_KEYUP:
		hdc = GetDC(hwnd);
		x = 200, y = 100, z = 20;
		x1 = 76, y1 = 230, z1 = 180;
		x2 = 31, y2 = 17, z2 = 179;
		x3 = 111, y3 = 7, z3 = 234;
		i = 0;
		turn1 = 0;
		InvalidateRgn(hwnd, NULL, FALSE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		InvalidateRgn(hwnd, NULL, FALSE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBrush = CreateSolidBrush(RGB(x, y, z));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Polygon(hdc, point1, 3);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(x1, y1, z1));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Polygon(hdc, point, 5);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(x3, y3, z3));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Polygon(hdc, point2, 5);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(x2, y2, z2));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Pie(hdc, 700, 220, 800, 320, 750, 220, 800, 270);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Polygon(hdc, point0, 4);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		if (turn == 1) {
			POINT point3[6] = { {370+i,350-i}, {530-i,350-i}, {450,210+i} };
			hBrush = CreateSolidBrush(RGB(x, y, z));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point3, 3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if (turn == 2) {
			POINT point3[10] = { {400+i,210+i} ,{500-i,210+i}, {400+i,350-i}, {500-i,350-i}, {450,280} };
			hBrush = CreateSolidBrush(RGB(x3, y3, z3));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point3, 5);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if (turn == 3) {
			POINT point3[10] = { {450,210+i%2}, {375+i,275-i}, {400+i,350-i}, {500-i,350-i} ,{525-i,275-i} };
			hBrush = CreateSolidBrush(RGB(x1, y1, z1));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point3, 5);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if (turn == 4) {
			hBrush = CreateSolidBrush(RGB(x2, y2, z2));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Pie(hdc, 400+i, 220+i, 500-i, 320-i, 450, 220, 500, 270);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}