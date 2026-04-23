/*
Title: Iterator Basics Complete Guide
Category: Iterators
File: iterator_basics.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to understanding C++ iterators as the abstraction layer between 
containers and algorithms. Covers basic traversal, iterator types (const vs non-const), 
and the critical concept of iterator invalidation.

Compile:
g++ -std=c++23 iterator_basics.cpp -o iterator_basics

Run:
./iterator_basics

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- The Iterator Pattern abstraction
- Basic operators: *, ->, ++, --, ==, !=
- Member vs. non-member begin()/end()
- Const iterators and cbegin()/cend()
- Iterator invalidation pitfalls
- C++23 std::println for debugging

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <list>
#include <algorithm>
#include <print>

/**
 * 1. BASIC TRAVERSAL
 * Demonstrates the fundamental "loop" using iterators.
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
void demo_basic_traversal() {
    std::println("--- 1. Basic Traversal ---");
    std::vector<int> nums = {10, 20, 30, 40, 50};

    // The classic iterator loop
    std::println("Manual loop:");
    for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // Modern auto loop (under the hood this uses iterators)
    std::println("Range-based for loop (syntactic sugar for iterators):");
    for (const auto& val : nums) {
        std::print("{} ", val);
    }
    std::println("\n");
}

/**
 * 2. CONST ITERATORS
 * Crucial for const-correctness. const_iterators allow reading but not writing.
 */
void demo_const_iterators() {
    std::println("--- 2. Const Iterators ---");
    std::vector<int> v = {1, 2, 3};
    
    // cbegin/cend return const_iterator regardless of container const-ness
    auto it = v.cbegin();
    // *it = 10; // Error: cannot assign to a variable that is const
    
    std::println("First element (const): {}", *it);
    
    const std::vector<int> cv = {4, 5, 6};
    auto it2 = cv.begin(); // it2 is automatically const_iterator
    std::println("Const container element: {}\n", *it2);
}

/**
 * 3. ITERATOR INVALIDATION
 * One of the most common C++ interview questions and production bugs.
 */
void demo_invalidation() {
    std::println("--- 3. Iterator Invalidation ---");
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.begin() + 2; // Points to '3'

    std::println("Before push_back: it points to {}", *it);

    // DANGEROUS: push_back might trigger a reallocation
    // If reallocation happens, 'it' becomes a "dangling" pointer/iterator.
    for(int i=0; i<100; ++i) v.push_back(i); 

    std::println("WARNING: After push_back, 'it' might be invalid!");
    // Accessing *it here is Undefined Behavior (UB) if v reallocated.
    
    // CORRECT PATTERN: Re-acquire or use indices if modifications are frequent.
    it = v.begin() + 2; 
    std::println("After re-acquisition: it points to {}\n", *it);
}

/**
 * 4. ITERATOR VS POINTER
 * Iterators are objects that *act* like pointers but can have complex logic.
 */
void demo_iterator_vs_pointer() {
    std::println("--- 4. Iterator vs Pointer ---");
    int arr[] = {1, 2, 3};
    int* p = arr; // A raw pointer is a valid iterator for raw arrays
    
    std::vector<int> v = {4, 5, 6};
    std::vector<int>::iterator it = v.begin();

    std::println("Pointer access: {}", *p);
    std::println("Iterator access: {}", *it);
    
    // Note: In std::vector, iterators are often implemented as pointers, 
    // but in std::list, they are definitely class objects.
    std::list<int> l = {7, 8, 9};
    auto lit = l.begin();
    // int* lp = lit; // Error: Cannot convert list iterator to pointer
    std::println("List iterator access: {}\n", *lit);
}

int main() {
    try {
        std::println("C++23 Iterator Basics Exploration\n");
        
        demo_basic_traversal();
        demo_const_iterators();
        demo_invalidation();
        demo_iterator_vs_pointer();

        std::println("--- Summary & Production Notes ---");
        std::println("1. Prefer cbegin()/cend() when you don't need to modify elements.");
        std::println("2. Always be aware of invalidation rules (e.g., vector::push_back, list::erase).");
        std::println("3. Iterators provide a uniform interface for algorithms like std::sort.");
        std::println("4. Interview Tip: Explain that iterators are a 'generalization' of pointers.");

    } catch (const std::exception& e) {
        std::println("Error: {}", e.what());
    }
    
    return 0;
}
