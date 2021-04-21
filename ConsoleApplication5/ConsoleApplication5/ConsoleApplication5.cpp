#include <iostream>
#include <windows.h>
#include <fstream>


using namespace std;

struct Tree {
	int data;
	Tree* left;
	Tree* right;
};


Tree* root;

Tree* addElement(Tree* current, int data);
void add(int value);
void makeAnEmptyTree();
void traversePreOrder(Tree* node);
void deleteElement(int data);
Tree* deleteRecursive(Tree* current, int data);
Tree* deleteAfterFinding(Tree* current);
Tree* deleteIfThereAreTwoBranches(Tree* current);
int findSmallestValue(Tree* root);



Tree* addElement(Tree* current, int data) {
	if (current == NULL) {
		current = new Tree;
		current->data = data;
		current->left = current->right = NULL;
	}
	else {
		if (data < current->data) {
			current->left = addElement(current->left, data);
		}
		else {
			if (data > current->data) {
				current->right = addElement(current->right, data);
			}
		}
	}
	return current;
}


void add(int value) {

	root = addElement(root, value);
}


void makeAnEmptyTree() {
	Tree* root;
	root = NULL;
	cout << endl << root;
}


void traversePreOrder(Tree* node) {

	if (node != NULL) {
		cout << " " << node->data;
		traversePreOrder(node->left);
		traversePreOrder(node->right);
	}
}


void deleteElement(int data) {
	root = deleteRecursive(root, data);
}


Tree* deleteRecursive(Tree* current, int data) {
	Tree* element;
	if (current == NULL) {
		element = NULL;
	}
	else {
		if (data == current->data) {
			element = deleteAfterFinding(current);
		}
		else {
			if (data < current->data) {
				current->left = deleteRecursive(current->left, data);
				element = current;
			}
			else {
				current->right = deleteRecursive(current->right, data);
				element = current;
			}
		}
	}
	return element;
}


Tree* deleteAfterFinding(Tree* current) {
	Tree* element;
	if (current->left == NULL && current->right == NULL) {
		element = NULL;
	}
	else {
		if (current->right == NULL) {
			element = current->left;
		}
		else {
			if (current->left == NULL) {
				element = current->right;
			}
			else {
				element = deleteIfThereAreTwoBranches(current);
			}
		}
	}
	return element;
}

Tree* deleteIfThereAreTwoBranches(Tree* current) {

	int smallestValue = findSmallestValue(current->right);
	current->data = smallestValue;
	current->right = deleteRecursive(current->right, smallestValue);
	Tree* element = current;
	return element;
}


int findSmallestValue(Tree* root) {
	int smallestElement;
	if (root->left == NULL) {
		smallestElement = root->data;
	}
	else {
		smallestElement = findSmallestValue(root->left);
	}
	return smallestElement;

}


int main()
{
	add(4);
	add(2);
	add(6);
	add(5);
	add(5);
	add(20);
	add(1);
	add(3);
	traversePreOrder(root);
	deleteElement(6);
	cout << endl;
	traversePreOrder(root);
	//makeAnEmptyTree();//создаем пустое дерево
	return 0;
}
