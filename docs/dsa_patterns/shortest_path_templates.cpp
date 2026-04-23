/*
Title: Shortest Path Algorithms Templates Guide
Category: DSA Patterns
File: shortest_path_templates.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
Production-ready templates for shortest path algorithms on weighted graphs: 
Dijkstra (Non-negative weights) and Bellman-Ford (Handles negative weights).

Compile:
g++ -std=c++23 shortest_path_templates.cpp -o shortest_path_templates

Run:
./shortest_path_templates

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Dijkstra's Algorithm (Priority Queue optimized)
- Bellman-Ford Algorithm (Negative cycle detection)
- Graph Representation for weighted edges
- Complexity Analysis: O((V+E) log V) and O(V*E)
- C++23 std::print and ranges for data display

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <queue>
#include <limits>
#include <print>

const long long INF = std::numeric_limits<long long>::max();

struct Edge {
    int to;
    int weight;
};

struct NodeDist {
    int node;
    long long dist;
    
    // Greater than operator for min-priority queue
    bool operator>(const NodeDist& other) const {
        return dist > other.dist;
    }
};

/**
 * @brief Dijkstra's algorithm for shortest paths.
 * Works only with non-negative edge weights.
 * Complexity: O(E log V)
 */
std::vector<long long> dijkstra(int n, int start, const std::vector<std::vector<Edge>>& adj) {
    std::vector<long long> dist(n, INF);
    std::priority_queue<NodeDist, std::vector<NodeDist>, std::greater<NodeDist>> pq;

    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        auto [u, d] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                pq.push({edge.to, dist[edge.to]});
            }
        }
    }
    return dist;
}

/**
 * @brief Bellman-Ford algorithm.
 * Handles negative weights and detects negative cycles.
 * Complexity: O(V * E)
 */
struct BellmanResult {
    std::vector<long long> dist;
    bool has_negative_cycle;
};

BellmanResult bellman_ford(int n, int start, const std::vector<std::vector<Edge>>& adj) {
    std::vector<long long> dist(n, INF);
    dist[start] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            if (dist[u] == INF) continue;
            for (const auto& edge : adj[u]) {
                if (dist[u] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[u] + edge.weight;
                }
            }
        }
    }

    // Check for negative weight cycles
    bool cycle = false;
    for (int u = 0; u < n; ++u) {
        if (dist[u] == INF) continue;
        for (const auto& edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                cycle = true;
                break;
            }
        }
    }

    return {dist, cycle};
}

// --- Demos ---

void demo_dijkstra() {
    std::println("\n--- Dijkstra's Algorithm ---");
    int n = 5;
    std::vector<std::vector<Edge>> adj(n);
    adj[0].push_back({1, 10});
    adj[0].push_back({4, 3});
    adj[1].push_back({2, 2});
    adj[4].push_back({1, 1});
    adj[4].push_back({2, 8});
    adj[4].push_back({3, 2});
    adj[3].push_back({2, 5});

    auto dists = dijkstra(n, 0, adj);
    std::println("Shortest distances from 0: {}", dists);
    // Path 0->4->1->2 is 3+1+2=6.
}

void demo_bellman() {
    std::println("\n--- Bellman-Ford Algorithm ---");
    int n = 3;
    std::vector<std::vector<Edge>> adj(n);
    adj[0].push_back({1, 1});
    adj[1].push_back({2, -1});
    adj[2].push_back({0, -1}); // Negative cycle: 1 + (-1) + (-1) = -1

    auto res = bellman_ford(n, 0, adj);
    if (res.has_negative_cycle) {
        std::println("Negative cycle detected!");
    } else {
        std::println("Distances: {}", res.dist);
    }
}

/**
 * Interview Pitfalls & Production Notes:
 * 1. Edge Case: Disconnected nodes will retain `INF` distance. Always check 
 *    `dist[u] == INF` before relaxing its neighbors.
 * 2. Precision: For very large graphs or weights, `int` can overflow. Use 
 *    `long long` for distances.
 * 3. Priority Queue: In Dijkstra, ensure you use a min-heap (`std::greater`). 
 *    Standard `std::priority_queue` is a max-heap.
 * 4. Negative Weights: Dijkstra FAILS with negative weights. Use Bellman-Ford 
 *    or SPFA (Shortest Path Faster Algorithm).
 * 5. Negative Cycles: A negative cycle means no shortest path exists (it's -infinity).
 * 6. Performance: Dijkstra is much faster than Bellman-Ford. Only use 
 *    Bellman-Ford when negative weights are possible.
 */

int main() {
    demo_dijkstra();
    demo_bellman();
    return 0;
}
