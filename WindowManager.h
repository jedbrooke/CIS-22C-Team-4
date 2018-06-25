/*
 * WindowManager.h
 *
 *  Created on: Jun 2, 2018
 *      Author: Jasper
 */

#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include "Window.h"
#include <vector>
#include <string>
#include <iostream>
#include <map> //for maps
#include <gtk/gtk.h>

class Window; //forward class declaration


using namespace std;

class WindowManager {

private:
	static map<string, string> windows;
	static Window* current_window;
	static string current_window_id;

public:
	WindowManager();
	~WindowManager();
	static void go_to_window(string id, string options);
	static void go_to_window(string id);
	static void loadxml(string path);
	static string getxml(string id);
	static string get_current_window_id();
	static void run_pbar();
};


#endif /* WINDOWMANAGER_H_ */
