#include <iostream>
#include <cstdlib>
#include <string>
#include "candy.h"

using namespace std;

Candy::Candy(string s, int a, int b){ // Constructor
	name = s;
	weight = a;
	price = b;
	cost = a*b;
}

void Candy::operator=(const Candy &input){ // Assignment operator
	name = input.name;
	weight = input.weight;
	price = input.price;
	cost = input.cost;
}

Candy::Candy(){
	name = "";
	weight = 0;
	price = 0;
	cost = 0;
}

/*ostream& operator<<(ostream&out, Candy&input){
	out << input.name << " Cost:" << input.cost << endl;
	return out;
}*/

int Candy::find(string input, int count){ // function that checks amount for order
	if (input == name){
		if (count >= weight){
			return weight;
		}
	}
	return 0;
}

float Candy::calc(string input, int count){ // function that calculates cost of order for one thing
	if (input == name){
		return (float)count*price;
	}
	return 0;
}
