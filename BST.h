/*
 * BST.h
 * Vu Pham
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <cstddef>
#include <string>
#include <assert.h>
#include <iomanip>

#include <fstream>
#include "Product.h"
#include "ProductS.h"

using namespace std;

template<class bstdata>
class BST {
private:
	struct Node {
		bstdata data;
		Node* left;
		Node* right;

		Node(bstdata newdata) {
			data = newdata;
			left = NULL;
			right = NULL;
		}
	};
	Node* root;

	void copyHelper(Node* copy);
	void destructorHelper(Node* root);
	bstdata minimumHelper(Node* root) const; //no wrapper -> for removeHelper function
	void getSizeHelper(Node* root, int& size) const;
	bool searchHelper(Node* root, bstdata data) const;
	bstdata * findHelper(Node * root, bstdata data) const;
	void insertHelper(Node* root, bstdata data);
	Node* removeHelper(Node* root, bstdata data);
	void printListHelper(Node* root, int& index) const;
	void printByMakeHelper(Node* root, int& index, string make) const;
	void printByModelHelper(Node* root, int& index, string model) const;
	void saveHelper(ostream& out, Node*root) const;

public:
	BST();
	BST(const BST &bst);
	~BST();

	bool isEmpty() const;
	bstdata getRoot() const;
	int getSize() const;
	bool search(bstdata data) const;
	bstdata * find(bstdata data) const;
	void insert(bstdata data);
	void remove(bstdata data);
	void printList() const;
	//Prints list alphabetically
	void printByMake(string make) const;
	//Prints product(s) that have certain make name
	void printByModel(string model) const;
	//Prints product(s) that have certain model name
	void loadPrimary(string fname);
	//Loads products into BST storing Product objects
	void loadSecondary(string fname);
	//Loads products into BST storing ProductS objects
	void save(string fname) const;
	//Saves products into given file name
};

//Constructor
template<class bstdata>
BST<bstdata>::BST() {
	root = NULL;
}

//Copy constructor
template<class bstdata>
BST<bstdata>::BST(const BST &bst) {
	root = NULL;
	copyHelper(bst.root);
}

template<class bstdata>
void BST<bstdata>::copyHelper(Node* copy) {
	if (copy == NULL)
		return;
	else {
		insert(copy->data);
		copyHelper(copy->left);
		copyHelper(copy->right);
	}
	return;
}

//Destructor
template<class bstdata>
BST<bstdata>::~BST() {
	destructorHelper(root);
}

template<class bstdata>
void BST<bstdata>::destructorHelper(Node* root) {
	if (root == NULL)
		return;
	else {
		destructorHelper(root->left);
		destructorHelper(root->right);
		remove(root->data);
	}
}

template<class bstdata>
bstdata BST<bstdata>::minimumHelper(Node* root) const {
	if (root->left == NULL)
		return root->data;
	else
		return minimumHelper(root->left);
}

//Is list empty?
template<class bstdata>
bool BST<bstdata>::isEmpty() const {
	return root == NULL;
}

//Get data stored at root
template<class bstdata>
bstdata BST<bstdata>::getRoot() const {
	assert(!isEmpty());
	return root->data;
}

//Get tree size
template<class bstdata>
int BST<bstdata>::getSize() const {
	int size = 0;
	getSizeHelper(root, size);
	return size;
}

template<class bstdata>
void BST<bstdata>::getSizeHelper(Node* root, int& size) const {
	if (root == NULL) {
		return;
	} else {
		size++;
		getSizeHelper(root->left, size);
		getSizeHelper(root->right, size);
	}
}

//Is a value stored in the tree?
template<class bstdata>
bool BST<bstdata>::search(bstdata data) const {
	assert(!isEmpty());
	return searchHelper(root, data);
}

template<class bstdata>
bool BST<bstdata>::searchHelper(Node* root, bstdata data) const {
	if (data == root->data)
		return true;
	else if (data < root->data) {
		if (root->left == NULL)
			return false;
		else
			return searchHelper(root->left, data);
	} else {
		if (root->right == NULL)
			return false;
		else
			return searchHelper(root->right, data);
	}
	return false;	//optional depending on compiler
}

/* find and findHelper modified from search and searchHelper by Andrew 6/6 - may need addt'l testing */

template<class bstdata>
bstdata* BST<bstdata>::find(bstdata data) const {
	assert(!isEmpty());
	return findHelper(root, data);
}

template<class bstdata>
bstdata * BST<bstdata>::findHelper(Node * root, bstdata data) const {
	if (data == root->data)
		return &(root -> data);
	else if (data < root->data) {
		if (root->left == NULL)
			return NULL;
		else
			return findHelper(root->left, data);
	} else {
		if (root->right == NULL)
			return NULL;
		else
			return findHelper(root->right, data);
	}
	return NULL;	//optional depending on compiler
}

//Insert a new value
template<class bstdata>
void BST<bstdata>::insert(bstdata data) {
	if (root == NULL)
		root = new Node(data);
	else
		insertHelper(root, data);
}

template<class bstdata>
void BST<bstdata>::insertHelper(Node* root, bstdata data) {
	if (data == root->data)
		return;	//No duplicates
	if (data < root->data) {
		if (root->left == NULL)
			root->left = new Node(data);
		else
			insertHelper(root->left, data);
	} else {
		if (root->right == NULL)
			root->right = new Node(data);
		else
			insertHelper(root->right, data);
	}
}

//Remove a value
template<class bstdata>
void BST<bstdata>::remove(bstdata data) {
	assert(!isEmpty());
	root = removeHelper(root, data);//root may change due to deletion of value
}

template<class bstdata>
typename BST<bstdata>::Node* BST<bstdata>::removeHelper(Node* root,
		bstdata data) {
	if (root == NULL)
		return root;
	else if (data < root->data)
		root->left = removeHelper(root->left, data);
	else if (data > root->data)
		root->right = removeHelper(root->right, data);
	else {	//if data == root->data
		if ((root->left == NULL) && (root->right == NULL)) {	//leaf node
			delete root;
			root = NULL;
		} else if ((root->left != NULL) && (root->right == NULL)) {	//left but no right
			Node* temp = root;
			root = root->left;	//set left node to be root
			delete temp;	//delete former root
		} else if ((root->left == NULL) && (root->right != NULL)) {	//right but no left
			Node* temp = root;
			root = root->right;	//set right node to be root
			delete temp;	//delete former root
		} else {	//both children
			root->data = minimumHelper(root->right);//set data at root = minimum value of right subtree
			root->right = removeHelper(root->right, root->data);//delete  duplicate value in the right subtree
		}
	}
	return root;
}

template<class bstdata>
void BST<bstdata>::printList() const {
	int index = 1;
	printListHelper(root, index);
	cout << endl << endl;
}

template<class bstdata>
void BST<bstdata>::printListHelper(Node* root, int& index) const {
	if (root == NULL)
		return;
	else {
		printListHelper(root->left, index);
		cout << left << setw(16) << index;
		index++;
		cout << root->data;
		printListHelper(root->right, index);
	}
}

template<class bstdata>
void BST<bstdata>::printByMake(string make) const {
	int index = 1;
	printByMakeHelper(root, index, make);
	cout << endl << endl;
}

template<class bstdata>
void BST<bstdata>::printByMakeHelper(Node* root, int& index, string make) const {
	if (root == NULL)
		return;
	else {
		printByMakeHelper(root->left, index, make);
		if (root->data.getMake() == make) {
			cout << left << setw(16) << index;
			index++;
			cout << root->data;
		}
		printByMakeHelper(root->right, index, make);
	}
}

template<class bstdata>
void BST<bstdata>::printByModel(string model) const {
	int index = 1;
	printByModelHelper(root, index, model);
	cout << endl << endl;
}

template<class bstdata>
void BST<bstdata>::printByModelHelper(Node* root, int& index, string model) const {
	if (root == NULL)
		return;
	else {
		printByModelHelper(root->left, index, model);
		if (root->data.getModel() == model) {
			cout << left << setw(16) << index;
			index++;
			cout << root->data;
		}
		printByModelHelper(root->right, index, model);
	}
}

template<class bstdata>
void BST<bstdata>::loadPrimary(string fname) {
	string make, model;
	double screenSize, price;
	unsigned cpuGen, year;
	ifstream fin(fname);

	while (fin) {
		getline(fin, make, '\n');
		getline(fin, model, '\n');
		fin >> screenSize;
		fin >> cpuGen;
		fin >> year;
		fin >> price;
		Product p(make, model, screenSize, cpuGen, year, price);
		insert(p);
		while (fin.peek() == '\n')
			fin.get();
	}

	fin.close();
}

template<class bstdata>
void BST<bstdata>::loadSecondary(string fname) {
	string make, model;
	double screenSize, price;
	unsigned cpuGen, year;
	ifstream fin(fname);

	while (fin) {
		getline(fin, make, '\n');
		getline(fin, model, '\n');
		fin >> screenSize;
		fin >> cpuGen;
		fin >> year;
		fin >> price;
		ProductS p(make, model, screenSize, cpuGen, year, price);
		insert(p);
		while (fin.peek() == '\n')
			fin.get();
	}

	fin.close();
}

template<class bstdata>
void BST<bstdata>::save(string fname) const {
	ofstream fout(fname);
	saveHelper(fout, root);
	fout.close();
}

template<class bstdata>
void BST<bstdata>::saveHelper(ostream& out, Node*root) const {
	if (root == NULL)
		return;
	else {
		saveHelper(out, root->left);
		root->data.print(out);
		out << endl;
		saveHelper(out, root->right);
	}
}

#endif /* BST_H_ */
