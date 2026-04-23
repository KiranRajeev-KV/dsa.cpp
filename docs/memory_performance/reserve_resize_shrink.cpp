/*
Title: Reserve, Resize, and Shrink: Vector Capacity Management
Category: Memory & Performance
File: reserve_resize_shrink.cpp
C++ Standard: C++23
Difficulty: Beginner to Intermediate

Purpose:
To master memory management in std::vector. This file explains the critical 
differences between size and capacity, how to avoid expensive reallocations 
using reserve(), and how to release unused memory with shrink_to_fit().

Compile:
g++ -std=c++23 reserve_resize_shrink.cpp -o reserve_resize_shrink

Run:
./reserve_resize_shrink

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- size() vs. capacity()
- The cost of reallocation (Geometric growth)
- reserve() for performance optimization
- resize() for value-initialization
- shrink_to_fit() for memory footprint reduction
- clear() and its effect on capacity

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <print>

/**
 * @brief Utility to print vector stats.
 */
template <typename T>
void print_vec_stats(std::string_view label, const std::vector<T>& v) {
    std::println("{:<15} | Size: {:<3} | Capacity: {:<3}", label, v.size(), v.capacity());
}

/**
 * @brief Demonstrates the effect of reallocations during growth.
 */
void demonstrate_growth_cost() {
    std::println("\n--- 1. Vector Growth and Reallocations ---");
    
    std::vector<int> v;
    size_t last_cap = 0;

    std::println("Pushing 20 elements into a default vector:");
    for (int i = 0; i < 20; ++i) {
        v.push_back(i);
        if (v.capacity() != last_cap) {
            std::println("  [Reallocation] New Capacity: {}", v.capacity());
            last_cap = v.capacity();
        }
    }
    std::println("Note: Reallocations involve copying/moving all existing elements to a new buffer.");
}

/**
 * @brief Demonstrates the benefit of reserve().
 */
void demonstrate_reserve() {
    std::println("\n--- 2. Optimization with reserve() ---");
    
    std::vector<int> v;
    v.reserve(20); // Pre-allocate memory for 20 elements
    
    print_vec_stats("After reserve(20)", v);

    for (int i = 0; i < 20; ++i) {
        v.push_back(i);
    }
    print_vec_stats("After pushing 20", v);
    std::println("Note: Zero reallocations occurred during push_back.");
}

/**
 * @brief Demonstrates the difference between resize() and reserve().
 */
void demonstrate_resize() {
    std::println("\n--- 3. resize() vs reserve() ---");
    
    std::vector<int> v1;
    v1.reserve(10);
    print_vec_stats("reserve(10)", v1);
    // v1[0] = 5; // UNDEFINED BEHAVIOR: Size is still 0!

    std::vector<int> v2;
    v2.resize(10);
    print_vec_stats("resize(10)", v2);
    v2[0] = 5; // OK: Size is 10, elements are value-initialized (to 0)
    
    v2.resize(5); // Shrink size
    print_vec_stats("resize(5)", v2);
    std::println("  Capacity after resize(5): {} (Capacity does NOT decrease)", v2.capacity());
}

/**
 * @brief Demonstrates shrink_to_fit().
 */
void demonstrate_shrink() {
    std::println("\n--- 4. Releasing Memory with shrink_to_fit() ---");
    
    std::vector<int> v(1000, 42);
    print_vec_stats("Initial (1000)", v);
    
    v.clear();
    print_vec_stats("After clear()", v);
    std::println("  Capacity after clear(): {} (Memory is still held!)", v.capacity());

    v.shrink_to_fit();
    print_vec_stats("After shrink()", v);
    std::println("  Capacity after shrink_to_fit(): {} (Memory released)", v.capacity());
}

int main() {
    std::println("C++23 Memory & Performance: Vector Capacity Management");
    
    demonstrate_growth_cost();
    demonstrate_reserve();
    demonstrate_resize();
    demonstrate_shrink();

    return 0;
}

/*
Complexity Analysis:
- push_back: O(1) amortized. 
- reserve: O(N) if reallocation occurs (copies/moves N elements).
- resize: O(K) where K is the new size. May trigger O(N) reallocation.
- shrink_to_fit: O(N) as it creates a new buffer and moves elements.

Production Notes:
1. Always use reserve() if you know the approximate number of elements in advance.
2. Vector growth is typically geometric (factor of 1.5x or 2x) to maintain 
   O(1) amortized push_back.
3. shrink_to_fit() is a "non-binding request". Compilers usually honor it, 
   but it's not guaranteed by the standard to actually reduce capacity.
4. Using clear() does NOT deallocate memory. To truly free memory, use 
   shrink_to_fit() or the "swap-with-empty-vector" idiom in older C++.

Interview Pitfalls:
- Confusing size() (number of elements) with capacity() (allocated memory).
- Thinking that reserve(N) makes the vector contain N elements.
- Forgetting that resizing or pushing back into a vector invalidates 
  iterators if a reallocation occurs.
- Calling shrink_to_fit() in a loop (it's O(N) and very expensive).
*/
