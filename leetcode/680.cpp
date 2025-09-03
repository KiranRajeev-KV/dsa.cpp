// 680. Valid Palindrome II
// g++ leetcode/680.cpp -o leetcode/680.o && ./leetcode/680.o

#include <bits/stdc++.h>
using namespace std;

bool validPalindrome(string s) {
    int left = 0;
    int right = s.size() - 1;
    int pass = 0;

    while (left < right) {
        if (s[left] == s[right]) {
            left++;
            right--;
        } else {
            pass += 1;
            if (pass > 1) return false;

            int l = left + 1;
            int r = right;
            bool skipLeft = true;
            while (l < r) {
                if (s[l] != s[r]) {
                    skipLeft = false;
                    break;
                }
                l++;
                r--;
            }

            l = left;
            r = right - 1;
            bool skipRight = true;
            while (l < r) {
                if (s[l] != s[r]) {
                    skipRight = false;
                    break;
                }
                l++;
                r--;
            }

            return skipLeft || skipRight;
        }
    }

    return true;
}

int main() {
    string s1 = "abca";
    cout << validPalindrome(s1) << endl;
    string s2 = "abc";
    cout << validPalindrome(s2) << endl;
}