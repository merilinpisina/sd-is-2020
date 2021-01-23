#ifndef BTREE
#define BTREE

#include <exception>
#include <queue>
#include <iostream>

struct CharNode {
    char data;
    CharNode *left, *right;
};

CharNode* newNode(char data) {
    CharNode* node = new (std::nothrow) CharNode;
    if (node == nullptr) {
        throw std::bad_alloc();
    }

    node->data = data;
    node->left = node->right = nullptr;
    return node;
}

class BTree {
public:
    BTree() {
        root = nullptr;
    }

    ~BTree() {
        destroy();
    }

    BTree(const BTree&) = delete;
    BTree& operator=(const BTree&) = delete;

    void insert(char key) {
        if (root == nullptr) {
            root = newNode(key);
            return;
        }
        insert(key, root);
    }

    CharNode* search(char key) {
        return search(key, root);
    }

    void destroy() {
        destroy(root);
    }

private:
    void destroy(CharNode* leaf) {
        if (leaf == nullptr) return;
        destroy(leaf->left);
        destroy(leaf->right);
        delete leaf;
    }

    void insert(char key, CharNode *node) {
        if (key < node->data) {
            if (node->left != nullptr) {
                insert(key, node->left);
            }
            else {
                node->left = newNode(key);
            }
            return;
        }
        if (node->right != nullptr) {
            insert(key, node->right);
        }
        else {
            node->right = newNode(key);
        }        
    }

    CharNode *search(char key, CharNode *node) {
        if (node == nullptr) return nullptr;
        if (key == node->data) return node;
        if (key < node->data) return search(key, node->left);
        return search(key, node->right);
    }
    CharNode *root;
};

#endif