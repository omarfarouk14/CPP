/*
Author: omar ali
Description:
    o Backtracking method to generate Solvable Sudoku Puzzle.
*/

#ifndef SUDOKU_GENERATOR
#define SUDOKU_GENERATOR

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"

class SudokuGenerator
{
private:
public:
    static bool generateSolvedPuzzle(SudokuBoard &board);
    static bool cleanBoard(SudokuBoard &board, int difficultyLevel);
};

#endif