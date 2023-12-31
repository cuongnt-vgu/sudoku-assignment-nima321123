#include "naked_pairs.h"
#include <stdlib.h>

int naked_pairs(SudokuBoard *p_board) {
    int changes_made = 0;

    // Loop through each row, column, and box
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Loop through each pair of cells
        for (int j = 0; j < BOARD_SIZE - 1; j++) {
            for (int k = j + 1; k < BOARD_SIZE; k++) {
                Cell *cell1 = p_board->p_rows[i][j];
                Cell *cell2 = p_board->p_rows[i][k];

                // Check if both cells have only two candidates and they are the same
                if (cell1->num_candidates == 2 && cell2->num_candidates == 2 &&
                    cell1->candidates[0] == cell2->candidates[0] && cell1->candidates[1] == cell2->candidates[1]) {
                    // Remove these numbers from all other cells in the same row
                    for (int l = 0; l < BOARD_SIZE; l++) {
                        if (l != j && l != k) {
                            Cell *cell = p_board->p_rows[i][l];
                            int removed_candidates = 0;
                            if (cell->candidates[cell1->candidates[0] - 1] == 1) {
                                cell->candidates[cell1->candidates[0] - 1] = 0;
                                removed_candidates++;
                            }
                            if (cell->candidates[cell1->candidates[1] - 1] == 1) {
                                cell->candidates[cell1->candidates[1] - 1] = 0;
                                removed_candidates++;
                            }
                            cell->num_candidates -= removed_candidates;
                            if (removed_candidates > 0) {
                                changes_made = 1;
                            }
                        }
                    }
                }

                // Check columns
                // Repeat the same changes as above

                // Check boxes
                // Repeat the same changes as above
            }
        }
    }

    return changes_made;
}