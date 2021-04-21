#pragma once

#include<iostream>
#include<string>
#include<sstream>

using namespace std;

template<typename T>
struct Node {
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
	Node<T>* parent = nullptr;
	T value;
	int index = 0;
	int countChildren = 0;
	bool select = false;
};

template<typename E>
class Tree {
public:
	int size = 0;
	Node<E>* root = nullptr;

	int(*comparator) (E first, E second) = nullptr;

	Node<E>* getNodeValue(E value) {
		Node<E>* result = nullptr;
		Node<E>* node = root;
		int current;
		while (node != nullptr) {
			current = comparator(value, node->value);
			if (current < 0) {
				node = node->left;
			}
			else if (current > 0) {
				node = node->right;
			}
			else {
				result = node;
				node = nullptr;
			}
		}
		return result;
	}

	Node<E>* nextOf(Node<E>* node) {
		Node<E>* result = nullptr;
		if (node != nullptr) {
			if (node->right != nullptr) {
				result = node->right;
				while (result->left != nullptr)
					result = result->left;
			}
			else {
				result = node->parent;
				Node<E>* temp = node;
				while (result != nullptr && temp == result->right) {
					temp = result;
					result = result->parent;
				}
			}
		}
		return result;
	}

	void deleteNode(Node<E>* node) {
		if (node->left != nullptr && node->right != nullptr) {
			Node<E>* temp = nextOf(node);
			node->value = temp->value;
			node = temp;
		}
		Node<E>* replacement = (node->left == nullptr ? node->right : node->left);
		if (replacement != nullptr) {
			replacement->parent = node->parent;
			if (node->parent == nullptr) {
				root = replacement;
			}
			else if (node == node->parent->left) {
				node->parent->left = replacement;
			}
			else {
				node->parent->right = replacement;
			}
			node->left = nullptr;
			node->right = nullptr;
			node->parent = nullptr;
		}
		else if (node->parent == nullptr) {
			root = nullptr;
		}
		else {
			if (node == node->parent->left) {
				node->parent->left = nullptr;
			}
			else if (node == node->parent->right) {
				node->parent->right = nullptr;
			}
			node->parent = nullptr;
		}
		size--;
	}
