/* @Author
* Student Name: Mustafa Efekan PEKEL
* Student ID: 150140050
* Date: 25.12.2016
*/
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>

#define _CRT_SECURE_NO_WARNINGS
#define LONG_MAX 2147483647 // long int limit
#define LONG_MIN -2147483647
#define MAX 100
#define MAX_SIZE 15

using namespace std;

struct StackData{ // data type to store data 
	char data[MAX_SIZE];
	StackData *next = NULL;
	StackData *back = NULL;
};

struct Stack{ // Stack structure
	StackData *head;
	int number;
	void create();
	void push(StackData*);
	bool isempty();
	StackData* pop();
};

void Stack::create(){ //Stack create function
	head = NULL;
	number = 0;
}

void Stack::push(StackData *add){ // Stack-push function
	if (head == NULL){
		head = add;
		head->next = NULL;
		head->back = NULL;
	}
	else {
		add->back = head;
		head->next = add;
		add->next = NULL;
		head = add;

	}
	number++;
}

bool Stack::isempty(){
	return (head == NULL);
}

StackData* Stack::pop(){ // Stack-pop function
	StackData *temp = head;
	head = head->back;
	temp->back = NULL;
	number--;
	return temp;
}

struct Queue{ // Queue struct
	StackData *front, *rear;
	int number;
	void create();
	bool isempty();
	void enqueue(StackData *);
	StackData* dequeue();
};

void Queue::create(){ // Queue-create function
	front = NULL;
	rear = NULL;
	number = 0;
}

bool Queue::isempty(){ // Queue-isempty function
	return (front == NULL);
}

void Queue::enqueue(StackData *add){ //Enqueue function
	add->next = NULL;
	if (isempty()){
		rear = add;
		front = rear;
	}
	else{
		rear->next = add;
		rear = add;
	}
	number++;
}

StackData* Queue::dequeue(){ // Dequeue function
	StackData *temp;
	temp = front;
	front = front->next;
	temp->next = NULL;
	number--;
	return temp;
}

bool isOperation(char *test){ // Checking string whether operation or not
	char opr[MAX][MAX];
	strcpy(opr[0], "abs");
	strcpy(opr[1], "sqrt");
	strcpy(opr[2], "div");
	strcpy(opr[3], "sub");
	strcpy(opr[4], "exp");
	strcpy(opr[5], "log");
	strcpy(opr[6], "mod");
	strcpy(opr[7], "product");
	strcpy(opr[8], "sum");
	strcpy(opr[9], "min");
	strcpy(opr[10], "max");

	for (int i = 0; i < 11; i++){
		if (!strcmp(test, opr[i])){
			return true;
		}
	}
	return false;
}


long int calculate(Queue &postfix, long int ans, Stack &sayilar, int a){ // main function which calculates the problem
	while (!postfix.isempty()){ // checking whether postfix queue is empty
		StackData *temp = postfix.dequeue(); // dequeue from postfix
		if (isOperation(temp->data)){ // checking whether operation of not
			if (!strcmp(temp->data, "abs")){ // absolute value operation
				if (sayilar.isempty()){ // if there is no number in stack
					cout << "Syntax error." << endl;
					return NULL;
				}
				StackData *temp1;
				temp1 = sayilar.pop();
				StackData *send = new StackData;
				if (!strcmp(temp1->data, "inf")){ // checking infinity conditions
					strcpy(send->data, "inf"); 
				}
				else if (!strcmp(temp1->data, "-inf")){
					strcpy(send->data, "inf");
				}
				else {
					long int value = atol(temp1->data);
					value = abs(value);
					sprintf(send->data, "%Ld", value);
				}
				sayilar.push(send); // pushing result to stack
			}
			else if (!strcmp(temp->data, "sqrt")){ // sqrt operation
				if (sayilar.isempty()){
					cout << "Syntax error." << endl;
					return NULL;
				}
				StackData *temp1;
				temp1 = sayilar.pop();
				StackData *send = new StackData;
				if (!strcmp(temp1->data, "inf")){ // checking inf condition
					strcpy(send->data, "inf");
				}
				else if (!strcmp(temp1->data, "-inf")){
					cout << "Syntax error." << endl;
					return NULL;
				}
				else {
					long int value = atol(temp1->data);
					value = floor(sqrt(value));
					sprintf(send->data, "%Ld", value);
				}
				sayilar.push(send);
			}
			else if (!strcmp(temp->data, "exp")){
				if (sayilar.isempty()){
					cout << "Syntax error." << endl;
					return NULL;
				}
				if (sayilar.number == 1){
					StackData *temp1;
					temp1 = sayilar.pop();
					StackData *send = new StackData;
					if (!strcmp(temp1->data, "inf")){
						strcpy(send->data, "inf");
					}
					else if (!strcmp(temp1->data, "-inf")){
						long int value = 0;
						sprintf(send->data, "%Ld", value);
					}
					else {
						long int value = atol(temp1->data);
						value = floor(exp(value));
						sprintf(send->data, "%Ld", value);
					}
					sayilar.push(send);
				}
				else {
					StackData *temp1 = sayilar.pop();
					StackData *temp2 = sayilar.pop();
					StackData *send = new StackData;
					if (!strcmp(temp2->data, "-inf")){
						long int value = 0;
						sprintf(send->data, "%Ld", value);
					}
					else if ((!strcmp(temp1->data, "inf") || !strcmp(temp1->data, "-inf")) && !strcmp(temp2->data, "inf")){
						cout << "Syntax error." << endl;
						return NULL;
					}
					else {
						long int value1 = atol(temp1->data);
						long int value2 = atol(temp2->data);
						if (value1 == 0 && (!strcmp(temp2->data, "inf") || !strcmp(temp2->data, "-inf"))){
							cout << "Syntax error." << endl;
							return NULL;
						}
						else if (value1 == 1 && !strcmp(temp2->data, "inf")){
							cout << "Syntax error." << endl;
							return NULL;
						}
						else if (value1 < 0 && !strcmp(temp2->data, "inf")){
							cout << "Syntax error." << endl;
							return NULL;
						}
						else if (value1>0 && !strcmp(temp2->data, "inf")){
							strcpy(send->data, "inf");
						}
						else if (!strcmp(temp1->data, "inf") && value2 < 0){
							long int value = 0;
							sprintf(send->data, "%Ld", value);
						}
						else if (!strcmp(temp1->data, "inf") && value2 > 0){
							strcpy(send->data, "inf");
						}
						else if (!strcmp(temp1->data, "inf") && value2 == 0){
							cout << "Syntax error." << endl;
							return NULL;
						}
						else if (!strcmp(temp1->data, "-inf") && value2 % 2 == 0){
							strcpy(send->data, "inf");
						}
						else if (!strcmp(temp1->data, "-inf") && value2 % 2 == 1){
							strcpy(send->data, "-inf");
						}
						
						else {
							long int value = pow((double)value1, (double)value2);
							sprintf(send->data, "%Ld", value);
						}
					}
					sayilar.push(send);
				}
			}
			else if (!strcmp(temp->data, "sub")){
				StackData *temp1 = sayilar.pop();
				StackData *temp2 = sayilar.pop();
				StackData *send = new StackData;
				if (!strcmp(temp1->data, "inf") && !strcmp(temp2->data, "inf")){
					cout << "Syntax error." << endl;
					return NULL;
				}
				else if (!strcmp(temp1->data, "-inf") && !strcmp(temp2->data, "-inf")){
					cout << "Syntax error." << endl;
					return NULL;
				}
				else if (!strcmp(temp1->data, "-inf") && !strcmp(temp2->data, "inf")){
					strcpy(send->data, "-inf");
				}
				else if (!strcmp(temp1->data, "inf") && !strcmp(temp2->data, "-inf")){
					strcpy(send->data, "inf");
				}
				else if (!strcmp(temp1->data, "inf") || !strcmp(temp2->data, "-inf")){
					strcpy(send->data, "inf");
				}
				else if (!strcmp(temp1->data, "-inf") || !strcmp(temp2->data, "inf")){
					strcpy(send->data, "-inf");
				}
				else {
					long int value1 = atol(temp1->data);
					long int value2 = atol(temp2->data);
					long int value = value1 - value2;
					sprintf(send->data, "%Ld", value);
				}
				sayilar.push(send);
			}
			else if (!strcmp(temp->data, "div")){ // You should give numerator with paranthesis 
				if (sayilar.isempty() || sayilar.number < 2){
					cout << "Syntax error." << endl;
					return NULL;
				}
				StackData *temp2 = sayilar.pop();
				StackData *temp1 = sayilar.pop();
				
				StackData *send = new StackData;
				if (!strcmp(temp1->data, "inf") && !strcmp(temp2->data, "inf")){
					cout << "Syntax error." << endl;
					return NULL;
				}
				else if (!strcmp(temp1->data, "-inf") && !strcmp(temp2->data, "-inf")){
					cout << "Syntax error." << endl;
					return NULL;
				}
				else if (!strcmp(temp1->data, "inf") && !strcmp(temp2->data, "-inf")){
					cout << "Syntax error." << endl;
					return NULL;
				}
				else if (!strcmp(temp1->data, "-inf") && !strcmp(temp2->data, "inf")){
					cout << "Syntax error." << endl;
					return NULL;
				}
				else if (!strcmp(temp1->data, "inf")){
					strcpy(send->data, "inf");
				}
				else if (!strcmp(temp1->data, "-inf")){
					strcpy(send->data, "-inf");
				}
				else if (!strcmp(temp2->data, "inf") || !strcmp(temp2->data, "-inf")){
					long int value = 0;
					sprintf(send->data, "%Ld", value);
				}
				else {
					long int value1 = atol(temp1->data);
					long int value2 = atol(temp2->data);
					if (value2 == 0 && value1>0){
						strcpy(send->data, "inf");
					}
					else if (value2 == 0 && value1 < 0){
						strcpy(send->data, "-inf");
					}
					else {
						long int value = floor(value1 / value2);
						sprintf(send->data, "%Ld", value);
					}
				}
				sayilar.push(send);
			}
			else if (!strcmp(temp->data, "log")){
				if (sayilar.isempty()){
					cout << "Syntax error." << endl;
					return NULL;
				}
				if (sayilar.number == 1){
					StackData *temp1;
					temp1 = sayilar.pop();
					StackData *send = new StackData;
					if (!strcmp(temp1->data, "inf")){
						strcpy(send->data, "inf");
					}
					else if (!strcmp(temp1->data, "-inf")){
						cout << "Syntax error." << endl;
						return NULL;
					}
					else {
						long int value = atol(temp1->data);
						if (value <= 0){
							cout << "Syntax error." << endl;
							return NULL;
						}
						else if (value == 1){
							long int value = 0;
							sprintf(send->data, "%Ld", value);
						}
						else {
							value = floor(log(value));
							sprintf(send->data, "%Ld", value);
						}
					}
					sayilar.push(send);
				}
				else {
					StackData *temp1 = sayilar.pop(); // base
					StackData *temp2 = sayilar.pop(); 
					StackData *send = new StackData;
					if (!strcmp(temp1->data, "-inf") || !strcmp(temp2->data ,"-inf")){
						cout << "Syntax error." << endl;
						return NULL;
					}
					else if (!strcmp(temp1->data, "inf") && !strcmp(temp2->data, "inf")){
						cout << "Syntax error." << endl;
						return NULL;
					}
					else if (!strcmp(temp2->data, "inf")){
						strcpy(send->data, "inf");
					}
					else if (!strcmp(temp1->data, "inf")){
						long int value = 0;
						sprintf(send->data, "%Ld", value);
					}
					else {
						long int value1 = atol(temp1->data);
						long int value2 = atol(temp2->data);
						
						if (value1 <= 0 || value2 <= 0){
							cout << "Syntax error." << endl;
							return NULL;
						}
						else if (value2 == 1){
							long int value = 0;
							sprintf(send->data, "%Ld", value);
						}
						else {
							long int value = floor(log(value2) / log(value1));
							sprintf(send->data, "%Ld", value);
						}	
					}
					sayilar.push(send);
				}
			}
			else if (!strcmp(temp->data,"mod")){
				if (sayilar.isempty()){
					cout << "Syntax error." << endl;
					return NULL;
				}
				if (sayilar.number == 1){
					StackData *temp1;
					temp1 = sayilar.pop();
					StackData *send = new StackData;
					if (!strcmp(temp1->data, "-inf") || !strcmp(temp1->data, "inf")){
						cout << "Syntax error." << endl;
						return NULL;
					}
					else {
						long int value = atol(temp1->data);
						value = value % 10;
						sprintf(send->data, "%Ld", value);
					}
					sayilar.push(send);
				}
				else {
					StackData *temp1 = sayilar.pop();
					StackData *temp2 = sayilar.pop();
					StackData *send = new StackData;
					if (!strcmp(temp1->data, "-inf") || !strcmp(temp1->data, "inf") || !strcmp(temp2->data, "inf") || !strcmp(temp2->data,"-inf")){
						cout << "Syntax error." << endl;
						return NULL;
					}
					else {
						long int value1 = atol(temp1->data);
						long int value2 = atol(temp2->data);
						long int value = value2 % value1;
						sprintf(send->data, "%Ld", value);
					}
					sayilar.push(send);
				}
			}
			else if (!strcmp(temp->data, "sum")){
				if (sayilar.isempty()){
					cout << "Syntax error." << endl;
					return NULL;
				}
				long int value = 0;
				StackData *send = new StackData;
				while (!sayilar.isempty()){
					StackData *temp1 = sayilar.pop();
					if (!strcmp(temp1->data, "inf")){
						while (!sayilar.isempty()){
							StackData *test = sayilar.pop();
							if (!strcmp(test->data, "-inf")){
								cout << "Syntax error." << endl;
								return NULL;
							}
						}
						strcpy(send->data, "inf");
						break;
					}
					else if (!strcmp(temp1->data, "-inf")){
						while (!sayilar.isempty()){
							StackData *test = sayilar.pop();
							if (!strcmp(test->data, "inf")){
								cout << "Syntax error." << endl;
								return NULL;
							}
						}
						strcpy(send->data, "-inf");
						break;
					}
					else {
						long int value1 = atol(temp1->data);
						value += value1;
						sprintf(send->data, "%Ld", value);
					}
				}
				sayilar.push(send);
			}
			else if (!strcmp(temp->data, "product")){
				if (sayilar.isempty()){
					cout << "Syntax error." << endl;
					return NULL;
				}
				long int value = 1;
				StackData *send = new StackData;
				while (!sayilar.isempty()){
					StackData *temp1 = sayilar.pop();
					if (!strcmp(temp1->data, "-inf")){
						
						long int value = 1;
						while (!sayilar.isempty()){
							StackData *test = sayilar.pop();
							if (!strcmp(test->data, "inf") || !strcmp(test->data, "-inf")){
								cout << "Syntax error." << endl;
								return NULL;
							}
							long int value1 = atol(test->data);
							value *= value1;
						}
						if (value < 0){
							strcpy(send->data, "inf");
							break;
						}
						else if (value>0){
							strcpy(send->data, "-inf");
							break;
						}
						else {
							value = 0;
							sprintf(send->data, "%Ld", value);
						}
					}
					else if (!strcmp(temp1->data, "inf")){
						strcpy(send->data, "inf");
						long int value = 1;
						while (!sayilar.isempty()){
							StackData *test = sayilar.pop();
							if (!strcmp(test->data, "inf") || !strcmp(test->data, "-inf")){
								cout << "Syntax error." << endl;
								return NULL;
							}
							long int value1 = atol(test->data);
							value *= value1;
						}
						if (value < 0){
							strcpy(send->data, "-inf");
							break;
						}
						else if (value>0){
							strcpy(send->data, "inf");
							break;
						}
						else {
							value = 0;
							sprintf(send->data, "%Ld", value);
						}
					}
					else {
						long int value1 = atol(temp1->data);
						if (value1 == 0){
							value = 0;
							sprintf(send->data, "%Ld", value);
						}
						else {
							value *= value1;
							sprintf(send->data, "%Ld", value);
						}
					}
				}
				sayilar.push(send);
			}
			else if (!strcmp(temp->data, "min")){
				if (sayilar.isempty()){
					cout << "Syntax error." << endl;
					return NULL;
				}
				long int value = LONG_MAX;
				StackData *send = new StackData;
				while (!sayilar.isempty()){
					StackData *temp1 = sayilar.pop();
					if (!strcmp(temp1->data, "-inf")){
						strcpy(send->data, "-inf");
						break;
					}
					else {
						long int value1 = atol(temp1->data);
						if (value1 < value){
							value = value1;
						}
					}
				}
				sprintf(send->data, "%Ld", value);
				sayilar.push(send);
			}
			else if (!strcmp(temp->data, "max")){
				if (sayilar.isempty()){
					cout << "Syntax error." << endl;
					return NULL;
				}
				long int value = LONG_MIN;
				StackData *send = new StackData;
				while (!sayilar.isempty()){
					StackData *temp1 = sayilar.pop();
					if (!strcmp(temp1->data, "inf")){
						strcpy(send->data, "inf");
						break;
					}
					long int value1 = atol(temp1->data);
					if (value1 > value){
						value = value1;
					}
				}
				sprintf(send->data, "%Ld", value);
				sayilar.push(send);
			}
		}
		else if (!strcmp(temp->data, "ans")){ // if string is not an operation then looking whether is answer or not
			sprintf(temp->data, "%Ld", ans);
			sayilar.push(temp); 
		}
		else {
			if (!strncmp(temp->data, "0", 1)){ // because atol function(4 line below) if data is 0 we need to keep
				sayilar.push(temp);
			}
			else {
				long int x = atol(temp->data); // when atol function don't work correctly then returns 0
				if (x == 0 && strcmp(temp->data, "inf") && strcmp(temp->data, "-inf")){
					cout << "Syntax error." << endl;
					return NULL;
				}
				else if (x == LONG_MAX){
					strcpy(temp->data, "inf");
				}
				else if (x == LONG_MIN){
					strcpy(temp->data, "-inf");
				}
				sayilar.push(temp);
			}
		}
	}
	StackData *result = sayilar.pop();

	if (!sayilar.isempty()){
		cout << "Syntax error." << endl;
		return NULL;
	}
	if (!strcmp(result->data, "inf")){
		cout << "inf" << endl;
		return LONG_MAX;
	}
	else if (!strcmp(result->data, "-inf")){
		cout << "-inf" << endl;
		return LONG_MIN;
	}
	else {
		long int result1 = atol(result->data);
		if (a == 2){ // if we call calculate function without file printing results else just return
			cout << result1 << endl;
		}
		return result1;
		
	}
}

int main(int argc, char **argv){
	char s[MAX];
	ifstream input;
	
	if (argc == 2){
		input.open(argv[1], ios::out | ios::in); // opening file from terminal
		long int ans=0;
		cout << "Answer queue: ";
		Queue answer; // Queue for answers
		answer.create();
		while (input.getline(s, MAX)){ // while we can read a line
			Queue postfix;
			postfix.create();
			char *temp;
			char delim1 = '(';
			char delim2 = ')';
			temp = strtok(s, " ,\n"); // separating string
			Stack main;
			main.create();
			StackData *temp2;
			while (temp != NULL){
				StackData *temp1 = new StackData;
				strcpy(temp1->data, temp);
				main.push(temp1);
				if (!strncmp(temp, &delim2, sizeof(char))){ // if separated string is ) 
					main.pop(); // then poping ')'
					temp2 = main.pop(); // then poping one more from stack
					while (strncmp(temp2->data, &delim1, sizeof(char))){ // if poping one is not '(' 
						postfix.enqueue(temp2);  // enqueue
						temp2 = main.pop(); // pop one more
					}
				}
				temp = strtok(NULL, " ,\n"); // separating string
			}
			while (!main.isempty()){ // if stack is not empty
				temp2 = main.pop(); // poping them 
				postfix.enqueue(temp2); // enqueue
			}
			ans = calculate(postfix,ans,main,1); // calling calculation function
			StackData *temp9 = new StackData;
			sprintf(temp9->data, "%Ld", ans);
			answer.enqueue(temp9); // enqueue
		}
		while (!answer.isempty()){  // printing answer queue
			StackData *temp10 = new StackData;
			temp10 = answer.dequeue();
			if (answer.number == 0) {
				cout << temp10->data;
			}
			else {
				cout << temp10->data << " -> ";
			}
		}
		cout << endl;
	}

	else if (argc == 1){
		long int ans = 0;
		Queue answer;
		answer.create();
		cout << "Initializing the interpreter..." << endl;
		while (1){
			
			cout << endl;
			cout << ">> ";
			cin.getline(s, MAX); // reading line
			Queue postfix; // postfix Queue
			postfix.create();
			char *temp;
			char delim1 = '(';
			char delim2 = ')';
			temp = strtok(s, " "); // separating string
			Stack main; 
			main.create();
			StackData *temp2;
			if (temp == NULL || !strcmp(temp, "exit")){ // if user enter exit
				cout << "Terminating the interpreter..." << endl;
				cout << "Answer queue: ";
				while (!answer.isempty()){ // printing answer queue
					StackData *temp10 = new StackData;
					temp10 = answer.dequeue();
					if (answer.number == 0) {
						cout << temp10->data;
					}
					else {
						cout << temp10->data << " -> ";
					}
				}
				cout << endl;
				return 0; 
			}
			else {
				cout << "Postfix string: "; // printing string
				while (temp != NULL){
					StackData *temp1 = new StackData;
					strcpy(temp1->data, temp);
					main.push(temp1);
					if (!strncmp(temp, &delim2, sizeof(char))){ // if separated string is )
						main.pop(); // then poping ')'
						temp2 = main.pop(); // then poping one more from stack
						while (strncmp(temp2->data, &delim1, sizeof(char))){
							cout << temp2->data << " "; // if poping one is not '('
							postfix.enqueue(temp2); // enqueue
							temp2 = main.pop(); // pop one more
						}
					}
					temp = strtok(NULL, " ,\n"); // separating string
				}
				while (!main.isempty()){ // if stack is not empty
					
					temp2 = main.pop(); // poping them 
					cout << temp2->data << " "; // printing
					postfix.enqueue(temp2);// enqueue
				}
			}
			cout << endl;
			ans = calculate(postfix, ans, main,2); // calling calculation function
			StackData *temp9 = new StackData;
			sprintf(temp9->data, "%Ld", ans);
			answer.enqueue(temp9); // enqueue

		}
	}
 	return 0;
}
