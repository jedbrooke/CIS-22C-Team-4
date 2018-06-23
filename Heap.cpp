/*
 * Heap.cpp
 * Andrew Maxwell
 */

#include <vector>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <sstream>
#include "Heap.h"

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
    	if(!heaped) {
    		build_heap();
    	}
    	if (*(heap -> at(floor(i/2))) < *key) {
    		heap -> at(i) = heap -> at(floor(i/2));
    		heap -> at(floor(i/2)) = key;
    		heap_increase_key(floor(i/2), key);
    	}
    }
    //helper function to insert
    //bubbles an element up to its proper location

    void Heap::remove(int index) {
    	if(!heaped) {
    		build_heap();
    	}
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
    	if(!heaped) {
    		build_heap();
    	}
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
    	if(!heaped) {
    		build_heap();
    	}
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
    	if(heaped) {
    		sort();
    	}
    	assert(1 <= index);
    	assert(index <= heap_size);
    	heap -> at(heap_size - index + 1) -> ship();
    }
    //Ships an order and removes it from the heap.

    void Heap::clear() {	//Removes the shipped orders. pre: is a heap.
    	if(!heaped) {
    		build_heap();
    	}
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
    	if(heaped) {
    		sort();
    	}
    	assert(1 <= index);
    	assert(index <= heap_size);
    	return heap -> at(heap_size - index + 1) -> printDetailed();
    }

    string Heap::printSorted() {			//Prints all of the orders in sorted order. Pre: must be sorted (!heaped).
    	if(heaped) {
    		sort();
    	}
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
