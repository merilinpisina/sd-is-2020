#include <iostream>
#include <fstream>
#include <stack>

void decode() {
	char in[32], out[32];
	bool success = true;

	std::cout << "Enter the two file names: \n";
	std::cin >> in;
	std::ifstream is(in, std::ios::in);
	if (!is.is_open()) {
		std::cout << "Could not open input file!\n";
		return;
	}

	std::cin >> out;
	std::fstream result(out, std::ios::out | std::ios::in | std::ios::app);
	if (!result) {
		std::cout << "Could not open output file!\n";
		return;
	}

	is.seekg(0, std::ios::end);
	const int MAX_SIZE = int(is.tellg());
	char* current = new (std::nothrow) char[MAX_SIZE*2];
	if (!current) {
		throw std::bad_alloc();
	}
	std::memset(current, '\0', MAX_SIZE*2);
	is.seekg(0);

	bool openQuotes = false;
	int currentIndex = 0;
	std::stack<std::pair<int, int>> numPosition;
	while (!is.eof()) {
		char element = is.get();
		if (is.eof()) {
			break;
		}

		if (element == '\\') {
			element = is.get();
			if (is.eof()) {
				throw std::runtime_error("Invalid input: \\");
			}

			current[currentIndex++] = element;
			continue;
		}

		if (element == '"') {
			if (!openQuotes) {
				openQuotes = true;
				if (is.eof()) {
					throw std::runtime_error("Invalid input: \"");
				}
			}
			// Mistake from exercise: missed that case
			else {
				openQuotes = false;
			}
			continue;
		}

		if (element != '"' && openQuotes) {
			current[currentIndex++] = element;
			continue;
		}

		if (element <= '9' && element >= '0') {
			if (element == '0') {
				throw std::runtime_error("Invalid input: 0 before brackets");
			}
			int number = 0;
			result.seekp(0, std::ios::end);
			result << current;
			std::memset(current, '\0', MAX_SIZE*2);
			currentIndex = 0;			
			int position = int(result.tellp());
			while (element <= '9' && element >= '0' && !is.eof()) {
				number = number * 10 + (element - '0');
				element = is.get();
			}
			numPosition.push(std::make_pair(number, position));
			if (is.eof() || element != '(') {
				throw std::runtime_error("Invalid input: number without content in brackets");
			}
			continue;
		}

		if (element == '(') {
			if (numPosition.empty()) {
				throw std::runtime_error("Invalid input: open bracket");
			}
		}

		if (element == ')') {
			if (numPosition.empty()) {
				throw std::runtime_error("Invalid input: closed bracket");
			}

			std::pair<int, int> currentPair = numPosition.top();
			result << current;
			numPosition.pop();
			std::memset(current, '\0', MAX_SIZE*2);
			currentIndex = 0;

			result.seekg(0, std::ios::end);
			int outPosition = int(result.tellg());
			std::cout << outPosition << std::endl;

			char *toWrite = new (std::nothrow) char[outPosition - currentPair.second + 1];
			if (!toWrite) {
				throw std::bad_alloc();
			}

			result.seekg(currentPair.second);
			result >> toWrite;
			result.seekg(0, std::ios::end);

			for (int i = 0; i < currentPair.first; ++i) {
				result << toWrite;
			}
			delete[] toWrite;
			continue;
		}
		current[currentIndex++] = element;
	}
	
	if (strlen(current)) {
		result << current;
	}

	if (!numPosition.empty()) {
		throw std::runtime_error("Invalid bracket count");
	}
	if (openQuotes) {
		throw std::runtime_error("Invalid quote count");
	}
	is.close();
	result.close();
}

int main() {

	try {
		decode();
	}
	catch (std::runtime_error& err) {
		//
		//std::remove(out);
		std::cout << "Error: " << err.what() << std::endl;
	}
	catch (std::bad_alloc& e) {
		//
		std::cout << "Not enough memory\n";
	}


	system("pause");
	return 0;
}