#pragma once

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <ctime>

#include "button.h"
#include "resource.h"
#include "define.h"

HINSTANCE hInstance_app;
bool move = false;
Button gameBoard(SIZE);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WNDCLASS NewWindowClass(HBRUSH BGcolor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddWudgets(HWND hwnd);

int randint(int start, int end) {
	return rand() % end + start;
}
