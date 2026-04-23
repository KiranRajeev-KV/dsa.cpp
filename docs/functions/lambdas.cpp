/*
Title: Lambda Expressions Complete Guide
Category: Functional Programming
File: lambdas.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Comprehensive exploration of C++ lambda expressions, covering evolution from C++11 
to C++23. Includes capture modes, generic lambdas, template lambdas, recursive 
lambdas, and C++23 specific enhancements like static operator().

Compile:
g++ -std=c++23 lambdas.cpp -o lambdas

Run:
./lambdas

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Basic Syntax and Captures
- Mutable and Constexpr Lambdas
- Generic and Template Lambdas
- Capturing 'this' and '*this'
- C++23: static operator() in lambdas
- C++23: Attributes on lambdas
- Recursive lambdas (using deducing this)
- Performance and Optimization (Inlining vs std::function)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <print>

/**
 * Lambda Anatomy:
 * [capture-list] <template-params> (params) specifiers exception-ref ret-type { body }
 */

void basic_lambdas() {
    std::println("--- Basic Lambdas ---");
    
    // 1. Simple lambda
    auto greet = []() { std::println("Hello from Lambda!"); };
    greet();

    // 2. Lambda with parameters and return type
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    std::println("Sum: {}", add(10, 20));

    // 3. Captures
    int x = 10;
    int y = 20;

    // Capture by value [x]
    auto cap_val = [x]() { return x + 5; };
    
    // Capture by reference [&y]
    auto cap_ref = [&y]() { y += 10; };

    // Capture all by value [=], all by reference [&]
    auto cap_all_val = [=]() { return x + y; };
    auto cap_all_ref = [&]() { x++; y++; };
    (void)cap_val; (void)cap_all_val; (void)cap_all_ref;

    cap_ref();
    std::println("Captured y by ref, new y: {}", y);
    
    // C++14: Initialization captures (Generalized Lambda Captures)
    auto ptr = std::make_unique<int>(42);
    auto move_cap = [p = std::move(ptr)]() {
        if (p) std::println("Unique pointer value: {}", *p);
    };
    move_cap();
}

void advanced_features() {
    std::println("\n--- Advanced Lambda Features ---");

    // 1. Mutable lambdas: Allows modifying captured-by-value variables
    int count = 0;
    auto counter = [count]() mutable {
        return ++count;
    };
    std::println("Counter: {}, {}, {}", counter(), counter(), counter());
    std::println("Original count still: {}", count);

    // 2. Generic Lambdas (C++14)
    auto generic_add = [](auto a, auto b) { return a + b; };
    std::println("Generic Add (int): {}", generic_add(5, 5));
    std::println("Generic Add (string): {}", generic_add(std::string("A"), "B"));

    // 3. Template Lambdas (C++20)
    // Allows explicit template parameters for better type control
    auto process_vector = []<typename T>(const std::vector<T>& vec) {
        std::println("Processing vector of size {}", vec.size());
    };
    process_vector(std::vector<int>{1, 2, 3});

    // 4. Constexpr Lambdas (C++17)
    constexpr auto square = [](int n) { return n * n; };
    static_assert(square(5) == 25);
}

struct MemberLambda {
    int value = 42;

    void demonstrate() {
        // Capture 'this' by reference
        auto ref_this = [this]() { value += 1; };
        
        // Capture '*this' by value (C++17) - copies the whole object
        // Essential for asynchronous operations to avoid use-after-free
        auto val_this = [*this]() { std::println("Value in copy: {}", value); };

        ref_this();
        val_this();
    }
};

void cpp23_features() {
    std::println("\n--- C++23 Lambda Enhancements ---");

    // 1. Static call operator (C++23)
    // If a lambda doesn't capture anything, its operator() can be static.
    // This can improve performance and reduces the closure object size.
    auto static_lambda = []() static {
        return 42;
    };
    std::println("Static lambda result: {}", static_lambda());

    // 2. Attributes on Lambdas (C++23)
    // You can now apply attributes directly to the lambda
    auto attributed_lambda = [] [[nodiscard]] (int x) { return x * 2; };
    int result = attributed_lambda(21);
    std::println("Attributed lambda: {}", result);

    // 3. Recursive Lambdas with Deducing this (C++23)
    // No more std::function or helper tricks needed for recursion!
    auto fib = [](this auto self, int n) -> int {
        if (n <= 1) return n;
        return self(n - 1) + self(n - 2);
    };
    std::println("Fibonacci(10): {}", fib(10));
}

/**
 * Performance & Interview Pitfalls:
 * 
 * 1. Capture by reference: Dangling references if the lambda outlives 
 *    the captured variables (e.g., returning a lambda that captures a local).
 * 
 * 2. std::function overhead: std::function uses type erasure and often 
 *    heap allocation. Lambdas themselves are just objects of unique, 
 *    unnamed class types (closures), which are usually inlined.
 * 
 * 3. Implicit captures: [=] or [&] can capture more than intended, 
 *    increasing the closure size or causing accidental side effects.
 * 
 * 4. Capturing 'this' in [=]: Prior to C++20, [=] implicitly captured 'this' 
 *    by reference. C++20 requires explicit [=, this].
 */

int main() {
    try {
        basic_lambdas();
        advanced_features();
        MemberLambda{}.demonstrate();
        cpp23_features();
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
        return 1;
    }
    return 0;
}

/**
 * Complexity Analysis:
 * - Closure Creation: O(1) space (stack-allocated unless wrapped in std::function).
 * - Call overhead: Equivalent to a function object (operator()). If no capture, 
 *   equivalent to a raw function pointer after optimization.
 * - Static Lambdas (C++23): Zero object size if no captures, potentially better 
 *   optimization since no 'this' pointer is passed.
 */
