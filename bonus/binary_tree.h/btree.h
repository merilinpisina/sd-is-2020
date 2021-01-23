#ifndef BTREE
#define BTREE

#include <exception>
#include <queue>
#include <iostream>

int sumArray(int arr[], int length) {
    int sum = 0;
    for(int i = 0; i < length; ++i) {
        sum += arr[i];
    }
    return sum;
}

struct Node {
    int data;
    Node *left, *right;
};

Node* newNode(int data) {
    Node* node = new (std::nothrow) Node;
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
        maxPath = 0;
    }

    ~BTree() {
        destroy();
    }

    BTree(const BTree&) = delete;
    BTree& operator=(const BTree&) = delete;

    void insert(int key) {
        if (root == nullptr) {
            root = newNode(key);
            return;
        }
        insert(key, root);
    }

    Node* search(int key) {
        return search(key, root);
    }

    void destroy() {
        destroy(root);
    }

    // maxpath(Node*) if the implementation is not in the scope of the class BTree
    int maxpath() {
        int *path = new (std::nothrow) int[depth(root)];
        if (path == nullptr) {
            throw std::bad_alloc();
        }
        getPathSums(root, path, 0);
        delete [] path;
        return maxPath;
    }

    void printAllAvg() {
        int treeDepth = depth(root);
        std::cout << "{";
        for (int i = 1; i <= treeDepth; ++i) {
            if (i == treeDepth) {
                std::cout << avgOfLevel(root, i) << "}\n";
                break;
            }
            std::cout << avgOfLevel(root, i) << ", ";
        }
    }

private:
    int depth(Node* node) {
        if (node == nullptr) return 0;
        int lDepth = depth(node->left);
        int rDepth = depth(node->right);
        return (lDepth > rDepth) ? lDepth + 1 : rDepth + 1; 
    }

    int avgOfLevel(Node* node, int level) {
        if (node == nullptr) return 0;
        std::queue<Node*> q;
        q.push(node);
        int currentLevel = 0;
        int sumAtLevel = 0;
        int nodesAtLevel = 0;

        bool flag = false;
        while(!q.empty()) {
            int size = q.size();
            while(size--) {
                Node *current = q.front();
                q.pop();
                
                if(currentLevel == level) {
                    flag = true;
                    sumAtLevel += current->data;
                    nodesAtLevel++;
                }
                else {
                    if (current->left) q.push(current->left);
                    if (current->right) q.push(current->right);
                }
            }
            currentLevel++;
            if (flag) break;
        }
        return sumAtLevel/nodesAtLevel;
    }

    void destroy(Node* leaf) {
        if (leaf == nullptr) return;
        destroy(leaf->left);
        destroy(leaf->right);
        delete leaf;
    }

    void insert(int key, Node *node) {
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

    Node *search(int key, Node *node) {
        if (node == nullptr) return nullptr;
        if (key == node->data) return node;
        if (key < node->data) return search(key, node->left);
        return search(key, node->right);
    }

    // recursive helper function - given a node and array that contains the path 
    // from the root up to (but not including this node) sum all the root-leaf paths
    void getPathSums(Node *node, int path[], int pathLength) {
        if (node == nullptr) return;
        if (path[pathLength - 1] > node->data) {
            return;
        }

        path[pathLength++] = node->data;

        if (node->left == nullptr && node->right == nullptr) {
            int currentSum = sumArray(path, pathLength);
            if (maxPath < currentSum) {
                maxPath = currentSum;
            }
            return;
        }
        getPathSums(node->left, path, pathLength);
        getPathSums(node->right, path, pathLength);
    }

    int maxPath;
    Node *root;
};

#endif