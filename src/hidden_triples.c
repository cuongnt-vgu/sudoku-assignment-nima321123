#include "hidden_triples.h"

int hidden_triples(SudokuBoard *p_board) {
    int hidden_triples_count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Cell *cell = &p_board->data[i][j];
            if (cell->value == 0) { // if cell is empty
                for (int k = 1; k <= BOARD_SIZE; k++) {
                    if (cell->candidates[k-1] == 1) { // if k is a candidate
                        for (int l = k+1; l <= BOARD_SIZE; l++) {
                            if (cell->candidates[l-1] == 1) { // if l is a candidate
                                for (int m = l+1; m <= BOARD_SIZE; m++) {
                                    if (cell->candidates[m-1] == 1) { // if m is a candidate
                                        // Check if there are two other cells in the same row, column, or box that have k, l, and m as their only candidates
                                        for (int n = 0; n < BOARD_SIZE; n++) {
                                            for (int o = 0; o < BOARD_SIZE; o++) {
                                                Cell *other_cell = &p_board->data[n][o];
                                                if (other_cell != cell && (other_cell->row_index == cell->row_index || other_cell->col_index == cell->col_index || other_cell->box_index == cell->box_index) && other_cell->candidates[k-1] == 1 && other_cell->candidates[l-1] == 1 && other_cell->candidates[m-1] == 1) {
                                                    int candidate_count = 0;
                                                    for (int p = 1; p <= BOARD_SIZE; p++) {
                                                        if (other_cell->candidates[p-1] == 1) {
                                                            candidate_count++;
                                                        }
                                                    }
                                                    if (candidate_count == 3) { // if other_cell has only k, l, and m as candidates
                                                        hidden_triples_count++;
                                                        // Remove k, l, and m from the candidate lists of all other cells in the same row, column, and box
                                                        for (int q = 0; q < BOARD_SIZE; q++) {
                                                            for (int r = 0; r < BOARD_SIZE; r++) {
                                                                Cell *another_cell = &p_board->data[q][r];
                                                                if (another_cell != cell && another_cell != other_cell && (another_cell->row_index == cell->row_index || another_cell->col_index == cell->col_index || another_cell->box_index == cell->box_index) && (another_cell->candidates[k-1] == 1 || another_cell->candidates[l-1] == 1 || another_cell->candidates[m-1] == 1)) {
                                                                    another_cell->candidates[k-1] = 0;
                                                                    another_cell->candidates[l-1] = 0;
                                                                    another_cell->candidates[m-1] = 0;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return hidden_triples_count;
}