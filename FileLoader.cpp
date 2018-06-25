//
//  FileLoader.cpp
//
//
//  Created by Alex Rao on 6/10/18.
//

#include <iostream>
#include <fstream>
#include "FileLoader.h"
using namespace std;



BST<Product> FileLoader::loadProducts(string path) {
	BST<Product> p;
	p.loadPrimary(path);
	return p;
}

BST<ProductS> FileLoader::loadProductsS(string path) {
	BST<ProductS> p;
	p.loadSecondary(path);
	return p;
}

HashTable<Customer> FileLoader::loadCustomers(string path, Heap& heap, BST<Product>& catalog) {

	cout << "loading customers from " << path << endl;

	HashTable<Customer> customers;
	ifstream fis(path.c_str());
	string line;
	if (fis.is_open()) {
		while (getline(fis, line)) {
            string username = line;
						cout << username << endl;
            string password;
            getline(fis, password);
						cout << password << endl;
            string first_name;
            getline(fis, first_name); //advance to the next line
            string last_name;
            getline(fis, last_name); //advance to the next line
            bool isEmployee = false;
            getline(fis, line); //advance to the next line
            string address;
            getline(fis, address);
            string city;
            getline(fis, city); //advance to the next line
            string zip_string;
            unsigned zip;
            getline(fis, zip_string); //advance to the next line
            zip = atoi(zip_string.c_str());
            string email;
            getline(fis,email);
            cout << "email: " << email << endl;
            Customer* c = new Customer(username, password, first_name, last_name, isEmployee, address, city, zip, email);
            customers.insert(*c);

						while(not (fis.peek() == '\n')){
							Order * o = new Order;
							heap.insert(o -> load(fis, catalog));
							c->insertOrder(o);
						}





            getline(fis, line); //skip the emtpy line

        }

	}
	fis.close();
	return customers;
}

HashTable<Employee> FileLoader::loadEmployees(string path) {

	cout << "loading employees..." << endl;

	HashTable<Employee> employees;
	ifstream fis(path.c_str());
	string line;
	if (fis.is_open()) {
		while (getline(fis, line)) {

            string username = line;
            string password;
            getline(fis, password);
            string first_name;
            fis >> first_name;
            getline(fis, line); //advance to the next line
            string last_name;
            fis >> last_name;
            getline(fis, line); //advance to the next line
            bool isEmployee;
            fis >> isEmployee;
            getline(fis, line); //advance to the next line

            Employee* e = new Employee(username, password, first_name, last_name, isEmployee);
            employees.insert(*e);

            getline(fis, line); //skip the emtpy line

		}
	}
	fis.close();
	return employees;
}

void FileLoader::saveProducts(string path, BST<Product> p){
		p.save(path);
}
void FileLoader::saveCustomers(string path, HashTable<Customer> c){
	ofstream of;
	of.open(path.c_str(),ios_base::out);

	List<Customer*> l(c.getAll());

	int size = l.getLength();

	l.startIterator();

	while(not l.offEnd()){
			l.getIterator()->write(of);
			l.moveIterNext();
	}

}
void FileLoader::saveEmployees(string path, HashTable<Employee> e){

	ofstream of;
	of.open(path.c_str(),ios_base::out);

	List<Employee*> l(e.getAll());

	int size = l.getLength();

	l.startIterator();

	while(not l.offEnd()){

			l.getIterator()->write(of);
			l.moveIterNext();
	}

}

void FileLoader::printProgBar(int percent, string message){
  string bar;

  for(int i = 0; i < 50; i++){
    if( i < (percent/2)){
      bar.replace(i,1,"=");
    }else if( i == (percent/2)){
      bar.replace(i,1,"_");
    }else{
      bar.replace(i,1," ");
    }
  }

  cout<< "\r" "[" << bar << "] ";
  cout.width( 3 );
  cout<< percent << "% " << message << flush;
}