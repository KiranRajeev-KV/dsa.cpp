/*
Title: std::array Complete Guide
Category: Sequence Containers
File: array.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::array, the modern, safer, and zero-overhead alternative 
to C-style arrays. Covers stack allocation, constexpr usage, and C++23 enhancements.

Compile:
g++ -std=c++23 array.cpp -o array

Run:
./array

Key Topics:
- Fixed-size contiguous memory
- Zero overhead abstraction
- Stack vs Heap allocation
- constexpr array and template metaprogramming
- C++23 multidimensional support considerations (std::mdspan related)
- tuple-like interfaces (std::get)

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <array>
#include <print>

/**
 * @brief Demonstrates basic array operations and zero-overhead principle.
 */
void basic_operations() {
    std::println("--- Array Basics ---");
    // Class Template Argument Deduction (CTAD) figures out type and size (int, 5)
    std::array arr = {1, 2, 3, 4, 5}; 
    
    std::println("Array size: {}", arr.size());
    std::println("Array elements: {}", arr);
    
    // Safe access
    try {
        arr.at(10) = 42; // Throws std::out_of_range
    } catch(const std::out_of_range& e) {
        std::println("Caught bounds error: {}", e.what());
    }
}

/**
 * @brief Shows constexpr usage and compile-time evaluations.
 */
constexpr auto generate_squares() {
    std::array<int, 10> sq{};
    for (int i = 0; i < 10; ++i) {
        sq[i] = i * i;
    }
    return sq;
}

void constexpr_array() {
    std::println("\n--- Constexpr Array ---");
    constexpr auto squares = generate_squares();
    
    std::println("Constexpr array elements: {}", squares);
    static_assert(squares[5] == 25, "Compile-time validation failed");
}

/**
 * @brief Tuple-like interface of std::array.
 */
void tuple_interface() {
    std::println("\n--- Tuple Interface ---");
    std::array<double, 3> point = {1.5, 2.5, 3.5};
    
    // Access via std::get
    double x = std::get<0>(point);
    double y = std::get<1>(point);
    double z = std::get<2>(point);
    
    std::println("Point: ({}, {}, {})", x, y, z);
    
    // Structured binding
    auto [cx, cy, cz] = point;
    std::println("Structured Binding: cx={}, cy={}, cz={}", cx, cy, cz);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Stack Overflow: std::array allocates on the stack by default. Large sizes (e.g., std::array<int, 1000000>) WILL cause a stack overflow. Use vector or unique_ptr<array> instead.");
    std::println("2. Passing to functions: Pass by const reference `const std::array<T, N>&` to avoid deep copying the entire array.");
    std::println("3. Uninitialized state: `std::array<int, 5> a;` contains garbage. Use `std::array<int, 5> a{{}};` to zero-initialize.");
    std::println("4. Size is part of the type: std::array<int, 5> and std::array<int, 6> are DIFFERENT types.");
}

/**
 * @brief Complexity:
 * - Access: O(1)
 * - Size: O(1)
 * - Space: O(N) on stack (usually)
 */
int main() {
    basic_operations();
    constexpr_array();
    tuple_interface();
    interview_notes();
    return 0;
}
