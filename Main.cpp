/*
 * Main.cpp
 * Mohamed Elgharbawy
 */

#include <iostream>

#include "BST.h"
#include "Customer.h"
#include "Employee.h"
#include "HashTable.h"
#include "Product.cpp" //will not compile with .h
#include "ProductS.cpp" //will not compile with .h
#include "Heap.h"
#include "FileLoader.h"
#include "WindowManager.cpp" //will not compile with .h
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
