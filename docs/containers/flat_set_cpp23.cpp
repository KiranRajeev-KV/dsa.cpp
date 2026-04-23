/*
Title: std::flat_set Complete Guide (C++23)
Category: Associative Containers (Adapters)
File: flat_set_cpp23.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
A comprehensive guide to std::flat_set, a C++23 container adapter that provides 
a set-like interface using a sorted contiguous container (usually std::vector).

Compile:
g++ -std=c++23 flat_set_cpp23.cpp -o flat_set_cpp23

Run:
./flat_set_cpp23

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Sorted Vector-based set logic
- Cache-friendly lookups
- O(N) Insertion vs O(log N) Search
- C++23 flat_set mechanics
- Production use cases for small/static datasets

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <vector>

#if __has_include(<flat_set>)
#include <flat_set>
#define HAS_FLAT_SET 1
#else
#define HAS_FLAT_SET 0
#endif

void demonstrate_flat_set() {
    std::println("--- flat_set Basics ---");
#if HAS_FLAT_SET
    std::flat_set<int> fs = {5, 2, 8, 1, 9, 2}; // Duplicates ignored
    
    std::println("flat_set size: {}", fs.size());
    
    // Search is binary search
    if (fs.contains(5)) {
        std::println("Found 5!");
    }
    
    // Elements are stored in sorted order
    std::print("Elements: ");
    for (int n : fs) std::print("{} ", n);
    std::println("");
#else
    std::println("std::flat_set is not yet supported by this compiler.");
    std::println("Conceptual usage: std::flat_set<T> keeps elements in a sorted vector.");
#endif
}

/**
 * @brief Explains why flat_set was added to C++23.
 */
void design_goals() {
    std::println("\n--- Design Goals ---");
    std::println("1. Cache Locality: std::set is node-based, causing cache misses. flat_set is contiguous.");
    std::println("2. Memory Efficiency: No per-node overhead (pointers, colors).");
    std::println("3. Performance: For small datasets, binary search on a vector often beats tree traversal due to modern CPU architectures.");
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Invalidation: Unlike std::set, adding/removing elements invalidates all iterators.");
    std::println("2. Insertion Cost: Inserting into the middle of a flat_set is O(N). Avoid if you have frequent insertions.");
    std::println("3. Best Use Case: Configuration sets, small lookups, or data that is sorted once and queried often.");
}

int main() {
    demonstrate_flat_set();
    design_goals();
    interview_notes();
    return 0;
}
