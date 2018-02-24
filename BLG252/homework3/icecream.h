#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Icecream{
public:
	string name; // name of icecream
	float litre; // per litre
	int price; // unit price for litre
	float cost; // cost of icecream
	Icecream(); // default constructor
	Icecream(string, float, int); // constructor
	Icecream(Icecream &); // copy constructor
	void operator=(Icecream &); // assignment operator
	friend ostream& operator<<(ostream&out, Icecream&input){ // printing operator
		out << input.name << " #" << input.litre << " Cost:" << input.cost << endl;
		return out;
	}
	int find(string, int); // function that checks amount for order
	float calc(string, int);// function that calculates cost of order for one thing
};