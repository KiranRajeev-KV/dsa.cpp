// 36. Valid Sudoku
// g++ leetcode/36.cpp -o leetcode/36.o && ./leetcode/36.o

#include<bits/stdc++.h>
using namespace std;

bool isValidSudoku(vector<vector<char>>& board) {
    unordered_set<char> rows[9], cols[9];
    unordered_map<int, unordered_set<char>> subSquares;
    for (int rowIdx = 0; rowIdx < 9; rowIdx++) {
        for (int colIdx = 0; colIdx < 9; colIdx++) {
            if (board[rowIdx][colIdx] == '.') continue;

            int key = (rowIdx / 3) * 3 + (colIdx / 3);

            if (rows[rowIdx].count(board[rowIdx][colIdx]) == 1) return false;
            if (cols[colIdx].count(board[rowIdx][colIdx]) == 1) return false;
            if (subSquares[key].count(board[rowIdx][colIdx]) == 1) return false;

            rows[rowIdx].insert(board[rowIdx][colIdx]);
            cols[colIdx].insert(board[rowIdx][colIdx]);
            subSquares[key].insert(board[rowIdx][colIdx]);
        }
    }
    return true;
}

int main () {
    vector<vector<char>> board1 = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    if (isValidSudoku(board1)) {
        std::cout << "board1 is valid\n";
    } else {
        std::cout << "board1 is invalid\n";
    }

    vector<vector<char>> board2 = {
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    if (isValidSudoku(board2)) {
        std::cout << "board2 is valid\n";
    } else {
        std::cout << "board2 is invalid\n";
    }
    return 0;
}