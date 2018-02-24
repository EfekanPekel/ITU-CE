#include <iostream>
#include <cstdlib>
#include <string>
#include "cookie.h"

Cookie::Cookie(string s, int a, int b){ // Constructor
	name = s;
	number = a;
	price = (float)b/12;
	cost = (float)b / 12 * a;
}

void Cookie::operator=(const Cookie &input){ // Assignment operator
	name = input.name;
	number = input.number;
	price = input.price;
	cost = input.cost;
}

Cookie::Cookie(){ // Default constructor
	name = "";
	number = 0;
	price = 0;
	cost = 0;
}

/*ostream& operator<< (ostream&out, Cookie&input){ // Printing operator
	out << input.name << " #" << input.number << " Cost:" << input.cost << endl;
	return out;
}*/

int Cookie::find(string input,int count){ // function that checks amount for order
	if (input == name){
		if (count >= number){
			return number; // returns number if there are not enough cookie for order
		}
	}
	return 0;
}

float Cookie::calc(string input, int count){ // function that calculates cost of order for one thing
	if (input == name){
		return (float)count*price; // calculating price for order
	}
			

	return 0;
}