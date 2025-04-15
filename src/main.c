#include <stdio.h>
#include <time.h>
#include "../include/build_board.h"
#include "../include/select_clues.h"
#include "../include/board_util.h"
#include "../include/upload_puzzle.h"

int gets_puzzle(int board[9][9], int num_clues) {
    get_board(board);
    get_puzzle(board, num_clues);
}

int main() {
    srand(time(NULL));

    int board[9][9];
    gets_puzzle(board, 25);
    print_board(board);
    upload_puzzle(board);
}
