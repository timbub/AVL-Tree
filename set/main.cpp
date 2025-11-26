#include <iostream>
#include <set>
#include <iterator>

template <typename KeyT, typename SetTree>
size_t range_required(SetTree& set, KeyT& left, KeyT& right);

int main() {
    static constexpr char KEY = 'k';
    static constexpr char REQUEST = 'q';

    char type;
    int first_key, second_key;

    std::set<int> tree;
    while (std::cin >> type) {

        if (type == KEY) {
            std::cin >> first_key;
            tree.insert(first_key);

        } else if (type == REQUEST) {
            std::cin >> first_key >> second_key;
            std::cout << range_required(tree, first_key, second_key) << " ";
        }
    }
    std::cout << "\n";
    return 0;
}

template <typename KeyT, typename SetTree>
size_t range_required(SetTree& set, KeyT& left, KeyT& right) {
    if (left > right) return 0;
    auto left_bound  = set.upper_bound(left);
    auto right_bound = set.upper_bound(right);
    return std::distance(left_bound, right_bound);
}
