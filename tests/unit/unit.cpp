#include <utility>
#include "../../avl/tree.hpp"
#include "gtest/gtest.h"

namespace {
    struct ThrowingElement {
        int value_;
        static inline int current_copies_ = 0;
        static inline int throw_after = -1;

        static void reset() {
            current_copies_ = 0;
            throw_after = -1;
        }

        explicit ThrowingElement(int value) : value_(value) {}

        ThrowingElement(const ThrowingElement& other) : value_(other.value_) {
            if (throw_after != -1 && ++current_copies_ >= throw_after) throw std::bad_alloc();
        }

        auto operator <=>(const ThrowingElement& other) const = default;

    };
};

TEST (BIG5, copy_ctor) {
    Tree::AvlTree<int> tree;
    tree.insert(10);
    tree.insert(6);
    tree.insert(0);
    tree.insert(-5);
    tree.insert(6);
    tree.insert(4);

    Tree::AvlTree<int> copy_tree{tree};

    size_t answer = copy_tree.range_required(3, 7);
    EXPECT_EQ(answer,2);
}

TEST (BIG5, move_ctor) {
    Tree::AvlTree<int> tree;
    tree.insert(10);
    tree.insert(6);
    tree.insert(0);
    tree.insert(-5);
    tree.insert(6);
    tree.insert(4);

    Tree::AvlTree<int> copy_tree{std::move(tree)};

    size_t answer = copy_tree.range_required(3, 7);
    EXPECT_EQ(answer,2);
}

TEST (BIG5, copy_assigment) {
    Tree::AvlTree<int> tree;
    tree.insert(10);
    tree.insert(6);
    tree.insert(0);
    tree.insert(-5);
    tree.insert(6);
    tree.insert(4);

    Tree::AvlTree<int> copy_tree;

    copy_tree = tree;

    size_t answer = copy_tree.range_required(3, 7);
    EXPECT_EQ(answer,2);
}

TEST (BIG5, move_assigment) {
    Tree::AvlTree<int> tree;
    tree.insert(10);
    tree.insert(6);
    tree.insert(0);
    tree.insert(-5);
    tree.insert(6);
    tree.insert(4);

    Tree::AvlTree<int> copy_tree;

    copy_tree = std::move(tree);

    size_t answer = copy_tree.range_required(3, 7);
    EXPECT_EQ(answer,2);
}

TEST (EXCEPTION, copy_ctor) {
    ThrowingElement::reset();

    Tree::AvlTree<ThrowingElement> tree;
    tree.insert(ThrowingElement(-2));
    tree.insert(ThrowingElement(9));
    tree.insert(ThrowingElement(234));
    tree.insert(ThrowingElement(-45));
    tree.insert(ThrowingElement(0));

    size_t answer_before = tree.range_required(ThrowingElement(-65), ThrowingElement(34));

    ThrowingElement::reset();
    ThrowingElement::throw_after = 3;

    EXPECT_THROW(Tree::AvlTree<ThrowingElement> copy_tree(tree), std::bad_alloc);

    ThrowingElement::reset();
    size_t answer_after = tree.range_required(ThrowingElement(-65), ThrowingElement(34));

    EXPECT_EQ(answer_after, answer_before);
}

TEST (EXCEPTION, copy_assigment) {
    ThrowingElement::reset();

    Tree::AvlTree<ThrowingElement> tree;
    tree.insert(ThrowingElement(-2));
    tree.insert(ThrowingElement(9));
    tree.insert(ThrowingElement(234));
    tree.insert(ThrowingElement(-45));
    tree.insert(ThrowingElement(0));

    size_t answer_before = tree.range_required(ThrowingElement(-65), ThrowingElement(34));

    ThrowingElement::reset();
    ThrowingElement::throw_after = 3;

    EXPECT_THROW(Tree::AvlTree<ThrowingElement> copy_tree = tree, std::bad_alloc);

    ThrowingElement::reset();
    size_t answer_after = tree.range_required(ThrowingElement(-65), ThrowingElement(34));

    EXPECT_EQ(answer_after, answer_before);
}



