#ifndef BUILD_BOARD_H
#define BUILD_BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board_util.h" 

bool fill_cell(board_vals* vals, int board[9][9], int row, int col);
void get_board(int board[9][9]);

#endif
