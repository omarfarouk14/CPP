/*
Author: omar ali
Description:
    o Presents console menu, reads/writes user input.
    o Coordinates SudokuBoard and SudokuSolver.
    o Handles error-checking for moves and file operations.
*/

#include "../Include/SudokuGame.hpp"

/*
    * Show the main menu for the Sudoku game.
    * This function displays the options available to the user.
    |====================================|
    |========== Sudoku Game Menu ========|
    |====================================|
    |1. Enter a move                     |
    |2. Solve a puzzle automatically     |
    |3. Generate a new puzzle            |
    |4. Load a saved game                |
    |5. Save current game                |
    |6. Exit                             |
    |====================================|
    |Enter your choice:
*/
void SudokuGame::showMenu(void)
{

    std::string menu =
        "|====================================| \n"
        "|========== Sudoku Game Menu ========| \n"
        "|====================================| \n"
        "|1. Enter a move                     | \n"
        "|2. Solve a puzzle automatically     | \n"
        "|3. Generate a new puzzle            | \n"
        "|4. Load a saved game                | \n"
        "|5. Save current game                | \n"
        "|6. Exit                             | \n"
        "|====================================| \n"
        "|Enter your choice: ";
    std::cout << menu;
}

/*
 * Initialize the Sudoku game.
 */
void SudokuGame::initGame(void)
{
    std::cout << "|====================================| \n"
              << "|====== Welcome to Sudoku Game!======|\n"
              << "|====================================|\n"
              << "|Loading the default puzzle .........|\n";

    if (board.loadPuzzle())
    {
        std::cout << "|Puzzle loaded successfully!         |" << std::endl;
        board.printBoard();
    }
    else
    {
        std::cout << "|Error loading the default puzzle.   |" << std::endl;
    }
    showMenu();

    while (true)
    {

        int choice;
        std::string fileName;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            /* code */
            std::cout << "|Enter a row and column in the following format: |\n"
                      << "|row col number (e.g. 1 2 3)                     |\n"
                      << "|Enter your move choice: ";
            int row, col, num;
            std::cin >> row >> col >> num;
            if (board.setCell(row, col, num))
            {
                std::cout << "|Valid move                                      |" << std::endl;
            }
            else
            {
                std::cout << "|Invalid move. Please try again.                 |" << std::endl;
            }
            break;

        case 2:
            std::cout << "|Solving the puzzle automatically.....|" << std::endl;
            if (SudokuSolver::findSolution(board))
            {
                std::cout << "|Puzzle solved successfully!          |" << std::endl;
            }
            else
            {
                std::cout << "|No solution exists for the puzzle.   |" << std::endl;
            }
            break;

        case 3:
            std::cout << "|Generating a new puzzle ............|\n";
            int difficultyLevel;
            std::cout << "|Enter difficulty level (1-3): ";
            std::cin >> difficultyLevel;
            if (SudokuGenerator::generateSolvedPuzzle(board))
            {
                if(SudokuGenerator::cleanBoard(board, difficultyLevel)){
                    std::cout << "|Puzzle generated successfully!      |" << std::endl;
                }
                else{
                    std::cout << "|Error generating the puzzle.        |" << std::endl;
                }
            }
            else
            {
                std::cout << "|Error generating the puzzle.         |" << std::endl;
            }
            break;
            
        case 4:
            std::cout << "|Loading a saved games ..............|\n";
            for (const auto &file : std::filesystem::directory_iterator("../Puzzle/"))
            {
                if (file.path().extension() == ".txt")
                {
                    std::cout << file.path().filename().stem() << std::endl;
                }
            }
            std::cout << "|Enter the game name to be loaded: ";
            std::cin >> fileName;
            if (board.loadPuzzle(fileName))
            {
                std::cout << "| " + fileName + " loaded successfully            |" << std::endl;
            }
            else
            {
                std::cout << "|Error loading " + fileName + "      |" << std::endl;
            }
            break;

        case 5:
            std::cout << "|Saving the current game ............|\n";
            std::cout << "|Enter the name of the game to be saved: ";
            std::cin >> fileName;
            if (board.savePuzzle(fileName))
            {
                std::cout << "|" + fileName + " saved successfully" + " |" << std::endl;
            }
            else
            {
                std::cout << "|Error saving the puzzle to file: " + fileName + "   |" << std::endl;
            }
            break;

        case 6:
            std::cout << "|Exiting the game. Goodbye!          |" << std::endl;
            return; // Exit the game loop
            break;

        default:
            std::cout << "|Invalid choice. Please try again.   |" << std::endl;
            break;
        }
        board.printBoard();
        showMenu();
    }
}