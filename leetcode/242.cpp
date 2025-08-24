// 242.Valid Anagram
// g++ leetcode/242.cpp -o leetcode/242.o && ./leetcode/242.o

#include<bits/stdc++.h>

using namespace std;

bool isAnagram(string s, string t) {
    if (s.length() != t.length()) return false;
    unordered_map<char,int> counts;
    for(auto i: s) {
        counts[i] += 1;
    }
    for (auto i: t) {
        counts[i] -= 1;
    }
    for(auto i: counts) {
        if(i.second != 0) return false;
    }
    return true;
}

int main() {
    vector<pair<string, string>> testCases = {
        {"anagram", "nagaram"},
        {"rat", "car"},
        {"auco", "racecar"},
        {"a", "ab"},
        {"abcde", "fghij"},
        {"abc", "ab"},
        {"", ""},
        {"aabb", "ab"}
    };

    for (const auto& [s, t] : testCases) {
        cout << "isAnagram(\"" << s << "\", \"" << t << "\") = " << isAnagram(s, t) << endl;
    }
    return 0;
}