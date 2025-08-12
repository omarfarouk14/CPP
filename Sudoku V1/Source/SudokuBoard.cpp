/*
Author: omar ali
Description:
    o Stores and manipulates the 9×9 grid.
    o Validates row/column/box constraints.
    o Prints the board.
    o (Optional) Loads and saves puzzle data to a file.
*/

#include "../Include/SudokuBoard.hpp"

/*
    check if the number is valid in the given row, column, and box
*/
bool SudokuBoard::isValid(int row, int col, int num) const
{
    if (num != 0)
    {
        /*
            check if the number is in the range of 1 to 9
        */
        if (num < 1 || num > 9)
        {
            /*
                in case of invalid number
            */
            return false;
        }

        /*
            row and col check 1 -> 9
        */
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if ((board[i][col]) == num || (board[row][i] == num))
            {
                /*
                    in case of invalid number
                */
                return false;
            }
        }

        /*
            box check 3*3
        */
        int boxRowStart = row - row % 3;
        int boxColStart = col - col % 3;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i + boxRowStart][j + boxColStart] == num)
                {
                    /*
                        in case of invalid number
                    */
                    return false;
                }
            }
        }
    }
    /*
        in case of valid number
    */
    return true;
}

/*
    print the board
*/
void SudokuBoard::printBoard(void)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        if (row % 3 == 0)
        {
            std::cout << "-------------------------\n";
        }
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (col % 3 == 0)
            {
                std::cout << "| ";
            }
            if (board[row][col] == 0)
            {
                std::cout << ". ";
            }
            else
            {
                std::cout << board[row][col] << " ";
            }
        }
        std::cout << "|\n";
    }
    std::cout << "-------------------------\n";
}

/*
 * Load a Sudoku puzzle from a file.
 */
bool SudokuBoard::loadPuzzle(const std::string fileName)
{
    std::ifstream file(( "../Puzzle/" + fileName + ".txt"));
    if (!file)
    {
        return false;
    }
    // std::cout << "sad\n"; 
    std::string line;
    int row = 0;

    while (getline(file, line))
    {

        if (!line.empty() && line.at(0) == '-')
        {
            continue;
        }

        std::istringstream iss(line);
        std::string word;
        int col = 0;
        while (iss >> word)
        {
            if (word == "|")
            {
                continue;
            }
            else if (word == ".")
            {
                board[row][col] = 0;
            }
            else
            {
                board[row][col] = std::stoi(word);
            }
            col++;
            if (col >= BOARD_SIZE)
            {
                break;
            }
        }

        row++;
        if (row >= BOARD_SIZE)
        {
            break;
        }

        // std::cout << "sad\n"; 

    }
    file.close();
    return true;
}

/*
 * Save the current Sudoku board to a file.
 */
bool SudokuBoard::savePuzzle(const std::string fileName) const
{
    std::ofstream file( ("../Puzzle/" + fileName + ".txt"), std::ios::app);
    if (!file)
    {
        return false;
    }

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        if (row % 3 == 0)
        {           
            file << "-------------------------\n";
        }
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (col % 3 == 0)
            {
                file << "| ";
            }
            if (board[row][col] == 0)
            {
                file << ". ";
            }
            else
            {
                file << board[row][col] << " ";
            }
        }
        file << "|\n";
        
    }
    file << "-------------------------\n";
    file.close();
    return true;
}

/*
 * Get the value of a cell in the Sudoku board.
 */
int SudokuBoard::getCell(int row, int col) const
{
    return board[row - 1][col - 1];
}

/*
 * Set the value of a cell in the Sudoku board.
 */
bool SudokuBoard::setCell(int row, int col, int num)
{
    if (isValid(row - 1, col - 1, num))
    {
        board[row - 1][col - 1] = num;
        return true;
    }
    else
    {
        return false;
    }
}