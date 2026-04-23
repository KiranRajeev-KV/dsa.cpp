/*
Title: C++23 Async, Futures, and Promises
Category: Concurrency
File: async_future.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Covers task-based concurrency as an alternative to thread-based concurrency.
Demonstrates std::async, std::future, std::promise, and std::packaged_task.

Compile:
g++ -std=c++23 async_future.cpp -o async_future

Run:
./async_future

Key Topics:
- std::async and launch policies (async, deferred)
- std::future (Single-use result)
- std::shared_future (Multiple-use result)
- std::promise (Providing a value to a future)
- std::packaged_task (Wrapping a function for async execution)
- Exception propagation across thread boundaries

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <future>
#include <thread>
#include <chrono>
#include <print>
#include <stdexcept>

using namespace std::chrono_literals;

// 1. A slow computation function
int slow_task(int x, int y) {
    std::println("Task: Starting calculation for {}, {}...", x, y);
    std::this_thread::sleep_for(200ms);
    return x + y;
}

// 2. Exception handling in futures
void risky_task() {
    std::this_thread::sleep_for(100ms);
    throw std::runtime_error("Something went wrong in the async task!");
}

// 3. std::promise / std::future pair
void promise_worker(std::promise<int> p) {
    try {
        std::this_thread::sleep_for(100ms);
        p.set_value(42); // Fulfill the promise
    } catch (...) {
        p.set_exception(std::current_exception());
    }
}

int main() {
    std::println("=== C++23 Async & Futures Guide ===");

    // --- 1. Basic std::async ---
    {
        std::println("\n[1] Basic std::async");
        // std::launch::async: starts task in a separate thread immediately
        // std::launch::deferred: starts task only when .get() or .wait() is called
        std::future<int> result = std::async(std::launch::async, slow_task, 10, 20);

        std::println("Main: Doing other work...");
        std::this_thread::sleep_for(50ms);

        std::println("Main: Result from async task: {}", result.get()); // Blocks until ready
    }

    // --- 2. Exception Propagation ---
    {
        std::println("\n[2] Exception Propagation");
        auto f = std::async(risky_task);
        
        try {
            f.get(); // Re-throws the exception from the other thread
        } catch (const std::exception& e) {
            std::println("Caught expected exception: {}", e.what());
        }
    }

    // --- 3. std::promise and std::future ---
    {
        std::println("\n[3] std::promise & std::future Manual Control");
        std::promise<int> prom;
        std::future<int> fut = prom.get_future();
        
        std::jthread t(promise_worker, std::move(prom));
        
        std::println("Waiting for promise...");
        std::println("Promise result: {}", fut.get());
    }

    // --- 4. std::packaged_task ---
    {
        std::println("\n[4] std::packaged_task");
        // packaged_task wraps a callable and provides a future
        std::packaged_task<int(int, int)> task(slow_task);
        std::future<int> fut = task.get_future();
        
        // We can choose WHEN and WHERE to execute the task
        std::jthread t(std::move(task), 5, 5);
        
        std::println("Packaged task result: {}", fut.get());
    }

    // --- 5. std::shared_future ---
    {
        std::println("\n[5] std::shared_future");
        // std::future is move-only. shared_future can be copied to multiple threads.
        std::shared_future<int> sf = std::async(slow_task, 1, 2).share();
        
        auto reader = [sf](int id) {
            std::println("Reader {}: Result is {}", id, sf.get());
        };

        std::jthread t1(reader, 1);
        std::jthread t2(reader, 2);
    }

    /**
     * COMPLEXITY ANALYSIS:
     * - std::async (async): Creates a thread (O(1) logic, but expensive).
     * - Future retrieval: O(1).
     * - Future wait/get: Blocks calling thread.
     *
     * INTERVIEW PITFALLS:
     * 1. std::async Destructor: The future returned by std::async will block in 
     *    its destructor if the launch policy is std::launch::async. 
     *    Storing the future is mandatory to avoid blocking immediately!
     * 2. Double get(): Calling .get() twice on a regular std::future is UB. 
     *    Use std::shared_future if multiple threads need the result.
     * 3. Blocking: Future .get() is a blocking operation.
     * 
     * PRODUCTION NOTES:
     * - Task-based concurrency (async) is generally preferred over raw threads 
     *   when you just want a result back.
     * - For high-throughput servers, consider custom thread pools instead of 
     *   spawning a new thread via std::async every time.
     */

    std::println("\n=== Async demonstration complete ===");
    return 0;
}
