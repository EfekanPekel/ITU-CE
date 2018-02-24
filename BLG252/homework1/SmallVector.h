/* @Author
* Student Name: Mustafa Efekan PEKEL
* Student ID: 150140050
* Date: 29.03.2017
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class SmallVector { // Declaration of SmallVector class
	int *dinamic_buf; // Integer pointer to keep dynamic memory
	int static_buf[32]; // Integer array to keep static memory
public: // public elements to be accessible
	int size=0; //size of SmallVector
	int size_dy=0; // size of dynamic part of SmallVector
	SmallVector(int*, int); // Constructor from array 
	SmallVector(const SmallVector&); // Copy-constructor
	~SmallVector(); // Destructor
	void push_back(int); // Pushing function
	int pop_back(); // Poping function
	int getSize() const; // GetSize function
	SmallVector operator+(const SmallVector&); // Concatenate operator
	SmallVector operator*(int); // Replicator operator
	const int &operator [](int) const; // [] operator for accessing
	int &operator [](int); // [] operator for changing
	void operator=(const SmallVector&); // Assignment operator
	SmallVector reverse(); // Reverse function
};

SmallVector::SmallVector(int *ar = 0, int x=0){ // Constructor with default parameters
	//size = 0; 
	//size_dy = 0;
	if (x < 32){ // If input is smaller than 32 then just putting values to the static array
		for (int i = 0; i < x; i++){
			static_buf[i] = ar[i];
		}
		size = x; // Changing size
	}
	if (x>=32){ // If input is greater than 32 then putting first 32 elements to the static array then dynamic part
		size_dy = x - 32;
		dinamic_buf = new int[x-32]; // Taking memory for after 32 elements
		for (int i = 0; i < 32; i++){
			static_buf[i] = ar[i];
		}
		for (int i = 32; i < x; i++){
			dinamic_buf[i-32] = ar[i];
		}
		size = x; // Changing size
	}
}

SmallVector::SmallVector(const SmallVector &vect){// Copy-constructor
	size = vect.size; 
	size_dy = vect.size_dy;
	if (size>32){ // If the input has dynamic part then copying first 32 elements to the static array and the rest to the dynamic part
		for (int i = 0; i < 32; i++){
			memcpy(&static_buf[i], &vect[i], sizeof(int)); //Memory copying from input to the static array
		}
		dinamic_buf = new int[size_dy]; // Taking memory for 32 elements
		for (int i = 0; i < size_dy; i++){
			memcpy(&dinamic_buf[i], &vect.dinamic_buf[i], sizeof(int)); // Memory copying from input to the dynamic part
		}
	}
	
	else{ // If input has smaller than 32 elements then just copying to the static array
		for (int i = 0; i < size; i++){
			memcpy(&static_buf[i], &vect.static_buf[i], sizeof(int)); // Memory copying from input to the static memory
		}
	}
}

SmallVector::~SmallVector(){ // Destructor
	if (size_dy != 0){
		delete[] dinamic_buf; // Deleting dynamic part if exists
	}
}

void SmallVector::push_back(int a){ // Pushing function
	if (size < 32){ // If size of class is smaller than 32 pushing input to the static array
		static_buf[size] = a; // Definition
		size++; // Increasing size
	}
	else if (size == 32){ // If size equals to 32 we need to take memory for dynamic part
		dinamic_buf = new int[1]; // taking memory
		size++; // increasing size
		size_dy++; // increasing size of dynamic part
		dinamic_buf[0] = a; // definition
	}
	else { // If size is greater than 32 then we need to increase dynamic memory part
		int *ar = new int[size_dy]; // temporary array to keep dynamic part
		for (int i = 0; i < size_dy; i++){ 
			ar[i] = dinamic_buf[i]; // assignments
		}
		dinamic_buf = new int[size_dy + 1]; // taking memory
		for (int i = 0; i<size_dy; i++){
			dinamic_buf[i] = ar[i]; //  giving elements back
		}
		dinamic_buf[size_dy] = a; // new element assigning
		size_dy++; // increasing size of dynamic part
		size++; // increasing size of SmallVector
		delete [] ar; // deleting temporary array
	}
}

int SmallVector::pop_back(){ // poping function
	if (size<32){ // If size is smaller than 32 we should pop from static memory
		return static_buf[size - 1];
		size--; // decreasing size
	}
	else{ // If size is greater than 32 we should pop from dynamic part
		return dinamic_buf[size - 32];
		size--; // decreasing size
		size_dy--; // decreasing size of dynamic part
	}
}

int SmallVector::getSize() const{ // Getting size function
	return size; // Returning size
}

const int& SmallVector::operator[](int i) const { // [] operator to get value of SmallVector
	if (i > 31){ // Because indexing starts from 0, our limit is 31
		return dinamic_buf[i-32]; 
	}
	else if (i>=0){
		return static_buf[i];
	}
	else if (abs(i) >= size_dy ){ // For negative values
		return static_buf[size + i];
	}
	else {
		return dinamic_buf[size_dy + i-1];
	}
}

int& SmallVector::operator[](int i) { // [] operator to be able to change value of SmallVector
	if (i > 31){ // Because indexing starts from 0, our limit is 31
		return dinamic_buf[i - 32];
	}
	else if (i >= 0){
		return static_buf[i];
	}
	else if (abs(i) >= size_dy){ // For negative values
		return static_buf[size + i];
	}
	else {
		return dinamic_buf[size_dy + i - 1];
	}
}

SmallVector SmallVector::operator+(const SmallVector &input){ // Concatenate operator
	SmallVector output; // New SmallVector for output
	output = *this; // Assigning to this
	if (output.size + input.size <= 32){ // If total size smaller than 32
		for (int i = output.size; i < output.size + input.size; i++){
			output.static_buf[i] = input.static_buf[i - output.size];
		}
		output.size += input.size; // increasing size
	}
	else if (output.size>32){ // If output size greater than 32
		int *ar = new int[size_dy]; 
		for (int i = 0; i < size_dy; i++){
			ar[i] = dinamic_buf[i];
		}
		output.dinamic_buf = new int[size_dy + input.size];
		for (int i = 0; i<size_dy; i++){
			output.dinamic_buf[i] = ar[i];
		}
		for (int i = size_dy; i < size_dy + input.size; i++){
			output.dinamic_buf[i] = input[i - size_dy];
		}
		output.size += input.size; // increasing size
		output.size_dy += input.size; // increasing size of dynamic part
	}
	else if (output.size + input.size>32){ // If total size greater than 32 but output size smaller than 32
		for (int i = output.size; i < 32; i++){
			output.static_buf[i] = input[i - output.size];
		}
		int *ar = new int[size_dy];
		for (int i = 0; i < size_dy; i++){
			ar[i] = dinamic_buf[i];
		}
		output.dinamic_buf = new int[input.size + output.size - 32];
		for (int i = 0; i < input.size + output.size - 32; i++){
			output.dinamic_buf[i] = input[i - output.size + 32];
		}
		output.size += input.size-1; // increasing size
		output.size_dy += output.size - 31; // increasing size of dynamic part
	}
	return output; // returning
}

void SmallVector::operator=(const SmallVector &input){ // Assigning operator like copy constructor
	size = input.size;
	size_dy = input.size_dy;
	if (size > 32){ // If size is greater than 32
		dinamic_buf = new int[size_dy];
		for (int i = 0; i < size_dy; i++){
			dinamic_buf[i] = input.dinamic_buf[i];
		}
		for (int i = 0; i < 32; i++){
			static_buf[i] = input.static_buf[i];
		}
	}
	else { // If size is smaller than 32
		for (int i = 0; i < size; i++){
			static_buf[i] = input.static_buf[i];
		}
	}
}

SmallVector SmallVector::operator*(int input){ // * Operator 
	SmallVector output(*this); // New SmallVector for output
	for (int i = 0; i<input-1; i++){
		output = output + *this; // using concatenate operator 
	}
	return output; // Returning
}

SmallVector SmallVector::reverse(){ // Taking reverse function
	SmallVector output(*this); // New SmallVector for output
	if (output.size > 32){ // If size is greater than 32
		int *ar = new int[output.size_dy];
		int *ar2 = new int[output.size_dy];
		for (int i = 0; i < output.size_dy; i++){ // Temporary array 
			ar[i] = output.dinamic_buf[i];
		}
		for (int i = 0; i < output.size_dy; i++){ // Temporary array 2
			ar2[i] = output.static_buf[i];
		}
		for (int i = 0; i < output.size_dy; i++){
			output.dinamic_buf[i] = ar2[size_dy-i-1]; // Giving back with reverse order
		}
		for (int i = size_dy; i < 16; i++){
			swap(output.static_buf[i], output.static_buf[31 - i + size_dy]); // Swaping
		}
		for (int i = 0; i < size_dy; i++){
			output.static_buf[i] = ar[i]; // Giving bach with reverse ordeer
		}
		delete[] ar; // Deleting temporary array
		delete[] ar2; // Deleting temporary array 2
	}

	else { // If size is smaller than 32
		for (int i = 0; i < floor(output.size / 2); i++){ 
			swap(output.static_buf[i], output.static_buf[size - i-1]); // Just swapping elements
		}
	}
	return output; // Returning
}