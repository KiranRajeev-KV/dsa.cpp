// 167. Two Sum II - Input Array Is Sorted
// g++ leetcode/167.cpp -o leetcode/167.o && ./leetcode/167.o

#include<bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> res;
    for (int i=0;i<nums.size();i++) {
        int val = target - nums[i];
        int left = i + 1;
        int right = nums.size()-1;
        while(left<=right) {
            int mid = (left + right) / 2;
            if (nums[mid] == val) {
                return {i+1, mid+1};
            } else if (nums[mid] < val) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return {};
}

int main () {
    vector<int> a = {2,3,4};
    int target = 6;
    vector<int> res = twoSum(a,target);
    for (auto i: res) {
        cout << i << " ";
    }
}