/*
Title: std::function Complete Guide
Category: Functional Programming
File: function.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
In-depth analysis of std::function, covering type erasure, polymorphic wrappers, 
Small Object Optimization (SOO), and performance characteristics.

Compile:
g++ -std=c++23 function.cpp -o function

Run:
./function

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Basic std::function usage
- Wrapping Lambdas, Functors, and Raw Function Pointers
- Type Erasure and SOO (Small Object Optimization)
- Performance overhead vs Raw Pointers/Lambdas
- std::function vs std::move_only_function (Introduction)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <functional>
#include <string>
#include <print>

// 1. Raw Function
int free_function(int x) {
    return x * x;
}

// 2. Functor (Function Object)
struct Multiplier {
    int factor;
    int operator()(int x) const { return x * factor; }
};

void basic_usage() {
    std::println("--- std::function Basic Usage ---");

    // std::function<ReturnType(ParamTypes...)>
    std::function<int(int)> func;

    // Pointing to free function
    func = free_function;
    std::println("Free function: {}", func(5));

    // Pointing to lambda
    func = [](int x) { return x + 10; };
    std::println("Lambda: {}", func(5));

    // Pointing to functor
    func = Multiplier{3};
    std::println("Functor: {}", func(5));

    // Empty state
    std::function<void()> empty_func;
    if (!empty_func) {
        std::println("empty_func is empty.");
    }
    
    try {
        std::println("Attempting to call empty_func...");
        empty_func(); // Throws std::bad_function_call
    } catch (const std::bad_function_call& e) {
        std::println("Caught expected exception: {}", e.what());
    }
}

/**
 * Performance & Type Erasure Note:
 * std::function uses type erasure to store different callable types with the 
 * same signature. This usually involves:
 * 1. A virtual function call (or function pointer jump) internally.
 * 2. Heap allocation if the closure is large (beyond SOO limit, often 16-32 bytes).
 * 3. Prevention of inlining by the compiler.
 */

void heap_vs_stack() {
    std::println("\n--- Type Erasure & SOO ---");

    // Small lambda (likely stack-allocated via SOO)
    auto small = [a = 1, b = 2]() { return a + b; };
    std::function<int()> f_small = small;

    // Large lambda (likely heap-allocated)
    auto large = [arr = std::vector<int>(100, 42)]() { return arr[0]; };
    std::function<int()> f_large = large;

    std::println("SOO limits are implementation-defined (usually 2-4 pointers).");
}

void wrapping_members() {
    std::println("\n--- Wrapping Member Functions ---");

    struct Player {
        std::string name;
        void shout(const std::string& msg) const {
            std::println("{} says: {}", name, msg);
        }
    };

    Player p{"Alice"};
    
    // Member function pointer requires 'this' as first argument (explicitly or via bind)
    std::function<void(const Player&, const std::string&)> f_shout = &Player::shout;
    f_shout(p, "Hello!");

    // Using lambda as a wrapper for better ergonomics
    std::function<void(const std::string&)> alice_shouts = [&p](const std::string& msg) {
        p.shout(msg);
    };
    alice_shouts("C++23 is great!");
}

/**
 * Interview Pitfalls:
 * 1. std::function is not a function pointer. It's a heavy wrapper.
 * 2. It doesn't support move-only types (like std::unique_ptr) in its captures 
 *    until C++23's std::move_only_function.
 * 3. It adds an extra indirection level, affecting hot-loop performance.
 * 4. Copying a std::function might involve a heap allocation if the original 
 *    allocated memory.
 */

int main() {
    try {
        basic_usage();
        heap_vs_stack();
        wrapping_members();
    } catch (const std::exception& e) {
        std::println(stderr, "Unexpected error: {}", e.what());
        return 1;
    }
    return 0;
}

/**
 * Complexity Analysis:
 * - Construction: O(1) if small (SOO), O(1) heap allocation if large.
 * - Invocation: O(1), but involves a virtual call/pointer indirection.
 * - Copying: O(1) or O(1) heap allocation.
 * - Space: sizeof(std::function) + potential heap allocation.
 */
