/*
Title: Disjoint Set Union (DSU) Complete Guide
Category: DSA Patterns
File: disjoint_set_union.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Implementation of the Disjoint Set Union (DSU) or Union-Find data structure. 
Features path compression and union by rank for near O(1) amortized operations.

Compile:
g++ -std=c++23 disjoint_set_union.cpp -o disjoint_set_union

Run:
./disjoint_set_union

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Path Compression
- Union by Rank/Size
- Cycle Detection in UnDirected Graphs
- Kruskal's Algorithm (Concept)
- Time Complexity: O(α(N)) (Inverse Ackermann)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <numeric>
#include <print>

/**
 * @brief Disjoint Set Union (DSU) class.
 * Efficiently handles disjoint set operations.
 */
class DSU {
    std::vector<int> parent;
    std::vector<int> rank;
    int num_components;

public:
    explicit DSU(int n) : num_components(n) {
        parent.resize(n);
        // Initially, each element is its own parent
        std::iota(parent.begin(), parent.end(), 0);
        rank.assign(n, 0);
    }

    /**
     * @brief Find operation with Path Compression.
     * Recursively flattens the tree.
     */
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    /**
     * @brief Union operation with Union by Rank.
     * Merges the smaller tree under the larger tree.
     * @return true if union happened, false if they were already in same set.
     */
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_i] = root_j;
                rank[root_j]++;
            }
            num_components--;
            return true;
        }
        return false;
    }

    int count_components() const {
        return num_components;
    }

    bool is_connected(int i, int j) {
        return find(i) == find(j);
    }
};

// --- Demos ---

void demo_dsu_basic() {
    std::println("\n--- DSU Basic Demo ---");
    DSU dsu(10); // 10 elements (0-9)
    
    dsu.unite(1, 2);
    dsu.unite(2, 3);
    dsu.unite(4, 5);
    
    std::println("1 and 3 connected? {}", dsu.is_connected(1, 3)); // Yes
    std::println("1 and 4 connected? {}", dsu.is_connected(1, 4)); // No
    std::println("Number of components: {}", dsu.count_components()); // 10 - 3 = 7
}

void demo_cycle_detection() {
    std::println("\n--- DSU Cycle Detection (Undirected) ---");
    // Graph: 0-1, 1-2, 2-0 (Triangle)
    DSU dsu(3);
    std::vector<std::pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}};
    
    for (auto [u, v] : edges) {
        if (!dsu.unite(u, v)) {
            std::println("Cycle detected when adding edge ({}, {})", u, v);
        } else {
            std::println("Added edge ({}, {})", u, v);
        }
    }
}

/**
 * Interview Pitfalls & Production Notes:
 * 1. Path Compression: Essential for O(α(N)) performance. Without it, 
 *    the structure can degrade to a linked list O(N).
 * 2. Union by Rank vs Size: Both are effective. Rank approximates height, 
 *    while Size keeps track of element count.
 * 3. Inverse Ackermann: Amortized complexity is practically constant O(1) 
 *    for any realistic N.
 * 4. Use Cases: Cycle detection in undirected graphs, Kruskal's MST, 
 *    dynamic connectivity, image processing (connected components).
 * 5. Memory: O(N) space for parent and rank arrays.
 */

int main() {
    demo_dsu_basic();
    demo_cycle_detection();
    return 0;
}
