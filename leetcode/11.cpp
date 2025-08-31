// 11.Container With Most Water
// g++ leetcode/11.cpp -o leetcode/11.o && ./leetcode/11.o

#include <bits/stdc++.h>
using namespace std;

int maxArea(vector<int> &height) {
    int left = 0;
    int right = height.size() - 1;
    double maxArea = 0;
    while (left < right) {
        double area = min(height[left], height[right]) * (right - left);
        maxArea = max(area, maxArea);
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return maxArea;
}

int main() {
    vector<int> a = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << maxArea(a) << endl;
}