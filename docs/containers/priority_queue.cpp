/*
Title: std::priority_queue Complete Guide
Category: Container Adapters
File: priority_queue.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::priority_queue, a container adapter providing O(log N) 
insertion and O(1) access to the largest (or smallest) element.
Covers heap mechanics, custom comparators, and C++23 features.

Compile:
g++ -std=c++23 priority_queue.cpp -o priority_queue

Run:
./priority_queue

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Max-heap vs Min-heap
- Underlying containers (vector, deque)
- Custom comparators (structs and lambdas)
- C++23: std::ranges improvements
- Production Use Cases: Dijkstra's Algorithm, Huffman Coding

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <queue>
#include <vector>
#include <print>
#include <string>

/**
 * @brief Demonstrates basic max-heap (default) operations.
 */
void basic_operations() {
    std::println("--- Max-Heap Basics ---");
    std::priority_queue<int> pq;
    
    for (int n : {10, 30, 20, 5, 40}) {
        pq.push(n);
    }
    
    std::println("Priority Queue top: {}", pq.top()); // Should be 40
    
    std::print("Popping all: ");
    while (!pq.empty()) {
        std::print("{} ", pq.top());
        pq.pop();
    }
    std::println("");
}

/**
 * @brief Shows how to create a min-heap.
 */
void min_heap_demonstration() {
    std::println("\n--- Min-Heap Demonstration ---");
    // Syntax: priority_queue<Type, Container, Comparator>
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
    
    for (int n : {10, 30, 20, 5, 40}) {
        min_pq.push(n);
    }
    
    std::println("Min-heap top: {}", min_pq.top()); // Should be 5
}

/**
 * @brief Custom objects with complex priority logic.
 */
struct Job {
    int priority;
    std::string name;
    
    // Custom comparator for min-heap by priority
    bool operator>(const Job& other) const {
        return priority > other.priority;
    }
};

void custom_objects() {
    std::println("\n--- Custom Objects with Lambda Comparator ---");
    
    auto comp = [](const Job& a, const Job& b) {
        return a.priority < b.priority; // Max-heap by priority
    };
    
    std::priority_queue<Job, std::vector<Job>, decltype(comp)> pq(comp);
    
    pq.push({1, "Low priority task"});
    pq.push({10, "Critical task"});
    pq.push({5, "Medium priority task"});
    
    std::println("Next task: {}", pq.top().name);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Heapify Complexity: Building a heap from a vector is O(N). Repeatedly pushing N elements is O(N log N).");
    std::println("2. Top Access: top() is O(1), but you cannot modify the top element directly (it would break the heap property).");
    std::println("3. Performance: std::priority_queue is very fast, but if you need to decrease-key (like in Dijkstra), it doesn't support it efficiently. You often have to push a new entry and ignore stale ones.");
    std::println("4. Default: Max-heap uses `std::less`. Min-heap uses `std::greater`.");
}

/**
 * @brief Complexity:
 * - Push: O(log N)
 * - Pop: O(log N)
 * - Top: O(1)
 */
int main() {
    basic_operations();
    min_heap_demonstration();
    custom_objects();
    interview_notes();
    return 0;
}
