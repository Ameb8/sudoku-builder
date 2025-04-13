#include "../include/select_clues.h"

bool solve(board_vals* vals, int board[9][9], int row, int col, int* solutions) {
    if(row == 9) { // Solution found
        *solutions += 1;
        
        if(*solutions == 2)
            return false; // Solution not unique
    }

    if(board[row][col] <= 0) {
        for(int i = 0; i < 9; i++) {
            if(is_valid(vals, board, row, col, i))  {
                update(vals, board, row, col, i);
                bool continue_search;

                // Continue solving
                if(col == 8)
                    continue_search = solve(vals, board, row + 1, 0, solutions);
                else
                    continue_search = solve(vals, board, row, col + 1, solutions);
            
                undo(vals, board, row, col);
                
                if(!continue_search)
                    return false;
            }
        }
    }

    return true;
}

bool unique_solution(board_vals* vals, int board[9][9]) {
    board_vals* solve_vals = copy_board_vals(vals);
    int solve_board[9][9];
    copy_board(board, solve_board);
    int num_solutions = 0;

    bool valid = solve(solve_vals, solve_board, 0, 0, &num_solutions);
    free(solve_vals);

    return valid;
}

bool hide_cell(board_vals* vals, int board[9][9], int remove_clues) {
    if(remove_clues == 0)
        return true;
    
    int row = rand() % 9;
    int col = rand() % 9;

    while(board[row][col] <= 0) {
        row = rand() % 9;
        col = rand() % 9;
    }

    int val = board[row][col];
    undo(vals, board, row, col);

    if(unique_solution(vals, board)) {
        if(hide_cell(vals, board, remove_clues - 1))
            return true;
        
        update(vals, board, row, col, val - 1);
    }

    return false;
}

void get_puzzle(int solution[9][9], int num_clues) {
    board_vals *vals = init_board_vals(true);
    bool success = hide_cell(vals, solution, 81 - num_clues);
}