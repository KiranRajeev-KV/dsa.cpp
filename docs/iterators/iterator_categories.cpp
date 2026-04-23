/*
Title: Iterator Categories and Concepts Guide
Category: Iterators
File: iterator_categories.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Deep dive into the hierarchy of iterator categories and modern C++20/23 concepts.
Explains why certain algorithms work with some containers and not others.

Compile:
g++ -std=c++23 iterator_categories.cpp -o iterator_categories

Run:
./iterator_categories

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Iterator Category Hierarchy (Input to Contiguous)
- C++20 Iterator Concepts (std::forward_iterator, etc.)
- Tag Dispatching vs. Concepts
- std::advance, std::distance, std::next, std::prev
- Performance implications (O(1) vs O(N) operations)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <list>
#include <forward_list>
#include <iterator>
#include <algorithm>
#include <print>
#include <vector>

/**
 * 1. ITERATOR CONCEPTS (C++20/23)
 * Demonstrates how to check iterator capabilities at compile-time.
 */
template <typename It>
void identify_iterator(It it) {
    (void)it; // Suppress unused warning
    if constexpr (std::contiguous_iterator<It>) {
        std::println("Category: Contiguous Iterator (e.g., std::vector, std::array)");
    } else if constexpr (std::random_access_iterator<It>) {
        std::println("Category: Random Access Iterator (e.g., std::deque)");
    } else if constexpr (std::bidirectional_iterator<It>) {
        std::println("Category: Bidirectional Iterator (e.g., std::list)");
    } else if constexpr (std::forward_iterator<It>) {
        std::println("Category: Forward Iterator (e.g., std::forward_list)");
    } else if constexpr (std::input_iterator<It>) {
        std::println("Category: Input Iterator (e.g., std::istream_iterator)");
    } else {
        std::println("Category: Unknown/Output Iterator");
    }
}

/**
 * 2. PERFORMANCE DIFFERENCES
 * Demonstrates std::advance and std::distance.
 * Note: std::distance is O(1) for Random Access, O(N) for others.
 */
void demo_iterator_operations() {
    std::println("--- 2. Iterator Operations Performance ---");
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::list<int> lst = {1, 2, 3, 4, 5};

    auto v_it = vec.begin();
    auto l_it = lst.begin();

    // std::advance(it, n)
    std::advance(v_it, 3); // O(1) for vector
    std::advance(l_it, 3); // O(N) for list (traverses 3 nodes)

    std::println("Vector advanced to: {}", *v_it);
    std::println("List advanced to: {}", *l_it);

    // std::distance(first, last)
    auto dist_v = std::distance(vec.begin(), v_it); // O(1)
    auto dist_l = std::distance(lst.begin(), l_it); // O(N)

    std::println("Vector distance: {}", dist_v);
    std::println("List distance: {}\n", dist_l);
}

/**
 * 3. WHY CATEGORIES MATTER FOR ALGORITHMS
 * std::sort requires Random Access Iterators.
 * std::list has its own .sort() because it only provides Bidirectional Iterators.
 */
void demo_algorithm_constraints() {
    std::println("--- 3. Algorithm Constraints ---");
    
    std::vector<int> v = {5, 2, 9};
    std::list<int> l = {5, 2, 9};

    // Works: std::vector has random access
    std::sort(v.begin(), v.end()); 
    
    // std::sort(l.begin(), l.end()); // COMPILE ERROR: list is not random access
    l.sort(); // List provides its own sort implementation

    std::println("Sorted vector: {}, {}, {}", v[0], v[1], v[2]);
    std::println("Sorted list: {}, {}, {}\n", *l.begin(), *std::next(l.begin()), *std::next(l.begin(), 2));
}

/**
 * 4. C++23 std::next / std::prev with Concepts
 */
void demo_next_prev() {
    std::println("--- 4. Next and Prev ---");
    std::list<int> l = {10, 20, 30};
    
    auto it = l.begin();
    auto next_it = std::next(it, 2); // Get iterator to 3rd element
    auto prev_it = std::prev(next_it); // Get iterator back to 2nd element
    
    std::println("Original: {}, Next(2): {}, Prev: {}\n", *it, *next_it, *prev_it);
}

int main() {
    std::println("C++23 Iterator Categories Exploration\n");

    std::println("--- 1. Category Identification ---");
    identify_iterator(std::vector<int>{}.begin());
    identify_iterator(std::list<int>{}.begin());
    identify_iterator(std::forward_list<int>{}.begin());
    std::println("");

    demo_iterator_operations();
    demo_algorithm_constraints();
    demo_next_prev();

    std::println("--- Production Engineering Notes ---");
    std::println("- Use `std::distance` carefully in loops if the iterator is not RandomAccess (O(N^2) trap).");
    std::println("- Prefer `std::next` and `std::prev` over manual `it++` for readability.");
    std::println("- Use C++20 concepts (`std::random_access_iterator<T>`) to constrain templates for better error messages.");
    
    return 0;
}
