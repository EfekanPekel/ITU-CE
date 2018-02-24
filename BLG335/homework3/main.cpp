#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include "Header.h"


using namespace std;

int main(){
	cout << "1" << endl;
	ifstream input;
	input.open("ds-set-input.txt", ios::in | ios::out);
	int M = 131071;
	int temp_p, temp_l, temp_i;
	char temp_c;
	Dictionary dict;
	cout << "DICTIONARY" << endl;
	clock_t t;
	t = clock();
	for (int i = 0; i < M; i++){
		input >> temp_p;
		input.ignore(' ');
		input >> temp_l;
		input.ignore('\t');
		input >> temp_i;
		input.ignore('\t');
		input >> temp_i;
		input.ignore('\n');
		BookChar temp(temp_p, temp_l, temp_i, temp_c);
		dict.insert(temp);
	}
	t = clock() - t;
	printf("Insertion finished after %f seconds.\n\n", ((float)t) / CLOCKS_PER_SEC);
	input.close();

	cout << "Average number of collisions (first 1,000)   |" << dict.calc_col(1000) << endl;
	cout << "Average number of collisions (first 10,000)  |" << dict.calc_col(10000) << endl;
	cout << "Average number of collisions (first 100,000) |" << dict.calc_col(100000) << endl;
	cout << "Average number of collisions (overall)       |" << dict.calc_col(M) << endl;



	return 0;
}
