#include "queue_ll.h"


Queue::Queue(size_t capacity): size(0) {
	QNode *first = new (std::nothrow) QNode();
	if (!first) {
		throw std::bad_alloc();
	}

	QNode *current = first;
	for (int i = 0; i < capacity-1; ++i) {
		QNode *new_node = new (std::nothrow) QNode();
		if (!new_node) {
			throw std::bad_alloc();
		}
		current->next = new_node;
		current = new_node;
	}

	front = first;
	rear = current;
}

Queue::Queue(const Queue &rhs)
{
	this->size = rhs.size;
	QNode* current = rhs.front;
	do {
		this->enqueue(current->row, current->col, current->pathLength);
		current = current->next;
	} while (current != rhs.rear);
}

Queue::~Queue()
{
	QNode *toDelete = front, *current = front;
	do {
		current = current->next;
		delete toDelete;
		toDelete = current;
	} while (current != nullptr);
	size = 0;
	front = nullptr;
	rear = nullptr;
}

bool Queue::empty() const
{
	return (size == 0);
}

size_t Queue::length() const
{
	return this->size;
}

QNode* Queue::first() const
{
	//if (front == nullptr) {
	//	throw std::runtime_error("Empty queue.");
	//}
	return front;
}

void Queue::enqueue(int row, int col, int pathLength = 0)
{
	QNode *new_node = new (std::nothrow) QNode(row, col, pathLength);
	if (new_node == nullptr) {
		throw std::bad_alloc();
	}

	size++;
	if (front == nullptr) {
		front = new_node;
		rear = new_node;
		return;
	}
	rear->next = new_node;
	rear = new_node;
}

int Queue::dequeue()
{
	if (empty()) {
		throw std::runtime_error("Trying to delete from an empty queue.");
	}

	if (front == rear) {
		int toReturn = front->pathLength;
		delete front;
		front = rear = nullptr;
		size = 0;
		return toReturn;
	}

	QNode *toRemove = front;
	front = front->next;
	int toReturn = toRemove->pathLength;
	delete toRemove;
	return toReturn;
}

void Queue::display() const
{
	if (empty()) {
		return;
	}

	QNode *current = front;
	do {
		std::cout << 
			"(" << 
			current->row << 
			", " << 
			current->col << 
			", " << 
			current->pathLength << 
			") -> ";
		current = current->next;
	} while (current != nullptr);
	std::cout << std::endl;
}




