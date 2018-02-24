#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
//#include <chrono>

using namespace std;

struct Cards {
	string name;
	string clas;
	string rarity;
	string set;
	string type;
	int cost;
	Cards();
	Cards(char*, char*, char*, char*, char*, int);
	void printCard();
};

Cards::Cards(){
	cost = 0;
}


void Cards::printCard(){
	cout << name << "\t" << clas << "\t" << rarity << "\t" << set << "\t" << type << "\t" << cost << "\n";
}


Cards::Cards(char* temp_name, char* temp_clas, char* temp_rarity, char* temp_set, char* temp_type, int temp_cost){
	name = temp_name;
	clas = temp_clas;
	rarity = temp_rarity;
	set = temp_set;
	type = temp_type;
	cost = temp_cost;
}

struct CardManager {
	Cards *ar= new Cards[100000];
	int number;
	CardManager();
	void add(Cards&);
	void insertion_sort();
	void insertion_sort2();
	void merge_sort(int, int);
	void WriteToFile(ofstream&);
	void Merge(Cards*, Cards*, int, int);
	void Merge2(Cards*, Cards*, int, int);
	int comparefilt(int, int);
};


CardManager::CardManager(){
	number = 0;
}

void CardManager::add(Cards&add){
	ar[number] = add;
	//cout << add.name << "\t" << add.type << endl;
	number++;
}





void CardManager::insertion_sort(){
	for (int j = 2; j<number; j++){
		int i = j-1;
		for (i; i > 0; i--){
			int cond = ar[i].clas.compare(ar[i - 1].clas);
			if (cond < 0){
				swap(ar[i], ar[i - 1]);
			}
			if (!cond && ar[i].cost < ar[i - 1].cost){
				swap(ar[i], ar[i - 1]);
			}

			if (!cond && ar[i].cost == ar[i - 1].cost && ar[i].name.compare(ar[i - 1].name) <0){
				swap(ar[i], ar[i - 1]);
			}
		}
	}
}

void CardManager::insertion_sort2(){
	for (int j = 2; j < number; j++){
		int i = j - 1;
		for (i; i>0; i--){
			int cond = ar[i].type.compare(ar[i - 1].type);
			if (cond < 0){
				swap(ar[i], ar[i - 1]);
			}
		}
	}
}

void CardManager::merge_sort(int bas, int bit){
	if (bit>bas){
		int interval = bit - bas;
		Cards *left = new Cards[interval+1/2];
		Cards *right = new Cards[interval + 1 - ((interval + 1) / 2)];
		int x = 0, y = 0;
		for (int i = 0; i < interval+1 / 2; i++){
			left[i] = ar[i];
		}
		for (int i = interval + 1 / 2 - (interval + 1) / 2; i < interval + 1; i++){

		}
		

	}
}

CardManager* Merge(CardManager *a, CardManager *b, CardManager *c){
	int x = a->number;
	int y = b->number;
	int i = 0, j = 0;
	while (i < x && j < y){
		if (a->ar[i].type.compare(b->ar[j].type) <= 0){
			c->add(a->ar[i]);
			i++;
		}
		else{
			c->add(b->ar[j]);
			j++;
		}
	}
	while (i < x){
		c->add(a->ar[i]);
		i++;
	}
	while (j < y){
		c->add(b->ar[j]);
		j++;
	}
	return c;

}

CardManager* MergeSort(CardManager* a){
	int n = a->number;
	if (n < 2){
		return a;
	}
	int middle = n / 2;
	CardManager left;
	CardManager right;
	for (int i = 0; i < middle; i++){
		left.add(a->ar[i]);
	}
	for (int i = middle; i <n; i++){
		right.add(a->ar[i]);
	}
	CardManager result;
	MergeSort(&left);
	MergeSort(&right);
	Merge(&left, &right, &result);
	*a = result;
}

CardManager* Merge2(CardManager *a, CardManager *b, CardManager *c){
	int x = a->number;
	int y = b->number;
	int i = 0, j = 0;
	while (i < x && j < y){
		int cond = a->ar[i].clas.compare(b->ar[j].clas);
			if (cond < 0){
				c->add(a->ar[i]);
				i++;
				continue;
			}
			if (cond>0){
				c->add(b->ar[j]);
				j++;
				continue;
			}

			if (cond ==0){
				if (a->ar[i].cost < b->ar[j].cost){
					c->add(a->ar[i]);
					i++;
					continue;
				}
				if (a->ar[i].cost > b->ar[j].cost){
					c->add(b->ar[j]);
					j++;
					continue;
				}
	
				if (cond ==0){
					cond = a->ar[i].name.compare(b->ar[j].name);
			if (cond < 0){
				c->add(a->ar[i]);
				i++;
				continue;
			}
			if (cond>0){
				c->add(b->ar[j]);
				j++;
				continue;
			}
			if(cond==0){
				c->add(a->ar[i]);
				i++;
				continue;
			}
			
			
				}
			}
	}
	while (i < x){
		c->add(a->ar[i]);
		i++;
	}
	while (j < y){
		c->add(b->ar[j]);
		j++;
	}
	return c;

}


CardManager* MergeSort2(CardManager* a){
	int n = a->number;
	if (n < 2){
		return a;
	}
	int middle = n / 2;
	CardManager left;
	CardManager right;
	for (int i = 0; i < middle; i++){
		left.add(a->ar[i]);
	}
	for (int i = middle; i <n; i++){
		right.add(a->ar[i]);
	}
	CardManager result;
	MergeSort(&left);
	MergeSort(&right);
	Merge2(&left, &right, &result);
	*a = result;
}

