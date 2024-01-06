#include "naked_triples.h"
int naked_triples(SudokuBoard *p_board) {
    int naked_triples_count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE - 2; j++) {
            for (int k = j + 1; k < BOARD_SIZE - 1; k++) {
                for (int l = k + 1; l < BOARD_SIZE; l++) {
                    Cell *cell1 = p_board->p_rows[i][j];
                    Cell *cell2 = p_board->p_rows[i][k];
                    Cell *cell3 = p_board->p_rows[i][l];
                    if (cell1->value == 0 && cell2->value == 0 && cell3->value == 0) { // if all cells are empty
                        int common_candidates[BOARD_SIZE] = {0};
                        for (int m = 1; m <= BOARD_SIZE; m++) {
                            if (cell1->candidates[m-1] == 1 && cell2->candidates[m-1] == 1 && cell3->candidates[m-1] == 1) {
                                common_candidates[m-1] = 1;
                            }
                        }
                        int common_candidate_count = 0;
                        for (int m = 1; m <= BOARD_SIZE; m++) {
                            if (common_candidates[m-1] == 1) {
                                common_candidate_count++;
                            }
                        }
                        if (common_candidate_count == 3) { // if all cells have the same three candidates
                            naked_triples_count++;
                            // Remove the common candidates from the candidate lists of all other cells in the same row
                            for (int m = 0; m < BOARD_SIZE; m++) {
                                if (m != j && m != k && m != l) {
                                    Cell *other_cell = p_board->p_rows[i][m];
                                    for (int n = 1; n <= BOARD_SIZE; n++) {
                                        if (common_candidates[n-1] == 1) {
                                            other_cell->candidates[n-1] = 0;
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
    return naked_triples_count;
}