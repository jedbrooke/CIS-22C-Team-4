#include <iostream>
#include "BST.h"
#include "Customer.h"
#include "Employee.h"
#include "HashTable.h"
#include "ProductS.h"
#include <fstream>
//#include "Heap.h"


using namespace std;
int main() {
	//creating some default customer
Customer max;
max.setFirstname("Bob");
max.setLastname("Mike");
max.setAddress("1101 1st street");

Customer max1;
max1.setFirstname("Tin");
max1.setLastname("Nguyen");
max1.setAddress("2nd street");

Customer max2;
max2.setFirstname("maria");
max2.setLastname("unknown");
max2.setAddress("3rd street");


Product x,y,z;

Order r(&max2);	//creating empty order for testing purpose.
Order p(&max2);	//creating empty order.

//some dummy products.
x.setMake("Dell");
x.setPrice(200);
x.setModel("LX");
y.setMake("Lenovo");
y.setPrice(100);
y.setModel("ASD");
z.setMake("alien waire");
z.setModel("keke");
z.setPrice(500);
p.addLaptop(&x);
p.addLaptop(&x);

Order k;

k.addLaptop(&x);
k.addLaptop(&y);
k.addLaptop(&x);

max2.activeOrder(&r);
max1.activeOrder(&k);

cout << "Testing active Order Printing 1: \n"
		<< max2.printActive();
max2.addToProduct(&x);		//add product x to the cart
max2.addToProduct(&x);
max2.addToProduct(&y);

max1.addToProduct(&y);

cout <<"After adding a product: \n"
		<< max2.printActive();

max2.removeProduct(2);	//remove the product.
cout <<"After remove: \n" << max2.printActive();

//testing HashTable
HashTable<Customer> h;
h.insert(max2);
h.insert(max1);
cout << "TESTING HASHTABLE 1:\n ";
h.displayCustomer(cout);

//place order.
r.placeOrder(30); //calling place order function.
k.placeOrder(20);
//max2.insertOrder(); //	once the order has been place, add to history list.
//max1.insertOrder();
cout << "TESTING HASHTABLE 2:\n ";
h.displayCustomer(cout);

//creating some dummy Order to reset active cart;
Order dummy(&max2);


max2.activeOrder(&dummy);		//pass in new empty order
cout << "Active Order:\n";		//to reset the Cart.
cout << max2.printActive();

max2.addToProduct(&x);
cout << "New Active Order 123: \n" << max2.printActive();
dummy.placeOrder(5);
//max2.insertOrder();

cout << "HashTable 3 \n";
h.displayCustomer(cout);


}








