#include <bits/stdc++.h>
using namespace std;
// Merge two sorted linked lists 

struct Node {  
    int data;  
    Node *next;  
    Node *prev;  
};  
 
// pull off the front node of 
// the source and put it in dest
void move(Node** destRef, Node** sourceRef); 
 
/* Takes two lists sorted in increasing
order, and splices their nodes together
to make one big sorted list which 
is returned. */
Node* sortedMerge(Node* a, Node* b) 
{ 
    /* a dummy first node to hang the result on */
    Node dummy; 
 
    /* tail points to the last result node */
    Node* tail = &dummy; 
 
    /* so tail->next is the place to  
    add new nodes to the result. */
    dummy.next = nullptr; 
    while (1) 
    { 
        if (a == nullptr) 
        { 
            /* if either list runs out, use the 
            other list */
            tail->next = b; 
            break; 
        } 
        else if (b == nullptr) 
        { 
            tail->next = a; 
            break; 
        } 
        if (a->data <= b->data) 
            move(&(tail->next), &a); 
        else
            move(&(tail->next), &b); 
 
        tail = tail->next; 
    } 
    return(dummy.next); 
} 
 
/* UTILITY FUNCTIONS */
/* move() function takes the
node from the front of the source,
and moves it to the front of the dest. 
It is an error to call this with the 
source list empty. 
 
Before calling move(): 
source == {1, 2, 3} 
dest == {1, 2, 3} 
 
Affter calling move(): 
source == {2, 3} 
dest == {1, 1, 2, 3} */
void move(Node** destRef, Node** sourceRef) { 
    Node* newNode = *sourceRef; 
    assert(newNode != nullptr); 
 
    *sourceRef = newNode->next; 
    newNode->next = *destRef; 
    *destRef = newNode; 
} 
 
 
/* Function to insert a node at  
the beginging of the linked list */
void push(Node** head_ref, int new_data) { 
    /* allocate node */
    Node* new_node = new Node();
    if (new_node == nullptr) {
        throw std::bad_alloc();
    }
 
    /* put in the data */
    new_node->data = new_data; 
 
    /* link the old list off the new node */
    new_node->next = (*head_ref); 
 
    /* move the head to point to the new node */
    (*head_ref) = new_node; 
} 
 
/* Function to print nodes in a given linked list */
void printList(Node *node) { 
    while (node!=nullptr) { 
        std::cout<<node->data<<" "; 
        node = node->next; 
    } 
} 

int main() { 
    Node* res = nullptr; 
    Node* a = nullptr; 
    Node* b = nullptr; 
 
    push(&a, 15); 
    push(&a, 10); 
    push(&a, 5); 
 
    push(&b, 20); 
    push(&b, 3); 
    push(&b, 2); 
 
    res = sortedMerge(a, b); 
 
    cout << "Merged Linked List is: \n"; 
    printList(res); 
 
    return 0; 
} 
