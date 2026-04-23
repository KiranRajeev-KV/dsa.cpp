/*
Title: C++23 Generator Guide
Category: Language Features
File: generator_cpp23.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
Demonstrates the C++23 `std::generator`, which provides a standard way to write synchronous coroutines that produce a sequence of values, integrating perfectly with C++ Ranges.

Compile:
g++ -std=c++23 generator_cpp23.cpp -o generator_cpp23
Note: Requires GCC 14+ or Clang 17+ with <generator> support.

Run:
./generator_cpp23

Key Topics:
- `std::generator<T>`
- `co_yield` and `co_return`
- Recursive generators (`co_yield std::ranges::elements_of`)
- Range composition with generators
- Memory management of coroutine frames

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <ranges>
#include <print>

// std::generator is a C++23 feature
#if __has_include(<generator>)
#include <generator>
#define HAS_GENERATOR 1
#else
#define HAS_GENERATOR 0
#endif

#if HAS_GENERATOR
/**
 * @brief 1. A Simple Generator.
 * Each 'co_yield' suspends the function and returns a value to the caller.
 */
std::generator<int> count_to(int n) {
    for (int i = 1; i <= n; ++i) {
        co_yield i; 
    }
}

/**
 * @brief 2. Infinite Sequence.
 * Generators are perfect for infinite streams as they are evaluated lazily.
 */
std::generator<long long> fibonacci() {
    long long a = 0, b = 1;
    while (true) {
        co_yield a;
        auto next = a + b;
        a = b;
        b = next;
    }
}

/**
 * @brief 3. Recursive Generator using std::ranges::elements_of.
 * This is a C++23 specific optimization for yielding all elements of another range 
 * (like another generator) without creating a new coroutine frame for every step.
 */
std::generator<int> nested_sequence(int start, int end) {
    if (start <= end) {
        co_yield start;
        // Efficiently yield elements from a recursive call
        co_yield std::ranges::elements_of(nested_sequence(start + 1, end));
    }
}

#endif

int main() {
    std::println("--- C++23 std::generator ---\n");

#if HAS_GENERATOR
    std::print("Counting to 5: ");
    for (int i : count_to(5)) {
        std::print("{} ", i);
    }
    std::println("");

    std::print("First 10 Fibonacci numbers: ");
    // Composing generator with a range view
    for (int f : fibonacci() | std::views::take(10)) {
        std::print("{} ", f);
    }
    std::println("");

    std::print("Recursive sequence (1-5): ");
    for (int v : nested_sequence(1, 5)) {
        std::print("{} ", v);
    }
    std::println("");

    std::println("\n--- Range Composition ---");
    // Generators are full-fledged ranges
    auto squares = count_to(10) 
                 | std::views::filter([](int x) { return x % 2 == 0; })
                 | std::views::transform([](int x) { return x * x; });

    std::print("Squares of even numbers (1-10): ");
    for (int val : squares) {
        std::print("{} ", val);
    }
    std::println("");
#else
    std::println("Error: <generator> header not found. This compiler does not support std::generator.");
#endif

    return 0;
}

/*
Complexity & Performance Notes:
- `std::generator` is an "input range." It is single-pass and lazy.
- Coroutine Frame: When a generator is called, a coroutine frame is allocated 
  on the heap (unless the compiler performs Halo optimization).
- `elements_of`: Using `std::ranges::elements_of` is critical for recursive 
  generators to avoid O(depth) overhead for every yielded element.

Interview Pitfalls:
- Generators are "move-only" types. You cannot copy a generator.
- Lifetime: A generator's iterator becomes invalid if the generator object 
  it was created from is destroyed (it's a view into the coroutine state).
- Single Pass: You cannot re-iterate a generator from the beginning unless 
  the function is designed to reset or you call the function again.
*/
