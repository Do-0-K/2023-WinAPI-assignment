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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 700, NULL, (HMENU)NULL, hInstance, NULL);
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
	int live = 0;
};
struct rect r[400];
struct ject {
	int x = 400, y = 520;
	int jump = 0;
};
struct ject re[1];
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
	static HBITMAP HBitmap[6];
	static HBITMAP oldbit[6];
	static HBITMAP backhbit{};
	static HBITMAP Backbit{};
	static HBITMAP hbit{};
	static BOOL drag;
	static RECT rt{};
	static int cnt = 0;
	static int cnt1 = 0;
	static int cnt2 = -1;
	static int cng = 0;
	int mx = 0, my = 0;
	static int t = 1, t1 = 0;
	static int a = 0, s = 0, p = 0, m = 0;
	int mx1 = 0, my1 = 0;
	static int movebackground = 1800;
	static int moveback = 1400;
	switch (iMsg) {
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rt);
		backhbit = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP13)); //배경1
		Backbit = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP14)); //배경2
		hbitmap[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP8)); //적
		hbitmap[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP9));
		hbitmap[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP10));
		hbitmap[3] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP11));
		hbitmap[4] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP12));
		hBitmap[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3)); //주인공
		hBitmap[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		hBitmap[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
		HBitmap[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP15));//폭발
		HBitmap[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP16));
		HBitmap[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP17));
		HBitmap[3] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP18));
		HBitmap[4] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP19));
		HBitmap[5] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP20));
		hbit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		SetTimer(hwnd, 1, 200, NULL);
		SetTimer(hwnd, 2, 100, NULL);
		SetTimer(hwnd, 3, 100, NULL);
		SetTimer(hwnd, 4, 1500, NULL);
		SetTimer(hwnd, 5, 50, NULL);
		SetTimer(hwnd, 6, 80, NULL);
		SetTimer(hwnd, 7, 200, NULL);
		r[0].x = rand() % (rt.right - 430)+180;
		r[0].y = -20;
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
			cnt++; //--- 애니메이션 이미지 순서
			if (cnt >= 4) {
				cnt = 1;
			}
			break;
		case 2:
			for (int i = 0;i < t;i++) {
				if (r[i].live < 3) {
					r[i].y += 10;
					if (r[i].y + 80 >= rt.bottom - 50) {
						r[i].y = -60;
					}
				}
			}
			break;
		case 3:
			for (int i = 0; i < 200; i++) {
				if (bul[i].move == 1) {
					bul[i].y -= 20;
					if (bul[i].y == 0) {
						bul[i].move = 0;
					}
				}
			}
			break;
		case 4:
			r[t].x = rand() % (rt.right - 430) + 180;
			r[t].y = -20;
			t++;
			break;
		case 5:
			cnt1++; //--- 애니메이션 이미지 순서
			if (cnt1 >= 3) {
				cnt1 = 0;
			}
			break;
		case 6:
			movebackground -= 20;
			if (movebackground == 0) {
				movebackground = 1800;
			}
			break;
		case 7:
			moveback -= 20;
			if (moveback == 700) {
				moveback = 1400;
			}
			break;
		case 8:
			cnt2++;
			if (cnt2 >= 6) {
				KillTimer(hwnd, 8);
				PostQuitMessage(0);
			}
			break;
		case 9:
			if (cng % 2 == 0) {
				m -= 10;
			}
			if (cng % 2 == 1) {
				m += 10;
			}
			if (m == -50) {
				cng++;
			}
			if (m == 0) {
				cng=0;
				re[0].jump = 0;
				KillTimer(hwnd, 9);
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
					}
				}
			}
		}
		for (int i = 0;i < t;i++) {
			if (r[i].live < 3) {
				if (re[0].x <= r[i].x && r[i].x <= re[0].x + 80) {
					if (re[0].y <= r[i].y + 80) {
						if (re[0].jump == 0) {
							KillTimer(hwnd, 1);
							KillTimer(hwnd, 2);
							KillTimer(hwnd, 3);
							KillTimer(hwnd, 4);
							KillTimer(hwnd, 5);
							KillTimer(hwnd, 6);
							KillTimer(hwnd, 7);
							SetTimer(hwnd, 8, 100, NULL);
						}
					}
				}
				if (re[0].x <= r[i].x + 80 && r[i].x + 80 <= re[0].x + 80) {
					if (re[0].y <= r[i].y + 80) {
						if (re[0].jump == 0) {
							KillTimer(hwnd, 1);
							KillTimer(hwnd, 2);
							KillTimer(hwnd, 3);
							KillTimer(hwnd, 4);
							KillTimer(hwnd, 5);
							KillTimer(hwnd, 6);
							KillTimer(hwnd, 7);
							SetTimer(hwnd, 8, 100, NULL);
						}
					}
				}
			}
		}
		hdc = GetDC(hwnd);
		memdc = CreateCompatibleDC(hdc); //--- 더블 버퍼로 사용 할 메모리 DC 생성
		kdc = CreateCompatibleDC(memdc); //--- 이미지를 저장 할 메모리 DC 생성
		oldbit[0] = (HBITMAP)SelectObject(memdc, hbit); //--- MemDC와 hBit 를 호환되게 선택함
		oldbit[1] = (HBITMAP)SelectObject(kdc, backhbit); //--- 배경 이미지1
		StretchBlt(memdc, 0, 0, rt.right, rt.bottom, kdc, 0, movebackground, 800, 700, SRCCOPY);
		oldbit[2] = (HBITMAP)SelectObject(kdc, Backbit); //--- 배경 이미지2
		StretchBlt(memdc, 180, 0, 420, rt.bottom, kdc, 0, moveback - 700, 800, 700, SRCCOPY);
		oldbit[3] = (HBITMAP)SelectObject(kdc, hbitmap[cnt]); //--- 애니메이션 이미지
		for (int i = 0;i < t;i++) {
			if (0 <= r[i].live && r[i].live < 3) {
				TransparentBlt(memdc, r[i].x, r[i].y, 80, 80, kdc, 0, 0, 100, 100, RGB(255, 0, 0));
			}
		}
		oldbit[4] = (HBITMAP)SelectObject(kdc, hBitmap[cnt1]);
		TransparentBlt(memdc, re[0].x, re[0].y, 80-m, 80-m, kdc, 0, 0, 300, 300, RGB(255, 255, 255));
		if (cnt2 >= 0) {
			oldbit[5] = (HBITMAP)SelectObject(kdc, HBitmap[cnt2]);
			TransparentBlt(memdc, 0, 0, rt.right, rt.bottom, kdc, 0, 0, 100, 100, RGB(0, 0, 0));
		}
		//--- MemDC에 배경과 애니메이션 저장  hBit 비트맵에 저장
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
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
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
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			re[0].x -= 10;
			if (re[0].x <= 150) {
				re[0].x += 10;
			}
		}
		if (wParam == VK_RIGHT) {
			re[0].x += 10;
			if (re[0].x >= 550) {
				re[0].x -= 10;
			}
		}
		if (wParam == VK_UP) {
			re[0].jump = 1;
			SetTimer(hwnd, 9, 200, NULL);
		}
		if (wParam == VK_SPACE) {
			bul[t1].x = re[0].x + 40;
			bul[t1].y = re[0].y + 10;
			bul[t1].w = 5;
			bul[t1].v = 5;
			bul[t1].r = 0;
			bul[t1].g = 255;
			bul[t1].b = 255;
			bul[t1].move = 1;
			bul[t1].rc = 0;
			t1++;
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