#include "../include/select_clues.h"


bool hide_cell(board_vals* vals, int board[9][9], int remove_clues) {
    if(remove_clues == 0)
        return true;
    
    int row = rand() % 9;
    int col = rand() % 9;

    while(board[row][col] > 0) {
        int row = rand() % 9;
        int col = rand() % 9;
    }

    undo(vals, board, row, col);

    //if(unique_solution(vals, board)) {

    //}

    return false;
    
    

}

void get_puzzle(int solution[9][9], int num_clues) {
    board_vals *vals = init_board_vals(true);

    bool success = hide_cell(vals, solution, 81 - num_clues);
}