/*
Title: std::flat_map Complete Guide (C++23)
Category: Associative Containers (Adapters)
File: flat_map_cpp23.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
A comprehensive guide to std::flat_map, a C++23 container adapter that provides 
a map-like interface using sorted contiguous memory (usually two vectors).

Compile:
g++ -std=c++23 flat_map_cpp23.cpp -o flat_map_cpp23

Run:
./flat_map_cpp23

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Sorted Vector-based mapping
- Cache-friendly O(log N) lookups
- Performance trade-offs: Fast search, Slow insertion
- C++23: Container adapters for associative logic
- Difference between flat_map and map/unordered_map

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <string>

// Note: std::flat_map is a C++23 feature.
// As of late 2023/early 2024, some compilers might still have it in <experimental/flat_map>
// or it might not be fully implemented. This code follows the C++23 standard.
#if __has_include(<flat_map>)
#include <flat_map>
#define HAS_FLAT_MAP 1
#else
#define HAS_FLAT_MAP 0
#endif

void demonstrate_flat_map() {
    std::println("--- flat_map Basics ---");
#if HAS_FLAT_MAP
    std::flat_map<std::string, int> fm;
    
    fm["Alice"] = 30;
    fm["Bob"] = 25;
    fm["Charlie"] = 35;
    
    std::println("flat_map size: {}", fm.size());
    std::println("Bob's age: {}", fm.at("Bob"));
    
    // Iteration is always sorted by key
    for (const auto& [name, age] : fm) {
        std::println("{}: {}", name, age);
    }
#else
    std::println("std::flat_map is not yet supported by this compiler.");
    std::println("However, here is the conceptual usage:");
    std::println("std::flat_map<Key, Value> uses sorted vectors internally.");
#endif
}

/**
 * @brief Performance characteristics comparison.
 */
void performance_notes() {
    std::println("\n--- Performance & Design ---");
    std::println("1. Memory Layout: Uses two vectors (one for keys, one for values) or one vector of pairs.");
    std::println("2. Search: O(log N) via binary search. Much more cache-friendly than std::map.");
    std::println("3. Insertion/Deletion: O(N) because it must maintain sorted order in a vector.");
    std::println("4. Use Case: When you have a dataset that is built once (or rarely modified) and searched many times.");
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. flat_map vs map: map is a tree (O(log N) insert/search, bad cache). flat_map is sorted vector (O(N) insert, O(log N) search, great cache).");
    std::println("2. flat_map vs unordered_map: unordered_map is O(1) average but higher memory and bad cache locality for iteration. flat_map is better for small datasets.");
    std::println("3. Stability: Iterators are invalidated on any insertion/deletion (unlike std::map).");
}

int main() {
    demonstrate_flat_map();
    performance_notes();
    interview_notes();
    return 0;
}
