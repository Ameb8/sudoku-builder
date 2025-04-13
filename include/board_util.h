#ifndef BOARD_UTIL_H
#define BOARD_UTIL_H

#include <stdbool.h>

typedef struct {
    bool row_vals[9][9];
    bool col_vals[9][9];
    bool sqr_vals[9][9];
} board_vals;

board_vals* init_board_vals(bool init_val);
board_vals* copy_board_vals(board_vals* orig);
void print_board(int board[9][9]);
int get_sqr(int row, int col);
bool is_valid(board_vals* vals, int board[9][9], int row, int col, int val);
void update(board_vals* vals, int board[9][9], int row, int col, int val);
void undo(board_vals* vals, int board[9][9], int row, int col);
void copy_board(int orig[9][9], int copy[9][9]);

#endif