/*
Title: Fast I/O in C++23 for Competitive Programming
Category: Competitive Programming
File: fast_io.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Demonstrates high-performance input/output techniques in modern C++23.
Covers traditional optimizations (ios_base::sync_with_stdio), C-style I/O, 
and the new C++23 std::print/std::println for formatted output.

Compile:
g++ -std=c++23 fast_io.cpp -o fast_io

Run:
./fast_io

Key Topics:
- ios_base::sync_with_stdio(false) and cin.tie(nullptr)
- std::print and std::println (C++23)
- Fast integer parsing
- Output buffering with '\n' vs std::endl
- Benchmarking different I/O methods

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdio>
#include <print>

/**
 * Competitive Programming I/O Fundamentals:
 * 
 * 1. sync_with_stdio(false):
 *    Disables the synchronization between C++ standard streams and their 
 *    corresponding C standard streams. This significantly speeds up cin/cout.
 * 
 * 2. cin.tie(nullptr):
 *    Unties cin from cout. By default, cin flushes cout before every read.
 *    Untying them prevents unnecessary flushes during heavy I/O.
 * 
 * 3. '\n' vs std::endl:
 *    std::endl inserts a newline AND flushes the buffer. 
 *    '\n' only inserts a newline. Flushing is expensive.
 */

namespace fast_io_demo {

    // A simple timer for benchmarking
    struct Timer {
        std::chrono::high_resolution_clock::time_point start;
        std::string name;
        Timer(std::string n) : name(n) {
            start = std::chrono::high_resolution_clock::now();
        }
        ~Timer() {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::println(stderr, "[{}] took {} ms", name, duration);
        }
    };

    /**
     * Fast Integer Input:
     * For extremely tight constraints, manual parsing can be faster than cin.
     */
    template <typename T>
    void read_int(T& x) {
        x = 0;
        T f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-') f = -1;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + ch - '0';
            ch = getchar();
        }
        x *= f;
    }

    /**
     * C++23 std::print / std::println:
     * These are generally faster than std::cout because they don't have
     * the overhead of locale-dependent formatting and stream state management.
     * They are comparable to or faster than printf.
     */
    void demonstrate_cpp23_io() {
        std::println("\n--- C++23 std::print/println Demo ---");
        int score = 42;
        double pi = 3.14159265;
        std::string name = "Competitive C++";

        // Formatted output (like Python f-strings or Rust println!)
        std::println("Hello, {}! Your score is {} and PI is {:.4f}", name, score, pi);
        
        // Printing to stderr
        std::println(stderr, "This is an error message (useful for debugging in CP)");
    }
}

int main() {
    // Standard CP optimization
    // Note: Do not mix cin/cout with scanf/printf after this!
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    fast_io_demo::demonstrate_cpp23_io();

    std::println("\n--- Performance Comparison (Conceptual) ---");
    std::println("1. std::println (C++23): Fast, type-safe, and modern.");
    std::println("2. printf/scanf: Fast but not type-safe.");
    std::println("3. std::cin/std::cout (optimized): Sufficient for 99% of CP problems.");
    std::println("4. Custom readInt: Only for the most extreme I/O limits.");

    std::println("\n--- Interview Pitfalls ---");
    std::println("- Mixing synchronized and unsynchronized I/O leads to undefined output order.");
    std::println("- Using std::endl in a loop is a common cause of TLE (Time Limit Exceeded).");
    std::println("- Forgetting to tie(nullptr) when using cin and cout together.");

    return 0;
}
