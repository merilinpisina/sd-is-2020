#ifndef TRIE
#define TRIE

#include <cstring>
#include <iostream>
#include <exception>

const unsigned int ALPHABET_SIZE = 26;
// . - + = -> index

struct TrieNode {
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord; // true if the node represents the end of a word
};

TrieNode* createNode() {
    TrieNode *newNode = new (std::nothrow) TrieNode;
    if (newNode == nullptr) {
        throw std::bad_alloc();
    }
    newNode->isEndOfWord = false;
    for(int i = 0; i < ALPHABET_SIZE; ++i) {
        newNode->children[i] = nullptr;
    }
    return newNode;
}

void insert(TrieNode* root, std::string key) {
    if (root == nullptr) {
        root = createNode();
    }

    // std::cout << "Inserting " << key << std::endl;
    
    TrieNode *current = root;
    int length = key.length();
    for (int i = 0; i < length; ++i) {
        int index = key[i] - 'a'; // get the index in the alphabet
        if (!current->children[index]) {
            current->children[index] = createNode();
        }

        current = current->children[index];
    }
    current->isEndOfWord = true;
}

bool search(TrieNode* root, std::string key) {
    // std::cout << "Searching for " << key << std::endl;
    if (root == nullptr) {
        return false;
    }

    // if key.length() > height of the trie => false

    TrieNode* current = root;
    int length = key.length();
    for (int i = 0; i < length; ++i) {
        int index = key[i] - 'a'; // get the index in the alphabet
        if (!current->children[index]) {
            return false;
        }
        current = current->children[index];
    }
    return (current != nullptr && current->isEndOfWord);
}

// returns true if the node has no children
bool isEmpty(TrieNode *node) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (node->children[i] != nullptr) {
            return false;
        }
    }
    return true;
}

// remove is a recursive function that deletes a key froma a given Trie
TrieNode* remove(TrieNode* root, std::string key, int depth = 0) {
    if (root == nullptr) {
        return nullptr;
    }

    // if last character is being processed
    
    if (root->isEndOfWord && depth == key.length()) {
        root->isEndOfWord = false;
        return root;
    }

    if (isEmpty(root) && depth == key.length()) {
        delete root;
        root = nullptr;
        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete root;
        root = nullptr;
    }
    return root;
}

#endif