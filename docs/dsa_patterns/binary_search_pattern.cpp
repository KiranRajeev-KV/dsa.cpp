/*
Title: Binary Search Pattern Complete Guide
Category: DSA Patterns
File: binary_search_pattern.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Deep dive into Binary Search variations, including finding exact elements, 
first/last occurrences, and the powerful "Binary Search on Answer" technique.

Compile:
g++ -std=c++23 binary_search_pattern.cpp -o binary_search_pattern

Run:
./binary_search_pattern

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Standard Binary Search
- Lower Bound & Upper Bound (Finding boundaries)
- Binary Search on Answer (Predicate-based)
- Real-number Binary Search
- C++23 std::ranges::binary_search / lower_bound

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <ranges>
#include <print>
#include <cmath>

/**
 * @brief Standard Binary Search.
 * Finds index of target in O(log N).
 */
int binary_search_recursive(const std::vector<int>& nums, int left, int right, int target) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    if (nums[mid] > target) return binary_search_recursive(nums, left, mid - 1, target);
    return binary_search_recursive(nums, mid + 1, right, target);
}

/**
 * @brief Find the first occurrence (Lower Bound) of target.
 * Return index.
 */
int find_first_occurrence(const std::vector<int>& nums, int target) {
    int left = 0, right = (int)nums.size() - 1;
    int ans = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] >= target) {
            if (nums[mid] == target) ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

/**
 * @brief Binary Search on Answer: The "Koko Eating Bananas" style problem.
 * Given a predicate, find the minimum value X such that can_do(X) is true.
 */
bool can_finish(const std::vector<int>& piles, int h, int k) {
    long long hours = 0;
    for (int p : piles) {
        hours += (p + k - 1) / k; // Ceiling division
    }
    return hours <= h;
}

int min_eating_speed(const std::vector<int>& piles, int h) {
    int left = 1;
    int right = *std::ranges::max_element(piles);
    int ans = right;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (can_finish(piles, h, mid)) {
            ans = mid;
            right = mid - 1; // Try smaller speed
        } else {
            left = mid + 1;  // Need faster speed
        }
    }
    return ans;
}

/**
 * @brief Binary Search for Square Root (Real Numbers).
 * Uses a fixed number of iterations for precision.
 */
double my_sqrt(double x, double precision = 1e-9) {
    if (x < 0) return NAN;
    if (x == 0) return 0;
    
    double left = 0, right = std::max(1.0, x);
    // Use precision for the stopping condition
    while ((right - left) > precision) {
        double mid = left + (right - left) / 2.0;
        if (mid * mid > x) right = mid;
        else left = mid;
    }
    return left;
}

// --- Demos ---

void demo_basic_bs() {
    std::println("\n--- Basic Binary Search ---");
    std::vector<int> nums = {1, 3, 5, 5, 5, 8, 10};
    int target = 5;
    
    // Using STL
    bool exists = std::ranges::binary_search(nums, target);
    auto it = std::ranges::lower_bound(nums, target);
    
    std::println("Nums: {}", nums);
    std::println("Target {} exists? {}", target, exists);
    if (it != nums.end()) {
        std::println("First occurrence of {} at index: {}", target, std::distance(nums.begin(), it));
    }
    
    std::println("Custom first occurrence index: {}", find_first_occurrence(nums, target));
}

void demo_bs_on_answer() {
    std::println("\n--- Binary Search on Answer (Eating Bananas) ---");
    std::vector<int> piles = {3, 6, 7, 11};
    int h = 8;
    std::println("Piles: {}, Hours: {}", piles, h);
    std::println("Min eating speed: {}", min_eating_speed(piles, h)); // Expect 4
}

void demo_real_bs() {
    std::println("\n--- Real Number Binary Search ---");
    double val = 2.0;
    std::println("Sqrt({}) = {:.10f}", val, my_sqrt(val));
}

/**
 * Interview Pitfalls & Production Notes:
 * 1. Mid Calculation: Use `L + (R - L) / 2` to avoid `(L + R)` overflow.
 * 2. Infinite Loops: Be extremely careful with `while(left < right)` vs `left <= right`.
 *    Standard safe pattern: `left <= right`, `mid = L + (R-L)/2`, `L = mid + 1`, `R = mid - 1`.
 * 3. Range boundaries: For BS on answer, ensure `right` is large enough to 
 *    cover the result but not so large it overflows during calculations.
 * 4. std::ranges: C++20/23 ranges provide `lower_bound`, `upper_bound`, and 
 *    `binary_search` which are preferred for standard containers.
 */

int main() {
    demo_basic_bs();
    demo_bs_on_answer();
    demo_real_bs();
    return 0;
}
