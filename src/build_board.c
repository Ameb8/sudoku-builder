#include "../include/build_board.h"

bool fill_cell(board_vals* vals, int board[9][9], int row, int col) {
    int first_val = rand() % 9;

    for(int i = 0; i < 9; i ++) {
        int this_val = (i + first_val) % 9;

        if(is_valid(vals, board, row, col, this_val)) {
            update(vals, board, row, col, this_val);
            
            if(row == 8 && col == 8) {
                return true; // Solution found
            } else if(col == 8) {
                if(fill_cell(vals, board, row + 1, 0))
                    return true;
            } else {
                if(fill_cell(vals, board, row, col + 1))
                    return true;
            }

            undo(vals, board, row, col);
        }
    }

    return false;
}

void get_board(int board[9][9]) {
    board_vals *vals = init_board_vals(false);
    bool success = fill_cell(vals, board, 0, 0);

    free(vals);
}
