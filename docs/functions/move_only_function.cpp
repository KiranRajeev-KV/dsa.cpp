/*
Title: std::move_only_function Complete Guide (C++23)
Category: Functional Programming
File: move_only_function.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
Detailed guide to std::move_only_function, a C++23 feature that addresses the 
limitations of std::function by supporting move-only callable objects.

Compile:
g++ -std=c++23 move_only_function.cpp -o move_only_function

Run:
./move_only_function

Key Topics:
- std::function vs std::move_only_function
- Capturing move-only types (std::unique_ptr)
- Const-correctness and ref-qualifiers
- Performance benefits (no copy requirement)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <functional>
#include <memory>
#include <print>

/**
 * Why std::move_only_function?
 * 1. std::function requires the callable to be CopyConstructible.
 * 2. Lambdas that capture move-only types (like unique_ptr) are NOT copyable.
 * 3. Therefore, std::function cannot wrap such lambdas.
 * 4. std::move_only_function only requires the callable to be MoveConstructible.
 */

void problem_with_std_function() {
    std::println("--- The Problem with std::function ---");

    auto ptr = std::make_unique<int>(42);
    auto lambda = [p = std::move(ptr)]() {
        if (p) return *p;
        return 0;
    };

    // This would NOT compile:
    // std::function<int()> f = std::move(lambda); 
    // Error: std::function requires copyability.

    std::println("std::function cannot wrap lambdas capturing unique_ptr.");
}

void solution_with_move_only_function() {
    std::println("\n--- The Solution: std::move_only_function ---");

    auto ptr = std::make_unique<int>(1337);
    
    // Lambda capturing a move-only type
    auto lambda = [p = std::move(ptr)]() {
        return (p ? *p : 0);
    };

    // C++23 move_only_function
    std::move_only_function<int()> mo_func = std::move(lambda);

    if (mo_func) {
        std::println("Result: {}", mo_func());
    }

    // mo_func itself is move-only!
    std::move_only_function<int()> mo_func2 = std::move(mo_func);
    // mo_func is now empty.
    std::println("Moved move_only_function, result: {}", mo_func2());
}

/**
 * Advanced Syntax:
 * std::move_only_function supports cv-qualifiers and ref-qualifiers in its 
 * signature, which std::function does not.
 */
void const_correctness() {
    std::println("\n--- Const and Ref Qualifiers ---");

    // Can only call on a const instance
    std::move_only_function<void() const> f_const = []() {
        std::println("Called a const move_only_function");
    };
    f_const();

    // Can only call on an rvalue instance (useful for one-shot functions)
    std::move_only_function<void() &&> f_rvalue = []() {
        std::println("Called an rvalue move_only_function");
    };
    std::move(f_rvalue)();
}

/**
 * Performance Note:
 * std::move_only_function is generally more efficient than std::function 
 * because it doesn't need to support copying. This means:
 * - No need to manage reference counting or deep copies of closures.
 * - Potentially better SOO (Small Object Optimization) usage.
 */

int main() {
    try {
        problem_with_std_function();
        solution_with_move_only_function();
        const_correctness();
    } catch (const std::exception& e) {
        std::println(stderr, "Fatal: {}", e.what());
        return 1;
    }
    return 0;
}

/**
 * Complexity Analysis:
 * - Construction: O(1) if small (SOO), O(1) heap allocation if large.
 * - Move: O(1).
 * - Invocation: O(1) with one level of indirection (type erasure).
 * - Space: sizeof(std::move_only_function) + potential heap allocation.
 */
