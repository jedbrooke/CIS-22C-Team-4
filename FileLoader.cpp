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
            fis >> address;
            getline(fis, line); //advance to the next line
            string city;
            fis >> city;
            getline(fis, line); //advance to the next line
            unsigned zip;
            fis >> zip;
            getline(fis, line); //advance to the next line
            string email;
            fis >> email;
            getline(fis, line); //advance to the next line

            Customer c(username, password, first_name, last_name, isEmployee, address, city, zip, email);
            customers.insert(c);

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

            Employee e(username, password, first_name, last_name, isEmployee);
            employees.insert(e);

            getline(fis, line); //skip the emtpy line

		}
	}
	fis.close();
	return employees;
}
