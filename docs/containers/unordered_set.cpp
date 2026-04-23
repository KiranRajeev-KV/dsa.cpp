/*
Title: std::unordered_set Complete Guide
Category: Associative Containers
File: unordered_set.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::unordered_set, a hash-table based associative container.
Covers hashing mechanics, load factors, collision handling, and C++23 features.

Compile:
g++ -std=c++23 unordered_set.cpp -o unordered_set

Run:
./unordered_set

Key Topics:
- Hash Table Mechanics (Buckets, Chaining)
- Average O(1) vs Worst Case O(N)
- Load Factor and Rehashing
- Custom Hash Functions
- C++23: std::ranges::to, ranges::contains

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <unordered_set>
#include <print>
#include <ranges>
#include <string>

/**
 * @brief Demonstrates basic unordered_set operations.
 */
void basic_operations() {
    std::println("--- Unordered Set Basics ---");
    std::unordered_set<int> us = {5, 2, 8, 1, 9, 2}; // Duplicates ignored, order is arbitrary
    
    std::println("Unordered Set elements: {}", us);
    
    // Efficiency check
    std::println("Bucket count: {}", us.bucket_count());
    std::println("Load factor: {:.2f}", us.load_factor());
}

/**
 * @brief Shows how to use custom types with unordered_set by providing hash and equality.
 */
struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Custom hash function
struct PointHash {
    std::size_t operator()(const Point& p) const noexcept {
        return std::hash<int>{}(p.x) ^ (std::hash<int>{}(p.y) << 1);
    }
};

void custom_types() {
    std::println("\n--- Custom Types & Hashing ---");
    std::unordered_set<Point, PointHash> points;
    points.insert({1, 2});
    points.insert({3, 4});
    
    std::println("Set contains {} points.", points.size());
}

/**
 * @brief Explains rehashing and reservation.
 */
void rehashing_and_performance() {
    std::println("\n--- Rehashing & Performance ---");
    std::unordered_set<int> us;
    
    std::println("Initial bucket count: {}", us.bucket_count());
    
    // Reserve to prevent multiple rehashes
    us.reserve(100);
    std::println("Bucket count after reserve(100): {}", us.bucket_count());
    
    for(int i=0; i<50; ++i) us.insert(i);
    std::println("Load factor with 50 elements: {:.2f}", us.load_factor());
}

/**
 * @brief C++23 features with unordered_set.
 */
void cpp23_unordered_set() {
    std::println("\n--- C++23 and Unordered Set ---");
    
    std::unordered_set<std::string> words = {"apple", "banana", "cherry"};
    
    // C++20/23 contains()
    if (words.contains("apple")) {
        std::println("Found apple!");
    }
    
    auto range = std::views::iota(1, 6) | std::views::transform([](int n){ return n * n; });
    auto us = std::ranges::to<std::unordered_set<int>>(range);
    
    std::println("Set from squares: {}", us);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Worst Case: O(N) if many collisions occur (all elements in one bucket). This can be a security vulnerability (Hash Flood Attack).");
    std::println("2. Iterator Invalidation: Rehashing invalidates all iterators, but NOT references to elements.");
    std::println("3. Memory: More memory than std::set due to bucket array and chaining pointers.");
    std::println("4. Order: If you need sorted output, use std::set. If order doesn't matter, unordered_set is usually faster.");
}

/**
 * @brief Complexity:
 * - Average: O(1) for Insert/Delete/Find
 * - Worst: O(N)
 * - Space: O(N)
 */
int main() {
    basic_operations();
    custom_types();
    rehashing_and_performance();
    cpp23_unordered_set();
    interview_notes();
    return 0;
}
