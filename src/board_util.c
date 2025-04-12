#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../include/board_util.h"

board_vals* init_board_vals(bool init_val) {
    board_vals *board = (board_vals*)calloc(1, sizeof(board_vals));
    if (board == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed!\n");
        return NULL;
    }

    if(init_val) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                board->row_vals[i][j] = true;
                board->col_vals[i][j] = true;
                board->sqr_vals[i][j] = true;
            }
        }
    }

    return board;
}

void print_board(int board[9][9]) {
    printf("\n");

    for(int i = 0; i < 9; i++) {
        printf("\n");
        
        if(i == 3 || i == 6)
            printf("\n");

        for(int j = 0; j < 9; j++) {
            printf("[%d]", board[i][j]);

            if(j == 2 || j == 5)
                printf(" | ");
        }
    }

    printf("\n\n");
}

int get_sqr(int row, int col) {
    return 3 * (row / 3) + col / 3;
}

bool is_valid(board_vals* vals, int board[9][9], int row, int col, int val) {
    if(vals->row_vals[row][val])
        return false;
    if(vals->col_vals[col][val])
        return false;
    if(vals->sqr_vals[get_sqr(row, col)][val])
        return false;
    
    return true;
}

void update(board_vals* vals, int board[9][9], int row, int col, int val) {
    board[row][col] = val + 1;

    vals->row_vals[row][val] = true;
    vals->col_vals[col][val] = true;
    vals->sqr_vals[get_sqr(row, col)][val] = true;
}

void undo(board_vals* vals, int board[9][9], int row, int col) {
    int val = board[row][col] - 1;
    board[row][col] = board[row][col] * -1;

    vals->row_vals[row][val] = false;
    vals->col_vals[col][val] = false;
    vals->sqr_vals[get_sqr(row, col)][val] = false;
}