#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define BLOCK "*"
#define EMPTY "."
#define QUEEN "&"
#define CHESS_BOARD_LENGTH 8
#define ACCEPTED_QUEENS 8

using namespace std;
using Chess_board = vector<vector<string>>;

void split(string line, vector<string> &splited)
{
    int i = 0;
    while (i < CHESS_BOARD_LENGTH)
    {
        splited[i] = line[i];
        i++;
    }
}

Chess_board getInput()
{
    cout << "in get inupt" << endl;
    Chess_board chess_board;
    string line;
    vector<string> new_line(CHESS_BOARD_LENGTH);
    int i = 0;
    while (i < CHESS_BOARD_LENGTH)
    {
        getline(cin, line);
        split(line, new_line);
        chess_board.push_back(new_line);
        i++;
    }
    return chess_board;
}

void solve(Chess_board chess_board, int first_index, int second_index, int queen_count, int &sum);

void makeBlocks(Chess_board chess_board, int first_index, int second_index, int queen_count, int &sum)
{
    int j = 1;
    for (int i = first_index + 1; i < CHESS_BOARD_LENGTH; i++)
    {
        chess_board[i][second_index] = BLOCK;
        if (second_index - j >= 0)
        {
            chess_board[i][second_index - j] = BLOCK;
        }
        if (second_index + j < CHESS_BOARD_LENGTH)
        {
            chess_board[i][second_index + j] = BLOCK;
        }
        j++;
    }
    solve(chess_board, first_index + 1, 0, queen_count, sum);
}

void solve(Chess_board chess_board, int first_index, int second_index, int queen_count, int &sum)
{    
    if (first_index >= CHESS_BOARD_LENGTH)
    {
        if (queen_count == ACCEPTED_QUEENS)
        {
            sum++;
            return;
        }
        else
        {
            return;
        }
    }
    if (second_index >= CHESS_BOARD_LENGTH)
    {
        solve(chess_board, first_index + 1, 0, queen_count, sum);
    }

    else if (chess_board[first_index][second_index] == BLOCK)
    {
        solve(chess_board, first_index, second_index + 1, queen_count, sum);
    }
    else if (chess_board[first_index][second_index] == EMPTY)
    {
        chess_board[first_index][second_index] = QUEEN;
        queen_count += 1;
        makeBlocks(chess_board, first_index, second_index, queen_count, sum);
        chess_board[first_index][second_index] = EMPTY;
        queen_count -= 1;
        if (second_index + 1 >= CHESS_BOARD_LENGTH)
        {
            return;
        }
        else
        {
            solve(chess_board, first_index, second_index + 1, queen_count, sum);
        }
    }
}

int main()
{
    Chess_board chess_board{getInput()};
    int sum{0};
    solve(chess_board, 0, 0, 0, sum);
    cout << sum << endl;

    return 0;
}