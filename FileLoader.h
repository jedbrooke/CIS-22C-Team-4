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
#include "BST.h"
#include "Product.h"
#include "ProductS.h"
#include "Customer.h"
#include "Employee.h"
#include "HashTable.h"
#include "Heap.h"

using namespace std;
class FileLoader{
private:

public:
    static BST<Product> loadProducts(string path);
    static BST<ProductS> loadProductsS(string path);
    static HashTable<Customer> loadCustomers(string path, Heap& heap, BST<Product>& catalog);
    static HashTable<Employee> loadEmployees(string path);
    static void saveProducts(string path, BST<Product> p);
    static void saveCustomers(string path, HashTable<Customer> c);
    static void saveEmployees(string path, HashTable<Employee> e);
    static void saveAll(string product_path,string customer_path,string employee_path, BST<Product> p, HashTable<Customer> c, HashTable<Employee> e);
    static void printProgBar(int percent, string message);
};

#endif /* FileLoader_h */
