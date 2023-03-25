#pragma once

#include <Windows.h>
#include "define.h"

typedef struct Cell {
	int id;
	bool press = false;
	int num = 0;
	HWND but;
};

class Button {

public:

	enum GameResult {
		CrossWin,
		CircleWin,
		Draw
	};

	Button(int size);

	void MainWndAddWudgets(HWND hwnd);
	Cell(*GetGrid())[SIZE];
	GameResult GetGameResult();

private:

	int size;
	GameResult state = Draw;
	Cell grid[SIZE][SIZE];

};

