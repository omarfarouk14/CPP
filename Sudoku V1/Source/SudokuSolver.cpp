/*
Author: omar ali
*/

#include "../Include/SudokuSolver.hpp"

/*
    pseudo code, thinking:
    so we assume we are in a maze there is no absolute for right or wrong, we are in trial and error journey as same as every aspect in our messy life
    first we have 81 cell some are filled and others are empty or maybe all of them are empty
    so we start looping on the 9 rows and the 9 columns if we find an empty cell we try to fill it with valid numbers from 1 -> 9 if one of them is
    valid we move to the next cell and repeat the process if we stuck in one number we return to the previous state and repeat the process with another
    number till we solve the entire puzzle or we stuck and there's no solution for the puzzle
*/
bool SudokuSolver::findSolution(SudokuBoard &board)
{
    
    for (int row = 1; row <= BOARD_SIZE; row++)
    {
        for (int col = 1; col <= BOARD_SIZE; col++)
        {
            if (board.getCell(row, col) == 0)
            {
                for (int i = 1; i <= 9; i++)
                {
                    if (board.setCell(row, col, i))
                    {
                        if (findSolution(board))
                        {
                            return true;
                        }
                        else
                        {
                            board.setCell(row, col, 0);
                        }
                    }
                }
                return false; // No valid number found, backtrack
            }
        }
    }

    return true;
}