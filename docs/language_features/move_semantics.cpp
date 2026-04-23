/*
Title: Move Semantics and RAII Complete Guide
Category: Language Features
File: move_semantics.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
A deep dive into move semantics, the Rule of Five, and Resource Acquisition Is Initialization (RAII). Explains how modern C++ avoids expensive copies.

Compile:
g++ -std=c++23 move_semantics.cpp -o move_semantics

Run:
./move_semantics

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Move Constructor and Move Assignment
- `std::move` and `std::forward`
- Rule of Five vs Rule of Zero
- Resource management (RAII)
- Small String Optimization (SSO) interaction

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <vector>
#include <algorithm>
#include <cstring>

class DynamicBuffer {
private:
    size_t size;
    int* data;

public:
    // Constructor (RAII)
    explicit DynamicBuffer(size_t s) : size(s), data(new int[s]) {
        std::println("Constructed buffer of size {}", size);
    }

    // Destructor (RAII)
    ~DynamicBuffer() {
        delete[] data;
        std::println("Destroyed buffer");
    }

    // 1. Copy Constructor
    DynamicBuffer(const DynamicBuffer& other) : size(other.size), data(new int[other.size]) {
        std::memcpy(data, other.data, size * sizeof(int));
        std::println("Copied buffer");
    }

    // 2. Copy Assignment
    DynamicBuffer& operator=(const DynamicBuffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::memcpy(data, other.data, size * sizeof(int));
        }
        std::println("Copy assigned buffer");
        return *this;
    }

    // 3. Move Constructor
    // Note: 'noexcept' is critical for STL containers to use move instead of copy during resize.
    DynamicBuffer(DynamicBuffer&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr; // Leave 'other' in a valid but unspecified state
        std::println("Moved buffer (constructor)");
    }

    // 4. Move Assignment
    DynamicBuffer& operator=(DynamicBuffer&& other) noexcept {
        if (this != &other) {
            delete[] data; // Free existing resource
            size = other.size;
            data = other.data;
            other.size = 0;
            other.data = nullptr;
        }
        std::println("Move assigned buffer");
        return *this;
    }
};

// --- Rule of Zero Example ---
// If your class only contains members that already handle their own resources
// (like std::vector, std::string, std::unique_ptr), don't write any of the 5!
struct RuleOfZero {
    std::string name;
    std::vector<int> scores;
};

int main() {
    std::println("--- Move Semantics & RAII ---\n");

    std::println("Scenario 1: Copying");
    DynamicBuffer b1(100);
    DynamicBuffer b2 = b1; // Copy

    std::println("\nScenario 2: Moving");
    DynamicBuffer b3 = std::move(b1); // Move
    // b1 is now "empty" (size 0, data nullptr)

    std::println("\nScenario 3: STL interaction");
    std::vector<DynamicBuffer> vec;
    vec.reserve(2);
    vec.push_back(DynamicBuffer(50)); // Temporary moved into vector
    vec.push_back(std::move(b2));     // Explicit move

    std::println("\nEnd of main - all buffers will be destroyed.");
    return 0;
}

/*
Complexity & Performance Notes:
- Move operations are typically O(1) (pointer swaps), whereas copy operations are O(N) (allocating and copying memory).
- `std::move` doesn't actually move anything; it's a cast to an rvalue reference (`static_cast<T&&>`). The actual move happens in the move constructor/assignment operator.

Interview Pitfalls:
- Forgetting `noexcept` on move constructors: `std::vector` will default to copying during a resize if the move constructor isn't `noexcept` to maintain the strong exception guarantee.
- Moving from a const object: `const T x; std::move(x);` results in a copy! You cannot move out of a const object because moving usually requires modifying the source.
- Accessing an object after `std::move`: It's valid but unspecified. Generally, only call functions that don't have preconditions (like `empty()`, `size()`, or re-assignment).
*/
