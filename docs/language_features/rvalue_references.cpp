/*
Title: Rvalue References and Perfect Forwarding Guide
Category: Language Features
File: rvalue_references.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
A deep dive into the C++ type system's value categories (lvalues, rvalues, xvalues, prvalues), rvalue references, and the mechanics of perfect forwarding using `std::forward`.

Compile:
g++ -std=c++23 rvalue_references.cpp -o rvalue_references

Run:
./rvalue_references

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Lvalue vs Rvalue references
- Perfect Forwarding (`std::forward`)
- Forwarding References (Universal References)
- Value Categories (Expression properties)
- C++23 `std::forward_like`

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <utility>
#include <string>
#include <type_traits>

// --- 1. Distinguishing Lvalue and Rvalue References ---
void process(int& lval) {
    std::println("Processing lvalue reference: {}", lval);
}

void process(int&& rval) {
    std::println("Processing rvalue reference: {}", rval);
}

// --- 2. Perfect Forwarding ---
// A forwarding reference (T&&) can bind to anything.
// std::forward preserves the value category.
template <typename T>
void wrapper(T&& arg) {
    std::println("Wrapper forwarding: ");
    process(std::forward<T>(arg));
}

// --- 3. C++23 std::forward_like ---
// Forwards the value category of one object (Owner) to another (Member).
// Useful in Deducing This or generic wrappers.
struct Data {
    std::string text = "C++23 data";
};

template <typename Owner>
void forward_data(Owner&& owner) {
    (void)owner; // Suppress unused warning
    Data d;
    // Forwards 'd' with the same const-ness and value category as 'owner'.
    auto&& redirected = std::forward_like<Owner>(d);
    
    if constexpr (std::is_const_v<std::remove_reference_t<decltype(redirected)>>) {
        std::println("Redirected is CONST");
    }
    if constexpr (std::is_rvalue_reference_v<decltype(redirected)>) {
        std::println("Redirected is RVALUE");
    } else {
        std::println("Redirected is LVALUE");
    }
}

int main() {
    std::println("--- Rvalue References & Perfect Forwarding ---\n");

    int x = 10;
    
    std::println("Direct calls:");
    process(x);      // Calls lvalue version
    process(20);     // Calls rvalue version
    process(std::move(x)); // Calls rvalue version

    std::println("\nWrapper calls (Perfect Forwarding):");
    int y = 30;
    wrapper(y);              // Forwards lvalue
    wrapper(40);             // Forwards rvalue
    wrapper(std::move(y));   // Forwards rvalue

    std::println("\nC++23 std::forward_like:");
    const Data cd;
    forward_data(cd);             // Owner is const lvalue
    forward_data(std::move(cd));  // Owner is const rvalue
    forward_data(Data{});         // Owner is rvalue

    return 0;
}

/*
Complexity & Performance Notes:
- Rvalue references and perfect forwarding are zero-cost abstractions. They purely affect how the compiler matches functions and performs casts.
- They enable "move semantics," which can turn O(N) copies into O(1) pointer swaps.

Interview Pitfalls:
- "Rvalue reference" vs "Forwarding reference": `T&&` is only a forwarding reference if `T` is a template parameter being deduced in that context. `std::vector<T>::push_back(T&&)` is an rvalue reference, NOT a forwarding reference, because `T` was already deduced for the class.
- Reference Collapsing Rules: 
  & + & -> &
  & + && -> &
  && + & -> &
  && + && -> &&
  This is why `std::forward<T>(arg)` works.
*/
