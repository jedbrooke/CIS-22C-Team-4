/*
 * HashTable.h
 * Tin Nguyen
 */


#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include <iostream>

using namespace std;

template <class htdata>
class HashTable {
public:
    /**Constructors*/

    HashTable(){}
    //constructor

    ~HashTable(){}
    //destructor


    /**Access Functions*/

    int hash(string key) const;

    void insert(htdata& c);

    void displayByLastname(ostream& out, string lastname) ;
    void displayByFirstname(ostream& out, string firstname);
    void displayCustomer(ostream& out);

    htdata* customerSignIn(string username);

private:
    static const int SIZE = 100;
    List<htdata*> Table[SIZE];
};

template<class htdata>
int HashTable<htdata>:: hash(string key) const {
	string temp;
		int index, sum = 0;
		for (int i = 0; i < key.length(); i++){
			sum += (int) key[i]; //summing the ASCII values for each character in the stringindex = sum % SIZE; //dividing the summed ASCII values by TABLE_SIZE//and storing remainder as my indexreturn index;}
	}
	index= sum % SIZE;
	return index;
}

template<class htdata>
void HashTable<htdata>::insert(htdata& c) {
	int index = hash (c.getFirstname()+ c.getLastname());
	Table[index].insertStop (&c);

}


template <class htdata>
void HashTable<htdata>::displayCustomer(ostream& out) {
	for (int i =0; i< SIZE; i++){
		Table[i].startIterator();
		while(!Table[i].offEnd()){
			out << *(Table[i].getIterator());
			Table[i].moveIterNext();
		}
	}
}

template <class htdata>
void HashTable<htdata>::displayByFirstname(ostream& out, string firstname) {
	for (int i =0; i< SIZE; i++){
		Table[i].startIterator();
		for (int j=0; j <Table[i].getLength(); j++){
			if(Table[i].getIterator()->getFirstname().find(firstname) != string::npos){
				out << *(Table[i].getIterator());
			}
			Table[i].moveIterNext();
		}
	}
	out << "Customer not found";
}


template <class htdata>
void HashTable<htdata>::displayByLastname(ostream& out, string lastname) {
	for (int i =0; i< SIZE; i++){
		Table[i].startIterator();
		for (int j=0; j <Table[i].getLength(); j++){
			if(Table[i].getIterator()->getLastname().find(lastname) != string::npos){
				out << *(Table[i].getIterator());
			}
			Table[i].moveIterNext();
		}
	}
	out << "Customer not found" ;
}

template <class htdata>
htdata* HashTable<htdata>::customerSignIn(string username){
	for (int i =0; i< SIZE; i++){
		Table[i].startIterator();
		for(int j=0; j<Table[i].getLength(); j++){
			if(Table[i].getIterator()->getUsername()== username){
				return Table[i].getIterator();
			}
			Table[i].moveIterNext();
		}

	}
	return NULL;
}
#endif /* HASHTABLE_H_ */
