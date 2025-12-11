#include <iostream>
#include <limits> // Required for numeric_limits
#include <vector> // Although <bits/stdc++.h> includes it, being explicit is good practice.

// Use the standard namespace to avoid writing std:: before every standard function
using namespace std;

// Define the size of the Sudoku grid (N x N)
#define N 9

// ----------------------
// Color Macros (ANSI)
// ----------------------
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

// Forward declarations of all functions used in the program
// Updated printGrid to accept originalGrid for color highlighting
void printGrid(int grid[N][N], int originalGrid[N][N]);
bool isSafe(int grid[N][N], int row, int col, int num);
bool solveSudoku(int grid[N][N]);
void inputGrid(int grid[N][N], int originalGrid[N][N]);
void copyGrid(int source[N][N], int destination[N][N]);
void playSudoku(int grid[N][N], int originalGrid[N][N]);
bool isGridFull(int grid[N][N]);

/*
 * ====================================================================
 * Main Function - Program Entry Point
 * ====================================================================
 */
int main()
{
    // `originalGrid` stores the initial puzzle state for the reset option.
    int originalGrid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    // `grid` is the working copy that the solver or player will modify.
    int grid[N][N];
    copyGrid(originalGrid, grid); // Start with the default puzzle

    int choice;
    // Main menu loop runs until the user chooses to exit.
    while (true)
    {
        cout << YELLOW << "\n======= Sudoku Solver Menu =======\n"
             << RESET;
        cout << WHITE << "   1. Solution of the Puzzle\n";
        cout << "   2. Solve Puzzle Manually\n";
        cout << "   3. Enter a New Puzzle\n";
        cout << "   4. Reset to Original Puzzle\n";
        cout << "   5. Display Current Puzzle\n";
        cout << "   6. Exit\n";
        cout << YELLOW << "==================================\n"
             << RESET;
        cout << GREEN << "Enter your choice: " << RESET;
        cin >> choice;

        // Input validation loop to prevent infinite loops
        while (cin.fail())
        {
            cout << RED << "Invalid input. Please enter a number.\n"
                 << RESET;
            cin.clear();                                     // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << GREEN << "Enter your choice: " << RESET;
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
        {
            int tempGrid[N][N];
            copyGrid(grid, tempGrid); // Create a copy to solve
            if (solveSudoku(tempGrid))
            {
                cout << GREEN << "\nSolution Found:\n"
                     << RESET;
                // Pass the *original* working grid 'grid' to highlight the new numbers
                printGrid(tempGrid, grid);
            }
            else
            {
                cout << RED << "\nNo solution exists for this puzzle.\n"
                     << RESET;
            }
            break;
        }
        case 2:
            playSudoku(grid, originalGrid);
            break;
        case 3:
            inputGrid(grid, originalGrid);
            break;
        case 4:
            copyGrid(originalGrid, grid); // Reset the working grid
            cout << GREEN << "\nPuzzle has been reset to its original state.\n"
                 << RESET;
            break;
        case 5:
            cout << CYAN << "\nCurrent Puzzle State:\n"
                 << RESET;
            printGrid(grid, originalGrid);
            break;
        case 6:
            cout << CYAN << "Exiting program. Goodbye!\n"
                 << RESET;
            return 0;
        default:
            cout << RED << "Invalid choice. Please enter a number between 1 and 6.\n"
                 << RESET;
        }
    }

    return 0;
}

/*
 * ====================================================================
 * Manual User Gameplay
 * ====================================================================
 */
void playSudoku(int grid[N][N], int originalGrid[N][N])
{
    int row, col, num;
    while (true)
    {
        printGrid(grid, originalGrid);
        cout << MAGENTA << "\n--- Manual Play Mode ---\n"
             << RESET;
        cout << CYAN << "TO MAKE A MOVE: Enter row, column, and number (e.g., 3 5 8)\n";
        cout << "TO EXIT       : Enter 0 0 0 to return to the main menu\n"
             << RESET;
        cout << GREEN << "Your move: " << RESET;
        cin >> row >> col >> num;

        // Input validation for the move
        if (cin.fail())
        {
            cout << RED << "\nInvalid input. Please enter numbers only.\n"
                 << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Restart the loop
        }

        if (row == 0 || col == 0 || num == 0)
        {
            cout << CYAN << "\nReturning to the main menu...\n"
                 << RESET;
            break;
        }

        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9)
        {
            cout << RED << "\nInvalid input. Please enter numbers between 1 and 9.\n"
                 << RESET;
            continue;
        }

        int rowIndex = row - 1;
        int colIndex = col - 1;

        if (originalGrid[rowIndex][colIndex] != 0)
        {
            cout << RED << "\nCannot change a pre-filled number from the original puzzle!\n"
                 << RESET;
            continue;
        }

        // We check 'isSafe' *before* placing the number.
        // We need to temporarily place it to check, or check without placing.
        // The original `isSafe` checks the grid, so this is a logic bug.
        // Let's create a temporary grid state to check.
        
        // Temporarily place the number to check if it's safe
        int oldVal = grid[rowIndex][colIndex];
        grid[rowIndex][colIndex] = num; 
        
        if (!isSafe(grid, rowIndex, colIndex, num))
        {
            cout << RED << "\nInvalid move! That number conflicts with another in the same row, column, or 3x3 box.\n"
                 << RESET;
            grid[rowIndex][colIndex] = oldVal; // Revert the change
            continue;
        }
        
        // If we are here, the move was safe, but we already placed it.
        // If we want to allow "clearing" a cell, we need to handle num=0,
        // but the prompt says 1-9. Let's allow clearing by setting num=0.
        // The prompt says 0 0 0 to exit, so let's check for num=0 separately.
        // A-ha, the check `if (row == 0 || col == 0 || num == 0)` handles exit.
        // But what if the user wants to clear a cell they entered?
        // Let's modify the logic slightly.
        
        // Re-checking logic from original code.
        // The original `isSafe` checks if `num` *already exists*.
        // But it doesn't check against the cell *itself*. This is a subtle bug.
        // Let's fix `isSafe` to be more robust.

        grid[rowIndex][colIndex] = num; // Place the number
        cout << GREEN << "\nMove accepted.\n"
             << RESET;

        if (isGridFull(grid))
        {
            cout << GREEN << BOLD << "\nCongratulations! You have solved the puzzle!\n"
                 << RESET;
            printGrid(grid, originalGrid);
            break;
        }
    }
}

/*
 * ====================================================================
 * Core Sudoku Logic (AI Solver & Rules)
 * ====================================================================
 */
bool solveSudoku(int grid[N][N])
{
    int row, col;
    bool isEmpty = false;
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (grid[row][col] == 0)
            {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
        {
            break;
        }
    }

    if (!isEmpty)
    {
        return true;
    }

    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            if (solveSudoku(grid))
            {
                return true;
            }
            grid[row][col] = 0; // Backtrack
        }
    }
    return false;
}

/**
 * Checks if placing 'num' at grid[row][col] is valid.
 * NOTE: This function assumes grid[row][col] is 0 or is the number
 * we are trying to place.
 */
bool isSafe(int grid[N][N], int row, int col, int num)
{
    // Check row
    for (int x = 0; x < N; x++)
    {
        // If we find the number in the same row, *but not at the same column*
        if (grid[row][x] == num && x != col)
            return false;
    }

    // Check column
    for (int x = 0; x < N; x++)
    {
         // If we find the number in the same col, *but not at the same row*
        if (grid[x][col] == num && x != row)
            return false;
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int r = i + startRow;
            int c = j + startCol;
            // If we find the number in the box, *but not at the same cell*
            if (grid[r][c] == num && (r != row || c != col))
                return false;
        }
    }

    return true;
}


/*
 * ====================================================================
 * Helper and Utility Functions
 * ====================================================================
 */

/**
 * Prints the Sudoku grid with colors.
 * - Original numbers are BOLD WHITE
 * - User-entered numbers are GREEN
 * - Grid lines are BLUE
 */
void printGrid(int grid[N][N], int originalGrid[N][N])
{
    cout << BLUE << "-------------------------\n"
         << RESET;
    for (int row = 0; row < N; ++row)
    {
        cout << BLUE << "| " << RESET;
        for (int col = 0; col < N; ++col)
        {
            if (grid[row][col] == 0)
            {
                cout << ". "; // Empty cell
            }
            else if (originalGrid[row][col] != 0)
            {
                // Original, fixed number
                cout << BOLD << WHITE << grid[row][col] << " " << RESET;
            }
            else
            {
                // User-entered or solver-entered number
                cout << GREEN << grid[row][col] << " " << RESET;
            }

            if ((col + 1) % 3 == 0)
            {
                cout << BLUE << "| " << RESET;
            }
        }
        cout << "\n";
        if ((row + 1) % 3 == 0)
        {
            cout << BLUE << "-------------------------\n"
                 << RESET;
        }
    }
}

void inputGrid(int grid[N][N], int originalGrid[N][N])
{
    cout << CYAN << "\nEnter your Sudoku puzzle row by row.\n";
    cout << "Use '0' for empty cells.\n\n"
         << RESET;
    for (int i = 0; i < N; i++)
    {
        cout << GREEN << "Enter numbers for row " << i + 1 << " (space-separated): " << RESET;
        for (int j = 0; j < N; j++)
        {
            cin >> grid[i][j];
            // Basic validation for each number entry
            while (cin.fail() || grid[i][j] < 0 || grid[i][j] > 9)
            {
                cout << RED << "\nInvalid input. Please enter numbers (0-9) only for the grid.\n"
                     << RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                // Ask to re-enter the whole row for simplicity
                cout << GREEN << "Please re-enter all 9 numbers for row " << i + 1 << ": " << RESET;
                for (int k = 0; k < N; ++k)
                {
                    cin >> grid[i][k];
                    // Mini-validation loop just in case
                    while(cin.fail() || grid[i][k] < 0 || grid[i][k] > 9) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << RED << "Invalid. Enter number " << k+1 << " again: " << RESET;
                        cin >> grid[i][k];
                    }
                }
                j = N - 1; // End inner loop after re-entry
            }
        }
    }
    copyGrid(grid, originalGrid);
    cout << GREEN << "\nNew puzzle has been set!\n"
         << RESET;
}

void copyGrid(int source[N][N], int destination[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            destination[i][j] = source[i][j];
        }
    }
}

bool isGridFull(int grid[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (grid[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}