#include <iostream> 
  
struct Node {  
    int data;  
    Node *next;  
    Node *prev;  
};  
  
// Function to reverse a Doubly Linked List 
void reverse(Node **head)  
{  
    Node *temp = nullptr;  
    Node *current = *head;  
      
    // swap next and prev for all nodes of the doubly linked list 
    while (current != nullptr) {  
        temp = current->prev;  
        current->prev = current->next;  
        current->next = temp;              
        current = current->prev;  
    }  
      
    // before changing the head, check for the cases like empty list and list with only one node
    if(temp != nullptr )  
        *head = temp->prev;  
}  

// insert a node at the beginging of the DLL
void push(Node** head, int new_data) {  
    // allocate node
    Node* new_node = new (std::nothrow) Node(); 
    if (new_node == nullptr) {
        throw std::bad_alloc();
    }

    new_node->data = new_data;  
    // since we are adding at the beginning, prev is always nullptr 
    new_node->prev = nullptr;  
    // link the old list off the new node
    new_node->next = *head;      
  
    // change prev of head node to new node
    if(*head != nullptr)  
    (*head)->prev = new_node ;  
  
    // move the head to point to the new node
    *head = new_node;  
}  
  
void printList(Node *node) {  
    while(node != nullptr) {  
        std::cout << node->data << " ";  
        node = node->next;  
    }  
}  
  
int main() {  
    Node* head = nullptr;  
    push(&head, 2);  
    push(&head, 4);  
    push(&head, 8);  
    push(&head, 10);  
      
    std::cout << "Before reverse:" << std::endl;  
    printList(head);  
    reverse(&head);  
    std::cout << "After reverse:" << std::endl;  
    printList(head);          
      
    return 0; 
}  
  