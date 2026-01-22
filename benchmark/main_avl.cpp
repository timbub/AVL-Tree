#include <iostream>
#include "../avl/tree.hpp"
#include "benchmark.hpp"
#include <vector>


int main(int argc, char* argv[]) {
    std::vector<benchmark::Operation> operations;
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
    std::cout << "avl: " << avl_time << "us\n";
 
    return 0;
}
