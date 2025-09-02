// 42.Trapping Rain Water
// g++ leetcode/42.cpp -o leetcode/42.o && ./leetcode/42.o

#include<bits/stdc++.h>
using namespace std;

int trap(vector<int>& height) {
    if (height.empty()) {
        return 0;
    }        
    int left = 0;
    int right = height.size() - 1;
    int leftMax = height[left];
    int rightMax = height[right];
    int trappedWater = 0;
    while(left<right) {
        if (leftMax < rightMax) {
            left++;
            leftMax = max(leftMax,height[left]);
            trappedWater += leftMax - height[left];
        } else {
            right--;
            rightMax = max(rightMax,height[right]);
            trappedWater += rightMax - height[right];
        }
    }
    return trappedWater;
}

int main () {
    vector<int> height1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << trap(height1) << endl;
    vector<int> height2 = {4,2,0,3,2,5};
    cout << trap(height2) << endl;
    return 0;
}
