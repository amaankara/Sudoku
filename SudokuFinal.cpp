#include <iostream>

using namespace std;

const int N = 9;

bool is_valid(int board[N][N], int row, int col, int num)
{
    // Check row
    for (int j = 0; j < N; j++)
        if (board[row][j] == num)
            return false;

    // Check column
    for (int i = 0; i < N; i++)
        if (board[i][col] == num)
            return false;

    // Check 3x3 subgrid
    int box_x = col / 3;
    int box_y = row / 3;
    for (int i = box_y * 3; i < box_y * 3 + 3; i++)
        for (int j = box_x * 3; j < box_x * 3 + 3; j++)
            if (board[i][j] == num)
                return false;

    return true;
}

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

bool enter_number(int board[N][N], int row, int col, int num)
{
    if (is_valid(board, row, col, num))
    {
        board[row][col] = num;
        cout << "Number " << num << " entered at row " << row + 1 << " and column " << col + 1 << endl;
        display_board(board);
        return true;
    }
    else
    {
        cout << "Invalid move. Number " << num << " is already present in the same row, column or 3x3 subgrid. Try again." << endl;
        return false;
    }
}

bool solve(int board[N][N], int row, int col)
{
    if (row == N)
        return true;

    if (board[row][col] != 0)
    {
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

        return false;
    }

    for (int i = 1; i <= N; i++)
    {
        if (is_valid(board, row, col, i))
        {
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

            board[row][col] = 0;
        }
    }

    return false;
}

int main()
{
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
    cout << "Enter 0 to have the program solve the game, or 1 to solve it yourself: ";

    int choice;
    cin >> choice;

    if (choice == 0)
    {
        if (solve(board, 0, 0))
        {
            cout << "The solved board is:" << endl;
            display_board(board);
        }
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
            cout << "Enter 0 0 if you want the computer to solve the rest of the board " << endl;
            cout << "Else enter the row (1-9) and column (1-9) you want to enter the number: ";
            cin >> row >> col;
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
                cout << "Enter the number (1-9): ";
                cin >> num;

                if (!enter_number(board, row, col, num))
                {
                    cout << "Try again." << endl;
                    continue;
                }
            }

            bool flag = true;
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    if (board[i][j] == 0)
                    {
                        flag = false;
                        break;
                    }

            if (flag)
            {
                cout << "Congratulations! You have solved the game of Sudoku." << endl;
                break;
            }
        }
    }
    return 0;
}