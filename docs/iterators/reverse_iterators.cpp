/*
Title: Reverse Iterators Complete Guide
Category: Iterators
File: reverse_iterators.cpp
C++ Standard: C++23
Difficulty: Intermediate

Purpose:
A comprehensive guide to traversing containers in reverse using reverse_iterators.
Explains the logical mapping between rbegin/rend and the base iterator.

Compile:
g++ -std=c++23 reverse_iterators.cpp -o reverse_iterators

Run:
./reverse_iterators

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::reverse_iterator adapter
- rbegin(), rend(), crbegin(), crend()
- The relationship: it.base()
- Inserting/Erasing with reverse iterators (The off-by-one mapping)
- Use cases in algorithms (reverse searching)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <print>
#include <iterator>

/**
 * 1. BASIC REVERSE TRAVERSAL
 */
void demo_reverse_traversal() {
    std::println("--- 1. Basic Reverse Traversal ---");
    std::vector<int> v = {1, 2, 3, 4, 5};

    std::print("Vector in reverse: ");
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
        std::print("{} ", *rit);
    }
    std::println("\n");
}

/**
 * 2. REVERSE ITERATOR MAPPING (.base())
 * Crucial Concept: A reverse iterator points to the element *before* its base.
 * why? Because rend() needs to be conceptually "before" the first element.
 */
void demo_base_conversion() {
    std::println("--- 2. The .base() Relationship ---");
    std::vector<int> v = {10, 20, 30, 40, 50};

    // Find '30' using a reverse iterator
    auto rit = std::find(v.rbegin(), v.rend(), 30);
    
    // Get the base iterator (regular forward iterator)
    auto bit = rit.base();

    std::println("Reverse iterator points to: {}", *rit);
    std::println("Base iterator points to: {}", *bit); 
    // Wait! bit points to 40, not 30! This is by design.
    
    std::println("Mapping Note: &*rit == &*(bit - 1)");
    std::println("Element pointed to by rit is physically one before bit.\n");
}

/**
 * 3. PRACTICAL USE: ERASING WITH REVERSE ITERATORS
 * To erase using a reverse iterator, you must convert it to a base iterator correctly.
 */
void demo_erase_with_reverse() {
    std::println("--- 3. Erasing with Reverse Iterators ---");
    std::vector<int> v = {1, 2, 3, 4, 5};

    // We want to find the first '4' from the back and erase it
    auto rit = std::find(v.rbegin(), v.rend(), 4);

    if (rit != v.rend()) {
        // v.erase(rit); // Error: erase takes a normal iterator
        
        // Correct way to erase the element pointed to by rit:
        // Use std::next(rit).base() OR rit.base() - 1
        v.erase(std::next(rit).base());
    }

    std::print("After erasing 4 from back: ");
    for (int x : v) std::print("{} ", x);
    std::println("\n");
}

/**
 * 4. REVERSE ADAPTER
 * How to make any bidirectional iterator reverse.
 */
void demo_reverse_adapter() {
    std::println("--- 4. std::reverse_iterator Adapter ---");
    std::vector<int> v = {100, 200, 300};
    
    // Manually create a reverse iterator from a forward one
    std::reverse_iterator<std::vector<int>::iterator> rit(v.end());
    
    std::println("Reverse beginning: {}", *rit); // Points to 300
    std::println("");
}

int main() {
    std::println("C++23 Reverse Iterators Mastery\n");

    demo_reverse_traversal();
    demo_base_conversion();
    demo_erase_with_reverse();
    demo_reverse_adapter();

    std::println("--- Interview & Production Notes ---");
    std::println("1. Memory Layout: Reverse iterators don't change the container, just how you step through it.");
    std::println("2. Efficiency: ++rit on a reverse iterator is physically --it on the base iterator.");
    std::println("3. Pitfall: The off-by-one shift between rit and rit.base() is the most common bug source.");
    std::println("4. Requirement: To have a reverse iterator, the container must provide Bidirectional Iterators.");
    
    return 0;
}
