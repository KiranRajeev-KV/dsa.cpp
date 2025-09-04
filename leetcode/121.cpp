// 121. Best Time to Buy and Sell Stock
// g++ leetcode/121.cpp -o leetcode/121.o && ./leetcode/121.o

#include <bits/stdc++.h>
using namespace std;

int maxProfit(vector<int>& prices) {
    // int maxProfit = 0;
    // for(int i=0;i<prices.size()-1;i++) {
    //     for(int j=i+1;j<prices.size();j++) {
    //         if (prices[j] < prices [i]) continue;
    //         int profit = prices[j] - prices[i];
    //         maxProfit = max(profit,maxProfit);
    //     }
    // }
    // return maxProfit;
    int maxProfit = 0;
    int left = 0;
    int right = 1;
    while(right < prices.size()) {
        if(prices[left] < prices[right]) {
            int profit = prices[right] - prices[left];
            maxProfit = max(maxProfit,profit);
        } else {
            left = right;
        }
        right++;
    }
    return maxProfit;
}

int main() {
    vector<int> prices1 = {7,1,5,3,6,4};
    cout << maxProfit(prices1) << endl;
    vector<int> prices2 = {7,6,4,3,1};
    cout << maxProfit(prices2) << endl;
}