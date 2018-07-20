/*
 * Order.cpp
 * Andrew Maxwell
 */

#include "Product.h"
#include "Order.h"
#include <assert.h>
#include <iomanip>
#include <sstream>
using namespace std;

	/** constructors */

	Order::Order() {
		shippingSpeed = price = 0;
		placed = shipped = false;
		timePlaced = arriveBy = 0;
		customer = NULL;
	}

	Order::Order(Customer * owner) {
		shippingSpeed = price = 0;
		placed = shipped = false;
		timePlaced = arriveBy = 0;
		customer = owner;
	}

	Order::Order(istream &in, BST<Product> &products, Customer * owner) {
		load(in, products);
		customer = owner;
	}

	/** management functions - getters and setters*/

	string Order::getArriveBy() const {
		tm * arriveByTm = localtime(&arriveBy);
		char * timeString = new char[25];
		strftime(timeString, 25, "%A %B %d", arriveByTm);
		return timeString;
	}
	//returns the date that the order should arrive, determined based on day order is placed and shipping speed, as a string

	string Order::getDayPlaced() const {
		tm * timePlacedtm = localtime(&timePlaced);
		char * timeString = new char[25];
		strftime(timeString, 25, "%A %B %d", timePlacedtm);
		return timeString;
	}
	//returns the date the order was placed as a string

	int Order::getShippingSpeed() const {
		return shippingSpeed;
	}
	//returns the shipping speed

	float Order::getPrice() const {
		return price;
	}

	bool Order::isPlaced() const {
		return placed;
	}
	//returns whether the order has been placed or not

	bool Order::isShipped() const {
		return shipped;
	}
	//returns whether the order has been shipped. If the order has been shipped, no further modification is allowed.

	bool Order::isDelivered() const {
		return (shipped and (time(NULL) > arriveBy));
	}

	void Order::ship() {
		shipped = true;
	}
	//sets the order to shipped.

	void Order::addLaptop(Product * newLaptop) {
		assert(!placed);
		subOrder newLT(newLaptop);
		int index = laptops.linearSearch(newLT);
		if (index > -1) {
			laptops.moveToIndex(index);
			setQuantity(index - 1, laptops.getIterator().getQuantity() + 1);
		} else {
			laptops.insertStop(newLT);
			price += newLT.price;
		}
	}
	//Adds a new laptop. If laptop matches existing laptop, increment by 1.
	//Pre: !placed

	void Order::removeLaptop(int index) {
		assert(!placed);
		assert(index <= laptops.getLength());
		assert(index > 0);
		laptops.moveToIndex(index);
		price -= laptops.getIterator().price;
		laptops.removeIterator();
	}
	//removes a laptop from the list, by index
	//Pre: !Placed
	//Pre: Index < length of list
	//(check for these before calling the function, so that you can display a user-friendly error message without crashing the program)

	void Order::setQuantity(int index, int quant) {
		assert(!placed);
		assert(quant >= 0);
		assert(index < laptops.getLength());
		laptops.moveToIndex(index);
		price -= laptops.getIterator().price;
		if (quant > 0) {
			subOrder tempSO = laptops.getIterator();
			tempSO.setQuantity(quant);
			price += tempSO.price;
			laptops.insertIterator(tempSO);
		}
		laptops.removeIterator();
	}
	//Pre: !Placed
	//Pre: Index < length of list
	//Pre: Quantity is positive or 0
	//changes the quantity variable for laptop at index + updates the price

	void Order::placeOrder(int daysToShip) {
		assert(!laptops.isEmpty());
		timePlaced = time(NULL);
		arriveBy = timePlaced;
		arriveBy += 86400 * daysToShip;
		shippingSpeed = daysToShip;
		placed = true;
		customer->placeOrder();
	}
	//places the order; sets it as ready to ship; sets value of timePlaced and arriveBy.

	bool Order::operator>(const Order& order) {

		if (!shipped and order.shipped) {
			return true;
		}
		else if ((!shipped and !order.shipped) and arriveBy/86400 < order.arriveBy/86400) {
			return true;
		} else {
			return false;
		}
	}
	//returns true if the first order is higher priority. That is, compares priority; item on left is greater priority.

	bool Order::operator<(const Order& order) {
		if (shipped and !order.shipped) {
			return true;
		}
		else if ((!shipped and !order.shipped) and arriveBy/86400 > order.arriveBy/86400) {
			return true;
		} else {
			return false;
		}
	}

	bool Order::operator>=(const Order& order) {
		if (order.shipped) {
			return true;
		} else if (shipped and !order.shipped) {
			return false;
		} else {
			return(arriveBy/86400 >= order.arriveBy/86400);
		}
	}

	bool Order::operator<=(const Order& order) {
		if (shipped) {
			return true;
		} else if (!shipped and order.shipped) {
			return false;
		} else {
			return(arriveBy/86400 <= order.arriveBy/86400);
		}
	}

	string Order::print() {	//Prints basic information about the order, including where to ship, etc.
		stringstream out;
		out << fixed << setprecision(2) << price;
		if (placed) {
			out << "," << getArriveBy() << ",";
			if (shipped) {
				if (isDelivered()) {
					out << "Delivered";
				} else {
					out << "En route";
				}
			} else {
				out << "Waiting to be shipped";
			}
		} else {
			out << ",N/A,Not Yet Placed";
		}
		return out.str();
	}

	string Order::printDetailed() {	//Prints above information + also the list of all laptops.
		stringstream out;
		out << print() << endl;
		//out << "\n" << *customer;
		laptops.displayNumberedList(out);
		return out.str();
	}

	void Order::save(ostream & out) {	//Prints out all information in format for load() to read
		out << shippingSpeed << "\t";
		out << price << "\t";
		out << placed << "\t";
		out << shipped << "\t";
		out << timePlaced << "\t";
		out << arriveBy << endl;
		laptops.startIterator();
		while (!laptops.offEnd()) {
			out << laptops.getIterator().laptop -> getMake() << endl;
			out << laptops.getIterator().laptop -> getModel() << endl;
			out << laptops.getIterator().quantity << endl;
			laptops.moveIterNext();
		}
		out << "end" << endl;
	}

	Order * Order::load(istream & in, BST<Product> & products) {	//reads in information from an input.
		int quantity = 0;
		string make = "", model, input;
		getline(in, input);
		stringstream getValue(input);
		getValue >> shippingSpeed;
		getValue >> price;
		getValue >> placed;
		getValue >> shipped;
		getValue >> timePlaced;
		getValue >> arriveBy;
		getline(in, make);
		while (make != "end") {
			getline(in, model);
			Product dummyProduct(make, model, 0, 0, 0, 0);
			subOrder newSO (products.find(dummyProduct));
			getline(in, input);
			stringstream getInt(input);
			getInt >> quantity;
			newSO.setQuantity(quantity);
			laptops.insertStop(newSO);
			getline(in, make);
		}
		if (placed and !shipped) {
			return this;
		} else {
			return NULL;
		}
	}

	ostream& operator<<(ostream& out, const Order& order) {
		out <<
				"\nOrder's Info: " <<
				"\nPrice: $" << order.getPrice()<<
				"\nOrder Placed: " <<order.isPlaced()<<
				"\nDate placed: " << order.getDayPlaced() <<
				"\nArrive By: " << order.getArriveBy()<<
				"\nShipping speed: "<<order.getShippingSpeed() << endl;
		order.laptops.displayNumberedList(out);
		return out;

	}
