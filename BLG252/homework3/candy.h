#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Candy{
public:
	string name; // name of candy
	int weight; // per kilogram
	int price; // unit price of candy
	float cost; // cost of candy
	Candy(); // default constructor
	Candy(string, int, int); // constructor
	void operator=(const Candy&); // assignment operator
	friend ostream& operator<<(ostream&out, Candy&input){ // printing operator
		out << input.name << " Cost:" << input.cost << endl;
		return out;
	}
	int find(string, int);// function that checks amount for order
	float calc(string, int); // function that calculates cost of order for one thing
};