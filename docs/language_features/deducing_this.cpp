/*
Title: Deducing This (Explicit Object Parameters) Complete Guide
Category: Language Features
File: deducing_this.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
A comprehensive guide to one of C++23's most powerful features: Deducing `this`. It simplifies CRTP, enables recursive lambdas, and allows elegant handling of const/reference qualifiers.

Compile:
g++ -std=c++23 deducing_this.cpp -o deducing_this

Run:
./deducing_this

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Explicit object parameters (`this self`)
- Replacing CRTP
- Deduplicating const/non-const overloads
- Recursive lambdas (without std::function)
- Forwarding `this`

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <vector>
#include <utility>

// --- 1. Deduplicating Const/Non-Const overloads ---
// Pre-C++23, you often had to write two identical functions for const and non-const.
struct Container {
    std::vector<int> data = {1, 2, 3, 4, 5};

    // C++23 way: Deduce 'this'
    template <typename Self>
    auto&& get_data(this Self&& self) {
        // self will be Container&, const Container&, Container&&, etc.
        return std::forward<Self>(self).data;
    }
};

// --- 2. Replacing CRTP ---
// Old CRTP: class Derived : public Base<Derived>
// New C++23 way:
struct Base {
    template <typename Self>
    void interface(this Self&& self) {
        self.implementation(); // Direct call to derived!
    }
};

struct Derived : Base {
    void implementation() {
        std::println("Derived implementation called via Deducing This!");
    }
};

// --- 3. Recursive Lambdas ---
// Before C++23, recursive lambdas were tricky (needed std::function or helper).
// Now, a lambda can capture its own type!
auto test_recursive_lambda() {
    auto factorial = [](this auto self, int n) -> int {
        return (n <= 1) ? 1 : n * self(n - 1);
    };
    return factorial(5);
}

// --- 4. Moving out of 'this' ---
struct HeavyObject {
    void process(this HeavyObject&& self) {
        std::println("Processing and consuming heavy object...");
        // self is an rvalue, we can move from it safely.
        [[maybe_unused]] auto internal = std::move(self.buffer);
    }
    std::vector<int> buffer = {1, 2, 3};
};

int main() {
    std::println("--- C++23 Deducing This ---\n");

    // 1. Overload deduction
    Container c;
    const Container cc;
    c.get_data()[0] = 10; // Calls non-const version, returns int&
    std::println("Modified data[0]: {}", c.get_data()[0]);
    // cc.get_data()[0] = 20; // ERROR: CC is const, returns const data&

    // 2. CRTP Replacement
    Derived d;
    d.interface();

    // 3. Recursive Lambda
    std::println("Factorial(5) via recursive lambda: {}", test_recursive_lambda());

    // 4. Consuming 'this'
    HeavyObject h;
    std::move(h).process(); // Explicitly call on rvalue

    return 0;
}

/*
Complexity & Performance Notes:
- Deducing `this` is purely a syntactic and type-system improvement. It generates the same machine code as traditional member functions or CRTP.
- It significantly reduces code duplication (the "const-correctness bloat") and improves compile times compared to complex CRTP hierarchies.

Interview Pitfalls:
- The first parameter MUST be prefixed with `this`.
- You cannot have both a traditional `void foo() const` and `void foo(this const Self& self)` for the same signature; it results in an ambiguity or redefinition.
- Remember to `std::forward<Self>(self)` if you want to preserve the value category (lvalue/rvalue) of the object.
*/
