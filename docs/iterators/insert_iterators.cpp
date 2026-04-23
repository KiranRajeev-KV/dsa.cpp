/*
Title: Insert Iterators Complete Guide
Category: Iterators
File: insert_iterators.cpp
C++ Standard: C++23
Difficulty: Beginner to Intermediate

Purpose:
Explains how insert iterators allow algorithms to grow containers dynamically 
instead of overwriting existing elements. Essential for std::copy and transformation algorithms.

Compile:
g++ -std=c++23 insert_iterators.cpp -o insert_iterators

Run:
./insert_iterators

Key Topics:
- std::back_insert_iterator (std::back_inserter)
- std::front_insert_iterator (std::front_inserter)
- std::insert_iterator (std::inserter)
- Comparison: Overwriting vs. Inserting
- Use cases in data transformation

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <list>
#include <deque>
#include <set>
#include <algorithm>
#include <print>
#include <iterator>

/**
 * 1. BACK INSERTER
 * Uses push_back() under the hood.
 */
void demo_back_inserter() {
    std::println("--- 1. Back Inserter (std::vector / std::deque) ---");
    std::vector<int> src = {1, 2, 3};
    std::vector<int> dest;

    // Without back_inserter, this would be UB (Undefined Behavior) 
    // because dest is empty and copy would try to overwrite dest[0].
    std::copy(src.begin(), src.end(), std::back_inserter(dest));

    std::print("Dest after back_insert: ");
    for(int x : dest) std::print("{} ", x);
    std::println("\n");
}

/**
 * 2. FRONT INSERTER
 * Uses push_front() under the hood. Only works for containers like list/deque.
 */
void demo_front_inserter() {
    std::println("--- 2. Front Inserter (std::list / std::deque) ---");
    std::vector<int> src = {1, 2, 3};
    std::deque<int> dest;

    // Elements are inserted at the front, effectively reversing them if copied sequentially.
    std::copy(src.begin(), src.end(), std::front_inserter(dest));

    std::print("Dest after front_insert: ");
    for(int x : dest) std::print("{} ", x);
    std::println(" (Notice it's 3 2 1)\n");
}

/**
 * 3. GENERAL INSERTER
 * Uses insert(iterator, value) under the hood. Works for most containers including sets.
 */
void demo_general_inserter() {
    std::println("--- 3. General Inserter (std::set / Mid-vector) ---");
    std::vector<int> src = {10, 20, 30};
    
    // Example with vector - inserting into the middle
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.begin() + 2; // Pointing to '3'
    std::copy(src.begin(), src.end(), std::inserter(v, it));

    std::print("Vector after middle insert: ");
    for(int x : v) std::print("{} ", x);
    std::println("");

    // Example with set
    std::set<int> s = {1, 5};
    std::vector<int> extras = {2, 3, 4};
    std::copy(extras.begin(), extras.end(), std::inserter(s, s.begin()));

    std::print("Set after insert: ");
    for(int x : s) std::print("{} ", x);
    std::println("\n");
}

/**
 * 4. PERFORMANCE PITFALL
 * back_inserter is generally faster than inserter for vectors 
 * because it avoids shifting elements (unless reallocation occurs).
 */
void demo_performance_notes() {
    std::println("--- 4. Production Performance Notes ---");
    std::println("- std::back_inserter: Amortized O(1) for vectors.");
    std::println("- std::inserter: O(N) for vectors (due to shifting), but O(log N) or O(1) hint for sets.");
    std::println("- std::front_inserter: O(1) but only for deque/list.");
    std::println("- Crucial: Always reserve() space in vector before using back_inserter if count is known.\n");
}

int main() {
    std::println("C++23 Insert Iterators Deep Dive\n");

    demo_back_inserter();
    demo_front_inserter();
    demo_general_inserter();
    demo_performance_notes();

    std::println("--- Interview Summary ---");
    std::println("Q: Why use std::back_inserter instead of just v.begin() in std::copy?");
    std::println("A: Because v.begin() overwrites existing memory. If the container is empty, it's a crash.");
    std::println("   back_inserter calls push_back(), ensuring the container grows to accommodate the data.");
    
    return 0;
}
