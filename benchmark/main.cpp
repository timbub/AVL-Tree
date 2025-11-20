#include <iostream>
#include <chrono>
#include "../avl/tree.hpp"
#include "benchmark.hpp"
#include <set>
#include <vector>
#include <iterator>

int main(int argc, char* argv[]) {
    std::vector<benchmark::Operation> operations;
    std::set<int> set;
    Tree::AvlTree<int> avl;
    char type;

    while (std::cin >> type) {
        benchmark::Operation op;
        op.type = type;
        if (type == benchmark::KEY) {
            std::cin >> op.first;
        } else if (type == benchmark::REQUEST) {
            std::cin >> op.first >> op.second;
        }
        operations.push_back(op);
    }

    long long avl_time = benchmark::run_benchmark(avl, operations);
    long long set_time = benchmark::run_benchmark(set, operations);

    std::cout << "set: " << set_time << "ms\n ";
    std::cout << "avl: " << avl_time << "ms\n";

    return 0;
}
