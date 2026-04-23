/*
Title: std::queue Complete Guide
Category: Container Adapters
File: queue.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::queue, a FIFO (First-In-First-Out) container adapter.
Covers usage patterns, underlying containers, and concurrency considerations.

Compile:
g++ -std=c++23 queue.cpp -o queue

Run:
./queue

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- FIFO Principle
- push, pop, front, back
- Container Adapters (Default: deque)
- Production Use Cases: Task scheduling, BFS (Breadth-First Search)
- Why no clear() method?

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <queue>
#include <list>
#include <print>
#include <string>

/**
 * @brief Demonstrates basic queue operations.
 */
void basic_operations() {
    std::println("--- Queue Basics ---");
    std::queue<std::string> q;
    
    q.push("Task 1");
    q.push("Task 2");
    q.emplace("Task 3");
    
    std::println("Queue front: {}", q.front());
    std::println("Queue back: {}", q.back());
    std::println("Queue size: {}", q.size());
    
    q.pop();
    std::println("After pop, front: {}", q.front());
}

/**
 * @brief Shows alternative underlying containers.
 */
void underlying_containers() {
    std::println("\n--- Underlying Containers ---");
    
    // Using list as base (O(1) push/pop at both ends)
    std::queue<int, std::list<int>> list_queue;
    
    list_queue.push(100);
    std::println("List-based queue front: {}", list_queue.front());
    
    // Note: vector cannot be used as a base for queue because it lacks pop_front()
    // std::queue<int, std::vector<int>> v_q; // Error
}

/**
 * @brief Practical Example: Simple BFS traversal logic.
 */
void bfs_mock() {
    std::println("\n--- BFS Mock Logic ---");
    std::queue<int> q;
    q.push(1); // Start node
    
    std::print("Processing nodes: ");
    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        std::print("{} ", curr);
        
        // Simulating adding neighbors
        if (curr < 3) {
            q.push(curr + 1);
            q.push(curr + 2);
        }
    }
    std::println("");
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. NO ITERATORS: Like stack, queue restricts access to front and back only.");
    std::println("2. pop() returns void: Must call front() then pop().");
    std::println("3. Memory Leak Pitfall: Always check .empty() before calling .front() or .pop(). Accessing front of empty queue is undefined behavior.");
    std::println("4. Concurrency: std::queue is NOT thread-safe. Use a mutex-protected wrapper or a lock-free queue for multi-threaded producer-consumer patterns.");
}

/**
 * @brief Complexity:
 * - Push/Pop/Front/Back: O(1)
 * - Space: O(N)
 */
int main() {
    basic_operations();
    underlying_containers();
    bfs_mock();
    interview_notes();
    return 0;
}
