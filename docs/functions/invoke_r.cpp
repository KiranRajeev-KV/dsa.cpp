/*
Title: std::invoke_r Complete Guide (C++23)
Category: Functional Programming
File: invoke_r.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
Explains std::invoke_r, a C++23 utility for invoking callables with an explicit 
return type conversion. Useful in generic programming and template metaprogramming.

Compile:
g++ -std=c++23 invoke_r.cpp -o invoke_r

Run:
./invoke_r

Key Topics:
- std::invoke (C++17) vs std::invoke_r (C++23)
- Explicit return type conversion
- Handling void return types
- Generic wrappers using invoke_r

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <functional>
#include <print>

/**
 * std::invoke_r<R>(f, args...) invokes f with args... and converts the result 
 * to type R.
 * 
 * It is equivalent to:
 * return static_cast<R>(std::invoke(f, std::forward<Args>(args)...));
 * 
 * Special case: If R is void, the result of the invocation is discarded.
 */

int get_int() { return 42; }
double get_double() { return 3.14159; }

struct Adder {
    int val;
    int add(int x) const { return val + x; }
};

void basic_invoke_r() {
    std::println("--- Basic std::invoke_r ---");

    // 1. Convert int to double
    double d = std::invoke_r<double>(get_int);
    std::println("Invoked get_int as double: {}", d);

    // 2. Convert double to int (truncation)
    int i = std::invoke_r<int>(get_double);
    std::println("Invoked get_double as int: {}", i);

    // 3. Invoking member function
    Adder adder{10};
    long res = std::invoke_r<long>(&Adder::add, &adder, 5);
    std::println("Invoked member add as long: {}", res);
}

void invoke_r_with_void() {
    std::println("\n--- std::invoke_r with void ---");

    // Useful when you want to ignore the return value of a function 
    // in a generic context where you expect void.
    std::invoke_r<void>(get_int);
    std::println("get_int invoked and return value discarded via void.");
}

/**
 * Real-world use case: Generic Wrapper
 * Suppose you want a function that logs and calls any callable, 
 * but you want to ensure the result is always converted to a specific type.
 */
template <typename R, typename F, typename... Args>
R logger_wrapper(F&& f, Args&&... args) {
    std::println("Logging: Calling function...");
    return std::invoke_r<R>(std::forward<F>(f), std::forward<Args>(args)...);
}

void generic_example() {
    std::println("\n--- Generic Wrapper Example ---");

    // This converts the integer 42 to a float via static_cast (inside invoke_r)
    auto float_res = logger_wrapper<float>([]() { return 42; });
    std::println("Wrapped result: {}", float_res);
}

/**
 * Why use std::invoke_r over static_cast(std::invoke)?
 * 1. Readability: Expresses intent clearly.
 * 2. Generic Programming: It handles the 'void' return case correctly, 
 *    which manual static_cast might not (you can't static_cast some expressions 
 *    to void as easily in all template contexts).
 * 3. SFINAE/Concepts: Useful in trailing return types and requirement blocks.
 */

int main() {
    try {
        basic_invoke_r();
        invoke_r_with_void();
        generic_example();
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
        return 1;
    }
    return 0;
}

/**
 * Complexity Analysis:
 * - Time: O(1) plus function call.
 * - Space: O(1).
 */
