/*
Title: C++23 Condition Variables & Signaling
Category: Concurrency
File: condition_variable.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Teaches thread signaling and the Producer-Consumer pattern using std::condition_variable.
Explains spurious wakeups, predicates, and efficient thread notification.

Compile:
g++ -std=c++23 condition_variable.cpp -o condition_variable

Run:
./condition_variable

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::condition_variable (Signaling)
- Producer-Consumer Pattern
- Spurious Wakeups and Predicates
- wait(), notify_one(), notify_all()
- unique_lock vs lock_guard in CV contexts
- Thread-safe Message Queue implementation

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <print>
#include <chrono>

using namespace std::chrono_literals;

/**
 * PRODUCTION NOTE: Thread-Safe Queue
 * A common production pattern. Notice how we use unique_lock for the 
 * condition variable wait, but could use lock_guard for basic push.
 */
template<typename T>
class SafeQueue {
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool finished = false;

public:
    void push(T value) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            queue.push(std::move(value));
        }
        // notify_one() is enough if we only need one consumer to wake up.
        cv.notify_one();
    }

    // Producer calls this when no more data is coming
    void set_finished() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            finished = true;
        }
        cv.notify_all(); // Wake up all consumers to check the finished flag
    }

    /**
     * INTERVIEW PITFALL: Spurious Wakeups
     * A thread might wake up from wait() even if no notification happened.
     * ALWAYS use a predicate (lambda) or a while-loop to check the condition.
     */
    bool try_pop(T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // wait(lock, predicate)
        // This is equivalent to: while(!predicate()) cv.wait(lock);
        cv.wait(lock, [this] { return !queue.empty() || finished; });

        if (queue.empty()) {
            return false; // Queue is finished
        }

        value = std::move(queue.front());
        queue.pop();
        return true;
    }
};

void producer(SafeQueue<std::string>& q) {
    std::vector<std::string> messages = {"Hello", "Modern", "C++23", "Concurrency", "World"};
    
    for (const auto& msg : messages) {
        std::this_thread::sleep_for(50ms); // Simulate work
        std::println("Producer: Pushing '{}'", msg);
        q.push(msg);
    }
    
    std::println("Producer: Done.");
    q.set_finished();
}

void consumer(SafeQueue<std::string>& q, int id) {
    std::string msg;
    while (q.try_pop(msg)) {
        std::println("Consumer {}: Popped '{}'", id, msg);
        std::this_thread::sleep_for(100ms); // Simulate processing
    }
    std::println("Consumer {}: Finished.", id);
}

int main() {
    std::println("=== C++23 Condition Variable Demo ===");

    SafeQueue<std::string> message_queue;

    // Start 1 producer and 2 consumers
    // Using std::jthread for automatic joining
    std::jthread p(producer, std::ref(message_queue));
    std::jthread c1(consumer, std::ref(message_queue), 1);
    std::jthread c2(consumer, std::ref(message_queue), 2);

    /**
     * COMPLEXITY ANALYSIS:
     * - notify_one/notify_all: O(1)
     * - wait: O(1) from the perspective of the queue, but involves OS-level 
     *   thread blocking and rescheduling.
     * - Space: O(N) where N is the number of items in the queue.
     *
     * INTERVIEW PITFALLS:
     * 1. Not using a predicate: Spurious wakeups lead to logic errors.
     * 2. notify_one vs notify_all: Incorrectly using notify_one when multiple 
     *    threads need to react to a state change (like the 'finished' flag).
     * 3. Holding the lock during notification: It's technically allowed but
     *    not optimal. The woken thread immediately tries to re-acquire the lock
     *    still held by the notifying thread.
     */

    std::println("\n=== Main execution finished, waiting for threads... ===");
    return 0;
}
