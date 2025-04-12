#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    bool row_vals[9][9];
    bool col_vals[9][9];
    bool sqr_vals[9][9];
} board_vals;

board_vals* init_board_vals() {
    board_vals *board = (board_vals*)calloc(1, sizeof(board_vals));
    if (board == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed!\n");
        return NULL;
    }

    return board;
}

/*
void get_shuffled_vals() {
    int vals[9];

    for(int i = 0; i < 9; i++)
        vals[i] = i + 1;

    for(int i = 8; i > 0; i--) {
        // Generate a random index
        int j = rand() % (i + 1);
    
            // Swap arr[i] with the element at random index arr[j]
        int temp = vals[i];
        vals[i] = vals[j];
        vals[j] = temp;
    }

    return vals;
}*/

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

void undo(board_vals* vals, int board[9][9], int row, int col, int val) {
    board[row][col] = 0;

    vals->row_vals[row][val] = false;
    vals->col_vals[col][val] = false;
    vals->sqr_vals[get_sqr(row, col)][val] = false;
}

bool fill_cell(board_vals* vals, int board[9][9], int row, int col) {
    printf("(%d, %d)\n", row, col);
    
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

            undo(vals, board, row, col, this_val);
        }
    }

    return false;
}

void get_board(int board[9][9]) {
    board_vals *vals = init_board_vals();
    bool success = fill_cell(vals, board, 0, 0);

    if(success) {
        printf("\nBoard Created!");
    } else {
        printf("\nGeneration Failed");
    }

    free(vals);
}

int main() {
    srand(time(NULL));

    int board[9][9] = {0};
    get_board(board);
    print_board(board);

    return 0;
}