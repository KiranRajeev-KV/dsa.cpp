/*
Title: Cache-Friendly C++: Data Locality and Performance
Category: Memory & Performance
File: cache_friendly_cpp.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
To demonstrate how CPU cache architecture impacts C++ performance. This guide covers
spatial and temporal locality, false sharing, and the performance differences
between Array of Structures (AoS) and Structure of Arrays (SoA).

Compile:
g++ -std=c++23 -O3 cache_friendly_cpp.cpp -o cache_friendly_cpp

Run:
./cache_friendly_cpp

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- CPU Cache Hierarchy (L1, L2, L3)
- Cache Lines and Row-Major vs. Column-Major traversal
- False Sharing and std::hardware_destructive_interference_size
- Array of Structures (AoS) vs. Structure of Arrays (SoA)
- Using C++23 std::mdspan for cache-aware matrix access

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <chrono>
#include <print>
#include <array>
#if __has_include(<mdspan>)
#include <mdspan>
#define HAS_MDSPAN 1
#else
#define HAS_MDSPAN 0
#endif
#include <atomic>
#include <thread>
#include <new> // for hardware_destructive_interference_size

/**
 * @brief Measures execution time of a function.
 */
template <typename Func>
auto measure_time(Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

/**
 * @brief Demonstrates Row-Major (Cache-Friendly) vs. Column-Major (Cache-Unfriendly) access.
 * 
 * Matrices in C++ are stored in Row-Major order. Accessing elements row by row
 * utilizes spatial locality (loading a cache line brings in subsequent elements).
 * Accessing column by column causes frequent cache misses.
 */
void demonstrate_locality() {
    std::println("\n--- 1. Spatial Locality: Row-Major vs Column-Major ---");

    constexpr size_t ROWS = 10000;
    constexpr size_t COLS = 10000;
    
    // Using a flat vector to represent a 2D matrix
    std::vector<int> matrix(ROWS * COLS, 1);

    // Row-Major (Fast)
    auto row_time = measure_time([&]() {
        long long sum = 0;
        for (size_t i = 0; i < ROWS; ++i) {
            for (size_t j = 0; j < COLS; ++j) {
                sum += matrix[i * COLS + j];
            }
        }
        // Black hole to prevent optimization
        [[maybe_unused]] auto volatile v = sum;
    });

    // Column-Major (Slow)
    auto col_time = measure_time([&]() {
        long long sum = 0;
        for (size_t j = 0; j < COLS; ++j) {
            for (size_t i = 0; i < ROWS; ++i) {
                sum += matrix[i * COLS + j];
            }
        }
        [[maybe_unused]] auto volatile v = sum;
    });

    std::println("  Row-Major access:    {} us", row_time);
    std::println("  Column-Major access: {} us", col_time);
    std::println("  Performance ratio:   {:.2f}x faster", (double)col_time / row_time);
}

/**
 * @brief Demonstrates AoS vs SoA for cache efficiency.
 * 
 * In AoS, all data for an entity is grouped. In SoA, separate arrays are used for 
 * each attribute. SoA is often better for SIMD and cache if only certain 
 * attributes are needed frequently.
 */
struct ParticleAoS {
    float x, y, z;
    float vx, vy, vz;
    int id;
};

struct ParticleSoA {
    std::vector<float> x, y, z;
    std::vector<float> vx, vy, vz;
    std::vector<int> id;
};

void demonstrate_aos_soa() {
    std::println("\n--- 2. AoS vs SoA (Design for Cache) ---");
    
    constexpr size_t N = 1'000'000;
    
    // AoS setup
    std::vector<ParticleAoS> aos(N);
    
    // SoA setup
    ParticleSoA soa;
    soa.x.resize(N); soa.y.resize(N); soa.z.resize(N);
    soa.vx.resize(N); soa.vy.resize(N); soa.vz.resize(N);
    soa.id.resize(N);

    // Goal: Update positions using velocities
    auto aos_time = measure_time([&]() {
        for (auto& p : aos) {
            p.x += p.vx;
            p.y += p.vy;
            p.z += p.vz;
        }
    });

    auto soa_time = measure_time([&]() {
        for (size_t i = 0; i < N; ++i) {
            soa.x[i] += soa.vx[i];
            soa.y[i] += soa.vy[i];
            soa.z[i] += soa.vz[i];
        }
    });

    std::println("  AoS Update time: {} us", aos_time);
    std::println("  SoA Update time: {} us", soa_time);
    std::println("  SoA/AoS ratio:   {:.2f}x", (double)soa_time / aos_time);
    std::println("  Note: SoA shines when only subset of fields are accessed or for SIMD.");
}

/**
 * @brief Demonstrates False Sharing.
 * 
 * Occurs when two threads modify different variables that reside on the same 
 * cache line. This causes the cache line to bounce between cores (ping-ponging).
 */
void demonstrate_false_sharing() {
    std::println("\n--- 3. False Sharing and Padding ---");

    struct BadCounter {
        std::atomic<int> c1;
        std::atomic<int> c2;
    };

    // Use C++17/20/23 feature for proper alignment to avoid false sharing
#ifdef __cpp_lib_hardware_interference_size
    struct GoodCounter {
        alignas(std::hardware_destructive_interference_size) std::atomic<int> c1;
        alignas(std::hardware_destructive_interference_size) std::atomic<int> c2;
    };
#else
    struct GoodCounter {
        alignas(64) std::atomic<int> c1;
        alignas(64) std::atomic<int> c2;
    };
#endif

    auto run_test = [](auto& counters) {
        auto t1 = std::thread([&]() {
            for(int i=0; i<10'000'000; ++i) counters.c1++;
        });
        auto t2 = std::thread([&]() {
            for(int i=0; i<10'000'000; ++i) counters.c2++;
        });
        t1.join();
        t2.join();
    };

    BadCounter bad;
    auto bad_time = measure_time([&]() { run_test(bad); });

    GoodCounter good;
    auto good_time = measure_time([&]() { run_test(good); });

    std::println("  Bad (False Sharing) time:  {} us", bad_time);
    std::println("  Good (Padded) time:        {} us", good_time);
    std::println("  Performance ratio:         {:.2f}x faster", (double)bad_time / good_time);
}

/**
 * @brief C++23 std::mdspan for better matrix abstractions.
 */
void demonstrate_mdspan() {
    std::println("\n--- 4. C++23 std::mdspan ---");
#if HAS_MDSPAN
    std::vector<double> data(100, 0.0);
    
    // Create a 10x10 view over the data
    auto ms = std::mdspan(data.data(), 10, 10);
    
    ms[2, 3] = 42.0; // New C++23 multidimensional operator[]
    
    std::println("  ms[2, 3] = {}", ms[2, 3]);
    std::println("  Data size: {} elements", ms.size());
#else
    std::println("  std::mdspan is not supported in this environment (Header <mdspan> not found).");
#endif
}

int main() {
    std::println("C++23 Memory & Performance: Cache Friendly Code");
    
    demonstrate_locality();
    demonstrate_aos_soa();
    demonstrate_false_sharing();
    demonstrate_mdspan();

    return 0;
}

/*
Complexity Analysis:
- Row-Major Access: O(N*M), where N is Rows and M is Columns. Practically O(1) cache miss rate.
- Column-Major Access: O(N*M). Practically O(N*M) cache miss rate if matrix is large.
- SoA/AoS: Both O(N). Performance difference is a constant factor based on cache line utilization.

Production Notes:
1. Always prefer row-major traversal for standard C++ containers.
2. Use std::hardware_destructive_interference_size to ensure high-performance 
   concurrency without false sharing.
3. Consider Data-Oriented Design (DoD) where data layout follows access patterns.
4. Profilers like 'perf' (Linux) or VTune are essential for diagnosing cache misses.

Interview Pitfalls:
- Forgetting that multidimensional arrays (e.g., int a[10][10]) are row-major in C++.
- Underestimating the impact of false sharing in multi-threaded code.
- Thinking that O(N) is the only metric that matters; constant factors from 
  cache misses can make an O(N) algorithm slower than an O(N log N) one.
*/
