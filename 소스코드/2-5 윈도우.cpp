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
    static SIZE size;
    static TCHAR str[11][31];
    static int count1 = 0;
    static int count2 = 0;
    static int yPos = 0;
    switch (iMessage) {
    case WM_CREATE:
        CreateCaret(hWnd, NULL, 2, 15);
        ShowCaret(hWnd);
        break;
    case WM_CHAR:
        hDC = GetDC(hWnd);
        if (wParam == VK_BACK) {
            count2--;
            str[count1][count2] = '\0';
            if (count2 == 0) {
                count1--;
                count2 = lstrlen(str[count1]);
                yPos = yPos - 20;
            }
            InvalidateRgn(hWnd, NULL, TRUE);
            break;
        }
        else if (wParam == VK_RETURN) {
            count1++;
            count2 = 0;
            yPos = yPos + 20;
        }
        else {
            str[count1][count2++] = wParam;
        }
        if (count2 >= 30) {
            count1++;
            count2 = 0;
            yPos = yPos + 20;
        }
        if (count1 >= 10) {
            yPos = 0;
            count1 = 0;
        }
        str[count1][count2] = '\0';
        InvalidateRgn(hWnd, NULL, FALSE);
        ReleaseDC(hWnd, hDC);
        break;
    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        for (int i = 0; i <= count1; i++) {
            GetTextExtentPoint32(hDC, str[i], lstrlen(str[i]), &size);
            TextOut(hDC, 0, i * 20, str[i], lstrlen(str[i]));
        }
        SetCaretPos(size.cx, yPos);
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