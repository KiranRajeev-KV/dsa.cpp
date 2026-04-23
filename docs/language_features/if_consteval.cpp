/*
Title: If Consteval Complete Guide
Category: Language Features
File: if_consteval.cpp
C++ Standard: C++23
Difficulty: Intermediate

Purpose:
Detailed exploration of C++23 `if consteval`, its comparison with C++20 `std::is_constant_evaluated()`, and its role in providing optimized compile-time vs run-time paths.

Compile:
g++ -std=c++23 if_consteval.cpp -o if_consteval

Run:
./if_consteval

Key Topics:
- `if consteval` (C++23)
- `if ! consteval` (C++23)
- `std::is_constant_evaluated()` (C++20, and why it's superseded)
- Providing optimized paths for math/algorithms

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <type_traits>
#include <cmath>

// --- Optimized Math Example ---
// We want a fast version for runtime (using SIMD or specialized HW)
// and a constexpr version for compile-time (using basic arithmetic).
constexpr double power(double base, int exp) {
    // C++23: if consteval
    // This is a block-level check.
    if consteval {
        // Compile-time path: recursive multiplication
        if (exp == 0) return 1.0;
        if (exp < 0) return 1.0 / power(base, -exp);
        return base * power(base, exp - 1);
    } else {
        // Run-time path: use highly optimized std::pow
        std::println("[LOG] Executing optimized runtime path");
        return std::pow(base, exp);
    }
}

// C++23 also supports negated check
constexpr void check_context() {
    if ! consteval {
        std::println("This is definitely NOT a constant evaluation context.");
    }
}

// Comparison with C++20 std::is_constant_evaluated()
constexpr int legacy_check() {
    // Pitfall: std::is_constant_evaluated() returns a bool.
    // In an 'if' statement, the condition itself is evaluated.
    // This often leads to confusion in nested constexpr contexts.
    if (std::is_constant_evaluated()) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    std::println("--- C++23 if consteval ---\n");

    // 1. Compile-time evaluation
    constexpr double val_ct = power(2.0, 10);
    static_assert(val_ct == 1024.0);
    std::println("2^10 (compile-time): {}", val_ct);

    // 2. Run-time evaluation
    double b = 2.0;
    int e = 10;
    double val_rt = power(b, e);
    std::println("2^10 (run-time): {}", val_rt);

    check_context();

    return 0;
}

/*
Complexity & Performance Notes:
- `if consteval` has ZERO runtime overhead for the check itself when evaluated at compile-time. At runtime, the branch is just a normal branch, though often easily predictable by the CPU.
- It allows library authors to provide "slow but correct" compile-time implementations and "fast, hardware-accelerated" runtime versions of the same function.

Interview Pitfalls:
- `if consteval` is a STATEMENT, not an expression. It doesn't have a boolean value you can store.
- Why C++23 added `if consteval`? Because `if (std::is_constant_evaluated())` interacts poorly with `if constexpr`. Specifically, `if constexpr (std::is_constant_evaluated())` is ALWAYS true because the call itself is a constant expression, even if the surrounding function isn't being evaluated as one! `if consteval` fixes this ambiguity.
*/
