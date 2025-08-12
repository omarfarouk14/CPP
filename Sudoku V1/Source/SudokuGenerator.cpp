/*
Author: omar ali
*/

#include "../Include/SudokuGenerator.hpp"

bool SudokuGenerator::generateSolvedPuzzle(SudokuBoard &board)
{

    for (int row = 1; row <= BOARD_SIZE; row++)
    {
        for (int col = 1; col <= BOARD_SIZE; col++)
        {

            board.setCell(row, col, 0); // Initialize the board to 0
        }
    }

    std::vector<int> num{1, 2, 3, 4, 5, 6, 7, 8, 9};
    // std::random_shuffle(num.begin(), num.end()); // not allowed in c++17
    std::shuffle(num.begin(), num.end(), std::mt19937(std::random_device()())); // Modern shuffle

    for (int row = 1; row <= BOARD_SIZE; row++)
    {
        for (int col = 1; col <= BOARD_SIZE; col++)
        {
            for (int random : num)
            {
                if (board.setCell(row, col, random))
                {
                    if (SudokuSolver::findSolution(board))
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
    return true;
}

bool SudokuGenerator::cleanBoard(SudokuBoard &board, int difficultyLevel)
{


    int emptyCells = 0;
    if (difficultyLevel == 1)
    { // easy level
        emptyCells = 40;
    }
    else if (difficultyLevel == 2)
    { // medium level
        emptyCells = 50;
    }
    else if (difficultyLevel == 3)
    { // hard level
        emptyCells = 60;
    }
    else
    {
        return false; // Invalid difficulty level
    }

    // may delete the same cell more than once
    // for(int i = 0; i < emptyCells; i++){
    //     int row = rand() % BOARD_SIZE + 1;
    //     int col = rand() % BOARD_SIZE + 1;
    //     board.setCell(row,col,0);
    // }

    /*
        we create pair container to store the positions of the 81 cells
    */
    std::vector<std::pair<int, int>> positions;
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            positions.push_back({row + 1, col + 1});
        }
    }
    /*
        then we shuffle the vector and delete the first emptyCells number of cells
        this way we are sure that we will not delete the same cell more than once
        and we are sure that the cells are random
        */
   // std::random_shuffle(positions.begin(), positions.end()); // not allowed in c++17
    std::shuffle(positions.begin(), positions.end(), std::mt19937(std::random_device()())); // Modern shuffle
    for (int i = 0; i < emptyCells; i++)
    {
        board.setCell(positions[i].first, positions[i].second, 0);
    }

    return true;
}