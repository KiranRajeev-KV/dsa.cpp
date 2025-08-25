// 49. Group Anagrams
// g++ leetcode/49.cpp -o leetcode/49.o && ./leetcode/49.o

#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> groupAnagrams1(vector<string>& strs) {
    unordered_map<string,vector<string>> res;
    for (auto i: strs) {
        vector<int> chCount(26,0);
        for(auto j: i) {
            chCount[j - 'a']++;
        }
        string key = to_string(chCount[0]);
        for (int i=1; i<26; ++i) {
            key += ',' + to_string(chCount[i]);
        }
        res[key].push_back(i);
    }
    vector<vector<string>> result;
    for (auto i: res) {
        result.push_back(i.second);
    }
    return result;
}

vector<vector<string>> groupAnagrams2(vector<string>& strs) {
    if (strs.empty()) {
        return {};
    }
    unordered_map<string,vector<string>> res;
    for (auto i: strs) {
        string key = i;
        sort(key.begin(),key.end());
        res[key].push_back(i);
    }
    vector<vector<string>> result;
    for (auto i: res) {
        result.push_back(i.second);
    }
    return result;
}

int main () {
    vector<vector<string>> testCases = {
        {"eat","tea","tan","ate","nat","bat"},
        {"abc","bca","cab","xyz","zyx","yxz"},
        {"a"},
        {"", ""},
        {"listen", "silent", "enlist", "google", "gooegl"}
    };

    for (size_t i = 0; i < testCases.size(); i++) {
        cout << "Test case " << i + 1 << ": ";
        vector<vector<string>> result = groupAnagrams2(testCases[i]);
        for (const auto& group : result) {
            cout << "[";
            for (const auto& str : group)
                cout << str << " ";
            cout <<"]";
        }
        cout << endl;
    }
    return 0;
}