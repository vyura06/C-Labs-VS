#include<iostream>
#include<string>
#include<sstream>
#include "Header.h"



	int getSize() {
		return size;
	}

	void add(E value) {
		Node<E>* node = root;
		Node<E>* newNode = new Node<E>();
		newNode->value = value;
		if (node == nullptr) {
			root = newNode;
		}
		else {
			int current = 0;
			Node<E>* parent = nullptr;
			do {
				parent = node;
				current = comparator(value, node->value);
				if (current < 0) {
					node = node->left;
				}
				else {
					node = node->right;
				}
			} while (node != nullptr);
			newNode->parent = parent;
			if (current < 0) {
				parent->left = newNode;
			}
			else {
				parent->right = newNode;
			}
		}
		size++;
	}

	bool contains(E value) {
		bool result = getNodeValue(value) != nullptr;
		return result;
	}

	bool remove(E value) {
		Node<E>* node = getNodeValue(value);
		bool result;
		if (node == nullptr) {
			result = false;
		}
		else {
			deleteNode(node);
			result = true;
		}
		return result;
	}

	bool removeE(E element) {
		bool result = false;
		Node<E>* node = getNodeValue(element);
		if (node != nullptr) {
			Node<E>* parent = node->parent;
			if (parent != nullptr) {
				if (parent->left == node) {
					parent->left = nullptr;
					result = true;
				}
				else if (parent->right == node) {
					parent->right = nullptr;
					result = true;
				}
			}
		}
		return result;
	}

	void clear() {
		size = 0;
		root = nullptr;
	}

	Node<E>* getFirstNode() {
		Node<E>* node = root;
		if (node != nullptr) {
			while (node->left != nullptr) {
				node = node->left;
			}
		}
		return node;
	}

	string toString() {
		string result;
		result += '[';
		if (root != nullptr) {
			Node<E>* next;
			Node<E>* node = getFirstNode();
			bool flag = true;
			while (flag) {
				next = nextOf(node);
				result += node->value;
				if (next == nullptr) {
					flag = false;
				}
				else {
					result += ", ";
					node = next;
				}
			}
		}
		result += ']';
		return result;
	}
};

int getNumber() {
	int result;
	string line;
	cout << "Enter number" << endl;
	while (!(cin >> result)) {
		cout << "Error" << endl;
		cin.clear();
		cin.sync();
		getline(cin, line);
	}
	getline(cin, line);
	return result;
}

string getLine() {
	cout << "Enter line" << endl;
	string line;
	getline(cin, line);
	return line;
}

string boll_to_string(bool value) {
	if (value) {
		return "true";
	}
	else {
		return "false";
	}
}

void launch(Tree<string>& tree) {
	string one = "1";
	string two = "2";
	string three = "3";
	string four = "4";
	string five = "5";
	string six = "6";
	string seven = "7";
	string message;
	message += "Enter operation:";
	message += "\nAdd = " + one;
	message += "\nContains element = " + two;
	message += "\nRemove element = " + three;
	message += "\nClear = " + four;
	message += "\nPrint = " + five;
	message += "\nRemove children = " + six;
	message += "\nExit = " + seven;
	string line;
	bool flag = true;
	bool temp;
	do {
		cout << message << endl;
		getline(cin, line);
		if (one == line) {
			tree.add(getLine());
			cout << "Done" << endl;
		}
		else if (two == line) {
			temp = tree.contains(getLine());
			cout << boll_to_string(temp) << endl;
		}
		else if (three == line) {
			temp = tree.remove(getLine());
			cout << boll_to_string(temp) << endl;
		}
		else if (four == line) {
			tree.clear();
			cout << "Done" << endl;
		}
		else if (five == line) {
			cout << tree.toString() << endl;
		}
		else if (six == line) {
			cout << boll_to_string(tree.removeE(getLine())) << endl;
		}
		else if (seven == line) {
			flag = false;
		}
	} while (flag);
}

int compareInt(int first, int second)
{
	int result;
	if (first == second) {
		result = 0;
	}
	else if (first > second) {
		result = 1;
	}
	else {
		result = -1;
	}
	return result;
}

int comparator(string first, string second)
{
	int result;
	stringstream ss;
	ss << first;
	int first0, second0;
	if (ss >> first0) {
		ss.clear();
		ss.sync();
		ss << second;
		if (ss >> second0) {
			result = compareInt(first0, second0);
			return result;
		}
	}
	result = first.compare(second);
	return result;
}

int main() {
	Tree<string> tree;
	tree.comparator = comparator;
	launch(tree);
	return 0;
}