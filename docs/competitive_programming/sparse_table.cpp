/*
Title: Sparse Table for O(1) Range Queries in C++23
Category: Competitive Programming
File: sparse_table.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Implements a Sparse Table for constant time Range Minimum Queries (RMQ).
Covers precomputation and theory behind idempotent operations.

Compile:
g++ -std=c++23 sparse_table.cpp -o sparse_table

Run:
./sparse_table

Key Topics:
- Precomputing powers of 2
- Sparse Table construction (O(N log N))
- O(1) Range Query for idempotent operations (Min, Max, GCD)
- Memory-Time trade-offs
- C++23 std::bit_width for log calculation

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <print>
#include <bit>

/**
 * Sparse Table:
 * A data structure that answers range queries in O(1) time after O(N log N) 
 * precomputation. It works only for static arrays (no updates).
 * 
 * It is particularly useful for idempotent operations (f(x, x) = x),
 * such as Min, Max, and GCD.
 */

template <typename T>
class SparseTable {
private:
    int n, max_log;
    std::vector<std::vector<T>> table;

public:
    SparseTable(const std::vector<T>& arr) {
        n = (int)arr.size();
        // Use C++23 std::bit_width to find the number of bits needed
        max_log = std::bit_width((unsigned int)n);
        table.assign(max_log, std::vector<T>(n));

        for (int i = 0; i < n; i++) {
            table[0][i] = arr[i];
        }

        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[j][i] = std::min(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    /**
     * Returns the minimum in range [l, r] in O(1).
     */
    T query(int l, int r) {
        if (l > r) return 0; // Should handle error or return identity
        int j = std::bit_width((unsigned int)(r - l + 1)) - 1;
        return std::min(table[j][l], table[j][r - (1 << j) + 1]);
    }
};

int main() {
    std::println("--- Sparse Table (RMQ) Demo ---");

    std::vector<int> data = {7, 2, 3, 0, 5, 10, 3, 12, 18};
    SparseTable<int> st(data);

    std::println("Min Range [0, 8]: {}", st.query(0, 8)); // 0
    std::println("Min Range [0, 2]: {}", st.query(0, 2)); // 2
    std::println("Min Range [4, 7]: {}", st.query(4, 7)); // 3
    std::println("Min Range [7, 8]: {}", st.query(7, 8)); // 12

    std::println("\n--- Complexity Analysis ---");
    std::println("- Precomputation: O(N log N)");
    std::println("- Query: O(1)");
    std::println("- Space: O(N log N)");

    std::println("\n--- Interview Pitfalls ---");
    std::println("- Not Static: Sparse Table does not support updates. Use Segment Tree if updates are needed.");
    std::println("- Non-idempotent: If you use it for Sum, query time is O(log N), similar to BIT but with more memory.");
    std::println("- Memory Limit: O(N log N) space can be quite large for N = 10^6.");
    std::println("- Indexing: Be careful with 0-based indexing and bit shifts (1 << j).");

    return 0;
}
