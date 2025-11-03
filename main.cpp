#include <iostream>
#include "tree.hpp"

int main() {

    char type;
    int a, b;

    using namespace Tree;
    AvlTree<int> tree;
    while (std::cin >> type) {

        if (type == 'k') {

            std::cin >> a;
            std::cout << a << "\n";
            tree.insert(a);

        } else if (type == 'q') {
            std::cin >> a >> b;
            if (b <= a) {
                std::cout << 0 << "\n";
            } else {
                std::cout << "processing\n" ;
            }
        }
    }
    return 0;
}
