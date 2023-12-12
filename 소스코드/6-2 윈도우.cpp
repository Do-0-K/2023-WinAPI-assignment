#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include "resource2.h"
#include <stdio.h>
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
int result = 0;
void calculate(char a, int x, int y) {
	if (a == '+') {
		result = x + y;
	}
	if (a == '-') {
		result = x - y;
	}
	if (a == '*') {
		result = x * y;
	}
	if (a == '/') {
		result = x / y;
	}
}
BOOL CALLBACK ModelessDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static TCHAR x[100];
	static TCHAR cal[100];
	static int t = 0;
	static int num[100];
	static int realnum[10];
	static int s[10];
	static int giho = 1, n = 0, gesu = 0;
	static int k = 0, k1 = 0, a = 0;
	static int mok = 0, nmg = 0, c = 0;
	static double su = 1;
	static char sag[12];
	static int n1 = 0;
	switch (iMsg) {
	case WM_INITDIALOG:
		t = 0;
		x[t] = '0';
		s[0]=-1;
		for (int i = 0;i < 100;i++) {
			x[i] = NULL;
		}
		for (int i = 0;i < 12;i++) {
			sag[i] = NULL;
		}
		SetDlgItemText(hDlg, IDC_EDIT1, x);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1:
			x[t++] = '1';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON2:
			x[t++] = '2';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON3:
			x[t++] = '3';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON4:
			x[t++] = '4';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON5:
			x[t++] = '5';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON6:
			x[t++] = '6';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON7:
			x[t++] = '7';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON8:
			x[t++] = '8';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON9:
			x[t++] = '9';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON10:
			x[t++] = '+';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON11:
			x[t++] = '-';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON12:
			x[t++] = '*';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON13:
			x[t++] = '/';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON14:
			x[t++] = '0';
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON15:// = 결과값을 계산해줘야함
			gesu = 0;
			for (int i = 0;i <= t;i++) {
				if (x[i] == '+' || x[i] == '-' || x[i] == '*' || x[i] == '/'||x[i] == NULL) {
					s[giho] = i;
					cal[a] = x[i];
					for (int j = s[giho-1]+1;j < s[giho];j++) {
						num[n] = x[j] - 48;
						gesu++;
						n++;
					}
					switch (gesu) {
					case 1:
						realnum[k1] = num[0];
						break;
					case 2:
						realnum[k1] = num[0] * 10 + num[1];
						break;
					case 3:
						realnum[k1] = num[0] * 100 + num[1] * 10 + num[2];
						break;
					case 4:
						realnum[k1] = num[0] * 1000 + num[1] * 100 + num[2]*10+num[3];
						break;
					case 5:
						realnum[k1] = num[0] * 10000 + num[1] * 1000 + num[2] * 100 + num[3] * 10 + num[4];
						break;
					}
					k1++;
					k = 0;
					n = 0;
					gesu = 0;
					giho++;
					a++;
				}
			}
			switch (a-1) {
			case 1:
				calculate(cal[0], realnum[0], realnum[1]);
				break;
			case 2:
				calculate(cal[0], realnum[0], realnum[1]);
				calculate(cal[1], result, realnum[2]);
				break;
			case 3:
				calculate(cal[0], realnum[0], realnum[1]);
				calculate(cal[1], result, realnum[2]);
				calculate(cal[2], result, realnum[3]);
				break;
			case 4:
				calculate(cal[0], realnum[0], realnum[1]);
				calculate(cal[1], result, realnum[2]);
				calculate(cal[2], result, realnum[3]);
				calculate(cal[3], result, realnum[4]);
				break;
			}
			lstrcpy(x, L" ");
			for (int i = 0;i < t;i++) {
				x[i] = NULL;
			}
			t = 0;
			wsprintf(x, L"%d",result);
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON16:// R
			giho = 1;
			for (int i = 0;i <= t;i++) {
				if (x[i] == '+' || x[i] == '-' || x[i] == '*' || x[i] == '/' || x[i] == NULL) {
					s[giho] = i;
					for (int j = s[giho - 1]+1;j < s[giho];j++) {
						num[n] = x[j] - 48;
						n++;
					}
					for (int k = s[giho - 1]+1;k < s[giho];k++) {
						x[k] = num[n - 1]+48;
						n--;
					}
					n = 0;
					gesu = 0;
					giho++;
				}
			}
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON17:// CE
			x[t - 1] = ' ';
			t--;
			if (t <= 0) {
				t = 0;
				x[t] = '0';
			}
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON18:// C
			lstrcpy(x, L" ");
			for (int i = 0;i < t;i++) {
				x[i] = NULL;
			}
			k1 = 0;
			gesu = 0;
			giho = 1;
			s[0] = -1;
			t = 0;
			a = 0;
			x[t] = '0';
			su = 1;
			n = 0;
			mok = 0;
			nmg = 0;
			n1 = 0;
			result = 0;
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON19://2진수
			gesu = 0;
			for (int i = 0;i <= t;i++) {
				if (x[i] == NULL) {
					s[giho] = i;
					cal[a] = x[i];
					for (int j = s[giho - 1] + 1;j < s[giho];j++) {
						num[n] = x[j] - 48;
						gesu++;
						n++;
					}
					switch (gesu) {
					case 1:
						realnum[0] = num[0];
						break;
					case 2:
						realnum[0] = num[0] * 10 + num[1];
						break;
					case 3:
						realnum[0] = num[0] * 100 + num[1] * 10 + num[2];
						break;
					case 4:
						realnum[0] = num[0] * 1000 + num[1] * 100 + num[2] * 10 + num[3];
						break;
					case 5:
						realnum[0] = num[0] * 10000 + num[1] * 1000 + num[2] * 100 + num[3] * 10 + num[4];
						break;
					}
				}
			}
			n = 0;
			do{
				mok = realnum[0] / 2;
				nmg = realnum[0] - mok * 2;
				num[n] = nmg;
				n++;
				realnum[0] = mok;
			} while (mok != 0);
			n1 = n;
			for (int k = 0;k < n1;k++) {
				x[k] = num[n-1] + 48;
				t++;
				n--;
			}
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON20://1/x
			gesu = 0;
			for (int i = 0;i <= t;i++) {
				if (x[i] == NULL) {
					s[giho] = i;
					cal[a] = x[i];
					for (int j = s[giho - 1] + 1;j < s[giho];j++) {
						num[n] = x[j] - 48;
						gesu++;
						n++;
					}
					switch (gesu) {
					case 1:
						realnum[0] = num[0];
						break;
					case 2:
						realnum[0] = num[0] * 10 + num[1];
						break;
					case 3:
						realnum[0] = num[0] * 100 + num[1] * 10 + num[2];
						break;
					case 4:
						realnum[0] = num[0] * 1000 + num[1] * 100 + num[2] * 10 + num[3];
						break;
					case 5:
						realnum[0] = num[0] * 10000 + num[1] * 1000 + num[2] * 100 + num[3] * 10 + num[4];
						break;
					}
				}
			}
			su /= float(realnum[0]);
			lstrcpy(x, L" ");
			for (int i = 0;i < t;i++) {
				x[i] = NULL;
			}
			t = 0;
			sprintf(sag, "%f", su);
			for (int i = 0;i < 12;i++) {
				x[i] = sag[i];
			}
			su = 1;
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON21:// *10
			gesu = 0;
			for (int i = 0;i <= t;i++) {
				if (x[i] == NULL) {
					s[giho] = i;
					cal[a] = x[i];
					for (int j = s[giho - 1] + 1;j < s[giho];j++) {
						num[n] = x[j] - 48;
						gesu++;
						n++;
					}
					switch (gesu) {
					case 1:
						realnum[0] = num[0];
						break;
					case 2:
						realnum[0] = num[0] * 10 + num[1];
						break;
					case 3:
						realnum[0] = num[0] * 100 + num[1] * 10 + num[2];
						break;
					case 4:
						realnum[0] = num[0] * 1000 + num[1] * 100 + num[2] * 10 + num[3];
						break;
					case 5:
						realnum[0] = num[0] * 10000 + num[1] * 1000 + num[2] * 100 + num[3] * 10 + num[4];
						break;
					}
				}
			}
			num[n] = 0;
			n++;
			t = 0;
			for (int k = 0;k < n;k++) {
				x[k] = num[k] + 48;
				t++;
			}
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON22://back
			x[t-1] = ' ';
			t--;
			if (t <= 0) {
				t = 0;
				x[t] = '0';
			}
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDC_BUTTON23://10x
			gesu = 0;
			for (int i = 0;i <= t;i++) {
				if (x[i] == NULL) {
					s[giho] = i;
					cal[a] = x[i];
					for (int j = s[giho - 1] + 1;j < s[giho];j++) {
						num[n] = x[j] - 48;
						gesu++;
						n++;
					}
					switch (gesu) {
					case 1:
						realnum[0] = num[0];
						break;
					case 2:
						realnum[0] = num[0] * 10 + num[1];
						break;
					case 3:
						realnum[0] = num[0] * 100 + num[1] * 10 + num[2];
						break;
					case 4:
						realnum[0] = num[0] * 1000 + num[1] * 100 + num[2] * 10 + num[3];
						break;
					case 5:
						realnum[0] = num[0] * 10000 + num[1] * 1000 + num[2] * 100 + num[3] * 10 + num[4];
						break;
					}
				}
			}
			n = 0;
			num[n] = 1;
			n++;
			for (int i = 1;i <= realnum[0];i++) {
				num[n] = 0;
				n++;
			}
			t = 0;
			for (int k = 0;k < n;k++) {
				x[k] = num[k] + 48;
				t++;
			}
			SetDlgItemText(hDlg, IDC_EDIT1, x);
			break;
		case IDCANCEL:
			DestroyWindow(hDlg);
			hDlg = NULL;
			break;
		}
		break;
	case WM_CHAR:
		if (wParam == VK_BACK) {
			t--;
		}
		else {
			x[t++] = wParam;
		}
		x[t++] = '\0';
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
	static BOOL Selection;
	static int x = 0;
	int mx;
	switch (iMsg) {
	case WM_CREATE:
		Selection = FALSE;
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		Rectangle(mdc, 0, 0, rt.right, rt.bottom);

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, (DLGPROC)&ModelessDlgProc);
		ShowWindow(hDlg, SW_SHOW);
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