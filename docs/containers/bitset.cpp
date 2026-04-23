/*
Title: std::bitset Complete Guide
Category: Sequence Containers (Specialized)
File: bitset.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::bitset, a fixed-size sequence of bits.
Covers bit manipulation, string conversions, and performance benefits for boolean flags.

Compile:
g++ -std=c++23 bitset.cpp -o bitset

Run:
./bitset

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Bitwise operations (&, |, ^, ~)
- set, reset, flip, test
- to_string, to_ulong, to_u64
- Performance: Space efficiency (1 bit per element)
- C++23: Improved string formatting

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <bitset>
#include <print>

/**
 * @brief Demonstrates basic bitset operations.
 */
void basic_operations() {
    std::println("--- Bitset Basics ---");
    std::bitset<8> b1("10101010");
    std::bitset<8> b2(0xAA); // same as above
    
    std::println("b1: {}", b1.to_string());
    
    // Bit manipulation
    b1.set(0); // Sets the 0-th bit (LSB)
    b1.reset(1); // Clears the 1-st bit
    b1.flip(7); // Flips the 7-th bit (MSB)
    
    std::println("Modified b1: {}", b1.to_string());
    std::println("b1 test(0): {}", b1.test(0));
    std::println("b1 all set? {}", b1.all());
    std::println("b1 any set? {}", b1.any());
}

/**
 * @brief Logical operations between bitsets.
 */
void logical_operations() {
    std::println("\n--- Logical Operations ---");
    std::bitset<4> a("1100");
    std::bitset<4> b("1010");
    
    std::println("a & b: {}", (a & b).to_string());
    std::println("a | b: {}", (a | b).to_string());
    std::println("a ^ b: {}", (a ^ b).to_string());
    std::println("~a:    {}", (~a).to_string());
}

/**
 * @brief Conversion to and from numeric types.
 */
void conversions() {
    std::println("\n--- Conversions ---");
    std::bitset<16> b(42);
    
    unsigned long val = b.to_ulong();
    std::println("Numeric value: {}", val);
    
    std::bitset<64> large(0xDEADBEEFCAFEBABEULL);
    std::println("Large bitset: {}", large.to_string());
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Fixed Size: Unlike std::vector<bool>, bitset size must be known at compile-time.");
    std::println("2. Bit ordering: Index 0 is the Least Significant Bit (LSB), usually the rightmost bit in string representation.");
    std::println("3. Performance: Very efficient for boolean arrays. Uses bit-packing (1 bit per element) which saves significant memory compared to bool[N] (1 byte per element).");
    std::println("4. bounds check: operator[] does not check bounds; test() does.");
}

/**
 * @brief Complexity:
 * - Most operations: O(N/word_size) - very fast bitwise instructions.
 * - Space: O(N) bits.
 */
int main() {
    basic_operations();
    logical_operations();
    conversions();
    interview_notes();
    return 0;
}
