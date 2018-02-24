#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "shop.h"
#include "candy.h"
#include "cookie.h"
#include "icecream.h"
#include "shop.cpp"
using namespace std;


int main() {
	Cookie cookie1("Chocolate Chip Cookies", 10, 180); //(name, pieces, priceperdozen)
	Cookie cookie2("Cake Mix Cookies", 16, 210);

	Shop<Cookie> cookieShop(cookie1);
	cookieShop.add(cookie2);
	cout << cookieShop << endl;

	//Catch an exception here while trying to access the element at(2)
	try{
		cout << cookieShop[2] << endl;
	}
	catch (const char* a){
		cout << a << endl;
	}

	Icecream icecream1("Chocolate ice cream", 1.5, 170); //(name, litre, priceperlitre)
	Shop<Icecream> icecreamShop(icecream1);
	cout << icecreamShop << endl;

	//Catch an exception here while trying to set the discount to(50)  
	try{
		icecreamShop.setDiscount(50);
	}
	catch (const char*){
		cout << "Discount rate is out of range!" << endl;
	}

	Candy candy2("Gummi bears", 12, 89); //(name, weight, priceperkg)
	Candy candy3("Hanukkah gelt", 8, 110);

	Shop<Candy> candyShop(candy2);
	candyShop.add(candy3);

	candyShop.setDiscount(15);
	cout << candyShop << endl;

	ifstream input; // Input file
	input.open("stock.txt", ios::out | ios::in); // Open input file
	char* first_line = new char[1000]; // variables to store data
	char* name = new char[50];
	int number;
	int itemcount;
	float itemcnt; // for icecream
	int price;
	Shop<Cookie> cookie_shop;
	Shop<Candy> candy_shop;
	Shop<Icecream> icecream_shop;
	input.getline(first_line, 1000, '\n'); // reading first line
	while (input.getline(name, 50, '\t')){ // reading other lines
		input >> number;
		if (number == 1){ // for cookie
			string name1 = name;
			input >> itemcount;
			input >> price;
			Cookie cookie_1(name1, itemcount, price);
			cookie_shop.add(cookie_1);
			input.ignore(1, '\n');
		}
		else if (number == 2){ // for candy
			string name1 = name;
			input >> itemcount;
			input >> price;
			Candy candy_1(name1, itemcount, price);
			candy_shop.add(candy_1);
			input.ignore(1, '\n');
		}
		else if (number == 3){ // for icecream
			string name1 = name;
			input >> itemcnt;
			input >> price;
			Icecream icecream_1(name1, itemcnt, price);
			icecream_shop.add(icecream_1);
			input.ignore(1, '\n');
		}
	}
	input.close(); // closing file

	ifstream order; // order file
	ofstream output; // output file
	int count; 
	int counter = 0; // counter variable for items
	order.open("order.txt", ios::out | ios::in); // opening order file
	output.open("checkout.txt", ios::out | ios::trunc); // opening output file
	int quantity[MAXSIZE]; // array to keep quantity of cookie,candy or icecream
	int j = 0;
	while (order.getline(name, 50, '\t')){ // reading orders and determining amounts if we dont have enough amounts then printing message
		order >> number;
		counter++;
		if (number == 1){
			string name1 = name;
			order >> count;
			int value = cookie_shop.search(name1, count);
			if (value != 0){
				output << "!!! We don't have " << count << " (" << name1 << ")s." << endl;
				quantity[j] = value;
			}
			else {
				quantity[j] = count;
			}
		}
		else if (number == 2){
			string name1 = name;
			order >> count;
			int value = candy_shop.search(name1, count);
			if (value != 0){
				output << "!!! We don't have " << count << " (" << name1 << ")s." << endl;
				quantity[j] = value;
			}
			else {
				quantity[j] = count;
			}
		}
		else if (number == 3){
			string name1 = name;
			order >> count;
			int value = icecream_shop.search(name1, count);
			if (value != 0){
				output << "!!! We don't have " << count << " (" << name1 << ")s." << endl;
				quantity[j] = value;
			}
			else {
				quantity[j] = count;
			}
		}
		order.ignore(1, '\n');
		j++;
	}
	order.close(); // closing order file
	float total_cost = 0, disc_cost=0; // total cost and discounted cost respectively
	int i = 1;
	output << "-----------------------" << endl;
	output << "Number of items: " << counter << endl;
	order.open("order.txt", ios::out | ios::in);
	while (order.getline(name, 50, '\t')){ // reading file again and printing values
		order >> number;
		string name1 = name;
		output << i << ": " << name1 << " #";
		if (number == 1){
			order >> count;
			float value = cookie_shop.calc_cost(name1, quantity[i - 1]);
			output << quantity[i - 1] << " Cost:" << value << endl;
			total_cost += (float)value * 108 / 100;
		}
		else if (number == 2){
			order >> count;
			float value = candy_shop.calc_cost(name1, quantity[i - 1]);
			output << quantity[i - 1] << " Cost:" << value << endl;
			total_cost += (float)value * 108 / 100;
		}
		else if (number == 3){
			order >> count;
			float value = icecream_shop.calc_cost(name1, quantity[i - 1]);
			output << quantity[i - 1] << " Cost:" << value << endl;
			total_cost += (float)value * 108 / 100;
		}
		order.ignore(1, '\n');
		i++;
	}
	order.close();
	disc_cost = (float)total_cost * 90 / 100;
	output << "**********************" << endl;
	output << "Total cost: " << total_cost << endl;
	output << "Discount: %10" << endl;
	output << "Discount amount: " << disc_cost - total_cost << endl;
	output << "Discounted cost: " << disc_cost << endl;
	output << "**********************" << endl;

	output.close();



	/*You will also
	1) Read dessert stock and customer order from "stock.txt" and "order.txt", respectively.
	2) Write the total cost with 10% discount to "checkout.txt".
	Expected output for checkout:
	!!! We don't have 7 (Orange Jelly Candy)s.
	!!! We don't have 11 (Chocolate ice cream)s.
	-----------------------
	Number of items:4
	1: Chocolate Chip Cookies #2 Cost: 100
	2: Orange Jelly Candy #5 Cost: 750
	3: Chocolate ice cream #2 Cost: 480
	4: Cake Mix Cookies #10 Cost: 150
	**********************
	Total cost: 1598.40
	Discount: %10
	Discount amount: -159.84
	Discounted cost: 1438.56
	**********************
	*/

	return 0;
}