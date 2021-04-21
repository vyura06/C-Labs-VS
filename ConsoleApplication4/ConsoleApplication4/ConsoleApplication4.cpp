#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename E>
class LinkedList {
private:
	template <typename E>
	struct Node {
	public:
		E value;
		Node<E>* next = nullptr;
	};

	Node<E>* first = nullptr;
	Node<E>* last = nullptr;
	int size = 0;

	void checkElementIndex(int& index) {
		if (index < 0 || index >= size) {
			string message;
			message += "Index: " + to_string(index) + ", Size: " + to_string(size);
			throw exception(message);
			cout << "Index out of bounds. Index = " << to_string(index) << ", size = " << to_string(size) << endl;
			throw - 1;
		}
	}

	Node<E>* getNode(int& index) {
		Node<E>* node = first;
		for (int i = 0; i < index; i++) {
			node = node->next;
		}
		return node;
	}

	void unlink(Node<E>* previous, Node<E>* node) {
		Node<E>* next = node->next;
		if (previous == nullptr) {
			first = next;
		}
		else {
			previous->next = next;
		}
		if (next == nullptr) {
			last = previous;
		}
		else {
			node->next = nullptr;
		}
		size--;
	}
public:
	int getsize()
	{
		return size;
	}

	E get(int& index) {
		checkElementIndex(index);
		Node<E>* node = getNode(index);
		return node->value;
	}

	void add(E element) {
		Node<E>* newNode = new Node<E>();
		newNode->value = element;
		if (last == nullptr) {
			first = newNode;
		}
		else {
			last->next = newNode;
		}
		last = newNode;
		size++;
	}

	void remove(int& index) {
		checkElementIndex(index);
		Node<E>* previous = nullptr;
		Node<E>* node = first;
		for (int i = 0; i < index; i++) {
			previous = node;
			node = node->next;
		}
		unlink(previous, node);
	}

	void removeAll(E object) {
		Node<E>* previous = nullptr;
		Node<E>* node = first;
		Node<E>* next;
		while (node != nullptr) {
			next = node->next;
			if (object == node->value) {
				unlink(previous, node);
			}
			else {
				previous = node;
			}
			node = next;
		}
	}

	string show() {
		string result;
		if (first == nullptr) {
			result = "[]";
		}
		else {
			result += '[';
			Node<E>* next;
			Node<E>* node = first;
			bool flag = true;
			do {
				next = node->next;
				result += node->value;
				if (next == nullptr) {
					result += ']';
					flag = false;
				}
				else {
					result += ", ";
					node = next;
				}
			} while (flag);
		}
		return result;
	}
};

LinkedList<LinkedList<string>> SOURCE;

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

void makeActionWidthFile(void consumer(fstream&, LinkedList<string>&), LinkedList<string>& list) {
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
				consumer(filesteam, list);
				filesteam.close();
			}
			else {
				cout << "File doesn't exist" << endl;
			}
		}
	} while (flag);
}

void writeInFile(fstream& filestream, LinkedList<string>& list) {
	filestream << list.show() << endl;
	cout << "Saved" << endl;
}

void writeToConsole(LinkedList<string>& list) {
	cout << list.show() << endl;
}

void printList(LinkedList<string>& list) {
	string line;
	string message = "Select when you want write data:\nTo console: " + ONE +
		"\nTo file: " + TWO +
		"\nExit: " + THREE;
	bool flag = true;
	do {
		cout << message << endl;
		getline(cin, line);
		if (ONE == line) {
			writeToConsole(list);
		}
		else if (TWO == line) {
			makeActionWidthFile(*writeInFile, list);
		}
		else if (THREE == line) {
			flag = false;
		}
	} while (flag);
}

void deleteAllSameElements(LinkedList<string>& list) {
	cout << "Enter line" << endl;
	string line;
	getline(cin, line);
	list.removeAll(line);
}

void deleteElement(LinkedList<LinkedList<string>>& list) {
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
			list.remove(index);
			flag = false;
		}
	} while (flag);
}

void deleteElement(LinkedList<string>& list) {
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
			list.remove(index);
			flag = false;
		}
	} while (flag);
}

void readAll(fstream& filestream, LinkedList<string>& list) {
	string line;
	while (getline(filestream, line)) {
		list.add(line);
	}
}

void readFromConsole(LinkedList<string>& list) {
	cout << "Enter line" << endl;
	string line;
	getline(cin, line);
	list.add(line);
}

void addElement(LinkedList<string>& list) {
	string line;
	string message = "Select when you want read data:\nFrom console: " + ONE +
		"\nFrom file: " + TWO +
		"\nExit: " + THREE;
	bool flag = true;
	do {
		cout << message << endl;
		getline(cin, line);
		if (ONE == line) {
			readFromConsole(list);
		}
		if (TWO == line) {
			makeActionWidthFile(*readAll, list);
		}
		if (THREE == line) {
			flag = false;
		}
	} while (flag);
}

void operations(LinkedList<string>& list) {
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
			addElement(list);
		}
		if (TWO == line) {
			deleteElement(list);
		}
		if (THREE == line) {
			deleteAllSameElements(list);
		}
		if (FOUR == line) {
			printList(list);
		}
		if (FIVE == line) {
			flag = false;
		}
	} while (flag);
}

LinkedList<string> getList() {
	LinkedList<string> result;
	string message = "Enter index";
	bool flag = true;
	do {
		cout << message << endl;
		int index = getNumber();
		if (index < 0) {
			cout << "Index can be positive!" << endl;
		}
		if (index >= SOURCE.getsize()) {
			cout << "Index out of bounds. Index = " << to_string(index) << ", size = " << to_string(SOURCE.getsize()) << endl;
		}
		else {
			result = SOURCE.get(index);
			flag = false;
		}
	} while (flag);
	return result;
}

void deleteList() {
	deleteElement(SOURCE);
}

void createNewList() {
	LinkedList<string> newList;
	SOURCE.add(newList);
	cout << "Done" << endl;
}

void launch() {
	string line;
	string message = "Enter operation:\nCreate new list: " + ONE +
		"\nDelete list by index: " + TWO +
		"\nMake operations width list: " + THREE +
		"\nExit: " + FOUR;
	bool flag = true;
	do {
		cout << message << endl;
		getline(cin, line);
		if (ONE == line) {
			createNewList();
		}
		if (TWO == line) {
			deleteList();
		}
		if (THREE == line) {
			if (SOURCE.getsize() == 0) {
				cout << "List is empty! Create new list" << endl;
			}
			else {
				LinkedList<string> list = getList();
				operations(list);
			}
		}
		if (FOUR == line) {
			flag = false;
		}
	} while (flag);
}

int main() {
	launch();
}

