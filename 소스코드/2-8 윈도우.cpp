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
	srand(time(NULL));
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT ps;
	HDC hDC;
	static SIZE size;
	static TCHAR str[11][81];
	static TCHAR star[11][81];
	static int count1 = 0;
	static int count2 = 0;
	static int yPos = 0;
	static int d = 0;
	static int g = 0;
	static int k = 0;
	static int e = 0;
	static int w = 0;
	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 2, 15);
		ShowCaret(hWnd);
		count1 = 0;
		count2 = 0;
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_LEFT) {
			count2--;
		}
		else if (wParam == VK_RIGHT) {
			if (str[count1][count2] == '\0') {
				str[count1][count2] = ' ';
			}
			count2++;
		}
		else if (wParam == VK_UP) {
			yPos = yPos - 20;
			count1--;
			if (str[count1][count2] == '\0') {
				for (int i = count1; i < count1 + 1; i++) {
					for (int j = lstrlen(str[count1]); j < count2; j++) {
						str[i][j] = ' ';
					}
				}
			}
		}
		else if (wParam == VK_DOWN) {
			yPos = yPos + 20;
			count1++;
			if (str[count1][count2] == '\0') {
				for (int i = count1; i < count1 + 1; i++) {
					for (int j = lstrlen(str[count1]); j < count2; j++) {
						str[i][j] = ' ';
					}
				}
			}
		}
		else if (wParam == VK_END) {
			count2 = lstrlen(str[count1]);
		}
		else if (wParam == VK_HOME) {
			count2 = 0;
		}
		else if (wParam == VK_F1) {
			d++;
			if (d > 1) {
				d = 0;
			}
		}
		else if (wParam == VK_F2) {
			k++;
			if (k > 1) {
				k = 0;
			}
		}
		else if (wParam == VK_F3) {
			for (int i = count1; i > -1; i--) {
				for (int j = 0; j < lstrlen(str[i]); j++) {
					str[i + 1][j] = str[i][j];
					str[i][j] = ' ';
				}
			}
		}
		else if (wParam == VK_F4) {
			for (int i = 0; i < lstrlen(str[count1]); i++) {
				str[count1][i] = ' ';
			}
		}
		else if (wParam == VK_INSERT) {
			g++;
			if (g > 1) {
				g = 0;
			}
		}
		else if (wParam == VK_DELETE) {
			for (int i = count2; str[count1][i] != ' '; i--) {
				str[count1][i] = ' ';
			}
			for (int i = count2 + 1; str[count1][i] != ' '&&str[count1][i]!='\0'; i++) {
				str[count1][i] = ' ';
			}
		}
		else if (wParam == VK_NEXT) {
			e++;
			int turn = 0;
			if (e == 1) {
				for (int j = 0; j < 10; j++) {
					for (int i = 0; i < lstrlen(str[count1]); i++) {
						if (str[j][i] == ' ' && isalpha(str[j][i + 1]) && turn == 0) {
							str[j][i] = '(';
							turn++;
						}
						else if (str[j][i] == ' ' && isalpha(str[j][i - 1]) && turn == 1) {
							str[j][i] = ')';
							turn--;
						}
					}
				}
			}
			else if (e > 1) {
				e = 0;
				for (int i = 0; i < count1 + 1; i++) {
					for (int j = 0; j < lstrlen(str[i]); j++) {
						if (str[i][j] == '(' || str[i][j] == ')') {
							str[i][j] = ' ';
						}
					}
				}
			}
		}
		else if (wParam == VK_PRIOR) {
			w++;
			int ct = 0;
			if (w == 1) {
				for (int i = 0; i < count1 + 1; i++) {
					for (int j = 0; j < lstrlen(str[i]); j++) {
						star[i][j] = str[i][j];
					}
				}
				for (int i = 0; i < count1 + 1; i++) {
					for (int j = 0; j < lstrlen(str[i]); j++) {
						str[i][j] = ' ';
					}
				}
				for (int i = 0; i < count1 + 1; i++) {
					for (int j = 0; j < lstrlen(star[i]); j++) {
						if (star[i][j] != ' ') {
							str[i][ct] = star[i][j];
							ct++;
						}
					}
					ct = 0;
				}
			}
			else if (w > 1) {
				w = 0;
				for (int i = 0; i < count1 + 1; i++) {
					for (int j = 0; j < lstrlen(str[i]); j++) {
						str[i][j] = star[i][j];
					}
				}
			}
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);
		if (wParam == VK_BACK) {
			if (count1 == 0 && count2 == 0) {
				count1 = 0;
				count2 = 0;
				str[count1][count2] = '\0';
			}
			else if (count2 > 0) {
				count2--;
				str[count1][count2] = '\0';
			}
			else if (count2 == 0) {
				count1--;
				count2 = lstrlen(str[count1]);
				yPos = yPos - 20;
			}
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		else if (wParam == VK_ESCAPE) {
			count1 = 0;
			count2 = 0;
			yPos = 0;
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 81; j++) {
					str[i][j] = NULL;
				}
			}
			str[count1][count2] = '\0';
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		else if (wParam == VK_RETURN) {
			count1++;
			count2 = 0;
			yPos = yPos + 20;
			str[count1][count2] = '\0';
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		else if (wParam == VK_TAB) {
			for (int i = 0; i < 4; i++) {
				str[count1][count2] = ' ';
				count2 += 1;
			}
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		else if (d == 1) {
			str[count1][count2++] = toupper(wParam);
			str[count1][count2] = '\0';
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		else if (g == 1) {
			for (int i = lstrlen(str[count1]); i > count2; i--) {
				str[count1][i + 1] = str[count1][i];
			}
			str[count1][count2++] = wParam;
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		else if (k == 1) {
			str[count1][count2++] = '*';
			str[count1][count2] = '\0';
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		else if (wParam == '+') {
			for (int i = 0; i < count1 + 1; i++) {
				for (int j = 0; j < lstrlen(str[i]); j++) {
					if (str[i][j] <= 57 && str[i][j] >= 48) {
						str[i][j] += 1;
						if (str[i][j] > 57) {
							str[i][j] = 57;
						}
					}
				}
			}
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		else if (wParam == '-') {
			for (int i = 0; i < count1 + 1; i++) {
				for (int j = 0; j < lstrlen(str[i]); j++) {
					if (str[i][j] <= 57 && str[i][j] >= 48) {
						str[i][j] -= 1;
						if (str[i][j] < 48) {
							str[i][j] = 48;
						}
					}
				}
			}
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		else {
			str[count1][count2++] = wParam;
		}
		if (count2 >= 80) {
			count1++;
			count2 = 0;
			yPos = yPos + 20;
		}
		if (count1 >= 10) {
			yPos = 0;
			count1 = 0;
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 10; i++) {
			TextOut(hDC, 0, i * 20, str[i], lstrlen(str[i]));
		}
		GetTextExtentPoint32(hDC, str[count1], count2, &size);
		SetCaretPos(size.cx, yPos);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}
