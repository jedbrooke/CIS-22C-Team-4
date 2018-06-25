/*
 * Window.cpp
 *
 *  Created on: Jun 2, 2018
 *      Author: Jasper
 */

#ifdef _WIN32
#include <algorithm>
#endif // _WIN32


#include "Window.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <locale>
#include <iterator>
#include <iostream>
#include <fstream>
#include <gtk/gtk.h>


using namespace std;

//static variables
GdkPixbuf* Window::icon;
map<string, GtkWidget*> Window::entries;
Heap* Window::priority_queue;
HashTable<Customer>* Window::customers;
HashTable<Employee>* Window::employees;
BST<Product>* Window::products;
BST<ProductS>* Window::products_secondary;
User* Window::user;
Order* Window::order;

Window::Window(string xml) {

    //create the window
    self_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(self_window, "delete-event", G_CALLBACK(delete_event), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(self_window), 10);

    //create box
    self_box = gtk_vbox_new(FALSE, 2);

    //set the box spacing
    gtk_box_set_spacing(GTK_BOX(self_box),3);

    //add the box to the window
    gtk_container_add(GTK_CONTAINER(self_window), self_box);

    //wipe the entries
    map<string, GtkWidget*> m;
    entries = m;

    //set up xml stringstream
    stringstream xmlss(xml);

    string tag, text, closetag = "";

    //create new vector of box pointers
	vector<GtkWidget*> boxes;
	boxes.push_back(self_box);

    while(getline(xmlss,tag)) {
        string msg;

        //get the tag
        string tagName;
        string options;
        try{
            tag = tag.substr(1, tag.length()-2); //get rid of the <>
            size_t pos = tag.find(" ");
            tagName = tag.substr(0, pos); //get the tag name
            options = tag.substr(pos+1); //get the options
        } catch(exception const &e){
            cerr << "Error: " << e.what() << endl;
            cerr << "tag: " << tag << endl;
        }


        map<string,string> optionsMap;

        string optionpair;
        stringstream optionsSS(options);

        while(getline(optionsSS,optionpair,' ')) {//loop through the options, separated by spaces
            string attribute;
            string value;

            stringstream optsep(optionpair);

            getline(optsep, attribute, '\"'); //skip the options=
            attribute = attribute.substr(0,attribute.length()-1); //get rid of the '='
            getline(optsep,value,'\"'); //get the actual value

            optionsMap.insert(make_pair(attribute,value));
        }

        if(tagName == "variable") { //skip unassigned variable tag, should not happen but just in case

            continue;

        } else if(tagName == "hbox") {// skip the line named box and assign inner box == true;

            //get homogeneous
            if(optionsMap["homogeneous"] == "true"){
                //create new box
                boxes.push_back(gtk_hbox_new(TRUE, 2));
            } else {
                //create new box
                boxes.push_back(gtk_hbox_new(FALSE, 2));
            }

            //set the box spacing
            gtk_box_set_spacing(GTK_BOX(boxes.at(boxes.size()-1)),3);

            if (optionsMap.find("left") != optionsMap.end()) {

                gtk_misc_set_alignment(GTK_MISC(boxes.at(boxes.size()-1)),(int)atoi(optionsMap["left"].c_str()),0);
            }

            //restart the while loop
            continue;

        } else if (tagName == "vbox") {

            //get homogeneous
            if(optionsMap["homogeneous"] == "true"){
                //create new box
                boxes.push_back(gtk_vbox_new(TRUE, 2));
            } else {
                //create new box
                boxes.push_back(gtk_vbox_new(FALSE, 2));
            }

            //set the box spacing
            gtk_box_set_spacing(GTK_BOX(boxes.at(boxes.size()-1)),3);

            continue;

        } else if (tagName == "scroll") {

        	//create the new scroll window
        	GtkWidget* scroll_window = gtk_scrolled_window_new(NULL,NULL);
        	boxes.push_back(scroll_window); //NULL,NULL for auto-generated scroll bars

        	if (optionsMap.find("columns") != optionsMap.end() && optionsMap.find("width") != optionsMap.end()) { //if the number of columns and the width is present
        		//set the scroll window size
        		int size = atoi(optionsMap["columns"].c_str()) * (atoi(optionsMap["width"].c_str())+4) + 15;
        		gtk_widget_set_size_request (scroll_window, size, 300);

        	} else if(optionsMap.find("width") != optionsMap.end()){ //if just the width is present
                //set the scroll window size
                int size = atoi(optionsMap["width"].c_str()) + 15;
                gtk_widget_set_size_request (scroll_window, size, 300);

            } else {
        		// just make it big
        		gtk_widget_set_size_request (scroll_window, 1500, 300);
        	}



        	//set the box border width
        	gtk_container_set_border_width (GTK_CONTAINER (boxes.at(boxes.size()-1)), 10);

        	//set the box policy
        	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (boxes.at(boxes.size()-1)), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

        	continue;

        } else if (tagName == "hr") {

        	//make a horizontal separator
        	GtkWidget* hr = gtk_hseparator_new();

        	//pack it into the box
        	gtk_box_pack_start(GTK_BOX(boxes.at(boxes.size()-1)),hr,FALSE,FALSE,0);

        	//show the wdiget
        	gtk_widget_show(hr);

        	continue;

        } else if (tagName == "vr") {

        	//make a horizontal separator
        	GtkWidget* vr = gtk_vseparator_new();

        	//pack it into the box
        	gtk_box_pack_start(GTK_BOX(boxes.at(boxes.size()-1)),vr,FALSE,FALSE,0);

        	//show the wdiget
        	gtk_widget_show(vr);

        	continue;

        } else if(tagName == "/hbox" || tagName == "/vbox" || tagName == "/scroll") {

            string box_name = g_strconcat(G_OBJECT_TYPE_NAME(boxes.at(boxes.size()-2)),NULL);
        	string window_name = "GtkScrolledWindow";
        	if( box_name == window_name) {
            	//pack it into the scroll box
            	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW (boxes.at(boxes.size()-2)), boxes.at(boxes.size()-1));
            } else {
            	//pack the box into the next higher box
            	gtk_box_pack_start(GTK_BOX(boxes.at(boxes.size()-2)),boxes.at(boxes.size()-1),FALSE,FALSE,0);
            }

            //show the box
            gtk_widget_show(boxes.at(boxes.size()-1));

            //remove the box from the box stack
            boxes.pop_back();

            continue;

        }

        //end of elf

        getline(xmlss,text); //get the text
        getline(xmlss,closetag); //and the closetag

        try{
            if(boxes.size() > 1) {
                create_content(tagName,text,optionsMap,boxes.at(boxes.size()-1));
            } else {
                create_content(tagName,text,optionsMap,self_box);
            }
        } catch(const string msg){
            cerr << msg << endl;
        }

    }

    //show the box
    gtk_widget_show(self_box);

    //align window in center
    gtk_window_set_position(GTK_WINDOW(self_window), GTK_WIN_POS_CENTER);

    //make the window deletable
    gtk_window_set_deletable(GTK_WINDOW(self_window), TRUE);

    //set the window icon
    gtk_window_set_icon(GTK_WINDOW(self_window), icon);

    //show the window
    gtk_widget_show(self_window);

    //make the window active
    //gtk_window_activate_focus(GTK_WINDOW(self_window));
}

Window::~Window() {
    // TODO Auto-generated destructor stub
    //idk, delete some stuff I guess
}

void Window::create_content(string tagName, string text, map<string,string> optionsMap, GtkWidget* box) {
    string msg;
    GtkWidget* widget;

    if(tagName == "title") {

        //make the title lable
        widget = gtk_label_new(text.c_str());

        //set alignment
        gtk_misc_set_alignment(GTK_MISC(widget),0,0);

        //title markup
        char* markup = g_strconcat("<big>", text.c_str(), "</big>", NULL);
        gtk_label_set_markup(GTK_LABEL(widget), markup);
        g_free(markup);
        gtk_misc_set_alignment(GTK_MISC(widget), 0, 0);

    } else if(tagName == "button") {

        //create new button
        widget = gtk_button_new_with_label(text.c_str());
        //set name
        gtk_widget_set_name(widget,optionsMap["options"].c_str());

        //set signal connect method
        g_signal_connect(widget, "clicked", G_CALLBACK(button_pressed), FALSE);

        if(optionsMap["stay"] != "true"){
            //connect it to the destroy event as well
            g_signal_connect_swapped(widget,"clicked",G_CALLBACK(destroy),self_window);
        }





    } else if(tagName == "label") {

        //create new label
        widget = gtk_label_new(text.c_str());

        //make the text selectable just for funsies, ok maybe not
        //gtk_label_set_selectable (GTK_LABEL(widget), TRUE);

        //set styles
        if(optionsMap["style"] == "error"){
        	//error markup
        	char* markup = g_strconcat("<span foreground=\"red\">", text.c_str(), "</span>", NULL);
        	gtk_label_set_markup(GTK_LABEL(widget), markup);
        	g_free(markup);
        }

        if (optionsMap.find("width") != optionsMap.end()) {//if the size option is present

        	gtk_widget_set_size_request(widget,atoi(optionsMap["width"].c_str()),-1);

        	gtk_label_set_line_wrap (GTK_LABEL(widget),TRUE);
        }

        if (optionsMap["justify"] == "center") {

        	gtk_label_set_justify(GTK_LABEL(widget),GTK_JUSTIFY_CENTER);

        	//set alignment
        	gtk_misc_set_padding(GTK_MISC(widget),atoi(optionsMap["width"].c_str())/2.0, 0);

        	//g_print("%s",g_strconcat("width is: ", to_string(atoi(optionsMap["width"].c_str())/2.0).c_str(),"\n",NULL));

        } else if (optionsMap["justify"] == "right") {

        	gtk_label_set_justify(GTK_LABEL(widget),GTK_JUSTIFY_RIGHT);
        } else {

        	//set alignment
        	gtk_misc_set_alignment(GTK_MISC(widget), 0, 0);
        }

    } else if (tagName == "entry") {

        //create new entry and assign it to the pointer
        widget = gtk_entry_new();

        //set the name
        gtk_widget_set_name(widget,text.c_str());

        //check if it's a password box
        if (optionsMap["type"] == "psw") {
            gtk_entry_set_visibility(GTK_ENTRY(widget),FALSE);
        } else if (optionsMap["type"] == "hidden"){
        	gtk_entry_set_text(GTK_ENTRY(widget),optionsMap["value"].c_str());
        }

        //adding entries to entries map
        entries.insert(make_pair(text,widget));

    } else if (tagName == "pbar") {

        msg = "creating pbar: " + text + "\n";
        //g_print("%s",msg.c_str());

        widget = gtk_progress_bar_new();

        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(widget),text.c_str());

    } else {
        string err = "Error: Invalid XML tag: " + tagName;
        throw err;
    }

    string box_name = g_strconcat(G_OBJECT_TYPE_NAME(box),NULL);
	string window_name = "GtkScrolledWindow";
	if(box_name == window_name) {
    	//pack it into the scroll box
    	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (box), widget);
    } else {
    	//add widget to box
    	gtk_box_pack_start(GTK_BOX(box), widget, FALSE, FALSE, 0);
    }

    //set it to default if it is set to default
    if (optionsMap["default"] == "true"){

    	msg = "setting button \"" + text + "\" to be default\n";
    	//g_print("%s",msg.c_str());

    	gtk_widget_set_can_default (widget, TRUE);
    	gtk_widget_grab_default (widget);
    }

    if(optionsMap["type"] == "hidden"){

    	//don't show the widget

    } else {
    	//show the widget
    	gtk_widget_show(widget);
    }

}

void Window::button_pressed(GtkWidget* widget, gpointer data) {

    string xml = "";

    string optionsRaw = gtk_widget_get_name(widget); //the options are stored in the button name
    stringstream optsep(optionsRaw); //now we need a string stream object to extract them
    map<string, string> optionsMap; //and a map to store them

    string optvalpair; //this will store the pairs of option:value

    while(getline(optsep,optvalpair,',')) { //loop through each comma separated option:value pair

        stringstream seperator(optvalpair); //another string stream object to separate the pair
        string option;
        string value;
        getline(seperator,option,':'); //get the option
        getline(seperator,value,':'); //get the value
        optionsMap.insert(make_pair(option,value)); //add them to the map
    }

    string name = optionsMap["name"];
    string msg;

    if(name == "quit") {
        user = NULL;
        order = NULL;
        //do all the write functions
        gtk_main_quit();

    } else if(name == "open"){
        string make_and_model = optionsMap["value"];
        string_find_and_replace("`"," ",make_and_model);
        string url = "https://google.com/search?q=" + make_and_model;

        string cmd_win = "explorer \"" + url + "\"";
        system(cmd_win.c_str());
        string cmd_unix = "open \"" + url + "\"";
        system(cmd_unix.c_str());

    } else if(name == "customer_sign_in") {

        string email = gtk_entry_get_text(GTK_ENTRY(entries["email"]));
        string psw = gtk_entry_get_text(GTK_ENTRY(entries["psw"]));

        Customer* c = customers->customerSignIn(email);
        Customer* c_check = new Customer(email,psw,"","",false,"","",0,"");

        if(c == NULL){
            xml += create_xml_tag("label","style=\"error\"","That username is not in our database");
            WindowManager::go_to_window("customer_sign_in_using_and_existing_account",xml);
            return;
        }

        if(!(*c_check == *c)){
            xml += create_xml_tag("label","style=\"error\"","usernames and/or passwords do not match");
            WindowManager::go_to_window("customer_sign_in_using_and_existing_account",xml);
            return;
        }

        user = c;

        order = new Order(c);
        c->activeOrder(order);

        xml += create_xml_tag("title","Welcome, " + c->getFirstname() + ".");
        xml += "<hr>\n";

        delete c_check;

    } else if(name == "employee_login") {

        string username = gtk_entry_get_text(GTK_ENTRY(entries["username"]));
        string psw = gtk_entry_get_text(GTK_ENTRY(entries["psw"]));

        username.erase(remove(username.begin(),username.end(),' '),username.end()); //remove white space

        Employee* e = employees->customerSignIn(username);
        Employee* e_check = new Employee(username,psw,"","",true);

        if(e == NULL){
            xml += create_xml_tag("label","style=\"error\"","That username is not in our database");
            WindowManager::go_to_window("employee_login_screen",xml);
            return;
        }

        if(!(*e_check == *e)){
            xml += create_xml_tag("label","style=\"error\"","Incorrect password");
            WindowManager::go_to_window("employee_login_screen",xml);
            return;
        }

        user = e;

        delete e_check;

    } else if(name == "customer_create_new_account_1") {

        //get parameters
        string email = gtk_entry_get_text(GTK_ENTRY(entries["email"]));
        string conf_email = gtk_entry_get_text(GTK_ENTRY(entries["conf_email"]));
        string psw = gtk_entry_get_text(GTK_ENTRY(entries["psw"]));
        string conf_psw = gtk_entry_get_text(GTK_ENTRY(entries["conf_psw"]));

        if(customers->customerSignIn(email) != NULL){ //check if it's taken
            xml += create_xml_tag("label","style=\"error\"","Sorry, that username is taken");
            WindowManager::go_to_window("customer_create_new_account",xml); //go back to the customer create new account window
            return;
        }

        //time to check
        if(email != conf_email || psw != conf_psw){
        	if(email != conf_email){
        		xml += create_xml_tag("label","style=\"error\"","error: usernames must match");
        	}
        	if (psw != conf_psw){
        		xml += create_xml_tag("label","style=\"error\"","error: passwords must match");
        	}

        	WindowManager::go_to_window("customer_create_new_account",xml); //go back to the customer create new account window
        	return;

        } else if(email == "" || psw == ""){

        	xml += create_xml_tag("label","style=\"error\"","error: please do not leave any fields blank");

        	WindowManager::go_to_window("customer_create_new_account",xml); //go back to the customer create new account window
        	return;

        }

    	string value = email + "`" + psw;
    	xml += create_xml_tag("entry","type=\"hidden\" value=\""+value+"\"","values");

    } else if(name == "customer_create_new_account_2") {

    	map<string,string> values;

    	string email_and_psw = gtk_entry_get_text(GTK_ENTRY(entries["values"]));
    	size_t sep = email_and_psw.find('`'); //separate the email and the password
    	values["email"] = email_and_psw.substr(0,sep);
    	values["psw"] = email_and_psw.substr(sep+1);

    	values["fname"] = gtk_entry_get_text(GTK_ENTRY(entries["fname"]));
    	values["lname"] = gtk_entry_get_text(GTK_ENTRY(entries["lname"]));
    	values["address"] = gtk_entry_get_text(GTK_ENTRY(entries["address"]));
    	values["phone_num"] = gtk_entry_get_text(GTK_ENTRY(entries["phone_num"]));
    	values["city"] = gtk_entry_get_text(GTK_ENTRY(entries["city"]));
    	values["zip_str"] = gtk_entry_get_text(GTK_ENTRY(entries["zip"]));
    	unsigned zip;

        bool isValid = true;

    	if(values["fname"] == "" || values["lname"] == "" || values["address"] == "" || values["phone_num"] == "" || values["city"] == "" || values["zip_str"] == ""){//if any of the fields are blank, reject
    		isValid = false;
            xml += create_xml_tag("label","style=\"error\"","error: please do not leave any fields blank");
    	}

        if(!is_number(values["zip_str"]) || values["zip_str"].length() != 5){ //if zip is not a number or is not 5 digits exactly
            isValid = false;
            xml += create_xml_tag("label","style=\"error\"","please enter a 5 digit number for the ZIP code");
        } else{
            zip = atoi(values["zip_str"].c_str());
        }

        if(!isValid){
            string value = values["email"] + "`" + values["psw"];
            xml += create_xml_tag("entry","type=\"hidden\" value=\""+value+"\"","values");
            WindowManager::go_to_window("customer_create_new_account_cont",xml);
            return;
        }

		Customer* c = new Customer(values["email"],values["psw"],values["fname"],values["lname"],false,values["address"],values["city"],zip,values["email"]);
		customers->insert(*c);

        user = customers->customerSignIn(values["email"]);

        Customer* c_ptr = static_cast<Customer*>(user);

        order = new Order(c_ptr);
        c_ptr->activeOrder(order);

        xml += create_xml_tag("title","Welcome, " + user->getFirstname() + ".");
        xml += "<hr>\n";

    } else if(name == "customer_search"){

    	string make = gtk_entry_get_text(GTK_ENTRY(entries["make"]));
        string model = gtk_entry_get_text(GTK_ENTRY(entries["model"]));

        if(make == "" && model == ""){
        	xml += create_xml_tag("label","style=\"error\"","Please enter the make and/or model you would like to search for.");
     		WindowManager::go_to_window("customer_search_for_a_product",xml);
     		return;
        }

        vector<string> productsV = products->printListToString();
        vector<string> matches;

        if( make != "" && model == ""){ //if they just searched for make
        	xml += create_xml_tag("title","Search Results for \"" + make + "\":");
        	//loop through the products in the vector
        	for (int i = 0; i < productsV.size(); ++i) {
        		vector<string> p = string_split(productsV[i],','); //vector storing product information from vector of all products
        		if(to_lower(p[1]).find(to_lower(make)) != string::npos ){ //if the queried make is present in the current porduct
        			p.at(0) = to_string(matches.size()+1); //set the index
        			matches.push_back(vector_join(p,",")); //add the product to the vector of matches
        		}
        	}

        } else if( make == "" && model != ""){ //if they just searched for model
        	xml += create_xml_tag("title","Search Results for \"" + model + "\":");
        	//loop through the products in the vector
        	for (int i = 0; i < productsV.size(); ++i) {
        		vector<string> p = string_split(productsV[i],','); //vector storing product information from vector of all products
        		if(to_lower(p[2]).find(to_lower(model)) != string::npos ){ //if the queried make is present in the current porduct
        			p.at(0) = to_string(matches.size()+1); //set the index
        			matches.push_back(vector_join(p,",")); //add the product to the vector of matches
        		}
        	}

        } else if( make != "" && model != ""){ //if they search for both
        	xml += create_xml_tag("title","Search Results for \"" + make + " " + model + "\":");
        	//loop through the products in the vector
        	for (int i = 0; i < productsV.size(); ++i) {
        		vector<string> p = string_split(productsV[i],','); //vector storing product information from vector of all products
        		if(to_lower(p[1]).find(to_lower(make)) != string::npos && to_lower(p[2]).find(to_lower(model)) != string::npos ){ //if the queried make is present in the current porduct
        			p.at(0) = to_string(matches.size()+1); //set the index
        			matches.push_back(vector_join(p,",")); //add the product to the vector of matches
        		}
        	}

        }

        if(matches.size() == 0){

        	xml += create_xml_tag("label","No matches");
        } else {
        	xml += create_xml_tag("label","There are " + to_string(matches.size()) + " matches.");
        	create_db_list_xml(matches,xml,"customer_view_cart","add_to_cart","add to cart",true);
        }

    } else if(name == "customer_db_list"){

        string value = optionsMap["value"];

        if(value == "comp_name"){

            vector<string> productsV = products->printListToString();
            create_db_list_xml(productsV,xml,"customer_view_cart","add_to_cart","add to cart",true);

        } else if(value == "price"){


        } else if(value == "model"){

            vector<string> productsV = products_secondary->printListToString();
            create_db_list_xml(productsV,xml,"customer_view_cart","add_to_cart","add to cart",true);
        }

    } else if(name == "add_to_cart"){

        string make_and_model = optionsMap["value"];

        size_t pos = make_and_model.find('`');
        string make = make_and_model.substr(0,pos);
        string model = make_and_model.substr(pos+1);

        string_find_and_replace("`"," ",model);

        Product pSearch(make,model,0,0,0,0);

        Customer* c = static_cast<Customer*>(user);

        if(products->find(pSearch) != NULL){
            c->addToProduct(products->find(pSearch));
        } else {
            cerr << "Error: Product Not found: " << endl << "product information: " << endl;
            cerr << "make: " << make << ", model: " << model << endl;
        }

        create_view_cart_xml(xml);

    } else if(name == "customer_view_cart"){

        if(optionsMap["action"] == "remove"){

            Customer* c = static_cast<Customer*>(user);
            int index = atoi(optionsMap["value"].c_str());
            c->removeProduct(index);

        }

        create_view_cart_xml(xml);

    } else if(name == "place_order"){

        //cout << "placing order" << endl;

        //place order

        int days = atoi(optionsMap["value"].c_str());

        //g_print("%s",g_strconcat("shipping days: ",to_string(days).c_str(),"\n",NULL));

        priority_queue->place(order,days);


        Customer* c = static_cast<Customer*>(user);

        order = new Order(c);
        c->activeOrder(order);

        //prepare purchase history page
        create_purchase_history_xml(xml);

    } else if(name == "purchase_history"){

        //prepare purchase history page
        create_purchase_history_xml(xml);

    } else if(name == "view_order_details"){

        string orderHex = optionsMap["value"]; //get the address hex value
        stringstream hex_convert;
        hex_convert << orderHex;
        long order_address;
        hex_convert >> hex >> order_address; //convert hex into long
        Order* order = reinterpret_cast<Order*>(order_address);

        stringstream orderSS(order->printDetailed());

        string summary;

        getline(orderSS,summary);

        vector<string> v = string_split(summary);

        string price = "Total Price: " + v[0];
        string date = "Arrive By: " + v[1];
        string status = "Order Status: " + v[2];

        xml += "<hbox>\n";
        xml += create_xml_tag("label",price);
        xml += "<vr>\n";
        xml += create_xml_tag("label",date);
        xml += "<vr>\n";
        xml += create_xml_tag("label",status);
        xml += "</hbox>\n";
        xml += "<hr>\n";

        create_order_laptop_list_xml(orderSS,"width=\"100\"","width=\"50\"",xml,false);


        if(not user->getIsEmployee()){

            xml += create_xml_tag("button","options=\"link:customer_interface\"","Back");

        } else{

            xml += create_xml_tag("button","options=\"link:employee_interface\"","Back");

        }

    } else if(name == "preship"){
        int index = atoi(optionsMap["value"].c_str());
        string order_str = priority_queue->printSpecific(index);

        //cout << "in preship func" << endl << order_str << endl;

        stringstream orderSS(order_str);

        string line;

        getline(orderSS,line); //get the order summary line

        std::vector<string> v = string_split(line);
        xml += create_xml_tag("label","Price: " + v[0]);
        xml += create_xml_tag("label","Arrive by: " + v[1]);

        create_order_laptop_list_xml(orderSS,"width=\"100\"","width=\"50\"",xml);

        xml += create_xml_tag("button","options=\"link:employee_shipping_confirmation,name:ship,value:" + to_string(index) + "\"","Confirm");

    } else if(name == "ship"){
        int index = atoi(optionsMap["value"].c_str());
        priority_queue->ship(index);

    } else if(name == "employee_customer_search"){

        string fname = gtk_entry_get_text(GTK_ENTRY(entries["fname"]));
        string lname = gtk_entry_get_text(GTK_ENTRY(entries["lname"]));

        stringstream matches;

        if (fname == "" and lname == "") {
            //wa- hey man you can't just leave the fields blank
            xml += create_xml_tag("label","Please enter a first and/or last name to search");
            WindowManager::go_to_window("employee_search_customer_by_name");
            return;

        } else if(not (fname == "") and lname == ""){ //just the first name

            customers->displayByFirstname(matches,fname);
            xml += create_xml_tag("label","Matches for \"" + fname + "\":");

        } else if(fname == "" and not (lname == "")){ //just last name

            customers->displayByFirstname(matches,lname);
            xml += create_xml_tag("label","Matches for \"" + lname + "\":");

        } else { //we got both

            customers->displayByFirstname(matches,fname);
            customers->displayByFirstname(matches,lname);
            xml += create_xml_tag("label","Matches for \"" + fname + " " + lname + "\":");

        }


        //cout << "matches:" << endl << matches.str() << endl;

        create_customer_list_xml(xml,matches);

    } else if(name == "employee_add_product") {

    	string make = gtk_entry_get_text(GTK_ENTRY(entries["make"]));
    	string model = gtk_entry_get_text(GTK_ENTRY(entries["model"]));
    	string screenSize = gtk_entry_get_text(GTK_ENTRY(entries["screenSize"]));
    	string cpuGen = gtk_entry_get_text(GTK_ENTRY(entries["cpuGen"]));
    	string year = gtk_entry_get_text(GTK_ENTRY(entries["year"]));
    	string price = gtk_entry_get_text(GTK_ENTRY(entries["price"]));

        string_find_and_replace("$","",price); //remove the dollar sign if they added it.

        bool isValid = true;

        if(!is_number(screenSize)){
            isValid = false;
            xml += create_xml_tag("label","style=\"error\"","Screen size must be a decimal number");
        }
        if(!is_number(cpuGen)){
            isValid = false;
            xml += create_xml_tag("label","style=\"error\"","CPU Gen must be a number");
        }
        if(!is_number(year)){
            isValid = false;
            xml += create_xml_tag("label","style=\"error\"","Year must be a number");
        }
        if(!is_number(price)){
            isValid = false;
            xml += create_xml_tag("label","style=\"error\"","Price must be a decimal number");
        }

        if(!isValid){
            WindowManager::go_to_window("employee_add_new_product",xml);
            return;
        }

    	Product p(make,model, atoi(screenSize.c_str()), atoi(cpuGen.c_str()), atoi(year.c_str()), atoi(price.c_str()));
    	products->insert(p);

    	ProductS ps(make,model, atoi(screenSize.c_str()), atoi(cpuGen.c_str()), atoi(year.c_str()), atoi(price.c_str()));
    	products_secondary->insert(ps);

    	xml += "<hr>\n";
    	xml += "<vbox homogeneous=\"true\">\n";
    	xml += create_xml_tag("label", "make: " + make);
    	xml += create_xml_tag("label", "model: " + model);
    	xml += create_xml_tag("label", "screen size: " + screenSize);
    	xml += create_xml_tag("label", "cpu Gen: " + cpuGen + "th gen");
    	xml += create_xml_tag("label", "year: " + year);
    	xml += create_xml_tag("label", "price: $" + price + ".00");
    	xml += "</vbox>\n";
    	xml += "<hr>\n";

    } else if(name == "add_product_by_file") {

        /*checkpoint*/

        string file_name = gtk_entry_get_text(GTK_ENTRY(entries["file_name"]));

        ifstream fis;

        size_t pos = file_name.find(".");

        if(file_name.substr(pos+1) != "txt"){//if it's not a text file
            xml += create_xml_tag("label","style=\"error\"","Error: Only text files are supported");
            WindowManager::go_to_window("employee_add_product_by_file",xml);
            return;
        }   

        fis.open(file_name.c_str());

        if(fis.fail()){//file not found or could not be open
            xml += create_xml_tag("label","style=\"error\"","Sorry, that file could not be found");
            WindowManager::go_to_window("employee_add_product_by_file",xml);
            return;
        }

        //if it's all good to go
        int pre_size = products->getSize();

        products->loadPrimary(file_name);
        products_secondary->loadSecondary(file_name);

        int num_new = products->getSize() - pre_size;

        xml += create_xml_tag("label","added " + num_new + " products.");


    } else if(name == "employee_remove_product"){

    	vector<string> productsV = products->printListToString();
    	create_db_list_xml(productsV,xml,"employee_remove_product_confirm","remove_product","remove");

    } else if(name == "remove_product"){

    	string make_and_model = optionsMap["value"];

    	size_t pos = make_and_model.find('`');
    	string make = make_and_model.substr(0,pos);
    	string model = make_and_model.substr(pos+1);

    	string_find_and_replace("`"," ",model);

    	Product pSearch(make,model,0,0,0,0);

    	xml += "<hr>\n";
    	xml += "<vbox homogeneous=\"true\">\n";
    	xml += create_xml_tag("label", "make: " + products->find(pSearch)->getMake());
    	xml += create_xml_tag("label", "model: " + products->find(pSearch)->getModel());
        string screenSize = to_string(products->find(pSearch)->getScreenSize());
        vector<string> v = string_split(screenSize,'.');
        screenSize = v[0] + "." + v[1][0] + " in.";
    	xml += create_xml_tag("label", "screen size: " + screenSize);
    	xml += create_xml_tag("label", "cpu Gen: " + to_string(products->find(pSearch)->getCpuGen()) + "th gen");
    	xml += create_xml_tag("label", "year: " + to_string(products->find(pSearch)->getYear()));
    	xml += create_xml_tag("label", "price: $" + to_string((int)products->find(pSearch)->getPrice()) + ".00");
    	xml += "</vbox>\n";
    	xml += "<hr>\n";
        string_find_and_replace(" ","`",model);
        string value = make + "`" + model;
        xml += create_xml_tag("entry","type=\"hidden\" value=\""+value+"\"","values");

    } else if(name == "remove_product_confirm"){

        string make_and_model = gtk_entry_get_text(GTK_ENTRY(entries["values"]));

        size_t pos = make_and_model.find('`');
        string make = make_and_model.substr(0,pos);
        string model = make_and_model.substr(pos+1);

        string_find_and_replace("`"," ",model);

        Product p(make,model,0,0,0,0);
        products->remove(p);

        ProductS ps(make,model,0,0,0,0);
        products_secondary->remove(ps);

    } else if(name == "employee_db_search"){

        string value = optionsMap["value"];

        if(value == "comp_name"){
            xml += create_xml_tag("title","List database of products by: Company name");
            xml += "<hr>\n";
            vector<string> productsV = products->printListToString();
            create_db_list_xml(productsV,xml);

        } else if(value == "price"){


        } else if(value == "model"){
            xml += create_xml_tag("title","List database of products by: Model name");
            xml += "<hr>\n";
            vector<string> productsV = products_secondary->printListToString();
            create_db_list_xml(productsV,xml);
        }

    } else if(name == "unsorted_customer_information"){

        stringstream customersSS;

        customers->displayCustomer(customersSS);

        create_customer_list_xml(xml, customersSS);

    } else if(name == "view_customer"){
        string username = optionsMap["value"];

        Customer* c = customers->customerSignIn(username);

        if(c != NULL){
            xml += create_xml_tag("title","View orders for " + c->getFirstname());
            xml += "<hr>\n";
            create_purchase_history_xml(xml, c);

        } else {
            xml += create_xml_tag("title","Customer not found!");
            cerr << "Customer \"" << username << "\" not found!" << endl;
        }

    } else if(name == "employee_view_orders") {

        string orders = priority_queue->printSorted();

        //cout << "orders: " << endl << orders << endl;

        stringstream ordersSep(orders);

        string title;
        string order_str;

        getline(ordersSep,title);

        //cout << title << endl;

        string width = "width=\"100\"";

        int index = 1;
        xml += "<hbox>\n";
        xml += create_xml_tag("label",width,"Number");
        xml += create_xml_tag("label",width,"Price");
        xml += create_xml_tag("label",width,"Arrive by:");
        xml += create_xml_tag("label",width,"Status");
        xml += create_xml_tag("label",width,""); //empty slot for ship button to go
        xml += "</hbox>\n";

        xml += "<placeholder>\n";


        while(getline(ordersSep,order_str)){

            xml += "<hbox homogeneous\"false\">\n";

            //get each order in the queue
            stringstream orderSep(order_str);

            string item;

            xml += create_xml_tag("label","width=\"50\"",to_string(index));

            while(getline(orderSep,item,',')){// price,ship date, status

                xml += "<vr>\n";
                xml += create_xml_tag("label",width,item);
            }

            if(item == "Waiting to be shipped"){
                xml += "<vr>\n";
                xml += create_xml_tag("button","options=\"link:employee_confirm_ship_order,name:preship,value:"+to_string(index)+"\"","Ship Order");
            }

            xml += "</hbox>\n";
            xml += "<hr>\n";
            index++;
        }

        if(index > 8){
            string_find_and_replace("<placeholder>\n","<scroll>\n<vbox>\n",xml);
            xml += "</vbox>\n";
            xml += "</scroll>\n";
        } else {
            string_find_and_replace("<placeholder>\n","",xml);
        }

    } else if(name == "send_feedback"){

        ofstream of;
        of.open("customer_feedback.txt",ios_base::app);

        string comment = gtk_entry_get_text(GTK_ENTRY(entries["comment"]));

        of << user->getFirstname() << " " << user->getLastname() << endl;
        of << user->getUsername() << endl;
        of << comment << endl << endl;

        of.flush();
        of.close();

    }
    if(optionsMap["link"] != "stay"){
        WindowManager::go_to_window(optionsMap["link"],xml); //go to the new window
    }

}

string Window::create_xml_tag(string tag, string text){

    string xml;
    xml += "<" + tag + ">\n";
    xml += text + "\n";
    xml += "</" + tag + ">\n";
    return xml;
}

string Window::create_xml_tag(string tag, string options, string text){

    string xml;
    xml += "<" + tag + " " + options + ">\n";
    xml += text + "\n";
    xml += "</" + tag + ">\n";
    return xml;
}

gboolean Window::delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) { //called when close window red button is pressed at app level

    if(WindowManager::get_current_window_id() == "end_screen") {
        gtk_main_quit();
        return TRUE;
    } else {

        WindowManager::go_to_window("end_screen","");
        //WindowManager::run_pbar();
        return FALSE;
    }
}

void Window::destroy(GtkWidget* widget, gpointer data) { //called from regular buttons

    gtk_widget_destroy(widget);
}

void Window::increase_pbar() {

    gdouble frac = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(pbar));
    frac += 0.1;
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar),frac);

}

void Window::set_icon(string path) {

    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(path.c_str(), &error);

    if (!pixbuf) {

        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }

    icon = pixbuf;

}

void Window::assign_pointers(Heap* heap, HashTable<Customer>* _customers, HashTable<Employee>* _employees, BST<Product>* _products, BST<ProductS>* _products_secondary) {

    priority_queue = heap;
    customers = _customers;
    employees = _employees;
	products = _products;
	products_secondary = _products_secondary;

    //g_print("pointers assigned\n");
}

void Window::create_db_list_xml(vector<string> productsV, string &xml, string link, string name, string text, bool glink){

	string size = "width=\"100\"";
	string index_options = "width=\"50\" justify=\"center\"";

	xml += "<vbox>\n";
	xml += "<hbox homogeneous=\"false\">\n";
	xml += create_xml_tag("label",size,"Number"); //index
	xml += create_xml_tag("label",size,"Company"); //manf comp
	xml += create_xml_tag("label",size,"Model"); //model
	xml += create_xml_tag("label",size,"Screen Size"); //screen size
	xml += create_xml_tag("label",size,"CPU Gen"); //cpu gen
	xml += create_xml_tag("label",size,"Year"); //year
	xml += create_xml_tag("label",size,"Price"); //price
	xml += "</hbox>\n";

	if(productsV.size() > 9){
        if(glink){
            xml += "<scroll columns=\"9\" " + size + ">\n";
        } else {
            xml += "<scroll columns=\"8\" " + size + ">\n";
        }

		xml += "<vbox>\n";
	}

	string attribute;
	string make;

	for (int i = 0; i < productsV.size(); ++i) {
		stringstream product(productsV.at(i));

	    xml += "<hbox homogeneous=\"false\">\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",index_options,attribute); //index

	    xml += "<vr>\n";

	    getline(product,make,',');
	    xml += create_xml_tag("label",size,make); //manf comp

	    xml += "<vr>\n";

	    string model;
	    getline(product,model,',');
	    xml += create_xml_tag("label",size,model); //model

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute+" in."); //screen size

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute+"th gen"); //cpu gen

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute); //year

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,"$"+attribute+".00"); //price

	    string_find_and_replace(" ","`",model);

		xml += "<vr>\n";

	    xml += create_xml_tag("button","options=\"link:" + link + ",name:" + name + ",value:" + make + "`" + model + "\"",text);

        if(glink){

            xml += "<vr>\n";
            xml += create_xml_tag("button","stay=\"true\" options=\"link:stay,name:open,value:" + make + "`" + model + "\"","Search on web");

        }

	    xml += "</hbox>\n";
	    xml += "<hr>\n";

	}

	if (productsV.size() > 9) {
		xml += "</vbox>\n";
		xml += "</scroll>\n";
	}

	xml += "</vbox>\n";

}

void Window::create_db_list_xml(vector<string> productsV, string &xml){ //no buttons

	string size = "width=\"100\"";
	string index_options = "width=\"50\" justify=\"center\"";

	xml += "<vbox>\n";
	xml += "<hbox homogeneous=\"false\">\n";
	xml += create_xml_tag("label","width=\"70\"","Number"); //index
	xml += create_xml_tag("label",size,"Company"); //manf comp
	xml += create_xml_tag("label",size,"Model"); //model
	xml += create_xml_tag("label",size,"Screen Size"); //screen size
	xml += create_xml_tag("label",size,"CPU Gen"); //cpu gen
	xml += create_xml_tag("label",size,"Year"); //year
	xml += create_xml_tag("label",size,"Price"); //price
	xml += "</hbox>\n";



	xml += "<scroll columns=\"7\" " + size + ">\n";
	xml += "<vbox>\n";
	string attribute;

	for (int i = 0; i < productsV.size(); ++i) {
		stringstream product(productsV.at(i));

	    xml += "<hbox homogeneous=\"false\">\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",index_options,attribute); //index

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute); //manf comp

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute); //model

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute+" in."); //screen size

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute+"th gen"); //cpu gen

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,attribute); //year

	    xml += "<vr>\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",size,"$"+attribute+".00"); //price

	    xml += "</hbox>\n";
	    xml += "<hr>\n";

	}

	xml += "</vbox>\n";
	xml += "</scroll>\n";
	xml += "</vbox>\n";

}

void Window::create_view_cart_xml(string& xml){

    Customer* c = static_cast<Customer*>(user);

    string active = c->printActive();

    stringstream orderSS(active);

    xml += create_xml_tag("title","Order Summary:");
    xml += "<hr>\n";

    string summary;
    getline(orderSS,summary); //get the order summary line

    //split it up
    stringstream price_sep(summary);

    string price;

    getline(price_sep,price,' '); //skip "active"
    getline(price_sep,price,' '); //skip "Order: "
    getline(price_sep,price,','); //this should now contain the price

    if(price == "0.00"){ //order is empty

        xml += create_xml_tag("label","Your cart is currently empty");

        return;
    }

    price = "$"+price;

    xml += "<hbox>\n";
    xml += create_xml_tag("label","Total Price:");
    xml += create_xml_tag("label",price);
    xml += "</hbox>\n";
    xml += "<hr>\n";

    string size = "width=\"80\"";
    string number_size = "width=\"50\" justify=\"center\"";



    create_order_laptop_list_xml(orderSS,size,number_size,xml);


    xml += create_xml_tag("button","options=\"link:customer_checkout\"","Checkout");

}

void Window::create_order_laptop_list_xml(stringstream& orderSS,string size,string number_size,string& xml,bool isCart){

    size_t start;
    size_t end_pos;

    string product;

    xml += "<hbox>\n";
    xml += create_xml_tag("label",size,"Number");
    xml += create_xml_tag("label",size,"Comapny");
    xml += create_xml_tag("label",size,"Model");
    xml += create_xml_tag("label",number_size,"Qty.");
    xml += "</hbox>\n";

    xml += "<placeholder>\n";

    int count = 0;

    while(getline(orderSS,product)){ //loop through each product in the cart

        if(product == "") break;

        count++;
        start = product.find("#");
        end_pos = product.find(":"); // get the number

        string number = product.substr(start+1,end_pos-1);

        xml += "<hr>\n";
        xml += "<hbox>\n";
        xml += create_xml_tag("label",number_size,number);
        xml += "<vr>\n";

        start = product.find(" ");

        stringstream product_info(product.substr(start+1));

        string token;

        getline(product_info,token,','); //company
        xml += create_xml_tag("label",size,token);
        xml += "<vr>\n";
        getline(product_info,token,','); //model
        xml += create_xml_tag("label",size,token);
        xml += "<vr>\n";
        getline(product_info,token,','); //Qty.
        xml += create_xml_tag("label",number_size,token);

        if(not user->getIsEmployee()){ //if the current user is a customer then show the remove option
            if(isCart){
                xml += "<vr>\n";
                string options = "options=\"link:customer_view_cart,name:customer_view_cart,action:remove,value:" + to_string(count) + "\"";
                //cout << "options:" << options << endl;
                xml += create_xml_tag("button",options,"remove");
            }
        }



        xml += "</hbox>\n";
    }

    if(count > 8){
        string_find_and_replace("<placeholder>\n","<scroll width=\"420\">\n<vbox>\n",xml); //blaze
        xml += "</vbox>\n";
        xml += "</scroll>\n";
    } else {
        string_find_and_replace("<placeholder>\n","",xml);
    }

}

void Window::create_purchase_history_xml(string& xml){

    Customer* c = static_cast<Customer*>(user);
    create_purchase_history_xml(xml, c);

}

void Window::create_purchase_history_xml(string& xml, Customer* c){

    //g_print("%s",g_strconcat("placing order for: ",c->getFirstname().c_str(),"\n",NULL));

    string orders = c->getOrder();

    if(orders == ""){
        xml += create_xml_tag("label","No orders have been placed yet");
        return;
    }

    //g_print("%s",g_strconcat("orders: ",orders.c_str(),"\n",NULL));

    stringstream orderSS(orders);

    string order_str;
    int index = 1;

    string size = "width=\"100\"";
    string number_size = "width=\"50\" justify=\"center\"";

    xml += "<hbox>\n";
    xml += create_xml_tag("label",number_size,""); // index
    xml += create_xml_tag("label",size,"Price:");
    xml += create_xml_tag("label",size,"Arrive By:");
    xml += create_xml_tag("label",size,"Shipping Status:");
    xml += "</hbox>\n";

    while(getline(orderSS,order_str)){

        size_t pos = order_str.find(" ");
        string orderHex = order_str.substr(pos+1); //get the address hex value
        stringstream hex_convert;
        hex_convert << orderHex;
        long order_address;
        hex_convert >> hex >> order_address; //convert hex into long
        Order* o = reinterpret_cast<Order*>(order_address); //reinterpret cast that sob and store it in a pointer

        order_str = o->print(); //get the order information

        vector<string> orderV = string_split(order_str);
        orderV.at(0) = "$" + orderV.at(0);

        xml += "<hr>\n";
        xml += "<hbox>\n";
        xml += create_xml_tag("label",number_size,to_string(index));
        for(int i = 0; i < orderV.size(); i++){
            xml += "<vr>\n";
            xml += create_xml_tag("label",size,orderV[i]);
        }

        xml += "<vr>\n";
        string options = "options=\"link:view_order_details,name:view_order_details,value:" + orderHex + "\"";
        xml += create_xml_tag("button",options,"view details");


        xml += "</hbox>\n";
        index++;

    }

}

void Window::create_customer_list_xml(string& xml, stringstream& customersSS){

    string width = "width=\"100\"";
    string zip_width = "width=\"40\"";

    xml += "<hbox homogeneous=\"false\">\n";
    xml += create_xml_tag("label",zip_width,"     ");
    xml += create_xml_tag("label",width,"First Name");
    xml += create_xml_tag("label",width,"Last Name");
    xml += create_xml_tag("label",width,"Address");
    xml += create_xml_tag("label",width,"City");
    xml += create_xml_tag("label",width,"Email");
    xml += create_xml_tag("label",width,"Zip");
    xml += "</hbox>\n";

    xml += "<placeholder>\n";

    string line;
    int count = 0;
    while(getline(customersSS,line,'\n')){
        if(line[0] == '#') continue;
        string field;
        xml += "<hr>\n";
        xml+= "<hbox>\n";
        bool isFirst = true;
        stringstream customer(line);
        int index = 0;
        string username;
        while(getline(customer,field,',')){

            xml += "<vr>\n";
            if(is_number(field)){ // if it's a number
                xml += create_xml_tag("label",zip_width,field);
            } else {
                xml += create_xml_tag("label",width,field);
            }
            if(index == 4){
                username = field;
                //cout << username << endl;
            }

            index++;
        }

        xml += "<vr>\n";
        xml += create_xml_tag("button","options=\"link:employee_search_customer_results,value:" + username + ",name:view_customer\"","view orders");
        xml += "</hbox>\n";
        count ++;
    }
    if(count > 8){
        string_find_and_replace("<placeholder>\n","<scroll columns=\"7\" " + width + ">\n<vbox>\n",xml);
        xml += "</vbox>\n";
        xml += "</scroll>\n";
    } else {
        string_find_and_replace("<placeholder>\n","",xml);
    }
}

void Window::string_find_and_replace(string find, string replace, string &subject){

	string::size_type n = 0;
	while( (n = subject.find(find,n)) != string::npos){

		subject.replace(n,find.size(), replace);
		n += replace.size();
	}

}

vector<string> Window::string_split(const string &input, char delim){

	vector<string> v;
	stringstream ss(input);
	string token;
	while(getline(ss,token,delim)){v.push_back(token);}
	return v;

}

string Window::to_lower(string str){ //Lifted from cplusplus.com http://www.cplusplus.com/reference/locale/tolower/
	string output;
	locale loc;
	for (string::size_type i=0; i<str.length(); ++i){
		output += tolower(str[i],loc);
	}
    return output;
}

string Window::vector_join(const vector<string> &v, const char* const delim){ //Lifted from SO: https://stackoverflow.com/questions/5288396/c-ostream-out-manipulation/5289170#5289170

	switch(v.size()){
		case 0:
			return "";
		case 1:
			return v[0];
		default:
			ostringstream ss;
			copy(v.begin(), v.end()-1, ostream_iterator<string>(ss, delim));
			ss << *v.rbegin();
			return ss.str();
	}
}

bool Window::is_number(const string& s) {
    int i;
    bool decimal = false;
    for(i = 0; i < s.length(); i++){
        if(!isdigit(s[i])){
            if(s[i] == '.' && !decimal){
                decimal = true;
            } else {
                break;
            }
        }
    }
    return !s.empty() && i == s.length();
}
