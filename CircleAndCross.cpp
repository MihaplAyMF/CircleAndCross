#ifndef UNICODE
#define UNICODE
#endif 

#include "function.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    WNDCLASS wc = NewWindowClass((HBRUSH)(COLOR_WINDOW + 2), LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1)), hInstance,
                                 LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON1)), L"MainWindowClass", WindowProc);

    if (!RegisterClass(&wc)) {
        return -1;
    }

    hInstance_app = hInstance;
    MSG msg = { 0 };

    DWORD dwStyle = WS_VISIBLE | WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME);
    DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

    CreateWindowEx(
        dwExStyle,
        L"MainWindowClass",                                 // Window class
        L"First c++ window",                                // Window text
        dwStyle,                                            // Window style
        100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,              // Size and position
        NULL,                                               // Parent window
        NULL,//LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),    // Menu
        hInstance,                                          // Instance handle
        NULL                                                // Additional application data
    );

    while (TRUE) {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }

    return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGcolor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {

    WNDCLASS wc = {};

    wc.hbrBackground = BGcolor;
    wc.hCursor = Cursor;
    wc.hInstance = hInst;
    wc.hIcon = Icon;
    wc.lpszClassName = Name;
    wc.lpfnWndProc = WindowProc;

    return wc;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;

    HFONT hFont = CreateFont(40, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                             CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Arial");
    switch (uMsg) {

        case WM_CREATE:
            hdc = GetDC(hwnd);
            GetClientRect(hwnd, &rect);
            gameBoard.MainWndAddWudgets(hwnd);


            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    Cell& cell = gameBoard.GetGrid()[i][j];
                    SendMessage(cell.but, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
                }
            }

            ReleaseDC(hwnd, hdc);
            ValidateRect(hwnd, &rect);

            break;
        case WM_COMMAND:

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    Cell& cell = gameBoard.GetGrid()[i][j];
                    if (cell.id == wParam && !cell.press) {
                        move == 0 ? gameBoard.GetGrid()[i][j].num = 1 : gameBoard.GetGrid()[i][j].num = 2;
                        SetWindowTextA(cell.but, move == 0 ? "X" : "O");
                        cell.press = true;
                        move = !move;
                    }
                }
            }

            if (gameBoard.GetGameResult() == Button::CrossWin) {
                MessageBoxA(NULL, "Перемогли хрестики", "Хто ж виграв?", MB_OK); PostQuitMessage(0);
            } else if (gameBoard.GetGameResult() == Button::CircleWin) {
                MessageBoxA(NULL, "Перемогли нолики", "Хто ж виграв?", MB_OK);  PostQuitMessage(0);
            }

            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

