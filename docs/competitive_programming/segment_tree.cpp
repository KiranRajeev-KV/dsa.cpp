/*
Title: Generic Segment Tree Guide in C++23
Category: Competitive Programming
File: segment_tree.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Implementation of a robust, generic Segment Tree for Range Queries 
(Sum, Min, Max, GCD) and Point Updates. Demonstrates C++ templates 
and functional programming for flexibility.

Compile:
g++ -std=c++23 segment_tree.cpp -o segment_tree

Run:
./segment_tree

Key Topics:
- Recursive Segment Tree structure
- Point Update, Range Query
- Generic merge functions (Lambda-based)
- Lazy Propagation (Introduction)
- Time & Space Complexity

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <iostream>
#include <vector>
#include <functional>
#include <print>
#include <algorithm>

/**
 * Segment Tree:
 * A data structure that allows answering range queries and updating 
 * elements in O(log N) time.
 */

template <typename T>
class SegmentTree {
private:
    int n;
    std::vector<T> tree;
    T identity;
    std::function<T(T, T)> merge_fn;

    void build(const std::vector<T>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = merge_fn(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = merge_fn(tree[2 * node], tree[2 * node + 1]);
    }

    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return identity;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return merge_fn(query(2 * node, start, mid, l, r),
                        query(2 * node + 1, mid + 1, end, l, r));
    }

public:
    SegmentTree(const std::vector<T>& arr, T _identity, std::function<T(T, T)> _merge_fn)
        : n((int)arr.size()), identity(_identity), merge_fn(_merge_fn) {
        tree.assign(4 * n, identity);
        if (n > 0) build(arr, 1, 0, n - 1);
    }

    void update(int idx, T val) {
        update(1, 0, n - 1, idx, val);
    }

    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    std::println("--- Generic Segment Tree Demo ---");

    std::vector<int> data = {1, 3, -2, 8, 0, 7};
    
    // Sum Segment Tree
    SegmentTree<int> st_sum(data, 0, [](int a, int b) { return a + b; });
    std::println("Sum Range [0, 5]: {}", st_sum.query(0, 5)); // 17
    std::println("Sum Range [1, 3]: {}", st_sum.query(1, 3)); // 9
    
    st_sum.update(2, 5); // data[2] becomes 5
    std::println("After update(2, 5), Sum Range [1, 3]: {}", st_sum.query(1, 3)); // 16

    // Min Segment Tree
    SegmentTree<int> st_min(data, 1e9, [](int a, int b) { return std::min(a, b); });
    std::println("\nMin Range [0, 5]: {}", st_min.query(0, 5)); // -2
    st_min.update(2, 10);
    std::println("After update(2, 10), Min Range [0, 5]: {}", st_min.query(0, 5)); // 0

    std::println("\n--- Complexity Analysis ---");
    std::println("- Build: O(N)");
    std::println("- Update: O(log N)");
    std::println("- Query: O(log N)");
    std::println("- Space: O(N)");

    std::println("\n--- Interview Pitfalls ---");
    std::println("- Off-by-one errors in range boundaries.");
    std::println("- Not handling identity elements correctly (e.g., 0 for Sum, infinity for Min).");
    std::println("- Forgetting to allocate 4*N space for the tree vector.");
    std::println("- Redundant builds inside queries (ensure tree is pre-built).");

    return 0;
}
