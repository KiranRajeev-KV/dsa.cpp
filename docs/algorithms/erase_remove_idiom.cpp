/*
Title: Erase-Remove Idiom & Modern std::erase
Category: Algorithms
File: erase_remove_idiom.cpp
C++ Standard: C++23
Difficulty: Beginner to Intermediate

Purpose:
Explains the evolution of removing elements from containers. From the 
clunky C++98/11/14/17 erase-remove idiom to the clean C++20/23 
std::erase and std::erase_if.

Compile:
g++ -std=c++23 erase_remove_idiom.cpp -o erase_remove

Run:
./erase_remove

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- The classic Erase-Remove Idiom
- Why std::remove doesn't actually remove
- C++20 std::erase and std::erase_if
- Efficiency differences between containers (vector vs list)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <print>
#include <list>
#include <map>

void print_separator(std::string_view title) {
    std::println("\n--- {} ---", title);
}

void print_vec(const std::vector<int>& v, std::string_view label) {
    std::print("{:<25}: ", label);
    for (int n : v) std::print("{} ", n);
    std::println("");
}

int main() {
    // 1. The Classic Erase-Remove Idiom (Pre-C++20)
    // std::remove doesn't know about the container's size, it only shifts 
    // elements. You MUST call container.erase() afterwards.
    print_separator("Classic Erase-Remove Idiom");
    std::vector<int> v1 = {1, 2, 3, 2, 4, 2, 5};
    print_vec(v1, "Original");

    // Remove all 2s
    auto it = std::remove(v1.begin(), v1.end(), 2);
    print_vec(v1, "After std::remove"); 
    std::println("  (Notice 2s are moved to end, but size is still {})", v1.size());
    
    v1.erase(it, v1.end());
    print_vec(v1, "After v.erase(it, end)");

    // 2. The Modern C++20 way: std::erase
    // A single, non-member function that handles everything.
    print_separator("C++20 std::erase");
    std::vector<int> v2 = {1, 2, 3, 2, 4, 2, 5};
    size_t removed_count = std::erase(v2, 2);
    print_vec(v2, "After std::erase(v, 2)");
    std::println("Removed {} elements.", removed_count);

    // 3. The Modern C++20 way: std::erase_if
    // Removes based on a predicate.
    print_separator("C++20 std::erase_if");
    std::vector<int> v3 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::erase_if(v3, [](int n) { return n % 2 == 0; });
    print_vec(v3, "After std::erase_if (evens)");

    // 4. Efficiency: std::list
    // For list, erase is O(1) per element, no shifting.
    print_separator("std::list erasure");
    std::list<int> l = {1, 2, 3, 4, 5};
    // Prior to C++20, list::remove() was better than erase-remove.
    // In C++20, std::erase(list, val) works correctly and optimally.
    std::erase(l, 3);
    std::print("List after erase(3): ");
    for (int n : l) std::print("{} ", n);
    std::println("");

    // 5. Associative Containers (std::map, std::set)
    // std::erase_if also works for maps and sets!
    print_separator("std::erase_if on std::map");
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    std::erase_if(m, [](const auto& pair) {
        return pair.first % 2 == 0;
    });
    std::println("Map size after erasing evens: {}", m.size());

    /*
    --- INTERVIEW PITFALLS ---
    1. Forgetting to call .erase(): This is the classic mistake with 
       `std::remove`. The container still contains "dead" elements at the end.
    2. Iterator Invalidation: Be very careful erasing while iterating manually. 
       `std::erase_if` handles this correctly and is the safest way.
    3. Performance: 
       - For `std::vector`, `std::erase_if` is O(N) because it shifts elements once.
       - For `std::list`, it is O(N) but involves pointer manipulation.
       - For `std::set/map`, it is O(N) as it must traverse the whole tree.

    --- PRODUCTION NOTES ---
    - NEVER use the old erase-remove idiom in C++20/23 projects. 
      `std::erase` and `std::erase_if` are more readable, harder to mess up, 
      and potentially more optimized by the compiler.
    - These functions are located in the headers of the containers they 
      support (e.g., `<vector>`, `<list>`, `<map>`), not just `<algorithm>`.
    */

    return 0;
}
