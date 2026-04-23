/*
Title: Monotonic Stack Pattern Complete Guide
Category: DSA Patterns
File: monotonic_stack.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Comprehensive guide to the Monotonic Stack pattern. Solves problems involving 
"nearest greater/smaller element" in O(N) time.

Compile:
g++ -std=c++23 monotonic_stack.cpp -o monotonic_stack

Run:
./monotonic_stack

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Monotonic Increasing Stack
- Monotonic Decreasing Stack
- Next Greater Element (NGE)
- Largest Rectangle in Histogram
- Trapping Rain Water (Stack approach)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <stack>
#include <print>

/**
 * @brief Next Greater Element (NGE).
 * For each element in nums, find the first element to its right that is greater.
 * If none exists, use -1.
 * Complexity: O(N) Time, O(N) Space.
 */
std::vector<int> next_greater_element(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> nge(n, -1);
    std::stack<int> s; // Stores indices

    for (int i = 0; i < n; ++i) {
        // While current element is greater than element at index s.top()
        while (!s.empty() && nums[i] > nums[s.top()]) {
            nge[s.top()] = nums[i];
            s.pop();
        }
        s.push(i);
    }
    return nge;
}

/**
 * @brief Largest Rectangle in Histogram.
 * Finds the maximum area of a rectangle that can be formed within a histogram.
 * Complexity: O(N) Time, O(N) Space.
 */
long long largest_rectangle_area(const std::vector<int>& heights) {
    int n = heights.size();
    std::stack<int> s;
    long long max_area = 0;

    for (int i = 0; i <= n; ++i) {
        // Use 0 as a sentinel at the end to flush the stack
        int h = (i == n) ? 0 : heights[i];
        
        while (!s.empty() && heights[s.top()] >= h) {
            int height = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            max_area = std::max(max_area, (long long)height * width);
        }
        s.push(i);
    }
    return max_area;
}

/**
 * @brief Trapping Rain Water.
 * Uses a monotonic decreasing stack to find "pits" that can hold water.
 */
int trap_water(const std::vector<int>& height) {
    int n = height.size();
    std::stack<int> s;
    int trapped = 0;

    for (int i = 0; i < n; ++i) {
        while (!s.empty() && height[i] > height[s.top()]) {
            int mid = s.top();
            s.pop();
            if (s.empty()) break;
            
            int left = s.top();
            int h = std::min(height[left], height[i]) - height[mid];
            int w = i - left - 1;
            trapped += h * w;
        }
        s.push(i);
    }
    return trapped;
}

// --- Demos ---

void demo_nge() {
    std::println("\n--- Next Greater Element ---");
    std::vector<int> nums = {2, 1, 2, 4, 3};
    auto res = next_greater_element(nums);
    std::println("Nums: {}", nums);
    std::println("NGEs: {}", res); // Expected: [4, 2, 4, -1, -1]
}

void demo_histogram() {
    std::println("\n--- Largest Rectangle in Histogram ---");
    std::vector<int> heights = {2, 1, 5, 6, 2, 3};
    std::println("Heights: {}", heights);
    std::println("Max Area: {}", largest_rectangle_area(heights)); // Expected: 10 (5 & 6)
}

void demo_trapping_water() {
    std::println("\n--- Trapping Rain Water (Stack) ---");
    std::vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    std::println("Height Map: {}", height);
    std::println("Total Trapped: {}", trap_water(height)); // Expected: 6
}

/**
 * Interview Pitfalls & Production Notes:
 * 1. Stack Content: Decide whether to store values or indices. Storing indices 
 *    is generally more powerful as it allows calculating widths/distances.
 * 2. Sentinels: Adding a `0` or `-1` to the end of the input (like in Histogram) 
 *    can simplify code by ensuring the stack is emptied at the end.
 * 3. Monotonicity:
 *    - Next Greater -> Monotonic Decreasing Stack (top is smallest).
 *    - Next Smaller -> Monotonic Increasing Stack (top is largest).
 * 4. Complexity: Every element is pushed and popped at most once, ensuring O(N).
 */

int main() {
    demo_nge();
    demo_histogram();
    demo_trapping_water();
    return 0;
}
