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
#include <cstddef> //for NULL
#include "Heap.h"
#include "BST.h"
#include "Product.h"
#include "Customer.h"


class WindowManager; //forward class declaration

using namespace std;

class Window{
	
protected:
	string title;
	GtkWidget* self_window;
	GtkWidget* self_box;
	GtkWidget* pbar;
	static map<string, GtkWidget*> entries;
	static GdkPixbuf* icon;
	static Heap* priority_queue;
	static BST<Customer>* customers;
	static BST<Product>* products;
	//static HashTable* employees;

public:
	Window();
	
	Window(string xml);
	
	//Window(string title, string labels_text[], string buttons_text[], string layout);
	
	~Window();
	
	static void button_pressed(GtkWidget *widget, gpointer data);

	//called when close window red button is pressed at app level
	static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);

	//called from regular buttons
	static void destroy(GtkWidget* widget, gpointer data);

	void increase_pbar();

	static void set_icon(string path);

	static void assign_pointers(Heap* heap, BST<Customer>* _customers, BST<Product>* _products);

	void create_content(string tagName, string text, map<string,string> optionsMap, GtkWidget* box);

	static string create_xml_tag(string tag, string text);

	static string create_xml_tag(string tag, string options, string text);

};


#endif /* WINDOW_H_ */

