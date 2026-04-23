/*
Title: Constexpr and Consteval Complete Guide
Category: Language Features
File: constexpr_consteval.cpp
C++ Standard: C++23
Difficulty: Intermediate

Purpose:
A comprehensive guide to compile-time programming using `constexpr`, `consteval`, and `constinit`, emphasizing C++23 improvements like non-literal types in unused constexpr paths.

Compile:
g++ -std=c++23 constexpr_consteval.cpp -o constexpr_consteval

Run:
./constexpr_consteval

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- `constexpr` functions and variables
- `consteval` (immediate functions, C++20)
- `constinit` (constant initialization, C++20)
- C++23 improvements in constexpr (relaxing literal types)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <string>
#include <vector>
#include <numeric>

// --- 1. constexpr (C++11/14/20/23) ---
// May be evaluated at compile-time OR run-time.
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}

// C++20 allowed std::vector and std::string in constexpr!
// The allocations must be freed before compile-time evaluation finishes.
constexpr int sum_vector(int n) {
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 1);
    int sum = 0;
    for (int x : v) sum += x;
    return sum;
}

// --- 2. consteval (C++20 Immediate Functions) ---
// MUST be evaluated at compile-time. If it cannot, it's a compile error.
consteval int square(int n) {
    return n * n;
}

// --- 3. constinit (C++20) ---
// Guarantees static initialization (no static initialization order fiasco),
// but the variable itself does NOT need to be const.
constinit int global_counter = factorial(3); // initialized at compile time to 6

// --- 4. C++23 Constexpr Improvements ---
// C++23 allows non-literal types in constexpr functions, as long as the
// control flow path executing them is not actually hit during compile-time evaluation.
struct NonLiteral {
    NonLiteral() { std::println("Runtime only!"); }
    ~NonLiteral() {}
};

constexpr int flexible_function(bool use_literal) {
    if (use_literal) {
        return 42;
    } else {
        // In C++20, declaring a non-literal type here made the whole function invalid for constexpr.
        // In C++23, it's perfectly fine as long as `use_literal == true` when evaluated at compile-time.
        NonLiteral nl;
        return 0;
    }
}

int main() {
    std::println("--- Constexpr and Consteval (C++23) ---\n");

    // Evaluated at compile-time
    constexpr int f5 = factorial(5);
    static_assert(f5 == 120, "Math is broken");
    std::println("Factorial 5: {}", f5);

    constexpr int vec_sum = sum_vector(10); // 1 to 10 sum is 55
    static_assert(vec_sum == 55);
    std::println("Vector sum (compile-time calculated): {}", vec_sum);

    // Evaluated at compile-time mandatory
    constexpr int sq = square(10);
    std::println("constexpr square(10) = {}", sq);
    // int runtime_val = 10;
    // int runtime_sq = square(runtime_val); // ERROR: runtime_val is not a constant expression

    global_counter++; // It's mutable!
    std::println("Global counter (constinit, mutated): {}", global_counter);

    // C++23 relaxed constexpr
    constexpr int flex_val = flexible_function(true); // OK: avoids non-literal path
    static_assert(flex_val == 42);
    
    // flexible_function(false); // OK at runtime! (Prints "Runtime only!")

    return 0;
}

/*
Complexity & Performance Notes:
- Compile-time evaluation pushes the computation cost to the compiler. Runtime cost is strictly O(1) (a literal value is baked into the binary).
- `constinit` solves the "Static Initialization Order Fiasco" by guaranteeing variables are initialized during compile-time/link-time rather than dynamically at runtime startup.

Interview Pitfalls:
- Forgetting that `constexpr` functions can run at RUNTIME if their arguments are not constant expressions. Use `consteval` if you want to explicitly forbid runtime evaluation.
- Memory allocated in a `constexpr` context (like `std::vector`) MUST be deallocated before the constant expression evaluation completes. You cannot return a `constexpr std::vector` from a function to the runtime world.
*/
