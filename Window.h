/*
 * Window.h
 *  Created on: Jun 2, 2018
 *      Author: Jasper
 */
#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <gtk/gtk.h>
#include <vector>
#include <map>
#include <cstddef> //for NULL
#include "Heap.h"
#include "BST.h"
#include "Product.h"
#include "ProductS.h"
#include "User.h"
#include "Customer.h"
#include "Employee.h"
#include "WindowManager.h"
#include "HashTable.h"


//class Heap;

class WindowManager; //forward class declaration

using namespace std;

class Window {
	
protected:
	string title;
	GtkWidget* self_window;
	GtkWidget* self_box;
	GtkWidget* pbar;
	static map<string, GtkWidget*> entries;
	static GdkPixbuf* icon;
	static Heap* priority_queue;
	static HashTable<Customer>* customers;
	static HashTable<Employee>* employees;
	static BST<Product>* products;
	static BST<ProductS>* products_secondary;
	static User* user;
	//static HashTable* employees;

public:
	Window();
	
	Window(string xml);
	
	~Window();
	
	static void button_pressed(GtkWidget *widget, gpointer data);

	//called when close window red button is pressed at app level
	static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);

	//called from regular buttons
	static void destroy(GtkWidget* widget, gpointer data);

	void increase_pbar();

	static void set_icon(string path);

	static void assign_pointers(Heap* heap, HashTable<Customer>* _customers, HashTable<Employee>* _employees, BST<Product>* _products, BST<ProductS>* _products_secondary);

	void create_content(string tagName, string text, map<string,string> optionsMap, GtkWidget* box);

	static string create_xml_tag(string tag, string text);

	static string create_xml_tag(string tag, string options, string text);

	static void create_db_list_xml(vector<string> productsV, string &xml, string link, string name, string text);

	static void create_db_list_xml(vector<string> productsV, string &xml);

	static void string_find_and_replace(string find, string replace, string &subject);

	static vector<string> string_split(const string &input, char delim);

	static string to_lower(string str);

	static string vector_join(const vector<string> &v, const char* const delim);

	static bool is_number(const string& s);

};


#endif /* WINDOW_H_ */

