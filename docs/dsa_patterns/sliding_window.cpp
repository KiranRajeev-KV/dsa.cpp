/*
Title: Sliding Window Pattern Complete Guide
Category: DSA Patterns
File: sliding_window.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Comprehensive guide to the Sliding Window pattern, covering fixed-size and 
variable-size windows. Showcases C++23's `std::views::slide` and manual pointer management.

Compile:
g++ -std=c++23 sliding_window.cpp -o sliding_window

Run:
./sliding_window

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Fixed-size Sliding Window
- Variable-size (Dynamic) Sliding Window
- C++23 std::views::slide
- Deque-based (Monotonic Queue) Sliding Window Max
- Character frequency mapping with windows

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <unordered_map>
#include <ranges>
#include <print>

/**
 * @brief Fixed-size window example: Max sum of K consecutive elements.
 * Demonstrates C++23 std::views::slide for elegant iteration.
 */
long long max_sum_fixed_window(const std::vector<int>& nums, int k) {
    if (nums.size() < static_cast<size_t>(k)) return 0;

    long long max_sum = 0;
    
    // Using C++23 std::views::slide to get windows of size k
    // Note: slide(k) returns a view of views, each inner view is size k
    auto windows = nums | std::views::slide(k);
    
    for (auto window : windows) {
        long long current_sum = std::ranges::fold_left(window, 0LL, std::plus<>());
        max_sum = std::max(max_sum, current_sum);
    }
    
    return max_sum;
}

/**
 * @brief Variable-size window example: Longest substring with K distinct characters.
 * Classic O(N) approach with two pointers (shrinkable window).
 */
int longest_substring_k_distinct(std::string_view s, int k) {
    if (k == 0) return 0;
    
    std::unordered_map<char, int> counts;
    int left = 0, max_len = 0;
    
    for (int right = 0; right < (int)s.size(); ++right) {
        counts[s[right]]++;
        
        while ((int)counts.size() > k) {
            counts[s[left]]--;
            if (counts[s[left]] == 0) {
                counts.erase(s[left]);
            }
            left++;
        }
        max_len = std::max(max_len, right - left + 1);
    }
    return max_len;
}

/**
 * @brief Monotonic Queue Window: Sliding Window Maximum.
 * Finds the maximum in every window of size K in O(N).
 */
std::vector<int> sliding_window_max(const std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::deque<int> dq; // Stores indices of elements in decreasing order

    for (int i = 0; i < (int)nums.size(); ++i) {
        // Remove indices outside the current window
        if (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Remove elements smaller than the current element from the back
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // First window is hit at i = k-1
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

// --- Demos ---

void demo_fixed_window() {
    std::println("\n--- Fixed Window (Max Sum of K) ---");
    std::vector<int> nums = {2, 1, 5, 1, 3, 2};
    int k = 3;
    std::println("Nums: {}, K: {}", nums, k);
    std::println("Max Sum: {}", max_sum_fixed_window(nums, k)); // 5+1+3 = 9
}

void demo_variable_window() {
    std::println("\n--- Variable Window (K Distinct Chars) ---");
    std::string_view s = "araaci";
    int k = 2;
    std::println("String: '{}', K: {}", s, k);
    std::println("Max Length: {}", longest_substring_k_distinct(s, k)); // "araa" -> 4
}

void demo_monotonic_window() {
    std::println("\n--- Monotonic Queue (Sliding Window Max) ---");
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    auto res = sliding_window_max(nums, k);
    std::println("Nums: {}, K: {}", nums, k);
    std::println("Window Maxes: {}", res);
}

/**
 * Interview Pitfalls & Production Notes:
 * 1. Edge Cases: Window size K > Array size, Empty inputs, K=0.
 * 2. Efficiency: Fixed windows can often be updated in O(1) by adding new element 
 *    and subtracting the old one (rolling sum).
 * 3. Space Complexity: std::unordered_map can have overhead; for ASCII, a fixed 
 *    size array `int count[128]` is often faster.
 * 4. C++23 Note: std::views::slide(k) provides a safe, range-based way to 
 *    access windows without manual pointer arithmetic.
 */

int main() {
    demo_fixed_window();
    demo_variable_window();
    demo_monotonic_window();
    return 0;
}
