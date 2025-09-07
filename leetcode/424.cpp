// 424. Longest Repeating Character Replacement
// g++ leetcode/424.cpp -o leetcode/424.o && ./leetcode/424.o

#include<bits/stdc++.h>
using namespace std;

int characterReplacement(string s, int k) {
    vector<int> freq(26, 0);
    int maxCount = 0;
    int maxLen = 0;
    int i = 0;
    for (int j = 0; j < s.size(); j++) {
        freq[s[j] - 'A']++;
        maxCount = max(maxCount, freq[s[j] - 'A']);
        while ((j - i + 1) - maxCount > k) {
            freq[s[i] - 'A']--;
            i++;
        }
        maxLen = max(maxLen, j - i + 1);
    }
    return maxLen;
}


int main() {
    string s1 = "ABAB";
    int k1 = 2;
    cout << characterReplacement(s1, k1) << endl;
    string s2 = "AABABBA";
    int k2 = 1;
    cout << characterReplacement(s2, k2) << endl;
}