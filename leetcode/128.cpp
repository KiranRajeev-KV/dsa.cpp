// 128. Longest Consecutive Sequence
// g++ leetcode/128.cpp -o leetcode/128.o && ./leetcode/128.o

#include <bits/stdc++.h>
using namespace std;

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> nums_set(nums.begin(),nums.end());
    int maxlength = 0;
    for (auto i: nums_set) {
        if(nums_set.find(i-1) == nums_set.end()) {
            int streak = 1;
            int curr = i;
            while (nums_set.find(curr+1) != nums_set.end()) {
                streak++;
                curr++;
            }
            maxlength =  max(maxlength, streak);
        }
    }
    return maxlength;
}

int main () {
    vector<int> nums1 = {100,4,200,1,3,2};
    cout << longestConsecutive(nums1) << endl;
    vector<int> nums2 = {0,3,7,2,5,8,4,6,0,1};
    cout << longestConsecutive(nums2) << endl;
    vector<int> nums3 = {0,-1};
    cout << longestConsecutive(nums3) << endl;
    vector<int> nums4 = {9,1,-3,2,4,8,3,-1,6,-2,-4,7};
    cout << longestConsecutive(nums4) << endl;
    return 0;
}