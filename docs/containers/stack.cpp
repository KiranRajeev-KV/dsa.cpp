/*
Title: std::stack Complete Guide
Category: Container Adapters
File: stack.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::stack, a LIFO (Last-In-First-Out) container adapter.
Explains underlying containers, performance, and C++23 usage.

Compile:
g++ -std=c++23 stack.cpp -o stack

Run:
./stack

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- LIFO Principle
- Container Adapters (Default: deque)
- push, pop, top, emplace
- Why no iterators?
- Production Use Cases: Expression parsing, Backtracking

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <stack>
#include <vector>
#include <list>
#include <print>
#include <string>

/**
 * @brief Demonstrates basic stack operations.
 */
void basic_operations() {
    std::println("--- Stack Basics ---");
    std::stack<int> s;
    
    s.push(10);
    s.push(20);
    s.emplace(30); // Constructs in-place
    
    std::println("Stack top: {}", s.top());
    std::println("Stack size: {}", s.size());
    
    s.pop();
    std::println("After pop, top: {}", s.top());
}

/**
 * @brief Shows how to change the underlying container.
 */
void underlying_containers() {
    std::println("\n--- Underlying Containers ---");
    
    // Using vector as base (O(1) push/pop at end, contiguous)
    std::stack<int, std::vector<int>> vector_stack;
    
    // Using list as base (Node-based)
    std::stack<std::string, std::list<std::string>> list_stack;
    
    vector_stack.push(1);
    list_stack.push("Hello");
    
    std::println("Vector-based stack size: {}", vector_stack.size());
    std::println("List-based stack top: {}", list_stack.top());
}

/**
 * @brief Practical Example: Reversing a string or Bracket Matching.
 */
bool is_balanced(std::string_view expr) {
    std::stack<char> s;
    for (char c : expr) {
        if (c == '(') s.push(c);
        else if (c == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

void practical_example() {
    std::println("\n--- Practical Example: Bracket Matching ---");
    std::string e1 = "(())()";
    std::string e2 = "(()))";
    
    std::println("Is '{}' balanced? {}", e1, is_balanced(e1));
    std::println("Is '{}' balanced? {}", e2, is_balanced(e2));
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. NO ITERATORS: std::stack does not provide iterators. This is by design to enforce LIFO constraints.");
    std::println("2. pop() returns void: It does NOT return the top element. You must call top() then pop(). This is for exception safety.");
    std::println("3. Default container: std::deque is the default because it doesn't require reallocating the whole array (unlike vector) and provides O(1) push/pop.");
}

/**
 * @brief Complexity:
 * - Push/Pop/Top: O(1)
 * - Space: O(N)
 */
int main() {
    basic_operations();
    underlying_containers();
    practical_example();
    interview_notes();
    return 0;
}
