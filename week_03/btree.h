#ifndef BIN_TREE
#define BIN_TREE

#include <iostream>

template <typename T>
struct BTreeNode {
    T data;
    BTreeNode *left, *right, *parent;

    BTreeNode(T data): data(data), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class BinaryTree {
private:
    BTreeNode<T> *root;
    
public:
    BinaryTree(): root(nullptr) {}
    BinaryTree(T root_data): root(new (std::nothrow) BTreeNode<T>(root_data)) {}
    BinaryTree(const BinaryTree<T>& other) {
        //...
    }
    ~BinaryTree() {
        delete root;
    }

    BTreeNode<T>* getRoot() {
        return root;
    }

    BTreeNode<T>* getRoot() const {
        return root;
    }

    void printTree() const {
        // ...
    }

    BTreeNode<T>* searchElement(T key) {
        //...
    }

    // Insert a node in binary SEARCH tree 
    // Insert the node to the BST, 
    // if there are no nodes in the BST, 
    // then it becomes the root node of the BST.
    BTreeNode<T>* insertNode(BTreeNode<T>* node, T key) {
        // If BST doesn't exist
        // create a new node as root
        // or it's reached when
        // there's no any child node
        // so we can insert a new node here
        if(node == nullptr)
        {
            node = new BTreeNode<T>(key);
            node->left = nullptr;
            node->right = nullptr;
            node->parent = nullptr;
        }

        // If the given key is greater than
        // node's key then go to right subtree
        else if(node->Key < key)
        {
            node->right = insertNode(node->right, key);
            node->right->parent = node;
        }

        // If the given key is smaller than
        // node's key then go to left subtree
        else
        {
            node->left = insertNode(node->left, key);
            node->left->parent = node;
        }

        return node;
    }

    void insert(int key)
    {
        root = insertNode(root, key);
    }

    // Note: keys are unique in this context
    void removeNode(T key) {
        BTreeNode<T> *temp = searchElement(key);

    }

    void inorderTraversal(BTreeNode<T> *currentRoot) const {
        // demo - print all nodes
        if (currentRoot != nullptr) {
            inorderTraversal(currentRoot->left);
            std::cout << currentRoot->data << " ";
            inorderTraversal(currentRoot->right);
        }
    }
    void printTreeInOrder()
    {
        // Traverse the BST
        // from root node
        // then print all keys
        inorderTraversal(root);
        std::cout << std::endl;
    }
};



#endif