/*
Title: Numeric Algorithms Complete Guide
Category: Algorithms
File: numeric_algorithms.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive overview of numeric algorithms in the C++ Standard Library, 
found in <numeric>. Covers basic accumulation to complex transformations 
and scans.

Compile:
g++ -std=c++23 numeric_algorithms.cpp -o numeric_algorithms

Run:
./numeric_algorithms

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::iota (Fill with sequences)
- std::accumulate vs std::reduce (C++17)
- std::inner_product & std::transform_reduce
- std::partial_sum & std::adjacent_difference
- std::inclusive_scan & std::exclusive_scan
- std::midpoint & std::lerp (C++20)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <numeric>
#include <algorithm>
#include <print>
#include <cmath>

void print_separator(std::string_view title) {
    std::println("\n--- {} ---", title);
}

int main() {
    // 1. std::iota
    // Fills a range with sequentially increasing values.
    print_separator("std::iota");
    std::vector<int> nums(10);
    std::iota(nums.begin(), nums.end(), 1); // 1, 2, 3...
    for (int n : nums) std::print("{} ", n);
    std::println("");

    // 2. std::accumulate (The classic sum)
    // Time Complexity: O(N)
    // Guaranteed sequential processing.
    print_separator("std::accumulate");
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    int product = std::accumulate(nums.begin(), nums.end(), 1, std::multiplies<int>());
    std::println("Sum: {}, Product: {}", sum, product);

    // 3. std::reduce (C++17)
    // Similar to accumulate but doesn't guarantee order. 
    // Designed for parallel execution.
    print_separator("std::reduce");
    int sum_reduce = std::reduce(nums.begin(), nums.end(), 0);
    std::println("Sum using reduce: {}", sum_reduce);

    // 4. std::inner_product
    // S0*T0 + S1*T1 + ...
    print_separator("std::inner_product");
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {4, 5, 6};
    int dot_product = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    std::println("Dot product of {{1,2,3}} and {{4,5,6}}: {}", dot_product);

    // 5. std::adjacent_difference
    // Calculates difference between adjacent elements.
    print_separator("std::adjacent_difference");
    std::vector<int> squares = {1, 4, 9, 16, 25};
    std::vector<int> diffs(squares.size());
    std::adjacent_difference(squares.begin(), squares.end(), diffs.begin());
    std::print("Differences: ");
    for (int d : diffs) std::print("{} ", d);
    std::println(" (Notice 1st element is unchanged)");

    // 6. std::partial_sum
    // S0, S0+S1, S0+S1+S2...
    print_separator("std::partial_sum");
    std::vector<int> p_sum(nums.size());
    std::partial_sum(nums.begin(), nums.end(), p_sum.begin());
    std::print("Partial sums: ");
    for (int s : p_sum) std::print("{} ", s);
    std::println("");

    // 7. C++20 Utility Functions
    print_separator("C++20: midpoint and lerp");
    int m = std::midpoint(10, 20);
    double l = std::lerp(0.0, 100.0, 0.5); // Linear interpolation
    std::println("Midpoint(10, 20): {}", m);
    std::println("Lerp(0, 100, 0.5): {}", l);

    // 8. transform_reduce (C++17)
    // Map-Reduce in a single STL call
    print_separator("std::transform_reduce");
    // Calculate sum of squares
    int sum_squares = std::transform_reduce(nums.begin(), nums.end(), 0, 
                                            std::plus<>(), 
                                            [](int n){ return n * n; });
    std::println("Sum of squares: {}", sum_squares);

    /*
    --- INTERVIEW PITFALLS ---
    1. accumulate vs reduce: `accumulate` is sequential (strict order), 
       `reduce` can be out-of-order. Use `reduce` if your operation is 
       associative and commutative (like addition).
    2. Precision in lerp/midpoint: Always use C++20 versions for floating 
       point arithmetic as they avoid common overflow/precision bugs 
       (e.g., (a+b)/2 can overflow).
    3. Iterator Validity: Ensure destination container has enough space 
       (use `std::back_inserter` if needed, but note performance implications).

    --- PRODUCTION NOTES ---
    - For large datasets, use the parallel execution policies (e.g., `std::execution::par`) 
      with `reduce` or `transform_reduce` if your compiler supports them.
    - `std::iota` is extremely useful for generating indices for sorting or 
      initializing mock data.
    - `std::adjacent_difference` is the inverse of `std::partial_sum`.
    */

    return 0;
}
