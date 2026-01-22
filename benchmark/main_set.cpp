#include <iostream>
#include "benchmark.hpp"
#include <set>
#include <vector>


int main(int argc, char* argv[]) {
    std::vector<benchmark::Operation> operations;
    std::set<int> set;
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

    long long set_time = benchmark::run_benchmark(set, operations);
    std::cout << "set: " << set_time << "us\n";

    return 0;
}
