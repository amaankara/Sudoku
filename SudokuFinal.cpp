#include <iostream>

using namespace std;

//Declaring a constant valiable N which is the size of the board
const int N = 9;

//Function to check if the number being entered is valid or not
bool is_valid(int board[N][N], int row, int col, int num)
{
    // Check row to see if number already exists
    for (int j = 0; j < N; j++)
        if (board[row][j] == num)
            //return false if number exists in row
            return false;

    // Check column to see if number already exists
    for (int i = 0; i < N; i++)
        if (board[i][col] == num)
            //return false if number exists in column
            return false;

    // Check 3x3 subgrid to see if number already exists
    int box_x = col / 3;
    int box_y = row / 3;
    for (int i = box_y * 3; i < box_y * 3 + 3; i++)
        for (int j = box_x * 3; j < box_x * 3 + 3; j++)
            if (board[i][j] == num)
                //return false if number exists in 3x3 subgrid
                return false;
    //return true if number does not exist in row, column or 3x3 subgrid
    return true;
}

//Function to display the board
void display_board(int board[N][N])
{
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

//Function to check if the number entered is correct
bool enter_number(int board[N][N], int row, int col, int num)
{
    //Make sure the number being entered is valid
    if (is_valid(board, row, col, num))
    {
        board[row][col] = num;
        //Display what row and column the number was entered at
        cout << "Number " << num << " entered at row " << row + 1 << " and column " << col + 1 << endl;
        display_board(board);
        return true;
    }
    //Else number is not valid
    else
    {
        //Display error message because number already exists
        cout << "Invalid move. Number " << num << " is already present in the same row, column or 3x3 subgrid. Try again." << endl;
        return false;
    }
}

//Function for the computer to solve the sudoku game
//Recurisvely call the solve function in order to complete the game.
bool solve(int board[N][N], int row, int col)
{
    //Check if the row is at the end of the board
    if (row == N)
        return true;
    //Check if the current cell is already filled
    if (board[row][col] != 0)
    {
        //Check if the current column is the last column
        if ((col + 1) == N)
        {
            //Try to fill the next row
            if (solve(board, row + 1, 0))
                return true;
        }
        else
        {
            //Try to fill the next cell in the same row
            if (solve(board, row, col + 1))
                return true;
        }

        return false;
    }

    for (int i = 1; i <= N; i++)
    {
        //Check if the current number is valid for the current cell
        if (is_valid(board, row, col, i))
        {
            //Fill the current cell with the current number
            board[row][col] = i;
            if ((col + 1) == N)
            {
                if (solve(board, row + 1, 0))
                    return true;
            }
            else
            {
                if (solve(board, row, col + 1))
                    return true;
            }
            //If the above conditions did not solve the sudoku, un-fill the current cell
            board[row][col] = 0;
        }
    }
    //Return false if there is no solution with the numbers currently entered in the Sudoku board
    return false;
}

//The main function
int main()
{
    //Creating a 2D array which is the 9x9 Sudoku board
    int board[N][N] = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
                       {6, 0, 0, 1, 9, 5, 0, 0, 0},
                       {0, 9, 8, 0, 0, 0, 0, 6, 0},
                       {8, 0, 0, 0, 6, 0, 0, 0, 3},
                       {4, 0, 0, 8, 0, 3, 0, 0, 1},
                       {7, 0, 0, 0, 2, 0, 0, 0, 6},
                       {0, 6, 0, 0, 0, 0, 2, 8, 0},
                       {0, 0, 0, 4, 1, 9, 0, 0, 5},
                       {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    cout << "Welcome to the game of Sudoku!" << endl;
    cout << "The board is partially filled. You can either fill in the rest of the numbers yourself or have the program solve the game for you." << endl;
    display_board(board);
    //Gives the user a choice if they want to fill the board or ask the computer to complete it.
    cout << "Enter 0 to have the program solve the game, or 1 to solve it yourself: ";

    int choice;
    cin >> choice;

    //If choice = 0 then the computer solves the game for them
    if (choice == 0)
    {
        //Call the solve function
        if (solve(board, 0, 0))
        {
            cout << "The solved board is:" << endl;
            //Display the solved board
            display_board(board);
        }
        ////Return this if there is no solution with the numbers currently entered in the Sudoku board
        else
            cout << "This Sudoku puzzle has no solution." << endl;
    }
    else
    {
        cout << "The board is partially filled. You need to fill in the rest of the numbers." << endl;
        display_board(board);

        int row, col, num;
        while (true)
        {
            //Allowing the user to let the computer solve the rest of the board at anytime during the game
            cout << "Enter 0 0 if you want the computer to solve the rest of the board " << endl;
            //User gets to pick the row and column where they want to enter the next number
            cout << "Else enter the row (1-9) and column (1-9) you want to enter the number: ";
            cin >> row >> col;
            //If they enter 0 0, the computer solves the board for them
            if(row == 0 && col == 0)
            {
                if (solve(board, 0, 0))
                {
                    cout << "The solved board is: " << endl;
                    display_board(board);
                }
                else
                    cout << "This sudoku puzzle has no solution." << endl;
                
            }
            else
            {
                row--;
                col--;
                //Enter the number to fill the board
                cout << "Enter the number (1-9): ";
                cin >> num;

                //Uses the enter_number function to check if it is valid
                if (!enter_number(board, row, col, num))
                {
                    cout << "Try again." << endl;
                    continue;
                }
            }

            //Create a flag variable to know when the board is complete
            bool flag = true;
            //Iteratively loops through the entire board to see if there is any 0s in the board
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    //If 0 exists then change flag to false, if no 0s then flag stays true
                    if (board[i][j] == 0)
                    {
                        flag = false;
                        break;
                    }

            //If flag = true, then there is no empty values and the game is complete
            if (flag)
            {
                cout << "Congratulations! You have solved the game of Sudoku." << endl;
                break;
            }
        }
    }
    return 0;
}