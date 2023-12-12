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
struct rect {
	int x = -100, y = 80;
	int temp = -1;
	int cng = 0;
	int live = 0;
};
struct rect r[20];
struct ject {
	int x = 400, y = 300;
};
struct ject re[1];
struct sect {
	int x = -100, y = -100;
	int live = 0;
	int mx = 0, my = 0;
};
struct sect wall[20];
struct kect {
	int x = -100, y = -100;
	int r = 0, g = 0, b = 0;
	int move = 0;
	int rc = 0;
	int w = 0, v = 0;
};
struct kect bul[200];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc, memdc, kdc;
	HPEN hPen, oldPen;
	HBRUSH hbrush, oldbrush;
	PAINTSTRUCT ps;
	static HBITMAP hbitmap[5];
	static HBITMAP hBitmap[3];
	static HBITMAP oldbit[5];
	static HBITMAP backhbit{};
	static HBITMAP hbit{};
	static HBITMAP HBitmap[1];
	static BOOL drag;
	static RECT rt{};
	static int cnt = 0;
	static int cnt1 = 0;
	int mx = 0, my = 0;
	static int t = 1, t1 = 0;
	static int ran = 0;
	static int temp = 0, temp1 = 0, temp2 = 0, temp3 = 0;
	static int v = 0, v1 = 0, v2 = 0, v3 = 0;
	static int c = 0, c1 = 0, c2 = 0, c3 = 0;
	static int cng = 0;
	static int rancnt = 0;
	static int a = 0, s = 0, p = 0;
	int mx1 = 0, my1 = 0;
	switch (iMsg) {
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rt);
		backhbit = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7)); //배경
		hbitmap[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP8)); //적
		hbitmap[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP9));
		hbitmap[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP10));
		hbitmap[3] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP11));
		hbitmap[4] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP12));
		hBitmap[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3)); //주인공
		hBitmap[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		hBitmap[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
		HBitmap[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2)); //장애물
		hbit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SetTimer(hwnd, 1, 200, NULL);
		ran = rand() % 5;
		switch (ran) {
		case 0:
			for (int i = 0;i < 1;i++) {
				r[i].x = rand() % (rt.right - 180) + 50;
				r[i].temp = rand() % 2;
				r[i].y = rand() % (rt.bottom - 180) + 50;
			}
			if (r[0].temp == 0) {
				r[1].x = r[0].x - 80;
				r[2].x = r[0].x + 80;
				r[1].y = r[0].y;
				r[2].y = r[0].y;
			}
			else {
				r[1].y = r[0].y - 80;
				r[2].y = r[0].y + 80;
				r[1].x = r[0].x;
				r[2].x = r[0].x;
			}
			r[1].temp = r[0].temp;
			r[2].temp = r[0].temp;
			t = 3;
			break;
		case 1:
			for (int i = 0;i < 2;i++) {
				r[i].x = rand() % (rt.right - 180) + 50;
				r[i].temp = rand() % 2;
				r[i].y = rand() % (rt.bottom - 180) + 50;
			}
			temp = r[1].x;
			v = r[1].temp;
			c = r[1].y;
			if (r[0].temp == 0) {
				r[1].x = r[0].x - 80;
				r[2].x = r[0].x + 80;
				r[1].y = r[0].y;
				r[2].y = r[0].y;
			}
			else {
				r[1].y = r[0].y - 80;
				r[2].y = r[0].y + 80;
				r[1].x = r[0].x;
				r[2].x = r[0].x;
			}
			r[1].temp = r[0].temp;
			r[2].temp = r[0].temp;
			if (v == 0) {
				r[3].x = temp;
				r[4].x = temp - 80;
				r[5].x = temp + 80;
				r[3].y = c;
				r[4].y = c;
				r[5].y = c;
			}
			else {
				r[3].y = c;
				r[4].y = c - 80;
				r[5].y = c + 80;
				r[3].x = temp;
				r[4].x = temp;
				r[5].x = temp;
			}
			r[3].temp = v;
			r[4].temp = v;
			r[5].temp = v;
			t = 6;
			break;
		case 2:
			for (int i = 0;i < 3;i++) {
				r[i].x = rand() % (rt.right - 180) + 50;
				r[i].temp = rand() % 2;
				r[i].y = rand() % (rt.bottom - 180) + 50;
			}
			temp = r[1].x;
			v = r[1].temp;
			c = r[1].y;
			temp1 = r[2].x;
			v1 = r[2].temp;
			c1 = r[2].y;
			if (r[0].temp == 0) {
				r[1].x = r[0].x - 80;
				r[2].x = r[0].x + 80;
				r[1].y = r[0].y;
				r[2].y = r[0].y;
			}
			else {
				r[1].y = r[0].y - 80;
				r[2].y = r[0].y + 80;
				r[1].x = r[0].x;
				r[2].x = r[0].x;
			}
			r[1].temp = r[0].temp;
			r[2].temp = r[0].temp;
			if (v == 0) {
				r[3].x = temp;
				r[4].x = temp - 80;
				r[5].x = temp + 80;
				r[3].y = c;
				r[4].y = c;
				r[5].y = c;
			}
			else {
				r[3].y = c;
				r[4].y = c - 80;
				r[5].y = c + 80;
				r[3].x = temp;
				r[4].x = temp;
				r[5].x = temp;
			}
			r[3].temp = v;
			r[4].temp = v;
			r[5].temp = v;
			if (v1 == 0) {
				r[6].x = temp1;
				r[7].x = temp1 - 80;
				r[8].x = temp1 + 80;
				r[6].y = c1;
				r[7].y = c1;
				r[8].y = c1;
			}
			else {
				r[6].y = c1;
				r[7].y = c1 - 80;
				r[8].y = c1 + 80;
				r[6].x = temp1;
				r[7].x = temp1;
				r[8].x = temp1;
			}
			r[6].temp = r[7].temp = r[8].temp = v1;
			t = 9;
			break;
		case 3:
			for (int i = 0;i < 4;i++) {
				r[i].x = rand() % (rt.right - 180) + 50;
				r[i].temp = rand() % 2;
				r[i].y = rand() % (rt.bottom - 180) + 50;
			}
			temp = r[1].x;
			v = r[1].temp;
			c = r[1].y;
			temp1 = r[2].x;
			v1 = r[2].temp;
			c1 = r[2].y;
			temp2 = r[3].x;
			v2 = r[3].temp;
			c2 = r[3].y;
			if (r[0].temp == 0) {
				r[1].x = r[0].x - 80;
				r[2].x = r[0].x + 80;
				r[1].y = r[0].y;
				r[2].y = r[0].y;
			}
			else {
				r[1].y = r[0].y - 80;
				r[2].y = r[0].y + 80;
				r[1].x = r[0].x;
				r[2].x = r[0].x;
			}
			r[1].temp = r[0].temp;
			r[2].temp = r[0].temp;
			if (v == 0) {
				r[3].x = temp;
				r[4].x = temp - 80;
				r[5].x = temp + 80;
				r[3].y = c;
				r[4].y = c;
				r[5].y = c;
			}
			else {
				r[3].y = c;
				r[4].y = c - 80;
				r[5].y = c + 80;
				r[3].x = temp;
				r[4].x = temp;
				r[5].x = temp;
			}
			r[3].temp = v;
			r[4].temp = v;
			r[5].temp = v;
			if (v1 == 0) {
				r[6].x = temp1;
				r[7].x = temp1 - 80;
				r[8].x = temp1 + 80;
				r[6].y = c1;
				r[7].y = c1;
				r[8].y = c1;
			}
			else {
				r[6].y = c1;
				r[7].y = c1 - 80;
				r[8].y = c1 + 80;
				r[6].x = temp1;
				r[7].x = temp1;
				r[8].x = temp1;
			}
			r[6].temp = r[7].temp = r[8].temp = v1;
			if (v2 == 0) {
				r[9].x = temp2;
				r[10].x = temp2 - 80;
				r[11].x = temp2 + 80;
				r[9].y = c2;
				r[10].y = c2;
				r[11].y = c2;
			}
			else {
				r[9].y = c2;
				r[10].y = c2 - 80;
				r[11].y = c2 + 80;
				r[9].x = temp2;
				r[10].x = temp2;
				r[11].x = temp2;
			}
			r[9].temp = r[10].temp = r[11].temp = v2;
			t = 12;
			break;
		case 4:
			for (int i = 0;i < 5;i++) {
				r[i].x = rand() % (rt.right - 180) + 50;
				r[i].temp = rand() % 2;
				r[i].y = rand() % (rt.bottom - 180) + 50;
			}
			temp = r[1].x;
			v = r[1].temp;
			c = r[1].y;
			temp1 = r[2].x;
			v1 = r[2].temp;
			c1 = r[2].y;
			temp2 = r[3].x;
			v2 = r[3].temp;
			c2 = r[3].y;
			temp3 = r[4].x;
			v3 = r[4].temp;
			c3 = r[4].y;
			if (r[0].temp == 0) {
				r[1].x = r[0].x - 80;
				r[2].x = r[0].x + 80;
				r[1].y = r[0].y;
				r[2].y = r[0].y;
			}
			else {
				r[1].y = r[0].y - 80;
				r[2].y = r[0].y + 80;
				r[1].x = r[0].x;
				r[2].x = r[0].x;
			}
			r[1].temp = r[0].temp;
			r[2].temp = r[0].temp;
			if (v == 0) {
				r[3].x = temp;
				r[4].x = temp - 80;
				r[5].x = temp + 80;
				r[3].y = c;
				r[4].y = c;
				r[5].y = c;
			}
			else {
				r[3].y = c;
				r[4].y = c - 80;
				r[5].y = c + 80;
				r[3].x = temp;
				r[4].x = temp;
				r[5].x = temp;
			}
			r[3].temp = v;
			r[4].temp = v;
			r[5].temp = v;
			if (v1 == 0) {
				r[6].x = temp1;
				r[7].x = temp1 - 80;
				r[8].x = temp1 + 80;
				r[6].y = c1;
				r[7].y = c1;
				r[8].y = c1;
			}
			else {
				r[6].y = c1;
				r[7].y = c1 - 80;
				r[8].y = c1 + 80;
				r[6].x = temp1;
				r[7].x = temp1;
				r[8].x = temp1;
			}
			r[6].temp = r[7].temp = r[8].temp = v1;
			if (v2 == 0) {
				r[9].x = temp2;
				r[10].x = temp2 - 80;
				r[11].x = temp2 + 80;
				r[9].y = c2;
				r[10].y = c2;
				r[11].y = c2;
			}
			else {
				r[9].y = c2;
				r[10].y = c2 - 80;
				r[11].y = c2 + 80;
				r[9].x = temp2;
				r[10].x = temp2;
				r[11].x = temp2;
			}
			r[9].temp = r[10].temp = r[11].temp = v2;
			if (v3 == 0) {
				r[12].x = temp3;
				r[13].x = temp3 - 80;
				r[14].x = temp3 + 80;
				r[12].y = c3;
				r[13].y = c3;
				r[14].y = c3;
			}
			else {
				r[12].y = c3;
				r[13].y = c3 - 80;
				r[14].y = c3 + 80;
				r[12].x = temp3;
				r[13].x = temp3;
				r[14].x = temp3;
			}
			r[12].temp = r[13].temp = r[14].temp = v3;
			t = 15;
			break;
		}
		rancnt = rand()%10+3;
		for (int i = 0;i < rancnt;i++) {
			a = rand() % 10;
			s = rand() % 8;
			wall[i].x = 80*a;
			wall[i].y = 80*s;
		}
		SetTimer(hwnd, 2, 100, NULL);
		SetTimer(hwnd, 3, 100, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		oldbit[0] = (HBITMAP)SelectObject(memdc, hbit); //--- hBit: 이미지가 저장되어 있는 비트맵 전역 변수
		StretchBlt(hdc, 0, 0, rt.right, rt.bottom, memdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
		SelectObject(memdc, oldbit[0]);
		DeleteDC(memdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			hdc = GetDC(hwnd);
			memdc = CreateCompatibleDC(hdc); //--- 더블 버퍼로 사용 할 메모리 DC 생성
			kdc = CreateCompatibleDC(memdc); //--- 이미지를 저장 할 메모리 DC 생성
			oldbit[0] = (HBITMAP)SelectObject(memdc, hbit); //--- MemDC와 hBit 를 호환되게 선택함
			oldbit[1] = (HBITMAP)SelectObject(kdc, backhbit); //--- 배경 이미지
			StretchBlt(memdc, 0, 0, rt.right, rt.bottom, kdc, 0, 0, 500, 500, SRCCOPY);
			oldbit[2] = (HBITMAP)SelectObject(kdc, hbitmap[cnt]); //--- 애니메이션 이미지
			for (int i = 0;i < t;i++) {
				if (0 <= r[i].live && r[i].live < 3) {
					TransparentBlt(memdc, r[i].x, r[i].y, 80, 80, kdc, 0, 0, 100, 100, RGB(255, 0, 0));
				}
			}
			cnt++; //--- 애니메이션 이미지 순서
			if (cnt >= 4) {
				cnt = 0;
			}
			oldbit[3] = (HBITMAP)SelectObject(kdc, hBitmap[cnt1]);
			TransparentBlt(memdc, re[0].x, re[0].y, 80, 80, kdc, 0, 0, 300, 300, RGB(255, 255, 255));
			//--- MemDC에 배경과 애니메이션 저장  hBit 비트맵에 저장
			cnt1++; //--- 애니메이션 이미지 순서
			if (cnt1 >= 3) {
				cnt1 = 0;
			}
			oldbit[4] = (HBITMAP)SelectObject(kdc, HBitmap[0]);
			for (int i = 0;i < rancnt;i++) {
				if (0 <= wall[i].live && wall[i].live < 3) {
					StretchBlt(memdc, wall[i].x, wall[i].y, 80, 80, kdc, 0, 0, 650, 400, SRCCOPY);
				}
			}
			for (int i = 0; i < t1; i++) {
				if (bul[i].move == 1) {
					hbrush = CreateSolidBrush(RGB(bul[i].r, bul[i].g, bul[i].b));
					oldbrush = (HBRUSH)SelectObject(memdc, hbrush);
					Rectangle(memdc, bul[i].x - bul[i].w, bul[i].y - bul[i].v, bul[i].x + bul[i].w, bul[i].y + bul[i].v);
					SelectObject(memdc, oldbrush);
					DeleteObject(hbrush);
				}
			}
			DeleteDC(memdc);
			DeleteObject(kdc);
			ReleaseDC(hwnd, hdc);
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 2:
			for (int i = 0;i < t;i++) {
				if (r[i].live < 3) {
					if (r[i].temp == 1) {
						if (r[i].cng % 2 == 0) {
							r[i].x -= 10;
						}
						if (r[i].cng % 2 == 1) {
							r[i].x += 10;
						}
						if (r[i].x >= rt.right - 60) {
							r[i].cng++;
						}
						if (r[i].x <= -30) {
							r[i].cng++;
						}
						for (int j = 0;j < rancnt;j++) {
							if (wall[j].live < 3) {
								if (wall[j].y <= r[i].y && r[i].y <= wall[j].y + 80) {
									if (wall[j].x <= r[i].x && r[i].x <= wall[j].x + 80) {
										r[i].cng++;
									}
									else if (wall[j].x <= r[i].x + 80 && r[i].x + 80 <= wall[j].x + 80) {
										r[i].cng++;
									}
								}
								else if(wall[j].y <= r[i].y+80 && r[i].y+80 <= wall[j].y + 80) {
									if (wall[j].x <= r[i].x && r[i].x <= wall[j].x + 80) {
										r[i].cng++;
									}
									else if (wall[j].x <= r[i].x + 80 && r[i].x + 80 <= wall[j].x + 80) {
										r[i].cng++;
									}
								}
							}
						}
					}
					if (r[i].temp == 0) {
						if (r[i].cng % 2 == 0) {
							r[i].y += 10;
						}
						if (r[i].cng % 2 == 1) {
							r[i].y -= 10;
						}
						if (r[i].y >= 550) {
							r[i].cng++;
						}
						if (r[i].y <= -30) {
							r[i].cng++;
						}
						for (int j = 0;j < rancnt;j++) {
							if (wall[j].live < 3) {
								if (wall[j].x <= r[i].x && r[i].x <= wall[j].x + 80) {
									if (wall[j].y <= r[i].y && r[i].y <= wall[j].y + 80) {
										r[i].cng++;
									}
									else if (wall[j].y <= r[i].y + 80 && r[i].y + 80 <= wall[j].y + 80) {
										r[i].cng++;
									}
								}
								else if (wall[j].y <= r[i].y + 80 && r[i].y+ 80 <= wall[j].y + 80) {
									if (wall[j].y <= r[i].y && r[i].y <= wall[j].y + 80) {
										r[i].cng++;
									}
									else if (wall[j].y <= r[i].y + 80 && r[i].y + 80 <= wall[j].y + 80) {
										r[i].cng++;
									}
								}
							}
						}
					}
				}
			}
			break;
		case 3:
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
						if (bul[i].y == 700) {
							bul[i].move = 0;
						}
					}
					else if (bul[i].rc == 2) {//오른쪽
						bul[i].x += 20;
						if (bul[i].x == 800) {
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
			break;
		}
		for (int i = 0;i < t;i++) {
			if (r[i].live < 3) {
				for (int j = 0;j < 200;j++) {
					if (bul[j].move == 1) {
						if (r[i].x <= bul[j].x && bul[j].x <= r[i].x + 80) {
							if (r[i].y <= bul[j].y && bul[j].y <= r[i].y + 80) {
								bul[j].x = -100;
								bul[j].y = -100;
								bul[j].move = 0;
								r[i].live++;
								if (r[i].live == 3) {
									r[i].x = -100;
									r[i].y = -100;
									cnt = 4;
								}
							}
							else if (r[i].y <= bul[j].y + bul[j].v && bul[j].y + bul[j].v <= r[i].y + 80) {
								bul[j].x = -100;
								bul[j].y = -100;
								bul[j].move = 0;
								r[i].live++;
								if (r[i].live == 3) {
									r[i].x = -100;
									r[i].y = -100;
									cnt = 4;
								}
							}
						}
						if (r[i].y <= bul[j].y && bul[j].y <= r[i].y + 80) {
							if (r[i].x <= bul[j].x && bul[j].x <= r[i].x + 80) {
								bul[j].x = -100;
								bul[j].y = -100;
								bul[j].move = 0;
								r[i].live++;
								if (r[i].live == 3) {
									r[i].x = -100;
									r[i].y = -100;
									cnt = 4;
								}
							}
							else if (r[i].x <= bul[j].x + bul[j].w && bul[j].x + bul[j].w <= r[i].x + 80) {
								bul[j].x = -100;
								bul[j].y = -100;
								bul[j].move = 0;
								r[i].live++;
								if (r[i].live == 3) {
									r[i].x = -100;
									r[i].y = -100;
									cnt = 4;
								}
							}
						}
					}
				}
			}
		}
		for (int i = 0;i < rancnt;i++) {
			if (wall[i].live < 3) {
				for (int j = 0;j < 200;j++) {
					if (bul[j].move == 1) {
						if (wall[i].x <= bul[j].x && bul[j].x <= wall[i].x + 80) {
							if (wall[i].y <= bul[j].y && bul[j].y <= wall[i].y + 80) {
								bul[j].x = -100;
								bul[j].y = -100;
								bul[j].move = 0;
								wall[i].live++;
								if (wall[i].live == 3) {
									wall[i].x = -100;
									wall[i].y = -100;
								}
							}
							else if (wall[i].y <= bul[j].y + bul[j].v && bul[j].y + bul[j].v <= wall[i].y + 80) {
								bul[j].x = -100;
								bul[j].y = -100;
								bul[j].move = 0;
								wall[i].live++;
								if (wall[i].live == 3) {
									wall[i].x = -100;
									wall[i].y = -100;
								}
							}
						}
						if (wall[i].y <= bul[j].y && bul[j].y <= wall[i].y + 80) {
							if (wall[i].x <= bul[j].x && bul[j].x <= wall[i].x + 80) {
								bul[j].x = -100;
								bul[j].y = -100;
								bul[j].move = 0;
								wall[i].live++;
								if (wall[i].live == 3) {
									wall[i].x = -100;
									wall[i].y = -100;
								}
							}
							else if (wall[i].x <= bul[j].x + bul[j].w && bul[j].x + bul[j].w <= wall[i].x + 80) {
								bul[j].x = -100;
								bul[j].y = -100;
								bul[j].move = 0;
								wall[i].live++;
								if (wall[i].live == 3) {
									wall[i].x = -100;
									wall[i].y = -100;
								}
							}
						}
					}
				}
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		for (int i = 0; i < t; i++) {
			if (wall[i].x <= mx && mx <= wall[i].x+80) {
				if (wall[i].y <= my && my <= wall[i].y+80) {
					p = i;
					wall[p].mx = my;
					wall[p].my = my;
				}
			}
		}
		drag = TRUE;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		drag = FALSE;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (drag) {
			mx1 = LOWORD(lParam);
			my1 = HIWORD(lParam);
			if (wall[p].mx < mx1) {
				if (wall[p].my < my1) {
					wall[p].y += 2;
					if (wall[p].y+80 > 800) {
						wall[p].y -= 2;
					}
					wall[p].x += 2;
					if (wall[p].x+80 > 800) {
						wall[p].x -= 2;
					}
				}
				else if (wall[p].my == my1) {
					wall[p].x += 2;
					if (wall[p].x+80 > 800) {
						wall[p].x -= 2;
					}
				}
				else {
					wall[p].x += 2;
					if (wall[p].x+80 > 800) {
						wall[p].x -= 2;
					}
					wall[p].y -= 2;
					if (wall[p].y < 0) {
						wall[p].y += 2;
					}
				}
			}
			if (wall[p].mx > mx1) {
				if (wall[p].my < my1) {
					wall[p].y += 2;
					if (wall[p].y+80 > 800) {
						wall[p].y -= 2;
					}
					wall[p].x -= 2;
					if (wall[p].x < 0) {
						wall[p].x += 2;
					}
				}
				else if (wall[p].my == my1) {
					wall[p].x -= 2;
					if (wall[p].x < 0) {
						wall[p].x += 2;
					}
				}
				else {
					wall[p].x -= 2;
					if (wall[p].x < 0) {
						wall[p].x += 2;
					}
					wall[p].y -= 2;
					if (wall[p].y < 0) {
						wall[p].y += 2;
					}
				}
			}
			if (wall[p].mx == mx1) {
				if (wall[p].my < my1) {
					wall[p].y += 2;
					if (wall[p].y+80 > 800) {
						wall[p].y -= 2;
					}
				}
				else {
					wall[p].y -= 2;
					if (wall[p].y < 0) {
						wall[p].y += 2;
					}
				}
			}
			wall[p].mx = mx1;
			wall[p].my = my1;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			cng = 4;
			re[0].x -= 10;
			if (re[0].x <= -30) {
				re[0].x += 10;
			}
		}
		if (wParam == VK_RIGHT) {
			cng = 3;
			re[0].x += 10;
			if (re[0].x >= rt.right - 60) {
				re[0].x -= 10;
			}
		}
		if (wParam == VK_UP) {
			cng = 2;
			re[0].y -= 10;
			if (re[0].y <= -30) {
				re[0].y += 10;
			}
		}
		if (wParam == VK_DOWN) {
			cng = 1;
			re[0].y += 10;
			if (re[0].y >= 550) {
				re[0].y -= 10;
			}
		}
		if (wParam == VK_SPACE) {
			if (cng == 1) {
				bul[t1].x = re[0].x + 40;
				bul[t1].y = re[0].y+90;
				bul[t1].w = 2;
				bul[t1].v = 5;
				bul[t1].r = 0;
				bul[t1].g = 255;
				bul[t1].b = 255;
				bul[t1].move = 1;
				bul[t1].rc = 1;
			}
			else if (cng == 2) {
				bul[t1].x = re[0].x + 40;
				bul[t1].y = re[0].y + 10;
				bul[t1].w = 2;
				bul[t1].v = 5;
				bul[t1].r = 0;
				bul[t1].g = 255;
				bul[t1].b = 255;
				bul[t1].move = 1;
				bul[t1].rc = 0;
			}
			else if (cng == 3) {
				bul[t1].x = re[0].x + 90;
				bul[t1].y = re[0].y + 40;
				bul[t1].w = 5;
				bul[t1].v = 2;
				bul[t1].r = 0;
				bul[t1].g = 255;
				bul[t1].b = 255;
				bul[t1].move = 1;
				bul[t1].rc = 2;
			}
			else if (cng == 4) {
				bul[t1].w = 5;
				bul[t1].v = 2;
				bul[t1].x = re[0].x - 10;
				bul[t1].y = re[0].y + 40;
				bul[t1].r = 0;
				bul[t1].g = 255;
				bul[t1].b = 255;
				bul[t1].move = 1;
				bul[t1].rc = 3;
			}
			t1++;
		}
		if (wParam == 's' || wParam == 'S') {
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			cnt = 0;cnt1 = 0;
			for (int i = 0;i < t;i++) {
				r[i].x = 0;
				r[i].y = 0;
				r[i].temp = 0;
				r[i].cng = 0;
			}
			SetTimer(hwnd, 1, 200, NULL);
			ran = rand() % 5;
			switch (ran) {
			case 0:
				for (int i = 0;i < 1;i++) {
					r[i].x = rand() % (rt.right - 130);
					r[i].temp = rand() % 2;
					r[i].y = rand() % (rt.bottom - 130);
				}
				if (r[0].temp == 0) {
					r[1].x = r[0].x - 80;
					r[2].x = r[0].x + 80;
					r[1].y = r[0].y;
					r[2].y = r[0].y;
				}
				else {
					r[1].y = r[0].y - 80;
					r[2].y = r[0].y + 80;
					r[1].x = r[0].x;
					r[2].x = r[0].x;
				}
				r[1].temp = r[0].temp;
				r[2].temp = r[0].temp;
				t = 3;
				break;
			case 1:
				for (int i = 0;i < 2;i++) {
					r[i].x = rand() % (rt.right - 130);
					r[i].temp = rand() % 2;
					r[i].y = rand() % (rt.bottom - 130);
				}
				temp = r[1].x;
				v = r[1].temp;
				c = r[1].y;
				if (r[0].temp == 0) {
					r[1].x = r[0].x - 80;
					r[2].x = r[0].x + 80;
					r[1].y = r[0].y;
					r[2].y = r[0].y;
				}
				else {
					r[1].y = r[0].y - 80;
					r[2].y = r[0].y + 80;
					r[1].x = r[0].x;
					r[2].x = r[0].x;
				}
				r[1].temp = r[0].temp;
				r[2].temp = r[0].temp;
				if (v == 0) {
					r[3].x = temp;
					r[4].x = temp - 80;
					r[5].x = temp + 80;
					r[3].y = c;
					r[4].y = c;
					r[5].y = c;
				}
				else {
					r[3].y = c;
					r[4].y = c - 80;
					r[5].y = c + 80;
					r[3].x = temp;
					r[4].x = temp;
					r[5].x = temp;
				}
				r[3].temp = v;
				r[4].temp = v;
				r[5].temp = v;
				t = 6;
				break;
			case 2:
				for (int i = 0;i < 3;i++) {
					r[i].x = rand() % (rt.right - 130);
					r[i].temp = rand() % 2;
					r[i].y = rand() % (rt.bottom - 130);
				}
				temp = r[1].x;
				v = r[1].temp;
				c = r[1].y;
				temp1 = r[2].x;
				v1 = r[2].temp;
				c1 = r[2].y;
				if (r[0].temp == 0) {
					r[1].x = r[0].x - 80;
					r[2].x = r[0].x + 80;
					r[1].y = r[0].y;
					r[2].y = r[0].y;
				}
				else {
					r[1].y = r[0].y - 80;
					r[2].y = r[0].y + 80;
					r[1].x = r[0].x;
					r[2].x = r[0].x;
				}
				r[1].temp = r[0].temp;
				r[2].temp = r[0].temp;
				if (v == 0) {
					r[3].x = temp;
					r[4].x = temp - 80;
					r[5].x = temp + 80;
					r[3].y = c;
					r[4].y = c;
					r[5].y = c;
				}
				else {
					r[3].y = c;
					r[4].y = c - 80;
					r[5].y = c + 80;
					r[3].x = temp;
					r[4].x = temp;
					r[5].x = temp;
				}
				r[3].temp = v;
				r[4].temp = v;
				r[5].temp = v;
				if (v1 == 0) {
					r[6].x = temp1;
					r[7].x = temp1 - 80;
					r[8].x = temp1 + 80;
					r[6].y = c1;
					r[7].y = c1;
					r[8].y = c1;
				}
				else {
					r[6].y = c1;
					r[7].y = c1 - 80;
					r[8].y = c1 + 80;
					r[6].x = temp1;
					r[7].x = temp1;
					r[8].x = temp1;
				}
				r[6].temp = r[7].temp = r[8].temp = v1;
				t = 9;
				break;
			case 3:
				for (int i = 0;i < 4;i++) {
					r[i].x = rand() % (rt.right - 130);
					r[i].temp = rand() % 2;
					r[i].y = rand() % (rt.bottom - 130);
				}
				temp = r[1].x;
				v = r[1].temp;
				c = r[1].y;
				temp1 = r[2].x;
				v1 = r[2].temp;
				c1 = r[2].y;
				temp2 = r[3].x;
				v2 = r[3].temp;
				c2 = r[3].y;
				if (r[0].temp == 0) {
					r[1].x = r[0].x - 80;
					r[2].x = r[0].x + 80;
					r[1].y = r[0].y;
					r[2].y = r[0].y;
				}
				else {
					r[1].y = r[0].y - 80;
					r[2].y = r[0].y + 80;
					r[1].x = r[0].x;
					r[2].x = r[0].x;
				}
				r[1].temp = r[0].temp;
				r[2].temp = r[0].temp;
				if (v == 0) {
					r[3].x = temp;
					r[4].x = temp - 80;
					r[5].x = temp + 80;
					r[3].y = c;
					r[4].y = c;
					r[5].y = c;
				}
				else {
					r[3].y = c;
					r[4].y = c - 80;
					r[5].y = c + 80;
					r[3].x = temp;
					r[4].x = temp;
					r[5].x = temp;
				}
				r[3].temp = v;
				r[4].temp = v;
				r[5].temp = v;
				if (v1 == 0) {
					r[6].x = temp1;
					r[7].x = temp1 - 80;
					r[8].x = temp1 + 80;
					r[6].y = c1;
					r[7].y = c1;
					r[8].y = c1;
				}
				else {
					r[6].y = c1;
					r[7].y = c1 - 80;
					r[8].y = c1 + 80;
					r[6].x = temp1;
					r[7].x = temp1;
					r[8].x = temp1;
				}
				r[6].temp = r[7].temp = r[8].temp = v1;
				if (v2 == 0) {
					r[9].x = temp2;
					r[10].x = temp2 - 80;
					r[11].x = temp2 + 80;
					r[9].y = c2;
					r[10].y = c2;
					r[11].y = c2;
				}
				else {
					r[9].y = c2;
					r[10].y = c2 - 80;
					r[11].y = c2 + 80;
					r[9].x = temp2;
					r[10].x = temp2;
					r[11].x = temp2;
				}
				r[9].temp = r[10].temp = r[11].temp = v2;
				t = 12;
				break;
			case 4:
				for (int i = 0;i < 5;i++) {
					r[i].x = rand() % (rt.right - 130);
					r[i].temp = rand() % 2;
					r[i].y = rand() % (rt.bottom - 130);
				}
				temp = r[1].x;
				v = r[1].temp;
				c = r[1].y;
				temp1 = r[2].x;
				v1 = r[2].temp;
				c1 = r[2].y;
				temp2 = r[3].x;
				v2 = r[3].temp;
				c2 = r[3].y;
				temp3 = r[4].x;
				v3 = r[4].temp;
				c3 = r[4].y;
				if (r[0].temp == 0) {
					r[1].x = r[0].x - 80;
					r[2].x = r[0].x + 80;
					r[1].y = r[0].y;
					r[2].y = r[0].y;
				}
				else {
					r[1].y = r[0].y - 80;
					r[2].y = r[0].y + 80;
					r[1].x = r[0].x;
					r[2].x = r[0].x;
				}
				r[1].temp = r[0].temp;
				r[2].temp = r[0].temp;
				if (v == 0) {
					r[3].x = temp;
					r[4].x = temp - 80;
					r[5].x = temp + 80;
					r[3].y = c;
					r[4].y = c;
					r[5].y = c;
				}
				else {
					r[3].y = c;
					r[4].y = c - 80;
					r[5].y = c + 80;
					r[3].x = temp;
					r[4].x = temp;
					r[5].x = temp;
				}
				r[3].temp = v;
				r[4].temp = v;
				r[5].temp = v;
				if (v1 == 0) {
					r[6].x = temp1;
					r[7].x = temp1 - 80;
					r[8].x = temp1 + 80;
					r[6].y = c1;
					r[7].y = c1;
					r[8].y = c1;
				}
				else {
					r[6].y = c1;
					r[7].y = c1 - 80;
					r[8].y = c1 + 80;
					r[6].x = temp1;
					r[7].x = temp1;
					r[8].x = temp1;
				}
				r[6].temp = r[7].temp = r[8].temp = v1;
				if (v2 == 0) {
					r[9].x = temp2;
					r[10].x = temp2 - 80;
					r[11].x = temp2 + 80;
					r[9].y = c2;
					r[10].y = c2;
					r[11].y = c2;
				}
				else {
					r[9].y = c2;
					r[10].y = c2 - 80;
					r[11].y = c2 + 80;
					r[9].x = temp2;
					r[10].x = temp2;
					r[11].x = temp2;
				}
				r[9].temp = r[10].temp = r[11].temp = v2;
				if (v3 == 0) {
					r[12].x = temp3;
					r[13].x = temp3 - 80;
					r[14].x = temp3 + 80;
					r[12].y = c3;
					r[13].y = c3;
					r[14].y = c3;
				}
				else {
					r[12].y = c3;
					r[13].y = c3 - 80;
					r[14].y = c3 + 80;
					r[12].x = temp3;
					r[13].x = temp3;
					r[14].x = temp3;
				}
				r[12].temp = r[13].temp = r[14].temp = v3;
				t = 15;
				break;
			}
			SetTimer(hwnd, 2, 100, NULL);
		}
		if (wParam == 'q' || wParam == 'Q') {
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			PostQuitMessage(0);
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}