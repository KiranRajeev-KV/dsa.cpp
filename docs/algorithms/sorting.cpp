/*
Title: Sorting Algorithms Complete Guide
Category: Algorithms
File: sorting.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to sorting algorithms in the C++ Standard Library, 
covering classic STL algorithms and the modern C++20/23 Ranges equivalents.
Includes practical examples, complexity analysis, and performance considerations.

Compile:
g++ -std=c++23 sorting.cpp -o sorting

Run:
./sorting

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::sort vs std::stable_sort
- Partial and Nth element sorting
- std::ranges::sort and Projections (C++20/23)
- Custom comparators and lambda expressions
- Performance pitfalls and best practices

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <ranges>
#include <string>
#include <print>
#include <functional>
#include <random>

struct Employee {
    int id;
    std::string name;
    double salary;

    // For debugging/printing
    void print() const {
        std::println("ID: {:<3} | Name: {:<10} | Salary: {:.2f}", id, name, salary);
    }
};

void print_separator(std::string_view title) {
    std::println("\n--- {} ---", title);
}

int main() {
    // Basic Data
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6, 3, 0, 8, 7};

    // 1. Standard std::sort (Introductory)
    // Time Complexity: O(N log N)
    // Space Complexity: O(log N) (usually Introsort: quicksort + heap + insertion)
    print_separator("std::sort (Basic)");
    std::vector<int> vec1 = numbers;
    std::sort(vec1.begin(), vec1.end());
    for (int n : vec1) std::print("{} ", n);
    std::println("");

    // 2. std::stable_sort (Maintain relative order of equals)
    // Time Complexity: O(N log^2 N) or O(N log N) if extra memory is available
    // Useful when sorting by multiple criteria
    print_separator("std::stable_sort");
    std::vector<int> vec2 = numbers;
    std::stable_sort(vec2.begin(), vec2.end(), std::greater<int>());
    for (int n : vec2) std::print("{} ", n);
    std::println(" (Sorted descending)");

    // 3. std::partial_sort (Sort top K elements)
    // Time Complexity: O(N log K)
    print_separator("std::partial_sort (Top 3)");
    std::vector<int> vec3 = numbers;
    std::partial_sort(vec3.begin(), vec3.begin() + 3, vec3.end());
    for (int n : vec3) std::print("{} ", n);
    std::println(" (First 3 are sorted smallest, others in unspecified order)");

    // 4. std::nth_element (Find the K-th element and partition)
    // Time Complexity: O(N) on average
    print_separator("std::nth_element (Median Finding)");
    std::vector<int> vec4 = numbers;
    auto mid = vec4.begin() + vec4.size() / 2;
    std::nth_element(vec4.begin(), mid, vec4.end());
    std::println("Median element is: {}", *mid);
    std::println("Everything to left is <= median, right is >= median");

    // 5. Modern C++20/23: std::ranges::sort with Projections
    // Projections allow sorting by a member without writing complex lambdas
    print_separator("std::ranges::sort with Projections");
    std::vector<Employee> employees = {
        {101, "Alice", 75000.0},
        {102, "Bob", 50000.0},
        {103, "Charlie", 90000.0},
        {104, "David", 50000.0}
    };

    // Sort by salary using projection
    std::ranges::sort(employees, {}, &Employee::salary);
    std::println("Sorted by Salary (Ascending):");
    for (const auto& e : employees) e.print();

    // Stable sort by salary, then by ID (Secondary sort)
    // Note: To do this properly with stable_sort, you'd sort by ID first, then salary
    std::ranges::sort(employees, {}, &Employee::id); // Secondary key
    std::ranges::stable_sort(employees, {}, &Employee::salary); // Primary key
    std::println("\nStable Sorted by Salary (then ID):");
    for (const auto& e : employees) e.print();

    // 6. Sorting with custom comparator (C++20 ranges)
    print_separator("std::ranges::sort with Custom Lambda");
    std::ranges::sort(employees, [](const auto& a, const auto& b) {
        return a.name > b.name; // Reverse alphabetical
    });
    for (const auto& e : employees) e.print();

    // 7. checking if sorted
    print_separator("Checking Sort Status");
    bool is_sorted = std::ranges::is_sorted(vec1);
    std::println("Is vec1 sorted? {}", is_sorted);

    auto [min_it, max_it] = std::ranges::minmax_element(vec1);
    if (min_it != vec1.end()) {
        std::println("Min: {}, Max: {}", *min_it, *max_it);
    }

    /*
    --- INTERVIEW PITFALLS ---
    1. std::sort requires Random Access Iterators (works for vector, deque, array).
       It does NOT work for std::list or std::forward_list (use list::sort() instead).
    2. Stability: std::sort is NOT guaranteed to be stable. Use std::stable_sort 
       if the relative order of equal elements matters (critical for multi-pass sorting).
    3. Performance: For very small ranges, insertion sort (used internally) is faster.
       For finding top K, partial_sort is better than full sort.
       For finding median, nth_element is the most efficient (O(N)).

    --- PRODUCTION NOTES ---
    - Prefer std::ranges versions in C++20/23 as they are safer and support projections.
    - Custom comparators must satisfy Strict Weak Ordering.
      (e.g., if a < b is true, then b < a must be false). Fail to do so leads to UB.
    - Large objects: If moving objects is expensive, sort a vector of pointers or indices.
    */

    return 0;
}
