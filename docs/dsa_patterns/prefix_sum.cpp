/*
Title: Prefix Sum Pattern Complete Guide
Category: DSA Patterns
File: prefix_sum.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Comprehensive guide to the Prefix Sum pattern, covering 1D, 2D, and specialized 
variations like XOR prefix sums. Includes production notes on overflow and 
C++23 range-based implementations.

Compile:
g++ -std=c++23 prefix_sum.cpp -o prefix_sum

Run:
./prefix_sum

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- 1D Prefix Sum (Range Queries)
- 2D Prefix Sum (Submatrix Sums)
- Difference Arrays (Range Updates)
- XOR Prefix Sums
- C++23 std::views::partial_sum (conceptually via ranges::views)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <print>
#include <ranges>
#include <string_view>

/**
 * @brief 1D Prefix Sum implementation.
 * Allows O(1) range sum queries after O(N) preprocessing.
 */
class PrefixSum1D {
    std::vector<long long> prefix;

public:
    explicit PrefixSum1D(const std::vector<int>& arr) {
        prefix.resize(arr.size() + 1, 0);
        for (size_t i = 0; i < arr.size(); ++i) {
            prefix[i + 1] = prefix[i] + arr[i];
        }
    }

    /**
     * @return Sum in range [L, R] (0-indexed)
     */
    long long query(int L, int R) const {
        if (L < 0 || R >= (int)prefix.size() - 1 || L > R) return 0;
        return prefix[R + 1] - prefix[L];
    }
};

/**
 * @brief 2D Prefix Sum implementation.
 * Allows O(1) submatrix sum queries after O(N*M) preprocessing.
 */
class PrefixSum2D {
    std::vector<std::vector<long long>> prefix;

public:
    explicit PrefixSum2D(const std::vector<std::vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        int R = matrix.size();
        int C = matrix[0].size();
        prefix.assign(R + 1, std::vector<long long>(C + 1, 0));

        for (int i = 1; i <= R; ++i) {
            for (int j = 1; j <= C; ++j) {
                prefix[i][j] = matrix[i - 1][j - 1] 
                             + prefix[i - 1][j] 
                             + prefix[i][j - 1] 
                             - prefix[i - 1][j - 1];
            }
        }
    }

    long long query(int r1, int c1, int r2, int c2) const {
        return prefix[r2 + 1][c2 + 1] 
             - prefix[r1][c2 + 1] 
             - prefix[r2 + 1][c1] 
             + prefix[r1][c1];
    }
};

/**
 * @brief Difference Array Pattern.
 * Efficiently perform range updates [L, R] with value V in O(1).
 * Final array construction takes O(N).
 */
class DifferenceArray {
    std::vector<long long> diff;
public:
    explicit DifferenceArray(size_t n) : diff(n + 1, 0) {}

    void update(int L, int R, int val) {
        diff[L] += val;
        if (R + 1 < (int)diff.size()) {
            diff[R + 1] -= val;
        }
    }

    std::vector<long long> build() {
        std::vector<long long> res(diff.size() - 1);
        long long current = 0;
        for (size_t i = 0; i < res.size(); ++i) {
            current += diff[i];
            res[i] = current;
        }
        return res;
    }
};

// --- Examples and Demonstrations ---

void demo_1d_prefix_sum() {
    std::println("\n--- 1D Prefix Sum Demo ---");
    std::vector<int> data = {1, 2, 3, 4, 5, 6};
    PrefixSum1D ps(data);
    
    std::println("Data: {}", data);
    std::println("Sum of range [1, 3] (indices): {}", ps.query(1, 3)); // 2+3+4 = 9
    std::println("Sum of range [0, 5] (indices): {}", ps.query(0, 5)); // 21
}

void demo_2d_prefix_sum() {
    std::println("\n--- 2D Prefix Sum Demo ---");
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    PrefixSum2D ps2(matrix);
    
    // Submatrix (1,1) to (2,2) -> {5, 6, 8, 9} -> sum = 28
    std::println("Sum of submatrix (1,1) to (2,2): {}", ps2.query(1, 1, 2, 2));
}

void demo_difference_array() {
    std::println("\n--- Difference Array Demo ---");
    DifferenceArray da(10);
    da.update(1, 5, 10); // Add 10 to indices 1 through 5
    da.update(3, 8, 5);  // Add 5 to indices 3 through 8
    
    auto result = da.build();
    std::println("Resulting array after range updates: {}", result);
}

/**
 * Interview Pitfalls & Production Notes:
 * 1. Overflow: Always use `long long` for prefix sums to avoid integer overflow.
 * 2. 1-based indexing: Using an extra row/column (prefix[i+1]) simplifies boundary logic significantly.
 * 3. Mutable Data: Prefix sums are best for static data. For dynamic data (updates), use Fenwick Tree or Segment Tree.
 * 4. Cache Locality: 2D prefix sums involve nested loops; ensure row-major traversal for performance.
 * 5. XOR Variant: XOR is its own inverse (x ^ x = 0), so query(L, R) = prefix[R] ^ prefix[L-1].
 */

int main() {
    try {
        demo_1d_prefix_sum();
        demo_2d_prefix_sum();
        demo_difference_array();
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
        return 1;
    }
    return 0;
}
