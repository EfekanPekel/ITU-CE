#include <iostream>
#include <cstdlib>
#include <string>
#include "shop.h"

using namespace std;
template <class Type> // 
Shop<Type>::Shop(){
	size = 0;
	ar = NULL;
	total_cost = 0;
	discount = 0;
}

template <class Type>
Shop<Type>::~Shop(){
	delete[] ar;
}

template <class Type>
Shop<Type>::Shop(Type& input){
	ar = new Type[1];
	size = 1;
	ar[0] = input;
	total_cost = (float)108 * input.cost / 100;
	discount = 0;
}

template <class Type>
void Shop<Type>::add(Type& input){
	if (size == 0){
		ar = new Type[1];
		ar[0] = input;
		size++;
		total_cost = (float)108 * input.cost / 100;
	}
	else {
		Type transfer[MAXSIZE];
		for (int i = 0; i < size; i++){
			transfer[i] = ar[i];
		}
		delete[] ar;
		ar = new Type[size + 1];
		for (int i = 0; i < size; i++){
			ar[i] = transfer[i];
		}
		ar[size] = input;
		size++;
		total_cost += (float)108 * input.cost / 100;
	}
}


template <class Type>
void Shop<Type>::setDiscount(int x){
	if (x<0 || x>30){
		discount = 0;
		throw "Discount rate is out of range!";
	}
	else {
		discount = x;
	}
}



template <class Type>
Type Shop<Type>::operator[](int x){
	if (x >= size)
		throw "We don't have enough cookies";
	else{
		return ar[x];
	}
}

template<class Type>
int Shop<Type>::search(string input, int count){
	for (int i = 0; i < size; i++){
		if (ar[i].find(input, count) != 0){
			return ar[i].find(input, count);
		}
	}
	return 0;
}

template<class Type>
float Shop<Type>::calc_cost(string input, int count){
	for (int i = 0; i < size; i++){
		if (ar[i].calc(input, count) != 0){
			return ar[i].calc(input, count);
		}
	}
}

