/*
Title: std::forward_list Complete Guide
Category: Sequence Containers
File: forward_list.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::forward_list (Singly-Linked List), explaining its minimalist design, 
zero-overhead philosophy, and specific insertion/deletion patterns.

Compile:
g++ -std=c++23 forward_list.cpp -o forward_list

Run:
./forward_list

Key Topics:
- Singly-Linked List Mechanics
- Zero space overhead compared to handwritten C lists
- insert_after and_after
- Lack of size() method (O(N) calculation)
- C++23: std::ranges::to, formatted output
- Production Use Cases: Extremely memory-constrained environments

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <forward_list>
#include <print>
#include <ranges>

/**
 * @brief Demonstrates basic forward_list operations.
 */
void basic_operations() {
    std::println("--- Forward List Basics ---");
    std::forward_list<int> flist = {10, 20, 30};
    
    // Only push_front is supported (no push_back, no back pointer)
    flist.push_front(5);
    
    std::println("Forward List: {}", flist);
}

/**
 * @brief Explains insert_after and erase_after mechanics.
 */
void insert_erase_mechanics() {
    std::println("\n--- Insert/Erase Mechanics ---");
    std::forward_list<int> flist = {1, 2, 4, 5};
    
    // To insert 3 between 2 and 4, we need an iterator to 2.
    auto it = flist.begin();
    std::advance(it, 1); // points to 2
    
    // Insert AFTER the iterator
    flist.insert_after(it, 3);
    std::println("After insertion: {}", flist);
    
    // To erase 4, we need an iterator to the element BEFORE 4 (which is 3)
    auto it2 = flist.begin();
    std::advance(it2, 2); // points to 3
    
    // Erase AFTER the iterator
    flist.erase_after(it2);
    std::println("After erasure: {}", flist);
}

/**
 * @brief C++23 features with forward_list.
 */
void cpp23_forward_list() {
    std::println("\n--- C++23 and Forward List ---");
    
    auto range = std::views::iota(1, 6) 
               | std::views::transform([](int n) { return n * 10; });
               
    auto flist = std::ranges::to<std::forward_list<int>>(range);
    
    std::println("Forward List from range: {}", flist);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. NO .size() METHOD: Calculating size is O(N) by design to avoid the memory overhead of storing it. Use std::distance(begin, end).");
    std::println("2. insert_after/erase_after: Requires a pointer to the PREVIOUS node. Keep this in mind during interviews (e.g., removing from singly linked list).");
    std::println("3. Use Case: When memory overhead is strictly monitored, or building hash tables with chaining (like std::unordered_map's internal structure).");
    std::println("4. Iterators: Forward iterators only (no rbegin/rend).");
}

/**
 * @brief Complexity:
 * - Access: O(N)
 * - Insert/Delete front: O(1)
 * - Insert/Delete after iterator: O(1)
 */
int main() {
    basic_operations();
    insert_erase_mechanics();
    cpp23_forward_list();
    interview_notes();
    return 0;
}
