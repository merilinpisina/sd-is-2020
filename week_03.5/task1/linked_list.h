#ifndef LINKED_LIST_C
#define LINKED_LIST_C

// In order to use strcpy with no warnings - 
// there are checks before using it to make sure it is safe
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cassert>
#include <iostream>

struct Node
{
	bool is_first;
	char *data;
	Node *next;
	int snake_length;
	int number_of_words;

	Node() = default;

	Node(const char* data) {
		if (data == nullptr)
		{
			throw std::invalid_argument("invalid data for new node");
		}

		this->data = new (std::nothrow) char[strlen(data) + 1];
		if (this->data == nullptr)
		{
			throw std::bad_alloc();
		}
		strcpy(this->data, data);
	}

	~Node() {
		delete[]data;
		next = nullptr;
	}
};

Node* create_new_node(const char *new_data)
{
	Node* new_node = new (std::nothrow) Node(new_data);
	if (new_node == nullptr) {
		throw std::bad_alloc();
	}
	return new_node;
}

Node *push_in_empty(const char *new_data)
{
	Node *cursor = create_new_node(new_data);
	// If the node hasn't been created, an exception should be thrown
	assert(cursor != nullptr);

	cursor->next = cursor;
	return cursor;
}

Node *push_front(Node *cursor, const char *new_data)
{
	// if list is empty
	if (cursor == nullptr)
	{
		return push_in_empty(new_data);
	}

	Node *temp = create_new_node(new_data);
	assert(temp != nullptr);

	temp->next = cursor->next;
	cursor->next = temp;
	return cursor;
}

Node *push_back(Node *cursor, const char *new_data)
{
	// if list is empty
	if (cursor == nullptr)
	{
		return push_in_empty(new_data);
	}

	Node *temp = create_new_node(new_data);
	assert(temp != nullptr);

	temp->next = cursor->next;
	cursor->next = temp;
	return temp;
}

Node *push_after(Node *cursor, const char *new_data, const char* item)
{
	// if list is empty
	if (cursor == nullptr)
	{
		throw std::invalid_argument("cannot use push_after on an empty list");
	}

	Node *p = cursor->next;
	do
	{
		if (strcmp(p->data, item) == 0)
		{
			Node *temp = create_new_node(new_data);
			assert(temp != nullptr);

			temp->next = p->next;
			p->next = temp;
			if (p == cursor) {
				cursor = temp;
			}
			return cursor;
		}
		p = p->next;
	} while (p != cursor->next);

	throw std::invalid_argument("item is not present in the list");
}

void print_list(Node* const root, const char* message = "") {
	if (root == nullptr) {
		return;
	}

	if (message != "") {
		std::cout << message << std::endl;
	}

	Node* temp = root;
	do {
		std::cout << "-> " << temp->data << " ";
		temp = temp->next;
	} while (temp != root);
	std::cout << "->" << std::endl;
}

void print_longest(Node* const root) {
	if (root == nullptr) {
		return;
	}

	Node* temp = root, *longest = root;
	do {
		if (temp->snake_length > longest->snake_length) {
			longest = temp;
		}
		temp = temp->next;
	} while (temp != root);
	std::cout << "Longest:\n";
	std::cout << longest->data << std::endl;
}

Node* create_snake(Node* root) {
	if (root == nullptr || root->data == nullptr || root->next == root) {
		return root;
	}

	Node* temp = root, *first = root;
	first->is_first = true;
	first->snake_length = strlen(first->data);
	first->number_of_words = 1;
	char current_cursor = first->data[strlen(first->data) - 1];
	char cursor_sanitized = (current_cursor >= 'A' && current_cursor <= 'Z') ? current_cursor - 'A' + 'a' : current_cursor;

	// loop-Pet-tiger-rat -> cat -> 
	do {
		Node* next = temp->next;
		if (next != nullptr && next->data != nullptr) {
			char current_sanitized = (next->data[0] >= 'A' && next->data[0] <= 'Z') ? next->data[0] - 'A' + 'a' : next->data[0];
			if (cursor_sanitized == current_sanitized) {
				if (next->is_first == true) {
					next->is_first = false;
					first->snake_length += next->snake_length;
					first->number_of_words += next->number_of_words;
				}
				else {
					first->snake_length += strlen(next->data);
					first->number_of_words++;
				}
			}
			else {
				first = next;
				next->is_first = true;
				first->snake_length = strlen(first->data);
				first->number_of_words = 1;
			}
			current_cursor = next->data[strlen(next->data) - 1];
			cursor_sanitized = (current_cursor >= 'A' && current_cursor <= 'Z') ? current_cursor - 'A' + 'a' : current_cursor;
			temp = temp->next;
		}
	} while (temp != root);
	return first;
}

void delete_list(Node* root) {
	if (root == nullptr) {
		return;
	}

	Node* to_traverse = root;
	Node* to_delete;
	do {
		to_delete = to_traverse;
		to_traverse = to_traverse->next;
		delete to_delete;
	} while (to_traverse != root);
}

void sortedInsert(Node** cursor, Node* new_node) {
	Node* current = *cursor;
	if (current == nullptr) {
		new_node->next = new_node;
		*root = new_node;
		return;
	}
	// whatever -> x -> y  zoo
	if (strcmp(current->data, new_node->data) >= 0) {
		while (current->next != *cursor) {
			current = current->next;
		}
		current->next = new_node;
		new_node->next = *cursor;
		*cursor = new_node;
		return;
	}

	while (current->next != *cursor && strcmp(current->next->data, new_node->data) < 0) {
		current->next;
	}
	new_node->next = current->next;
	current->next = new_node;
}

Node* concat_nodes(Node* first) {
	if (first == nullptr || 
		first->data == nullptr || 
		!first->is_first) {
		return first;
	}
	// Pet-tag-giggle

	Node* temp = first, *new_first = nullptr, *currentFirst = first;
	do {
		char* new_data = new (std::nothrow) char[temp->snake_length + temp->number_of_words];
		int length = temp->snake_length + temp->number_of_words;
		if (new_data == nullptr) {
			throw std::bad_alloc();
		}

		strcpy(new_data, temp->data);
		int number_of_words = temp->number_of_words - 1, helper_count = temp->number_of_words;
		int helper_length = temp->snake_length;
		while (number_of_words){
			//Node *to_delete = temp;
			temp = temp->next;
			//delete to_delete;
			strcat(new_data, "-");
			strcat(new_data, temp->data);
			number_of_words--;
		} 
		Node* new_node = create_new_node(new_data);
		new_node->number_of_words = helper_count;
		new_node->snake_length = helper_length;
		sortedInsert(&new_first, new_node);
		temp = temp->next;

		//// optimization:
		//delete[]currentFirst->data;
		//currentFirst->data = new /*nothrow */ char[length];
		//// if nullptr
		//stcpy(currentFirst->data, new_data);
	} while (temp != first);

	delete_list(first);
	return new_first;
}

#endif