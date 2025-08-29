// 4.Median of Two Sorted Arrays
// g++ leetcode/4.cpp -o leetcode/4.o && ./leetcode/4.o

#include<bits/stdc++.h>
using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    vector<int> merged;
    merged.reserve(nums1.size() + nums2.size());
    merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), back_inserter(merged));

    int n = merged.size();
    if (n % 2 == 0) {
        return (merged[n/2 - 1] + merged[n/2]) / 2.0;
    } else {
        return merged[n/2];
    }
}

int main() {
    vector<int> nums1 = {1,3};
    vector<int> nums2 = {2, 7, 9};
    cout << findMedianSortedArrays(nums1, nums2) << endl;
}