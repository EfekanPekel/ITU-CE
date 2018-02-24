#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

class line{
public:
	int min_age;
	int max_age;
	string gender;
	int zipcode;
	int population;
	string geoid;
	line();
	line(int, int, int, char*, int, char*);
};

line::line(){
	population = 0;
	min_age = 0;
	max_age = 0;
	gender = "";
	zipcode = 0;
	geoid = "";
}

line::line(int pop, int mina, int maxa, char* gen, int zip, char* geo){
	population = pop;
	min_age = mina;
	max_age = maxa;
	gender = gen;
	zipcode = zip;
	geoid = geo;
}

int partition(line* A, int p, int r){
	line x = A[r];
	int i = p - 1;
	for (int j = p; j<r; j++){
		if (A[j].population < x.population){
			i = i + 1;
			swap(A[i], A[j]);
		}
		else if (A[j].population == x.population && A[j].geoid.compare(x.geoid) < 0 ) {
			i = i + 1;
			swap(A[i], A[j]);
		}

	}
	swap(A[i + 1], A[r]);

	return i + 1;
}

void quicksort(line* A, int p, int r){
	if (p<r){
		int q = partition(A, p, r);
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}

int strtoi(char* input){
	if (!strcmp(input,"")){
		return -1;
	}
	else {
		return atoi(input);
	}
}
