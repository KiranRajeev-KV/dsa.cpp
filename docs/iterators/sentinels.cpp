/*
Title: Sentinels in C++23 Guide
Category: Iterators / Ranges
File: sentinels.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
Explains the concept of sentinels which decouple the end of a range from its iterator type.
Essential for understanding modern Ranges and efficient null-termination handling.

Compile:
g++ -std=c++23 sentinels.cpp -o sentinels

Run:
./sentinels

Key Topics:
- What is a Sentinel? (std::sentinel_for)
- Mismatched Types: Iterator != Sentinel
- Implementing a Null-Terminated String Sentinel
- "Until" logic in ranges
- Performance benefits of sentinels

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <ranges>
#include <print>

/**
 * 1. THE NULL-TERMINATOR SENTINEL
 * Classic example: Iterating a C-style string without knowing its length upfront.
 * The 'end' isn't an iterator, it's a condition (char == '\0').
 */
struct NullTerminator {
    // Equality operator defines the termination condition
    friend bool operator==(auto it, NullTerminator) {
        return *it == '\0';
    }
};

void demo_custom_sentinel() {
    std::println("--- 1. Custom Null-Terminator Sentinel ---");
    const char* str = "Hello C++23";

    // We can define a range using a pointer and our custom sentinel
    auto range = std::ranges::subrange(str, NullTerminator{});

    std::print("Iterating with sentinel: ");
    for (char c : range) {
        std::print("{} ", c);
    }
    std::println("\n");
}

/**
 * 2. C++23 std::views::take_while
 * This view effectively uses a sentinel logic under the hood.
 */
void demo_conditional_sentinel() {
    std::println("--- 2. Conditional Termination (Sentinels) ---");
    std::vector<int> nums = {1, 2, 3, 0, 4, 5};

    // Stop when we hit a zero
    auto until_zero = nums | std::views::take_while([](int n) { return n != 0; });

    std::print("Until zero: ");
    for (int n : until_zero) std::print("{} ", n);
    std::println("\n");
}

/**
 * 3. WHY SENTINELS?
 * Efficiency: You don't need to calculate the end() iterator upfront.
 * For example, if you are reading from a network stream, you don't know the end 
 * until you see a specific packet.
 */
void demo_sentinel_concept() {
    std::println("--- 3. The std::sentinel_for Concept ---");
    
    // In C++20/23, std::ranges::begin() and std::ranges::end() 
    // are NOT required to return the same type.
    
    using It = const char*;
    using Sen = NullTerminator;
    
    static_assert(std::sentinel_for<Sen, It>, "NullTerminator is a valid sentinel for char*");
    
    std::println("Concept check: NullTerminator is a valid sentinel for const char*.\n");
}

/**
 * 4. PERFORMANCE IMPACT
 * Comparison:
 * - Traditional: strlen(s) -> O(N) then iterate -> O(N). Total O(2N).
 * - Sentinel: Iterate until '\0' -> O(N). Total O(N).
 */
void demo_performance_notes() {
    std::println("--- 4. Performance & Design Notes ---");
    std::println("- Sentinels allow for 'lazy' end-detection.");
    std::println("- They enable infinite ranges (e.g., std::views::iota) to have an unreachable sentinel.");
    std::println("- Advanced Tip: std::unreachable_sentinel_t can be used for optimized loops where "
                 "the programmer guarantees the end will never be reached or checked.");}

int main() {
    std::println("C++23 Sentinels Exploration\n");

    demo_custom_sentinel();
    demo_conditional_sentinel();
    demo_sentinel_concept();
    demo_performance_notes();

    std::println("\n--- Summary ---");
    std::println("Iterators represent 'Where you are'.");
    std::println("Sentinels represent 'When to stop'.");
    std::println("Modern C++ allows these to be different types for maximum flexibility.");

    return 0;
}
