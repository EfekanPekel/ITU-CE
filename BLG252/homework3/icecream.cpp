#include <iostream>
#include <cstdlib>
#include <string>
#include "icecream.h"

using namespace std;

Icecream::Icecream(string s, float a, int b){ // Constructor
	name = s;
	litre = a;
	price = b;
	cost = (float)a*b;
}

void Icecream::operator=(Icecream &input){ //Assignment operator
	name = input.name;
	litre = input.litre;
	price = input.price;
	cost = input.cost;
}

Icecream::Icecream(){ // Default constructor
	name = "";
	litre = 0;
	price = 0;
	cost = 0;
}

/*ostream& operator<<(ostream&out, Icecream&input){
	out << input.name << " #" << input.litre << " Cost:" << input.cost << endl;
	return out;
}*/

int Icecream::find(string input, int count){ // function that checks amount for order
	if (input == name){
		if (count >= litre){
			return litre;
		}
	}
	return 0;
}
float Icecream::calc(string input, int count){ // function that calculates cost of order for one thing
	if (input == name){
		return (float)count*price;
	}
	return 0;
}