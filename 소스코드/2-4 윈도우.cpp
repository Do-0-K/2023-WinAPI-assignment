#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
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
    hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, 100, 50, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hDC;
    static int input_x;
    static int input_y;
    static TCHAR gugu[100];
    static SIZE size;
    static TCHAR str[20][10];
    static int count1 = 0;
    static int count2 = 0;
    static int dan = 0;
    static int num = 0;
    switch (iMessage) {
    case WM_CREATE:
        CreateCaret(hWnd, NULL, 2, 15);
        ShowCaret(hWnd);
        break;
    case WM_CHAR:
        hDC = GetDC(hWnd);
        if (wParam == VK_BACK)
            count2--;
        else if (wParam == VK_RETURN) {
            _stscanf_s(str[0], L"%d %d %d %d", &input_x, &input_y, &dan, &num);
            count1 = 0;
            count2 = 0;
            if (input_x == 0 && input_y == 0 && dan == 0 && num == 0) {
                exit(1);
            }
        }
        else {
            str[count1][count2++] = wParam;
        }
        str[count1][count2] = '\0';
        InvalidateRect(hWnd, NULL, TRUE);
        ReleaseDC(hWnd, hDC);
        break;
    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        if (input_x != 0 && input_y != 0 && dan < 20 && num < 30) {
            for (int i = 0; i < num; i++) {
                wsprintf(gugu, L"%d * %d = %d", dan, i + 1, dan * (i + 1));
                TextOut(hDC, input_x, input_y + 20 * i, gugu, lstrlen(gugu));
            }
            input_x = 0;
            input_y = 0;
            dan = 0;
            num = 0;
        }
        else {
            TextOut(hDC, 0, 0, str[0], lstrlen(str[0]));
        }
        GetTextExtentPoint32(hDC, str[0], lstrlen(str[0]), &size);
        SetCaretPos(size.cx, 0);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        HideCaret(hWnd);
        DestroyCaret();
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}