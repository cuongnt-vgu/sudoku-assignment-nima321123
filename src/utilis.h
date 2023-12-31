#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "sudoku.h"
void update_num_candidates(Cell *cell);
void init_sudoku(SudokuBoard *p_board);
void free_sudoku(SudokuBoard *p_board);
bool is_solved(SudokuBoard *p_board);
void print_solution(SudokuBoard *p_board);
void set_candidate(Cell *cell, int value);
void unset_candidate(Cell *cell, int value);
bool is_candidate(Cell *cell, int value);
void set_candidates(Cell *cell, int *candidates, int size);
int *get_candidates(Cell *cell);
void load_sudoku(SudokuBoard *p_board, char *textData);
bool apply_constraint(Cell **p_cells, int value);
bool show_possible(SudokuBoard *p_board, Cell **p_solved_cells, int counter);
bool is_in_list(Cell **p_array, int size, Cell *p);
int check_solved_cells(SudokuBoard *p_board, Cell ***p_solved_cells);
void print_candidate_num(SudokuBoard *p_board);

#endif // UTILS_H