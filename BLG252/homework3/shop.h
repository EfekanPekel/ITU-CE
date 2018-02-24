#ifndef SHOP_H
#define SHOP_H


#include <iostream>
#include <cstdlib>
#include <string>

#define MAXSIZE 100

using namespace std;

template <class Type> // Shop class
class Shop{ 
private:
	Type *ar; // Dynamic part
public:
	int size; // size of array
	float total_cost, disc_cost; // total cost and discounted cost respectively
	int discount; // percentage of discount
	Shop(); // default constructor
	Shop(Type&); // Constructor
	void add(Type&); // adding function
	friend ostream& operator<<(ostream&out, Shop&input){ //printing function
		cout << "**********************" << endl;
		cout << "Number of items:" << input.size << endl;
		for (int i = 0; i < input.size; i++){
			out << i + 1 << ": " << input.ar[i] << endl;
		}
		cout << "**********************" << endl;
		cout << "Total cost: " << input.total_cost << endl;
		if (input.discount == 0){
			cout << "**********************";
		}
		if (input.discount != 0){
			input.disc_cost = (float)input.total_cost * (100 - input.discount) / 100;
			cout << "Discount: %" << input.discount << endl;
			cout << "Discount amount: " << input.disc_cost - input.total_cost << endl;
			cout << "Discounted cost: " << input.disc_cost << endl;
			cout << "**********************" << endl;
		}
		return out;
	}
	Type operator[](int); // operator for direct access
	void setDiscount(int); // setdiscount function
	int search(string, int); // searching function to determine whether we have enough amount of cookie,candy or icecream
	float calc_cost(string, int); // calculating cost for order
	~Shop();
};


#endif // !SHOP_H