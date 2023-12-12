#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "resource2.h"
#define PIE 3.141592
#define _USE_MATH_DEFINES
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
COLORREF SetBkColor(HDC hdc, COLORREF crColor);
COLORREF SetTextColor(HDC hdc, COLORREF crColor);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlalog_Proc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, 0, 0, 900, 900, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

int Sin = 0;
int zigzag = 0;
int spring = 0;
int pie = 0;
int X1 = 0;
int Y1 = 0;
int reset = 0;
int r = 0, g = 0, b = 0;
int won = 0;
double rad(double degree) {
	return PIE * degree / 180.0;
}
double radi(double degree) {
	return PIE * degree / 30.0;
}
struct won {
	int x1 = 0;
	double x = 0;
	double y = 0;
	double degree = 0;
	double de = 0;
};
struct won w;
BOOL CALLBACK Dlalog_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static int cng = 0, cng1 = 0, cng2 = 0, cng3 = 0;
	static int dr = 0, dg = 0, db = 0;
	switch (iMsg) {
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RADIO1:
			Sin = 1;
			zigzag = 0;
			spring = 0;
			pie = 0;
			break;
		case IDC_RADIO2:
			Sin = 0;
			zigzag = 1;
			spring = 0;
			pie = 0;
			break;
		case IDC_RADIO3:
			Sin = 0;
			zigzag = 0;
			spring = 1;
			pie = 0;
			break;
		case IDC_RADIO4:
			Sin = 0;
			zigzag = 0;
			spring = 0;
			pie = 1;
			break;
		case IDC_BUTTON2: //move_x
			X1 = 1;
			Y1 = 0;
			reset = 0;
			break;
		case IDC_BUTTON1: //move_y
			Y1 = 1;
			X1 = 0;
			reset = 0;
			break;
		case IDC_BUTTON3: //stop
			X1 = 0;
			Y1 = 0;
			reset = 0;
			break;
		case IDC_BUTTON4: //Reset
			reset = 1;
			X1 = 0;
			Y1 = 0;
			won = 0;
			w.x = 0;
			w.y = 0;
			w.degree = 0;
			break;
		case IDC_BUTTON5: //원이동
			won = 1;
			break;
		case IDC_CHECK1:
			if (cng % 2 == 0) {
				g += 200;
				b += 255;
			}
			if (cng % 2 == 1) {
				g -= 200;
				b -= 255;
			}
			if (r > 255) {
				r = 255;
			}
			if (g > 255) {
				g = 255;
			}
			if (b > 255) {
				b = 255;
			}
			cng++;
			break;
		case IDC_CHECK2:
			if (cng1 % 2 == 0) {
				r += 255;
				b += 255;
			}
			if (cng1 % 2 == 1) {
				r -= 255;
				b -= 255;
			}
			if (r > 255) {
				r = 255;
			}
			if (g > 255) {
				g = 255;
			}
			if (b > 255) {
				b = 255;
			}
			cng1++;
			break;
		case IDC_CHECK3:
			if (cng2 % 2 == 0) {
				r += 255;
				g += 255;
			}
			if (cng2 % 2 == 1) {
				r -= 255;
				g -= 255;
			}
			if (r > 255) {
				r = 255;
			}
			if (g > 255) {
				g = 255;
			}
			if (b > 255) {
				b = 255;
			}
			cng2++;
			break;
		case IDC_CHECK4:
			if (cng3 % 2 == 0) {
				dr = r;
				dg = g;
				db = b;
				r = 255 - r;
				g = 255 - g;
				b = 255 - b;
			}
			if (cng3 % 2 == 1) {
				r = dr;
				g = dg;
				b = db;
			}
			cng3++;
			break;
		case IDOK: //--- 버튼
			r = 0;g = 0;b = 0;
			X1 = 0;Y1 = 0;reset = 0;
			Sin = 0;
			zigzag = 0;
			spring = 0;
			pie = 0;
			EndDialog(hDlg, 0);
			break;
		case IDCANCEL: //--- 버튼
			EndDialog(hDlg, 0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	static HDC hDC, memdc; //장치 컨텍스트 핸들
	static HDC mdc;
	static HBITMAP myBitmap;
	static HBITMAP hBitmap;
	RECT rt;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static BOOL Selection;
	static int degree, x, y, x2, y2;
	static int x1 = 0, y1 = 0;
	double radian, result, result1;
	static int cng = -1;
	static double move_x = 0, move_y = 450, move_y1 = 450;
	static int cng1 = 0, cng2 = 0, cng3 = 0, m = 0;
	static int spring_x = 0, spring_y = 0;
	static int cs = 0;
	switch (iMessage) {
	case WM_CREATE:
		srand(time(NULL));
		SetTimer(hWnd, 1, 50, NULL);
		SetTimer(hWnd, 2, 50, NULL);
		SetTimer(hWnd, 3, 50, NULL);
		myBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			if (X1 == 1) {
				x1 -= 10;
				if (won == 1) {
					if (Sin == 1) {
						w.x -= 10;
					}
					if (spring == 1) {
						w.degree += 10;
					}
					if (zigzag == 1) {
						w.degree += 2;
						w.de += 2;
					}
				}
			}
			if (Y1 == 1) {
				if (cng1 % 2 == 0) {
					y1 -= 10;
				}
				if (cng1 % 2 == 1) {
					y1 += 10;
				}
				if (y1 == -100) {
					cng1++;
				}
				if (y1 == 100) {
					cng1++;
				}
			}
			if (reset == 1) {
				x1 = 0;
				y1 = 0;
			}
			break;
		case 2:
			if (X1 == 1) {
				spring_x -= 10;
			}
			if (Y1 == 1) {
				if (cng2 % 2 == 0) {
					spring_y -= 1;
				}
				if (cng2 % 2 == 1) {
					spring_y += 1;
				}
				if (spring_y == -3) {
					cng2++;
				}
				if (spring_y == 3) {
					cng2++;
				}
			}
			if (reset == 1) {
				spring_x = 0;
				spring_y = 0;
			}
			break;
		case 3:
			if (won == 1) {
				if (Sin == 1) {
					w.x += 10;
					w.degree += 10;
				}
				if (spring == 1) {
					w.degree += 10;
				}
				if (zigzag == 1) {
					w.degree += 2;
					w.x += 2;
					w.x1 += 2;
					w.de += 2;
					if (cng3 % 2 == 0) {
						w.y = double(((550 - y1) - (350 + y1))) / double(((224 * cs + x1) - (224 * cs + 112 + x1))) * (w.x  + double((224 * cs + x1))) + double(550 - y1);
					}
					if (cng3 % 2 == 1) {
						w.y = double(((350 + y1) - (550 - y1))) / double(((224 * cs + 112 + x1) - (224 * (cs + 1) + x1))) * (w.x  + double((224 * (cs + 1) + x1))) + double(550 - y1);
					}
					if (w.x > 5) {
						if (-2<=w.x1 % 112&& w.x1 % 112 <= 2) {
							cng3++;
							w.degree = 0;
							w.de = 0;
							cs++;
						}
					}
					if (w.x > 900) {
						w.degree = 0;
					}
				}
			}
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		switch (wParam) {

			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		mdc = CreateCompatibleDC(hDC);
		memdc = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		SelectObject(memdc, myBitmap);
		Rectangle(mdc, 0, 0, rt.right, rt.bottom);
		if (Sin == 1) {
			MoveToEx(mdc, 0, 450, 0);
			LineTo(mdc, 900, 450);
			MoveToEx(mdc, 450, 900, 0);
			LineTo(mdc, 450, 0);
			for (degree = 0; degree <= 5000; degree++) {
				result = sin(rad((double)(degree)));
				x = degree + x1;
				y = 450 - (int)((100.0 - y1) * result);
				SetPixel(mdc, x, y, RGB(r, g, b));
			}
			if (won == 1) {
				result1 = sin(rad((double)(w.degree)));
				w.y = 450 - (int)((100.0 - y1) * result1);
			}
			if (w.x > 900) {
				w.x = 0;
			}
		}
		if (zigzag == 1) {
			MoveToEx(mdc, 0, 450, 0);
			LineTo(mdc, 900, 450);
			MoveToEx(mdc, 450, 900, 0);
			LineTo(mdc, 450, 0);
			for (int i = 0;i < 1400;i++) {
				hPen = CreatePen(PS_SOLID, 5, RGB(r, g, b));
				oldPen = (HPEN)SelectObject(mdc, hPen);
				MoveToEx(mdc, 224 * i + x1, 550 - y1, NULL);
				LineTo(mdc, 224 * i + 112 + x1, 350 + y1);
				MoveToEx(mdc, 224 * i + 112 + x1, 350 + y1, NULL);
				LineTo(mdc, 224 * (i + 1) + x1, 550 - y1);
				SelectObject(mdc, oldPen);
				DeleteObject(hPen);
			}
		}
		if (spring == 1) {
			MoveToEx(mdc, 0, 450, 0);
			LineTo(mdc, 900, 450);
			MoveToEx(mdc, 450, 900, 0);
			LineTo(mdc, 450, 0);
			for (degree = -100;degree <= 1440;degree++) {
				hPen = CreatePen(PS_SOLID, 5, RGB(r, g, b));
				oldPen = (HPEN)SelectObject(mdc, hPen);
				x = degree + 50 * cos(radi((double)degree + spring_x)) * (spring_y + 1);
				y = 450 + 50 * sin(radi((double)degree + spring_x)) * (spring_y + 1);
				x2 = (degree + 1) + 50 * cos(radi((double)degree + 1.0 + spring_x)) * (spring_y + 1);
				y2 = 450 + 50 * sin(radi((double)degree + 1.0 + spring_x)) * (spring_y + 1);
				MoveToEx(mdc, x, y, NULL);
				LineTo(mdc, x2, y2);
				SelectObject(mdc, oldPen);
				DeleteObject(hPen);
			}
			if (won == 1) {
				w.x = w.degree + 50 * cos(radi((double)w.degree + spring_x)) * (spring_y + 1);
				w.y = 450 + 50 * sin(radi((double)w.degree + spring_x)) * (spring_y + 1);
			}
			if (w.x > 900) {
				w.degree = 0;
			}
		}
		if (pie == 1) {
			MoveToEx(mdc, 0, 450, 0);
			LineTo(mdc, 900, 450);
			MoveToEx(mdc, 450, 900, 0);
			LineTo(mdc, 450, 0);
			for (int i = -500;i < 500;i++) {
				hPen = CreatePen(PS_SOLID, 5, RGB(r, g, b));
				oldPen = (HPEN)SelectObject(mdc, hPen);
				MoveToEx(mdc, 225 * i + x1, 550 - y1, NULL);
				LineTo(mdc, 225 * i + 112 + x1, 550 - y1);
				MoveToEx(mdc, 225 * i + 112 + x1, 550 - y1, NULL);
				LineTo(mdc, 225 * i + 112 + x1, 350 + y1);
				MoveToEx(mdc, 225 * i + 112 + x1, 350 + y1, NULL);
				LineTo(mdc, 225 * (i + 1) + x1, 350 + y1);
				MoveToEx(mdc, 225 * (i + 1) + x1, 350 + y1, NULL);
				LineTo(mdc, 225 * (i + 1) + x1, 550 - y1);
				SelectObject(mdc, oldPen);
				DeleteObject(hPen);
			}
		}
		if (won == 1) {
			hBrush = CreateSolidBrush(RGB(150, 30, 220));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, w.x - 15, w.y - 15, w.x + 15, w.y + 15);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
		}
		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);//한번에 복사해서 출력해주기
		DeleteDC(memdc); //메모리 삭제 이거안하면 프로그램이 죽음
		DeleteDC(mdc); //--- 생성한 메모리 DC 삭제: 계속 사용할 경우 전역변수 또는 정적 변수로 선언해도 무방함.
		DeleteObject(hBitmap); //메모리 삭제 이거안하면 프로그램이 죽음
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)&Dlalog_Proc);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		hDC = GetDC(hWnd);

		ReleaseDC(hWnd, hDC);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		DeleteObject(myBitmap);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}