#include <iostream>
#include "tree.hpp"

int main() {
    static constexpr char KEY = 'k';
    static constexpr char REQUEST = 'q';

    char type;
    int first_key, second_key;

    using namespace Tree;
    AvlTree<int> tree;
    while (std::cin >> type) {

        if (type == KEY) {

            std::cin >> first_key;
            tree.insert(first_key);

        } else if (type == REQUEST) {
            std::cin >> first_key >> second_key;
            std::cout << tree.count_in_range(first_key, second_key) << " ";
        }
    }
    return 0;
}
