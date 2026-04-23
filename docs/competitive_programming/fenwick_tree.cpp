/*
Title: Fenwick Tree (Binary Indexed Tree) in C++23
Category: Competitive Programming
File: fenwick_tree.cpp
C++ Standard: C++23
Difficulty: Beginner to Intermediate

Purpose:
Detailed implementation of a Fenwick Tree for efficient prefix sum 
queries and point updates. Comparison with Segment Tree and real-world 
competitive programming use cases.

Compile:
g++ -std=c++23 fenwick_tree.cpp -o fenwick_tree

Run:
./fenwick_tree

Key Topics:
- BIT structure and bit manipulation (i & -i)
- Point Update, Prefix Query
- Range Sum Query
- 0-based vs 1-based indexing
- Multi-dimensional Fenwick Trees (Brief overview)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <iostream>
#include <vector>
#include <print>

/**
 * Fenwick Tree (BIT):
 * A space-efficient data structure for prefix sums.
 * 
 * Pros:
 * - Extremely easy to implement.
 * - Low constant factor.
 * - Uses exactly O(N) space.
 * 
 * Cons:
 * - Only works for invertible operations (Sum, XOR) if range queries are needed.
 * - Harder to use for range-min/max queries compared to Segment Tree.
 */

template <typename T>
class FenwickTree {
private:
    int n;
    std::vector<T> bit;

public:
    // 0-indexed interface, but internally 1-indexed for bit tricks
    FenwickTree(int _n) : n(_n), bit(_n + 1, 0) {}

    FenwickTree(const std::vector<T>& arr) : FenwickTree((int)arr.size()) {
        for (int i = 0; i < n; i++) {
            update(i, arr[i]);
        }
    }

    /**
     * Adds 'val' to element at index 'idx'.
     * Time Complexity: O(log N)
     */
    void update(int idx, T val) {
        for (++idx; idx <= n; idx += idx & -idx) {
            bit[idx] += val;
        }
    }

    /**
     * Returns the prefix sum up to index 'idx' (inclusive).
     * Time Complexity: O(log N)
     */
    T query(int idx) {
        T res = 0;
        for (++idx; idx > 0; idx -= idx & -idx) {
            res += bit[idx];
        }
        return res;
    }

    /**
     * Returns the sum in range [l, r].
     * Time Complexity: O(log N)
     */
    T query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

int main() {
    std::println("--- Fenwick Tree (BIT) Demo ---");

    std::vector<long long> data = {3, 2, -1, 6, 5, 4, -3, 3, 7, 2, 3};
    FenwickTree<long long> ft(data);

    std::println("Original Data Sum [0, 10]: {}", ft.query(0, 10)); // 31
    std::println("Prefix Sum [0, 5]: {}", ft.query(5)); // 19
    std::println("Range Sum [3, 7]: {}", ft.query(3, 7)); // 13

    std::println("\nUpdating index 3 by +10...");
    ft.update(3, 10);
    std::println("New Range Sum [3, 7]: {}", ft.query(3, 7)); // 23

    std::println("\n--- Complexity Analysis ---");
    std::println("- Space: O(N)");
    std::println("- Point Update: O(log N)");
    std::println("- Prefix Query: O(log N)");
    std::println("- Construction: O(N log N) or O(N) with optimization");

    std::println("\n--- Interview Pitfalls ---");
    std::println("- Indexing: 1-based indexing is required for the bitwise trick (i & -i).");
    std::println("- Non-invertible operations: Cannot easily use BIT for Range Max without extra logic.");
    std::println("- Multi-dimensional BIT: Complexity becomes O(log^D N) which is fine for 2D but slow for higher.");

    return 0;
}
