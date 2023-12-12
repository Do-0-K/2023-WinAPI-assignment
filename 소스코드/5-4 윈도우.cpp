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
	double x = 400, y = 300;
	int cng = 0, cng1 = 0;
	int mx = 0, my = 0;
	double c_x = 0, c_y = 0;
	int move = 0;
};
struct rect r[6];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	HDC hdc, memdc, kdc;
	PAINTSTRUCT ps;
	static HBITMAP hbitmap[4];
	static HBITMAP oldbit[3];
	static HBITMAP backhbit{};
	static HBITMAP hbit{};
	static RECT rt{};
	static int cnt;
	int mx = 0, my = 0;
	static int jump = 0;
	static int jump_cnt = 0;
	static int m = 0, m_cnt = 0;
	static int t = 1;
	static int r_cnt = 0, a_cnt = 0;
	static double d_x = 0, d_y = 0;
	static int over = 0;
	static int dir = 0;
	switch (iMsg) {
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd,&rt);
		backhbit = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7));
		hbitmap[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		hbitmap[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		hbitmap[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
		hbitmap[3] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
		cnt = 0;
		hbit = CreateCompatibleBitmap(hdc,rt.right, rt.bottom);
		SetTimer(hwnd, 1, 200, NULL);
		SetTimer(hwnd, 8, 100, NULL);
		r[0].move = 1;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		oldbit[0] = (HBITMAP)SelectObject(memdc, hbit); //--- hBit: 이미지가 저장되어 있는 비트맵 전역 변수
		StretchBlt(hdc, 0, 0, rt.right, rt.bottom, memdc, 0, 0,rt.right,rt.bottom,SRCCOPY);
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
				TransparentBlt(memdc, r[i].x, r[i].y, 300 + m, 300 + m, kdc, 0, 0, 300, 300, RGB(255, 255, 255));
				if (cnt == 3) {
					r[i].y += 20;
				}
			}
			//--- MemDC에 배경과 애니메이션 저장  hBit 비트맵에 저장
			cnt++; //--- 애니메이션 이미지 순서
			if (cnt >= 3) {
				cnt = 0;
			}
			DeleteDC(memdc);
			DeleteObject(kdc);
			ReleaseDC(hwnd, hdc);
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 2:
			for (int i = 0;i < t;i++) {
				if (jump == 1) {
					if (jump_cnt <= 1) {
						r[i].y -= 10;
					}
					if (1 < jump_cnt && jump_cnt <= 3) {
						r[i].x -= 10;
					}
					if (3 < jump_cnt && jump_cnt <= 5) {
						r[i].y += 10;
					}
				}
				if (jump == 2) {
					if (jump_cnt <= 1) {
						r[i].y -= 10;
					}
					if (1 < jump_cnt && jump_cnt <= 3) {
						r[i].x += 10;
					}
					if (3 < jump_cnt && jump_cnt <= 5) {
						r[i].y += 10;
					}
				}
				if (jump == 3) {
					if (jump_cnt <= 1) {
						r[i].x -= 10;
					}
					if (1 < jump_cnt && jump_cnt <= 3) {
						r[i].y -= 10;
					}
					if (3 < jump_cnt && jump_cnt <= 5) {
						r[i].x += 10;
					}
				}
				if (jump == 4) {
					if (jump_cnt <= 1) {
						r[i].x += 10;
					}
					if (1 < jump_cnt && jump_cnt <= 3) {
						r[i].y += 10;
					}
					if (3 < jump_cnt && jump_cnt <= 5) {
						r[i].x -= 10;
					}
				}
			}
			jump_cnt++;
			if (jump_cnt >= 6) {
				jump_cnt = 0;
				KillTimer(hwnd, 2);
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 3:
			if (m_cnt == 0) {
				m += 10;
				if (m == 100) {
					m_cnt++;
				}
			}
			if (m_cnt == 1) {
				m -= 10;
				if (m == 0) {
					m_cnt = 0;
					KillTimer(hwnd, 3);
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 4:
			if (m_cnt == 0) {
				m -= 10;
				if (m == -100) {
					m_cnt++;
				}
			}
			if (m_cnt == 1) {
				m += 10;
				if (m == 0) {
					m_cnt = 0;
					KillTimer(hwnd, 4);
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 5:
			for (int i = 0;i < t;i++) {
				if (r[i].cng % 2 == 0) {
					r[i].x += 5;
				}
				if (r[i].cng % 2 == 1) {
					r[i].x -= 5;
				}
				if (r[i].x <= -50) {
					if (r[i].cng1 % 2 == 0) {
						r[i].y += 50;
					}
					if (r[i].cng1 % 2 == 1) {
						r[i].y -= 50;
					}
					if (r[i].y < -30) {
						r[i].cng1++;
					}
					if (r[i].y > 300) {
						r[i].cng1++;
					}
					r[i].cng++;
				}
				if (r[i].x + 250 >= 800) {
					if (r[i].cng1 % 2 == 0) {
						r[i].y += 50;
					}
					if (r[i].cng1 % 2 == 1) {
						r[i].y -= 50;
					}
					if (r[i].y > 300) {
						r[i].cng1++;
					}
					if (r[i].y < -30) {
						r[i].cng1++;
					}
					r[i].cng++;
				}
			}
			break;
		case 6:
			for (int i = t - 1; i >= 1; i--) {
				r[i].x = r[i - 1].x;
				r[i].y = r[i - 1].y;
			}
			if (r[0].cng % 2 == 0) {
				r[0].x += 30;
			}
			if (r[0].cng % 2 == 1) {
				r[0].x -= 30;
			}
			if (r[0].x <= -60) {
				if (r[0].cng1 % 2 == 0) {
					r[0].y += 50;
				}
				if (r[0].cng1 % 2 == 1) {
					r[0].y -= 50;
				}
				if (r[0].y < -30) {
					r[0].cng1++;
				}
				if (r[0].y > 300) {
					r[0].cng1++;
				}
				r[0].cng++;
			}
			if (r[0].x + 250 >= 800) {
				if (r[0].cng1 % 2 == 0) {
					r[0].y += 50;
				}
				if (r[0].cng1 % 2 == 1) {
					r[0].y -= 50;
				}
				if (r[0].y > 300) {
					r[0].cng1++;
				}
				if (r[0].y < -30) {
					r[0].cng1++;
				}
				r[0].cng++;
			}
			break;
		case 7:
			if (over == 1) {
				r[0].x -= 5;
				r[0].y = (d_y - r[0].c_y) / (d_x - r[0].c_x) * (r[0].x - r[0].c_x) + r[0].c_y;
				if (r[0].x < d_x) {
					KillTimer(hwnd, 7);
					SetTimer(hwnd, 8, 100, NULL);
				}
			}
			if (over == 2) {
				r[0].x += 5;
				r[0].y = (d_y - r[0].c_y) / (d_x - r[0].c_x) * (r[0].x - r[0].c_x) + r[0].c_y;
				if (r[0].x > d_x) {
					KillTimer(hwnd, 7);
					SetTimer(hwnd, 8, 100, NULL);
				}
			}
			break;
		case 8:
			if (dir == 0) {
				for (int i = 0;i < t;i++) {
					if (r[i].move == 1) {
						r[i].x -= 10;
						if (r[i].x <= -50) {
							r[i].x = rt.right-250;
						}
					}
				}
			}
			if (dir == 1) {
				for (int i = 0;i < t;i++) {
					if (r[i].move == 1) {
						r[i].x += 10;
						if (r[i].x >= rt.right - 250) {
							r[i].x = -50;
						}
					}
				}
			}
			if (dir == 2) {
				for (int i = 0;i < t;i++) {
					if (r[i].move == 1) {
						r[i].y -= 10;
						if (r[i].y <= -30) {
							r[i].y = rt.bottom - 270;
						}
					}
				}
			}
			if (dir == 3) {
				for (int i = 0;i < t;i++) {
					if (r[i].move == 1) {
						r[i].y += 10;
						if (r[i].y >= rt.bottom - 270) {
							r[i].y = -30;
						}
					}
				}
			}
			break;
		}
		InvalidateRect(hwnd, NULL, FALSE); 
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (r[0].x + 50 <= mx && mx <= r[0].x + 150) {
			if (r[0].y <= my && my <= r[0].y + 300) {
				cnt = 3;
				for (int i = 0;i < t;i++) {
					r[i].y -= 20;
				}
				SetTimer(hwnd, 1, 200, NULL);
			}
		}
		else {
			KillTimer(hwnd, 7);
			KillTimer(hwnd, 8);
			r[0].c_x = r[0].x;
			r[0].c_y = r[0].y;
			d_x = mx;
			d_y = my;
			if (d_x < r[0].x) {
				over = 1;
				SetTimer(hwnd, 7, 100, NULL);
			}
			if (d_x > r[0].x) {
				over = 2;
				SetTimer(hwnd, 7, 100, NULL);
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			dir = 0;
			jump = 1;
		}
		if (wParam == VK_RIGHT) {
			dir = 1;
			jump = 2;
		}
		if (wParam == VK_UP) {
			dir = 2;
			jump = 3;
		}
		if (wParam == VK_DOWN) {
			dir = 3;
			jump = 4;
		}
		if (wParam == 'j' || wParam == 'J') {
			SetTimer(hwnd, 2, 100, NULL);
		}
		if (wParam == 'e' || wParam == 'E') {
			SetTimer(hwnd, 3, 100, NULL);
		}
		if (wParam == 's' || wParam == 'S') {
			SetTimer(hwnd, 4, 100, NULL);
		}
		if (wParam == 'r' || wParam == 'R') {
			if (r_cnt == 0) {
				KillTimer(hwnd, 8);
				SetTimer(hwnd, 5, 100, NULL);
				r_cnt++;
			}
			else if (r_cnt != 0) {
				r_cnt = 0;
				SetTimer(hwnd, 8, 100, NULL);
				KillTimer(hwnd, 5);
			}
		}
		if (wParam == 't' || wParam == 'T') {
			r[t].move = 1;
			r[t].x = rand() % 500;
			r[t].y = rand() % 300;
			t++;
		}
		if (wParam == 'a' || wParam == 'A') {
			if (a_cnt == 0) {
				for (int i = 1;i < t;i++) {
					r[i].mx = r[i].x;
					r[i].my = r[i].y;
				}
				SetTimer(hwnd, 6, 100, NULL);
				a_cnt++;
			}
			else if (a_cnt != 0) {
				a_cnt = 0;
				for (int i = 1;i < t;i++) {
					r[i].x = r[i].mx;
					r[i].y = r[i].my;
				}
				KillTimer(hwnd, 6);
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}