/*
Title: std::bind_back Complete Guide (C++23)
Category: Functional Programming
File: bind_back_cpp23.cpp
C++ Standard: C++23
Difficulty: Intermediate

Purpose:
Demonstrates the use of std::bind_back, a C++23 feature for partial function 
application by binding arguments to the END of a function's parameter list.

Compile:
g++ -std=c++23 bind_back_cpp23.cpp -o bind_back_cpp23

Run:
./bind_back_cpp23

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::bind_back vs std::bind_front (C++20)
- Partial application of last arguments
- Use cases in functional pipelines and ranges
- Comparison with Lambdas

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <functional>
#include <string>
#include <vector>
#include <print>

/**
 * std::bind_back(f, args...) returns a callable object that, when called 
 * with more arguments (call_args...), invokes f(call_args..., args...).
 * 
 * It is particularly useful for functions where the data to be processed 
 * is the first argument, and the configuration is the last.
 */

int power(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; ++i) res *= base;
    return res;
}

void demonstrate_bind_back() {
    std::println("--- std::bind_back Basic ---");

    // Bind the exponent (last argument) to 2
    auto square = std::bind_back(power, 2);
    // Bind the exponent to 3
    auto cube = std::bind_back(power, 3);

    std::println("Square of 5: {}", square(5)); // Equivalent to power(5, 2)
    std::println("Cube of 5: {}", cube(5));     // Equivalent to power(5, 3)
}

void multi_argument_bind_back() {
    std::println("\n--- Multi-argument bind_back ---");

    auto logger = [](std::string msg, std::string level, int code) {
        std::println("[{}] Code {}: {}", level, code, msg);
    };

    // Bind level and code (last two arguments)
    auto log_error_404 = std::bind_back(logger, "ERROR", 404);
    
    log_error_404("Page not found");
    log_error_404("Retry failed");
}

void ranges_integration_mock() {
    std::println("\n--- bind_back in Pipelines (Mock) ---");

    // Imagine a function that takes a range and a predicate
    auto filter_and_print = [](const std::vector<int>& vec, auto predicate) {
        for (int x : vec) {
            if (predicate(x)) std::print("{} ", x);
        }
        std::println();
    };

    std::vector<int> nums = {1, 2, 3, 4, 5, 6};

    // Bind the predicate
    auto only_evens = std::bind_back(filter_and_print, [](int x) { return x % 2 == 0; });
    
    std::print("Evens: ");
    only_evens(nums);
}

/**
 * Performance & Comparison:
 * 
 * bind_front (C++20) and bind_back (C++23) are often preferred over std::bind 
 * because they are simpler, don't require placeholders, and generally 
 * result in cleaner code.
 * 
 * However, a Lambda is still the most flexible tool:
 * auto square = [](int x) { return power(x, 2); };
 * 
 * bind_back is "functional candy" that makes partial application 
 * more expressive in certain contexts.
 */

int main() {
    try {
        demonstrate_bind_back();
        multi_argument_bind_back();
        ranges_integration_mock();
    } catch (const std::exception& e) {
        std::println(stderr, "Fatal error: {}", e.what());
        return 1;
    }
    return 0;
}

/**
 * Complexity Analysis:
 * - Space: O(N) to store N bound arguments.
 * - Time (Invocation): O(1) plus function call overhead.
 */
