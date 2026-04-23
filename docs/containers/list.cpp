/*
Title: std::list Complete Guide
Category: Sequence Containers
File: list.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::list (Doubly-Linked List), focusing on its specific use cases, 
node-based memory allocation, constant time insertions/deletions, and list-specific algorithms.

Compile:
g++ -std=c++23 list.cpp -o list

Run:
./list

Key Topics:
- Doubly-Linked List Mechanics
- O(1) Insertions and Deletions (with iterator)
- Iterator invalidation (or lack thereof)
- List-specific member functions: splice, merge, sort, unique
- C++23: std::ranges::to, std::print
- Production Notes: When NOT to use list (cache misses)

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <list>
#include <print>
#include <algorithm>
#include <ranges>
#include <string>

/**
 * @brief Demonstrates basic list operations and node manipulation.
 */
void basic_operations() {
    std::println("--- List Basics ---");
    std::list<int> l = {10, 20, 30};
    
    // Constant time insertion at ends
    l.push_front(5);
    l.push_back(40);
    
    std::println("List elements: {}", l);
    
    // Constant time deletion
    l.pop_front();
    l.pop_back();
    std::println("After pops: {}", l);
}

/**
 * @brief Showcases list-specific algorithms which are faster than generic algorithms.
 */
void list_specific_algorithms() {
    std::println("\n--- List Specific Algorithms ---");
    std::list<int> l1 = {5, 2, 8, 1, 9};
    std::list<int> l2 = {3, 7, 4};
    
    // List has its own sort because std::sort requires random access iterators
    l1.sort();
    l2.sort();
    std::println("Sorted l1: {}", l1);
    
    // Merge l2 into l1 (both must be sorted)
    l1.merge(l2);
    std::println("Merged list: {}", l1);
    std::println("l2 after merge: {} (empty because nodes were transferred)", l2);
    
    // Splice: Transfer elements without reallocation or copying
    std::list<int> l3 = {100, 200};
    auto it = l1.begin();
    std::advance(it, 2);
    l1.splice(it, l3); // Insert l3 into l1 before position `it`
    std::println("After splice: {}", l1);
}

/**
 * @brief Demonstrates C++23 features with list.
 */
void cpp23_list() {
    std::println("\n--- C++23 and List ---");
    
    auto string_view_range = std::views::split(std::string_view("C++23 is great"), ' ')
                           | std::views::transform([](auto&& rng) {
                               return std::string(rng.begin(), rng.end());
                             });
                             
    // Convert view to list
    auto str_list = std::ranges::to<std::list<std::string>>(string_view_range);
    
    std::println("List from split view: {}", str_list);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Iterators: Only bidirectional. std::sort() does not work; use l.sort().");
    std::println("2. Invalidation: Insertions and deletions DO NOT invalidate iterators or references (except the deleted one).");
    std::println("3. Cache Performance: Extremely poor cache locality compared to std::vector. Avoid unless O(1) insertions in the middle are proven to be the bottleneck.");
    std::println("4. Memory Overhead: 2 pointers per node (prev, next) + allocator overhead.");
}

/**
 * @brief Complexity:
 * - Access: O(N) (No random access)
 * - Insert/Delete at ends: O(1)
 * - Insert/Delete at iterator: O(1)
 */
int main() {
    basic_operations();
    list_specific_algorithms();
    cpp23_list();
    interview_notes();
    return 0;
}
