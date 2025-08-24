// 217.Contains Duplicate
// g++ leetcode/217.cpp -o leetcode/217.o && ./leetcode/217.o

#include <bits/stdc++.h>
#include <vector>
using namespace std;

bool containsDuplicate(vector<int>& nums) {
    unordered_map<int,int> counts;
    for (auto i: nums) {
        if (counts.find(i) == counts.end()) {
            counts[i] = 1;
        } else {
            return true;
        }
    }
    return false;
}

int main() {
    vector<int> nums = {0,0};
    cout << containsDuplicate(nums) << endl;
    return 0;
}