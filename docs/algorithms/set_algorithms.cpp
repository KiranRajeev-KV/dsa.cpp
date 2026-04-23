/*
Title: Set Algorithms Complete Guide
Category: Algorithms
File: set_algorithms.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to set operations on sorted ranges in the C++ STL.
Covers union, intersection, difference, and inclusion.

Compile:
g++ -std=c++23 set_algorithms.cpp -o set_algorithms

Run:
./set_algorithms

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::set_union
- std::set_intersection
- std::set_difference
- std::set_symmetric_difference
- std::includes
- std::ranges equivalents (C++20/23)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <iterator>
#include <ranges>
#include <print>

void print_separator(std::string_view title) {
    std::println("\n--- {} ---", title);
}

void print_vec(const std::vector<int>& v, std::string_view label) {
    std::print("{:<25}: ", label);
    for (int n : v) std::print("{} ", n);
    std::println("");
}

int main() {
    // Set algorithms REQUIRE sorted ranges
    std::vector<int> set1 = {1, 2, 3, 4, 5};
    std::vector<int> set2 = {3, 4, 5, 6, 7};

    print_vec(set1, "Set 1");
    print_vec(set2, "Set 2");

    // 1. std::set_union
    // Result contains elements present in either set.
    // Complexity: O(N + M)
    print_separator("std::set_union");
    std::vector<int> v_union;
    std::set_union(set1.begin(), set1.end(), 
                   set2.begin(), set2.end(), 
                   std::back_inserter(v_union));
    print_vec(v_union, "Union (1 | 2)");

    // 2. std::set_intersection
    // Result contains elements present in both sets.
    print_separator("std::set_intersection");
    std::vector<int> v_inter;
    std::set_intersection(set1.begin(), set1.end(), 
                          set2.begin(), set2.end(), 
                          std::back_inserter(v_inter));
    print_vec(v_inter, "Intersection (1 & 2)");

    // 3. std::set_difference
    // Elements in set1 that are NOT in set2.
    print_separator("std::set_difference");
    std::vector<int> v_diff;
    std::set_difference(set1.begin(), set1.end(), 
                        set2.begin(), set2.end(), 
                        std::back_inserter(v_diff));
    print_vec(v_diff, "Difference (1 - 2)");

    // 4. std::set_symmetric_difference
    // Elements in either set, but not both.
    print_separator("std::set_symmetric_difference");
    std::vector<int> v_symm;
    std::set_symmetric_difference(set1.begin(), set1.end(), 
                                  set2.begin(), set2.end(), 
                                  std::back_inserter(v_symm));
    print_vec(v_symm, "Symmetric Diff (1 ^ 2)");

    // 5. std::includes
    // Checks if every element from range2 is present in range1.
    print_separator("std::includes");
    std::vector<int> subset = {2, 4};
    bool is_subset = std::includes(set1.begin(), set1.end(), 
                                   subset.begin(), subset.end());
    std::println("Is {{2,4}} a subset of Set 1? {}", is_subset);

    // 6. C++20 Ranges versions
    print_separator("std::ranges versions");
    std::vector<int> res;
    // Note: Ranges versions also return the input and output iterators as a struct
    std::ranges::set_union(set1, set2, std::back_inserter(res));
    print_vec(res, "Ranges Union Result");

    /*
    --- INTERVIEW PITFALLS ---
    1. Sorting requirement: This is the most common mistake. Ranges MUST be 
       sorted according to the same comparator used in the algorithm.
    2. Duplicates: If the input ranges have duplicate elements, the output 
       will handle them in a multiset-like fashion.
    3. Iterator performance: Using `std::back_inserter` causes reallocations 
       if the destination vector is not pre-reserved. For maximum performance, 
       reserve `set1.size() + set2.size()`.

    --- PRODUCTION NOTES ---
    - These algorithms are much more efficient than inserting into a `std::set` 
      repeatedly (O(N+M) vs O(M log N)).
    - Use `std::ranges::set_intersection` with projections to intersect 
      complex objects based on specific fields.
    - If you are using these on `std::set` containers, remember that `std::set` 
      is already sorted, so you can pass its iterators directly.
    */

    return 0;
}
