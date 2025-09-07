// 704. Binary Search
// g++ leetcode/704.cpp -o leetcode/704.o && ./leetcode/704.o

#include <bits/stdc++.h>
using namespace std;

int search(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;

    while (l <= r) {
        int m = l + ((r - l) / 2);
        if (nums[m] > target) {
            r = m - 1;
        } else if (nums[m] < target) {
            l = m + 1;
        } else {
            return m;
        }
    }
    return -1;
}

int main() {
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    int target1 = 9;
    cout << search(nums1, target1) << endl;
    vector<int> nums2 = {-1, 0, 3, 5, 9, 12};
    int target2 = 2;
    cout << search(nums2, target2) << endl;
}
