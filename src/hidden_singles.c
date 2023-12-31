#include "sudoku.h"
#include <stdlib.h>
#include <stdio.h>
#include "utilis.h"
#include "hidden_singles.h"


int hidden_singles(SudokuBoard *p_board) {
    int num_detections = 0;

    // Loop through each row, column, and box
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Loop through each number from 1 to 9
        for (int num = 1; num <= BOARD_SIZE; num++) {
            int count_row = 0, count_col = 0, count_box = 0;
            Cell *single_row = NULL, *single_col = NULL, *single_box = NULL;

            // Check rows, columns, and boxes simultaneously
            for (int j = 0; j < BOARD_SIZE; j++) {
                Cell *cell_row = p_board->p_rows[i][j];
                Cell *cell_col = p_board->p_cols[i][j];
                Cell *cell_box = p_board->p_boxes[i][j];

                if (cell_row->value == 0 && cell_row->candidates[num - 1] == 1) {
                    count_row++;
                    single_row = cell_row;
                }

                if (cell_col->value == 0 && cell_col->candidates[num - 1] == 1) {
                    count_col++;
                    single_col = cell_col;
                }

                if (cell_box->value == 0 && cell_box->candidates[num - 1] == 1) {
                    count_box++;
                    single_box = cell_box;
                }
            }

            // Update hidden singles in row, column, and box
            if (count_row == 1 && single_row->value != num) {
                num_detections++;
                single_row->value = num;
                single_row->num_candidates = 0;
                apply_constraint(p_board->p_rows[i], num);
                printf("Detected hidden single in row %d, value: %d\n", i, num);  // Print when a hidden single is detected
            }

            if (count_col == 1 && single_col->value != num) {
                num_detections++;
                single_col->value = num;
                single_col->num_candidates = 0;
                apply_constraint(p_board->p_cols[i], num);
                printf("Detected hidden single in column %d, value: %d\n", i, num);  // Print when a hidden single is detected
            }

            if (count_box == 1 && single_box->value != num) {
                num_detections++;
                single_box->value = num;
                single_box->num_candidates = 0;
                apply_constraint(p_board->p_boxes[i], num);
                printf("Detected hidden single in box %d, value: %d\n", i, num);  // Print when a hidden single is detected
            }

            // Update the number of candidates for all cells
            for (int j = 0; j < BOARD_SIZE; j++) {
                update_num_candidates(p_board->p_rows[i][j]);
                update_num_candidates(p_board->p_cols[i][j]);
                update_num_candidates(p_board->p_boxes[i][j]);
            }
        }
    }

    return num_detections;
}