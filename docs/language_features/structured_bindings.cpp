/*
Title: Structured Bindings Complete Guide
Category: Language Features
File: structured_bindings.cpp
C++ Standard: C++23
Difficulty: Beginner to Intermediate

Purpose:
A guide to C++ structured bindings, allowing clean unpacking of tuples, pairs, structs, and arrays. Covers C++20/23 improvements such as lambda captures and use in constexpr contexts.

Compile:
g++ -std=c++23 structured_bindings.cpp -o structured_bindings

Run:
./structured_bindings

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Unpacking `std::pair` and `std::tuple`
- Unpacking custom structs and arrays
- Binding by value, reference, and const reference
- C++20: Capturing structured bindings in lambdas
- C++23: Structured bindings in more contexts

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <tuple>
#include <string>
#include <map>
#include <array>

struct Player {
    std::string name;
    int score;
    double health;
};

int main() {
    std::println("--- Structured Bindings (C++23) ---\n");

    // 1. Unpacking a Struct
    Player p1{"Alice", 1500, 95.5};
    auto [name, score, health] = p1; // By value
    std::println("Player: {}, Score: {}", name, score);

    // 2. Binding by Reference (Modifying the source)
    auto& [rName, rScore, rHealth] = p1;
    rScore += 500;
    std::println("Updated p1 Score: {}", p1.score);

    // 3. Unpacking std::pair (Common in maps)
    std::map<std::string, int> inventory = {{"Potions", 5}, {"Arrows", 20}};
    std::println("\nInventory:");
    for (const auto& [item, count] : inventory) {
        std::println("- {}: {}", item, count);
    }

    // 4. Unpacking Arrays
    int coords[3] = {10, 20, 30};
    auto [x, y, z] = coords;
    std::println("\nCoordinates: {}, {}, {}", x, y, z);

    // 5. C++20: Capturing in Lambdas
    // Before C++20, you couldn't capture structured bindings directly.
    auto [id, val] = std::make_pair(1, 100);
    auto lambda = [id, val]() {
        return id + val;
    };
    std::println("\nLambda result from captured bindings: {}", lambda());

    // 6. std::tuple and std::ignore
    // Note: You cannot use std::ignore with structured bindings. 
    // You must bind all members. If you don't need one, use [[maybe_unused]].
    [[maybe_unused]] auto [a, b, c_unused] = std::make_tuple(1, 2.5, "unneeded");
    std::println("\nTuple unpacked: {}, {}", a, b);

    return 0;
}

/*
Complexity & Performance Notes:
- Structured bindings are purely "syntactic sugar." The compiler creates an anonymous hidden object (the "e") and the names you provide are aliases to the members of that object.
- There is NO runtime cost compared to manual access (e.g., `p.name`).

Interview Pitfalls:
- You cannot use `static`, `thread_local`, or `constexpr` modifiers on the structured binding names themselves.
- You must unpack ALL members of the struct/tuple/array. No skipping (unlike Go or JavaScript).
- The hidden object created by `auto [a, b] = ...` has the cv-qualifiers of the `auto`. If you use `const auto& [a, b]`, then `a` and `b` are references to const members.
*/
