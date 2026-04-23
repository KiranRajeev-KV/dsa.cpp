/*
Title: Smart Pointers Complete Guide
Category: Language Features
File: smart_pointers.cpp
C++ Standard: C++23
Difficulty: Intermediate

Purpose:
A definitive guide to C++ smart pointers (`unique_ptr`, `shared_ptr`, `weak_ptr`), covering ownership semantics, custom deleters, and C++20/23 improvements.

Compile:
g++ -std=c++23 smart_pointers.cpp -o smart_pointers

Run:
./smart_pointers

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- `std::unique_ptr` (Exclusive ownership)
- `std::shared_ptr` (Reference counting)
- `std::weak_ptr` (Breaking cycles)
- Custom deleters
- `make_unique_for_overwrite` / `make_shared_for_overwrite` (C++20)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <memory>
#include <vector>
#include <cassert>

struct Resource {
    int id;
    Resource(int i) : id(i) { std::println("Resource {} created", id); }
    ~Resource() { std::println("Resource {} destroyed", id); }
    void use() { std::println("Using resource {}", id); }
};

// --- Custom Deleter Example ---
void custom_deleter(Resource* r) {
    std::println("Custom deleting resource {}...", r->id);
    delete r;
}

// --- Shared Pointer Cycle Example ---
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // Use weak_ptr to break the cycle!
    ~Node() { std::println("Node destroyed"); }
};

int main() {
    std::println("--- Modern Smart Pointers ---\n");

    // 1. std::unique_ptr
    {
        std::println("1. Unique Pointers:");
        auto u1 = std::make_unique<Resource>(1);
        // auto u2 = u1; // ERROR: Cannot copy unique_ptr
        auto u2 = std::move(u1); // Move ownership
        assert(u1 == nullptr);
        u2->use();
    } // u2 goes out of scope, Resource 1 destroyed

    // 2. Custom Deleter
    {
        std::println("\n2. Custom Deleters:");
        std::unique_ptr<Resource, void(*)(Resource*)> u_custom(new Resource(2), custom_deleter);
    }

    // 3. std::shared_ptr and std::weak_ptr
    {
        std::println("\n3. Shared and Weak Pointers:");
        std::shared_ptr<Resource> s1 = std::make_shared<Resource>(3);
        {
            std::shared_ptr<Resource> s2 = s1; // Ref count = 2
            std::println("Shared ref count: {}", s1.use_count());
            
            std::weak_ptr<Resource> w1 = s1; // Ref count stays 2
            if (auto shared_from_weak = w1.lock()) {
                shared_from_weak->use();
            }
        } // s2 destroyed, ref count = 1
        std::println("Shared ref count after inner scope: {}", s1.use_count());
    } // s1 destroyed, Resource 3 destroyed

    // 4. Breaking Cycles
    {
        std::println("\n4. Breaking Cycles:");
        auto head = std::make_shared<Node>();
        auto tail = std::make_shared<Node>();
        head->next = tail;
        tail->prev = head; // weak_ptr doesn't increase ref count
    } // Both nodes destroyed correctly

    // 5. C++20 for_overwrite
    // Useful for performance when you're about to fill the buffer anyway.
    auto p = std::make_unique_for_overwrite<int[]>(100); // uninitialized
    std::println("\n5. make_unique_for_overwrite used for efficient allocation.");

    return 0;
}

/*
Complexity & Performance Notes:
- `std::unique_ptr`: Zero overhead compared to raw pointers (in size and speed). The destructor call is inlined.
- `std::shared_ptr`: 16-32 bytes (2 pointers: one to object, one to control block). Atomic increment/decrement of ref count has a small runtime cost.
- `std::make_shared` is more efficient than `shared_ptr<T>(new T)` because it performs a single heap allocation for both the object and the control block.

Interview Pitfalls:
- Creating a `shared_ptr` from a raw pointer twice: `Resource* r = new Resource(1); shared_ptr<Resource> p1(r); shared_ptr<Resource> p2(r);` - This will cause a double delete!
- Circular references with `shared_ptr`: Lead to memory leaks as ref counts never reach zero. Always use `weak_ptr` for the "back" pointer.
- `std::unique_ptr<T[]>` is supported, but `std::vector<T>` is almost always a better choice.
*/
