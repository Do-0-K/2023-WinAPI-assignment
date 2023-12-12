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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 900, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) { // 1.꼬리 없애기 2.재시작
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static TCHAR witch[40][40];
	static int j = 0, k = 0;
	static int s = 0; static int t = 0;
	static int x=0, y=0, z=0;
	static int x1=0,y1=0,z1=0;
	static int q=0, w=0;
	static int p = 0, o = 0;
	static int g = 0;
	static int n = 0, m = 0;
	static int v = 0,l = 0;
	static int turn1 = 0,turn2=0;
	static int turn0 = 0;
	switch (iMsg) {
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == 'e' || wParam == 'E') {
			t = rand()%5+1;
			x = rand() % 255;
			y = rand() % 255;
			z = rand() % 255;
			x1 = rand() % 255;
			y1 = rand() % 255;
			z1 = rand() % 255;
			g = rand() % 5 + 1;
			q= rand() % 40;
			w = rand() % 40;
			p = rand() % 40;
			o = rand() % 40;
			k = 0;j = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == 'r' || wParam == 'R') {//재시작하는 변수
			t = 0;
			g = 0;
			k = 0;j = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		else if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		else if (wParam == VK_RIGHT) {
			if (turn0 % 2 == 0) {
				q++;
				if (q > 39) {
					q = 0;
				}
				if (witch[q][w] == 'R') {
					q--;
				}
				else if (witch[q][w] == 'Y') {
					x = rand() % 255;
					y = rand() % 255;
					z = rand() % 255;
				}
				else if (witch[q][w] == 'P') {
					if (turn1 == 0) {
						m++;n++;
						if (m > 5 && n > 5) {
							turn1++;
						}
					}
					else if (turn1 == 1) {
						m--;n--;
						if (m < 1 && n < 1) {
							turn1 = 0;
						}
					}
				}
				else if (witch[q][w] == 'B') {
					t = rand() % 5 + 1;
				}
				k = 0;j = 0;
				turn0++;
				InvalidateRect(hwnd, NULL, TRUE);
				ReleaseDC(hwnd, hdc);
			}
			break;
		}
		else if (wParam == VK_LEFT) {
			if (turn0 % 2 == 0) {
				q--;
				if (q < 0) {
					q = 39;
				}
				if (witch[q][w] == 'R') {
					q++;
				}
				else if (witch[q][w] == 'Y') {
					x = rand() % 255;
					y = rand() % 255;
					z = rand() % 255;
				}
				else if (witch[q][w] == 'P') {
					if (turn1 == 0) {
						m++;n++;
						if (m > 5 && n > 5) {
							turn1++;
						}
					}
					else if (turn1 == 1) {
						m--;n--;
						if (m < 1 && n < 1) {
							turn1 = 0;
						}
					}
				}
				else if (witch[q][w] == 'B') {
					t = rand() % 5 + 1;
				}
				k = 0;j = 0;
				turn0++;
				InvalidateRgn(hwnd, NULL, TRUE);
				ReleaseDC(hwnd, hdc);
			}
			break;
		}
		else if (wParam == VK_UP) {
			if (turn0 % 2 == 0) {
				w--;
				if (w < 1) {
					w = 39;
				}
				if (witch[q][w] == 'R') {
					w++;
				}
				else if (witch[q][w] == 'Y') {
					x = rand() % 255;
					y = rand() % 255;
					z = rand() % 255;
				}
				else if (witch[q][w] == 'P') {
					if (turn1 == 0) {
						m++;n++;
						if (m > 5 && n > 5) {
							turn1++;
						}
					}
					else if (turn1 == 1) {
						m--;n--;
						if (m < 1 && n < 1) {
							turn1 = 0;
						}
					}
				}
				else if (witch[q][w] == 'B') {
					t = rand() % 5 + 1;
				}
				k = 0;j = 0;
				turn0++;
				InvalidateRgn(hwnd, NULL, TRUE);
				ReleaseDC(hwnd, hdc);
			}
			break;
		}
		else if (wParam == VK_DOWN) {
			if (turn0 % 2 == 0) {
				w++;
				if (w > 39) {
					w = 1;
				}
				if (witch[q][w] == 'R') {
					w--;
				}
				else if (witch[q][w] == 'Y') {
					x = rand() % 255;
					y = rand() % 255;
					z = rand() % 255;
				}
				else if (witch[q][w] == 'P') {
					if (turn1 == 0) {
						m++;n++;
						if (m > 5 && n > 5) {
							turn1++;
						}
					}
					else if (turn1 == 1) {
						m--;n--;
						if (m < 1 && n < 1) {
							turn1 = 0;
						}
					}
				}
				else if (witch[q][w] == 'B') {
					t = rand() % 5 + 1;
				}
				k = 0;j = 0;
				turn0++;
				InvalidateRgn(hwnd, NULL, TRUE);
				ReleaseDC(hwnd, hdc);
			}
			break;
		}
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == 'l') {
			if (turn0 % 2 == 1) {
				p++;
				if (p > 39) {
					p = 1;
				}
				if (witch[p][o] == 'R') {
					p--;
				}
				else if (witch[p][o] == 'Y') {
					x1 = rand() % 255;
					y1 = rand() % 255;
					z1 = rand() % 255;
				}
				else if (witch[p][o] == 'P') {
					if (turn2 == 0) {
						v++;l++;
						if (v > 5 && l > 5) {
							turn2++;
						}
					}
					else if (turn2 == 1) {
						v--;l--;
						if (v < 1 && l < 1) {
							turn2 = 0;
						}
					}
				}
				else if (witch[p][o] == 'B') {
					g = rand() % 5 + 1;
				}
				k = 0;j = 0;
				turn0++;
				InvalidateRect(hwnd, NULL, TRUE);
				ReleaseDC(hwnd, hdc);
			}
			break;
		}
		else if (wParam == 'j') {
			if (turn0 % 2 == 1) {
				p--;
				if (p < 0) {
					p = 39;
				}
				if (witch[p][o] == 'R') {
					p++;
				}
				else if (witch[p][o] == 'Y') {
					x1 = rand() % 255;
					y1 = rand() % 255;
					z1 = rand() % 255;
				}
				else if (witch[p][o] == 'P') {
					if (turn2 == 0) {
						v++;l++;
						if (v > 5 && l > 5) {
							turn2++;
						}
					}
					else if (turn2 == 1) {
						v--;l--;
						if (v < 1 && l < 1) {
							turn2 = 0;
						}
					}
				}
				else if (witch[p][o] == 'B') {
					g = rand() % 5 + 1;
				}
				k = 0;j = 0;
				turn0++;
				InvalidateRgn(hwnd, NULL, TRUE);
				ReleaseDC(hwnd, hdc);
			}
			break;
		}
		else if (wParam == 'i') {
			if (turn0 % 2 == 1) {
				o--;
				if (o < 1) {
					p = 39;
				}
				if (witch[p][o] == 'R') {
					o++;
				}
				else if (witch[p][o] == 'Y') {
					x1 = rand() % 255;
					y1 = rand() % 255;
					z1 = rand() % 255;
				}
				else if (witch[p][o] == 'P') {
					if (turn2 == 0) {
						v++;l++;
						if (v > 5 && l > 5) {
							turn2++;
						}
					}
					else if (turn2 == 1) {
						v--;l--;
						if (v < 1 && l < 1) {
							turn2 = 0;
						}
					}
				}
				else if (witch[p][o] == 'B') {
					g = rand() % 5 + 1;
				}
				k = 0;j = 0;
				turn0++;
				InvalidateRgn(hwnd, NULL, TRUE);
				ReleaseDC(hwnd, hdc);
			}
			break;
		}
		else if (wParam == 'k') {
			if (turn0 % 2 == 1) {
				o++;
				if (o > 39) {
					o = 1;
				}
				if (witch[p][o] == 'R') {
					o--;
				}
				else if (witch[p][o] == 'Y') {
					x1 = rand() % 255;
					y1 = rand() % 255;
					z1 = rand() % 255;
				}
				else if (witch[p][o] == 'P') {
					if (turn2 == 0) {
						v++;l++;
						if (v > 5 && l > 5) {
							turn2++;
						}
					}
					else if (turn2 == 1) {
						v--;l--;
						if (v < 1 && l < 1) {
							turn2 = 0;
						}
					}
				}
				else if (witch[p][o] == 'B') {
					g = rand() % 5 + 1;
				}
				k = 0;j = 0;
				turn0++;
				InvalidateRgn(hwnd, NULL, TRUE);
				ReleaseDC(hwnd, hdc);
			}
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0;i < 1600;i++) {
			if (i % 40 == 0) {
				k = 0;
				j++;
			}
			if (i == 1 || i==150 ||i==740 ||i==1423||i==49||i==264) {
				POINT point0[8] = { {0 + k * 20,0 + j * 20},{20 + k * 20,0 + j * 20}, {20 + k * 20, 20 + j * 20} ,{0 + k * 20, 20 + j * 20} };
				hBrush = CreateSolidBrush(RGB(255, 0, 0));//빨강->장애물
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Polygon(hdc, point0, 4);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
				witch[k][j] = 'R';
				k++;
			}
			else if (i == 12||i==727||i==333||i==558||i==1684||i==782) {
				POINT point0[8] = { {0 + k * 20,0 + j * 20},{20 + k * 20,0 + j * 20}, {20 + k * 20, 20 + j * 20} ,{0 + k * 20, 20 + j * 20} };
				hBrush = CreateSolidBrush(RGB(255, 255, 0));//노랑->색상변경
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Polygon(hdc, point0, 4);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
				witch[k][j] = 'Y';
				k++;
			}
			else if (i == 36||i==195||i==456||i==824||i==1168||i==666) {
				POINT point0[8] = { {0 + k * 20,0 + j * 20},{20 + k * 20,0 + j * 20}, {20 + k * 20, 20 + j * 20} ,{0 + k * 20, 20 + j * 20} };
				hBrush = CreateSolidBrush(RGB(255, 0, 255));//보라->크기변경
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Polygon(hdc, point0, 4);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
				witch[k][j] = 'P';
				k++;
			}
			else if (i == 45||i==348||i==684||i==753||i==1384||i==941) {
				POINT point0[8] = { {0 + k * 20,0 + j * 20},{20 + k * 20,0 + j * 20}, {20 + k * 20, 20 + j * 20} ,{0 + k * 20, 20 + j * 20} };
				hBrush = CreateSolidBrush(RGB(0, 255, 255));//하늘->모양변경
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Polygon(hdc, point0, 4);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
				witch[k][j] = 'B';
				k++;
			}
			else {
				POINT point0[8] = { {0 + k * 20,0 + j * 20},{20 + k * 20,0 + j * 20}, {20 + k * 20, 20 + j * 20} ,{0 + k * 20, 20 + j * 20} };
				hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				oldPen = (HPEN)SelectObject(hdc, hPen);
				Polygon(hdc, point0, 4);
				SelectObject(hdc, oldPen);
				DeleteObject(hPen);
				k++;
			}
		}
		if (t == 1) {
			POINT point3[6] = { {0 + q * 20+m,20 + w * 20-n}, {20 + q * 20-m,20 + w * 20-n}, {10 + q * 20,0 + w * 20+n} };
			hBrush = CreateSolidBrush(RGB(x, y, z));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point3, 3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if (t == 2) {
			POINT point4[10] = { {0 + q * 20+m,0 + w * 20+n} ,{20 + q * 20-m,0 + w * 20+n}, {0 + q * 20+m,20 + w * 20-n}, {20 + q * 20-m,20 + w * 20-n}, {10 + q * 20,10 + w * 20} };
			hBrush = CreateSolidBrush(RGB(x, y, z));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point4, 5);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if (t == 3) {
			POINT point3[10] = { {10+q*20,0+w*20+n}, {0+q*20+m,10+w*20+n}, {5+q*20+m,20+w*20-n}, {15+q*20-m,20+w*20-n} ,{20+q*20-m,10+w*20+n} };
			hBrush = CreateSolidBrush(RGB(x, y, z));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point3, 5);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if (t == 4) {
			hBrush = CreateSolidBrush(RGB(x, y, z));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, 0+q*20+m, 0+w*20+n, 20+q*20-m, 20+w*20-n);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if (t == 5) {
			hBrush = CreateSolidBrush(RGB(x, y, z));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, 2 + q * 20+m, 2 + w * 20+n, 17 + q * 20-m, 17 + w * 20-n);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if ( g == 1) {
			POINT point3[6] = { {0 + p * 20+v,20 + o * 20-l}, {20 + p * 20-v,20 + o * 20-l}, {10 + p * 20,0 + o * 20+l} };
			hBrush = CreateSolidBrush(RGB(x1, y1, z1));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point3, 3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if ( g == 2) {
			POINT point4[10] = { {0 + p * 20+v,0 + o * 20+l} ,{20 + p * 20-v,0 + o * 20+l}, {0 + p * 20+v,20 + o * 20-l}, {20 + p * 20-v,20 + o * 20-l}, {10 + p * 20,10 + o * 20} };
			hBrush = CreateSolidBrush(RGB(x1, y1, z1));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point4, 5);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if (g == 3) {
			POINT point3[10] = { {10 + p * 20,0 + o * 20+l}, {0 + p * 20+v,10 + o * 20+l}, {5 + p * 20+v,20 + o * 20-l}, {15 + p * 20-v,20 + o * 20-l} ,{20 + p * 20-v,10 + o * 20+l} };
			hBrush = CreateSolidBrush(RGB(x1, y1, z1));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point3, 5);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if ( g == 4) {
			hBrush = CreateSolidBrush(RGB(x1, y1, z1));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, 0 + p * 20+v, 0 + o * 20+l, 20 + p * 20-v, 20 + o * 20-l);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if ( g == 5) {
			hBrush = CreateSolidBrush(RGB(x1, y1, z1));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, 2 + p * 20+v, 2 + o * 20+l, 17 + p * 20-v, 17 + o * 20-l);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}