#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include "resource2.h"
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
    WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7);
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
    static int x = 0;
    static int y = 0;
    static int yPos = 0;
    OPENFILENAME OFN;
    OPENFILENAME SFN;
    TCHAR str1[100], lpstrFile[100] = L"";
    TCHAR filter[100] = L"문서 파일(*.txt) \0*.txt\0";
    static HANDLE hFile;
    DWORD dwWritten;
    WORD wd = 0xFEFF;
    DWORD dwRead;
    TCHAR strRead[1][330]{};
    TCHAR d[2] = L"\n";
    static int co = 0;
    switch (iMessage) {
    case WM_CREATE:
        CreateCaret(hWnd, NULL, 2, 15);
        ShowCaret(hWnd);
        for (int i = 0;i < 330;i++) {
            strRead[0][i] = ' ';
        }
        break;
    case WM_CHAR:
        hDC = GetDC(hWnd);
        if (wParam == VK_BACK) {
            count2--;
            str[count1][count2] = '\0';
            if (count2 == 0) {
                if (count1 == 0) {
                    count1 = 0;
                    count2 = 0;
                    InvalidateRgn(hWnd, NULL, TRUE);
                    break;
                }
                count1--;
                count2 = lstrlen(str[count1]);
                yPos = yPos - 20;
                if (count1 < 0) {
                    count1 = 0;
                }
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
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_40072: //--- 메뉴 선택
            memset(&OFN, 0, sizeof(OPENFILENAME));
            OFN.lStructSize = sizeof(OPENFILENAME);
            OFN.hwndOwner = hWnd;
            OFN.lpstrFilter = filter;
            OFN.lpstrFile = lpstrFile;
            OFN.nMaxFile = 256;
            OFN.lpstrInitialDir = L".";
            if (GetOpenFileName(&OFN) != 0) {
                wsprintf(str1, L"%s 파일을 여시겠습니까 ?", OFN.lpstrFile);
                MessageBox(hWnd, str1, L"열기 선택", MB_OK);
                hDC = GetDC(hWnd);
                hFile = CreateFile(lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                ReadFile(hFile, strRead[0], 500, &dwRead, NULL);
                for (int count1 = 0;count1 < 11;count1++) {
                    for (int count2 = 0;count2 < 31;count2++) {
                        if (strRead[0][co] == '\n') {
                            count2 = 0;
                            co++;
                            break;
                        }
                        if (strRead[0][co] != '\0' && count2!=30) {
                            str[count1][count2] = strRead[0][co];
                            x = count1;
                            y = count2;
                        }
                        co++;
                    }
                }
                for (int i = 0; i <= x; i++) {
                    TextOut(hDC, 0, i * 20, str[i], lstrlen(str[i]));
                }
                count1 = x;
                count2 = y;
                CloseHandle(hFile);
                ReleaseDC(hWnd, hDC);
                break;
            }
            break;
        case ID_40073:
            memset(&SFN, 0, sizeof(OPENFILENAME));
            SFN.lStructSize = sizeof(OPENFILENAME);
            SFN.hwndOwner = hWnd;
            SFN.lpstrFilter = filter;
            SFN.lpstrFile = lpstrFile;
            SFN.nMaxFile = 256;
            SFN.lpstrInitialDir = L".";
            if (GetSaveFileName(&SFN) != 0) {
                wsprintf(str1, L"%s 파일에 저장하시겠습니까 ?", SFN.lpstrFile);
                MessageBox(hWnd, str1, L"저장하기 선택", MB_OK);
                hFile = CreateFile(lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
                for (int i = 0;i <= count1;i++) {
                    memcpy(str[i], &wd, 0);
                    WriteFile(hFile, str[i], lstrlen(str[i])*sizeof(TCHAR), &dwWritten, NULL);
                    WriteFile(hFile, d, lstrlen(d) * sizeof(TCHAR), &dwWritten, NULL);
                }
                CloseHandle(hFile);
            }
            break;
        }
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