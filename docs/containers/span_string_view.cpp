/*
Title: std::span and std::string_view Complete Guide
Category: Sequence Containers (Views)
File: span_string_view.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to non-owning views: std::span and std::string_view.
Covers performance benefits, safety, and C++23 enhancements.

Compile:
g++ -std=c++23 span_string_view.cpp -o span_string_view

Run:
./span_string_view

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Non-owning semantics
- std::string_view for efficient string handling
- std::span for contiguous memory (arrays, vectors)
- C++23 improvements: span from range, string_view contains
- Bounds safety and lifetime pitfalls

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <string_view>
#include <span>
#include <vector>
#include <array>
#include <print>
#include <string>

/**
 * @brief Demonstrates std::string_view for zero-copy string processing.
 */
void string_view_demonstration() {
    std::println("--- String View Basics ---");
    std::string s = "Hello C++23 World";
    
    // No allocation here
    std::string_view sv = s;
    
    // Efficient substring (still no allocation)
    std::string_view sub = sv.substr(0, 5);
    std::println("Substring: '{}'", sub);
    
    // C++23 contains
    if (sv.contains("C++23")) {
        std::println("sv contains C++23");
    }
}

/**
 * @brief Demonstrates std::span for viewing contiguous data.
 */
void print_ints(std::span<const int> data) {
    std::print("Span elements: ");
    for (int n : data) {
        std::print("{} ", n);
    }
    std::println("");
}

void span_demonstration() {
    std::println("\n--- Span Basics ---");
    
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> v = {10, 20, 30};
    std::array<int, 3> a = {100, 200, 300};
    
    // span can view raw arrays, vectors, and std::arrays
    print_ints(arr);
    print_ints(v);
    print_ints(a);
    
    // Subspans
    std::span<int> full_span(arr);
    auto first_three = full_span.first(3);
    std::print("First three: ");
    for(int n : first_three) std::print("{} ", n);
    std::println("");
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. LIFETIME DANGER: Views do NOT own the data. If the underlying container is destroyed, the view becomes a dangling pointer. Never return a string_view to a local std::string.");
    std::println("2. string_view is NOT null-terminated: Do NOT pass `sv.data()` to functions expecting a C-string (like `printf(\"%s\")`) unless you know the length.");
    std::println("3. Performance: Use views in function parameters to avoid unnecessary copies and to accept multiple container types (e.g., span accepts both vector and array).");
    std::println("4. span vs const vector&: span is more flexible as it can point to a subset of data or even a raw memory buffer.");
}

int main() {
    string_view_demonstration();
    span_demonstration();
    interview_notes();
    return 0;
}
