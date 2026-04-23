/*
Title: std::expected Complete Guide
Category: Language Features
File: expected_cpp23.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
A comprehensive guide to `std::expected<T, E>`, a vocabulary type for error handling. It represents either a value or an error, similar to Rust's Result.

Compile:
g++ -std=c++23 expected_cpp23.cpp -o expected_cpp23

Run:
./expected_cpp23

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- `std::expected` basics
- `std::unexpected`
- Monadic operations: `and_then`, `or_else`, `transform`
- Error handling without exceptions

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <expected>
#include <string>

// --- Error Codes ---
enum class MathError {
    DivisionByZero,
    NegativeLogarithm,
    NegativeRoot
};

std::string to_string(MathError e) {
    switch(e) {
        case MathError::DivisionByZero: return "Division by Zero";
        case MathError::NegativeLogarithm: return "Negative Logarithm";
        case MathError::NegativeRoot: return "Negative Root";
        default: return "Unknown Error";
    }
}

// --- 1. Basic usage of std::expected ---
std::expected<double, MathError> safe_divide(double a, double b) {
    if (b == 0) {
        return std::unexpected(MathError::DivisionByZero);
    }
    return a / b;
}

// --- 2. Monadic Operations (C++23) ---
// We can chain operations cleanly.
std::expected<double, MathError> complex_calculation(double input) {
    return safe_divide(10.0, input)
        .and_then([](double val) -> std::expected<double, MathError> {
            if (val < 0) return std::unexpected(MathError::NegativeRoot);
            return val * 2.0;
        })
        .transform([](double val) {
            return val + 1.0; // transform applies to the value if present
        });
}

int main() {
    std::println("--- C++23 std::expected ---\n");

    // Scenario 1: Success
    auto res1 = complex_calculation(2.0); // 10/2 = 5 -> 5*2 = 10 -> 10+1 = 11
    if (res1) {
        std::println("Result 1: {}", *res1);
    }

    // Scenario 2: Division by Zero
    auto res2 = complex_calculation(0.0);
    if (!res2) {
        std::println("Result 2 Error: {}", to_string(res2.error()));
    }

    // Scenario 3: Negative Result
    auto res3 = complex_calculation(-1.0); // 10/-1 = -10 -> and_then returns NegativeRoot
    if (!res3) {
        std::println("Result 3 Error: {}", to_string(res3.error()));
    }

    // value_or() helper
    double final_val = complex_calculation(0).value_or(-1.0);
    std::println("Final fallback value: {}", final_val);

    return 0;
}

/*
Complexity & Performance Notes:
- `std::expected` has similar overhead to `std::variant`. It usually adds 1 byte + alignment to the size of the larger of T or E.
- It is significantly faster than exceptions for "expected" errors because it doesn't require stack unwinding or RTTI.

Interview Pitfalls:
- **Monadic Operations**: C++23 adds `.and_then()`, `.transform()`, and `.or_else()`. In an interview, using these shows you understand modern functional patterns in C++.
- `std::expected` is NOT a replacement for all exceptions. Use it for errors that are part of the normal API contract (e.g., parsing, network timeouts). Use exceptions for truly exceptional, unrecoverable conditions.
- Forgetting to use `std::unexpected()` when returning an error. `return MathError::DivisionByZero;` will try to convert the error code to a `double` value!
*/
