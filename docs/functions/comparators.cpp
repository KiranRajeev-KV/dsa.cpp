/*
Title: Custom Comparators Complete Guide
Category: Functional Programming
File: comparators.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Detailed exploration of comparison logic in C++. Covers custom ordering for 
associative containers, sorting algorithms, and the C++20/23 Spaceship Operator (<=>).

Compile:
g++ -std=c++23 comparators.cpp -o comparators

Run:
./comparators

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Strict Weak Ordering (Importance and Rules)
- Comparators for std::sort and std::set/std::map
- Lambdas as Comparators
- The Spaceship Operator (<=>) and std::compare_three_way
- C++20/23 Projections in Ranges

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <compare>
#include <print>

struct Student {
    std::string name;
    int grade;

    // C++20: Defaulted spaceship operator for lexicographical comparison
    auto operator<=>(const Student&) const = default;
};

struct Employee {
    int id;
    std::string department;
    double salary;
};

void basic_comparators() {
    std::println("--- Basic Comparators ---");

    std::vector<int> nums = {5, 2, 9, 1, 5, 6};

    // 1. Descending order using std::greater
    std::sort(nums.begin(), nums.end(), std::greater<int>());
    std::print("Sorted Descending: ");
    for (int n : nums) std::print("{} ", n);
    std::println();

    // 2. Custom lambda comparator (Absolute value)
    std::vector<int> mixed = {-10, 5, -2, 1};
    std::sort(mixed.begin(), mixed.end(), [](int a, int b) {
        return std::abs(a) < std::abs(b);
    });
    std::print("Sorted by Abs: ");
    for (int n : mixed) std::print("{} ", n);
    std::println();
}

void container_comparators() {
    std::println("\n--- Associative Container Comparators ---");

    // Case-insensitive string set
    struct CaseInsensitiveCompare {
        bool operator()(const std::string& a, const std::string& b) const {
            return std::lexicographical_compare(
                a.begin(), a.end(), b.begin(), b.end(),
                [](char c1, char c2) { return std::tolower(c1) < std::tolower(c2); }
            );
        }
    };

    std::set<std::string, CaseInsensitiveCompare> names = {"Alice", "bob", "CHARLIE"};
    std::print("Case-Insensitive Set: ");
    for (const auto& name : names) std::print("{} ", name);
    std::println();
}

void spaceship_operator() {
    std::println("\n--- Spaceship Operator (<=>) ---");

    Student s1{"Alice", 90};
    Student s2{"Bob", 85};
    Student s3{"Alice", 90};

    auto res = s1 <=> s2;
    if (res < 0) std::println("Alice < Bob (alphabetically)");
    else if (res > 0) std::println("Alice > Bob (alphabetically)");
    
    std::println("s1 == s3: {}", s1 == s3);
}

void range_projections() {
    std::println("\n--- C++20/23 Projections ---");

    std::vector<Employee> staff = {
        {101, "Sales", 55000},
        {102, "Eng", 95000},
        {103, "Eng", 85000}
    };

    // Sorting by salary using a projection
    // Projections allow you to "transform" the element before comparison 
    // without changing the original data.
    std::ranges::sort(staff, std::less<>{}, &Employee::salary);

    std::println("Staff sorted by salary:");
    for (const auto& e : staff) {
        std::println("  ID: {}, Salary: {}", e.id, e.salary);
    }
}

/**
 * Strict Weak Ordering Rules (Crucial for Interviews):
 * A comparator must satisfy:
 * 1. Irreflexivity: comp(a, a) is false.
 * 2. Asymmetry: if comp(a, b) is true, then comp(b, a) is false.
 * 3. Transitivity: if comp(a, b) and comp(b, c) are true, then comp(a, c) is true.
 * 4. Transitivity of Equivalence: if a~b and b~c, then a~c (where a~b means !comp(a,b) && !comp(b,a)).
 * 
 * FAILURE to follow these leads to UNDEFINED BEHAVIOR (crashes, infinite loops).
 */

int main() {
    try {
        basic_comparators();
        container_comparators();
        spaceship_operator();
        range_projections();
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
        return 1;
    }
    return 0;
}

/**
 * Complexity Analysis:
 * - Time: Comparators are usually O(1) for primitives or O(L) for strings. 
 *   Sorting using them is O(N log N).
 * - Space: O(1) for the comparator object (usually stateless).
 */
