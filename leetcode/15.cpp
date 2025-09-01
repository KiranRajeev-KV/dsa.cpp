// 15. 3Sum
// g++ leetcode/15.cpp -o leetcode/15.o && ./leetcode/15.o

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> threeSum(vector<int> &nums) {
    sort(nums.begin(),nums.end());
    vector<vector<int>> result;

    for (int i=0;i<nums.size();i++) {
        if(nums[i]>0) break;
        if(i>0 && nums[i] == nums[i-1]) continue; // remove duplicate entires
        
        int left = i+1;
        int right = nums.size() - 1;
        while(left<right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum>0) right--;
            else if (sum<0) left++;
            else {
                result.push_back({nums[i], nums[left], nums[right]});
                left++;
                right--;
                while(left<right && nums[left] == nums[left-1]) left++;
                while(left<right && nums[right] == nums[right+1]) right--;
            }
        }
    }
    return result;
}

int main() {
    vector<int> nums1 = {-1,0,1,2,-1,-4};
    vector<vector<int>> result = threeSum(nums1);
    for (auto &triplet : result) {
        cout << "[";
        for (int num : triplet) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }
        
    vector<int> nums2 = {1,-1,-1,0};
    result = threeSum(nums2);
    for (auto &triplet : result) {
        cout << "[";
        for (int num : triplet) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }
}
