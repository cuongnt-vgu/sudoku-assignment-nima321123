#include <stdlib.h>
#include "sudoku.h"
#include <stdio.h>
#define BOARD_SIZE 9

typedef struct {
    Cell *p_cell;
    int values[2];
} HiddenPair;

int check_hidden_pair_row(SudokuBoard *p_board, int row, int candidate1, int candidate2) {
    int count[2] = {0, 0};

    for (int j = 0; j < BOARD_SIZE; j++) {
        Cell *currentCell = &p_board->data[row][j];
        int *candidates = get_candidates(currentCell);

        for (int c = 0; c < currentCell->num_candidates; c++) {
            if (candidates[c] == candidate1) count[0]++;
            if (candidates[c] == candidate2) count[1]++;
        }

        free(candidates);
    }

    return (count[0] == 2 && count[1] == 2);
}

int check_hidden_pair_column(SudokuBoard *p_board, int column, int candidate1, int candidate2) {
    int count[2] = {0, 0};

    for (int i = 0; i < BOARD_SIZE; i++) {
        Cell *currentCell = &p_board->data[i][column];
        int *candidates = get_candidates(currentCell);

        for (int c = 0; c < currentCell->num_candidates; c++) {
            if (candidates[c] == candidate1) count[0]++;
            if (candidates[c] == candidate2) count[1]++;
        }

        free(candidates);
    }

    return (count[0] == 2 && count[1] == 2);
}

int check_hidden_pair_box(SudokuBoard *p_board, int row, int column, int candidate1, int candidate2) {
    int count[2] = {0, 0};
    int startRow = row - row % 3;
    int startColumn = column - column % 3;

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startColumn; j < startColumn + 3; j++) {
            Cell *currentCell = &p_board->data[i][j];
            int *candidates = get_candidates(currentCell);

            for (int c = 0; c < currentCell->num_candidates; c++) {
                if (candidates[c] == candidate1) count[0]++;
                if (candidates[c] == candidate2) count[1]++;
            }

            free(candidates);
        }
    }

    return (count[0] == 2 && count[1] == 2);
}
int hidden_pairs(SudokuBoard *p_board) {
    int num_cells = BOARD_SIZE * BOARD_SIZE;
    HiddenPair *hiddenPairs = (HiddenPair *)malloc(num_cells * sizeof(HiddenPair));
    if (hiddenPairs == NULL) {
        printf("Error: could not allocate memory for hiddenPairs\n");
        return -1;
    }
    int hiddenPairCounter = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Cell *currentCell = &p_board->data[i][j];

            if (currentCell->num_candidates > 2) {
                int *candidates = get_candidates(currentCell);

                for (int c1 = 0; c1 < currentCell->num_candidates - 1; c1++) {
                    for (int c2 = c1 + 1; c2 < currentCell->num_candidates; c2++) {
                        int isHiddenPair[3] = {0, 0, 0};

                        // Check for hidden pair in the row
                        isHiddenPair[0] = check_hidden_pair_row(p_board, i, candidates[c1], candidates[c2]);

                        // Check for hidden pair in the column
                        isHiddenPair[1] = check_hidden_pair_column(p_board, j, candidates[c1], candidates[c2]);

                        // Check for hidden pair in the box
                        isHiddenPair[2] = check_hidden_pair_box(p_board, i, j, candidates[c1], candidates[c2]);

                        if (isHiddenPair[0] || isHiddenPair[1] || isHiddenPair[2]) {
                            if (hiddenPairCounter >= num_cells) {
                                free(hiddenPairs);
                                free(candidates);
                                return -1;
                            }
                            hiddenPairs[hiddenPairCounter].p_cell = currentCell;
                            hiddenPairs[hiddenPairCounter].values[0] = candidates[c1];
                            hiddenPairs[hiddenPairCounter].values[1] = candidates[c2];
                            hiddenPairCounter++;
                        }
                    }
                }
                free(candidates);
            }
        }
    }

    for (int k = 0; k < hiddenPairCounter; k++) {
        Cell *currentCell = hiddenPairs[k].p_cell;
        int values[2] = {hiddenPairs[k].values[0], hiddenPairs[k].values[1]};

        for (int c = 0; c < BOARD_SIZE; c++) {
            if (c != values[0] - 1 && c != values[1] - 1) {
                currentCell->candidates[c] = 0;
            } else {
                currentCell->candidates[c] = 1;
            }
        }
        currentCell->num_candidates = 2;
    }

    free(hiddenPairs);

    return hiddenPairCounter;
}