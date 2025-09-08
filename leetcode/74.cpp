// 74. Search a 2D Matrix
// g++ leetcode/74.cpp -o leetcode/74.o && leetcode/74.o

#include <bits/stdc++.h>
using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    int left = 0, right = rows * cols - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row = mid / cols;
        int col = mid % cols;
        if (target > matrix[row][col]) {
            left = mid + 1;
        } else if (target < matrix[row][col]) {
            right = mid - 1;
        } else {
            return true;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    int target = 3;
    cout << searchMatrix(matrix, target) << "\n";
    return 0;
}