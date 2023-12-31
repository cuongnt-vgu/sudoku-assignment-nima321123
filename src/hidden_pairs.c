#include "hidden_pairs.h"
#include <stdlib.h>

int hidden_pairs(SudokuBoard *p_board) {
    int changes_made = 0;

    // Loop through each row, column, and box
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Loop through each pair of numbers
        for (int num1 = 1; num1 < BOARD_SIZE; num1++) {
            for (int num2 = num1 + 1; num2 <= BOARD_SIZE; num2++) {
                int count = 0;
                Cell *pair[2] = {NULL, NULL};

                // Check rows
                for (int j = 0; j < BOARD_SIZE; j++) {
                    Cell *cell = p_board->p_rows[i][j];
                    if (cell->value == 0 && cell->candidates[num1 - 1] == 1 && cell->candidates[num2 - 1] == 1) {
                        if (count < 2) {
                            pair[count] = cell;
                        }
                        count++;
                    }
                }

                if (count == 2) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        Cell *cell = p_board->p_rows[i][j];
                        if (cell != pair[0] && cell != pair[1]) {
                            if (cell->candidates[num1 - 1] == 1 || cell->candidates[num2 - 1] == 1) {
                                cell->candidates[num1 - 1] = 0;
                                cell->candidates[num2 - 1] = 0;
                                cell->num_candidates -= 2;
                                changes_made = 1;
                            }
                        }
                    }
                }

                // Check columns
                count = 0;
                pair[0] = NULL;
                pair[1] = NULL;
                for (int j = 0; j < BOARD_SIZE; j++) {
                    Cell *cell = p_board->p_cols[i][j];
                    if (cell->value == 0 && cell->candidates[num1 - 1] == 1 && cell->candidates[num2 - 1] == 1) {
                        if (count < 2) {
                            pair[count] = cell;
                        }
                        count++;
                    }
                }

                if (count == 2) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        Cell *cell = p_board->p_cols[i][j];
                        if (cell != pair[0] && cell != pair[1]) {
                            if (cell->candidates[num1 - 1] == 1 || cell->candidates[num2 - 1] == 1) {
                                cell->candidates[num1 - 1] = 0;
                                cell->candidates[num2 - 1] = 0;
                                cell->num_candidates -= 2;
                                changes_made = 1;
                            }
                        }
                    }
                }

                // Check boxes
                count = 0;
                pair[0] = NULL;
                pair[1] = NULL;
                for (int j = 0; j < BOARD_SIZE; j++) {
                    Cell *cell = p_board->p_boxes[i][j];
                    if (cell->value == 0 && cell->candidates[num1 - 1] == 1 && cell->candidates[num2 - 1] == 1) {
                        if (count < 2) {
                            pair[count] = cell;
                        }
                        count++;
                    }
                }

                if (count == 2) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        Cell *cell = p_board->p_boxes[i][j];
                        if (cell != pair[0] && cell != pair[1]) {
                            if (cell->candidates[num1 - 1] == 1 || cell->candidates[num2 - 1] == 1) {
                                cell->candidates[num1 - 1] = 0;
                                cell->candidates[num2 - 1] = 0;
                                cell->num_candidates -= 2;
                                changes_made = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    return changes_made;
}