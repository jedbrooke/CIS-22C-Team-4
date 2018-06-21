/*
 * Main.cpp
 * Mohamed Elgharbawy
 */

#include <iostream>

#include "BST.h"
#include "Customer.h"
#include "Employee.h"
#include "HashTable.h"
#include "Product.h"
#include "ProductS.h"
#include "Heap.h"
#include "FileLoader.h"
#include "WindowManager.h"
#include "Window.h"
#include <gtk/gtk.h>

using namespace std;


int main(int argc, char *argv[]) {


	gtk_init (&argc, &argv);

	g_print("args passed to gtk_init\n");

	BST<Product> bstp;
	bstp.loadPrimary("Products_in.txt");
	BST<ProductS> bsts;
	bsts.loadSecondary("Products_in.txt");

	//HashTable<Customer> htc = FileLoader::loadCustomers("Customers.txt");
	//  HashTable<Employee> hte = FileLoader::loadEmployees("Employees.txt");

	HashTable<Customer> htc;
	HashTable<Employee> hte;

	Product product;
	ProductS productS;
	Heap heap;
	

	Customer c("foo@bar.com","Hi1234","Bobby","Mcbobface",false,"123 faké street","Cupertinoville",12345,"helloIamcustomer");
	Customer c2("foo2@bar.com","2Hi1234","Bobby2","Mcbobface2",false,"123 faké street2","Cupertinoville2",12345,"helloIamcustomer2");
	Employee e("joe","hi","joe","joeman",true);

	htc.insert(c);
	htc.insert(c2);
	hte.insert(e);

	cout << "Success!" << endl;


	Window::assign_pointers(&heap,&htc,&hte,&bstp,&bsts);
	WindowManager::loadxml("window_data.xml");
	WindowManager::go_to_window("welcome_screen");

	g_print("going to gtk_main\n");

	gtk_main();

	g_print("gtk_main has ended\n");



	return 0;
}
