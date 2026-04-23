/*
Title: Searching Algorithms Complete Guide
Category: Algorithms
File: searching.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to non-modifying sequence algorithms in C++ for 
searching and finding elements. Covers standard STL and modern Ranges.

Compile:
g++ -std=c++23 searching.cpp -o searching

Run:
./searching

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::find, std::find_if, std::find_if_not
- std::ranges::find and its variants
- std::adjacent_find, std::find_first_of
- std::search, std::find_end
- std::ranges::contains (C++23)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <ranges>
#include <string>
#include <print>
#include <list>

void print_separator(std::string_view title) {
    std::println("\n--- {} ---", title);
}

int main() {
    const std::vector<int> numbers = {10, 20, 30, 40, 50, 20, 60, 70};

    // 1. Basic find
    // Complexity: O(N)
    print_separator("std::find & std::ranges::find");
    auto it1 = std::find(numbers.begin(), numbers.end(), 30);
    if (it1 != numbers.end()) {
        std::println("Found 30 at index: {}", std::distance(numbers.begin(), it1));
    }

    // Ranges version (C++20)
    auto it2 = std::ranges::find(numbers, 20);
    if (it2 != numbers.end()) {
        std::println("Found 20 at index: {}", std::distance(numbers.begin(), it2));
    }

    // 2. find_if & find_if_not
    print_separator("Predicate-based Searching");
    auto it3 = std::ranges::find_if(numbers, [](int n) { return n > 50; });
    if (it3 != numbers.end()) {
        std::println("First number > 50 is: {}", *it3);
    }

    auto it4 = std::ranges::find_if_not(numbers, [](int n) { return n % 10 == 0; });
    if (it4 == numbers.end()) {
        std::println("All numbers are multiples of 10.");
    }

    // 3. adjacent_find (Find first pair of equal adjacent elements)
    print_separator("std::adjacent_find");
    std::vector<int> dupes = {1, 2, 3, 3, 4, 5};
    auto it5 = std::ranges::adjacent_find(dupes);
    if (it5 != dupes.end()) {
        std::println("Found adjacent duplicates: {}", *it5);
    }

    // 4. search (Find a sub-sequence)
    print_separator("Sub-sequence Searching (std::search)");
    std::vector<int> pattern = {20, 30, 40};
    auto it6 = std::ranges::search(numbers, pattern);
    if (!it6.empty()) {
        std::println("Found sub-sequence {{20, 30, 40}} starting at index: {}", 
                     std::distance(numbers.begin(), it6.begin()));
    }

    // 5. C++23: std::ranges::contains
    // A highly requested convenience function
    print_separator("C++23 std::ranges::contains");
    bool has_50 = std::ranges::contains(numbers, 50);
    bool has_99 = std::ranges::contains(numbers, 99);
    std::println("Contains 50? {}", has_50);
    std::println("Contains 99? {}", has_99);

    // 6. Searching in a string (specialized methods)
    print_separator("String Searching");
    std::string text = "Modern C++23 is powerful";
    size_t pos = text.find("C++23");
    if (pos != std::string::npos) {
        std::println("'C++23' found at position: {}", pos);
    }

    // 7. find_first_of
    print_separator("std::find_first_of");
    std::vector<int> targets = {99, 20, 77};
    // Find the first occurrence of ANY element in 'targets' within 'numbers'
    auto it7 = std::ranges::find_first_of(numbers, targets);
    if (it7 != numbers.end()) {
        std::println("First target found in numbers: {}", *it7);
    }

    /*
    --- INTERVIEW PITFALLS ---
    1. find vs find_if: Use find for values, find_if for complex logic.
    2. std::string::find vs std::find: String's find member returns index (size_t), 
       algorithm returns iterator. Be careful with 'npos'.
    3. Performance: All linear searches are O(N). If you find yourself searching 
       frequently, consider std::set, std::unordered_set, or sorting the data 
       and using binary search (O(log N)).
    4. End-iterator check: ALWAYS check if the result is != end() before dereferencing.

    --- PRODUCTION NOTES ---
    - Use std::ranges::contains for readability in C++23.
    - std::search can take a Searcher (like Boyer-Moore) for high-performance sub-string 
      searching in large texts (available since C++17).
    - Projections (C++20) allow searching by member:
      std::ranges::find(employees, "Alice", &Employee::name);
    */

    return 0;
}
