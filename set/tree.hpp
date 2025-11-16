#include <set>
#include <iterator>

namespace Tree {
    template<typename KeyT>
    class SetTree {

        std::set<KeyT> set;
    public:
        int range_reqired(KeyT left, KeyT right) {
            auto left_bound  = upper_bound(left);
            auto right_bound = upper_bound(right);
            return std::distance(left_bound, right_bound);
        }
    };
}
