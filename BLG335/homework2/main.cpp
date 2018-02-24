#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <ctime>
#include "Header.h"

using namespace std;

int main(int argc, char *argv[]){
	ifstream input;
	input.open("population_by_zip_2010.csv", ios::in);
	input.ignore(1000, '\n');
	int N = atoi(argv[1]);
	line *ar = new line[N];
	for (int i = 0; i < N; i++){
		int temp_p, temp_min, temp_max, temp_zip;
		char temp_gen[50], temp_geo[50], temp[50];
		input >> temp_p;
		input.ignore(1, ',');
		input.getline(temp, 50, ',');
		temp_min = strtoi(temp);
		strcpy(temp, "");
		input.getline(temp, 50, ',');
		temp_max = strtoi(temp);
		strcpy(temp, "");
		input.getline(temp_gen, 50, ',');
		input >> temp_zip;
		input.ignore(1, ',');
		input.getline(temp_geo, 50, '\n');
		
		line temp1(temp_p, temp_min, temp_max, temp_gen, temp_zip, temp_geo);
		ar[i] = temp1;
	}
	clock_t t;
	t = clock();
	quicksort(ar, 0, N-1);
	t = clock()-t;
	printf ("%f seconds.\n",((float)t)/CLOCKS_PER_SEC);
	input.close();
	ofstream output;
	output.open("population_sorted.csv", ios::out | ios::trunc);
	output << "population,minimum_age,maximum_age,gender,zipcode,geo_id" << endl;
	for (int i = 0; i < N; i++){
		output << ar[i].population << ",";
		if (ar[i].min_age == -1){
			output << ",";
		}
		else{
			output << ar[i].min_age << ",";
		}

		if (ar[i].max_age == -1){
			output << ",";
		}
		else{
			output << ar[i].max_age << ",";
		}
		output << ar[i].gender << "," << ar[i].zipcode << "," << ar[i].geoid << endl;

	}
	output.close();

	return 0;
}
