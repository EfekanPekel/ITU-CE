#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
//#include <chrono>
#include "Header.h"

using namespace std;

int main(int argc, char* argv){
	char temp_name[100], temp_clas[100], temp_rarity[100], temp_set[100], temp_type[100];
	int temp_cost; 
	ifstream input;
	ofstream output;
	CardManager cardmng;
	string inputfile = string(argv[3]);
	input.open(inputfile, ios::out | ios::in);
	while (input.getline(temp_name, 100, '\t')){
		if(input.eof()){
			break;
		}
		input.getline(temp_clas, 100, '\t');
		input.getline(temp_rarity, 100, '\t');
		input.getline(temp_set, 100, '\t');
		input.getline(temp_type, 100, '\t');
		input >> temp_cost;
		input.ignore(1, '\n');
		Cards temp_card(temp_name, temp_clas, temp_rarity, temp_set, temp_type, temp_cost);
		cardmng.add(temp_card);
	}
	if(string(argv[2]).compare("-i")){
		if(string(argv[1]).compare("-full")){
			cardmng.insertion_sort();
		}
		else{
			cardmng.insertion_sort2();
		}
	}
	else {
		if(string(argv[1]).compare("-filter")){
			MergeSort(cardmng);
		}
		else {
			MergeSort2(cardmng);
		}
	}
	
	
	
	output.open(string(argv[4]), ios::out | ios::trunc);
	CardManager *card = MergeSort(&cardmng);
	for (int i = 0; i < cardmng.number; i++){
		output << i << '\t' << card->ar[i].name << "\t" << card->ar[i].clas << "\t" << card->ar[i].rarity << "\t" << card->ar[i].set << "\t" << card->ar[i].type << "\t" << card->ar[i].cost << "\n";
	}

	input.close();
	output.close();

	return 0;


}
