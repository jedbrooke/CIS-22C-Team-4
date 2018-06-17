//
//  FileLoaderTest.cpp
//  
//
//  Created by Jasper Edbrooke on 6/10/18.
//

#include <stdio.h>
#include "FileLoader.cpp"
#include "Product.h"
#include "Customer.h"
#include "Employee.h"
#include <sstream>
using namespace std;

class FileLoader;

int main(){

    string path = "products_in.txt";
    BST<Product> p(FileLoader::loadProducts(path));

    path = "Customers.txt";
    BST<Customer> c(FileLoader::loadCustomers(path));

    path = "Employees.txt";
    BST<Employee> e(FileLoader::loadEmployees(path));

    cout << "hi";
}
