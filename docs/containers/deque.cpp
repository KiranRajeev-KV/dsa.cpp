/*
Title: std::deque Complete Guide
Category: Sequence Containers
File: deque.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A detailed guide to std::deque (Double-Ended Queue), explaining its segmented memory architecture, 
performance trade-offs compared to vector, and C++23 features.

Compile:
g++ -std=c++23 deque.cpp -o deque

Run:
./deque

Key Topics:
- Segmented Array Mechanics (Map of Chunks)
- O(1) Push/Pop at both ends
- Iterator Stability vs Vector
- C++23: std::ranges::to, formatted output
- Production Use Cases: When to prefer deque over vector

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <deque>
#include <print>
#include <ranges>
#include <string>

/**
 * @brief Demonstrates deque's bidirectional efficiency.
 */
void demonstrate_deque_basics() {
    std::println("--- Deque Basics ---");
    std::deque<std::string> dq = {"C++", "is"};
    
    dq.push_front("Modern");
    dq.push_back("Awesome");
    
    // std::deque supports random access like vector
    std::println("Second element: {}", dq[1]);
    
    std::println("Current Deque: {}", dq);
}

/**
 * @brief Explains memory layout and performance characteristics.
 */
void memory_and_performance() {
    std::println("\n--- Memory & Performance ---");
    std::println("Unlike std::vector, std::deque is not guaranteed to be contiguous.");
    std::println("It uses a map of fixed-size memory chunks.");
    
    std::deque<int> dq;
    // Pushing front is O(1) and doesn't require shifting elements
    dq.push_front(10);
    dq.push_back(20);
    
    std::println("Size: {}, First: {}, Last: {}", dq.size(), dq.front(), dq.back());
    
    std::println("Trade-off: Higher overhead for random access and iteration compared to vector.");
    std::println("Benefit: Efficient insertion at both ends and no full reallocations.");
}

/**
 * @brief C++23 features with deque.
 */
void cpp23_deque() {
    std::println("\n--- C++23 and Deque ---");
    
    // Filtering a range into a deque
    auto numbers = std::views::iota(1, 10) 
                 | std::views::filter([](int n){ return n % 2 == 0; });
                 
    auto dq = std::ranges::to<std::deque<int>>(numbers);
    
    std::println("Deque from filtered range: {}", dq);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Iterator Invalidation: Pushing at ends invalidates iterators, but NOT references.");
    std::println("2. Memory usage: Deque has higher constant factor overhead than vector.");
    std::println("3. Cache locality: Worse than vector due to non-contiguous chunks.");
    std::println("4. Default stack/queue: std::deque is the default underlying container for std::stack and std::queue.");
}

/**
 * @brief Complexity:
 * - Access: O(1)
 * - Insert/Delete at ends: O(1)
 * - Insert/Delete in middle: O(N)
 */
int main() {
    demonstrate_deque_basics();
    memory_and_performance();
    cpp23_deque();
    interview_notes();
    return 0;
}
