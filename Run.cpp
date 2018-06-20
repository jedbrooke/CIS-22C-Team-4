/*
 * Product.h
 * Vu Pham
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	string make;
	string model;
	double screenSize;
	unsigned cpuGen;
	unsigned year;
	double price;

public:
	Product();
	Product(string make, string model, double screenSize, unsigned cpuGen, unsigned year, double price);

	string getMake() const;
	string getModel() const;
	double getScreenSize() const;
	unsigned getCpuGen() const;
	unsigned getYear() const;
	double getPrice() const;

	void setMake(string make);
	void setModel(string model);
	void setScreenSize(double screenSize);
	void setCpuGen(unsigned cpuGen);
	void setYear(unsigned year);
	void setPrice(double price);

	bool operator==(const Product& product);
	//determines if this->product and product are the same
	bool operator<(const Product& product);
	//determines if this->product comes before product alphabetically BASED ON PRIMARY KEY (make) FIRST, THEN SECONDARY KEY (model)
	bool operator>(const Product& product);
	//determines if this->product comes after product alphabetically BASED ON PRIMARY KEY (make) FIRST, THEN SECONDARY KEY (model)

	friend ostream& operator<<(ostream& out, const Product& product);
	//prints all fields using a column format
	void print(ostream& out) const;
	//Print in the format of:
	//<make>
	//<model>
	//<screenSize>
	//<cpuGen>
	//<year>
	//<price>
	string toString() const;
};


#endif /* PRODUCT_H_ */


/*
 * ProductS.h
 * Vu Pham
 */


#ifndef PRODUCTS_H_
#define PRODUCTS_H_

#include <iostream>
#include <string>


using namespace std;

class ProductS : public Product {
public:
	ProductS();
	ProductS(string make, string model, double screenSize, unsigned cpuGen, unsigned year, double price);

	void operator=(const Product& product);
	//copies contents from Product to ProductS

	//Overriding functions
	bool operator==(const ProductS& product);
	//determines if this->product and product are the same
	bool operator<(const ProductS& product);
	//determines if this->product comes before product alphabetically BASED ON SECONDARY KEY (model) FIRST, THEN PRIMARY KEY (make)
	bool operator>(const ProductS& product);
	//determines if this->product comes after product alphabetically BASED ON SECONDARY KEY (model) FIRST, THEN PRIMARY KEY (make)
};



#endif /* PRODUCTS_H_ */


/*
 * User.h
 * Vu Pham
 */

#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <string>
using namespace std;

class User {
protected:
	string username;
	string password;
	string firstname;
	string lastname;
	bool isEmployee;

public:
	User();

	string getUsername() const;
	string getPassword() const;
	string getFirstname() const;
	string getLastname() const;
	bool getIsEmployee() const;

	void setUsername(string username);
	void setPassword(string password);
	void setFirstname(string firstname);
	void setLastname(string lastname);
	void setIsEmployee(bool isEmployee);

};


#endif /* USER_H_ */


/*
 * List.h
 * Andrew Maxwell
 */

#ifndef LIST_H_
#define LIST_H_
#include <iostream>
#include <cstddef> //for NULL
#include <assert.h>
using namespace std;

template <class listdata> //list stores generic listdata

class List {

private:
    struct Node {
        listdata data;
        Node* next;
        Node* previous;

        Node(listdata newData){
            data = newData;
            next = NULL;
            previous = NULL;
        }
    };

    Node* start;
    Node* stop;
    Node* iterator;
    int length;

public:

    /**Constructors and Destructors*/

    List();
    //Default constructor; initializes an empty list
    //Postcondition: start and stop initialized to null.
    //Length initialized to 0.

    List(const List<listdata> &oldList);
    //Copy constructor; creates a duplicate list
    //Postcondition: New list has same data as old list, stored
    //in different memory.

    ~List();
    //Destructor. Frees memory allocated to the list
    //Postcondition: Deletes every node in the list
    //before the list object is destroyed.

    /**Accessors*/

    listdata getStart() const;
    //Returns the data at the start of the list
    //Precondition: Length of list >= 1.

    listdata getStop() const;
    //Returns the data at the end of the list
    //Precondition: Length of list >= 1.

    bool isEmpty() const;
    //Determines whether a list is empty.

    int getLength() const;
    //Returns the size of the list

    listdata getIterator() const;
    //returns the data stored in the element pointed at by the iterator
    //Precondition: Iterator must be pointing at a list element

    bool offEnd() const;
    //Is false if iterator is pointing at a valid list element

    bool operator==(const List &rhs) const;
    //Compares two lists.

    bool isSorted() const;

    //Wrapper function that calls the isSorted helper function to determine whether
    //a list is sorted in ascending order.
    //We will consider that a list is trivially sorted if it is empty.
    //Therefore, no precondition is needed for this function

private:

    bool isSorted(Node* node) const;
    //Helper function for the public isSorted() function.
    //Recursively determines whether a list is sorted in ascending order.

public:

    int getIndex() const;
    //Indicates the index of the Node where the iterator is currently pointing
    //Nodes are numbered starting at 1 through the size of the list
    //Pre: !offEnd()

    int linearSearch(listdata data) const;
    //Iteratively searchs the list, element by element, from the start of the List to the end of the List
    //Returns the index of the element, if it is found in the List
    //Does not call the indexing functions in the implementation
    //Returns -1 if the element is not in the List
    //Pre: length != 0
    //Post: The iterator location has not been changed

    int binarySearch(listdata data) const;
    //Returns the index where data is located in the List
    //Calls the private helper function binarySearch to perform the search
    //Pre: length != 0
    //Pre: List is sorted (must test on a sorted list)
    //Post: The iterator location has not been changed

private:

    int binarySearch(int low, int high, listdata data) const;
    //Recursively search the list by dividing the search space in half
    //Returns the index of the element, if it is found in the List
    //Returns -1 if the element is not in the List
    //Post: The iterator location has not been changed

public:

    /**Manipulation Procedures*/

    void removeStart();
    //Removes the value stored in first node in the list
    //Precondition: Length of list >= 1.
    //Postcondition: First node of list is deleted. Start pointer
    //now points to second node in the list.

    void removeStop();
    //Removes the value stored in the last node in the list
    //Precondition: Length of list >= 1.
    //Postcondition: Last node of list is deleted. Stop pointer now
    //points to the new last node. Last node points to null.

    void insertStart (listdata data);
    //Inserts a new data at the beginning of the list
    //If the list is empty, the new data becomes both start and stop
    //Postcondition: Node created at the beginning of the list,
    //data stored in node.

    void insertStop(listdata data);
    //Inserts a new data at the end of the list
    //If the list is empty, the new data becomes both start and stop
    //Postcondition: Node created at end of list, data stored in node.

    void startIterator();
    //Sets the iterator to the start pointer

    void removeIterator();
    //Deletes the node pointed at by the iterator.
    //Precondition: Iterator must be pointing at a valid list node.

    void insertIterator(listdata data);
    //Inserts a list node after the one pointed at by the iterator.
    //Postcondition: New list node.
    //Precondition: Iterator must point at a valid node.

    void moveIterNext();
    //move iterator up list one

    void moveIterPrevious();
    //move iterator down list one

    void moveToIndex(int index);
    //Moves the iterator to the node whose index number is specified in the parameter
    //Nodes are numbered starting at 1 through the size of the List
    //Pre: size != 0
    //Pre: index <= size

    /**Additional List Operations*/

    void displayList(ostream &out) const;
    //Prints to the console the value of each data in the list sequentially
    //and separated by a blank space
    //Prints a empty newline character if it's empty..

    void displayNumberedList(ostream &out) const;
    //Prints to the console the value of each data in the list, with a number.
    //Prints an empty newline character if the list is empty.

    void displayReverse(ostream& out) const;
    //Wrapper function that calls the private displayReverse helper function to print a list in reverse
    //prints nothing if the List is empty

private:

    void displayReverse(Node* node, ostream& out) const;
    //Helper function for the public displayReverse wrapper function.
    //Recursively prints the data in a List in reverse.
};

#endif /* LIST_H_ */

/**Function Declarations*/
/**Constructors and Destructors*/

template <class listdata>   //Default constructor
List<listdata>::List() {
    start = stop = iterator = NULL;
    length = 0;
}

template <class listdata>
List<listdata>::List(const List<listdata> &oldList) {   //Copy constructor
	length = 0;
	if (oldList.length == 0)
	{
		start = stop = iterator = NULL;
	}
	else
	{
		Node * temp = oldList.start;
		while (temp != NULL)
		{
			insertStop(temp -> data);
			temp = temp -> next;
		}
	}
}

template <class listdata>   //Destructor
List<listdata>::~List()
{
    Node* b = start;
    Node* a = NULL; //a stands for "after" (i.e. after b)
    while (b != NULL)
    {
        a = b -> next; //move a to node after b
        delete b; //remove b (you know it is not NULL from if)
        b = a; //b "catches up" with a (both point to same place in list)
    }
}

/**Accessors*/

template <class listdata>   //returns data in first element
listdata List<listdata>::getStart() const
{
    assert(start);
    return start -> data;
}

template <class listdata>   //returns data in last element
listdata List<listdata>::getStop() const
{
    assert(stop);
	return stop -> data;
}

template <class listdata>   //returns whether the list is empty
bool List<listdata>::isEmpty() const
{
    return (length == 0);
}

template <class listdata>   //returns number of elements
int List<listdata>::getLength() const
{
	return length;
}

template <class listdata>   //returns data contained in element at iterator
listdata List<listdata>::getIterator() const
{
    assert(iterator);
    return iterator -> data;
}

template <class listdata>   //Returns false if iterator points to an element.
bool List<listdata>::offEnd() const
{
    return (iterator == NULL);
}

template <class listdata>   //== operator overload
bool List<listdata>::operator==(const List &rhs) const
{
    Node * thisIterator = start;
    Node * thatIterator = rhs.start;
    bool same = true;
    while (thisIterator and thatIterator)
    {
        if (thisIterator -> data != thatIterator -> data)
        {
            same = false;
            break;
        }
        else
        {
            thisIterator = thisIterator -> next;
            thatIterator = thatIterator -> next;
        }
    }
    if (thisIterator != thatIterator)
    {
        same = false;
    }
    return same;
}

template <class listdata>
bool List<listdata>::isSorted() const
{
    if (length < 2) {
        return true;
    }
    else {
        return isSorted(start);
    }
}

template <class listdata>
bool List<listdata>::isSorted(Node* node) const
{
    bool inOrder = true;
    if (node -> next != NULL) {
        if (node -> next -> data > node -> data and isSorted(node -> next)) {
            inOrder = true;
        }
        else {
            inOrder = false;
        }
    }
    return inOrder;
}

template <class listdata>
int List<listdata>::getIndex() const {
    assert(iterator != NULL);
    Node * temp = start;
    int count = 1;
    while (temp != iterator) {
        temp = temp -> next;
        count++;
    }
    return count;
}

template <class listdata>
int List<listdata>::linearSearch(listdata data) const {
    Node * tempIter = start;
    int index = 1;
    bool found = false;
    while (tempIter != NULL) {
        if (data == tempIter -> data) {
            found = true;
            break;
        }
        else {
            index++;
            tempIter = tempIter -> next;
        }
    }
    if(found) {
        return index;
    }
    else {
        return -1;
    }
}

template <class listdata>
int List<listdata>::binarySearch(listdata data) const {
    assert(length > 0);
    assert(isSorted());
    return binarySearch(0, length, data) + 1;
}

template <class listdata>
int List<listdata>::binarySearch(int low, int high, listdata data) const {
    Node * tempIter = start;
    for (int i = 0; i < (low + high) / 2; i++) {
        tempIter = tempIter -> next;
    }
    if (tempIter -> data == data) {
        return ((low + high) / 2);
    }
    else if (low + 1 == high) {
        return -2;
    }
    else if (tempIter -> data < data) {
        return binarySearch((low + high) / 2, high, data);
    }
    else {
        return binarySearch(low, (low + high) / 2, data);
    }
}



/**Manipulation Procedures*/

template <class listdata>   //Removes first node in the list.
void List<listdata>::removeStart()
{
    assert(start);
    if (length == 1)
	{
		delete start;
		start = stop = NULL;
		length--;
	}
	else
	{
		start = start -> next;
		delete start -> previous;
		start -> previous = NULL;
		length--;
	}
}

template <class listdata>   //removes last element in the list
void List<listdata>::removeStop()
{
    assert(stop);
    if (length == 1)
	{
		delete stop;
		start = stop = NULL;
		length = 0;
	}
	else
	{
		stop = stop -> previous;
		delete stop -> next;
		stop -> next = NULL;
		length--;
	}
}

template <class listdata>   //Inserts node at start of list
void List<listdata>::insertStart(listdata data)
{
    Node* N = new Node(data);
    if (length == 0)
    {
        start = N;
        stop = N;
    }
    else
    {
        N -> next = start;
        start -> previous = N;
        start = N;
    }
    length++;
}

template <class listdata>   //Inserts node at end of list
void List<listdata>::insertStop(listdata data)
{
	Node* N = new Node(data);
	if (length == 0)
	{
		start = N;
		stop = N;
	}
	else
	{
		stop -> next = N;
		N -> previous = stop;
		stop = N;
	}
	length++;
}

template <class listdata>   //moves iterator to start of list
void List<listdata>::startIterator()
{
    iterator = start;
}

template <class listdata>   //removes element pointed at by iterator.
void List<listdata>::removeIterator()
{
    assert(iterator);
    if (iterator -> next)
    {
    iterator -> next -> previous = iterator -> previous;
    }
    else
    {
        stop = iterator -> previous;
    }
    if (iterator -> previous)
    {
    iterator -> previous -> next = iterator -> next;
    }
    else
    {
        start = iterator -> next;
    }
    delete iterator;
    iterator = NULL;
    length--;
}

template <class listdata>   //inserts an element after the element the iterator
void List<listdata>::insertIterator(listdata data)
{
    assert(iterator);
    Node * newNode = new Node(data);
    if (iterator -> next)
    {
        iterator -> next -> previous = newNode;
        newNode -> next = iterator -> next;
    }
    else
    {
        stop = newNode;
    }
    newNode -> previous = iterator;
    iterator -> next = newNode;
    length++;
}

template <class listdata>   //moves iterator towards the end
void List<listdata>::moveIterNext()
{
    assert(iterator);
    iterator = iterator -> next;
}

template <class listdata>   //moves iterator towards the start
void List<listdata>::moveIterPrevious()
{
    assert(iterator);
    iterator = iterator -> previous;
}

template <class listdata>
void List<listdata>::moveToIndex(int index) {
    index--;
    assert (length > 0);
    assert (index <= length);
    startIterator();
    for (int i = 0; i < index; i++) {
        moveIterNext();
    }
}

/** Display functions */

template <class listdata>   //Displays the list
void List<listdata>::displayList(ostream &out) const
{
    Node* temp = start; //create a temporary iterator
    while (temp != NULL) {
    	out << temp->data << " ";	//outputs data
    	temp = temp->next;		//moves iterator to next node
    }
    out << endl; //ends line after outputting list
}

template <class listdata>   //displays list vertically w/ numbers.
void List<listdata>::displayNumberedList(ostream &out) const
{
    Node* temp = start;
    int i = 1;
    while (temp != NULL)
    {
        out << "#" << i << ": " << &temp -> data << endl;
        temp = temp -> next;
        i++;
    }
}

template <class listdata> //displays list in reverse - public wrapper function
void List<listdata>::displayReverse(ostream &out) const
{
    cout << endl;
    if (stop) {
        displayReverse(stop, out);
    }
}

template <class listdata> //displays list in reverse - recursive helper function
void List<listdata>::displayReverse(Node * node, ostream &out) const
{
    out << node -> data << " ";
    if (node -> previous != NULL) {
        displayReverse(node -> previous, out);
    }
}






/*
 * SubOrder.h
 * Andrew Maxwell
 */

#ifndef SRC_SUBORDER_H_
#define SRC_SUBORDER_H_


struct subOrder {
	Product * laptop;
	int quantity;
	float price;
	subOrder();					//Default constructor

	subOrder(Product * toBuy);	//Constructor

	void setQuantity(int q);	//Changes the number of laptops

	int getQuantity();

	friend ostream & operator<<(ostream & out, const subOrder& SO);

	bool operator==(const subOrder &rhs);
};

#endif /* SRC_SUBORDER_H_ */


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
#include <vector>
#include <sstream>

#include <fstream>

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

	//to-String methods
	void printListToStringHelper(Node* root, int& index, vector<string> &string) const;
	void printByMakeToStringHelper(Node* root, int& index, string make, vector<string> &string);
	void printByModelToStringHelper(Node* root, int& index, string model, vector<string> &string);

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

	//to-String methods
	vector<string> printListToString() const;
	//returns a vector of string for the list of products
	vector<string> printByMakeToString(string make) const;
	//returns a vector of string for a list of products that have certain make name
	vector<string> printByModelToString(string model) const;
	//returns a vector of string for a list of products that have certain model name
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
		root->data.print(out);
		out << endl;
		saveHelper(out, root->left);
		saveHelper(out, root->right);
	}
}

template<class bstdata>
vector<string> BST<bstdata>::printListToString() const {
	int index = 1;
	vector<string> string;
	printListToStringHelper(root, index, string);
	return string;
}

template<class bstdata>
void BST<bstdata>::printListToStringHelper(Node* root, int& index, vector<string> &string) const {
	if (root == NULL)
		return;
	else {
		printListToStringHelper(root->left, index, string);
		stringstream ss;
		ss << index++ << "," << root->data.toString();
		string.push_back(ss.str());
		printListToStringHelper(root->right, index, string);
	}
}

template<class bstdata>
vector<string> BST<bstdata>::printByMakeToString(string make) const {
	int index = 1;
	vector<string> string;
	printByMakeToStringHelper(root, index, make, string);
	return string;
}

template<class bstdata>
void BST<bstdata>::printByMakeToStringHelper(Node* root, int& index, string make, vector<string> &string) {
	if (root == NULL)
		return;
	else {
		printByMakeToStringHelper(root->left, index, make, string);
		if (root->data.getMake() == make) {
			stringstream ss;
			ss << index++ << "," << root->data.toString();
			string.push_back(ss.str());
		}
		printByMakeToStringHelper(root->right, index, make, string);
	}
}

template<class bstdata>
vector<string> BST<bstdata>::printByModelToString(string model) const {
	int index = 1;
	vector<string> string;
	printByModelToStringHelper(root, index, model, string);
	return string;
}

template<class bstdata>
void BST<bstdata>::printByModelToStringHelper(Node* root, int& index, string model, vector<string> &string) {
	if (root == NULL)
		return;
	else {
		printByModelToStringHelper(root->left, index, model, string);
		if (root->data.getModel() == model) {
			stringstream ss;
			ss << index++ << "," << root->data.toString();
			string.push_back(ss.str());
		}
		printByModelToStringHelper(root->right, index, model, string);
	}
}

#endif /* BST_H_ */




#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <iostream>
#include <string>

using namespace std;

class Order;
class Customer: public User {
private:
	string address;
	string city;
	unsigned zip;
	string email;
	subOrder sub;
	Order * r;	//store active order
	List<Order> orders; //store history order

public:
	Customer();
	Customer(string username, string password, string firstName,
			string lastName, bool isEmployee, string address, string city,
			unsigned zip, string email);

	string getAddress() const;
	string getCity() const;
	unsigned getZip() const;
	string getEmail() const;

	void setAddress(string address);
	void setCity(string city);
	void setZip(unsigned zip);
	void setEmail(string email);

	string displayCustomer(); //print all customers
	string getOrder() const;		//print list of orders
	//void insertOrder();

	bool operator==(const Customer& customer);
	bool operator<(const Customer& customer);
	bool operator>(const Customer& customer);

	string toString();	//return customer's info without
						//order information

	void read(ifstream& in);	//read data from file
	void write(ostream& out);	//write data to file

	friend ostream& operator<<(ostream& out, const Customer& customer);
	void activeOrder(Order *p);	//pass in orders to the cart.
	string printActive();//return active order detail (Order's printDeTailed() )
	void placeOrder(int i);		//place order
	void addToProduct(Product* p);	//add product to the active Order
	void removeProduct(int index);//remove product from cart if order not placed.
};

#endif /* CUSTOMER_H_ */


/*
 * Employee.h
 * Vu Pham
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>
#include <string>


using namespace std;

class Employee : public User {
public:
	Employee();
	Employee(string username, string password, string firstName, string lastName, bool isEmployee);

	//check firstname -> lastname -> username -> password
	bool operator==(const Employee& employee);
	bool operator<(const Employee& employee);
	bool operator>(const Employee& employee);

	void read(ifstream& in);		//read data from file
	void write(ostream& out);	//write data to file

	friend ostream& operator<<(ostream& out, const Employee& employee);

	//to-String method
	string toString() const;
};



#endif /* EMPLOYEE_H_ */


//
//  FileLoader.h
//  
//
//  Created by Alex Rao on 6/10/18.
//

#ifndef FileLoader_h
#define FileLoader_h
#include <stdio.h>
#include <fstream>

using namespace std;
class FileLoader{
private:
    
public:
    static BST<Product> loadProducts(string path);
    static BST<Customer> loadCustomers(string path);
    static BST<Employee> loadEmployees(string path);
};

#endif /* FileLoader_h */


/*
 * HashTable.h
 * Tin Nguyen
 */


#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include <iostream>

using namespace std;

template <class htdata>
class HashTable {
public:
    /**Constructors*/

    HashTable(){}
    //constructor

    ~HashTable(){}
    //destructor


    /**Access Functions*/

    int hash(string key) const;





    void insert(htdata& c);

    void displayByLastname(ostream& out, string lastname) ;
    void displayByFirstname(ostream& out, string firstname);
    void displayCustomer(ostream& out);

private:
    static const int SIZE = 100;
    List<htdata*> Table[SIZE];
};

template<class htdata>
int HashTable<htdata>:: hash(string key) const {
	string temp;
		int index, sum = 0;
		for (int i = 0; i < key.length(); i++){
			sum += (int) key[i]; //summing the ASCII values for each character in the stringindex = sum % SIZE; //dividing the summed ASCII values by TABLE_SIZE//and storing remainder as my indexreturn index;}
	}
	index= sum % SIZE;
	return index;
}

template<class htdata>
void HashTable<htdata>::insert(htdata& c) {
	int index = hash (c.getFirstname()+ c.getLastname());
	Table[index].insertStop (&c);

}





template <class htdata>
void HashTable<htdata>::displayCustomer(ostream& out) {
	for (int i =0; i< SIZE; i++){
		Table[i].startIterator();
		while(!Table[i].offEnd()){
			out << *(Table[i].getIterator());
			Table[i].moveIterNext();
		}
	}
}

template <class htdata>
void HashTable<htdata>::displayByFirstname(ostream& out, string firstname) {
	for (int i =0; i< SIZE; i++){
		Table[i].startIterator();
		for (int j=0; j <Table[i].getLength(); j++){
			if(Table[i].getIterator()->getFirstname() == firstname){
				out << *(Table[i].getIterator());
			}
			Table[i].moveIterNext();
		}
	}
	cout << "Customer not found";
}


template <class htdata>
void HashTable<htdata>::displayByLastname(ostream& out, string lastname) {
	for (int i =0; i< SIZE; i++){
		Table[i].startIterator();
		for (int j=0; j <Table[i].getLength(); j++){
			if(Table[i].getIterator()->getLastname() == lastname){
				out << *(Table[i].getIterator());
			}
			Table[i].moveIterNext();
		}
	}
	cout << "Customer not found" ;
}

#endif /* HASHTABLE_H_ */


/*
 * Heap.h
 * Andrew Maxwell
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <vector>
#include <iostream>
using namespace std;

class Heap {
private:
    int heap_size;
    vector<Order*> *heap;
    bool heaped;

    /**Helper Functions*/

    void heapify(int i);
    //helper function to build_heap, remove, and sort
    //bubbles an element down to its proper location within the heap

    void heap_increase_key(int i, Order * key);
    //helper funciton to insert
    //bubbles an element up to its proper location

    void remove(int index);
    //removes the node at the provided index of the heap
    //pre: 1 <= i <= get_size()
    //Called as a helper function to clear();

public:

    /**Constructors*/

    Heap();

    /**Manipulation Procedures*/

    void sort();	//heap sorts.

    void build_heap();
    //Takes an unordered vector and builds it into a heap
    //Called as a helper function of the constructor
    //Calls heapify as a helper function

    void buildHeap();
    //calls build_heap

    void place(Order * o, int days);
    //Inserts a new value onto the end of the heap and
    //Bubbles it up to the correct location in the heap
    //Calls heap_increase_key as a helper function

    void insert(Order * o);
    //Same as place, only doesn't mark the order as placed.
    //Useful for loading placed orders from a file.

    void ship(int index);
    //removes the node at the provided index of the heap
    //pre: 1 <= index <= get_size()

    void clear();
    //removes shipped orders
    //pre: heaped

    /**Access Functions*/

    Order * get_max() const;
    //returns the maximum value in the heap
    //pre: heap_size > 0

    Order * get_parent(int i) const;
    //returns the location (index) of the element stored at index i
    //pre: 0 < i <= heap_size

    Order * get_left(int i)  const;
    //returns the location (index) of the left child of the element stored at i
    //pre: 0 < i <= heap_size

    Order * get_right(int i)  const;
    //returns the location (index) of the right child of the element stored at i
    //pre: 0 < i <= heap_size

    int get_size() const;
    //returns the heap_size (current number of elements

    Order * get_element(int i) const;
    //returns the element at the specified index i
    //pre: 0 < i <= heap_size

    bool isHeaped() const;

    /**Additional Operations*/

    void printRaw(ostream& out) const;
    //prints the heap in level order. USED FOR DEBUGGING ONLY.

    string printSpecific(int index);

    string printSorted();
    //prints the heap as a list of orders, highest priority first.
    //Pre: !heaped


};

#endif /* HEAP_H_ */


/*
 * Order.h
 * Andrew Maxwell
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <ctime>
using namespace std;

class Customer;

class Order {
	
private:
	Customer * customer;
	List<subOrder> laptops;
	int shippingSpeed;
	time_t timePlaced, arriveBy;
	bool placed, shipped;
	float price;
	
public:
	
	/** constructors */

	Order();

	Order(Customer * customer);

	Order(istream &in, BST <Product> &products, Customer * customer);

	/** getters */

	string getArriveBy() const;
	//returns the date that the order should arrive, determined based on day order is placed and shipping speed

	string getDayPlaced() const;
	//returns the date the order was placed

	int getShippingSpeed() const;
	//returns the shipping speed

	float getPrice() const;
	//returns the total price of all of the items.

	bool isPlaced() const;
	//returns whether the order has been placed or not

	bool isShipped() const;
	//returns whether the order has been shipped. If the order has been shipped, no further modification is allowed.
	bool isDelivered() const;

	/** setters */

	void ship();
	//sets the order to shipped. Should only be called by Heap, not manually.

	void addLaptop(Product * newLaptop);
	//Adds a new laptop. If laptop matches existing laptop, increment by 1. Changes price of order.
	//Pre: !isShipped
	
	void addLaptop(string laptopKey);

	void removeLaptop(int index);
	//removes a laptop from the list, by index. Changes price of order.
	//Pre: !isShipped
	//Pre: Index < length of list
	//(check for these before calling the function, so that you can display a user-friendly error message)

	void setQuantity(int index, int quant);
	//changes the quantity variable for laptop at index. If quantity is 0, removes laptop.

	void placeOrder(int daysToShip);
	//places the order; sets it as ready to ship. Should only be called by Heap, not manually.

	bool operator>(const Order&);
	//Compares orders based on when they need to ship. Used for priority queue.

	bool operator<(const Order&);

	bool operator>=(const Order&);

	bool operator<=(const Order&);

	string print();

	string printDetailed();

	void save(ostream & out);

	Order * load(istream & in, BST<Product> & products);
};


#endif /* ORDER_H_ */


/*
 * Window.h
 *  Created on: Jun 2, 2018
 *      Author: Jasper
 */
#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <gtk/gtk.h>
#include <vector>
#include <map>
#include <cstddef> //for NULL


//class Heap;

class WindowManager; //forward class declaration

using namespace std;

class Window {
	
protected:
	string title;
	GtkWidget* self_window;
	GtkWidget* self_box;
	GtkWidget* pbar;
	static map<string, GtkWidget*> entries;
	static GdkPixbuf* icon;
	static Heap* priority_queue;
	static BST<Customer>* customers;
	static BST<Product>* products;
	static BST<ProductS>* products_secondary;
	//static Customer customer;
	//static HashTable* employees;

public:
	Window();
	
	Window(string xml);
	
	~Window();
	
	static void button_pressed(GtkWidget *widget, gpointer data);

	//called when close window red button is pressed at app level
	static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);

	//called from regular buttons
	static void destroy(GtkWidget* widget, gpointer data);

	void increase_pbar();

	static void set_icon(string path);

	static void assign_pointers(Heap* heap, BST<Customer>* _customers, BST<Product>* _products, BST<ProductS>* _products_secondary);

	void create_content(string tagName, string text, map<string,string> optionsMap, GtkWidget* box);

	static string create_xml_tag(string tag, string text);

	static string create_xml_tag(string tag, string options, string text);

	static void create_db_list_xml(vector<string> productsV, string &xml, string link, string name, string text);

	static void create_db_list_xml(vector<string> productsV, string &xml);

	static void string_find_and_replace(string find, string replace, string &subject);

	static vector<string> string_split(const string &input, char delim);

	static string to_lower(string str);

	static string vector_join(const vector<string> &v, const char* const delim);

};


#endif /* WINDOW_H_ */



/*
 * WindowManager.h
 *
 *  Created on: Jun 2, 2018
 *      Author: Jasper
 */

#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_


#include <vector>
#include <string>
#include <iostream>
#include <map> //for maps
#include <gtk/gtk.h>

class Window; //forward class declaration


using namespace std;

class WindowManager {

private:
	static map<string, string> windows;
	static Window* current_window;
	static string current_window_id;

public:
	WindowManager();
	~WindowManager();

	static void go_to_window(string id, string options);
	static void loadxml(string path);
	static string getxml(string id);
	static string get_current_window_id();
	static map<string, GtkWidget*> get_current_window_entries();
	static void run_pbar();
};


#endif /* WINDOWMANAGER_H_ */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Order;
Customer::Customer() {
	username = "";
	password = "";
	firstname = "";
	lastname = "";
	isEmployee = false;
	address = "";
	city = "";
	zip = 0;
	email = "";
	r = NULL;
}

Customer::Customer(string username, string password, string firstName,
		string lastName, bool isEmployee, string address, string city,
		unsigned zip, string email) {
	this->username = username;
	this->password = password;
	this->firstname = firstName;
	this->lastname = lastName;
	this->isEmployee = isEmployee;
	this->address = address;
	this->city = city;
	this->zip = zip;
	this->email = email;
	r = NULL;
}

string Customer::getAddress() const {
	return address;
}

string Customer::getCity() const {
	return city;
}

unsigned Customer::getZip() const {
	return zip;
}

string Customer::getEmail() const {
	return email;
}

void Customer::setAddress(string address) {
	this->address = address;
}

void Customer::setCity(string city) {
	this->city = city;
}

void Customer::setZip(unsigned zip) {
	this->zip = zip;
}

void Customer::setEmail(string email) {
	this->email = email;
}

string Customer::getOrder() const {
	stringstream out;
	orders.displayNumberedList(out);
	return out.str();
}
/*
 void Customer::insertOrder() { //storing list of past order (Shipped);
 if (r->isPlaced()) {
 orders.insertStop(*r);
 }

 Order r;
 r.addLaptop(p);
 orders.insertStop(r);
 }
 */

bool Customer::operator==(const Customer& customer) {
	return (username == customer.username);
}

bool Customer::operator<(const Customer& customer) {
	if (firstname < customer.firstname)
		return true;
	else if (firstname == customer.firstname) {
		if (lastname < customer.lastname)
			return true;
		else if (lastname == customer.lastname) {
			if (username < customer.username)
				return true;
			else if (username == customer.username) {
				if (password < customer.password)
					return true;
				else
					return false;
			} else
				return false;
		} else
			return false;
	} else
		return false;
}

bool Customer::operator>(const Customer& customer) {
	if (firstname > customer.firstname)
		return true;
	else if (firstname == customer.firstname) {
		if (lastname > customer.lastname)
			return true;
		else if (lastname == customer.lastname) {
			if (username > customer.username)
				return true;
			else if (username == customer.username) {
				if (password > customer.password)
					return true;
				else
					return false;
			} else
				return false;
		} else
			return false;
	} else
		return false;
}

void Customer::read(ifstream& in) {
	string temp;
	bool temp1;
	unsigned temp2;

	in >> temp;
	username = temp;
	in >> temp;
	password = temp;
	in >> temp;
	firstname = temp;
	in >> temp;
	lastname = temp;
	in >> temp1;
	isEmployee = temp1;
	getline(in, temp);
	address = temp;
	in >> temp;
	city = temp;
	in >> temp2;
	zip = temp2;
	in >> temp;
	email = temp;

	while (in.peek() == '\n')
		in.get();
}

void Customer::write(ostream& out) {
	out << username << '\n';
	out << password << '\n';
	out << firstname << '\n';
	out << lastname << '\n';
	out << isEmployee << '\n';
	out << address << '\n';
	out << city << '\n';
	out << zip << '\n';
	out << email << '\n';
	orders.startIterator();
	while (!orders.offEnd()) {
		out << orders.getIterator().getPrice() << endl;
		out << orders.getIterator().isPlaced() << endl;
		out << orders.getIterator().getDayPlaced() << endl;
		out << orders.getIterator().getShippingSpeed() << endl;
		out << orders.getIterator().isShipped() << endl;
		orders.moveIterNext();
	}
	out << "End";
}

ostream& operator<<(ostream& out, const Customer& customer) {
	stringstream os;
	customer.orders.displayNumberedList(os);
//out << customer.r->printDetailed();
	out << customer.getFirstname() << "," << customer.getLastname() << ","
			<< customer.getAddress() << "," << customer.getCity() << ","
			<< customer.getEmail() << "," << customer.getZip() << '\n';
	out << os.str();
	return out;
}

string Customer::toString() { //return a string with customer's data.
	stringstream ss;
	ss << firstname << "," << lastname << "," << address << "," << city << ","
			<< zip << "," << email;
	return ss.str();
}

string Customer::displayCustomer() {
	stringstream out;
	out << "\nFirst name: " << firstname << "\nLast name: " << lastname
			<< "\nAddress:  " << address << endl;
	return out.str();
}

void Customer::activeOrder(Order *p) {

	r = p; 	//point activeORder to the order passed in.
}

string Customer::printActive() {
	stringstream out;
	out << "Active Order: " << r->printDetailed();
	return out.str();
}

void Customer::addToProduct(Product* p) {
	r->addLaptop(p);

}

void Customer::removeProduct(int index) {
	assert(r->isPlaced());
	if (!r->isPlaced()) {
		r->removeLaptop(index - 1);
	}
}

void Customer::placeOrder(int i) {
	r->placeOrder(i);
	if (r->isPlaced()) {
		orders.insertStop(*r);
	}
}



/*
 * Employee.cpp
 * Vu Pham
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

Employee::Employee() {
	username = "";
	password = "";
	firstname = "";
	lastname = "";
	isEmployee = true;
}

Employee::Employee(string username, string password, string firstName, string lastName, bool isEmployee) {
	this->username = username;
	this->password = password;
	this->firstname = firstname;
	this->lastname = lastname;
	this->isEmployee = isEmployee;
}

bool Employee::operator==(const Employee& employee) {
	return (username == employee.username);
}

bool Employee::operator<(const Employee& employee) {
	if (firstname < employee.firstname)
		return true;
	else if (firstname == employee.firstname) {
		if (lastname < employee.lastname)
			return true;
		else if (lastname == employee.lastname) {
			if (username < employee.username)
				return true;
			else if (username == employee.username) {
				if (password < employee.password)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool Employee::operator>(const Employee& employee) {
	if (firstname > employee.firstname)
		return true;
	else if (firstname == employee.firstname) {
		if (lastname > employee.lastname)
			return true;
		else if (lastname == employee.lastname) {
			if (username > employee.username)
				return true;
			else if (username == employee.username) {
				if (password > employee.password)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

void Employee::read(ifstream& in) {
	string temp;
	bool temp1;

	in >> temp;
	username = temp;
	in >> temp;
	password = temp;
	in >> temp;
	firstname = temp;
	in >> temp;
	lastname = temp;
	in >> temp1;
	isEmployee = temp1;

	while (in.peek() == '\n')
		in.get();
}

void Employee::write(ostream& out) {
	out << username << '\n';
	out << password << '\n';
	out << firstname << '\n';
	out << lastname << '\n';
	out << isEmployee << '\n' << '\n';
}

ostream& operator<<(ostream& out, const Employee& employee) {
	out << left << setw(15) << employee.firstname << employee.lastname << "\n";
	return out;
}

string Employee::toString() const {
	stringstream ss;
	ss << username << "," << password << "," << firstname << "," << lastname;
	return ss.str();
}


//
//  FileLoader.cpp
//  
//
//  Created by Alex Rao on 6/10/18.
//

#include <iostream>
using namespace std;

BST<Product> FileLoader::loadProducts(string path){

	cout << "loading products..." << endl;

    BST<Product> products;
    ifstream fis(path.c_str());
    string line;
    if (fis.is_open()) {
        while (getline(fis, line)) {
            string manf_company = line;
            string model;
            getline(fis, model);
            double screen_size;
            fis >> screen_size;
            getline(fis, line); //advance to the next line
            unsigned cpuGen;
            fis >> cpuGen;
            getline(fis, line); //advance to the next line
            unsigned year;
            fis >> year;
            getline(fis, line); //advance to the next line
            unsigned price;
            fis >> price;
            getline(fis, line); //advance to the next line

            Product p(manf_company,model,screen_size,cpuGen,year,price);
            products.insert(p);

            getline(fis, line); //skip the emtpy line

        }
    }
    fis.close();
    return products;
}

BST<Customer> FileLoader::loadCustomers(string path) {

	cout << "loading customers..." << endl;

	BST<Customer> customers;
	ifstream fis(path.c_str());
	if (fis.is_open()) {
		while(fis.peek() != ios_base::end) {
			Customer c;
			c.read(fis);
			customers.insert(c);
		}
	}
	fis.close();
	return customers;
}

BST<Employee> FileLoader::loadEmployees(string path) {

	cout << "loading employees..." << endl;

	BST<Employee> employees;
	ifstream fis(path.c_str());
	if (fis.is_open()) {
		while(fis.peek() != ios_base::end) {
			Employee e;
			e.read(fis);
			employees.insert(e);
		}
	}
	fis.close();
	return employees;
}


/*
 * Heap.cpp
 * Andrew Maxwell
 */

#include <vector>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <sstream>

using namespace std;

bool DEBUG = false;

    /**Helper Functions*/

    void Heap::heapify(int i) {
        int l = i * 2;
        int r = i * 2 + 1;
        int greatest = i;
    	if (l <= heap_size and *(heap -> at(l)) > *(heap -> at(greatest))) {
    		greatest = l;
    	}
    	if (r <= heap_size and *(heap -> at(r)) > *(heap -> at(greatest))) {
    		greatest = r;
    	}
        if (greatest != i) {
        	Order * swap = heap -> at(greatest);
        	heap -> at(greatest) = heap -> at(i);
        	heap -> at(i) = swap;
        	heapify(greatest);
        }
    }
    //helper function to build_heap, remove, and sort
    //bubbles an element down to its proper location within the heap

    void Heap::heap_increase_key(int i, Order * key) {
    	assert(heaped);
    	if (*(heap -> at(floor(i/2))) < *key) {
    		heap -> at(i) = heap -> at(floor(i/2));
    		heap -> at(floor(i/2)) = key;
    		heap_increase_key(floor(i/2), key);
    	}
    }
    //helper function to insert
    //bubbles an element up to its proper location

    void Heap::remove(int index) {
    	assert(heaped);
    	assert(1 <= index);
    	assert(index <= heap_size);
    	heap -> at(index) = heap -> at(heap_size);
    	heap -> pop_back();
    	heap_size--;
    	heapify(index);
    }

    /**Constructors*/

    Heap::Heap() {
    	heap_size = 0;
    	heap = new vector<Order *>;
    	Order* placeHolder = new Order;
    	heap -> push_back(placeHolder);
    	heaped = true;
    }
    //Constructor for a new heap

    /**Manipulation Procedures*/

    void Heap::sort() {				//sorts (de-heaps) the vector.
    	if (heaped) {
    		int realLength = heap_size;
    		while (heap_size > 1) {
    			if (DEBUG) {
    				cout << "\ninitially\n";
    				printRaw(cout);
    			}
    			Order * swap = heap -> at(1);
    			heap -> at(1) = heap -> at(heap_size);
    			heap -> at(heap_size) = swap;
    			if (DEBUG) {
    				cout << "\nafter swapping\n";
    				printRaw(cout);
    			}
    			heap_size--;
    			heapify(1);
    			if (DEBUG) {
    				cout << "\nafter decreasing length and heapify\n";
    				printRaw(cout);
    			}
    		}
    		heap_size = realLength;
    		heaped = false;
    	}
    }

    void Heap::build_heap() {
        for (int i = heap_size/2; i > 0; i--) {
            heapify(i);
        }
        heaped = true;
    }
    //Builds the heap
    //Called as a helper function of the constructor
    //Calls heapify as a helper function

    void Heap::buildHeap() {
    	build_heap();
    }

    void Heap::place(Order * o, int days) {
    	assert(heaped);
    	if (o == NULL) {
    		return;
    	}
    	assert (!o -> isShipped());
    	assert (!o -> isPlaced());
    	o -> placeOrder(days);
    	heap -> push_back(o);
    	heap_size++;
    	heap_increase_key(heap_size, o);
    }
    //Places an order while simultaneously putting it on the heap

    void Heap::insert(Order * o) {
    	assert(heaped);
    	if (o == NULL) {
    		return;
    	}
    	assert (!o -> isShipped());
    	assert (o -> isPlaced());
    	heap -> push_back(o);
    	heap_size++;
    	heap_increase_key(heap_size, o);
    }

    void Heap::ship(int index) {
    	assert(!heaped);
    	assert(1 <= index);
    	assert(index <= heap_size);
    	heap -> at(heap_size - index + 1) -> ship();
    }
    //Ships an order and removes it from the heap.

    void Heap::clear() {	//Removes the shipped orders. pre: is a heap.
    	assert(heaped);
    	while (heap -> at(heap_size) -> isShipped()) {	//Remove all shipped orders at the end of the vector manually so that they don't get swapped with other shipped orders by the remove function and then not get removed.
    		heap -> pop_back();
    		heap_size--;
    	}
    	for (int i = 1; i <= heap_size; i++) {
    		if (heap -> at(i) -> isShipped()) {
    			remove(i);
    		}
    	}
    }

    /**Access Functions*/

    Order * Heap::get_max() const {
    	assert(heaped);
        assert(heap_size > 0);
        return heap -> at(1);
    }
    //returns the maximum value in the heap
    //pre: heap_size > 0

    Order * Heap::get_parent(int i) const {
    	assert(heaped);
        assert(0 < i);
        assert(i <= heap_size);
        return heap -> at(floor(i/2));
    }
    //returns the location (index) of the element stored at index i
    //pre: 0 < i <= heap_size

     Order * Heap::get_left(int i)  const {
    	assert(heaped);
        assert(0 < i);
        assert(i <= heap_size);
        return heap -> at(i * 2);
    }
    //returns the location (index) of the left child of the element stored at i
    //pre: 0 < i <= heap_size

    Order * Heap::get_right(int i)  const {
    	assert(heaped);
        assert(0 < i);
        assert(i <= heap_size);
        return heap -> at((i * 2) + 1);

    }
    //returns the location (index) of the right child of the element stored at i
    //pre: 0 < i <= heap_size

    int Heap::get_size() const {
        return heap_size;
    }

    Order * Heap::get_element(int i) const {
        assert(0 < i);
        assert(i <= heap_size);
        return heap -> at(i);
    }
    //returns the element at the specified index i
    //pre: 0 < i <= heap_size

    bool Heap::isHeaped() const {
    	return heaped;
    }

    /**Additional Operations*/

    void Heap::printRaw(ostream& out) const {	//prints all of the orders for debugging without sorting.
        for (int i = 0; i <= heap_size; i++) {
            out << "#" << i << " " << heap -> at(i) -> print() << endl;
        }
    }

    string Heap::printSpecific(int index) {	//Prints the order at the given index in the sorted vector
    	assert(!heaped);
    	assert(1 <= index);
    	assert(index <= heap_size);
    	return heap -> at(heap_size - index + 1) -> printDetailed();
    }

    string Heap::printSorted() {			//Prints all of the orders in sorted order. Pre: must be sorted (!heaped).
    	assert(!heaped);
    	stringstream out;
    	if (heap_size == 0) {
    		out << "No orders to ship!\n";
    	} else {
    		out << "Unshipped orders:\n";
        	for (int i = heap_size; i >= 1; i--) {
            	out << (*heap)[i] -> print() << endl;
        	}
    	}
    	heaped = false;
    	return out.str();
    }
    //prints each element in the array (heap) on a different line


/*
 * Main.cpp
 * Mohamed Elgharbawy
 */

#include <iostream>

#include <gtk/gtk.h>

using namespace std;


int main(int argc, char *argv[]) {


	gtk_init (&argc, &argv);

	g_print("args passed to gtk_init\n");

	BST<Product> bstp;
	bstp.loadPrimary("Products_in.txt");
	BST<ProductS> bsts;
	bsts.loadSecondary("Products_in.txt");
	Product product;
	ProductS productS;
	Heap heap;
	Customer customer;
	Employee employee;

	cout << "Success!" << endl;


	Window::assign_pointers(NULL,NULL,&bstp,&bsts);
	WindowManager::loadxml("window_data.xml");
	WindowManager::go_to_window("welcome_screen","");

	g_print("going to gtk_main\n");

	gtk_main();

	g_print("gtk_main has ended\n");



	return 0;
}


/*
 * Order.cpp
 * Andrew Maxwell
 */

#include <assert.h>
#include <iomanip>
#include <sstream>
using namespace std;

	/** constructors */

	Order::Order() {
		shippingSpeed = price = 0;
		placed = shipped = false;
		timePlaced = arriveBy = 0;
		customer = NULL;
	}

	Order::Order(Customer * owner) {
		shippingSpeed = price = 0;
		placed = shipped = false;
		timePlaced = arriveBy = 0;
		customer = owner;
	}

	Order::Order(istream &in, BST<Product> &products, Customer * owner) {
		load(in, products);
		customer = owner;
	}

	/** management functions - getters and setters*/

	string Order::getArriveBy() const {
		tm * arriveByTm = localtime(&arriveBy);
		char * timeString = new char[25];
		strftime(timeString, 25, "%A %B %d", arriveByTm);
		return timeString;
	}
	//returns the date that the order should arrive, determined based on day order is placed and shipping speed, as a string

	string Order::getDayPlaced() const {
		tm * timePlacedtm = localtime(&timePlaced);
		char * timeString = new char[25];
		strftime(timeString, 25, "%A %B %d", timePlacedtm);
		return timeString;
	}
	//returns the date the order was placed as a string

	int Order::getShippingSpeed() const {
		return shippingSpeed;
	}
	//returns the shipping speed

	float Order::getPrice() const {
		return price;
	}

	bool Order::isPlaced() const {
		return placed;
	}
	//returns whether the order has been placed or not

	bool Order::isShipped() const {
		return shipped;
	}
	//returns whether the order has been shipped. If the order has been shipped, no further modification is allowed.

	bool Order::isDelivered() const {
		return (shipped and (time(NULL) > arriveBy));
	}

	void Order::ship() {
		shipped = true;
	}
	//sets the order to shipped.

	void Order::addLaptop(Product * newLaptop) {
		assert(!placed);
		subOrder newLT(newLaptop);
		int index = laptops.linearSearch(newLT);
		if (index > -1) {
			laptops.moveToIndex(index);
			setQuantity(index - 1, laptops.getIterator().getQuantity() + 1);
		} else {
			laptops.insertStop(newLT);
			price += newLT.price;
		}
	}
	//Adds a new laptop. If laptop matches existing laptop, increment by 1.
	//Pre: !placed

	void Order::removeLaptop(int index) {
		assert(!placed);
		assert(index < laptops.getLength());
		laptops.moveToIndex(index);
		price -= laptops.getIterator().price;
		laptops.removeIterator();
	}
	//removes a laptop from the list, by index
	//Pre: !Placed
	//Pre: Index < length of list
	//(check for these before calling the function, so that you can display a user-friendly error message without crashing the program)

	void Order::setQuantity(int index, int quant) {
		assert(!placed);
		assert(quant >= 0);
		assert(index < laptops.getLength());
		laptops.moveToIndex(index);
		price -= laptops.getIterator().price;
		if (quant > 0) {
			subOrder tempSO = laptops.getIterator();
			tempSO.setQuantity(quant);
			price += tempSO.price;
			laptops.insertIterator(tempSO);
		}
		laptops.removeIterator();
	}
	//Pre: !Placed
	//Pre: Index < length of list
	//Pre: Quantity is positive or 0
	//changes the quantity variable for laptop at index + updates the price

	void Order::placeOrder(int daysToShip) {
		assert(!laptops.isEmpty());
		timePlaced = time(NULL);
		arriveBy = timePlaced;
		arriveBy += 86400 * daysToShip;
		shippingSpeed = daysToShip;
		placed = true;
	}
	//places the order; sets it as ready to ship; sets value of timePlaced and arriveBy.

	bool Order::operator>(const Order& order) {

		if (!shipped and order.shipped) {
			return true;
		}
		else if ((!shipped and !order.shipped) and arriveBy/86400 < order.arriveBy/86400) {
			return true;
		} else {
			return false;
		}
	}
	//returns true if the first order is higher priority. That is, compares priority; item on left is greater priority.

	bool Order::operator<(const Order& order) {
		if (shipped and !order.shipped) {
			return true;
		}
		else if ((!shipped and !order.shipped) and arriveBy/86400 > order.arriveBy/86400) {
			return true;
		} else {
			return false;
		}
	}

	bool Order::operator>=(const Order& order) {
		if (order.shipped) {
			return true;
		} else if (shipped and !order.shipped) {
			return false;
		} else {
			return(arriveBy/86400 >= order.arriveBy/86400);
		}
	}

	bool Order::operator<=(const Order& order) {
		if (shipped) {
			return true;
		} else if (!shipped and order.shipped) {
			return false;
		} else {
			return(arriveBy/86400 <= order.arriveBy/86400);
		}
	}

	string Order::print() {	//Prints basic information about the order, including where to ship, etc.
		stringstream out;
		out << fixed << setprecision(2) << price;
		if (placed) {
			out << "," << getArriveBy() << ",";
			if (shipped) {
				if (isDelivered()) {
					out << "Delivered";
				} else {
					out << "En route";
				}
			} else {
				out << "Waiting to be shipped";
			}
		} else {
			out << ",N/A,Not Yet Placed";
		}
		return out.str();
	}

	string Order::printDetailed() {	//Prints above information + also the list of all laptops.
		stringstream out;
		out << print();
		out << "\n" << *customer;
		laptops.displayNumberedList(out);
		out << endl << endl;
		return out.str();
	}

	void Order::save(ostream & out) {	//Prints out all information in format for load() to read
		out << shippingSpeed << "\t";
		out << price << "\t";
		out << placed << "\t";
		out << shipped << "\t";
		out << timePlaced << "\t";
		out << arriveBy << endl;
		laptops.startIterator();
		while (!laptops.offEnd()) {
			out << laptops.getIterator().laptop -> getMake() << endl;
			out << laptops.getIterator().laptop -> getModel() << endl;
			out << laptops.getIterator().quantity << endl;
			laptops.moveIterNext();
		}
		out << "end" << endl;
	}

	Order * Order::load(istream & in, BST<Product> & products) {	//reads in information from an input.
		int quantity = 0;
		string make = "", model, input;
		getline(in, input);
		stringstream getValue(input);
		getValue >> shippingSpeed;
		getValue >> price;
		getValue >> placed;
		getValue >> shipped;
		getValue >> timePlaced;
		getValue >> arriveBy;
		getline(in, make);
		while (make != "end") {
			getline(in, model);
			Product dummyProduct(make, model, 0, 0, 0, 0);
			subOrder newSO (products.find(dummyProduct));
			getline(in, input);
			stringstream getInt(input);
			getInt >> quantity;
			newSO.setQuantity(quantity);
			laptops.insertStop(newSO);
			getline(in, make);
		}
		if (placed and !shipped) {
			return this;
		} else {
			return NULL;
		}

	}


/*
 * Product.cpp
 * Vu Pham
 */

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;


Product::Product() {
	make = "";
	model = "";
	screenSize = 0.0;
	cpuGen = 0;
	year = 0;
	price = 0;
}

Product::Product(string make, string model, double screenSize, unsigned cpuGen, unsigned year, double price) {
	this->make = make;
	this->model = model;
	this->screenSize = screenSize;
	this->cpuGen = cpuGen;
	this->year = year;
	this->price = price;
}

string Product::getMake() const {
	return make;
}

string Product::getModel() const {
	return model;
}

double Product::getScreenSize() const {
	return screenSize;
}

unsigned Product::getCpuGen() const {
	return cpuGen;
}

unsigned Product::getYear() const {
	return year;
}

double Product::getPrice() const {
	return price;
}

void Product::setMake(string make) {
	this->make = make;
}

void Product::setModel(string model) {
	this->model = model;
}

void Product::setScreenSize(double screenSize) {
	this->screenSize = screenSize;
}

void Product::setCpuGen(unsigned cpuGen) {
	this->cpuGen = cpuGen;
}

void Product::setYear(unsigned year) {
	this->year = year;
}

void Product::setPrice(double price) {
	this->price = price;
}

bool Product::operator==(const Product& product) {
	return (make == product.make && model == product.model);
}

bool Product::operator<(const Product& product) {
	if (make < product.make)
		return true;
	else if (make == product.make) {
		if (model < product.model)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Product::operator>(const Product& product) {
	if (make > product.make)
		return true;
	else if (make == product.make) {
		if (model > product.model)
			return true;
		else
			return false;
	}
	else
		return false;
}

ostream& operator<<(ostream& out, const Product& product) {
	out << left << setw(16) << product.make << setw(32) << product.model << setw(16)
			<< product.screenSize << setw(16) << product.cpuGen << setw(16) << product.year << product.price << "\n";
	return out;
}

void Product::print(ostream& out) const {
	out << make << '\n'
		<< model << '\n'
		<< screenSize << '\n'
		<< cpuGen << '\n'
		<< year << '\n'
		<< price << '\n';
}

string Product::toString() const {
	stringstream ss;
	ss << make << "," << model << "," << screenSize << "," << cpuGen << "," << year << "," << price;
	return ss.str();
}


/*
 * ProductS.cpp
 * Vu Pham
 */

#include <iostream>
using namespace std;

ProductS::ProductS() {
	make = "";
	model = "";
	screenSize = 0.0;
	cpuGen = 0;
	year = 0;
}

ProductS::ProductS(string make, string model, double screenSize, unsigned cpuGen, unsigned year, double price) {
	this->make = make;
	this->model = model;
	this->screenSize = screenSize;
	this->cpuGen = cpuGen;
	this->year = year;
	this->price = price;
}

void ProductS::operator=(const Product& product) {
	make = product.getMake();
	model = product.getModel();
	screenSize = product.getScreenSize();
	cpuGen = product.getCpuGen();
	year = product.getYear();
	price = product.getPrice();
}

bool ProductS::operator==(const ProductS& product) {
	return (model == product.model && make == product.make);
}

bool ProductS::operator<(const ProductS& product) {
	if (model < product.model)
		return true;
	else if (model == product.model) {
		if (make < product.make)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool ProductS::operator>(const ProductS& product) {
	if (model > product.model)
		return true;
	else if (model == product.model) {
		if (make > product.make)
			return true;
		else
			return false;
	}
	else
		return false;
}



/*
 * SubOrder.cpp
 *
 *  Created on: Jun 17, 2018
 *      Author: Andrew
 */


    subOrder::subOrder() {
		laptop = NULL;
		price = 0;
		quantity = 1;
	}
    subOrder::subOrder(Product * toBuy) {
		laptop = toBuy;
		price = toBuy->getPrice();
		quantity = 1;
	}
	void subOrder::setQuantity(int q) {
		quantity = q;
		price = laptop -> getPrice() * q;
	}
	int subOrder::getQuantity() {
		return quantity;
	}
	ostream & operator<<(ostream & out, const subOrder& SO) {
		out << SO.laptop -> getMake() << "," <<  SO.laptop -> getModel() << "," << SO.quantity;
		return out;
	}
	bool subOrder::operator==(const subOrder &rhs) {
		return (*laptop == *rhs.laptop);
	}





/*
 * User.h
 * Vu Pham
 */

#include <iostream>
#include <iomanip>
using namespace std;

User::User() {
	username = "";
	password = "";
	firstname = "";
	lastname = "";
	isEmployee = true;
}

string User::getUsername() const {
	return username;
}

string User::getPassword() const {
	return password;
}

string User::getFirstname() const {
	return firstname;
}

string User::getLastname() const {
	return lastname;
}

bool User::getIsEmployee() const {
	return isEmployee;
}

void User::setUsername(string username) {
	this->username = username;
}

void User::setPassword(string password) {
	this->password = password;
}

void User::setFirstname(string firstname) {
	this->firstname = firstname;
}

void User::setLastname(string lastname) {
	this->lastname = lastname;
}

void User::setIsEmployee(bool isEmployee) {
	this->isEmployee = isEmployee;
}




/*
 * Window.cpp
 *
 *  Created on: Jun 2, 2018
 *      Author: Jasper
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <locale>
#include <gtk/gtk.h>

using namespace std;


//static variables
GdkPixbuf* Window::icon;
map<string, GtkWidget*> Window::entries;
Heap* Window::priority_queue;
BST<Customer>* Window::customers;
BST<Product>* Window::products;
BST<ProductS>* Window::products_secondary;
//Customer customer;


Window::Window(string xml) {

    //create the window
    self_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(self_window, "delete-event", G_CALLBACK(delete_event), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(self_window), 10);
    
    //create box
    self_box = gtk_vbox_new(FALSE, 2);
    
    //set the box spacing
    gtk_box_set_spacing(GTK_BOX(self_box),3);

    //add the box to the window
    gtk_container_add(GTK_CONTAINER(self_window), self_box);
    
    //wipe the entries
    map<string, GtkWidget*> m;
    entries = m;
    
    //set up xml stringstream
    stringstream xmlss(xml);
    
    string tag, text, closetag = "";
    
    //create new vector of box pointers
	vector<GtkWidget*> boxes;
	boxes.push_back(self_box);
    
    while(getline(xmlss,tag)) {
        string msg;
        
        //get the tag
        tag = tag.substr(1, tag.length()-2); //get rid of the <>
        size_t pos = tag.find(" ");
        string tagName = tag.substr(0, pos); //get the tag name
        string options = tag.substr(pos+1); //get the options
        
        map<string,string> optionsMap;
        
        string optionpair;
        stringstream optionsSS(options);
        
        while(getline(optionsSS,optionpair,' ')) {//loop through the options, separated by spaces
            string attribute;
            string value;
            
            stringstream optsep(optionpair);
            
            getline(optsep, attribute, '\"'); //skip the options=
            attribute = attribute.substr(0,attribute.length()-1); //get rid of the '='
            getline(optsep,value,'\"'); //get the actual value
            
            optionsMap.insert(make_pair(attribute,value));
        }
        
        if(tagName == "variable") { //skip unassigned variable tag
            
            continue;
            
        } else if(tagName == "hbox") {// skip the line named box and assign inner box == true;

            //get homogeneous
            if(optionsMap["homogeneous"] == "true"){
                //create new box
                boxes.push_back(gtk_hbox_new(TRUE, 2));
            } else {
                //create new box
                boxes.push_back(gtk_hbox_new(FALSE, 2));
            }
            
            //set the box spacing
            gtk_box_set_spacing(GTK_BOX(boxes.at(boxes.size()-1)),3);
                       
            //restart the while loop
            continue;
            
        } else if (tagName == "vbox") {
            
            //get homogeneous
            if(optionsMap["homogeneous"] == "true"){
                //create new box
                boxes.push_back(gtk_vbox_new(TRUE, 2));
            } else {
                //create new box
                boxes.push_back(gtk_vbox_new(FALSE, 2));
            }

            //set the box spacing
            gtk_box_set_spacing(GTK_BOX(boxes.at(boxes.size()-1)),3);
            
            continue;
            
        } else if (tagName == "scroll") {
        	
        	//create the new scroll window
        	GtkWidget* scroll_window = gtk_scrolled_window_new(NULL,NULL);
        	boxes.push_back(scroll_window); //NULL,NULL for auto-generated scroll bars

        	if (optionsMap.find("columns") != optionsMap.end() && optionsMap.find("width") != optionsMap.end()) { //if the number of columns and the width is present
        		//set the scroll window size
        		int size = atoi(optionsMap["columns"].c_str()) * (atoi(optionsMap["width"].c_str())+4) + 15;
        		gtk_widget_set_size_request (scroll_window, size, 300);
        	} else {
        		// just make it big
        		gtk_widget_set_size_request (scroll_window, 1500, 300);
        	}

        	

        	//set the box border width
        	gtk_container_set_border_width (GTK_CONTAINER (boxes.at(boxes.size()-1)), 10);

        	//set the box policy
        	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (boxes.at(boxes.size()-1)), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);


        	continue;

        } else if (tagName == "hr") {

        	//make a horizontal separator
        	GtkWidget* hr = gtk_hseparator_new();

        	//pack it into the box
        	gtk_box_pack_start(GTK_BOX(boxes.at(boxes.size()-1)),hr,FALSE,FALSE,0);

        	//show the wdiget
        	gtk_widget_show(hr);

        	continue;

        } else if (tagName == "vr") {

        	//make a horizontal separator
        	GtkWidget* vr = gtk_vseparator_new();

        	//pack it into the box
        	gtk_box_pack_start(GTK_BOX(boxes.at(boxes.size()-1)),vr,FALSE,FALSE,0);

        	//show the wdiget
        	gtk_widget_show(vr);

        	continue;

        } else if(tagName == "/hbox" || tagName == "/vbox" || tagName == "/scroll") {

            string box_name = g_strconcat(G_OBJECT_TYPE_NAME(boxes.at(boxes.size()-2)),NULL);
        	string window_name = "GtkScrolledWindow";
        	if( box_name == window_name) {
            	//pack it into the scroll box
            	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (boxes.at(boxes.size()-2)), boxes.at(boxes.size()-1));
            } else {
            	//pack the box into the next higher box
            	gtk_box_pack_start(GTK_BOX(boxes.at(boxes.size()-2)),boxes.at(boxes.size()-1),FALSE,FALSE,0);
            }
            
            //show the box
            gtk_widget_show(boxes.at(boxes.size()-1));

            //remove the box from the box stack
            boxes.pop_back();

            continue;
        } 

        //end of elf


        getline(xmlss,text); //get the text
        getline(xmlss,closetag); //and the closetag
        
        if(boxes.size() > 1) {
            create_content(tagName,text,optionsMap,boxes.at(boxes.size()-1));
        } else {
            create_content(tagName,text,optionsMap,self_box);
        }
    } 

    //show the box
    gtk_widget_show(self_box);
    
    //align window in center
    gtk_window_set_position(GTK_WINDOW(self_window), GTK_WIN_POS_CENTER);
    
    //make the window deletable
    gtk_window_set_deletable(GTK_WINDOW(self_window), TRUE);
    
    //set the window icon
    gtk_window_set_icon(GTK_WINDOW(self_window), icon);
    
    //show the window
    gtk_widget_show(self_window);
    
    //make the window active
    //gtk_window_activate_focus(GTK_WINDOW(self_window));
}

Window::~Window() {
    // TODO Auto-generated destructor stub
}

void Window::create_content(string tagName, string text, map<string,string> optionsMap, GtkWidget* box) {
    string msg;
    GtkWidget* widget;

    if(tagName == "title") {
        
        //make the title lable
        widget = gtk_label_new(text.c_str());
        
        //set alignment
        gtk_misc_set_alignment(GTK_MISC(widget),0,0);
        
        //title markup
        char* markup = g_strconcat("<big>", text.c_str(), "</big>", NULL);
        gtk_label_set_markup(GTK_LABEL(widget), markup);
        g_free(markup);
        gtk_misc_set_alignment(GTK_MISC(widget), 0, 0);
        
    } else if(tagName == "button") {

        //create new button
        widget = gtk_button_new_with_label(text.c_str());
        //set name
        gtk_widget_set_name(widget,optionsMap["options"].c_str());
        
        //set signal connect method
        g_signal_connect(widget, "clicked", G_CALLBACK(button_pressed), FALSE);
        
        //connect it to the destroy event as well
        g_signal_connect_swapped(widget,"clicked",G_CALLBACK(destroy),self_window);

                
    } else if(tagName == "label") {

        //create new label
        widget = gtk_label_new(text.c_str());

        //make the text selectable just for funsies, ok maybe not
        //gtk_label_set_selectable (GTK_LABEL(widget), TRUE);

        //set styles
        if(optionsMap["style"] == "error"){
        	//error markup
        	char* markup = g_strconcat("<span foreground=\"red\">", text.c_str(), "</span>", NULL);
        	gtk_label_set_markup(GTK_LABEL(widget), markup);
        	g_free(markup);
        }

        if (optionsMap.find("width") != optionsMap.end()) {//if the size option is present


        	gtk_widget_set_size_request(widget,atoi(optionsMap["width"].c_str()),-1);
        	
        	gtk_label_set_line_wrap (GTK_LABEL(widget),TRUE);
        }

        if (optionsMap["justify"] == "center") {

        	gtk_label_set_justify(GTK_LABEL(widget),GTK_JUSTIFY_CENTER);

        	//set alignment
        	gtk_misc_set_padding(GTK_MISC(widget),atoi(optionsMap["width"].c_str())/2.0, 0);

        	//g_print("%s",g_strconcat("width is: ", to_string(atoi(optionsMap["width"].c_str())/2.0).c_str(),"\n",NULL));

        } else if (optionsMap["justify"] == "right") {

        	gtk_label_set_justify(GTK_LABEL(widget),GTK_JUSTIFY_RIGHT);
        } else {

        	//set alignment
        	gtk_misc_set_alignment(GTK_MISC(widget), 0, 0);
        }
        
       
        
    } else if (tagName == "entry") {
        
        //create new entry and assign it to the pointer
        widget = gtk_entry_new();
        
        //set the name
        gtk_widget_set_name(widget,text.c_str());
        
        //check if it's a password box
        if (optionsMap["type"] == "psw") {
            gtk_entry_set_visibility(GTK_ENTRY(widget),FALSE);
        } else if (optionsMap["type"] == "hidden"){
        	gtk_entry_set_text(GTK_ENTRY(widget),optionsMap["value"].c_str());
        }
        
        //adding entries to entries map
        entries.insert(make_pair(text,widget));
        
    } else if (tagName == "pbar") {
        
        msg = "creating pbar: " + text + "\n";
        g_print("%s",msg.c_str());
        
        widget = gtk_progress_bar_new();
        
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(widget),text.c_str());
        
    }

    string box_name = g_strconcat(G_OBJECT_TYPE_NAME(box),NULL);
	string window_name = "GtkScrolledWindow";
	if(box_name == window_name) {
    	//pack it into the scroll box
    	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (box), widget);
    } else {
    	//add widget to box
    	gtk_box_pack_start(GTK_BOX(box), widget, FALSE, FALSE, 0);
    }

    //set it to default if it is set to default
    if (optionsMap["default"] == "true"){

    	msg = "setting button \"" + text + "\" to be default\n";
    	g_print("%s",msg.c_str());

    	gtk_widget_set_can_default (widget, TRUE);
    	gtk_widget_grab_default (widget);
    }

    if(optionsMap["type"] == "hidden"){

    	//don't show the widget

    } else {
    	//show the widget
    	gtk_widget_show(widget);
    }
    
}

void Window::button_pressed(GtkWidget* widget, gpointer data) {
    
    string xml = "";
    
    string optionsRaw = gtk_widget_get_name(widget); //the options are stored in the button name
    stringstream optsep(optionsRaw); //now we need a string stream object to extract them
    map<string, string> optionsMap; //and a map to store them
    
    string optvalpair; //this will store the pairs of option:value
    
    while(getline(optsep,optvalpair,',')) { //loop through each comma separated option:value pair
        
        stringstream seperator(optvalpair); //another string stream object to separate the pair
        string option;
        string value;
        getline(seperator,option,':'); //get the option
        getline(seperator,value,':'); //get the value
        optionsMap.insert(make_pair(option,value)); //add them to the map
    }
    
    string name = optionsMap["name"];
    string msg;
    
    if(name == "quit") {
        
        gtk_main_quit();

    } else if(name == "customer_sign_in") {
        
        g_print("in customer_sign_in block\n");
        
        string email = gtk_entry_get_text(GTK_ENTRY(entries["email"]));
        string psw = gtk_entry_get_text(GTK_ENTRY(entries["psw"]));
        
        msg = "email: " + email + "\n";
        g_print("%s",msg.c_str());
        msg = "password: " + psw + "\n";
        g_print("%s",msg.c_str());
              
    } else if(name == "employee_login") {
        
        unsigned id = atoi(gtk_entry_get_text(GTK_ENTRY(entries["id"])));
        string psw = gtk_entry_get_text(GTK_ENTRY(entries["psw"]));
        
        msg = "id: " + to_string(id) + "\n";
        g_print("%s",msg.c_str());
        msg = "password: " + psw + "\n";
        g_print("%s",msg.c_str());
        
    } else if(name == "customer_create_new_account_1") {
        
        //get parameters
        string email = gtk_entry_get_text(GTK_ENTRY(entries["email"]));
        string conf_email = gtk_entry_get_text(GTK_ENTRY(entries["conf_email"]));
        string psw = gtk_entry_get_text(GTK_ENTRY(entries["psw"]));
        string conf_psw = gtk_entry_get_text(GTK_ENTRY(entries["conf_psw"]));
        
        //time to check
        if(email != conf_email || psw != conf_psw){
        	if(email != conf_email){
        		xml += create_xml_tag("label","style=\"error\"","error: emails must match");
        	}
        	if (psw != conf_psw){
        		xml += create_xml_tag("label","style=\"error\"","error: passwords must match");
        	}

        	WindowManager::go_to_window("customer_create_new_account",xml); //go back to the customer create new account window
        	return;

        } else if(email == "" || psw == ""){

        	xml += create_xml_tag("label","style=\"error\"","error: please do not leave any fields blank");

        	WindowManager::go_to_window("customer_create_new_account",xml); //go back to the customer create new account window
        	return;

        } else {
        	string value = email + "`" + psw; 
        	xml += create_xml_tag("entry","type=\"hidden\" value=\""+value+"\"","values");

        }
            
    } else if(name == "customer_create_new_account_2") {

    	map<string,string> values;

    	string email_and_psw = gtk_entry_get_text(GTK_ENTRY(entries["values"]));
    	size_t sep = email_and_psw.find('`'); //separate the email and the password
    	values["email"] = email_and_psw.substr(0,sep);
    	values["psw"] = email_and_psw.substr(sep+1);

    	values["fname"] = gtk_entry_get_text(GTK_ENTRY(entries["fname"]));
    	values["lname"] = gtk_entry_get_text(GTK_ENTRY(entries["lname"]));
    	values["address"] = gtk_entry_get_text(GTK_ENTRY(entries["address"]));
    	values["phone_num"] = gtk_entry_get_text(GTK_ENTRY(entries["phone_num"]));
    	values["city"] = gtk_entry_get_text(GTK_ENTRY(entries["city"]));
    	values["zip_str"] = gtk_entry_get_text(GTK_ENTRY(entries["zip"]));
    	unsigned zip = atoi(values["zip_str"].c_str());


    	map<string,string>::iterator it;

    	for(it = values.begin(); it != values.end(); it++){

    		msg = it->first + ": " + it->second + "\n";
    		g_print("%s",msg.c_str());
    	}


    	if(values["fname"] == "" || values["lname"] == "" || values["address"] == "" || values["phone_num"] == "" || values["city"] == "" || values["zip_str"] == ""){//if any of the fields are blank, reject
    		xml += create_xml_tag("label","style=\"error\"","error: please do not leave any fields blank");
    		string value = values["email"] + "`" + values["psw"]; 
    		xml += create_xml_tag("entry","type=\"hidden\" value=\""+value+"\"","values");

    		WindowManager::go_to_window("customer_create_new_account_cont",xml);
    		return;

    	} else {
    		//Customer c(email,psw,fname,lname,false,address,city,zip,email);
    		//customers->insert(c);
    	}

    } else if(name == "customer_search"){

    	string make = gtk_entry_get_text(GTK_ENTRY(entries["make"]));
        string model = gtk_entry_get_text(GTK_ENTRY(entries["model"]));

        if(make == "" && model == ""){
        	xml += create_xml_tag("label","style=\"error\"","Please enter the make and/or model you would like to search for.");
     		WindowManager::go_to_window("customer_search_for_a_product",xml);
     		return;
        } 



        vector<string> productsV = products->printListToString();
        vector<string> matches;

        if( make != "" && model == ""){ //if they just searched for make
        	xml += create_xml_tag("title","Search Results for \"" + make + "\":");
        	//loop through the products in the vector
        	for (int i = 0; i < productsV.size(); ++i) {
        		vector<string> p = string_split(productsV[i],','); //vector storing product information from vector of all products
        		if(to_lower(p[1]).find(to_lower(make)) != string::npos ){ //if the queried make is present in the current porduct
        			p.at(0) = to_string(matches.size()+1); //set the index
        			matches.push_back(vector_join(p,",")); //add the product to the vector of matches
        		}
        	}

        } else if( make == "" && model != ""){ //if they just searched for model
        	xml += create_xml_tag("title","Search Results for \"" + model + "\":");
        	//loop through the products in the vector
        	for (int i = 0; i < productsV.size(); ++i) {
        		vector<string> p = string_split(productsV[i],','); //vector storing product information from vector of all products
        		if(to_lower(p[2]).find(to_lower(model)) != string::npos ){ //if the queried make is present in the current porduct
        			p.at(0) = to_string(matches.size()+1); //set the index
        			matches.push_back(vector_join(p,",")); //add the product to the vector of matches
        		}
        	}

        } else if( make != "" && model != ""){ //if they search for both
        	xml += create_xml_tag("title","Search Results for \"" + make + " " + model + "\":");
        	//loop through the products in the vector
        	for (int i = 0; i < productsV.size(); ++i) {
        		vector<string> p = string_split(productsV[i],','); //vector storing product information from vector of all products
        		if(to_lower(p[1]).find(to_lower(make)) != string::npos && to_lower(p[2]).find(to_lower(model)) != string::npos ){ //if the queried make is present in the current porduct
        			p.at(0) = to_string(matches.size()+1); //set the index
        			matches.push_back(vector_join(p,",")); //add the product to the vector of matches
        		}
        	}

        }

        if(matches.size() == 0){

        	xml += create_xml_tag("label","No matches");
        } else {
        	xml += create_xml_tag("label","There are " + to_string(matches.size()) + " matches.");
        	create_db_list_xml(matches,xml,"customer_view_cart","add_to_cart","add to cart");
        }

    } else if(name == "customer_db_list"){
        
        string value = optionsMap["value"];
        
        if(value == "comp_name"){

            vector<string> productsV = products->printListToString();
            create_db_list_xml(productsV,xml,"customer_view_cart","add_to_cart","add to cart");
            
        } else if(value == "price"){
            
            
        } else if(value == "model"){
            
            vector<string> productsV = products_secondary->printListToString();
            create_db_list_xml(productsV,xml,"customer_view_cart","add_to_cart","add to cart");
        }
        
    } else if(name == "add_to_cart"){

        //do a bunch of stuff

    } else if(name == "ship"){

        //ship(index)

    } else if (name == "employee_add_product") {
    	gtk_entry_get_text(GTK_ENTRY(entries["email"]));

    	string make = gtk_entry_get_text(GTK_ENTRY(entries["make"]));
    	string model = gtk_entry_get_text(GTK_ENTRY(entries["model"]));
    	string screenSize = gtk_entry_get_text(GTK_ENTRY(entries["screenSize"]));
    	string cpuGen = gtk_entry_get_text(GTK_ENTRY(entries["cpuGen"]));
    	string year = gtk_entry_get_text(GTK_ENTRY(entries["year"]));
    	string price = gtk_entry_get_text(GTK_ENTRY(entries["price"]));

    	Product p(make,model, atoi(screenSize.c_str()), atoi(cpuGen.c_str()), atoi(year.c_str()), atoi(price.c_str()));
    	products->insert(p);

    	xml += "<hr>\n";
    	xml += "<vbox homogeneous=\"true\">\n";
    	xml += create_xml_tag("label", "make: " + make);
    	xml += create_xml_tag("label", "model: " + model);
    	xml += create_xml_tag("label", "screen size: " + screenSize);
    	xml += create_xml_tag("label", "cpu Gen: " + cpuGen + "th gen");
    	xml += create_xml_tag("label", "year: " + year);
    	xml += create_xml_tag("label", "price: $" + price + ".00");
    	xml += "</vbox>\n";
    	xml += "<hr>\n";

    } else if(name == "employee_remove_product"){

    	vector<string> productsV = products->printListToString();
    	create_db_list_xml(productsV,xml,"employee_remove_product_confirm","remove_product","remove");

    } else if(name == "remove_product"){

    	string make_and_model = optionsMap["value"];

    	msg = "value: " + make_and_model + "\n";

    	g_print("%s",msg.c_str());

    	size_t pos = make_and_model.find('`');
    	string make = make_and_model.substr(0,pos);
    	string model = make_and_model.substr(pos+1);

    	string_find_and_replace("`"," ",model);

    	g_print("%s",g_strconcat("make: ",make.c_str()," model: ", model.c_str(),"\n",NULL));

    	Product pSearch(make,model,0,0,0,0);

    	g_print("product made\n");

    	msg = "product:\n" + products->find(pSearch)->toString() + "\n";

    	g_print("%s",msg.c_str());

    	xml += "<hr>\n";
    	xml += "<vbox homogeneous=\"true\">\n";
    	xml += create_xml_tag("label", "make: " + products->find(pSearch)->getMake());
    	xml += create_xml_tag("label", "model: " + products->find(pSearch)->getModel());
    	xml += create_xml_tag("label", "screen size: " + to_string(products->find(pSearch)->getScreenSize()));
    	xml += create_xml_tag("label", "cpu Gen: " + to_string(products->find(pSearch)->getCpuGen()) + "th gen");
    	xml += create_xml_tag("label", "year: " + to_string(products->find(pSearch)->getYear()));
    	xml += create_xml_tag("label", "price: $" + to_string(products->find(pSearch)->getPrice()) + ".00");
    	xml += "</vbox>\n";
    	xml += "<hr>\n";

    	products->remove(pSearch);

    } else if(name == "employee_db_search"){
        
        string value = optionsMap["value"];
        
        if(value == "comp_name"){
            xml += create_xml_tag("title","List Database of products by: Company name");
            xml += "<hr>\n";
            vector<string> productsV = products->printListToString();
            create_db_list_xml(productsV,xml);
            
        } else if(value == "price"){
            
            
        } else if(value == "model"){
            xml += create_xml_tag("title","List Database of products by: Company name");
            xml += "<hr>\n";
            vector<string> productsV = products_secondary->printListToString();
            create_db_list_xml(productsV,xml);
        }
    }
    
    /*else if(name == "employee_view_orders") {
       string orders = priority_queue.printSorted();

       stringstream ordersSep(orders);

       string order;

       xml += "<hbox homogeneous\"true\">\n";

       while(getline(ordersSep,order)){

            //get each order in the queue
            stringstream orderSep(order);

            string item;
            xml += "<scroll>"
            while(getline(orderSep,item,',')){

                xml += create_xml_tag("label",item);

            }
        }

        xml += "</hbox>";
    }*/
    
    /**
     @TODO
     - execute options based on if else to detect name and proceed accordingly
     (so we will still need the huge if-elif stack)
     [begun]
     - destroy this window [done]
     */
    
    WindowManager::go_to_window(optionsMap["link"],xml); //go to the new window
}

string Window::create_xml_tag(string tag, string text){
    
    string xml;
    xml += "<" + tag + ">\n";
    xml += text + "\n";
    xml += "</" + tag + ">\n";
    return xml;
}

string Window::create_xml_tag(string tag, string options, string text){
    
    string xml;
    xml += "<" + tag + " " + options + ">\n";
    xml += text + "\n";
    xml += "</" + tag + ">\n";
    return xml;
}

gboolean Window::delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) { //called when close window red button is pressed at app level
     
    if(WindowManager::get_current_window_id() == "end_screen") {
        gtk_main_quit();
        return TRUE;
    } else {
        
        WindowManager::go_to_window("end_screen","");
        //WindowManager::run_pbar();
        return FALSE;
    }
    
}

void Window::destroy(GtkWidget* widget, gpointer data) { //called from regular buttons
    
    gtk_widget_destroy(widget);
    
}

void Window::increase_pbar() {
    
    gdouble frac = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(pbar));
    frac += 0.1;
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar),frac);
    
}

void Window::set_icon(string path) {
    
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(path.c_str(), &error);
    
    if (!pixbuf) {
        
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }
    
    icon = pixbuf;
    
}

void Window::assign_pointers(Heap* heap, BST<Customer>* _customers, BST<Product>* _products, BST<ProductS>* _products_secondary) {
    
    //priority_queue = &heap;
    //customers = _customers;
	products = _products;

	products_secondary = _products_secondary;

    g_print("pointers assigned\n");    
}


void Window::create_db_list_xml(vector<string> productsV, string &xml, string link, string name, string text){

	string size = "width=\"100\""; 
	string index_options = "width=\"50\" justify=\"center\"";

	xml += "<vbox>\n";
	xml += "<hbox homogeneous=\"false\">\n";
	xml += create_xml_tag("label",size,"number"); //index
	xml += create_xml_tag("label",size,"company"); //manf comp
	xml += create_xml_tag("label",size,"model"); //model
	xml += create_xml_tag("label",size,"screen size"); //screen size
	xml += create_xml_tag("label",size,"cpu gen"); //cpu gen
	xml += create_xml_tag("label",size,"year"); //year
	xml += create_xml_tag("label",size,"price"); //price
	xml += "</hbox>\n";

	if(productsV.size() > 9){
		xml += "<scroll columns=\"8\" " + size + ">\n";
		xml += "<vbox>\n";
	}
	
	string attribute;
	string make;

	for (int i = 0; i < productsV.size(); ++i) {
		stringstream product(productsV.at(i));

	    xml += "<hbox homogeneous=\"false\">\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",index_options,attribute); //index

	    xml += "<vr>\n";

	    getline(product,make,',');
	    xml += create_xml_tag("label",size,make); //manf comp
	    
	    xml += "<vr>\n";

	    string model;
	    getline(product,model,',');
	    xml += create_xml_tag("label",size,model); //model
	    
	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute+" in."); //screen size
	    
	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute+"th gen"); //cpu gen
	    
	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute); //year
	    
	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,"$"+attribute+".00"); //price

	    string_find_and_replace(" ","`",model);

		xml += "<vr>\n";

	    xml += create_xml_tag("button","options=\"link:" + link + ",name:" + name + ",value:" + make + "`" + model + "\"",text);
	    
	    xml += "</hbox>\n";
	    xml += "<hr>\n";

	}
	
	if (productsV.size() > 9) {
		xml += "</vbox>\n";
		xml += "</scroll>\n";
	}
	
	xml += "</vbox>\n";

}

void Window::create_db_list_xml(vector<string> productsV, string &xml){ //no buttons

	string size = "width=\"100\""; 
	string index_options = "width=\"50\" justify=\"center\"";

	xml += "<vbox>\n";
	xml += "<hbox homogeneous=\"false\">\n";
	xml += create_xml_tag("label",size,"number"); //index
	xml += create_xml_tag("label",size,"company"); //manf comp
	xml += create_xml_tag("label",size,"model"); //model
	xml += create_xml_tag("label",size,"screen size"); //screen size
	xml += create_xml_tag("label",size,"cpu gen"); //cpu gen
	xml += create_xml_tag("label",size,"year"); //year
	xml += create_xml_tag("label",size,"price"); //price
	xml += "</hbox>\n";

	           

	xml += "<scroll columns=\"7\" " + size + ">\n";
	xml += "<vbox>\n";
	string attribute;

	for (int i = 0; i < productsV.size(); ++i) {
		stringstream product(productsV.at(i));

	    xml += "<hbox homogeneous=\"false\">\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",index_options,attribute); //index

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute); //manf comp
	    
	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute); //model
	    
	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute+" in."); //screen size
	    
	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute+"th gen"); //cpu gen
	    
	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute); //year
	    
	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,"$"+attribute+".00"); //price
	    
	    xml += "</hbox>\n";
	    xml += "<hr>\n";

	}
	
	xml += "</vbox>\n";
	xml += "</scroll>\n";
	xml += "</vbox>\n";

}

void Window::string_find_and_replace(string find, string replace, string &subject){

	string::size_type n = 0;
	while( (n = subject.find(find,n)) != string::npos){

		subject.replace(n,find.size(), replace);
		n += replace.size();
	}

}

vector<string> Window::string_split(const string &input, char delim){

	vector<string> v;
	stringstream ss(input);
	string token;
	while(getline(ss,token,delim)){v.push_back(token);} 
	return v;

}

string Window::to_lower(string str){ //Lifted from cplusplus.com http://www.cplusplus.com/reference/locale/tolower/
	string output;
	locale loc;
	for (string::size_type i=0; i<str.length(); ++i){
		output += tolower(str[i],loc);
	}
    return output;
}

string Window::vector_join(const vector<string> &v, const char* const delim){ //Lifted from SO: https://stackoverflow.com/questions/5288396/c-ostream-out-manipulation/5289170#5289170

	switch(v.size()){
		case 0:
			return "";
		case 1:
			return v[0];
		default:
			ostringstream ss;
			copy(v.begin(), v.end()-1, ostream_iterator<string>(ss, delim));
			ss << *v.rbegin();
			return ss.str();
	}
}

/*
 * WindowManager.cpp
 *
 *  Created on: Jun 2, 2018
 *      Author: Jasper
 */

#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <iostream>
#include <cstddef> //for NULL

using namespace std;

//static variables
map<string, string> WindowManager::windows;
Window* WindowManager::current_window;
string WindowManager::current_window_id;

WindowManager::WindowManager() {
	
	current_window = NULL;
	
}

WindowManager::~WindowManager() {
	delete current_window;
}

void WindowManager::go_to_window(string id, string options){

	if(windows.find(id) == windows.end()){
		id = "404";
	}

	current_window_id = id; //set the current window id to the new id
	string xml = windows[id]; //get the xml
	string replace = "<variable>\n"; //set the replace string
	size_t find = xml.find(replace); //find the variable tag in the xml
	if(find != string::npos){
		xml.replace(find,replace.length(),options); //replace the variable tag with the options
	}
	Window w(xml);	//create the new window
	current_window = &w; //update the current window pointer
}

void WindowManager::loadxml(string path){

	ifstream xmlFile(path.c_str());
	if (xmlFile.is_open()){
		string line;
		while (getline(xmlFile, line)) {
			//this is the window line
			stringstream ss(line);
			string window_id;
			getline(ss, window_id, '\"'); //skip the first part 
			getline(ss, window_id, '\"'); //get the actual id
			string tag = "";
			getline(xmlFile, tag);
			string xml;
			while(tag != "</window>"){
				tag.erase(remove(tag.begin(),tag.end(),'\t'),tag.end()); //remove white space
				xml += tag + "\n";
				getline(xmlFile, tag);
			}
			windows.insert(make_pair(window_id,xml));
		}
	}
}

string WindowManager::get_current_window_id(){
	return current_window_id;
}

void WindowManager::run_pbar(){

	if(current_window_id == "end_screen"){

		clock_t start;
		double duration = 0;
		for(int i = 0; i < 10; i++){
			start = clock();
			while(duration < 10.0 ){

				duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
			}
			g_print("increasing pbar\n");
			current_window->increase_pbar();
		}
		
	}
}


