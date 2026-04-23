/*
Title: Policy-Based Data Structures (PBDS) in C++23
Category: Competitive Programming
File: policy_based_ds.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
Demonstrates the use of GNU Policy-Based Data Structures, specifically 
the 'ordered_set' (Tree-based container). It allows O(log N) operations 
to find the K-th element and the number of elements smaller than X.

Compile:
g++ -std=c++23 policy_based_ds.cpp -o policy_based_ds

Run:
./policy_based_ds

Key Topics:
- __gnu_pbds library
- tree_policy and tree structure
- order_of_key (Number of elements strictly smaller than k)
- find_by_order (K-th element in the set)
- Handling duplicate elements using pairs

Authoring Rule:
This file must be independently runnable and production-grade.
Note: PBDS is a GCC extension and may not work on all compilers (e.g., MSVC).
*/

#include <iostream>
#include <vector>
#include <print>

// PBDS Headers
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

/**
 * ordered_set:
 * A set that supports two additional operations:
 * 1. find_by_order(k): Returns an iterator to the k-th smallest element (0-indexed).
 * 2. order_of_key(k): Returns the number of elements strictly smaller than k.
 * 
 * Time Complexity: O(log N) for both.
 */
typedef tree<
    int,
    null_type,
    std::less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_set;

/**
 * Handling Duplicates:
 * By default, ordered_set acts like a std::set (unique elements).
 * To store duplicates, use std::pair<int, int> where the second element 
 * is a unique identifier (like index or counter).
 */
typedef tree<
    std::pair<int, int>,
    null_type,
    std::less<std::pair<int, int>>,
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_multiset;

int main() {
    std::println("--- Policy-Based Data Structures (PBDS) Demo ---");

    ordered_set os;
    os.insert(1);
    os.insert(10);
    os.insert(2);
    os.insert(5);

    // Elements are sorted: {1, 2, 5, 10}
    std::println("Set size: {}", (int)os.size());

    // find_by_order(k) returns iterator
    std::println("0-th element: {}", *os.find_by_order(0)); // 1
    std::println("2-nd element: {}", *os.find_by_order(2)); // 5

    // order_of_key(k) returns count
    std::println("Number of elements smaller than 6: {}", (int)os.order_of_key(6)); // 3
    std::println("Number of elements smaller than 1: {}", (int)os.order_of_key(1)); // 0

    std::println("\n--- Handling Duplicates with ordered_multiset ---");
    ordered_multiset oms;
    int timer = 0;
    
    auto add = [&](int val) {
        oms.insert({val, timer++});
    };

    add(5);
    add(2);
    add(5);
    add(8);

    // Elements: {(2, 1), (5, 0), (5, 2), (8, 3)}
    std::println("Multiset size: {}", (int)oms.size());
    std::println("1-st element: {}", oms.find_by_order(1)->first); // 5
    std::println("2-nd element: {}", oms.find_by_order(2)->first); // 5

    std::println("\n--- Complexity Analysis ---");
    std::println("- insert/erase: O(log N)");
    std::println("- find_by_order: O(log N)");
    std::println("- order_of_key: O(log N)");

    std::println("\n--- Interview Pitfalls ---");
    std::println("- Portability: PBDS is a GCC extension. It won't work on Clang/MSVC without extra headers.");
    std::println("- Iterator validation: find_by_order returns end() if index is out of bounds.");
    std::println("- Multiset behavior: null_type with std::less_equal is buggy in PBDS; use pairs instead.");

    return 0;
}
