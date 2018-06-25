/*
 * Main.cpp
 * Mohamed Elgharbawy
 */

#include <iostream>
#include <cstdlib> 
#include <thread>
#include <chrono>

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

	//g_print("args passed to gtk_init\n");
	Heap heap;
	BST<Product> bstp;
	bstp.loadPrimary("Products_in.txt");
	BST<ProductS> bsts;
	bsts.loadSecondary("Products_in.txt");

	HashTable<Customer> htc = FileLoader::loadCustomers("Customers.txt",heap,bstp);
	HashTable<Employee> hte = FileLoader::loadEmployees("Employees.txt");

	cout << "Great Success!" << endl;

	Window::assign_pointers(&heap,&htc,&hte,&bstp,&bsts);
	Window::set_icon("icon.png");
	WindowManager::loadxml("window_data.xml");
	WindowManager::go_to_window("welcome_screen");

	//g_print("going to gtk_main\n");

	gtk_main();

	//g_print("gtk_main has ended\n");

	FileLoader::saveProducts("Products_in.txt",bstp);
	FileLoader::saveCustomers("Customers.txt", htc);
	FileLoader::saveEmployees("Employees.txt", hte);

	cout << "writing files..." << endl;
	for(int i = 0; i < 100; i++){
		if(i < 50){
			FileLoader::printProgBar(i,"Writing Products");
		} else if (i >= 50 and i < 75){
			FileLoader::printProgBar(i,"Writing Customers");
		} else {
			FileLoader::printProgBar(i,"Writing Employees");
		}
		int rand_int = (int)(((rand() % 10)/9.0) * 90) + 10; //rand int between 10 and 100
		this_thread::sleep_for(chrono::milliseconds(10));
	}

	FileLoader::printProgBar(100,"Complete         ");

	cout << endl;


	return 0;
}
