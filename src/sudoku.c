#include "sudoku.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "utilis.h"
#include "hidden_singles.h"
#include "hidden_pairs.h"
#include "hidden_triples.h"
#include "naked_pairs.h"
#include "naked_triples.h"


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        //printf("Usage: %s <sudoku string>\n", argv[0]);
        return 1;
    }

    SudokuBoard *board = malloc(sizeof(SudokuBoard));
    if (board == NULL) {
        //printf("Memory allocation failed\n");
        return 1;
    }

    //printf("Initializing Sudoku board...\n");
    init_sudoku(board);

    //printf("Loading Sudoku from input...\n");
    load_sudoku(board, argv[1]);

    Cell **p_solved_cells = board->solved_cells;
    int solved_counter = board->solved_counter;
    while (board->solved_counter < BOARD_SIZE * BOARD_SIZE)
    {
        //printf("Checking solved cells...\n");
        solved_counter = check_solved_cells(board, &p_solved_cells);
        if (show_possible(board, p_solved_cells, solved_counter))
        {
            //printf("Possible solution found, continuing...\n");
            continue;
        }
        //printf("Checking for hidden singles...\n");
        solved_counter = hidden_singles(board);
        //printf("After hidden_singles, solved_counter = %d\n", solved_counter);
        if (solved_counter)
        {
            //printf("Hidden single found, continuing...\n");
            continue;
        }
        //printf("Checking for hidden pairs...\n");
        solved_counter = hidden_pairs(board);
        //printf("After hidden_pairs, solved_counter = %d\n", solved_counter);
        if (solved_counter)
        {
            //printf("Hidden pair found, continuing...\n");
            continue;
        }
        //printf("Checking for hidden triples...\n");
        solved_counter = hidden_triples(board);
        //printf("After hidden_triples, solved_counter = %d\n", solved_counter);
        if (solved_counter)
        {
            //printf("Hidden triple found, continuing...\n");
            continue;
        }
        //printf("Checking for naked pairs...\n");
        solved_counter = naked_pairs(board);
        //printf("After naked_pairs, solved_counter = %d\n", solved_counter);
        if (solved_counter)
        {
            //printf("Naked pair found, continuing...\n");
            continue;
        }
        //printf("Checking for naked triples...\n");
        solved_counter = naked_triples(board);
        //printf("After naked_triples, solved_counter = %d\n", solved_counter);
        if (solved_counter)
        {
            //printf("Naked triple found, continuing...\n");
            continue;
        }
    }
    //printf("//printing solution...\n");
    print_solution(board);

    // clean up
    //printf("Freeing Sudoku board...\n");
    free_sudoku(board);
    free(board);
    return 0;
}