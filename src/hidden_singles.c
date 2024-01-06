#include "hidden_singles.h"
#include "sudoku.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Function to find hidden singles in the board and update cell values
int hidden_singles(SudokuBoard *board) {
    int hiddenCount = 0;

    // Create a temporary array to store hidden singles
    HiddenSingle hiddenArray[BOARD_SIZE * BOARD_SIZE];

    // Iterate through each unsolved cell
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            Cell *cell = &board->data[row][col];

            // Check if cell is unsolved
            if (cell->num_candidates > 1) {
                int *cellCandidates = get_candidates(cell);

                // Checking each candidate in the candidates list
                for (int candidateIndex = 0; candidateIndex < cell->num_candidates; candidateIndex++) {
                    int isHidden[3] = {1, 1, 1};

                    // Check uniqueness in the box
                    int boxStartRow = (row / 3) * 3;
                    int boxStartCol = (col / 3) * 3;
                    for (int r = boxStartRow; r < boxStartRow + 3; r++) {
                        if (isHidden[2] == 0) {
                            break;
                        }
                        for (int column = boxStartCol; column < boxStartCol + 3; column++) {
                            if ((r != row || column != col) && is_candidate(&board->data[r][column], cellCandidates[candidateIndex])) {
                                // The candidate is not unique in the same box
                                isHidden[2] = 0;
                                break;
                            }
                        }
                    }

                    // Check uniqueness in the row
                    for (int column = 0; column < BOARD_SIZE; column++) {
                        if (column != col && is_candidate(&board->data[row][column], cellCandidates[candidateIndex])) {
                            // The candidate is not unique in that row
                            isHidden[0] = 0;
                            break;
                        }
                    }

                    // Check uniqueness in the column
                    for (int r = 0; r < BOARD_SIZE; r++) {
                        if (r != row && is_candidate(&board->data[r][col], cellCandidates[candidateIndex])) {
                            // The candidate is not unique in the column
                            isHidden[1] = 0;
                            break;
                        }
                    }

                    // If the candidate is a hidden single, store it in the temporary array
                    if (isHidden[0] || isHidden[1] || isHidden[2]) {
                        printf("SINGLE: %d set to row %d, col %d\n",cellCandidates[candidateIndex],row+1,col+1);
                        hiddenArray[hiddenCount].p_cell = cell;
                        hiddenArray[hiddenCount].value = cellCandidates[candidateIndex];
                        hiddenCount++;
                    }
                }
                free(cellCandidates);
            }
        }
    }

    // Update the board with the found hidden singles
    for (int index = 0; index < hiddenCount; index++) {
        Cell *cell = hiddenArray[index].p_cell;
        int value = hiddenArray[index].value;

        // Update the cell's value
        cell->value = value;
        for (int i=0; i<BOARD_SIZE; i++){
            if (i != (value-1)){
                cell->candidates[i]=0;
            }
        }
        cell->num_candidates = 1;
    }

    return hiddenCount;
}