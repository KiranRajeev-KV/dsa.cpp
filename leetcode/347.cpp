// 347. Top K Frequent Elements
// g++ leetcode/347.cpp -o leetcode/347.o && ./leetcode/347.o

#include <bits/stdc++.h>
using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> count;
    for (int num : nums) {
        count[num]++;
    }

    vector<pair<int, int>> arr;
    for (const auto& p : count) {
        arr.push_back({p.second, p.first});
    }
    sort(arr.rbegin(), arr.rend());

    vector<int> res;
    for (int i = 0; i < k; ++i) {
        res.push_back(arr[i].second);
    }
    return res;
}

int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{1,1,1,2,2,3}, 2},
        {{1}, 1},
        {{4,4,4,4,5,5,6}, 2},
        {{1,2,3,4,5,6,7,8,9,10}, 5},
        {{3,0,1,0}, 1}
    };

    for (size_t i = 0; i < testCases.size(); i++) {
        cout << "Test case " << i + 1 << ": ";
        vector<int> result = topKFrequent(testCases[i].first, testCases[i].second);
        cout << "[";
        for (const auto& num : result)
            cout << num << " ";
        cout << "]" << endl;
    }
    return 0;
}