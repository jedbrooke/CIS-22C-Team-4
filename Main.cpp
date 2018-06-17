/*
 * Main.cpp
 * Mohamed Elgharbawy
 */

#include <iostream>

#include "BST.h"
#include "Customer.h"
#include "Employee.h"
#include "HashTable.h"
#include "Product.cpp"
#include "ProductS.cpp"
#include "Heap.h"
#include "FileLoader.h"
#include "WindowManager.cpp"
#include <gtk/gtk.h>

using namespace std;


int main(int argc, char *argv[]) {


	gtk_init (&argc, &argv);

	g_print("args passed to gtk_init\n");

	BST<Product> bstp;
	Product product;
	ProductS productS;
	//Heap heap;

	cout << "Success!" << endl;


	Window::assign_pointers(NULL,NULL,&bstp);
	WindowManager::loadxml("window_data.xml");
	WindowManager::go_to_window("welcome_screen","");

	g_print("going to gtk_main\n");

	gtk_main();

	g_print("gtk_main has ended\n");



	return 0;
}
