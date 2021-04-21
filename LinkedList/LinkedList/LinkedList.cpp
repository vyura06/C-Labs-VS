#include <iostream>
#include <string>

using namespace std;

template<typename T>
struct Node {
	Node<T>* next = nullptr;
	Node<T>* previous = nullptr;
	T value;
};

template<typename E>
class LinkedList {
public:
	int size{};
	Node<E>* first0 = nullptr;
	Node<E>* last0 = nullptr;

	string outOfBoundsMsg(int index) {
		return "Index: " + to_string(index) + ", Size: " + to_string(size);
	}

	void checkElementIndex(int index) {
		if (index < 0 || index >= size)
			throw outOfBoundsMsg(index);
	}

	void checkPositionIndex(int index) {
		if (index < 0 || index > size)
			throw outOfBoundsMsg(index);
	}

	Node<E>* getNode(int index) {
		Node<E>* node = nullptr;
		if (index < (size / 2)) {
			node = first0;
			for (int i = 0; i < index; i++)
				node = node->next;
		}
		else {
			node = last0;
			for (int i = size - 1; i > index; i--)
				node = node->previous;
		}
		return node;
	}

	int indexOf(E object) {
		int index = 0;
		Node<E>* node = first0;
		while (node != nullptr) {
			if (object == node->value)
				return index;
			index++;
			node = node->next;
		}
		return -1;
	};

	void linkFirst(E element) {
		Node<E>* first = first0;
		auto* newNode = new Node<E>();
		newNode->value = element;
		newNode->next = first;
		first0 = newNode;
		if (first == nullptr)
			last0 = newNode;
		else
			first->previous = newNode;
		size++;
	}

	void linkLast(E element) {
		Node<E>* last = last;
		auto* newNode = new Node<E>();
		newNode->previous = last;
		newNode->value = element;
		last0 = newNode;
		if (last == nullptr)
			first0 = newNode;
		else
			last->next = newNode;
		size++;
	}

	void linkBefore(E element, Node<E>* node) {
		Node<E>* previous = node->previous;
		auto* newNode = new Node<E>();
		newNode->previous = previous;
		newNode->value = element;
		newNode->next = node;
		node->previous = newNode;
		if (previous == nullptr)
			first0 = newNode;
		else
			previous->next = newNode;
		size++;
	}

	E unlinkFirst(Node<E>* node) {
		E element = node->value;
		Node<E>* next = node->next;
		node->value = nullptr;
		node->next = nullptr;
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
		node->value = nullptr;
		node->previous = nullptr;
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

		node->value = nullptr;
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
		for (Node<E>* node = first0; node != nullptr; node = node->next) {
			if (object == node->value) {
				unlink(node);
				return true;
			}
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
		if (first0 == nullptr) {
			result = "[]";
		}
		else {
			result += '[';
			Node<E>* next;
			Node<E>* node = first0;
			bool flag = true;
			do {
				next = node->next;
				result += to_string(node->value);
				if (next == nullptr) {
					result = result += ']';
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

	string naoborot() {
		string result;
		if (last0 == nullptr) {
			result = "[]";
		}
		else {
			result += '[';
			Node<E>* previous;
			Node<E>* node = last0;
			bool flag = true;
			do {
				previous = node->previous;
				result.append(node->value);
				if (previous == nullptr) {
					result += ']';
					flag = false;
				}
				else {
					result += ", ";
					node = previous;
				}
			} while (flag);
		}
		return result;
	}

	LinkedList() = default;
};



