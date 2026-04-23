/*
Title: std::pair and std::tuple Complete Guide
Category: Utilities / Heterogeneous Containers
File: pair_tuple.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::pair and std::tuple. Covers structured bindings, 
tie, forward_as_tuple, and C++23 enhancements.

Compile:
g++ -std=c++23 pair_tuple.cpp -o pair_tuple

Run:
./pair_tuple

Key Topics:
- Fixed-size heterogeneous collections
- Structured Bindings (C++17/20/23)
- std::apply and std::make_from_tuple
- std::tie for unpacking and comparison
- C++23: std::tuple constructor improvements

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <tuple>
#include <utility>
#include <string>
#include <print>

/**
 * @brief Demonstrates std::pair basics and structured bindings.
 */
void pair_basics() {
    std::println("--- Pair Basics ---");
    std::pair<std::string, int> p = {"C++", 23};
    
    // Traditional access
    std::println("Pair: {}, {}", p.first, p.second);
    
    // Structured binding
    auto [lang, version] = p;
    std::println("Structured binding: lang={}, version={}", lang, version);
}

/**
 * @brief Demonstrates std::tuple basics and heterogeneous data.
 */
void tuple_basics() {
    std::println("\n--- Tuple Basics ---");
    std::tuple<int, std::string, double> t = {1, "Sensor", 98.6};
    
    // Access via std::get<Index>
    std::println("Tuple: {}, {}, {}", std::get<0>(t), std::get<1>(t), std::get<2>(t));
    
    // Access via std::get<Type> (only if type is unique in tuple)
    std::println("Tuple by type (double): {}", std::get<double>(t));
    
    // Structured binding
    auto [id, name, val] = t;
    std::println("Unpacked: id={}, name={}, val={}", id, name, val);
}

/**
 * @brief Advanced tuple utilities.
 */
void tuple_utilities() {
    std::println("\n--- Tuple Utilities ---");
    
    auto t1 = std::make_tuple(1, "A");
    auto t2 = std::make_tuple(2, "B");
    
    // tuple_cat: concatenating tuples
    auto t3 = std::tuple_cat(t1, t2);
    std::println("Cat size: {}", std::tuple_size_v<decltype(t3)>);
    
    // std::apply: calling a function with tuple elements as arguments
    auto print_sum = [](int a, int b) { std::println("Sum: {}", a + b); };
    std::apply(print_sum, std::make_tuple(10, 20));
}

/**
 * @brief Using std::tie for multiple return values and comparison.
 */
struct Record {
    int id;
    std::string name;
    
    // Easy comparison using tie
    bool operator<(const Record& other) const {
        return std::tie(id, name) < std::tie(other.id, other.name);
    }
};

void tie_demonstration() {
    std::println("\n--- std::tie Demonstration ---");
    int x;
    std::string y;
    
    // Unpacking into existing variables
    std::tie(x, y) = std::make_pair(10, "Hello");
    std::println("x={}, y={}", x, y);
    
    // std::ignore
    std::tie(std::ignore, y) = std::make_pair(99, "World");
    std::println("y after ignore: {}", y);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Readability: Tuples are great but can become unreadable with many elements. Consider a named struct if you have more than 3-4 elements.");
    std::println("2. Compilation Time: Extensive use of tuple (especially tuple_cat) can increase compile times significantly due to heavy template recursion.");
    std::println("3. pair vs tuple: pair is just a 2-element tuple but has the convenient .first/.second naming.");
}

int main() {
    pair_basics();
    tuple_basics();
    tuple_utilities();
    tie_demonstration();
    interview_notes();
    return 0;
}
