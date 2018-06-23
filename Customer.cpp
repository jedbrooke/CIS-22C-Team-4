#include "Customer.h"
#include <iostream>
#include "Order.h"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Order;
Customer::Customer() {
	username = "";
	password = "";
	firstname = "";
	lastname = "";
	isEmployee = false;
	address = "";
	city = "";
	zip = 0;
	email = "";
	r = NULL;
}

Customer::Customer(string username, string password, string firstName,
		string lastName, bool isEmployee, string address, string city,
		unsigned zip, string email) {
	this->username = username;
	this->password = password;
	this->firstname = firstName;
	this->lastname = lastName;
	this->isEmployee = isEmployee;
	this->address = address;
	this->city = city;
	this->zip = zip;
	this->email = email;
	r = NULL;
}

string Customer::getAddress() const {
	return address;
}

string Customer::getCity() const {
	return city;
}

unsigned Customer::getZip() const {
	return zip;
}

string Customer::getEmail() const {
	return email;
}

void Customer::setAddress(string address) {
	this->address = address;
}

void Customer::setCity(string city) {
	this->city = city;
}

void Customer::setZip(unsigned zip) {
	this->zip = zip;
}

void Customer::setEmail(string email) {
	this->email = email;
}

string Customer::getOrder() const {
	stringstream out;
	orders.displayNumberedList(out);
	return out.str();
}
/*
 void Customer::insertOrder() { //storing list of past order (Shipped);
 if (r->isPlaced()) {
 orders.insertStop(*r);
 }

 Order r;
 r.addLaptop(p);
 orders.insertStop(r);
 }
 */

bool Customer::operator==(const Customer& customer) {
	return (username == customer.username);
}

bool Customer::operator<(const Customer& customer) {
	if (firstname < customer.firstname)
		return true;
	else if (firstname == customer.firstname) {
		if (lastname < customer.lastname)
			return true;
		else if (lastname == customer.lastname) {
			if (username < customer.username)
				return true;
			else if (username == customer.username) {
				if (password < customer.password)
					return true;
				else
					return false;
			} else
				return false;
		} else
			return false;
	} else
		return false;
}

bool Customer::operator>(const Customer& customer) {
	if (firstname > customer.firstname)
		return true;
	else if (firstname == customer.firstname) {
		if (lastname > customer.lastname)
			return true;
		else if (lastname == customer.lastname) {
			if (username > customer.username)
				return true;
			else if (username == customer.username) {
				if (password > customer.password)
					return true;
				else
					return false;
			} else
				return false;
		} else
			return false;
	} else
		return false;
}

void Customer::read(ifstream& in) {
	string temp;
	bool temp1;
	unsigned temp2;

	in >> temp;
	username = temp;
	in >> temp;
	password = temp;
	in >> temp;
	firstname = temp;
	in >> temp;
	lastname = temp;
	in >> temp1;
	isEmployee = temp1;
	getline(in, temp);
	address = temp;
	in >> temp;
	city = temp;
	in >> temp2;
	zip = temp2;
	in >> temp;
	email = temp;

	while (in.peek() == '\n')
		in.get();
}

void Customer::write(ostream& out) {
	out << username << '\n';
	out << password << '\n';
	out << firstname << '\n';
	out << lastname << '\n';
	out << isEmployee << '\n';
	out << address << '\n';
	out << city << '\n';
	out << zip << '\n';
	out << email << '\n';
	orders.startIterator();
	while (!orders.offEnd()) {
		out << orders.getIterator().getPrice() << endl;
		out << orders.getIterator().isPlaced() << endl;
		out << orders.getIterator().getDayPlaced() << endl;
		out << orders.getIterator().getShippingSpeed() << endl;
		out << orders.getIterator().isShipped() << endl;
		orders.moveIterNext();
	}
	out << "End";
}

ostream& operator<<(ostream& out, const Customer& customer) {
	stringstream os;
	customer.orders.displayNumberedList(os);
//out << customer.r->printDetailed();
	out << customer.getFirstname() << "," << customer.getLastname() << ","
			<< customer.getAddress() << "," << customer.getCity() << ","
			<< customer.getEmail() << "," << customer.getZip() << '\n';
	out << os.str();
	return out;
}

string Customer::toString() { //return a string with customer's data.
	stringstream ss;
	ss << firstname << "," << lastname << "," << address << "," << city << ","
			<< zip << "," << email;
	return ss.str();
}

string Customer::displayCustomer() {
	stringstream out;
	out << "\nFirst name: " << firstname << "\nLast name: " << lastname
			<< "\nAddress:  " << address << endl;
	return out.str();
}

void Customer::activeOrder(Order *p) {

	r = p; 	//point activeORder to the order passed in.
}

string Customer::printActive() {
	stringstream out;
	out << "Active Order: " << r->printDetailed();
	return out.str();
}

void Customer::addToProduct(Product* p) {
	r->addLaptop(p);

}

void Customer::removeProduct(int index) {
	assert(!r->isPlaced());
		r->removeLaptop(index - 1);
}

void Customer::placeOrder() {
		orders.insertStop(*r); //add order to list 
}

