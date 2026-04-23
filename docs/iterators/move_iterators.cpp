/*
Title: Move Iterators Complete Guide
Category: Iterators
File: move_iterators.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Demonstrates how move iterators turn element access into moves rather than copies.
Crucial for performance when transferring large objects or move-only types between containers.

Compile:
g++ -std=c++23 move_iterators.cpp -o move_iterators

Run:
./move_iterators

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::move_iterator adapter
- std::make_move_iterator utility
- Moving vs. Copying large objects
- Working with move-only types (std::unique_ptr)
- Performance implications (ownership transfer)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <print>
#include <iterator>

/**
 * A heavy class to demonstrate move benefits
 */
struct BigData {
    std::string name;
    std::vector<int> data;

    BigData(std::string n) : name(n), data(1000, 42) {}
    
    // Log move construction
    BigData(BigData&& other) noexcept : name(std::move(other.name)), data(std::move(other.data)) {
        // std::println("Log: Moved BigData '{}'", name);
    }
    
    // Delete copy to ensure we only move
    BigData(const BigData&) = delete;
    BigData& operator=(const BigData&) = delete;
    BigData& operator=(BigData&&) = default;
};

/**
 * 1. BASIC MOVE ITERATOR
 * Moving elements from one vector to another.
 */
void demo_move_iterator() {
    std::println("--- 1. Basic Move Iterator ---");
    
    std::vector<std::string> source = {"apple", "banana", "cherry"};
    
    // Using make_move_iterator to transfer strings without copying their buffers
    std::vector<std::string> dest(
        std::make_move_iterator(source.begin()),
        std::make_move_iterator(source.end())
    );

    std::println("Dest: {}, {}, {}", dest[0], dest[1], dest[2]);
    
    // Note: Source elements are now in a "valid but unspecified" state (usually empty for strings)
    std::println("Source after move: '{}', '{}', '{}'\n", source[0], source[1], source[2]);
}

/**
 * 2. MOVING MOVE-ONLY TYPES
 * move_iterators are the ONLY way to transfer std::unique_ptr using range constructors.
 */
void demo_move_only_types() {
    std::println("--- 2. Moving Move-Only Types (unique_ptr) ---");
    
    std::vector<std::unique_ptr<int>> source;
    source.push_back(std::make_unique<int>(10));
    source.push_back(std::make_unique<int>(20));

    // This would fail if we didn't use move iterators because unique_ptr cannot be copied
    std::vector<std::unique_ptr<int>> dest(
        std::make_move_iterator(source.begin()),
        std::make_move_iterator(source.end())
    );

    std::println("Dest contains: {}, {}", *dest[0], *dest[1]);
    std::println("Source contains: {}, {}\n", 
        source[0] ? "valid" : "null", 
        source[1] ? "valid" : "null");
}

/**
 * 3. MOVE VS COPY PERFORMANCE
 * Conceptually: O(1) per element move vs O(M) per element copy (where M is internal buffer size).
 */
void demo_performance_logic() {
    std::println("--- 3. Performance Logic ---");
    std::println("- std::move_iterator wraps a normal iterator.");
    std::println("- operator* returns an rvalue reference (T&&) instead of an lvalue reference (T&).");
    std::println("- Result: std::copy behaves like std::move for each element.");
}

int main() {
    std::println("C++23 Move Iterators Exploration\n");

    demo_move_iterator();
    demo_move_only_types();
    demo_performance_logic();

    std::println("\n--- Production Notes ---");
    std::println("1. Post-condition: After using move_iterators, the source container remains valid but its elements are 'empty'.");
    std::println("2. Algorithm Compatibility: Many STL algorithms (std::copy, std::transform) work perfectly with move iterators.");
    std::println("3. Safety: Never access source elements after a move-iterator range operation unless you re-initialize them.");
    
    return 0;
}
