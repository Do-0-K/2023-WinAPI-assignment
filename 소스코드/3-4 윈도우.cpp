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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 900, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
struct rect {
	int x = 60, y = -60;
	int r = 0, g = 0, b = 0;
	int color = -1;
	int dd = 0;
	RECT ra{};
};
struct rect re[60];
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt{};
	RECT ry{};
	RECT rg{};
	static int k = 0, j = 0;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static int ran = 0;
	static int rancolor = 0, rc = 0, color = 0;
	static int cng = 0, cng1 = 0, cng2 = 0, cng3 = 0;
	static int k1 = 0, turn = 0, turn1 = 0, k2 = 0, k3 = 0;
	static int count = 0, color1 = 0;
	static int n = 0;
	static TCHAR rule[50] = L"~~렉트리스 게임 규칙~~";
	static TCHAR rule1[50] = L"1. 가로 또는 세로로 같은색의 사각형이 4개가 되면 삭제!(무조건 4개만 삭제!)";
	static TCHAR rule2[50] = L"2. 사각형들 삭제 후 아래칸이 비면 위의 사각형들은 아래로 내려온다.";
	static TCHAR rule3[25] = L"~~렉트리스 COMMAND~~";
	static TCHAR rule4[25] = L"1. 화살표로 이동!";
	static TCHAR rule5[50] = L"2. Enter 키로 사각형 회전!";
	int x = 0, y = 0;
	switch (uMsg) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		turn = 0;
		k1 = 0;
		cng = 0;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 72; i++) {
			if (i > 0) {
				if (i % 6 == 0) {
					k = 0;
					j++;
				}
			}
			POINT point0[8] = { {0 + k * 60,0 + j * 60},{60 + k * 60,0 + j * 60}, {60 + k * 60, 60 + j * 60} ,{0 + k * 60, 60 + j * 60} };
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point0, 4);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			k++;
		}
		for (int i = 0; i <= k1; i++) {
			if (re[i].dd == 0) {
				hBrush = CreateSolidBrush(RGB(re[i].r, re[i].g, re[i].b));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, re[i].x, re[i].y, re[i].x + 60, re[i].y + 60);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
			}
		}
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, 600, 100, rule, lstrlen(rule));
		TextOut(hdc, 430, 150, rule1, lstrlen(rule1));
		TextOut(hdc, 430, 200, rule2, lstrlen(rule2));
		TextOut(hdc, 600, 300, rule3, lstrlen(rule3));
		TextOut(hdc, 580, 350, rule4, lstrlen(rule4));
		TextOut(hdc, 580, 400, rule5, lstrlen(rule5));
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == VK_RIGHT) {
			for (int i = k3; i < k1; i++) {
				re[i].x += 60;
				if ((re[i].x + 60) > 360) {
					for (int i = k3; i < k1; i++) {
						re[i].x -= 60;
					}
				}
				if (k2 == 4) {
					if ((re[i].x + 60) == 300) {
						cng = 1;
					}
					else { cng = 0; }
				}
				if (k2 == 2) {
					if ((re[i].x + 60) == 360) {
						cng = 1;
					}
					else { cng = 0; }
				}
			}
			for (int i = 0; i < k3; i++) {
				for (int j = k3; j < k1; j++) {
					if (re[i].y <= re[j].y && re[j].y < (re[i].y + 60)) {
						if ((re[i].x + 60) > re[j].x) {
							for (int v = k3; v < k1; v++) {
								re[v].x -= 60;
							}
							continue;
						}
					}
					else if (re[i].y < (re[j].y + 60) && (re[j].y + 60) <= (re[i].y + 60)) {
						if ((re[i].x + 60) < re[j].x) {
							for (int v = k3; v < k1; v++) {
								re[v].x -= 60;
							}
							continue;
						}
					}
				}
			}
			k = 0; j = 0;
			InvalidateRgn(hWnd, NULL, TRUE);
			ReleaseDC(hWnd, hdc);
		}
		else if (wParam == VK_LEFT) {
			for (int i = k3; i < k1; i++) {
				re[i].x -= 60;
				if (re[i].x < 0) {
					for (int i = k3; i < k1; i++) {
						re[i].x += 60;
					}
				}
				cng = 0;
			}
			for (int i = 0; i < k3; i++) {
				for (int j = k3; j < k1; j++) {
					if (re[i].y <= re[j].y && re[j].y < (re[i].y + 60)) {
						if ((re[i].x + 60) > re[j].x) {
							for (int v = k3; v < k1; v++) {
								re[v].x += 60;
							}
							continue;
						}
					}
					else if (re[i].y < (re[j].y + 60) && (re[j].y + 60) <= (re[i].y + 60)) {
						if ((re[i].x + 60) > re[j].x) {
							for (int v = k3; v < k1; v++) {
								re[v].x += 60;
							}
							continue;
						}
					}
				}
			}
			k = 0; j = 0;
			InvalidateRgn(hWnd, NULL, TRUE);
			ReleaseDC(hWnd, hdc);
		}
		else if (wParam == VK_UP) {
			for (int i = k3; i < k1; i++) {
				re[i].y -= 60;
				if (re[i].y < 0) {
					for (int i = k3; i < k1; i++) {
						re[i].y += 60;
					}
				}
				cng = 0;
			}
			k = 0; j = 0;
			InvalidateRgn(hWnd, NULL, TRUE);
			ReleaseDC(hWnd, hdc);
		}
		else if (wParam == VK_DOWN) {
			for (int i = k3; i < k1; i++) {
				re[i].y += 60;
				if (re[i].y > 660) {
					for (int i = k3; i < k1; i++) {
						re[i].y -= 60;
					}
				}
				if (re[i].y == 660) {
					turn1=1;
				}
			}
			k = 0; j = 0;
			InvalidateRgn(hWnd, NULL, TRUE);
			ReleaseDC(hWnd, hdc);
		}
		else if (wParam == VK_RETURN) {
			if (cng == 0) {
				switch (k2) {
				case 0: break;
				case 1:
					re[k3 + 1].x = re[k3].x;
					re[k3 + 1].y = re[k3].y + 60;
					k2 = 2;
					break;
				case 2:
					re[k3 + 1].y = re[k3].y;
					re[k3 + 1].x = re[k3].x + 60;
					k2 = 1;
					break;
				case 3:
					re[k3 + 1].x = re[k3].x;
					re[k3 + 1].y = re[k3].y + 60;
					re[k3 + 2].x = re[k3].x;
					re[k3 + 2].y = re[k3 + 1].y + 60;
					k2 = 4;
					break;
				case 4:
					re[k3 + 1].y = re[k3].y;
					re[k3 + 1].x = re[k3].x + 60;
					re[k3 + 2].y = re[k3].y;
					re[k3 + 2].x = re[k3 + 1].x + 60;
					k2 = 3;
					break;
				}
			}
			k = 0; j = 0;
			InvalidateRgn(hWnd, NULL, TRUE);
			ReleaseDC(hWnd, hdc);
		}
		break;
	case WM_TIMER:
		if (turn == 0) {
			ran = rand() % 5;
			k2 = ran; //몇 칸인지 담는 값
			k3 = k1; //첫 네모를 담는 값
			rancolor = rand() % 5;
			rc = rancolor; //첫 네모의 색을 담는 값
			switch (ran) {
			case 0://한칸
				re[k1].y = -60;
				k1++;
				break;
			case 1://가로 2칸
				re[k1].y = -60;
				k1++;
				re[k1].y = -60;
				re[k1].x = 120;
				k1++;
				break;
			case 2://세로 2칸
				re[k1].y = -60;
				k1++;
				re[k1].y = 0;
				re[k1].x = 60;
				k1++;
				break;
			case 3://가로 3칸
				re[k1].y = -60;
				k1++;
				re[k1].y = -60;
				re[k1].x = 120;
				k1++;
				re[k1].y = -60;
				re[k1].x = 180;
				k1++;
				break;
			case 4://세로 3칸
				re[k1].y = -60;
				k1++;
				re[k1].y = 0;
				re[k1].x = 60;
				k1++;
				re[k1].y = 60;
				re[k1].x = 60;
				k1++;
				break;
			}
			switch (rancolor) {
			case 0://빨강
				for (int i = k3; i < k1; i++) {
					re[i].r = 255;
					re[i].g = 0;
					re[i].b = 0;
					re[i].color = rancolor;
				}
				break;
			case 1://노랑
				for (int i = k3; i < k1; i++) {
					re[i].r = 255;
					re[i].g = 255;
					re[i].b = 0;
					re[i].color = rancolor;
				}
				break;
			case 2://초록
				for (int i = k3; i < k1; i++) {
					re[i].r = 0;
					re[i].g = 255;
					re[i].b = 0;
					re[i].color = rancolor;
				}
				break;
			case 3://파랑
				for (int i = k3; i < k1; i++) {
					re[i].r = 0;
					re[i].g = 0;
					re[i].b = 255;
					re[i].color = rancolor;
				}
				break;
			case 4://핑쿠
				for (int i = k3; i < k1; i++) {
					re[i].r = 255;
					re[i].g = 0;
					re[i].b = 255;
					re[i].color = rancolor;
				}
				break;
			}
			turn++;
		}
		for (int i = 0; i < k3; i++) {
			for (int j = k3; j < k1; j++) {
				if ((re[j].y + 60) == re[i].y) {
					if (re[i].x <= re[j].x && re[j].x < (re[i].x + 60)) {
						if (cng1 == 0) {
							turn1++;
							cng1++;
							break;
						}
					}
					else if (re[i].x < (re[j].x + 60) && (re[j].x + 60) <= (re[i].x + 60)) {
						if (cng1 == 0) {
							turn1++;
							cng1++;
							break;
						}
					}
				}
			}
		}
		if (turn1 % 2 == 0) {
			for (int i = k3; i < k1; i++) {
				re[i].y += 60;
				if ((re[i].y+60) == 720) {
					turn1=1;
				}
			}
		}
		if (turn1 % 2 == 1) {
			turn = 0;
			turn1++;
			cng1 = 0;
			cng2 = 0;
			count = 0;
			color = 0;
			color1 = 0;
			n = 0;
			for (int i = k3; i < k1; i++) {
				re[i].ra.left = re[i].x;
				re[i].ra.top = re[i].y;
				re[i].ra.right = re[i].x + 60;
				re[i].ra.bottom = re[i].y + 60;
			}
			for (int i = 0; i < k3; i++) {//세로 판별
				for (int j = k3; j < k1; j++) {
					if (re[i].x == re[j].x) {
						if (re[i].color == re[j].color) {
							if (abs(re[i].y - re[j].y) >= 180) {
								color = re[i].color;
								UnionRect(&rt, &re[i].ra, &re[j].ra);
								break;
							}
						}
					}
				}
			}
			for (int i = 0; i < k3; i++) {//가로 판별
				for (int j = k3; j < k1; j++) {
					if (re[i].y == re[j].y) {
						if (re[i].color == re[j].color) {
							if (abs(re[i].x - re[j].x) >= 180) {
								color1 = re[i].color;
								UnionRect(&ry, &re[i].ra, &re[j].ra);
								break;
							}
						}
					}
				}
			}
			for (int i = 0; i < k1; i++) {
				if (rt.left == re[i].x && (re[i].x + 60) == rt.right) {
					if (rt.top <= re[i].y && (re[i].y + 60) <= rt.bottom) {
						if (color == re[i].color) {
							re[i].r = 255;
							re[i].g = 255;
							re[i].b = 255;
							re[i].x = -10000000;
							re[i].y = -10000000;
						}
					}
				}
			}
			for (int i = 0; i < k1; i++) {
				if (rt.left == re[i].x && (re[i].x + 60) == rt.right) {
					count++;
				}
			}
			for (int i = 0; i < k1; i++) {
				if (rt.left == re[i].x && (re[i].x + 60) == rt.right) {
					if (count == 1) {
						re[i].y = 660;
					}
					if (count == 2) {
						re[i].y = 660 - 60 * n;
						n++;
					}
					if (count == 3) {
						re[i].y = 660 - 60 * n;
						n++;
					}
					if (count == 4) {
						re[i].y = 660 - 60 * n;
						n++;
					}
					if (count == 5) {
						re[i].y = 660 - 60 * n;
						n++;
					}
					if (count == 6) {
						re[i].y = 660 - 60 * n;
						n++;
					}
					if (count == 7) {
						re[i].y = 660 - 60 * n;
						n++;
					}
					if (count == 8) {
						re[i].y = 660 - 60 * n;
						n++;
					}
					if (count == 9) {
						re[i].y = 660 - 60 * n;
						n++;
					}
				}
			}
			for (int i = 0; i < k1; i++) {
				if (ry.top == re[i].y && (re[i].y + 60) == ry.bottom) {
					if (ry.left <= re[i].x && (re[i].x + 60) <= ry.right) {
						if (color1 == re[i].color) {
							re[i].r = 255;
							re[i].g = 255;
							re[i].b = 255;
							re[i].x = -10000000;
							re[i].y = -10000000;
						}
					}
				}
			}
			for (int i = 0; i < k1; i++) {
				if (ry.left <= re[i].x && (re[i].x + 60) <= ry.right) {
					if (re[i].y != 660) {
						re[i].y += 60;
					}
				}
			}
		}
		k = 0; j = 0;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}