/*
 * SubOrder.h
 * Andrew Maxwell
 */

#ifndef SRC_SUBORDER_H_
#define SRC_SUBORDER_H_

#include "Product.h"

struct subOrder {
	Product * laptop;
	int quantity;
	float price;
	subOrder();					//Default constructor

	subOrder(Product * toBuy);	//Constructor

	void setQuantity(int q);	//Changes the number of laptops

	int getQuantity();

	friend ostream & operator<<(ostream & out, const subOrder& SO);

	bool operator==(const subOrder &rhs);
};

#endif /* SRC_SUBORDER_H_ */
