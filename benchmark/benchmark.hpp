#pragma once
namespace benchmark {
    static constexpr char KEY = 'k';
    static constexpr char REQUEST = 'q';
    struct Operation {
        char type;
        int first;
        int second;
    };

    template <typename KeyT>
    size_t perform_query(Tree::AvlTree<KeyT>& tree, KeyT first, KeyT second) {
        return tree.range_required(first, second);
    }

    template <typename KeyT, typename SetTree>
    size_t perform_query(SetTree& tree, KeyT left, KeyT right) {
        auto left_bound  = tree.upper_bound(left);
        auto right_bound = tree.upper_bound(right);
        return std::distance(left_bound, right_bound);
    }

    template <typename TreeType>
    long long run_benchmark(TreeType& tree, const std::vector<Operation> ops) {
        using Clock = std::chrono::high_resolution_clock;
        using Ns    = std::chrono::microseconds;

        long long total_time = 0;
        for (const auto& op: ops) {
            if (op.type == KEY) {
                auto start = Clock::now();
                tree.insert(op.first);
                auto end = Clock::now();
                total_time += std::chrono::duration_cast<Ns>(end - start).count();
            } else if (op.type == REQUEST) {
                auto start = Clock::now();
                volatile size_t distance = perform_query(tree, op.first, op.second);
                auto end = Clock::now();
                total_time += std::chrono::duration_cast<Ns>(end - start).count();
            }
        }
        return total_time;
    }
}

