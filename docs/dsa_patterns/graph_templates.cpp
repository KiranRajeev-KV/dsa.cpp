/*
Title: Graph Algorithms Templates Guide
Category: DSA Patterns
File: graph_templates.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Production-grade templates for fundamental graph algorithms: DFS, BFS, and 
Topological Sort. Uses C++23 std::expected for error handling in cycle detection.

Compile:
g++ -std=c++23 graph_templates.cpp -o graph_templates

Run:
./graph_templates

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Adjacency List Representation
- Depth First Search (DFS)
- Breadth First Search (BFS)
- Topological Sort (Kahn's Algorithm)
- Cycle Detection in Directed Graphs
- C++23 std::expected and std::print usage

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <queue>
#include <print>
#include <expected>
#include <string_view>

/**
 * @brief Directed Graph representation using Adjacency List.
 */
class Graph {
    int num_vertices;
    std::vector<std::vector<int>> adj;

public:
    explicit Graph(int v) : num_vertices(v), adj(v) {}

    void add_edge(int u, int v) {
        if (u < num_vertices && v < num_vertices) {
            adj[u].push_back(v);
        }
    }

    int size() const { return num_vertices; }
    const std::vector<int>& neighbors(int u) const { return adj[u]; }

    /**
     * @brief Breadth-First Search (BFS).
     * Useful for finding shortest paths in unweighted graphs.
     */
    void bfs(int start_node) const {
        std::vector<bool> visited(num_vertices, false);
        std::queue<int> q;

        visited[start_node] = true;
        q.push(start_node);

        std::print("BFS from {}: ", start_node);
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            std::print("{} ", curr);

            for (int neighbor : adj[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        std::println();
    }

    /**
     * @brief Depth-First Search (DFS) recursive.
     */
    void dfs(int start_node) const {
        std::vector<bool> visited(num_vertices, false);
        std::print("DFS from {}: ", start_node);
        dfs_util(start_node, visited);
        std::println();
    }

    /**
     * @brief Topological Sort using Kahn's Algorithm.
     * @return Sorted nodes or an error if a cycle is detected.
     */
    std::expected<std::vector<int>, std::string_view> topological_sort() const {
        std::vector<int> in_degree(num_vertices, 0);
        for (int u = 0; u < num_vertices; ++u) {
            for (int v : adj[u]) {
                in_degree[v]++;
            }
        }

        std::queue<int> q;
        for (int i = 0; i < num_vertices; ++i) {
            if (in_degree[i] == 0) q.push(i);
        }

        std::vector<int> sorted_order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            sorted_order.push_back(u);

            for (int v : adj[u]) {
                if (--in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }

        if (sorted_order.size() != (size_t)num_vertices) {
            return std::unexpected("Cycle detected in graph!");
        }

        return sorted_order;
    }

private:
    void dfs_util(int u, std::vector<bool>& visited) const {
        visited[u] = true;
        std::print("{} ", u);
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs_util(v, visited);
            }
        }
    }
};

// --- Demos ---

void demo_traversals() {
    std::println("\n--- BFS and DFS Demo ---");
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(2, 5);

    g.bfs(0);
    g.dfs(0);
}

void demo_topo_sort() {
    std::println("\n--- Topological Sort Demo ---");
    Graph g(6);
    g.add_edge(5, 2);
    g.add_edge(5, 0);
    g.add_edge(4, 0);
    g.add_edge(4, 1);
    g.add_edge(2, 3);
    g.add_edge(3, 1);

    auto result = g.topological_sort();
    if (result) {
        std::println("Topological Order: {}", *result);
    } else {
        std::println("Error: {}", result.error());
    }

    std::println("\n--- Cycle Detection Demo ---");
    Graph cyclic(3);
    cyclic.add_edge(0, 1);
    cyclic.add_edge(1, 2);
    cyclic.add_edge(2, 0);
    auto cyclic_res = cyclic.topological_sort();
    if (!cyclic_res) {
        std::println("Expected error: {}", cyclic_res.error());
    }
}

/**
 * Interview Pitfalls & Production Notes:
 * 1. Graph Storage: Adjacency list (O(V+E) space) is almost always better than 
 *    adjacency matrix (O(V^2)) unless the graph is extremely dense.
 * 2. Connectivity: BFS/DFS only visit nodes reachable from the start node. 
 *    To visit all nodes, loop over all vertices.
 * 3. Topological Sort: Only applies to DAGs (Directed Acyclic Graphs). Cycles 
 *    break the ordering.
 * 4. Recursion Limit: DFS can hit stack overflow on very deep graphs (e.g., 
 *    linked-list style). Consider iterative DFS with `std::stack` for production.
 * 5. Kahn's Algorithm: Uses in-degree to find nodes with no dependencies.
 */

int main() {
    demo_traversals();
    demo_topo_sort();
    return 0;
}
