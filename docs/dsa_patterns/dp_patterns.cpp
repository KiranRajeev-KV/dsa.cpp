/*
Title: Dynamic Programming Patterns Complete Guide
Category: DSA Patterns
File: dp_patterns.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
A comprehensive guide to core DP patterns: 0/1 Knapsack, Longest Common 
Subsequence, and Fibonacci. Demonstrates memoization (Top-Down) and 
tabulation (Bottom-Up) with memory optimizations.

Compile:
g++ -std=c++23 dp_patterns.cpp -o dp_patterns

Run:
./dp_patterns

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Fibonacci (The building block)
- 0/1 Knapsack (Subset selection)
- Longest Common Subsequence (LCS) (String alignment)
- Memory Optimization (Space-saving tabulation)
- Production Notes: std::mdspan and Cache Locality

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <print>
#include <string_view>

/**
 * @brief Fibonacci with Tabulation and Space Optimization.
 * Complexity: O(N) Time, O(1) Space.
 */
long long fibonacci(int n) {
    if (n <= 1) return n;
    long long prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; ++i) {
        long long curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

/**
 * @brief 0/1 Knapsack Problem.
 * Given weights and values, find max value within capacity W.
 * Complexity: O(N*W) Time, O(W) Space (Optimized).
 */
int knapsack_01(int W, const std::vector<int>& weights, const std::vector<int>& values) {
    int n = weights.size();
    // Space optimized DP: use 1D array instead of 2D
    std::vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; ++i) {
        // Traverse backwards to avoid using the same item multiple times
        for (int w = W; w >= weights[i]; --w) {
            dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    return dp[W];
}

/**
 * @brief Longest Common Subsequence (LCS).
 * Complexity: O(M*N) Time, O(M*N) Space.
 */
int longest_common_subsequence(std::string_view s1, std::string_view s2) {
    int m = s1.size();
    int n = s2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}

// --- Demos ---

void demo_fib() {
    std::println("\n--- Fibonacci (Space Optimized) ---");
    int n = 10;
    std::println("Fib({}) = {}", n, fibonacci(n));
}

void demo_knapsack() {
    std::println("\n--- 0/1 Knapsack ---");
    std::vector<int> values = {60, 100, 120};
    std::vector<int> weights = {10, 20, 30};
    int W = 50;
    std::println("Weights: {}, Values: {}, Capacity: {}", weights, values, W);
    std::println("Max Value: {}", knapsack_01(W, weights, values));
}

void demo_lcs() {
    std::println("\n--- Longest Common Subsequence ---");
    std::string_view s1 = "abcde";
    std::string_view s2 = "ace";
    std::println("S1: '{}', S2: '{}'", s1, s2);
    std::println("LCS Length: {}", longest_common_subsequence(s1, s2)); // "ace" -> 3
}

/**
 * Interview Pitfalls & Production Notes:
 * 1. State Identification: The most critical step is defining `dp[i][j]`. 
 *    Always write down the recurrence relation before coding.
 * 2. Overlapping Subproblems: Use DP only when subproblems repeat. If not, 
 *    standard recursion or greedy might be better.
 * 3. Space Optimization: Many 2D DP problems (like Knapsack) can be reduced 
 *    to 1D by observing that we only need the previous row or current row.
 * 4. C++23 std::mdspan: In production, for multi-dimensional DP, `std::mdspan` 
 *    (C++23) can provide a safer and more expressive view over a contiguous 
 *    1D buffer, improving cache locality and reducing allocation overhead.
 * 5. Recursion Depth: For Top-Down (Memoization), be wary of stack overflow 
 *    on large inputs. Bottom-Up (Tabulation) is generally safer.
 */

int main() {
    demo_fib();
    demo_knapsack();
    demo_lcs();
    return 0;
}
