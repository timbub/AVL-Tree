#include <iostream>
#include "tree.hpp"

int main() {
    try {
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
                std::cout << tree.range_required(first_key, second_key) << " ";
            }
        }
        std::cout << "\n";
    }
    catch(const std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << "\n";
    }
    catch(const std::bad_alloc& e) {
        std::cerr << "Not enough memory/n";
    }
    catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Unknown error/n";
    }
    return 0;
}
