// 125.Valid Palindrome
// g++ leetcode/125.cpp -o leetcode/125.o && ./leetcode/125.o

#include<bits/stdc++.h>
using namespace std;

bool isPalindrome(string s) {
    int left = 0;
    int right = s.size() - 1;
    while(left<right) {
        if (!isalnum(s[left])) {
            left++;
            continue;
        }
        if(!isalnum(s[right])) {
            right--;
            continue;
        }
        // cout<<left<<" "<<right<<endl;
        if (tolower(s[left])!=tolower(s[right])) {
            // cout<<s[left]<<" "<<s[right]<<endl;
            return false;
        }
        right--;
        left++;
    }
    return true;
}

int main () {
    string s1 = "A man, a plan, a canal: Panama";
    cout << isPalindrome(s1) << endl;
    string s2 = "race a car";
    cout << isPalindrome(s2) << endl;
    string s3 = " ";
    cout << isPalindrome(s3) << endl;
    string s4 = "0P@#A!!NnN!a@@P0";
    cout << isPalindrome(s4) << endl;
}