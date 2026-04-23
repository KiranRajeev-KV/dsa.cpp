/*
Title: Partitioning Algorithms Complete Guide
Category: Algorithms
File: partitioning.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Covers partitioning algorithms that reorganize elements in a range based 
on a predicate. Critical for quicksort, selection, and data organization.

Compile:
g++ -std=c++23 partitioning.cpp -o partitioning

Run:
./partitioning

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::partition vs std::stable_partition
- std::is_partitioned
- std::partition_point
- std::partition_copy
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
    std::vector<int> nums = {1, 10, 2, 9, 3, 8, 4, 7, 5, 6};
    auto is_even = [](int n) { return n % 2 == 0; };

    // 1. std::partition
    // Reorders elements so that all elements satisfying the predicate 
    // come before those that don't.
    // Complexity: O(N)
    print_separator("std::partition");
    std::vector<int> p1 = nums;
    auto it1 = std::partition(p1.begin(), p1.end(), is_even);
    print_vec(p1, "Partitioned");
    std::println("Pivot point value (first false): {}", (it1 != p1.end() ? std::to_string(*it1) : "end"));

    // 2. std::stable_partition
    // Like partition, but preserves the relative order of elements 
    // within each group.
    print_separator("std::stable_partition");
    std::vector<int> p2 = nums;
    std::stable_partition(p2.begin(), p2.end(), is_even);
    print_vec(p2, "Stable Partitioned (Even first)");

    // 3. std::is_partitioned
    print_separator("std::is_partitioned");
    bool partitioned = std::is_partitioned(p2.begin(), p2.end(), is_even);
    std::println("Is p2 partitioned by is_even? {}", partitioned);

    // 4. std::partition_point
    // In a partitioned range, finds the first element that doesn't 
    // satisfy the predicate (the pivot).
    print_separator("std::partition_point");
    auto it2 = std::partition_point(p2.begin(), p2.end(), is_even);
    std::print("First partition (even): ");
    for (auto it = p2.begin(); it != it2; ++it) std::print("{} ", *it);
    std::println("");

    // 5. std::partition_copy
    // Copies elements to two different destinations based on predicate.
    print_separator("std::partition_copy");
    std::vector<int> evens, odds;
    std::partition_copy(nums.begin(), nums.end(), 
                        std::back_inserter(evens), 
                        std::back_inserter(odds), 
                        is_even);
    print_vec(evens, "Evens");
    print_vec(odds, "Odds");

    // 6. C++20 Ranges version
    print_separator("std::ranges::partition");
    std::vector<int> p3 = nums;
    std::ranges::partition(p3, [](int n) { return n < 5; });
    print_vec(p3, "Partitioned (< 5)");

    /*
    --- INTERVIEW PITFALLS ---
    1. Stability: Standard `partition` is NOT stable. If the original order 
       of evens relative to each other must be kept, use `stable_partition`.
    2. Partition vs Sort: Partitioning is O(N), Sorting is O(N log N). 
       If you only need to group elements (e.g., "move all zeros to end"), 
       partitioning is much faster.
    3. Return value: The returned iterator points to the first element of 
       the SECOND group (those for which predicate is false).

    --- PRODUCTION NOTES ---
    - `std::partition` is the core algorithm used in Quicksort's partitioning step.
    - `stable_partition` may allocate extra memory to maintain stability and 
       achieve O(N) complexity. If memory is tight, it uses an in-place 
       algorithm with O(N log N) complexity.
    - Use `partition_point` to binary search for the split in an already 
      partitioned range (useful for combining with other algorithms).
    */

    return 0;
}
