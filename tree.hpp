#pragma once
#include <stack>
#include <utility>
#include <algorithm>
#include <cstdlib>

namespace Tree {
    template <typename KeyT>
    class AvlTree {
        struct Node {
            KeyT   key_;
            Node*  left_;
            Node*  right_;
            Node*  parent_;
            int    height_;
            Node(KeyT key, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, size_t height = 0) :
            key_(key), left_(left), right_(right), parent_(parent), height_(height) {}
        };
        struct Node;
    public:
        Node* root_;
        AvlTree() {} //constructor

        AvlTree(const AvlTree<KeyT>& other) { //copy constructor
            root_ = copy_tree(other);
        }

        AvlTree(const AvlTree<KeyT>&& other) noexcept : root_(other.root_) { //move constructor
            other.root_ = nullptr;
        }

        AvlTree<KeyT>& operator=(AvlTree<KeyT>&& other) noexcept { //move assigment
            if (&other == this) return *this;
            delete root_;
            root_       = other.root_;
            other.root_ = nullptr;
            return *this;
        }

        AvlTree<KeyT>& operator=(const AvlTree<KeyT>& other) { //copy assigment
            if (this == &other) return *this;

            delete_tree();
            root_ = copy_tree(other);
            return *this;
        }

        ~AvlTree() { // destructor
            delete_tree();
        }

        void insert(KeyT key) {
            Node* new_node = new Node(key, nullptr, nullptr, nullptr, 0);
            if(root_ == nullptr) {
                root_ = new_node;
                return;
            }
            Node* current_node = root_;
            Node* parent       = nullptr;
            while (current_node) {
                parent = current_node;
                if (key < current_node->key_) {
                    current_node = current_node->left_;
                } else if (key >= current_node->key_) {
                    current_node = current_node->right_;
                }
            }
            new_node->parent_ = parent;
            if (key < parent->key_) {
                parent->left_ = new_node;
            } else {
                parent->right_ = new_node;
            }
            std::cout << "insert" << key << "\n";
            Node* unbalanced_node = fix_height(parent);
            if(unbalanced_node) {
                std::cout << unbalanced_node->key_ << "balanced\n";
                unbalanced_node = balance_tree(unbalanced_node);
            }
        }
    private:
        Node* copy_tree(const AvlTree& other) {
            std::stack<std::pair<Node*, Node*>> stack;

            Node* new_root = new Node(other.root->key, nullptr, nullptr, other.root->parent, other.root->height);
            Node* old_node = other.root;

            stack.push({old_node, new_root});
            while (!stack.empty()) {

                auto [old_node, new_node] = stack.top();
                stack.pop();

                if (old_node->left_) {
                    new_node->left_ = new Node(old_node->left_->key, nullptr, nullptr, new_node, old_node->left_->height);
                    stack.push({old_node->left_, new_node->left_});
                }
                if (old_node->right_) {
                    new_node->right_ = new Node(old_node->right_->key, nullptr, nullptr, new_node, old_node->right_->height);
                    stack.push({old_node->right_, new_node->right_});
                }
            }

            return new_root;
        }
        void delete_tree() {
            Node* current_node = root_;
            while (current_node) {
                if (current_node->left_)  {
                    current_node = current_node->left_;
                } else if (current_node->right_) {
                    current_node = current_node->right_;
                } else {
                    Node* parent = current_node->parent_;
                    if (parent && current_node == parent->left_) {
                        parent->left_  = nullptr;
                    } else if (parent && current_node == parent->right_) {
                        parent->right_ = nullptr;
                    }
                    if (current_node == root_) {
                        delete current_node;
                        break;
                    }
                    delete current_node;
                    current_node = parent;
                }
            }
        }

        Node* fix_height(Node* node) {
            Node* current_node = node;
            while (current_node) {
                int old_height   = current_node->height_;
                int left_height  = current_node->left_  ? current_node->left_->height_  : 0;
                int right_height = current_node->right_ ? current_node->right_->height_ : 0;

                current_node->height_ = 1 + std::max(left_height, right_height);
                if (std::abs(left_height - right_height) > 1) return current_node;
                if (current_node->height_ == old_height) break;
                current_node = current_node->parent_;
            }
            return nullptr;
        }

        Node* balance_tree(Node* node) {
            int left_height  = node->left_  ? node->left_->height_  : 0;
            int right_height = node->right_ ? node->right_->height_ : 0;
            int balance = left_height - right_height;
            if (balance > 1) {
                if (left_height < right_height) node->left_->right_ = left_rotate(node->left_->right_);
                return right_rotate(node);
            } else if (balance < -1) {
                if (left_height > right_height) node->right_->left_ = right_rotate(node->right_->left_);
                return left_rotate(node);
            }
            return node;
        }

        Node* right_rotate(Node* node) {
            Node* parent     = node->parent_;

            if (!node->left_) return node;
            Node* left_node = node->left_;

            node->left_ = left_node->right_;
            if (left_node->right_) left_node->right_->parent_ = node;

            left_node->parent_ = parent;
            if(!parent) {
                root_ = left_node;
            } else if (node == parent->left_) {
                parent->left_ = left_node;
            } else if (node == parent->right_) {
                parent->right_ = left_node;
            }

            left_node->right_ = node;
            node->parent_     = left_node;

            return left_node;
        }

        Node* left_rotate(Node* node) {
            Node* parent     = node->parent_;

            if (!node->right_) return node;
            Node* right_node = node->right_; // проверка

            node->right_ = right_node->left_;
            if (right_node->left_) right_node->left_->parent_ = node;

            right_node->parent_ = parent;
            if(!parent) {
                root_ = right_node;
            } else if (node == parent->left_) {
                parent->left_ = right_node;
            } else if (node == parent->right_) {
                parent->right_ = right_node;
            }

            right_node->left_ = node;
            node->parent_     = right_node;

            return right_node;
        }
    };
}
