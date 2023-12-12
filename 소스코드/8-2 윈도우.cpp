#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include "resource2.h"
#define IDC_LISTBOX1 200
#define IDC_BUTTON51 223
#define IDC_BUTTON52 224
#define IDC_BUTTON53 225
#define IDC_BUTTON54 226
#define IDC_BUTTON55 227
#define IDC_BUTTON56 228
#define IDC_BUTTON57 2231
#define IDC_BUTTON58 230
#define IDC_BUTTON59 330
#define IDC_BUTTON60 331
#define IDC_BUTTON61 332
#define IDC_EDIT51 229
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7);
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
static int Selection[3];
static int chose[3];
static HBITMAP hbm[6];
static int t = 0;
static int move = 0;
static TCHAR ba[3][10] = { {L"1 stage"},{L"2 stage"},{L"3 stage"} };
static int x = 0;
struct wall {
	int x = -100, y = -100;
	HBITMAP wal;
	int life = 0;
};
struct wall wa[500];
static HBITMAP wall;
static int test = 0;
static int del = 0;
static HBITMAP you;
static int you_x = 250, you_y = 10;
static int side = 0;
static int t1 = 0;
static TCHAR str[15][45];
static TCHAR stu[3][1];
static HBITMAP hb[6]{};
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
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
	HBITMAP hbmt[2]{};
	HWND b1, b2, b3, b4, b5;
	HWND w1, w2, w3, w4, w5, w6;
	HWND hEdit;
	OPENFILENAME OFN;
	OPENFILENAME SFN;
	TCHAR str1[100], lpstrFile[100] = L"";
	TCHAR filter[100] = L"문서 파일(*.txt) \0*.txt\0";
	static HANDLE hFile;
	DWORD dwWritten , dw;
	WORD wd = 0xFEFF;
	WORD ww = 0xFEFF;
	DWORD dwRead[15]{};
	DWORD dwR;
	TCHAR strRead[15][45];
	TCHAR strR[3][1];
	switch (iMsg) {
	case WM_CREATE:
		child_hWnd = CreateWindow(L"ChildClass", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, 120, 120, 500, 500, hwnd, NULL, g_hInst, NULL);
		list = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_STANDARD, 760, 30, 200, 300, hwnd, (HMENU)IDC_LISTBOX1, g_hInst, NULL);
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
		b1 = CreateWindow(L"button", L"1-이동", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 20, 120, 80, 500, hwnd, (HMENU)IDC_BUTTON51, g_hInst, NULL);
		hbmt[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
		SendMessage(b1, BM_SETIMAGE, 0, (LPARAM)hbmt[0]);
		b2 = CreateWindow(L"button", L"1-이동", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 640, 120, 80, 500, hwnd, (HMENU)IDC_BUTTON52, g_hInst, NULL);
		hbmt[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP27));
		SendMessage(b2, BM_SETIMAGE, 0, (LPARAM)hbmt[1]);
		hEdit = CreateWindow(L"edit", ba[t], WS_CHILD | WS_VISIBLE | WS_BORDER, 280, 30, 160, 60, hwnd, (HMENU)IDC_EDIT51, g_hInst, NULL);
		w1 = CreateWindow(L"button", L"벽 1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 760, 350, 50, 50, hwnd, (HMENU)IDC_BUTTON53, g_hInst, NULL);
		hb[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP29));
		SendMessage(w1, BM_SETIMAGE, 0, (LPARAM)hb[0]);
		w2 = CreateWindow(L"button", L"벽 2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 820, 350, 50, 50, hwnd, (HMENU)IDC_BUTTON54, g_hInst, NULL);
		hb[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP30));
		SendMessage(w2, BM_SETIMAGE, 0, (LPARAM)hb[1]);
		w3 = CreateWindow(L"button", L"벽 3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 880, 350, 50, 50, hwnd, (HMENU)IDC_BUTTON55, g_hInst, NULL);
		hb[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP31));
		SendMessage(w3, BM_SETIMAGE, 0, (LPARAM)hb[2]);
		w4 = CreateWindow(L"button", L"벽 4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 760, 410, 50, 50, hwnd, (HMENU)IDC_BUTTON56, g_hInst, NULL);
		hb[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP32));
		SendMessage(w4, BM_SETIMAGE, 0, (LPARAM)hb[3]);
		w5 = CreateWindow(L"button", L"벽 5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 820, 410, 50, 50, hwnd, (HMENU)IDC_BUTTON57, g_hInst, NULL);
		hb[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP33));
		SendMessage(w5, BM_SETIMAGE, 0, (LPARAM)hb[4]);
		w6 = CreateWindow(L"button", L"벽 6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 880, 410, 50, 50, hwnd, (HMENU)IDC_BUTTON58, g_hInst, NULL);
		hb[5] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP34));
		b3 = CreateWindow(L"button", L"Select", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 760, 480, 80, 40, hwnd, (HMENU)IDC_BUTTON59, g_hInst, NULL);
		b5 = CreateWindow(L"button", L"Delete", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 850, 480, 80, 40, hwnd, (HMENU)IDC_BUTTON61, g_hInst, NULL);
		b4 = CreateWindow(L"button", L"Test", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 760, 550, 170, 60, hwnd, (HMENU)IDC_BUTTON60, g_hInst, NULL);
		SendMessage(w6, BM_SETIMAGE, 0, (LPARAM)hb[5]);
		Selection[0] = -1;
		Selection[1] = -1;
		Selection[2] = -1;
		chose[0] = -1;
		chose[1] = -1;
		chose[2] = -1;
		you = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP11));
		for (int i = 0;i < 15;i++) {
			for (int j = 0;j < 45;j++) {
				str[i][j] = '0';
			}
		}
		for (int i = 0;i < 3;i++) {
			stu[i][0] = '0';
		}
		for (int i = 0;i < 15;i++) {
			for (int j = 0;j < 45;j++) {
				strRead[i][j] = '0';
			}
		}
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
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT) {
			x += 10;
			you_x += 15;
			if (x >= 1000) {
				x -= 10;
			}
			if (you_x >= 1450) {
				you_x -= 15;
			}
			for (int i = 0;i < t1;i++) {
				if (wa[i].y - 16.5 <= you_y && you_y <= wa[i].y + 16.5) {
					if (wa[i].x - 16.5 <= you_x + 22) {
						you_x -= 15;
					}
				}
			}
		}
		else if (wParam == VK_LEFT) {
			x -= 10;
			you_x -= 15;
			if (x <= 0) {
				x += 10;
			}
			if (you_x <= 20) {
				you_x += 15;
			}
		}
		else if (wParam == VK_UP) {
			you_y -= 45;
		}
		InvalidateRect(child_hWnd, NULL, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LISTBOX1:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				if (chose[t] == -1) {
					Selection[t] = SendMessage(list, LB_GETCURSEL, 0, 0);
				}
			}
			break;
		case IDC_BUTTON51:
			t--;
			if (t < 0) {
				t++;
			}
			if (chose[t] == -1) {
				Selection[t] = -1;
			}
			x = 500 * t;
			SetDlgItemText(hwnd, IDC_EDIT51, ba[t]);
			break;
		case IDC_BUTTON52:
			t++;
			if (t > 2) {
				t--;
			}
			if (chose[t] == -1) {
				Selection[t] = -1;
			}
			x = 500 * t;
			SetDlgItemText(hwnd, IDC_EDIT51, ba[t]);
			break;
		case IDC_BUTTON53:
			wall = hb[0];
			del = 0;
			break;
		case IDC_BUTTON54:
			wall = hb[1];
			del = 0;
			break;
		case IDC_BUTTON55:
			wall = hb[2];
			del = 0;
			break;
		case IDC_BUTTON56:
			wall = hb[3];
			del = 0;
			break;
		case IDC_BUTTON57:
			wall = hb[4];
			del = 0;
			break;
		case IDC_BUTTON58:
			wall = hb[5];
			del = 0;
			break;
		case IDC_BUTTON59:
			if (chose[t] == -1) {
				chose[t] = 0;
			}
			break;
		case IDC_BUTTON60:
			test = 1;
			del = -1;
			SetFocus(hwnd);
			break;
		case IDC_BUTTON61:
			del = 1;
			break;
		case ID_40072: //--- 메뉴 선택
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hwnd;
			OFN.lpstrFilter = filter;
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = L".";
			if (GetOpenFileName(&OFN) != 0) {
				wsprintf(str1, L"%s 파일을 여시겠습니까 ?", OFN.lpstrFile);
				MessageBox(hwnd, str1, L"열기 선택", MB_OK);
				hdc = GetDC(hwnd);
				hFile = CreateFile(lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				for (int i = 0;i < 15;i++) {
					ReadFile(hFile, strRead[i], 90, &dwRead[i], NULL);
				}
				for (int i = 0;i < 15;i++) {
					for (int j = 0;j < 45;j++) {
						if (strRead[i][j] == '1') {
							wa[t1].wal = hb[0];
							if (0<= j && j < 15) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (15 <= j && j < 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 5;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (j >= 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 10;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							t1++;
						}
						else if (strRead[i][j] == '2') {
							wa[t1].wal = hb[1];
							if (0 <= j && j < 15) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (15 <= j && j < 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 5;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (j >= 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 10;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							t1++;
						}
						else if (strRead[i][j] == '3') {
							wa[t1].wal = hb[2];
							if (0 <= j && j < 15) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (15 <= j && j < 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 5;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (j >= 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 10;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							t1++;
						}
						else if (strRead[i][j] == '4') {
							wa[t1].wal = hb[3];
							if (0 <= j && j < 15) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (15 <= j && j < 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 5;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (j >= 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 10;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							t1++;
						}
						else if (strRead[i][j] == '5') {
							wa[t1].wal = hb[4];
							if (0 <= j && j < 15) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (15 <= j && j < 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 5;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (j >= 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 10;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							t1++;
						}
						else if (strRead[i][j] == '6') {
							wa[t1].wal = hb[5];
							if (0 <= j && j < 15) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (15 <= j && j < 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 5;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							else if (j >= 30) {
								wa[t1].x = (0 + 33 * j + 33 + 33 * j) / 2 + 10;
								wa[t1].y = (0 + 33 * i + 33 + 33 * i) / 2;
							}
							t1++;
						}
					}
				}
				for (int i = 0;i < 3;i++) {
					ReadFile(hFile, strR[i], 2, &dwR, NULL);
				}
				for (int i = 0;i < 3;i++) {
					if (strR[i][0] == '1') {
						Selection[i] = 0;
					}
					if (strR[i][0] == '2') {
						Selection[i] = 1;
					}
					if (strR[i][0] == '3') {
						Selection[i] = 2;
					}
					if (strR[i][0] == '4') {
						Selection[i] = 3;
					}
					if (strR[i][0] == '5') {
						Selection[i] = 4;
					}
					if (strR[i][0] == '6') {
						Selection[i] = 5;
					}
					chose[i] = 0;
				}
				CloseHandle(hFile);
				ReleaseDC(hwnd, hdc);
				break;
			}
			InvalidateRect(child_hWnd, NULL, FALSE);
			break;
		case ID_40073:
			for (int i = 0;i < 3;i++) {
				if (Selection[i] == 0) {
					stu[i][0] = '1';
				}
				if (Selection[i] == 1) {
					stu[i][0] = '2';
				}
				if (Selection[i] == 2) {
					stu[i][0] = '3';
				}
				if (Selection[i] == 3) {
					stu[i][0] = '4';
				}
				if (Selection[i] == 4) {
					stu[i][0] = '5';
				}
				if (Selection[i] == 5) {
					stu[i][0] = '6';
				}
			}
			memset(&SFN, 0, sizeof(OPENFILENAME));
			SFN.lStructSize = sizeof(OPENFILENAME);
			SFN.hwndOwner = hwnd;
			SFN.lpstrFilter = filter;
			SFN.lpstrFile = lpstrFile;
			SFN.nMaxFile = 256;
			SFN.lpstrInitialDir = L".";
			if (GetSaveFileName(&SFN) != 0) {
				wsprintf(str1, L"%s 파일에 저장하시겠습니까 ?", SFN.lpstrFile);
				MessageBox(hwnd, str1, L"저장하기 선택", MB_OK);
				hFile = CreateFile(lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
				for (int i = 0;i < 15;i++) {
					memcpy(str[i], &wd, 0);
					WriteFile(hFile, str[i], 90, &dwWritten, NULL);
				}
				for (int i = 0;i < 3;i++) {
					memcpy(stu[i], &ww, 0);
					WriteFile(hFile, stu[i], 2, &dw, NULL);
				}
				CloseHandle(hFile);
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
	HDC hdc, kdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HDC mdc;
	HBITMAP hBitmap[3]{};
	HBITMAP oldbit[2]{};
	HBITMAP hbit;
	RECT rt{};
	static HBITMAP s;
	int mx = 0, my = 0;
	static int x1 = 0, y1 = 0, v1 = 0, v2 = 0;
	static int x2 = -500;
	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		SetTimer(hwnd, 1, 50, NULL);
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		kdc = CreateCompatibleDC(hdc);
		mdc = CreateCompatibleDC(kdc);
		hbit = CreateCompatibleBitmap(hdc, 1500, rt.bottom);
		oldbit[0] = (HBITMAP)SelectObject(kdc, hbit);
		for (int i = 0;i < 3;i++) {
			if (chose[i] == 0) {
				oldbit[1] = (HBITMAP)SelectObject(mdc, hBitmap[i]);
				SelectObject(mdc, (HBITMAP)hbm[Selection[i]]);
				StretchBlt(kdc, 500 * i, 0, 500, 500, mdc, 0, 0, 500, 500, SRCCOPY);
			}
		}
		for (int k = 0;k < t1;k++) {
			if (wa[k].life == 0) {
				oldbit[1] = (HBITMAP)SelectObject(mdc, wa[k].wal);
				StretchBlt(kdc, wa[k].x - 16.5, wa[k].y - 16.5, 33, 33, mdc, 0, 0, 50, 50, SRCCOPY);
			}
		}
		if (test == 1) {
			s = (HBITMAP)SelectObject(mdc, you);
			TransparentBlt(kdc, you_x, you_y, 22, 22, mdc, 0, 0, 100, 100, RGB(255, 0, 0));
		}
		StretchBlt(hdc, 0, 0, rt.right, rt.bottom, kdc, x, 0, rt.right, rt.bottom, SRCCOPY);
		if (test == 0) {
			hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, 0, 33, NULL);
			LineTo(hdc, 500, 33);
			MoveToEx(hdc, 0, 66, NULL);
			LineTo(hdc, 500, 66);
			MoveToEx(hdc, 0, 99, NULL);
			LineTo(hdc, 500, 99);
			MoveToEx(hdc, 0, 132, NULL);
			LineTo(hdc, 500, 132);
			MoveToEx(hdc, 0, 165, NULL);
			LineTo(hdc, 500, 165);
			MoveToEx(hdc, 0, 198, NULL);
			LineTo(hdc, 500, 198);
			MoveToEx(hdc, 0, 231, NULL);
			LineTo(hdc, 500, 231);
			MoveToEx(hdc, 0, 264, NULL);
			LineTo(hdc, 500, 264);
			MoveToEx(hdc, 0, 297, NULL);
			LineTo(hdc, 500, 297);
			MoveToEx(hdc, 0, 330, NULL);
			LineTo(hdc, 500, 330);
			MoveToEx(hdc, 0, 363, NULL);
			LineTo(hdc, 500, 363);
			MoveToEx(hdc, 0, 396, NULL);
			LineTo(hdc, 500, 396);
			MoveToEx(hdc, 0, 429, NULL);
			LineTo(hdc, 500, 429);
			MoveToEx(hdc, 0, 462, NULL);
			LineTo(hdc, 500, 462);
			MoveToEx(hdc, 0, 495, NULL);
			LineTo(hdc, 500, 495);

			MoveToEx(hdc, 33, 0, NULL);
			LineTo(hdc, 33, 500);
			MoveToEx(hdc, 66, 0, NULL);
			LineTo(hdc, 66, 500);
			MoveToEx(hdc, 99, 0, NULL);
			LineTo(hdc, 99, 500);
			MoveToEx(hdc, 132, 0, NULL);
			LineTo(hdc, 132, 500);
			MoveToEx(hdc, 165, 0, NULL);
			LineTo(hdc, 165, 500);
			MoveToEx(hdc, 198, 0, NULL);
			LineTo(hdc, 198, 500);
			MoveToEx(hdc, 231, 0, NULL);
			LineTo(hdc, 231, 500);
			MoveToEx(hdc, 264, 0, NULL);
			LineTo(hdc, 264, 500);
			MoveToEx(hdc, 297, 0, NULL);
			LineTo(hdc, 297, 500);
			MoveToEx(hdc, 330, 0, NULL);
			LineTo(hdc, 330, 500);
			MoveToEx(hdc, 363, 0, NULL);
			LineTo(hdc, 363, 500);
			MoveToEx(hdc, 396, 0, NULL);
			LineTo(hdc, 396, 500);
			MoveToEx(hdc, 429, 0, NULL);
			LineTo(hdc, 429, 500);
			MoveToEx(hdc, 462, 0, NULL);
			LineTo(hdc, 462, 500);
			MoveToEx(hdc, 495, 0, NULL);
			LineTo(hdc, 495, 500);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}
		SelectObject(kdc, oldbit[0]);
		DeleteDC(mdc);
		DeleteDC(kdc);
		DeleteObject(hBitmap[t]);
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (del == 0) {
			x1 = mx + 500 * t;
			v1 = x1 / 33;
			wa[t1].x = (0 + 33 * v1 + 33 + 33 * v1) / 2 + 5 * t; 
			y1 = my;
			v2 = y1 / 33;
			wa[t1].y = (0 + 33 * v2 + 33 + 33 * v2) / 2;
			wa[t1].wal = wall;
			if (wa[t1].wal == hb[0]) {
				str[v2][v1] = '1';
			}
			else if (wa[t1].wal == hb[1]) {
				str[v2][v1] = '2';
			}
			else if (wa[t1].wal == hb[2]) {
				str[v2][v1] = '3';
			}
			else if (wa[t1].wal == hb[3]) {
				str[v2][v1] = '4';
			}
			else if (wa[t1].wal == hb[4]) {
				str[v2][v1] = '5';
			}
			else if (wa[t1].wal == hb[5]) {
				str[v2][v1] = '6';
			}
			t1++;
		}
		if (del == 1) {
			for (int i = 0;i < t1;i++) {
				if (wa[i].x - 16.5 <= mx && mx <= wa[i].x + 16.5) {
					if (wa[i].y - 16.5 <= my && my <= wa[i].y + 16.5) {
						wa[i].life = 1;
						str[wa[i].x / 33][wa[i].y / 33] = '0';
					}
				}
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_TIMER:
		if (test == 1) {
			you_y += 10;
			for (int i = 0;i < t1;i++) {
				if (wa[i].x - 16.5 <= you_x && you_x <= wa[i].x + 16.5) {
					if (you_y + 35 >= wa[i].y) {
						you_y -= 10;
					}
				}
			}
			if (you_y >= 500) {
				you_y = -10;
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