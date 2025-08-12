/*
Author: Omar ali 
Description:
    o Stores and manipulates the 9×9 grid.
    o Validates row/column/box constraints.
    o Prints the board.
    o (Optional) Loads and saves puzzle data to a file.
*/

#ifndef SUDOKU_BOARD
#define SUDOKU_BOARD

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#define BOARD_SIZE 9

class SudokuBoard
{

private:
    std::vector<std::vector<int>> board;

public:
    SudokuBoard(void) : board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0)){}
    bool isValid(int row, int col, int num) const;
    void printBoard(void);
    bool loadPuzzle(const std::string fileName = "Default_Puzzle");
    bool savePuzzle(const std::string fileName) const;
    int getCell(int row, int col) const;
    bool setCell(int row, int col, int num);
};

#endif