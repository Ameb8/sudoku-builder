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

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Number of puzzles to generate and number of clues each must be provided as arguments\n");
        return -1;
    }

    int num_puzzles = atoi(argv[1]);
    int num_clues = atoi(argv[2]);

    if(num_puzzles < 1 || num_clues < 17 || num_clues > 80) {
        printf("Arguments are invalid. Please try again\n");
        return -1;
    }

    srand(time(NULL));

    for(int i = 0; i < num_puzzles; i++) {
        int board[9][9];
        gets_puzzle(board, num_clues);
        upload_puzzle(board);
    }
}
