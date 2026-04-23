/*
Title: std::multimap Complete Guide
Category: Associative Containers
File: multimap.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::multimap, an ordered associative container allowing multiple values per key.
Covers range-based lookups and specific multimap behaviors.

Compile:
g++ -std=c++23 multimap.cpp -o multimap

Run:
./multimap

Key Topics:
- Ordered Pairs with Duplicate Keys
- equal_range for multiple values
- No operator[] support
- C++23: std::ranges::to
- Production Use Cases: Dictionary with multiple definitions, grouping data

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <map>
#include <print>
#include <ranges>
#include <string>

/**
 * @brief Demonstrates basic multimap operations.
 */
void basic_operations() {
    std::println("--- Multimap Basics ---");
    std::multimap<std::string, int> mm;
    
    // Note: No operator[] because it would be ambiguous which value to return/update
    mm.insert({"Apple", 1});
    mm.insert({"Banana", 2});
    mm.insert({"Apple", 3});
    mm.insert({"Cherry", 4});
    
    std::println("Multimap contents: {}", mm);
}

/**
 * @brief Explains how to find all values associated with a single key.
 */
void range_lookup() {
    std::println("\n--- Range Lookup (equal_range) ---");
    std::multimap<std::string, int> mm = {
        {"A", 10}, {"B", 20}, {"A", 30}, {"A", 40}
    };
    
    std::print("Values for key 'A': ");
    auto [first, last] = mm.equal_range("A");
    for (auto it = first; it != last; ++it) {
        std::print("{} ", it->second);
    }
    std::println("");
    
    // count() returns the number of values for a key
    std::println("Count for 'A': {}", mm.count("A"));
}

/**
 * @brief C++23 features with multimap.
 */
void cpp23_multimap() {
    std::println("\n--- C++23 and Multimap ---");
    
    auto pairs = std::views::iota(1, 6) 
               | std::views::transform([](int n) { 
                   return std::make_pair(n % 2, n); 
                 });
                 
    auto mm = std::ranges::to<std::multimap<int, int>>(pairs);
    std::println("Multimap from transformed range: {}", mm);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Missing operator[]: This is the most common confusion for beginners moving from map to multimap.");
    std::println("2. Value ordering: Values for the same key are stored in the order they were inserted (since C++11).");
    std::println("3. Erase: `mm.erase(key)` removes ALL entries for that key. Use an iterator to remove a specific one.");
}

/**
 * @brief Complexity:
 * - Insert: O(log N)
 * - Find: O(log N)
 * - count(key): O(log N + K) where K is number of values for key.
 */
int main() {
    basic_operations();
    range_lookup();
    cpp23_multimap();
    interview_notes();
    return 0;
}
