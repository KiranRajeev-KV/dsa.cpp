// 3. Longest Substring Without Repeating Characters
// g++ leetcode/3.cpp -o leetcode/3.o && ./leetcode/3.o

#include <bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(string s) {
    unordered_set<char> seen;
    int maxLen = 0;
    int i = 0, j = 0;
    while (j < s.size()) {
        if (seen.find(s[j]) == seen.end()) {
            seen.insert(s[j]);
            maxLen = max(maxLen, j - i + 1);
            j++;
        } else {
            seen.erase(s[i]);
            i++;
        }
    }
    return maxLen;
}

int main() {
    string s1 = "abcabcbb";
    cout << lengthOfLongestSubstring(s1) << endl;
    string s2 = "bbbbb";
    cout << lengthOfLongestSubstring(s2) << endl;
    string s3 = "pwwkew";
    cout << lengthOfLongestSubstring(s3) << endl;
}