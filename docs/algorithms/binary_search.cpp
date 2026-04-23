/*
Title: Binary Search Algorithms Complete Guide
Category: Algorithms
File: binary_search.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A deep dive into binary search algorithms in the C++ Standard Library. 
Covers finding bounds, searching in sorted ranges, and efficiency analysis.

Compile:
g++ -std=c++23 binary_search.cpp -o binary_search

Run:
./binary_search

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::binary_search (Existence check)
- std::lower_bound (First element >= value)
- std::upper_bound (First element > value)
- std::equal_range (Combination of lower and upper)
- std::ranges equivalents (C++20/23)
- Custom comparators for complex objects

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <ranges>
#include <string>
#include <print>

void print_separator(std::string_view title) {
    std::println("\n--- {} ---", title);
}

int main() {
    // Binary search requires a SORTED sequence
    std::vector<int> sorted_nums = {10, 20, 30, 30, 30, 40, 50, 60};

    // 1. std::binary_search (Returns bool)
    // Complexity: O(log N)
    print_separator("std::binary_search");
    bool found_30 = std::binary_search(sorted_nums.begin(), sorted_nums.end(), 30);
    bool found_35 = std::binary_search(sorted_nums.begin(), sorted_nums.end(), 35);
    std::println("Is 30 present? {}", found_30);
    std::println("Is 35 present? {}", found_35);

    // 2. std::lower_bound
    // Returns iterator to first element NOT LESS than value (i.e., >= value)
    print_separator("std::lower_bound");
    auto it_lb = std::lower_bound(sorted_nums.begin(), sorted_nums.end(), 30);
    if (it_lb != sorted_nums.end()) {
        std::println("Lower bound of 30: {} at index {}", *it_lb, std::distance(sorted_nums.begin(), it_lb));
    }

    // 3. std::upper_bound
    // Returns iterator to first element GREATER than value (i.e., > value)
    print_separator("std::upper_bound");
    auto it_ub = std::upper_bound(sorted_nums.begin(), sorted_nums.end(), 30);
    if (it_ub != sorted_nums.end()) {
        std::println("Upper bound of 30: {} at index {}", *it_ub, std::distance(sorted_nums.begin(), it_ub));
    }

    // 4. Counting occurrences in O(log N)
    print_separator("Counting Occurrences");
    auto count = std::distance(it_lb, it_ub);
    std::println("Number 30 appears {} times", count);

    // 5. std::equal_range
    // Returns a pair of [lower_bound, upper_bound]
    print_separator("std::equal_range");
    auto [first, last] = std::equal_range(sorted_nums.begin(), sorted_nums.end(), 30);
    std::println("equal_range of 30 found {} elements", std::distance(first, last));

    // 6. C++20 Ranges versions
    print_separator("std::ranges::binary_search / lower_bound");
    bool found_ranges = std::ranges::binary_search(sorted_nums, 50);
    auto it_ranges = std::ranges::lower_bound(sorted_nums, 45); // First element >= 45
    std::println("Ranges check for 50: {}", found_ranges);
    if (it_ranges != sorted_nums.end()) {
        std::println("First element >= 45: {}", *it_ranges);
    }

    // 7. Binary Search on Custom Objects (Projection)
    print_separator("Binary Search with Projections");
    struct Task {
        int priority;
        std::string name;
    };
    std::vector<Task> tasks = {
        {1, "Fix minor bug"},
        {2, "Document API"},
        {5, "Refactor core"},
        {10, "Critical security patch"}
    };

    // Note: Data must be sorted by the priority for this to work
    bool has_prio_5 = std::ranges::binary_search(tasks, 5, {}, &Task::priority);
    std::println("Has task with priority 5? {}", has_prio_5);

    /*
    --- INTERVIEW PITFALLS ---
    1. Data must be SORTED: If the range is not sorted, behavior is undefined.
    2. Random Access Iterators: For vectors/arrays, binary search is O(log N).
       For std::list, it is O(N) because of iterator incrementing, even though 
       it minimizes comparisons.
    3. lower_bound vs upper_bound: 
       - lower_bound: >= value
       - upper_bound: > value
       - If value is NOT in range, both return the position where it COULD be inserted.
    4. C++23 Ranges: Prefer `std::ranges::lower_bound` as it supports projections 
       and works more cleanly with modern C++.

    --- PRODUCTION NOTES ---
    - If you need both bounds, use `std::equal_range` to avoid two binary searches.
    - When searching in large data, cache locality of binary search is worse than 
      linear search for small ranges, but O(log N) wins for large N.
    - Floating point: Binary search works but be careful with precision if your 
      comparator isn't robust.
    */

    return 0;
}
