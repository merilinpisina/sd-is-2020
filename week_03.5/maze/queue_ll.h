#ifndef QUEUE_LINKED_LIST
#define QUEUE_LINKED_LIST	

#include <iostream>
#include <cassert>
// Creating the queue class:
	// struct node -> data, next
	// class queue -> *front, *rear, size
	//   -> queue(), ~queue(), queue(const queue&)
	//   -> bool empty() const, void enqueue(int), int dequeue(), 
	//     int size() const, int front() const

struct QNode {
	int row, col, pathLength;
	QNode *next;

	QNode() : next(nullptr), row(0), col(0), pathLength(0) {}
	QNode(int row, int col, int pathLength = 0): 
		next(nullptr), row(row), col(col), pathLength(pathLength) {}
};

class Queue {
public:
	Queue() = default;
	Queue(size_t);
	Queue(const Queue&);
	~Queue();

	bool empty() const;
	size_t length() const;

	QNode* first() const;
	void enqueue(int, int, int);
	int dequeue();

	void display() const;
private:
	size_t size;
	QNode *front, *rear;
};



#endif