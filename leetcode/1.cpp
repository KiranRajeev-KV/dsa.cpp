// 1. Two Sum
// g++ leetcode/1.cpp -o leetcode/1.o && ./leetcode/1.o

#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int,int> counts;
    for (int i = 0; i < nums.size(); i++) {
        int val = target - nums[i];
        if (counts.count(val) > 0) {
            return {counts[val], i};
        }
        counts[nums[i]] = i;
    }
    return {};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = twoSum(nums, target);
    if (!result.empty()) {
        cout << "Indices: " << result[0] << ", " << result[1] << endl;
    } else {
        cout << "No solution found." << endl;
    }
    return 0;
}

    