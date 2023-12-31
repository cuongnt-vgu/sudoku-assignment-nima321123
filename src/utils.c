#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "sudoku.h"

void init_sudoku(SudokuBoard *p_board)
{
    p_board->data = malloc(BOARD_SIZE * sizeof(Cell *));
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        p_board->data[i] = malloc(BOARD_SIZE * sizeof(Cell));
        p_board->p_rows[i] = malloc(BOARD_SIZE * sizeof(Cell *));
        p_board->p_cols[i] = malloc(BOARD_SIZE * sizeof(Cell *));
        p_board->p_boxes[i] = malloc(BOARD_SIZE * sizeof(Cell *));
    }

    // assign rows, cols, boxes constraint
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            p_board->p_rows[i][j] = &p_board->data[i][j];
            p_board->p_cols[j][i] = &p_board->data[i][j];
            p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3] =
                &p_board->data[i][j];

            // set row index and col index
            p_board->data[i][j].row_index = i;
            p_board->data[i][j].col_index = j;
            p_board->data[i][j].box_index = (i / 3) * 3 + j / 3;
        }
    }

    p_board->solved_counter = 0;
}

void free_sudoku(SudokuBoard *p_board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        free(p_board->data[i]);
        free(p_board->p_rows[i]);
        free(p_board->p_cols[i]);
        free(p_board->p_boxes[i]);
    }
    free(p_board->data);
}

bool is_solved(SudokuBoard *p_board)
{
    return p_board->solved_counter == BOARD_SIZE * BOARD_SIZE;
}

void print_solution(SudokuBoard *p_board)
{
    if (!is_solved(p_board)) {
        printf("The Sudoku puzzle is not yet solved.\n");
        return;
    }

    char solution[BOARD_SIZE * BOARD_SIZE + 1]; // +1 for the null-terminating character
    int index = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            solution[index++] = '0' + p_board->data[i][j].value; // Convert integer to character
        }
    }

    solution[index] = '\0'; // Null-terminate the string

    printf("%s\n", solution);
}
void set_candidate(Cell *cell, int value)
{
    cell->candidates[value - 1] = 1;
    cell->num_candidates += 1;
}

void unset_candidate(Cell *cell, int value)
{
    cell->candidates[value - 1] = 0;
    cell->num_candidates -= 1;
}

bool is_candidate(Cell *cell, int value)
{
    return cell->candidates[value - 1] == 1;
}

void set_candidates(Cell *cell, int *candidates, int size)
{
    // reset candidates
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cell->candidates[i] = 0;
    }

    cell->num_candidates = 0;

    // set candidate list
    for (int i = 0; i < size; i++)
    {
        set_candidate(cell, candidates[i]);
    }

    if (size == 1)
    {
        cell->value = candidates[0];
    }
}

int *get_candidates(Cell *cell)
{
    int *out = malloc(cell->num_candidates * sizeof(int));
    int counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (cell->candidates[i])
        {
            out[counter++] = i + 1;
        }
    }
    return out;
}

void load_sudoku(SudokuBoard *p_board, char *textData)
{
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        if (textData[i] - '0')
        {
            int candidates[] = {textData[i] - '0'};
            int num_candidates = 1;
            set_candidates(&(p_board->data[i / BOARD_SIZE][i % BOARD_SIZE]),
                           candidates, num_candidates);
        }
        else
        {
            int candidates[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            int num_candidates = BOARD_SIZE;
            set_candidates(&(p_board->data[i / BOARD_SIZE][i % BOARD_SIZE]),
                           candidates, num_candidates);
        }
    }
}
void update_num_candidates(Cell *cell) {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (cell->candidates[i] == 1) {
            count++;
        }
    }
    cell->num_candidates = count;
}
bool apply_constraint(Cell **p_cells, int value)
{
    bool ret = false;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (is_candidate(p_cells[i], value))
        {
            unset_candidate(p_cells[i], value);
            update_num_candidates(p_cells[i]);  // Update the number of candidates
            ret = true;
        }
    }
    return ret;
}
bool show_possible(SudokuBoard *p_board, Cell **p_solved_cells, int counter)
{
    bool ret = false;
    for (int i = 0; i < counter; i++)
    {
        Cell *solved_cell = p_solved_cells[i];
        ret |= apply_constraint(p_board->p_rows[solved_cell->row_index],
                                solved_cell->value);
        ret |= apply_constraint(p_board->p_cols[solved_cell->col_index],
                                solved_cell->value);
        ret |= apply_constraint(p_board->p_boxes[solved_cell->box_index],
                                solved_cell->value);
    }
    return ret;
}

bool is_in_list(Cell **p_array, int size, Cell *p)
{
    for (int i = 0; i < size; i++)
    {
        if (p == p_array[i])
            return true;
    }
    return false;
}

int check_solved_cells(SudokuBoard *p_board, Cell ***p_solved_cells)
{
    int counter = p_board->solved_counter;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_board->data[i][j].num_candidates == 1 &&
                !is_in_list(p_board->solved_cells, counter,
                            &p_board->data[i][j]))
            {
                int *candidates = get_candidates(&p_board->data[i][j]);
                p_board->data[i][j].value = candidates[0];
                free(candidates);
                p_board->solved_cells[p_board->solved_counter++] =
                    &p_board->data[i][j];
            }
        }
    }
    *p_solved_cells = &p_board->solved_cells[counter];
    return p_board->solved_counter - counter;
}

void print_candidate_num(SudokuBoard *p_board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%d ", p_board->data[i][j].num_candidates);
        }
        printf("\n");
    }
}
