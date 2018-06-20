/*
 * Order.h
 * Andrew Maxwell
 */

#ifndef ORDER_H_
#define ORDER_H_

#include "BST.h"
#include "SubOrder.h"
#include "Customer.h"
#include <ctime>
using namespace std;

class Customer;

class Order {
	
private:
	Customer * customer;
	List<subOrder> laptops;
	int shippingSpeed;
	time_t timePlaced, arriveBy;
	bool placed, shipped;
	float price;
	
public:
	
	/** constructors */

	Order();

	Order(Customer * customer);

	Order(istream &in, BST <Product> &products, Customer * customer);

	/** getters */

	string getArriveBy() const;
	//returns the date that the order should arrive, determined based on day order is placed and shipping speed

	string getDayPlaced() const;
	//returns the date the order was placed

	int getShippingSpeed() const;
	//returns the shipping speed

	float getPrice() const;
	//returns the total price of all of the items.

	bool isPlaced() const;
	//returns whether the order has been placed or not

	bool isShipped() const;
	//returns whether the order has been shipped. If the order has been shipped, no further modification is allowed.
	bool isDelivered() const;

	/** setters */

	void ship();
	//sets the order to shipped. Should only be called by Heap, not manually.

	void addLaptop(Product * newLaptop);
	//Adds a new laptop. If laptop matches existing laptop, increment by 1. Changes price of order.
	//Pre: !isShipped
	
	void addLaptop(string laptopKey);

	void removeLaptop(int index);
	//removes a laptop from the list, by index. Changes price of order.
	//Pre: !isShipped
	//Pre: Index < length of list
	//(check for these before calling the function, so that you can display a user-friendly error message)

	void setQuantity(int index, int quant);
	//changes the quantity variable for laptop at index. If quantity is 0, removes laptop.

	void placeOrder(int daysToShip);
	//places the order; sets it as ready to ship. Should only be called by Heap, not manually.

	bool operator>(const Order&);
	//Compares orders based on when they need to ship. Used for priority queue.

	bool operator<(const Order&);

	bool operator>=(const Order&);

	bool operator<=(const Order&);

	string print();

	string printDetailed();

	void save(ostream & out);

	Order * load(istream & in, BST<Product> & products);
};


#endif /* ORDER_H_ */
