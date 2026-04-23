/*
Title: Two Pointers Pattern Complete Guide
Category: DSA Patterns
File: two_pointers.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Detailed exploration of the Two Pointers technique, including converging pointers, 
fast & slow pointers (Floyd's Cycle Finding), and sorted array manipulation.

Compile:
g++ -std=c++23 two_pointers.cpp -o two_pointers

Run:
./two_pointers

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Opposite Ends (Converging) Pointers
- Fast & Slow Pointers (Cycle Detection)
- Merging Sorted Arrays
- Partitioning (QuickSort style)
- C++23 ranges and iterators

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <print>
#include <optional>

/**
 * @brief Opposite Ends: Find two numbers in a sorted array that sum to target.
 * Complexity: O(N) Time, O(1) Space.
 */
std::optional<std::pair<int, int>> two_sum_sorted(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = (int)nums.size() - 1;

    while (left < right) {
        int current_sum = nums[left] + nums[right];
        if (current_sum == target) {
            return std::make_pair(nums[left], nums[right]);
        } else if (current_sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return std::nullopt;
}

/**
 * @brief Fast & Slow Pointers: Detect cycle in a linked list.
 * (Conceptual implementation using a vector to simulate list nodes).
 */
struct Node {
    int value;
    Node* next;
    explicit Node(int v) : value(v), next(nullptr) {}
};

bool has_cycle(Node* head) {
    if (!head) return false;
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

/**
 * @brief Fast & Slow: Find the middle of a linked list.
 */
Node* find_middle(Node* head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

/**
 * @brief Merging Sorted Arrays: In-place merge (assuming nums1 has space).
 */
void merge_sorted_inplace(std::vector<int>& nums1, int m, const std::vector<int>& nums2, int n) {
    int i = m - 1;     // Pointer for nums1 end
    int j = n - 1;     // Pointer for nums2 end
    int k = m + n - 1; // Pointer for result end

    while (j >= 0) {
        if (i >= 0 && nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }
}

// --- Demos ---

void demo_two_sum() {
    std::println("\n--- Two Sum (Sorted) ---");
    std::vector<int> nums = {1, 2, 3, 4, 6, 8, 11};
    int target = 10;
    auto res = two_sum_sorted(nums, target);
    if (res) {
        std::println("Target {}: Found pair ({}, {})", target, res->first, res->second);
    } else {
        std::println("Target {}: No pair found", target);
    }
}

void demo_linked_list_pointers() {
    std::println("\n--- Fast & Slow Pointers ---");
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    n1->next = n2; n2->next = n3; n3->next = n4;
    
    std::println("Middle node value: {}", find_middle(n1)->value);
    
    n4->next = n2; // Create cycle
    std::println("Has cycle: {}", has_cycle(n1));
    
    // Cleanup (Careful with cycles)
    n4->next = nullptr;
    delete n4; delete n3; delete n2; delete n1;
}

void demo_merge() {
    std::println("\n--- Merge Sorted Arrays ---");
    std::vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    std::vector<int> nums2 = {2, 5, 6};
    merge_sorted_inplace(nums1, 3, nums2, 3);
    std::println("Merged Array: {}", nums1);
}

/**
 * Interview Pitfalls & Production Notes:
 * 1. Sorting: Two pointers often requires a sorted array. If the array isn't 
 *    sorted, O(N log N) sorting cost must be factored in.
 * 2. Integer Overflow: When calculating `(left + right) / 2` or sums, watch 
 *    out for overflow. Use `long long` or `left + (right - left) / 2`.
 * 3. Null Pointers: In linked list problems, always check `fast` and `fast->next` 
 *    to avoid segmentation faults.
 * 4. In-place vs New Array: Merging in-place from the back avoids overwriting 
 *    elements you haven't processed yet.
 */

int main() {
    demo_two_sum();
    demo_linked_list_pointers();
    demo_merge();
    return 0;
}
