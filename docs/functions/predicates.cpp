/*
Title: Predicates in Modern C++ Guide
Category: Functional Programming
File: predicates.cpp
C++ Standard: C++23
Difficulty: Beginner to Intermediate

Purpose:
Deep dive into predicates—functions or objects that return a boolean value. 
Explores their role in STL algorithms, ranges, and logical composition.

Compile:
g++ -std=c++23 predicates.cpp -o predicates

Run:
./predicates

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Unary and Binary Predicates
- STL Algorithms using Predicates (all_of, any_of, none_of)
- Partitioning and Searching
- Predicate Composition (std::not_fn)
- C++23: std::ranges::contains with predicates (indirectly)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <functional>
#include <ranges>
#include <print>

// 1. Simple Unary Predicate
bool is_even(int n) { return n % 2 == 0; }

// 2. Binary Predicate
bool is_shorter(const std::string& a, const std::string& b) {
    return a.length() < b.length();
}

void basic_predicates() {
    std::println("--- Basic Predicates ---");

    std::vector<int> nums = {1, 3, 5, 8, 10};

    // any_of: returns true if at least one element satisfies the predicate
    if (std::any_of(nums.begin(), nums.end(), is_even)) {
        std::println("The list contains at least one even number.");
    }

    // all_of: returns true if all elements satisfy the predicate
    if (std::all_of(nums.begin(), nums.end(), [](int x) { return x > 0; })) {
        std::println("All numbers are positive.");
    }
}

void logical_composition() {
    std::println("\n--- Predicate Composition ---");

    auto is_odd = std::not_fn(is_even); // C++17 negator
    
    std::vector<int> nums = {1, 2, 3, 4, 5};
    auto odd_count = std::count_if(nums.begin(), nums.end(), is_odd);
    std::println("Number of odd elements: {}", odd_count);
}

void range_predicates() {
    std::println("\n--- C++20/23 Ranges and Predicates ---");

    std::vector<int> nums = {10, 20, 30, 40, 50};

    // Using ranges versions of algorithms
    bool has_large = std::ranges::any_of(nums, [](int x) { return x > 35; });
    std::println("Has number > 35: {}", has_large);

    // C++23 ranges::contains (though it's for values, we use it for context)
    // For predicates, we still use any_of or find_if
    auto it = std::ranges::find_if(nums, [](int x) { return x % 7 == 0; });
    if (it == nums.end()) {
        std::println("No multiples of 7 found.");
    }
}

void advanced_partitioning() {
    std::println("\n--- Partitioning with Predicates ---");

    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Partition numbers into evens (first) and odds (second)
    std::ranges::partition(nums, is_even);
    
    std::print("Partitioned (Evens first): ");
    for (int n : nums) std::print("{} ", n);
    std::println();
}

/**
 * Interview Tips:
 * 1. Pure Functions: Predicates should ideally be "pure" (no side effects) 
 *    because algorithms might call them in any order or multiple times.
 * 2. Performance: Prefer lambdas for predicates to allow the compiler 
 *    to inline the logic.
 * 3. Standard Library: Familiarize yourself with <functional>'s built-in 
 *    predicates like std::equal_to, std::less, etc.
 */

int main() {
    try {
        basic_predicates();
        logical_composition();
        range_predicates();
        advanced_partitioning();
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
        return 1;
    }
    return 0;
}

/**
 * Complexity Analysis:
 * - Time: Predicates are O(1) in the examples above. The algorithms using 
 *   them (like find_if) are O(N).
 * - Space: O(1) for most predicates.
 */
