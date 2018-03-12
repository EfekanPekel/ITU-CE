#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

class Person{
public:
	string name;
	char gender;
	int age;
	char color;
	Person *left;
	Person *right;
	Person *parent;
	Person();
	Person(char*, char, int);
};


Person::Person(char* temp_name, char temp_gender, int temp_age){
	this->name = temp_name;
	this->gender = temp_gender;
	this->age = temp_age;
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
	this->color = 'R';
}

class Tree{
public:
	Tree();
	Person *root;
	void rb_insert(Person*);
	void tree_insert(Person*);
	void left_rotate(Person*);
	void right_rotate(Person*);
	Person* num_woman(int);
	Person* num_man(int);
};

Tree::Tree(){
	root = NULL;
}

void Tree::tree_insert(Person* x){
	if (root == NULL){
		root = x;
		root->parent = NULL;
	}
	else {
		Person *trav = root;
		bool added = false;
		while (trav != NULL && !added){
			if (x->name < trav->name){
				if (trav->left != NULL){
					trav = trav->left;
				}
				else{
					trav->left = x;
					x->parent = trav;
					added = true;
				}
			}
			else{
				if (trav->right != NULL){
					trav = trav->right;
				}
				else {
					trav->right = x;
					x->parent = trav;
					added = true;
				}
			}
		}
	}
}

void Tree::rb_insert(Person* x){
	tree_insert(x);
	while (x != root && x->parent != root && x->parent->parent != NULL && x->parent->color == 'R'){
		if (x->parent == x->parent->parent->left){
			Person *y = x->parent->parent->right;
			if (y != NULL && y->color == 'R'){
				x->parent->color = 'B';
				y->color = 'B';
				x->parent->parent->color = 'R';
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->right){
					x = x->parent;
					left_rotate(x);
				}
				x->parent->color = 'B';
				x->parent->parent->color = 'R';
				right_rotate(x->parent->parent);
			}
		}
		else{
			if (x->parent->parent->left != NULL){
				Person* y = x->parent->parent->left;
				if (y != NULL && y->color == 'R'){
					x->parent->color = 'B';
					y->color = 'B';
					x->parent->parent->color = 'R';
					x = x->parent->parent;
				}
			}
			else{
				if (x->parent->left == x){
					x = x->parent;
					right_rotate(x);
				}
				x->parent->color = 'B';
				x->parent->parent->color = 'R';
				left_rotate(x->parent->parent);
			}
		}
		root->color = 'B';
	}
}

void Tree::left_rotate(Person *x){
	if (x->right == NULL){
		return;
	}
	else{
		Person *y = x->right;
		if (y->left != NULL){
			x->right = y->left;
			y->left->parent = x;
		}
		else {
			x->right = NULL;
		}
		if (x->parent != NULL){
			y->parent = x->parent;
		}
		if (x->parent == NULL){
			root = y;
		}
		else {
			if(x==x->parent->left){
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
		}
		y->left = x;
		x->parent = y;
	}
}

void Tree::right_rotate(Person *x){
	if (x->left == NULL){
		return;
	}
	else{
		Person *y = x->left;
		if (y->right != NULL){
			x->left = y->right;
			y->right->parent = x;
		}
		else{
			x->left = NULL;
		}
		if (x->parent != NULL){
			y->parent = x->parent;
		}
		if (x->parent == NULL){
			root = y;
		}
		else{
			if (x == x->parent->left){
				x->parent->left = y;
			}
			else{
				x->parent->right = y;
			}
		}
		y->right = x;
		x->parent = y;
	}
}
int a = 0;
void print(Person* input, int depth){
	Person *root = input;
	if (root == NULL){
		return;
	}
	a++;
	print(root->left,a);
	for (int i = 1; i < a; i++){
		cout << "       ";
	}
	if (root->parent != NULL && root == root->parent->left ){
		cout << "â”Œ---";
	}
	else if (root->parent != NULL && root == root->parent->right){
		cout << "â””---";
	}
	cout << "(" << root->color << ")" << root->name << "-" << root->age << "-" << root->gender << endl;
	print(root->right,a);
	a--;
}

int man = 0;
Person *output;
Person* num_man(Person* root, int number){
	Person *trav = root;
	if(trav == NULL){
		return NULL;
	}
	num_man(trav->left,number);
	if(trav->gender == 'M'){
		man++;
		if(man == number){
			output = trav;
		}
	}
	num_man(trav->right, number);
	return output;
}

int woman = 0;
Person* output2;
Person* num_woman(Person* root, int number){
	Person *trav = root;
	if(trav == NULL){
		return NULL;
	}
	num_woman(trav->left,number);
	if(trav->gender == 'F'){
		woman++;
		if(woman == number){
			output2 = trav;
		}
	}
	num_woman(trav->right, number);
	return output2;
}

int main(int argc,char** argv ){
	ifstream input;
	input.open(argv[1], ios::in);
	Tree redblack;
	while (!input.eof()){
		int temp_age;
		char temp_gender;
		char temp_name[50];
		input.getline(temp_name, 50, '\t');
		input >> temp_gender;
		input >> temp_age;
		input.ignore(1, '\n');
		Person *temp = new Person(temp_name, temp_gender, temp_age);
		redblack.rb_insert(temp);
	}
	input.close();
	print(redblack.root,0);

	Person *man = num_man(redblack.root, 4);
	Person *woman = num_woman(redblack.root, 3);
	cout << "3th woman: " << woman->name << endl;
	cout << "4th man: " << man->name << endl;

	return 0;
}
