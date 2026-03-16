#pragma once
#include <stack>
#include <utility>
#include <algorithm>
#include <cstdlib>

namespace Tree {
    template <typename KeyT>
    class AvlTree {
    private:
    static constexpr int SELF_COUNT = 1;
        struct Node {
            KeyT   key_;
            Node*  left_   = nullptr;
            Node*  right_  = nullptr;
            Node*  parent_ = nullptr;
            int    height_ = 0;
            int    subtree_size_ = SELF_COUNT;
            Node(const KeyT& key, Node* parent = nullptr) :
            key_(key), parent_(parent) {}
        };

        Node* root_;
    public:
        AvlTree() : root_(nullptr) {}
        AvlTree(const AvlTree<KeyT>& other) : root_(copy_tree(other)) {}

        AvlTree(AvlTree<KeyT>&& other) noexcept : root_(other.root_) {
            other.root_ = nullptr;
        }

        AvlTree<KeyT>& operator=(AvlTree<KeyT>&& other) noexcept {
            if (&other == this) return *this;
            delete_tree(root_);
            root_       = other.root_;
            other.root_ = nullptr;
            return *this;
        }

        AvlTree<KeyT>& operator=(const AvlTree<KeyT>& other) {
            if (this == &other) return *this;
            AvlTree<KeyT> tmp;
            tmp.root_ = copy_tree(other);
            std::swap(root_, tmp.root_);
            return *this;
        }

        ~AvlTree() {
            delete_tree(root_);
        }

        void insert(const KeyT& key) {
            Node* current_node = root_;
            Node* parent       = nullptr;
            while (current_node) {
                parent = current_node;
                if (key < current_node->key_) {
                    current_node = current_node->left_;
                } else if (key > current_node->key_) {
                    current_node = current_node->right_;
                } else {
                    return;
                }
            }

            Node* new_node = new Node(key);
            if(root_ == nullptr) {
                root_ = new_node;
                return;
            }

            new_node->parent_ = parent;
            if (key < parent->key_) {
                parent->left_ = new_node;
            } else {
                parent->right_ = new_node;
            }

            fix_size(parent);
            Node* unbalanced_node = fix_height(parent);
            if(unbalanced_node) unbalanced_node = balance_tree(unbalanced_node);
        }

    private:
        int height(const Node* node) const {
            return node ? node->height_ : 0;
        }
        int size(const Node* node) const {
            return node ? node->subtree_size_ : 0;
        }
        Node* copy_tree(const AvlTree& other) const {
            if (!other.root_) return 0;
            std::stack<std::pair<Node*, Node*>> stack;

            Node* new_root = new Node(other.root_->key_);
            new_root->height_ = other.root_->height_;
            new_root->subtree_size_ = other.root_->subtree_size_;

            Node* old_node = other.root_;

            try {
                stack.push({old_node, new_root});
                while (!stack.empty()) {

                    auto [old_node, new_node] = stack.top();
                    stack.pop();

                    if (old_node->left_) {
                        new_node->left_                = new Node(old_node->left_->key_, new_node);
                        new_node->left_->height_       = old_node->left_->height_;
                        new_node->left_->subtree_size_ = old_node->left_->subtree_size_;
                        stack.push({old_node->left_, new_node->left_});
                    }
                    if (old_node->right_) {
                        new_node->right_                = new Node(old_node->right_->key_, new_node);
                        new_node->right_->height_       = old_node->right_->height_;
                        new_node->right_->subtree_size_ = old_node->right_->subtree_size_;
                        stack.push({old_node->right_, new_node->right_});
                    }
                }
            }
            catch(...) {
                delete_tree(new_root);
                throw;
            }
            return new_root;
        }
        void delete_tree(Node* root) const noexcept {
            Node* current_node = root;
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
                    if (current_node == root) {
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
                int left_height  = height(current_node->left_);
                int right_height = height(current_node->right_);

                current_node->height_ = SELF_COUNT + std::max(left_height, right_height);
                if (std::abs(left_height - right_height) > 1) return current_node;
                if (current_node->height_ == old_height) break;
                current_node = current_node->parent_;
            }
            return nullptr;
        }

        void fix_size(Node* node) {
            Node* current_node = node;
            while(current_node) {
                current_node->subtree_size_++;
                current_node = current_node->parent_;
            }
        }

        Node* balance_tree(Node* node) {
            int left_height  = height(node->left_);
            int right_height = height(node->right_);
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
            Node* parent = node->parent_;

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

            //update height
            node->height_ = std::max(height(node->left_), height(node->right_)) + SELF_COUNT;
            left_node->height_ = std::max(height(left_node->left_), height(left_node->right_)) + SELF_COUNT;
            fix_height(left_node->parent_);
            //update size
            node->subtree_size_ = size(node->left_) + size(node->right_) + SELF_COUNT;
            left_node->subtree_size_ = size(left_node->left_) + size(left_node->right_) + SELF_COUNT;

            return left_node;
        }

        Node* left_rotate(Node* node) {
            Node* parent     = node->parent_;

            if (!node->right_) return node;
            Node* right_node = node->right_;

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

            //update height
            node->height_ = std::max(height(node->left_), height(node->right_)) + SELF_COUNT;
            right_node->height_ = std::max(height(right_node->left_), height(right_node->right_)) + SELF_COUNT;
            fix_height(right_node->parent_);
            //update size
            node->subtree_size_ = size(node->left_) + size(node->right_) + SELF_COUNT;
            right_node->subtree_size_ = size(right_node->left_) + size(right_node->right_) + SELF_COUNT;

            return right_node;
        }

        private:
        Node* upper_bound(const KeyT& key) const {
            Node* current_node = root_;
            Node* best_node    = nullptr;
            while(current_node) {
                if (current_node->key_ > key) {
                    best_node    = current_node;
                    current_node = current_node->left_;
                } else {
                    current_node = current_node->right_;
                }
            }
            return best_node;
        }

        Node* lower_bound(const KeyT& key) const {
            Node* current_node = root_;
            Node* best_node    = nullptr;
            while(current_node) {
                if (current_node->key_ >= key) {
                    best_node    = current_node;
                    current_node = current_node->left_;
                } else {
                    current_node = current_node->right_;
                }
            }
            return best_node;
        }

        int count_less(const Node* node) const {
            if (!node) return size(root_);
            Node* current_node = root_;
            KeyT key = node->key_;
            int count = 0;
            while(current_node) {
                if(key > current_node->key_) {
                    count += size(current_node->left_) + SELF_COUNT;
                    current_node = current_node->right_;
                } else {
                    current_node = current_node->left_;
                }
            }
            return count;
        }

    public:
        int range_required(const KeyT& left, const KeyT& right) const {
            if (right < left) return 0;
            Node* left_bound  = lower_bound(left);
            Node* right_bound = upper_bound(right);
            int upper_count = count_less(right_bound);
            int lower_count = count_less(left_bound);
            return upper_count - lower_count;
        }
    };
};
