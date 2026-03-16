#pragma once
#include "../avl/tree.hpp"
#include <chrono>
#include <set>
#include <vector>
#include <iterator>
namespace benchmark {
    static constexpr char KEY = 'k';
    static constexpr char REQUEST = 'q';
    static constexpr int US_PER_Us = 1000;

    struct Operation {
        char type;
        int first;
        int second;
    };

    template <typename KeyT>
    size_t perform_query(Tree::AvlTree<KeyT>& tree, KeyT first, KeyT second) {
        return tree.range_required(first, second);
    }

    template <typename KeyT>
    size_t perform_query(std::set<KeyT>& tree, KeyT left, KeyT right) {
        if (left > right) return 0;
        auto left_bound  = tree.lower_bound(left);
        auto right_bound = tree.upper_bound(right);
        return std::distance(left_bound, right_bound);
    }

    template <typename TreeType>
    long long run_benchmark(TreeType& tree, const std::vector<Operation> ops) {
        using Clock = std::chrono::high_resolution_clock;
        using Us    = std::chrono::microseconds;

        long long total_time = 0;
        for (const auto& op: ops) {
            if (op.type == KEY) {
                auto start = Clock::now();
                tree.insert(op.first);
                auto end = Clock::now();
                total_time += std::chrono::duration_cast<Us>(end - start).count();
            } else if (op.type == REQUEST) {
                auto start = Clock::now();
                volatile size_t distance = perform_query(tree, op.first, op.second);
                auto end = Clock::now();
                total_time += std::chrono::duration_cast<Us>(end - start).count();
            }
        }
        return total_time;
    }
}

