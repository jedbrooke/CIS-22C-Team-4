//============================================================================
// Name        : BST_Driver.cpp
// Author      : vupham
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "BST.h"
#include "Product.h"
#include "ProductS.h"
using namespace std;
using namespace std;

const int MENU_SIZE = 8;

string intro();
void title();
void header();
int menu();
void choice1(BST<Product> bst_primary);
void choice2(BST<ProductS> bst_secondary);
void choice3(BST<Product> bst_primary);
void choice4(BST<ProductS> bst_secondary);
Product choice5(BST<Product> bst_primary);
Product choice6(BST<Product> bst_primary);
void choice7(BST<Product> bst_primary);
void choice8();
void clearScreen();		//pseudo-system("CLS") <- cause can't seem to work in Eclipse
void pressEnter();

int main() {
	BST<Product> bst_primary;		//will be sorted by primary key - make
	BST<ProductS> bst_secondary;	//will be sorted by secondary key - model
	Product tempP;
	ProductS tempS;
	int choice;

	string fname = intro();
	bst_primary.loadPrimary(fname);
	bst_secondary.loadSecondary(fname);

	do {

		choice = menu();
		switch(choice) {
		case 1: {
			choice1(bst_primary);
		} break;
		case 2: {
			choice2(bst_secondary);
		}break;
		case 3: {
			choice3(bst_primary);
		}break;
		case 4: {
			choice4(bst_secondary);
		}break;
		case 5: {
			tempP = choice5(bst_primary);	//pre: not in the list
			tempS = tempP;
			bst_primary.insert(tempP);
			bst_secondary.insert(tempS);
		}break;
		case 6: {
			tempP = choice6(bst_primary); 	//pre: in the list
			tempS = tempP;
			bst_primary.remove(tempP);
			bst_secondary.remove(tempS);
		}break;
		case 7: {
			choice7(bst_primary);
		}break;
		case 8: {
			choice8();
		}break;
		default: break;
		}

	}while (choice != MENU_SIZE);

	return 0;
}

string intro() {
	ifstream fin;
	string fname;
	bool valid;

	cout << "Welcome to BST-Product test program!\n\n";
	do {
		cout << "Please enter the name of the input file: ";
		cin >> fname;
		fin.open(fname);
		if (!fin.is_open()) {
			cout << "Invalid file name!\n\n";
		}
		else
			valid = true;
	} while (valid == false);

	fin.close();
	cout << "\nSuccess!\n";
	return fname;
}

void title() {
	cout << "********************************\n" <<
			"*                              *\n" <<
			"*       BST TEST PROGRAM       *\n" <<
			"*                              *\n" <<
			"********************************\n\n";
	return;
}

void header() {
	cout << "Index           Make            Model                           Screen size     CPU Gen         Year            Price\n"
	    << "                                                                (in.)           (Intel)                         ($)  \n"
	    << "---------------------------------------------------------------------------------------------------------------------\n";
	return;
}

int menu() {
	int choice;
	bool valid = false;

	while (valid == false) {
		clearScreen();
		title();
		cout << "What do you want to do?\n" <<
				"1. Display product list sorted by Make\n" <<
				"2. Display product list sorted by Model\n" <<
				"3. Search for product(s) by make name\n" <<
				"4. Search for product(s) by model name\n" <<
				"5. Add a new product\n" <<
				"6. Remove an existing product\n" <<
				"7. Save current list to file\n" <<
				"8. Quit\n\n" <<
				"Enter your choice: ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(50, '\n');
			cout << "\nPlease enter numbers not letters\n\n";
			pressEnter();
			valid = false;
		}
		else if (choice < 1 || choice > MENU_SIZE) {
			cout << "\nInvalid input.\n\n";
			pressEnter();
			valid = false;
		}
		else
			valid = true;
	}
	return choice;
}

void choice1(BST<Product> bst_primary) {
	clearScreen();
	title();
	cout << "-----------------------------------\n" <<
			"Display product list sorted by Make\n" <<
			"-----------------------------------\n\n";
	header();
	bst_primary.printList();
	pressEnter();
	return;
}
void choice2(BST<ProductS> bst_secondary) {
	clearScreen();
	title();
	cout << "------------------------------------\n" <<
			"Display product list sorted by Model\n" <<
			"------------------------------------\n\n";
	header();
	bst_secondary.printList();
	pressEnter();
	return;
}
void choice3(BST<Product> bst_primary) {
	string make;

	clearScreen();
	title();
	cout << "----------------------------------\n" <<
			"Search for product(s) by make name\n" <<
			"----------------------------------\n\n";
	cout << "Enter make name: ";
	cin.ignore(50, '\n');
	cin >> make;
	cout << "Below is a list of products that have the entered make name.\n";
	cout << "(NOTE: if the list is empty, there is no product with that make name...)\n\n";
	header();
	bst_primary.printByMake(make);
	pressEnter();
	return;
}
void choice4(BST<ProductS> bst_secondary) {
	string model;

	clearScreen();
	title();
	cout << "-----------------------------------\n" <<
			"Search for product(s) by model name\n" <<
			"-----------------------------------\n\n";
	cout << "Enter model name: ";
	cin.ignore(50, '\n');
	getline(cin, model);
	cout << "Below is a list of products that have the entered model name.\n";
	cout << "(NOTE: if the list is empty, there is no product with that model name...)\n\n";
	header();
	bst_secondary.printByModel(model);
	pressEnter();
	return;
}
Product choice5(BST<Product> bst_primary) {
	string make, model;
	double screenSize, price;
	unsigned cpuGen, year;
	Product p;
	bool valid = false;

	clearScreen();
	title();
	cout << "-----------------\n" <<
			"Add a new product\n" <<
			"-----------------\n\n";
	while (valid == false) {
		cout << "Enter make name: ";
		cin >> make;
		p.setMake(make);
		cout << "Enter model name: ";
		cin.ignore(50, '\n');
		getline(cin, model);
		p.setModel(model);
		if (bst_primary.search(p) == true) {
			cout << "A product with that make and model name already exist. Please try again...\n\n";
		} else {
			valid = true;
			cout << "Enter screen size (in.): ";
			cin >> screenSize;
			p.setScreenSize(screenSize);
			cout << "Enter cpu generation (ex: 8): ";
			cin >> cpuGen;
			p.setCpuGen(cpuGen);
			cout << "Enter model year (ex: 2016): ";
			cin >> year;
			p.setYear(year);
			cout << "Enter price ($): ";
			cin >> price;
			p.setPrice(price);
		}
	}
	cout << "\nProduct added complete!\n\n";
	pressEnter();
	return p;
}
Product choice6(BST<Product> bst_primary) {
	string make, model;
	Product p;
	bool valid = false;

	clearScreen();
	title();
	cout << "--------------------------\n" <<
			"Remove an existing product\n" <<
			"--------------------------\n\n";
	while (valid == false) {
		cout << "Enter make name: ";
		cin >> make;
		p.setMake(make);
		cout << "Enter model name: ";
		cin.ignore(50, '\n');
		getline(cin, model);
		p.setModel(model);
		if (bst_primary.search(p) == false) {
			cout << "A product with that make and model name does not exist. Please try again...\n\n";
		} else {
			valid = true;
		}
	}
	cout << "\nProduct removal complete!\n\n";
	pressEnter();
	return p;
}
void choice7(BST<Product> bst_primary) {
	string fname;

	clearScreen();
	title();
	cout << "-------------------------\n" <<
			"Save current list to file\n" <<
			"-------------------------\n\n";
	cout << "Enter output file name: ";
	cin.ignore(50, '\n');
	cin >> fname;
	bst_primary.save(fname);
	cout << "\nSave complete!\n\n";
	pressEnter();
	return;
}
void choice8() {
	cout << "\n\n\n BYE!!";
	return;
}

void clearScreen() {
	cout << string(50, '\n');
}

void pressEnter() {
	cout << "Press ENTER to continue...";
	cin.ignore(50, '\n');
	cin.get();
	return;
}
