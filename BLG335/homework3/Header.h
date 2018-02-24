#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <map>

using namespace std;

class BookChar{
	int page, line, index;
	char ch;
	void generate();
public:
	unsigned long int key;
	BookChar();
	BookChar(int, int, int, char);
};

BookChar::BookChar(){
	ch = NULL;
	key = -1;
}

BookChar::BookChar(int p, int l, int i, char c){
	page = p;
	line = l;
	index = i;
	ch = c;
}

void BookChar::generate(){
	key = key + (10000 * page)+ (100 * line) + index;
	
}

class Dictionary{
	BookChar ar[131071];
	map<int, int> values;
	map<int, int> collisions;
	int h(BookChar&);
public:
	int tot_col;
	void insert(BookChar&);
	float calc_col(int);
};

void Dictionary::insert(BookChar &input){
	h(input);
	int ind = values[input.key];
	ar[ind] = input;
}

int Dictionary::h(BookChar &input){
	int M = 131071;
	float a = input.key*0.618;
	int collision = 0;
	int h = (int)floor(M * fmod(a, 1));
	if (ar[h].key != -1){
		do {
			collision++;
			h = (h + 7 * collision + 3 * pow(collision, 2));
			h = h % M;
		} while (ar[h].key != -1);
	}
	values[input.key] = h;
	collisions[input.key] = collision;
	return h;
}

float Dictionary::calc_col(int N){
	int total_col = 0;
	for (int i = 0; i < N; i++){
		total_col += collisions[ar[i].key];
	}
	return (float)total_col / N;
}

