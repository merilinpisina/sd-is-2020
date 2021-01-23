#include "trie.h"

void testTrie() {
    std::string keys[] = {"the", "there", "by", "a", "hero", "heroplane", "their", "bye", "any", "answer"};
    int n = sizeof(keys) / sizeof(keys[0]);
    TrieNode* root = createNode();
    for (int i = 0; i < n; ++i) {
        insert(root, keys[i]);
    }

    std::cout << "Searching for the: " << (search(root, "the") ? "Yes" : "No") << std::endl; // Yes
    std::cout << "Searching for these: " << (search(root, "these") ? "Yes" : "No") << std::endl; // No
    remove(root, "heroplane");
    std::cout << "Searching for hero: " << (search(root, "hero") ? "Yes" : "No") << std::endl; // Yes
    std::cout << "Searching for heroplane: " << (search(root, "heroplane") ? "Yes" : "No") << std::endl; // No
}

int main() {
    testTrie();

    return 0;
}