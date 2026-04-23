/*
Title: std::multiset Complete Guide
Category: Associative Containers
File: multiset.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::multiset, an ordered associative container that allows duplicate elements.
Covers bounds checking, counting, and iterator ranges.

Compile:
g++ -std=c++23 multiset.cpp -o multiset

Run:
./multiset

Key Topics:
- Red-Black Tree Mechanics with duplicates
- lower_bound, upper_bound, equal_range
- Erase mechanics (single vs all duplicates)
- C++23: std::ranges::to
- Production Use Cases: Sliding window minimum/maximum (e.g., in competitive programming)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <set>
#include <print>
#include <ranges>

/**
 * @brief Demonstrates basic multiset operations and duplicate handling.
 */
void basic_operations() {
    std::println("--- Multiset Basics ---");
    std::multiset<int> ms = {5, 2, 8, 1, 9, 2, 2, 5};
    
    std::println("Multiset elements (sorted, with duplicates): {}", ms);
    
    // Count occurrences of a specific element (O(log N + count))
    std::println("Count of 2: {}", ms.count(2));
}

/**
 * @brief Explains erase mechanics which can be tricky with duplicates.
 */
void erase_mechanics() {
    std::println("\n--- Erase Mechanics ---");
    std::multiset<int> ms = {10, 20, 20, 20, 30};
    
    std::println("Original: {}", ms);
    
    // Pitfall: ms.erase(value) removes ALL occurrences of value
    ms.erase(20);
    std::println("After ms.erase(20): {}", ms);
    
    // To remove only ONE occurrence, use an iterator
    ms = {10, 20, 20, 20, 30};
    auto it = ms.find(20); // finds the first occurrence
    if (it != ms.end()) {
        ms.erase(it);
    }
    std::println("After erasing one occurrence of 20: {}", ms);
}

/**
 * @brief Demonstrates finding ranges of duplicate elements.
 */
void range_queries() {
    std::println("\n--- Range Queries (equal_range) ---");
    std::multiset<int> ms = {1, 3, 3, 3, 5, 7};
    
    auto [first, last] = ms.equal_range(3);
    
    std::print("Elements matching 3: ");
    for (auto it = first; it != last; ++it) {
        std::print("{} ", *it);
    }
    std::println("");
}

/**
 * @brief C++23 features with multiset.
 */
void cpp23_multiset() {
    std::println("\n--- C++23 and Multiset ---");
    
    auto range = std::views::iota(1, 10) 
               | std::views::transform([](int n) { return n % 3; }); // generates duplicates
               
    auto ms = std::ranges::to<std::multiset<int>>(range);
    std::println("Multiset from transforming range: {}", ms);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Erasing one duplicate: Remember `ms.erase(ms.find(val))` instead of `ms.erase(val)`. This is a very common bug in sliding window problems.");
    std::println("2. equal_range: Highly useful for finding the contiguous block of duplicates in the tree.");
    std::println("3. Performance: count(x) takes O(log N + C) where C is the number of duplicates. If C is large, it can be slow.");
}

/**
 * @brief Complexity:
 * - Insert/Delete/Find: O(log N)
 * - Count: O(log N + count)
 * - Space: O(N)
 */
int main() {
    basic_operations();
    erase_mechanics();
    range_queries();
    cpp23_multiset();
    interview_notes();
    return 0;
}
