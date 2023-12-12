#include <windows.h>
#include <tchar.h>
#include<time.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"2023 Window Programming Exam 02반 김도영";	//____________부분에 *반 이름을 넣으세요
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
int  WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_  LPSTR lpszCmdParam, _In_  int nCmdShow) {
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
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	//--- 크기 변경 가능 (기존 (1024, 768))
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1024, 768, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
struct rect {
	int x = -100, y = -100;
	int r = 0, g = 0, b = 0;
	int move = 0;
	int rc = 0;
	int w = 0, v = 0;
};
struct rect item[400];
struct rect bul[200];
struct rect enemy[10];
struct rc {
	int x = -100;
	int y = -100;
	int r = 100, g = 100, b = 100;
	int temp = 0;
	int ct = 0;
};
struct rc wall[400];
struct rc star[1];
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hbrush, oldbrush;
	HDC	hDC;
	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	static int botton = 0;
	static int sf = 0;
	static int j = 0, k = 0;
	static int cng = 0;
	static int t = 0, t2 = 0;
	int mx = 0, my = 0;
	static int v1 = 0;
	static int x1 = 0, y1 = 0;
	static BOOL selection;
	static int r = 0;
	switch (iMessage) {
	case WM_CREATE:
		star[0].x = rand() % 20 * 20;
		star[0].y = rand() % 20 * 20;
		star[0].r = 0;
		star[0].g = 255;
		star[0].b = 0;
		r = 255;
		selection = TRUE;
		botton = 0;
		t2 = 0;
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &rt);
		hDC = BeginPaint(hWnd, &ps);
		mdc = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		Rectangle(mdc, 0, 0, rt.right, rt.bottom);
		for (int i = 0; i < 400; i++) {
			if (i > 0) {
				if (i % 20 == 0) {
					k = 0;
					j++;
				}
			}
			POINT point0[8] = { { 0 + k * 20,0 + j * 20 }, { 20 + k * 20,0 + j * 20 }, { 20 + k * 20,20 + j * 20 }, { 0 + k * 20,20 + j * 20 } };
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(mdc, hPen);
			Polygon(mdc, point0, 4);
			SelectObject(mdc, oldPen);
			DeleteObject(hPen);
			k++;
		}
		if (star[0].temp == 0) {
			hbrush = CreateSolidBrush(RGB(star[0].r, star[0].g, star[0].b));
			oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
			Rectangle(mdc, star[0].x + 5, star[0].y + 5, star[0].x + 15, star[0].y + 15);
			SelectObject(mdc, oldbrush);
			DeleteObject(hbrush);
		}
		if (star[0].temp == 1) {
			hbrush = CreateSolidBrush(RGB(star[0].r, star[0].g, star[0].b));
			oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
			Ellipse(mdc, star[0].x, star[0].y, star[0].x + 20, star[0].y + 20);
			SelectObject(mdc, oldbrush);
			DeleteObject(hbrush);
		}
		for (int i = 0; i < 20; i++) {
			hbrush = CreateSolidBrush(RGB(item[i].r, item[i].g, item[i].b));
			oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
			Rectangle(mdc, item[i].x + 5, item[i].y + 5, item[i].x + 15, item[i].y + 15);
			SelectObject(mdc, oldbrush);
			DeleteObject(hbrush);
		}
		for (int i = 0; i < 10; i++) {
			hbrush = CreateSolidBrush(RGB(enemy[i].r, enemy[i].g, enemy[i].b));
			oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
			Ellipse(mdc, enemy[i].x, enemy[i].y, enemy[i].x + 20, enemy[i].y + 20);
			SelectObject(mdc, oldbrush);
			DeleteObject(hbrush);
		}
		for (int i = 0; i < t; i++) {
			if (bul[i].move == 1) {
				hbrush = CreateSolidBrush(RGB(bul[i].r, bul[i].g, bul[i].b));
				oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
				Rectangle(mdc, bul[i].x - bul[i].w, bul[i].y - bul[i].v, bul[i].x + bul[i].w, bul[i].y + bul[i].v);
				SelectObject(mdc, oldbrush);
				DeleteObject(hbrush);
			}
		}
		for (int i = 0; i <= t2; i++) {
			if (wall[i].ct == 0) {
				hbrush = CreateSolidBrush(RGB(wall[i].r, wall[i].g, wall[i].b));
				oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
				Rectangle(mdc, wall[i].x - 10, wall[i].y - 10, wall[i].x + 10, wall[i].y + 10);
				SelectObject(mdc, oldbrush);
				DeleteObject(hbrush);
			}
		}
		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		x1 = mx;
		v1 = x1 / 20;
		wall[t2].x = (0 + 20 * v1 + 20 + 20 * v1) / 2;
		y1 = my;
		v1 = y1 / 20;
		wall[t2].y = (0 + 20 * v1 + 20 + 20 * v1) / 2;
		t2++;
		k = 0; j = 0;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		k = 0; j = 0;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_DOWN) {
			star[0].y += 20;
			cng = 1;
			for (int i = 0; i < 20; i++) {
				if (item[i].x == star[0].x && item[i].y == star[0].y) {
					star[0].r = item[i].r;
					star[0].g = item[i].g;
					star[0].b = item[i].b;
					item[i].x = -100;
					item[i].y = -100;
					star[0].temp = 1;
				}
			}
			for (int i = 0; i <= t2; i++) {
				if (wall[i].x - 10 == star[0].x && wall[i].y - 10 == star[0].y) {
					wall[i].r = 255;
					wall[i].g = 255;
					wall[i].b = 255;
					wall[i].x = -100;
					wall[i].y = -100;
					wall[i].ct = 1;
					star[0].temp = 0;
					star[0].r = 0;
					star[0].g = r;
					star[0].b = 0;
				}
			}
			k = 0; j = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		else if (wParam == VK_UP) {
			star[0].y -= 20;
			cng = 2;
			for (int i = 0; i < 20; i++) {
				if (item[i].x == star[0].x && item[i].y == star[0].y) {
					star[0].r = item[i].r;
					star[0].g = item[i].g;
					star[0].b = item[i].b;
					item[i].x = -100;
					item[i].y = -100;
					star[0].temp = 1;
				}
			}
			for (int i = 0; i <= t2; i++) {
				if (wall[i].x - 10 == star[0].x && wall[i].y - 10 == star[0].y) {
					wall[i].r = 255;
					wall[i].g = 255;
					wall[i].b = 255;
					wall[i].x = -100;
					wall[i].y = -100;
					wall[i].ct = 1;
					star[0].temp = 0;
					star[0].r = 0;
					star[0].g = r;
					star[0].b = 0;
				}
			}
			k = 0; j = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		else if (wParam == VK_RIGHT) {
			star[0].x += 20;
			cng = 3;
			for (int i = 0; i < 20; i++) {
				if (item[i].x == star[0].x && item[i].y == star[0].y) {
					star[0].r = item[i].r;
					star[0].g = item[i].g;
					star[0].b = item[i].b;
					item[i].x = -100;
					item[i].y = -100;
					star[0].temp = 1;
				}
			}
			for (int i = 0; i <= t2; i++) {
				if (wall[i].x - 10 == star[0].x && wall[i].y - 10 == star[0].y) {
					wall[i].r = 255;
					wall[i].g = 255;
					wall[i].b = 255;
					wall[i].x = -100;
					wall[i].ct = 1;
					wall[i].y = -100;
					star[0].temp = 0;
					star[0].r = 0;
					star[0].g = r;
					star[0].b = 0;
				}
			}
			k = 0; j = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		else if (wParam == VK_LEFT) {
			star[0].x -= 20;
			cng = 4;
			for (int i = 0; i < 20; i++) {
				if (item[i].x == star[0].x && item[i].y == star[0].y) {
					star[0].r = item[i].r;
					star[0].g = item[i].g;
					star[0].b = item[i].b;
					item[i].x = -100;
					item[i].y = -100;
					star[0].temp = 1;
				}
			}
			for (int i = 0; i <= t2; i++) {
				if (wall[i].x - 10 == star[0].x && wall[i].y - 10 == star[0].y) {
					wall[i].r = 255;
					wall[i].g = 255;
					wall[i].b = 255;
					wall[i].x = -100;
					wall[i].y = -100;
					wall[i].ct = 1;
					star[0].temp = 0;
					star[0].r = 0;
					star[0].g = r;
					star[0].b = 0;
				}
			}
			k = 0; j = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		else if (wParam == 'S' || wParam == 's') {
			if (botton == 0) {
				botton++;
			}
			if (botton > 1) {
				botton = 0;
			}
			k = 0; j = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		else if (wParam == 'p' || wParam == 'P') {
			botton = 0;
			for (int i = 0; i < 10; i++) {
				enemy[i].x = rand() % 20 * 20;
				enemy[i].y = rand() % 20 * 20;
				enemy[i].r = 0;
				enemy[i].g = 0;
				enemy[i].b = 255;
				enemy[i].move = 1;
				enemy[i].rc = rand() % 4;
			}
			for (int i = 0; i < 20; i++) {
				item[i].x = rand() % 20 * 20;
				item[i].y = rand() % 20 * 20;
				item[i].r = rand() % 255;
				item[i].g = rand() % 255;
				item[i].b = rand() % 255;
			}
			SetTimer(hWnd, 1, 300, NULL);
			k = 0; j = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		else if (wParam == 't' || wParam == 'T') {
			if (sf == 0) {
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				sf++;
				k = 0; j = 0;
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
			else if (sf == 1) {
				star[0].x = rand() % 20 * 20;
				star[0].y = rand() % 20;
				for (int i = 0; i < 10; i++) {
					enemy[i].x = rand() % 20 * 20;
					enemy[i].y = rand() % 20 * 20;
					enemy[i].r = 0;
					enemy[i].g = 0;
					enemy[i].b = 255;
					enemy[i].move = 1;
					enemy[i].rc = rand() % 4;
				}
				for (int i = 0; i < 20; i++) {
					item[i].x = rand() % 20 * 20;
					item[i].y = rand() % 20 * 20;
					item[i].r = rand() % 255;
					item[i].g = rand() % 255;
					item[i].b = rand() % 255;
				}
				SetTimer(hWnd, 1, 300, NULL);
				sf = 0;
			}
			k = 0; j = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		else if (wParam == 'q' || wParam == 'Q') {
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			PostQuitMessage(0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		else if (wParam == VK_RETURN) {
			if (cng == 1) {
				bul[t].x = star[0].x + 10;
				bul[t].y = star[0].y;
				bul[t].w = 2;
				bul[t].v = 5;
				bul[t].r = 0;
				bul[t].g = 255;
				bul[t].b = 255;
				bul[t].move = 1;
				bul[t].rc = 1;
			}
			else if (cng == 2) {
				bul[t].x = star[0].x + 10;
				bul[t].y = star[0].y + 20;
				bul[t].w = 2;
				bul[t].v = 5;
				bul[t].r = 0;
				bul[t].g = 255;
				bul[t].b = 255;
				bul[t].move = 1;
				bul[t].rc = 0;
			}
			else if (cng == 3) {
				bul[t].x = star[0].x + 20;
				bul[t].y = star[0].y + 10;
				bul[t].w = 5;
				bul[t].v = 2;
				bul[t].r = 0;
				bul[t].g = 255;
				bul[t].b = 255;
				bul[t].move = 1;
				bul[t].rc = 2;
			}
			else if (cng == 4) {
				bul[t].w = 5;
				bul[t].v = 2;
				bul[t].x = star[0].x;
				bul[t].y = star[0].y + 10;
				bul[t].r = 0;
				bul[t].g = 255;
				bul[t].b = 255;
				bul[t].move = 1;
				bul[t].rc = 3;
			}
			t++;
			k = 0; j = 0;
			SetTimer(hWnd, 2, 100, NULL);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			for (int i = 0; i < 10; i++) {
				if (enemy[i].move == 1) {
					if (enemy[i].rc == 0) {//위
						enemy[i].y -= 20;
						if (enemy[i].y == 0) {
							enemy[i].y = 400;
						}
					}
					else if (enemy[i].rc == 1) {//아래
						enemy[i].y += 20;
						if (enemy[i].y == 380) {
							enemy[i].y = 0;
						}
					}
					else if (enemy[i].rc == 2) {//오른쪽
						enemy[i].x += 20;
						if (enemy[i].x == 380) {
							enemy[i].x = 0;
						}
					}
					else if (enemy[i].rc == 3) {//왼쪽
						enemy[i].x -= 20;
						if (enemy[i].x == 0) {
							enemy[i].x = 400;
						}
					}
				}
			}
			k = 0; j = 0;
			break;
		case 2:
			for (int i = 0; i < 200; i++) {
				if (bul[i].move == 1) {
					if (bul[i].rc == 0) {//위
						bul[i].y -= 20;
						if (bul[i].y == 0) {
							bul[i].move = 0;
						}
					}
					else if (bul[i].rc == 1) {//아래
						bul[i].y += 20;
						if (bul[i].y == 400) {
							bul[i].move = 0;
						}
					}
					else if (bul[i].rc == 2) {//오른쪽
						bul[i].x += 20;
						if (bul[i].x == 400) {
							bul[i].move = 0;
						}
					}
					else if (bul[i].rc == 3) {//왼쪽
						bul[i].x -= 20;
						if (bul[i].x == 0) {
							bul[i].move = 0;
						}
					}
				}
			}
			k = 0; j = 0;
			break;
		}
		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 20; i++) {
				if (bul[i].y - 10 <= enemy[j].y && enemy[j].y < bul[i].y) {
					if (bul[i].x <= enemy[j].x && enemy[j].x < bul[i].x + bul[i].w) {
						enemy[j].move = 0;
						enemy[j].r = 0;
						enemy[j].g = 0;
						enemy[j].b = 0;
					}
				}
				if (bul[i].y <= enemy[j].y && enemy[j].y < bul[i].y + 10) {
					if (bul[i].x <= enemy[j].x && enemy[j].x < bul[i].x + bul[i].w) {
						enemy[j].move = 0;
						enemy[j].r = 0;
						enemy[j].g = 0;
						enemy[j].b = 0;
					}
				}
				if (bul[i].x - 10 <= enemy[j].x && enemy[j].x <= bul[i].x) {
					if (bul[i].y <= enemy[j].y && enemy[j].y < bul[i].y + bul[j].v) {
						enemy[j].move = 0;
						enemy[j].r = 0;
						enemy[j].g = 0;
						enemy[j].b = 0;
					}
				}
				if (bul[i].x <= enemy[j].x && enemy[j].x <= bul[i].x + 10) {
					if (bul[i].y <= enemy[j].y && enemy[j].y < bul[i].y + bul[j].v) {
						enemy[j].move = 0;
						enemy[j].r = 0;
						enemy[j].g = 0;
						enemy[j].b = 0;
					}
				}
			}
		}
		k = 0; j = 0;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}