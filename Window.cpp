/*
 * Window.cpp
 *
 *  Created on: Jun 2, 2018
 *      Author: Jasper
 */

#include "Window.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <gtk/gtk.h>
//#include "Customer.h"

using namespace std;


//static variables
GdkPixbuf* Window::icon;
map<string, GtkWidget*> Window::entries;
Heap* Window::priority_queue;
BST<Customer>* Window::customers;
BST<Product>* Window::products;
//Customer customer;


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
        tag = tag.substr(1, tag.length()-2); //get rid of the <>
        size_t pos = tag.find(" ");
        string tagName = tag.substr(0, pos); //get the tag name
        string options = tag.substr(pos+1); //get the options
        
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
        
        if(tagName == "variable") { //skip unassigned variable tag
            
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

        	//make the window bigger
        	gtk_widget_set_size_request (scroll_window, 1500, 300);

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

        } else if(tagName == "/hbox" || tagName == "/vbox" || tagName == "/scroll") {

            string box_name = g_strconcat(G_OBJECT_TYPE_NAME(boxes.at(boxes.size()-2)),NULL);
        	string window_name = "GtkScrolledWindow";
        	if( box_name == window_name) {
            	//pack it into the scroll box
            	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (boxes.at(boxes.size()-2)), boxes.at(boxes.size()-1));
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
        
        if(boxes.size() > 1) {
            create_content(tagName,text,optionsMap,boxes.at(boxes.size()-1));
        } else {
            create_content(tagName,text,optionsMap,self_box);
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
        
        //connect it to the destroy event as well
        g_signal_connect_swapped(widget,"clicked",G_CALLBACK(destroy),self_window);

                
    } else if(tagName == "label") {

        //create new label
        widget = gtk_label_new(text.c_str());

        //set styles
        if(optionsMap["style"] == "error"){
        	//error markup
        	char* markup = g_strconcat("<span foreground=\"red\">", text.c_str(), "</span>", NULL);
        	gtk_label_set_markup(GTK_LABEL(widget), markup);
        	g_free(markup);
        }
        
        //set alignment
        gtk_misc_set_alignment(GTK_MISC(widget), 0, 0);
        
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
        g_print("%s",msg.c_str());
        
        widget = gtk_progress_bar_new();
        
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(widget),text.c_str());
        
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
    	g_print("%s",msg.c_str());

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
        
        gtk_main_quit();

    } else if(name == "customer_sign_in") {
        
        g_print("in customer_sign_in block\n");
        
        string email = gtk_entry_get_text(GTK_ENTRY(entries["email"]));
        string psw = gtk_entry_get_text(GTK_ENTRY(entries["psw"]));
        
        msg = "email: " + email + "\n";
        g_print("%s",msg.c_str());
        msg = "password: " + psw + "\n";
        g_print("%s",msg.c_str());
              
    } else if(name == "employee_login") {
        
        unsigned id = atoi(gtk_entry_get_text(GTK_ENTRY(entries["id"])));
        string psw = gtk_entry_get_text(GTK_ENTRY(entries["psw"]));
        
        msg = "id: " + to_string(id) + "\n";
        g_print("%s",msg.c_str());
        msg = "password: " + psw + "\n";
        g_print("%s",msg.c_str());
        
    } else if(name == "customer_create_new_account_1") {
        
        //get parameters
        string email = gtk_entry_get_text(GTK_ENTRY(entries["email"]));
        string conf_email = gtk_entry_get_text(GTK_ENTRY(entries["conf_email"]));
        string psw = gtk_entry_get_text(GTK_ENTRY(entries["psw"]));
        string conf_psw = gtk_entry_get_text(GTK_ENTRY(entries["conf_psw"]));
        
        //time to check
        if(email != conf_email || psw != conf_psw){
        	if(email != conf_email){
        		xml += create_xml_tag("label","style=\"error\"","error: emails must match");
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

        } else {
        	string value = email + "`" + psw; 
        	xml += create_xml_tag("entry","type=\"hidden\" value=\""+value+"\"","values");

        }
            
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
    	unsigned zip = atoi(values["zip_str"].c_str());


    	map<string,string>::iterator it;

    	for(it = values.begin(); it != values.end(); it++){

    		msg = it->first + ": " + it->second + "\n";
    		g_print("%s",msg.c_str());
    	}


    	if(values["fname"] == "" || values["lname"] == "" || values["address"] == "" || values["phone_num"] == "" || values["city"] == "" || values["zip_str"] == ""){//if any of the fields are blank, reject
    		xml += create_xml_tag("label","style=\"error\"","error: please do not leave any fields blank");
    		string value = values["email"] + "`" + values["psw"]; 
    		xml += create_xml_tag("entry","type=\"hidden\" value=\""+value+"\"","values");

    		WindowManager::go_to_window("customer_create_new_account_cont",xml);
    		return;

    	} else {
    		//Customer c(email,psw,fname,lname,false,address,city,zip,email);
    		//customers->insert(c);
    	}

    } else if(name == "customer_db_search"){
        
        string value = optionsMap["value"];
        
        if(value == "comp_name"){
            
            create_db_list_xml(xml,"customer_view_cart","add_to_cart","add to cart");
            
        } else if(value == "price"){
            
            
        }
        
    } else if(name == "add_to_cart"){

        //do a bunch of stuff

    } else if(name == "ship"){

        //ship(index)

    } else if (name == "employee_add_product") {
    	gtk_entry_get_text(GTK_ENTRY(entries["email"]));

    	string make = gtk_entry_get_text(GTK_ENTRY(entries["make"]));
    	string model = gtk_entry_get_text(GTK_ENTRY(entries["model"]));
    	string screenSize = gtk_entry_get_text(GTK_ENTRY(entries["screenSize"]));
    	string cpuGen = gtk_entry_get_text(GTK_ENTRY(entries["cpuGen"]));
    	string year = gtk_entry_get_text(GTK_ENTRY(entries["year"]));
    	string price = gtk_entry_get_text(GTK_ENTRY(entries["price"]));

    	Product p(make,model, atoi(screenSize.c_str()), atoi(cpuGen.c_str()), atoi(year.c_str()), atoi(price.c_str()));
    	products->insert(p);

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

    } else if(name == "employee_remove_product"){

    	create_db_list_xml(xml,"employee_remove_product_confirm","remove_product","remove");

    } else if(name == "remove_product"){

    	string make_and_model = optionsMap["value"];

    	msg = "value: " + make_and_model + "\n";

    	g_print("%s",msg.c_str());

    	size_t pos = make_and_model.find('`');
    	string make = make_and_model.substr(0,pos);
    	string model = make_and_model.substr(pos+1);

    	string_find_and_replace("`"," ",model);

    	g_print("%s",g_strconcat("make: ",make.c_str()," model: ", model.c_str(),"\n",NULL));

    	Product pSearch(make,model,0,0,0,0);

    	g_print("product made\n");

    	msg = "product:\n" + products->find(pSearch)->toString() + "\n";

    	g_print("%s",msg.c_str());

    	xml += "<hr>\n";
    	xml += "<vbox homogeneous=\"true\">\n";
    	xml += create_xml_tag("label", "make: " + products->find(pSearch)->getMake());
    	xml += create_xml_tag("label", "model: " + products->find(pSearch)->getModel());
    	xml += create_xml_tag("label", "screen size: " + to_string(products->find(pSearch)->getScreenSize()));
    	xml += create_xml_tag("label", "cpu Gen: " + to_string(products->find(pSearch)->getCpuGen()) + "th gen");
    	xml += create_xml_tag("label", "year: " + to_string(products->find(pSearch)->getYear()));
    	xml += create_xml_tag("label", "price: $" + to_string(products->find(pSearch)->getPrice()) + ".00");
    	xml += "</vbox>\n";
    	xml += "<hr>\n";

    	products->remove(pSearch);

    }
    
    /*else if(name == "employee_view_orders") {
       string orders = priority_queue.printSorted();

       stringstream ordersSep(orders);

       string order;

       xml += "<hbox homogeneous\"true\">\n";

       while(getline(ordersSep,order)){

            //get each order in the queue
            stringstream orderSep(order);

            string item;
            xml += "<scroll>"
            while(getline(orderSep,item,',')){

                xml += create_xml_tag("label",item);

            }
        }

        xml += "</hbox>";
    }*/
    
    /**
     @TODO
     - execute options based on if else to detect name and proceed accordingly
     (so we will still need the huge if-elif stack)
     [begun]
     - destroy this window [done]
     */
    
    WindowManager::go_to_window(optionsMap["link"],xml); //go to the new window
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

void Window::assign_pointers(Heap* heap, BST<Customer>* _customers, BST<Product>* _products) {
    
    //priority_queue = &heap;
    customers = _customers;
	products = _products;

    g_print("pointers assigned\n");    
}


void Window::create_db_list_xml(string &xml, string link, string name, string text){

	vector<string> productsV = products->printListToString();

	xml += "<vbox>\n";
	xml += "<hbox homogeneous=\"true\">\n";
	xml += create_xml_tag("label","number"); //index
	xml += create_xml_tag("label","company"); //manf comp
	xml += create_xml_tag("label","model"); //model
	xml += create_xml_tag("label","screen size"); //screen size
	xml += create_xml_tag("label","cpu gen"); //cpu gen
	xml += create_xml_tag("label","year"); //year
	xml += create_xml_tag("label","price"); //price
	xml += create_xml_tag("label"," "); //order column
	xml += "</hbox>\n";            

	xml += "<scroll>\n";
	xml += "<vbox>\n";
	string attribute;
	string make;

	for (int i = 0; i < productsV.size(); ++i) {
		stringstream product(productsV.at(i));

	    xml += "<hbox homogeneous=\"true\">\n";

	    getline(product,attribute,',');
	    xml += create_xml_tag("label",attribute); //index

	    getline(product,make,',');
	    xml += create_xml_tag("label",make); //manf comp
	    
	    string model;
	    getline(product,model,',');
	    xml += create_xml_tag("label",model); //model
	    
	    getline(product,attribute,',');
	    xml += create_xml_tag("label",attribute+" in."); //screen size
	    
	    getline(product,attribute,',');
	    xml += create_xml_tag("label",attribute+"th gen"); //cpu gen
	    
	    getline(product,attribute,',');
	    xml += create_xml_tag("label",attribute); //year
	    
	    getline(product,attribute,',');
	    xml += create_xml_tag("label","$"+attribute+".00"); //price

	    string_find_and_replace(" ","`",model);

	    xml += create_xml_tag("button","options=\"link:" + link + ",name:" + name + ",value:" + make + "`" + model + "\"",text);
	    
	    xml += "</hbox>\n";
	    xml += "<hr>\n";

	}
	
	xml += "</vbox>\n";
	xml += "</scroll>\n";
	xml += "</vbox>\n";

}

void Window::string_find_and_replace(string find, string replace, string &subject){

	string::size_type n = 0;
	while( (n = subject.find(find,n)) != string::npos){

		subject.replace(n,find.size(), replace);
		n += replace.size();
	}
}