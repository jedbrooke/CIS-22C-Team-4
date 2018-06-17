//
//  FileLoader.h
//  
//
//  Created by Jasper Edbrooke on 6/10/18.
//

#ifndef FileLoader_h
#define FileLoader_h
#include <stdio.h>
#include <fstream>
#include "Product.cpp"
#include "Customer.h"
#include "Employee.h"
#include "BST.h"

using namespace std;
class FileLoader{
private:
    
public:
    static BST<Product> loadProducts(string path);
    static BST<Customer> loadCustomers(string path);
    static BST<Employee> loadEmployees(string path);
};

#endif /* FileLoader_h */
