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

HashTable<Customer> FileLoader::loadCustomers(string path) {

	cout << "loading customers..." << endl;

	HashTable<Customer> customers;
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
            string address;
            getline(fis, address);
            string city;
            fis >> city;
            getline(fis, line); //advance to the next line
            unsigned zip;
            fis >> zip;
            getline(fis, line); //advance to the next line
            string email;
            fis >> email;
            getline(fis, line); //advance to the next line

            Customer* c = new Customer(username, password, first_name, last_name, isEmployee, address, city, zip, email);
            customers.insert(*c);

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

static void saveProducts(string path, BST<Product> p);
static void saveCustomers(string path, HashTable<Customer> c);
static void saveEmployees(string path, HashTable<Employee> e);
