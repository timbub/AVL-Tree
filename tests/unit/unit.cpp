#include <utility>
#include "../../avl/tree.hpp"
#include "gtest/gtest.h"

TEST (BIG5, copy_ctor) {
    Tree::AvlTree<int> tree;
    tree.insert(10);
    tree.insert(6);
    tree.insert(0);
    tree.insert(-5);
    tree.insert(6);
    tree.insert(4);

    Tree::AvlTree<int> copy_tree(tree);

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

    Tree::AvlTree<int> copy_tree(std::move(tree));

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



