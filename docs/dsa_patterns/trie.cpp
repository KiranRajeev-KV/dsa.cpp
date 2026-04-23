/*
Title: Trie (Prefix Tree) Complete Guide
Category: DSA Patterns
File: trie.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Detailed implementation of a Trie (Prefix Tree) and a Bitwise Trie. 
Focuses on memory management using smart pointers and efficient string retrieval.

Compile:
g++ -std=c++23 trie.cpp -o trie

Run:
./trie

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Standard Trie (Character-based)
- Bitwise Trie (Integer XOR problems)
- Memory safety with std::unique_ptr
- Search, Insert, and StartsWith operations
- Recursive vs Iterative Trie operations

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <string>
#include <memory>
#include <print>
#include <string_view>

/**
 * @brief Standard Trie Node for lowercase English letters.
 */
struct TrieNode {
    std::unique_ptr<TrieNode> children[26];
    bool is_end_of_word = false;

    TrieNode() {
        for (auto& child : children) child = nullptr;
    }
};

/**
 * @brief Prefix Tree (Trie) implementation.
 */
class Trie {
    std::unique_ptr<TrieNode> root;

public:
    Trie() : root(std::make_unique<TrieNode>()) {}

    void insert(std::string_view word) {
        TrieNode* curr = root.get();
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) {
                curr->children[idx] = std::make_unique<TrieNode>();
            }
            curr = curr->children[idx].get();
        }
        curr->is_end_of_word = true;
    }

    bool search(std::string_view word) const {
        TrieNode* curr = root.get();
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) return false;
            curr = curr->children[idx].get();
        }
        return curr->is_end_of_word;
    }

    bool starts_with(std::string_view prefix) const {
        TrieNode* curr = root.get();
        for (char c : prefix) {
            int idx = c - 'a';
            if (!curr->children[idx]) return false;
            curr = curr->children[idx].get();
        }
        return true;
    }
};

/**
 * @brief Bitwise Trie (Binary Trie).
 * Often used to find maximum XOR of two numbers in an array.
 */
struct BinaryTrieNode {
    std::unique_ptr<BinaryTrieNode> children[2];
};

class BinaryTrie {
    std::unique_ptr<BinaryTrieNode> root;

public:
    BinaryTrie() : root(std::make_unique<BinaryTrieNode>()) {}

    void insert(int num) {
        BinaryTrieNode* curr = root.get();
        // Assuming 31-bit integers
        for (int i = 30; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!curr->children[bit]) {
                curr->children[bit] = std::make_unique<BinaryTrieNode>();
            }
            curr = curr->children[bit].get();
        }
    }

    int find_max_xor(int num) const {
        BinaryTrieNode* curr = root.get();
        int max_xor = 0;
        for (int i = 30; i >= 0; --i) {
            int bit = (num >> i) & 1;
            // To maximize XOR, we want the opposite bit
            int target = 1 - bit;
            if (curr->children[target]) {
                max_xor |= (1 << i);
                curr = curr->children[target].get();
            } else if (curr->children[bit]) {
                curr = curr->children[bit].get();
            } else {
                return 0; // Empty trie case
            }
        }
        return max_xor;
    }
};

// --- Demos ---

void demo_string_trie() {
    std::println("\n--- String Trie Demo ---");
    Trie t;
    t.insert("apple");
    std::println("Search 'apple': {}", t.search("apple"));   // true
    std::println("Search 'app': {}", t.search("app"));       // false
    std::println("StartsWith 'app': {}", t.starts_with("app")); // true
    t.insert("app");
    std::println("Search 'app' after insert: {}", t.search("app")); // true
}

void demo_binary_trie() {
    std::println("\n--- Binary Trie (Max XOR) Demo ---");
    std::vector<int> nums = {3, 10, 5, 25, 2, 8};
    BinaryTrie bt;
    for (int n : nums) bt.insert(n);
    
    int max_result = 0;
    for (int n : nums) {
        max_result = std::max(max_result, bt.find_max_xor(n));
    }
    std::println("Max XOR in {}: {}", nums, max_result); // 25 ^ 5 = 28
}

/**
 * Interview Pitfalls & Production Notes:
 * 1. Memory Overhead: Tries can be memory-heavy. Each node has an array of 
 *    pointers. For Unicode or large alphabets, consider using `std::map` or 
 *    `std::unordered_map` for children.
 * 2. Smart Pointers: Using `std::unique_ptr` ensures that when the Trie goes 
 *    out of scope, the entire tree is cleaned up recursively without leaks.
 * 3. Deletion: Deletion in a Trie is tricky. It usually involves recursive 
 *    cleanup of nodes that are no longer part of any word.
 * 4. Compression: Radix Trees (Compressed Tries) merge nodes with a single 
 *    child to save space.
 * 5. Bitwise Trie: Excellent for bit manipulation problems and competitive 
 *    programming.
 */

int main() {
    demo_string_trie();
    demo_binary_trie();
    return 0;
}
