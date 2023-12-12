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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) { // 1.입력받은 문자와 기존에 저장해둔 문자 비교 2.랜덤으로 뽑은 단어의 길이만큼의 네모 출력
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static TCHAR str[1][50];
	static TCHAR dic[10][10] = { {L"apple"},{L"different"},{L"pineapple"},{L"black"},{L"yellow"},{L"purple"},{L"keyboard"},{L"computer"},{L"handphone"},{L"vancouver"} };
	static TCHAR check[1][10];
	static TCHAR answer[1][10];
	static TCHAR precheck[1][10];
	static TCHAR wordlen[10];
	static TCHAR win[25] = L"CONGRATULATION! YOU WIN";
	static TCHAR lose[25] = L"YOU LOSE";
	static SIZE size;
	POINT point0[8] = { {450,530},{450,560}, {550, 560} ,{550, 530} };
	POINT point1[8] = { {50,400},{50,500}, {250, 500} ,{250, 400} };
	POINT point2[4] = { {150,400},{150,50} };
	POINT point3[4] = { {150,50},{300,50} };
	POINT point4[4] = { {300,50},{300,100} };
	POINT point5[4] = { {300,200},{300,300} };
	POINT point6[4] = { {300,230},{250,270} };
	POINT point7[4] = { {300,230},{350,270} };
	POINT point8[4] = { {300,300},{250,340} };
	POINT point9[4] = { {300,300},{350,340} };
	static int r = 0;
	static int count2 = 0;
	static int t = 0, g = 0;
	static int w = 0, m = 0, n = 0;
	switch (iMsg) {
	case WM_CREATE:
		count2 = 0;
		r = rand() % 10;
		for (int i = 0; i < 10; i++) {
			check[0][i] = dic[r][i];
		}
		for (int i = 0; i < lstrlen(check[0]); i++) {
			answer[0][i] = ' ';
		}
		CreateCaret(hwnd, NULL, 2, 15);
		ShowCaret(hwnd);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == VK_DELETE) {
			PostQuitMessage(0);
		}
		else if (wParam == VK_F1) {
			r = rand() % 10;
			for (int i = 0; i < 10; i++) {
				check[0][i] = dic[r][i];
			}
			t = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == VK_BACK) {
			count2--;
			if (count2 <= 0) {
				count2 = 0;
			}
		}
		else if (wParam == VK_RETURN) {
			for (int i = 0; check[0][i] != '\0'; i++) {
				if (str[0][count2 - 1] == check[0][i]) {
					g++;
				}
			}
			if (g == 0) {
				t++;
				n += 40;
				if (t > 6) {
					r = rand() % 10;
					for (int i = 0; i < 10; i++) {
						check[0][i] = dic[r][i];
					}
					for (int i = 0; i < lstrlen(check[0]); i++) {
						answer[0][i] = ' ';
					}
					t = 0;
					n = 0;
				}
			}
			if (g > 0) {
				for (int i = 0; check[0][i] != '\0'; i++) {
					if (str[0][count2 - 1] == check[0][i]) {
						answer[0][i] = check[0][i];
					}
				}
			}
			for (int i = 0; i < check[0][i] != '\0'; i++) {
				if (answer[0][i] == check[0][i]) {
					w++;
				}
			}
			if (w == lstrlen(check[0])) {
				r = rand() % 10;
				for (int i = 0; i < 10; i++) {
					precheck[0][i] = check[0][i];
				}
				for (int i = 0; i < 10; i++) {
					check[0][i] = dic[r][i];
				}
				for (int i = 0; i < 10; i++) {
					answer[0][i] = NULL;
				}
				for (int i = 0; i < lstrlen(check[0]); i++) {
					answer[0][i] = ' ';
				}
				t = 0;
				m++;
			}
			w = 0;
			g = 0;
			count2 = 0;
		}
		else {
			str[0][count2++] = wParam;
		}
		str[0][count2] = '\0';
		InvalidateRect(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Polygon(hdc, point0, 4);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		hBrush = CreateSolidBrush(RGB(0, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Polygon(hdc, point1, 4);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Polygon(hdc, point2, 2);
		Polygon(hdc, point3, 2);
		Polygon(hdc, point4, 2);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		if (t == 1) {
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, 250, 100, 350, 200);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (t == 2) {
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, 250, 100, 350, 200);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point5, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		if (t == 3) {
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, 250, 100, 350, 200);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point5, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point6, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		if (t == 4) {
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, 250, 100, 350, 200);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point5, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point6, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point7, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		if (t == 5) {
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, 250, 100, 350, 200);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point5, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point6, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point7, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point8, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point9, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		if (t == 6) {
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, 250, 100, 350, 200);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point5, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point6, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point7, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point8, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point9, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			TextOut(hdc, 550, 100, lose, lstrlen(lose));
		}
		if (m == 1) {
			TextOut(hdc, 550, 100, win, lstrlen(win));
			TextOut(hdc, 550, 160, precheck[0], lstrlen(precheck[0]));
			m = 0;
			n = 0;
		}
		hBrush = CreateSolidBrush(RGB(255-n, 255-n, 255-n));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 500, 240, 650, 280);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		SetBkColor(hdc, RGB(255-n, 255-n, 255-n));
		TextOut(hdc, 550, 260, answer[0], lstrlen(answer[0]));
		SetBkColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 500, 540, str[0], lstrlen(str[0]));
		wsprintf(wordlen, L"글자 수 : %d", lstrlen(check[0]));
		TextOut(hdc, 550, 200, wordlen, lstrlen(wordlen));
		GetTextExtentPoint32(hdc, str[0], lstrlen(str[0]), &size);
		SetCaretPos(size.cx + 500, 540);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hwnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}