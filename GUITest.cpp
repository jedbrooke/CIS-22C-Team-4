/*
 * GUITest.cpp
 *
 *  Created on: Jun 2, 2018
 *      Author: Jasper
 */

#include <gtk/gtk.h>
#include "WindowManager.cpp"
#include "FileLoader.cpp"

using namespace std;

int main(int argc, char *argv[]) {

	gtk_init (&argc, &argv);

	g_print("args passed to gtk_init\n");

	Window::set_icon("icon.png");
    
    string path = "products_in.txt";
    static BST<Product> p(FileLoader::loadProducts("products_in.txt"));

    g_print("assigning pointers\n");

    Window::assign_pointers(NULL,NULL,&p);
    
    
	WindowManager::loadxml("window_data.xml");
	WindowManager::go_to_window("boxes","");

	g_print("going to gtk_main\n");

	gtk_main();

	g_print("gtk_main has ended\n");

	return 0;

}

