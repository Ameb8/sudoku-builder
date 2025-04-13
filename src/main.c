#include <stdio.h>
#include <time.h>
#include "../include/build_board.h"
#include "../include/select_clues.h"
#include "../include/board_util.h"

int main() {
    srand(time(NULL));
    int board[9][9] = {0};
    
    // Generate solution
    get_board(board);
    print_board(board);
    
    // Generate puzzle
    get_puzzle(board, 25);
    print_board(board);
}