#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Cookie{
public:
	string name; // name of cookie
	int number; // per dozen
	float price; // unit price of cookie
	float cost; // cost of cookie
	Cookie(); // default constructor
	Cookie(string, int, int); // constructor
	void operator=(const Cookie&); // assignment operator
	friend ostream& operator<<(ostream& out, Cookie&input){// printing operator
		out << input.name << " #" << input.number << " Cost:" << input.cost << endl;
		return out;
	}
	int find(string,int); // function that checks amount for order
	float calc(string, int); // function that calculates cost of order for one thing
};