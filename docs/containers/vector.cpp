/*
Title: std::vector Complete Guide
Category: Sequence Containers
File: vector.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive exploration of std::vector, the most widely used STL container. 
Covers internal mechanics, memory management, C++23 enhancements, and performance optimization.

Compile:
g++ -std=c++23 vector.cpp -o vector

Run:
./vector

Key Topics:
- Dynamic Array Mechanics (Growth, Reallocation, Amortization)
- Iterator Invalidations and Reference Stability
- C++23 Features: std::ranges::to, constexpr vector
- Performance: reserve() vs resize(), shrink_to_fit()
- Interview Pitfalls: vector<bool>, vector vs list vs deque

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <print>
#include <ranges>

/**
 * @brief Demonstrates the vector<bool> proxy object trap.
 */
void vector_bool_trap() {
    std::println("\n--- The vector<bool> Trap ---");
    std::vector<bool> vb = {true, false, true};
    auto ref = vb[0]; // 'ref' is a proxy object
    ref = false;      // Modifies the bit in the vector
    std::println("Modified vb[0] via proxy: {}", vb[0]);
}

/**
 * @brief Demonstrates basic vector operations and C++23 print integration.
 */
void demonstrate_basics() {
    std::println("--- Basic Operations ---");
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // C++23 push_back and emplace_back
    vec.push_back(6);
    vec.emplace_back(7);

    std::println("Vector size: {}, capacity: {}", vec.size(), vec.capacity());
    
    // Modern iteration using ranges
    std::print("Elements: ");
    for (int n : vec) std::print("{} ", n);
    std::println("");
}

/**
 * @brief Deep dive into memory management and growth strategy.
 */
void memory_mechanics() {
    std::println("\n--- Memory Mechanics ---");
    std::vector<int> vec;
    
    size_t last_capacity = vec.capacity();
    std::println("Initial capacity: {}", last_capacity);

    for (int i = 0; i < 20; ++i) {
        vec.push_back(i);
        if (vec.capacity() != last_capacity) {
            std::println("Capacity changed from {} to {}", last_capacity, vec.capacity());
            last_capacity = vec.capacity();
        }
    }

    // Optimization: reserve
    std::vector<int> optimized_vec;
    optimized_vec.reserve(100);
    std::println("After reserve(100), capacity: {}", optimized_vec.capacity());
}

/**
 * @brief C++23 Features for std::vector
 */
void cpp23_features() {
    std::println("\n--- C++23 Features ---");
    
    // std::ranges::to - Converting a view to a vector
    auto doubled_view = std::views::iota(1, 11) | std::views::transform([](int n) { return n * 2; });
    auto vec = std::ranges::to<std::vector<int>>(doubled_view);
    
    std::println("Vector from ranges::to: {}", vec); // Requires C++23 print support for containers

    // constexpr std::vector
    // Note: constexpr vector is available in C++20, but refined in 23.
    // It can only be used in constant expressions if its lifetime is within the expression.
    static_assert([] {
        std::vector<int> v = {1, 2, 3};
        v.push_back(4);
        return v.size() == 4;
    }());
    std::println("static_assert passed for constexpr vector logic.");
}

/**
 * @brief Advanced: Custom Allocator hint and vector<bool>
 */
void advanced_topics() {
    std::println("\n--- Advanced Topics ---");
    
    // vector<bool> is a space-optimized specialization
    std::vector<bool> bool_vec = {true, false, true};
    std::println("vector<bool> size: {}", bool_vec.size());
    // Pitfall: &bool_vec[0] does not return a bool*
    // it returns a proxy object.
    
    // shrink_to_fit
    std::vector<int> large(1000, 42);
    large.clear();
    std::println("After clear(), capacity: {}", large.capacity());
    large.shrink_to_fit();
    std::println("After shrink_to_fit(), capacity: {}", large.capacity());
}

/**
 * @brief Complexity Analysis:
 * - Access: O(1)
 * - Insert/Delete at end: O(1) amortized
 * - Insert/Delete at middle/start: O(N)
 * - Space: O(N) but can have excess capacity.
 */
void print_complexity() {
    std::println("\n--- Complexity Analysis ---");
    std::println("- Random Access: O(1)");
    std::println("- Push Back: O(1) amortized");
    std::println("- Insert/Erase (middle): O(N)");
    std::println("- Memory: Contiguous, Cache-friendly.");
}

int main() {
    try {
        demonstrate_basics();
        vector_bool_trap();
        memory_mechanics();
        cpp23_features();
        advanced_topics();
        print_complexity();
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
        return 1;
    }
    return 0;
}
