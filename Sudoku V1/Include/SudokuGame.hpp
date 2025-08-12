/*
Author: Omar ali
Description:
    o Presents console menu, reads/writes user input.
    o Coordinates SudokuBoard and SudokuSolver.
    o Handles error-checking for moves and file operations.
*/

#ifndef SUDOKU_GAME
#define SUDOKU_GAME
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include "SudokuGenerator.hpp"

class SudokuGame 
{
private:
    SudokuBoard board;
public:
    void showMenu(void);
    void initGame(void);
};

#endif