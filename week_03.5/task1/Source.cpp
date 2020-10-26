#include "linked_list.h"

Node* build_snake_from_list(Node* root) {
	if (root == nullptr) {
		return root;
	}
	Node* new_root = create_snake(root);
	return concat_nodes(new_root);
}

int main() {
	try {
		char current_data[128];
		Node* root = nullptr, *temp = nullptr;
		while (std::cin.getline(current_data, 128) && current_data[0] != '\0' && current_data[0] != '\n') {
			if (root == nullptr) {
				root = push_in_empty(current_data);
				temp = root;
			} 
			else {
				temp = push_back(temp, current_data);
			}
		}
		print_list(root, "Starting list:");
		Node* new_root = build_snake_from_list(root);
		print_list(new_root, "New list:");
		//print_longest(new_root);
		delete_list(new_root);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}

	//system("pause");
	return 0;
}