/*
Title: Min/Max Algorithms Complete Guide
Category: Algorithms
File: minmax.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Covers algorithms for finding minimum and maximum elements, as well as 
clamping values within a range.

Compile:
g++ -std=c++23 minmax.cpp -o minmax

Run:
./minmax

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::min, std::max, std::minmax (Values)
- std::min_element, std::max_element, std::minmax_element (Ranges)
- std::clamp (C++17)
- C++20 Ranges equivalents and projections
- Handling empty ranges

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <ranges>
#include <print>
#include <string>

void print_separator(std::string_view title) {
    std::println("\n--- {} ---", title);
}

int main() {
    // 1. Basic min/max (C++11/14/17)
    print_separator("std::min / std::max / std::minmax");
    int a = 10, b = 20;
    std::println("min(10, 20): {}", std::min(a, b));
    std::println("max(10, 20): {}", std::max(a, b));

    auto [val_min, val_max] = std::minmax({1, 5, 2, 9, 3}); // Initializer list
    std::println("minmax of list: min={}, max={}", val_min, val_max);

    // 2. Element searching in ranges
    // Complexity: O(N)
    print_separator("std::min_element / std::max_element");
    std::vector<int> nums = {40, 10, 70, 30, 90, 20};
    auto it_min = std::min_element(nums.begin(), nums.end());
    auto it_max = std::max_element(nums.begin(), nums.end());
    if (it_min != nums.end()) {
        std::println("Min element: {} at index {}", *it_min, std::distance(nums.begin(), it_min));
    }
    if (it_max != nums.end()) {
        std::println("Max element: {} at index {}", *it_max, std::distance(nums.begin(), it_max));
    }

    // 3. std::minmax_element (More efficient than calling both separately)
    print_separator("std::minmax_element");
    auto [min_it, max_it] = std::minmax_element(nums.begin(), nums.end());
    std::println("Result: [{}, {}]", *min_it, *max_it);

    // 4. std::clamp (C++17)
    // Constrains a value between a low and high bound.
    print_separator("std::clamp");
    int sensor_val = 150;
    int safe_val = std::clamp(sensor_val, 0, 100);
    std::println("Clamped 150 between 0 and 100: {}", safe_val);

    // 5. C++20 Ranges with Projections
    print_separator("Ranges and Projections");
    struct Player {
        std::string name;
        int score;
    };
    std::vector<Player> players = {
        {"Alice", 500},
        {"Bob", 1200},
        {"Charlie", 800}
    };

    // Find player with max score using projection
    auto top_player = std::ranges::max_element(players, {}, &Player::score);
    if (top_player != players.end()) {
        std::println("Top Player: {} with score {}", top_player->name, top_player->score);
    }

    // 6. C++23: std::ranges::min/max on entire ranges
    print_separator("C++23 std::ranges::min/max");
    // Returns the VALUE, not the iterator (requires non-empty range)
    int smallest = std::ranges::min(nums);
    int largest = std::ranges::max(nums);
    std::println("Smallest value: {}, Largest: {}", smallest, largest);

    /*
    --- INTERVIEW PITFALLS ---
    1. Empty Ranges: Calling `min_element` on an empty container returns the 
       `end()` iterator. Dereferencing it is UB.
    2. Stability: 
       - `min_element` returns the FIRST occurrence of the minimum.
       - `max_element` returns the FIRST occurrence of the maximum.
       - `minmax_element` returns the FIRST occurrence of min and LAST occurrence of max.
    3. Performance: `minmax_element` performs about 1.5 * N comparisons, while 
       calling `min_element` and `max_element` separately performs 2 * N.

    --- PRODUCTION NOTES ---
    - Use `std::clamp` for UI logic, physics engines, or any bound-checking.
    - Ranges versions are generally safer and more expressive with projections.
    - For large datasets, consider if you only need the min/max or if the 
      data should be kept in a sorted container or a heap.
    */

    return 0;
}
