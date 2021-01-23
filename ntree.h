#ifndef NARYTREE
#define NARYTREE

#include <vector>
#include <exception>
#include <cstring>
// me -> root->data = 'm' -> root->children = append(root->children, 'e')
// root->data = ''
// me -> root->children = 'm' -> root->'m'->children = append(root->'m'->children, 'e')

class Node {
    char data;
    std::vector<Node*> children;
    Node(char data) {
        this->data = data;
    }
}

class Dictionary{
    private:
        Node* root;
        Node* InsertNode(Node* parent, Node* child, char data) {
            if(parent == nullptr) 
                child = CreateNode(data);

            Node* newNode = this->CreateNode(data);
            parent->children.push_back(newNode);

            return newNode;
        }
    public:
        Dictionary() {
            this->root = new (std::nothrow) Node(0);
            if(this->root == nullptr) throw std::bad_alloc();
        }

        Node* CreateNode(char data) {
            Node* temp = new (std::nothrow) Node(data);
            if(this->root == nullptr) throw std::bad_alloc();

            return temp;
        }

        Node* Search(Node* root, char* data){
            if(root == nullptr) return nullptr;

            for (std::vector<Node*>::iterator it = root->children.begin(); it != root->children.end(); it++){
                if((*it)->data == *data){
                    Search((*it), ++data);
                }
            }
            return root;
        }

        Node* Insert(Node* parent, char data){
            return InstertNode(parent, nullptr, data);
        }

        void InsertWord(const char* word) {
            Node* next = this->root;
            int length = std::strlen(word);

            for(int i = 0; i < length; i++) {
                if(next->data == 0){
                    next->data = word[i];
                    continue;
                }

                if(next->data != word[i]){
                    next = Insert(next, word[i]);
                }
                else {
                    Node* tempNode = Search(next, &word[i + 1]);
                    next = Insert(tempNode, word[i]);
                }
            }
        }
}

#endif