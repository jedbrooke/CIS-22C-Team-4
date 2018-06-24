//
//  FileLoader.h
//  
//
//  Created by Alex Rao on 6/10/18.
//

#ifndef FileLoader_h
#define FileLoader_h
#include <stdio.h>
#include <fstream>
#include "Product.h"
#include "ProductS.h"
#include "Customer.h"
#include "Employee.h"
#include "HashTable.h"
#include "BST.h"

using namespace std;
class FileLoader{
private:
    
public:
    static BST<Product> loadProducts(string path);
    static BST<ProductS> loadProductsS(string path);
    static HashTable<Customer> loadCustomers(string path);
    static HashTable<Employee> loadEmployees(string path);
    static void saveProducts(string path, BST<Product> p);
    static void saveCustomers(string path, HashTable<Customer> c);
    static void saveEmployees(string path, HashTable<Employee> e);
};

#endif /* FileLoader_h */
