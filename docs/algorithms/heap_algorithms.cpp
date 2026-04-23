/*
Title: Heap Algorithms Complete Guide
Category: Algorithms
File: heap_algorithms.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to STL heap algorithms. Heaps are the foundation of 
priority queues and heap sort. This file covers how to transform sequences 
into heaps and maintain the heap property.

Compile:
g++ -std=c++23 heap_algorithms.cpp -o heap_algorithms

Run:
./heap_algorithms

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::make_heap (Building a heap)
- std::push_heap & std::pop_heap
- std::sort_heap (In-place sort)
- std::is_heap & std::is_heap_until
- std::ranges equivalents (C++20/23)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <ranges>
#include <print>

void print_separator(std::string_view title) {
    std::println("\n--- {} ---", title);
}

void print_vec(const std::vector<int>& v, std::string_view label) {
    std::print("{:<15}: ", label);
    for (int n : v) std::print("{} ", n);
    std::println("");
}

int main() {
    // 1. make_heap
    // Transforms a range into a Max-Heap (by default)
    // Complexity: O(N)
    print_separator("std::make_heap");
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    print_vec(data, "Original");

    std::make_heap(data.begin(), data.end());
    print_vec(data, "After make_heap");
    std::println("Is it a max-heap? {}", std::is_heap(data.begin(), data.end()));

    // 2. push_heap
    // When you add an element to the end of the container, 
    // push_heap restores the heap property.
    // Complexity: O(log N)
    print_separator("std::push_heap");
    data.push_back(7); // Add to end
    print_vec(data, "Before push_heap");
    std::push_heap(data.begin(), data.end());
    print_vec(data, "After push_heap");

    // 3. pop_heap
    // Swaps the max element (at front) with the last element,
    // then restores the heap property for the remaining range.
    // Note: It doesn't actually remove the element from the container!
    // Complexity: O(log N)
    print_separator("std::pop_heap");
    std::pop_heap(data.begin(), data.end());
    int max_val = data.back();
    data.pop_back(); // Now remove it
    std::println("Popped max value: {}", max_val);
    print_vec(data, "After pop_heap");

    // 4. sort_heap
    // Converts a heap into a sorted range in-place.
    // Complexity: O(N log N)
    print_separator("std::sort_heap");
    std::sort_heap(data.begin(), data.end());
    print_vec(data, "After sort_heap");
    std::println("Is it still a heap? {}", std::is_heap(data.begin(), data.end()));

    // 5. Ranges version (C++20)
    print_separator("std::ranges::make_heap");
    std::vector<int> r_data = {10, 5, 20, 15};
    std::ranges::make_heap(r_data, std::greater<int>()); // Min-Heap
    print_vec(r_data, "Min-Heap");
    std::println("Top element (min): {}", r_data.front());

    // 6. is_heap_until
    print_separator("std::is_heap_until");
    std::vector<int> partial_heap = {10, 8, 7, 1, 15, 20}; // Broken after 1
    auto it = std::is_heap_until(partial_heap.begin(), partial_heap.end());
    std::println("Heap property valid for first {} elements.", std::distance(partial_heap.begin(), it));

    /*
    --- INTERVIEW PITFALLS ---
    1. Forgetting push_heap: After `vec.push_back(x)`, the heap property is broken. 
       You MUST call `std::push_heap(vec.begin(), vec.end())`.
    2. pop_heap doesn't remove: `pop_heap` only moves the max element to the back. 
       You MUST call `vec.pop_back()` to actually remove it.
    3. Custom Comparators: If you use a custom comparator in `make_heap`, 
       you MUST use the same comparator in `push_heap`, `pop_heap`, etc.
    4. max-heap vs min-heap: 
       - `std::less<T>` (default) -> Max-Heap (largest at front).
       - `std::greater<T>` -> Min-Heap (smallest at front).

    --- PRODUCTION NOTES ---
    - If you need a persistent heap, prefer `std::priority_queue` (which uses 
      these algorithms internally) for a safer interface.
    - Use heap algorithms directly when you need more control, such as 
      accessing elements in the middle of the container or using 
      `sort_heap` to avoid extra allocations.
    - Cache locality: Heaps are generally cache-friendly as they use 
      contiguous memory (vector/array).
    */

    return 0;
}
