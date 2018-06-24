//
//  FileLoaderTest.cpp
//  
//
//  Created by Alex Rao on 6/10/18.
//

#include <stdio.h>
#include "FileLoader.h"
#include "HashTable.h"
#include <sstream>
using namespace std;

class FileLoader;

int main(){

    string path = "products_in.txt";
    BST<Product> p(FileLoader::loadProducts(path));

    path = "Customers.txt";
    HashTable<Customer> c(FileLoader::loadCustomers(path));

    path = "Employees.txt";
    HashTable<Employee> e(FileLoader::loadEmployees(path));

    Employee* em = e.customerSignIn("sandhater50");


    cout << "employee:" << endl;
    em->write(cout);
}
