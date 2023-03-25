#include "button.h"


int HasInHorizontalOrVerticalLine(Cell field[SIZE][SIZE], int crossOrCircle);
int HasInDiagonalLine(Cell field[SIZE][SIZE], int res, int crossOrCircle);


enum class Mark {
    Empty, Cross, Circle
};

Button::Button(int size) {

    this->size = size;

    int x = 1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j].id = x++;
        }
    }
}

void Button::MainWndAddWudgets(HWND hwnd) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j].but = CreateWindowA("Button", " ", WS_VISIBLE | WS_CHILD | ES_CENTER,
                                           i * 100, j * 100, 100, 100, hwnd, (HMENU)grid[i][j].id, NULL, NULL);
        }
    }
}

Cell(*Button::GetGrid())[SIZE] {
    return grid;
}


Button::GameResult Button::GetGameResult() {

    Cell(*field)[SIZE] = GetGrid();

    int cross = HasInHorizontalOrVerticalLine(field, 1);
    int circle = HasInHorizontalOrVerticalLine(field, 2);

    cross = HasInDiagonalLine(field, cross, 1);
    circle = HasInDiagonalLine(field, circle, 2);

    if (cross == 3 && circle == 0) {
        return Button::GameResult::CrossWin;
    } else if (circle == 3 && cross == 0) {
        return Button::GameResult::CircleWin;
    } else {
        return Button::GameResult::Draw;
    }
}

int HasInHorizontalOrVerticalLine(Cell field[SIZE][SIZE], int crossOrCircle) {
    int res = 0;
    int auditHorizontal;
    int auditVertical;

    for (int i = 0; i < SIZE; i++) {
        auditHorizontal = 0;
        auditVertical = 0;
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j].num == crossOrCircle) {
                auditHorizontal++;
                if (auditHorizontal == 3)
                    res += 3;
            }
            if (field[j][i].num == crossOrCircle) {
                auditVertical++;
                if (auditVertical == 3)
                    res += 3;
            }
        }
    }
    return res;
}

int HasInDiagonalLine(Cell field[SIZE][SIZE], int res, int crossOrCircle) {
    int auditDiagonal = 0;
    for (int i = 0; i < SIZE; i++) {
        if (field[i][i].num == crossOrCircle) {
            auditDiagonal++;
            if (auditDiagonal == 3)
                res += 3;
        } else continue;
    }
    auditDiagonal = 0;
    for (int j = 3 - 1, i = 0; j >= 0; i++, j--) {
        if (field[i][j].num == crossOrCircle) {
            auditDiagonal++;
            if (auditDiagonal == 3)
                res += 3;
        } else continue;
    }
    return res;
}
