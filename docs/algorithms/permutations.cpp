/*
Title: Permutation Algorithms Complete Guide
Category: Algorithms
File: permutations.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A guide to generating and checking permutations of sequences using the 
Standard Library.

Compile:
g++ -std=c++23 permutations.cpp -o permutations

Run:
./permutations

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::next_permutation
- std::prev_permutation
- std::is_permutation
- Complexity of generating all permutations
- std::ranges equivalents (C++20/23)

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
    // 1. next_permutation
    // Reorders elements into the lexicographically next greater permutation.
    // Returns false if no such permutation exists (the range is sorted descending).
    // Complexity: O(N) per call.
    print_separator("std::next_permutation");
    std::string s = "abc";
    std::println("Generating all permutations of '{}':", s);
    do {
        std::println("  - {}", s);
    } while (std::next_permutation(s.begin(), s.end()));

    // 2. is_permutation
    // Checks if one sequence is a permutation of another.
    // Complexity: O(N^2) (or O(N) if we can use a hash map, but STL is O(N^2))
    print_separator("std::is_permutation");
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {5, 4, 3, 2, 1};
    std::vector<int> v3 = {1, 2, 3, 3, 5};
    
    std::println("v2 is a permutation of v1? {}", std::is_permutation(v1.begin(), v1.end(), v2.begin()));
    std::println("v3 is a permutation of v1? {}", std::is_permutation(v1.begin(), v1.end(), v3.begin()));

    // 3. prev_permutation
    // Reorders elements into the lexicographically previous smaller permutation.
    print_separator("std::prev_permutation");
    std::vector<int> nums = {3, 2, 1};
    std::print("Descending sequence: ");
    for (int n : nums) std::print("{} ", n);
    std::println("");
    
    std::prev_permutation(nums.begin(), nums.end());
    std::print("Previous permutation: ");
    for (int n : nums) std::print("{} ", n);
    std::println("");

    // 4. Ranges Version (C++20)
    print_separator("std::ranges::is_permutation");
    bool is_p = std::ranges::is_permutation(v1, v2);
    std::println("Ranges version check: {}", is_p);

    // 5. Practical Interview Example: All Permutations of a vector
    print_separator("Finding k-th Permutation Tip");
    std::vector<int> p_vec = {1, 2, 3};
    // To get ALL permutations, you MUST start from a SORTED sequence.
    std::ranges::sort(p_vec);
    int count = 0;
    do {
        count++;
    } while (std::ranges::next_permutation(p_vec).found);
    std::println("Total permutations of size 3: {}", count); // 3! = 6

    /*
    --- INTERVIEW PITFALLS ---
    1. Lexicographical Order: next_permutation assumes you start with the SMALLEST 
       permutation (fully sorted ascending). If you start in the middle, you only 
       get the remaining permutations.
    2. Complexity: Generating all permutations is O(N! * N). Only feasible for 
       small N (usually N <= 10 or 12).
    3. Duplicates: next_permutation handles duplicates correctly (e.g., 
       permutations of "AAB" are "AAB", "ABA", "BAA").

    --- PRODUCTION NOTES ---
    - Use `std::is_permutation` when order doesn't matter but content does.
    - If comparing large sequences for permutation property, it might be 
      faster to sort both and then compare (O(N log N)) instead of 
      `std::is_permutation`'s O(N^2).
    - C++20 `std::ranges::next_permutation` returns a result object with 
      a `.found` boolean, which is more idiomatic.
    */

    return 0;
}
