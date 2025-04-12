#ifndef SELECT_CLUES_H
#define SELECT_CLUES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board_util.h" 

bool hide_cell(board_vals* vals, int board[9][9], int remove_clues);
void get_puzzle(int solution[9][9], int num_clues);

#endif
