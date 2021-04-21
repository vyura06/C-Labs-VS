#include <iostream>
#include <fstream>
#include <string>
#include "Header1.h"


	E unlinkFirst(Node<E>* node) {
		E element = node->value;
		Node<E>* next = node->next;
		first0 = next;
		if (next == nullptr)
			last0 = nullptr;
		else
			next->previous = nullptr;
		size--;
		return element;
	}

	E unlinkLast(Node<E>* node) {
		E element = node->value;
		Node<E>* prev = node->previous;
		last0 = prev;
		if (prev == nullptr)
			first0 = nullptr;
		else
			prev->next = nullptr;
		size--;
		return element;
	}

	E unlink(Node<E>* node) {
		E element = node->value;
		Node<E>* next = node->next;
		Node<E>* prev = node->previous;

		if (prev == nullptr) {
			first0 = next;
		}
		else {
			prev->next = next;
			node->previous = nullptr;
		}

		if (next == nullptr) {
			last0 = prev;
		}
		else {
			next->previous = prev;
			node->next = nullptr;
		}
		size--;
		return element;
	}

	E getFirst() {
		Node<E>* first = first0;
		if (first == nullptr)
			throw - 1;
		return first->value;
	}

	E getLast() {
		Node<E>* last = last0;
		if (last == nullptr)
			throw - 1;
		return last->value;
	}

	E removeFirst() {
		Node<E>* node = first0;
		if (node == nullptr)
			throw - 1;
		return unlinkFirst(node);
	}

	E removeLast() {
		Node<E>* node = last0;
		if (node == nullptr)
			throw - 1;
		return unlinkLast(node);
	}

	void addFirst(E element) {
		linkFirst(element);
	}

	void addLast(E element) {
		linkLast(element);
	}

	bool contains(E object) {
		return indexOf(object) >= 0;
	}

	bool add(E element) {
		linkLast(element);
		return true;
	}

	bool remove(E object) {
		Node<E>* node = first0;
		while (node != nullptr) {
			if (object == node->value) {
				unlink(node);
				return true;
			}
			node = node->next;
		}
		return false;
	}

	void clear() {
		Node<E>* next;
		Node<E>* node = first0;
		while (node != nullptr) {
			next = node->next;
			node->value = nullptr;
			node->next = nullptr;
			node->previous = nullptr;
			node = next;
		}
		first0 = nullptr;
		last0 = nullptr;
	}

	E get(int index) {
		checkElementIndex(index);
		return getNode(index)->value;
	}

	E set(int index, E element) {
		checkElementIndex(index);
		Node<E>* node = getNode(index);
		E oldVal = node->value;
		node->value = element;
		return oldVal;
	}

	void add(int index, E element) {
		checkPositionIndex(index);
		if (index == size)
			linkLast(element);
		else
			linkBefore(element, getNode(index));
	}

	E remove1(int index) {
		checkElementIndex(index);
		return unlink(getNode(index));
	}

	string normalno() {
		string result;
		result += '[';
		if (first0 != nullptr) {
			Node<E>* next;
			Node<E>* node = first0;
			bool flag = true;
			do {
				next = node->next;
				result += node->value;
				if (next == nullptr) {
					flag = false;
				}
				else {
					result += ", ";
					node = next;
				}
			} while (flag);
		}
		result += ']';
		return result;
	}

	string naoborot() {
		string result;
		result += '[';
		if (last0 != nullptr) {
			Node<E>* previous;
			Node<E>* node = last0;
			bool flag = true;
			do {
				previous = node->previous;
				result += node->value;
				if (previous == nullptr) {
					flag = false;
				}
				else {
					result += ", ";
					node = previous;
				}
			} while (flag);
		}
		result += ']';
		return result;
	}
};

LinkedList<string> list;

string ONE = "1";
string TWO = "2";
string THREE = "3";
string FOUR = "4";
string FIVE = "5";

int getNumber() {
	string line;
	int result;
	while (!(cin >> result)) {
		cout << "Error" << endl;
		cin.clear();
		cin.sync();
		getline(cin, line);
	}
	return result;
}

void makeActionWidthFile(void consumer(fstream&)) {
	fstream filesteam;
	string line;
	string message = "Enter path to file or enter " + ONE + " to exit";
	bool flag = true;
	do {
		cout << message << endl;
		getline(cin, line);
		if (ONE == line) {
			flag = false;
		}
		else {
			filesteam.open(line);
			if (filesteam.is_open()) {
				consumer(filesteam);
				filesteam.close();
			}
			else {
				cout << "File doesn't exist" << endl;
			}
		}
	} while (flag);
}

void writeInFile(fstream& filestream) {
	filestream << list.normalno() << endl;
	filestream << list.naoborot() << endl;
	cout << "Saved" << endl;
}

void writeToConsole() {
	cout << list.normalno() << endl;
	cout << list.naoborot() << endl;
}

void printList() {
	string line;
	string message = "Select when you want write data:\nTo console: " + ONE +
		"\nTo file: " + TWO +
		"\nExit: " + THREE;
	bool flag = true;
	do {
		cout << message << endl;
		getline(cin, line);
		if (ONE == line) {
			writeToConsole();
		}
		else if (TWO == line) {
			makeActionWidthFile(*writeInFile);
		}
		else if (THREE == line) {
			flag = false;
		}
	} while (flag);
}

void deleteElement() {
	string message = "Enter index";
	bool flag = true;
	do {
		cout << message << endl;
		int index = getNumber();
		if (index < 0) {
			cout << "Index can be positive!" << endl;
		}
		if (index >= list.getsize()) {
			cout << "Index out of bounds. Index = " << to_string(index) <<
				", size = " << to_string(list.getsize()) << endl;
		}
		else {
			list.remove1(index);
			flag = false;
		}
	} while (flag);
}

void readAll(fstream& filestream) {
	string line;
	while (getline(filestream, line)) {
		list.add(line);
	}
}

void readFromConsole() {
	cout << "Enter line" << endl;
	string line;
	getline(cin, line);
	list.add(line);
}

void addElement() {
	string line;
	string message = "Select when you want read data:\nFrom console: " + ONE +
		"\nFrom file: " + TWO +
		"\nExit: " + THREE;
	bool flag = true;
	do {
		cout << message << endl;
		getline(cin, line);
		if (ONE == line) {
			readFromConsole();
		}
		if (TWO == line) {
			makeActionWidthFile(*readAll);
		}
		if (THREE == line) {
			flag = false;
		}
	} while (flag);
}

void launch() {
	string line;
	string message = "Enter operation:\nAdd element: " + ONE +
		"\nDelete element by index: " + TWO +
		"\nDelete add same elements: " + THREE +
		"\nWrite data: " + FOUR +
		"\nExit: " + FIVE;
	bool flag = true;
	do {
		cout << message << endl;
		getline(cin, line);
		if (ONE == line) {
			addElement();
		}
		if (TWO == line) {
			deleteElement();
		}
		if (FOUR == line) {
			printList();
		}
		if (FIVE == line) {
			flag = false;
		}
	} while (flag);
}

int main() {
	launch();
}
