/*
Title: std::mdspan Complete Guide (C++23)
Category: Sequence Containers (Views)
File: mdspan_cpp23.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
A comprehensive guide to std::mdspan, a non-owning multidimensional view over a contiguous 
range. Covers layouts, accessors, and multidimensional operator[].

Compile:
g++ -std=c++23 mdspan_cpp23.cpp -o mdspan_cpp23

Run:
./mdspan_cpp23

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Multidimensional views over flat memory
- Extents (static and dynamic)
- Layouts (layout_left, layout_right, layout_stride)
- Multidimensional operator[] (C++23 feature)
- Production Use Cases: Scientific computing, Image processing, Tensors

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <array>
#include <print>

// Note: std::mdspan is a C++23 feature. 
// Some compilers may require a specific header or be in the experimental stage.
// For GCC 13+ and Clang 16+, it's in <mdspan>.
#if __has_include(<mdspan>)
#include <mdspan>
#define HAS_MDSPAN 1
#else
#define HAS_MDSPAN 0
#endif

#if HAS_MDSPAN
/**
 * @brief Demonstrates basic mdspan usage with 2D mapping.
 */
void basic_2d_mdspan() {
    std::println("--- 2D mdspan Basics ---");
    
    // Flat data representing a 3x4 matrix
    std::vector<int> data(12);
    for (int i = 0; i < 12; ++i) data[i] = i;
    
    // Create a 2D mdspan (3 rows, 4 columns)
    // std::mdspan<element_type, extents<types...>, layout, accessor>
    auto ms = std::mdspan(data.data(), 3, 4);
    
    std::println("Matrix (3x4):");
    for (size_t i = 0; i < ms.extent(0); ++i) {
        for (size_t j = 0; j < ms.extent(1); ++j) {
            // Using C++23 multidimensional operator[]
            std::print("{:2d} ", ms[i, j]);
        }
        std::println("");
    }
}

/**
 * @brief Shows static vs dynamic extents.
 */
void static_vs_dynamic() {
    std::println("\n--- Static vs Dynamic Extents ---");
    
    int data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // Static extents: size is part of the type (3x3)
    using static_extents = std::extents<size_t, 3, 3>;
    std::mdspan<int, static_extents> m_static(data);
    
    std::println("Static 3x3 middle element [1,1]: {}", m_static[1, 1]);
    
    // Dynamic extents: size is provided at runtime
    std::mdspan m_dynamic(data, 3, 3);
    std::println("Dynamic 3x3 middle element [1,1]: {}", m_dynamic[1, 1]);
}

/**
 * @brief Explains Layouts (Row-major vs Column-major).
 */
void layout_demonstration() {
    std::println("\n--- Layout Demonstration ---");
    
    int data[4] = {1, 2, 3, 4};
    
    // layout_right (default, C-style, row-major)
    auto m_right = std::mdspan<int, std::extents<size_t, 2, 2>, std::layout_right>(data);
    
    // layout_left (Fortran-style, column-major)
    auto m_left = std::mdspan<int, std::extents<size_t, 2, 2>, std::layout_left>(data);
    
    std::println("Data: [1, 2, 3, 4]");
    std::println("layout_right [0,1]: {} (expected 2)", m_right[0, 1]);
    std::println("layout_left  [0,1]: {} (expected 3)", m_left[0, 1]);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Non-owning: Like std::span, mdspan does not own the memory. Do not let the underlying buffer go out of scope.");
    std::println("2. C++23 operator[]: This is a major syntax improvement. Instead of m[i][j], we now use m[i, j].");
    std::println("3. Abstraction: mdspan allows you to write generic algorithms that work on any multidimensional data (images, tensors) regardless of their memory layout.");
    std::println("4. Performance: Zero-overhead. The compiler optimizes index calculations to direct memory access.");
}
#endif

int main() {
#if HAS_MDSPAN
    try {
        basic_2d_mdspan();
        static_vs_dynamic();
        layout_demonstration();
        interview_notes();
    } catch (...) {
        std::println("An error occurred during mdspan demonstration.");
    }
#else
    std::println("std::mdspan is not supported by this compiler yet.");
#endif
    return 0;
}
