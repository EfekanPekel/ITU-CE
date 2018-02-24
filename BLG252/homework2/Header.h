/* @Author
* Student Name: Mustafa Efekan PEKEL
* Student ID: 150140050
* Date: 27.04.2017
*/

#include <cstdio> // Including necessary libraries
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

struct Node { // Node struct for keep data
	int data;
	Node* next;
	Node* back;
};

class ARTraverser{ // ARTraverser class
	friend class AdderRemover; // To access data in ARTraverser 
protected: // Protected part of class
	Node* current;
public: // Public part of class
	virtual bool hasNode() = 0; // Pure virtual functions
	virtual Node* next() = 0; 
	ARTraverser(); // Constructor
	~ARTraverser(); // Destructor
};


class AdderRemover{ // AdderRemover class
protected: // Protected part of class
	Node* head; 
	Node* tail;
	string name;
	int nodeCount;
	ARTraverser* traverser;
public: // Public part of class
	virtual void add(int) = 0; // Pure virtual functions
	virtual void remove() = 0;
	virtual void setTraverser() = 0;
	void display(); // Not virtual functions
	void removeAll();
	void traverse();
	~AdderRemover(); // Destructor

};

AdderRemover::~AdderRemover(){ // Destructor
	removeAll(); // removing all elements except head
	delete head; // deleting head
	delete tail; // deleting tail
	delete traverser; // deleting traverser
}

void AdderRemover::traverse(){ // Traverse function
	cout << name << " | NodeCount:" << nodeCount << endl;
	cout << "------" << endl;
	if (nodeCount == 0){
		cout << "There is no element to print" << endl;
	}
	else {
		while (traverser->hasNode()){
			cout << traverser->current->data << endl;
			traverser->next();
		}
	}
	cout << endl;
}

void AdderRemover::display(){ // Display function
	cout << name << " | NodeCount:" << nodeCount << endl;
	cout << "------" << endl;
	if (nodeCount == 0){
		cout << "There is no element to print" << endl;
	}
	else {
		Node *trav = head;
		while (trav != NULL){
			cout << trav->data << endl;
			trav = trav->next;
		}
	}
	cout << endl;
}

void AdderRemover::removeAll(){ // RemoveAll Function
	Node *trav = head->next; // For removing used two node variable
	Node *todelete = head->next;
	for (int i = 0; i < nodeCount-1; i++){
		trav = trav->next;
		delete todelete;
		todelete = trav;
	}
	head = NULL;
	nodeCount = 0; // Assigning nodeCount to 0
}


ARTraverser::ARTraverser(){ // Constructor for ARTraverser
	current = NULL;
}

ARTraverser::~ARTraverser(){ // Destructor for ARTraverser
	delete current;
}



class ARTF : public ARTraverser{ // ARTF class
public: 
	ARTF(Node*);
	bool hasNode();
	Node* next();
};

class ARTL : public ARTraverser{ // ARTL class
public:
	ARTL(Node*);
	bool hasNode();
	Node* next();
};

ARTF::ARTF(Node* input){ // ARTF constructor
	current = input;
}

ARTL::ARTL(Node *input){ // ARTL destructor
	current = input;
}

bool ARTF::hasNode(){ // hasNode function
	if (current == NULL){
		return false;
	}
	return true;
}

bool ARTL::hasNode(){ // hasNode function
	if (current == NULL){
		return false;
	}
	return true;
}

Node* ARTF::next(){ // next function for ARTF
	current = current->next;
	return current;
}

Node* ARTL::next(){ // next function for ARTL
	current = current->back;
	return current;
}

class FAFR : public AdderRemover{ // FAFR class
public:
	FAFR();// Constructor
	void add(int);
	void remove();
	void setTraverser();
};

class FALR : public AdderRemover{ // FALR class
public:
	FALR();// Constructor
	void add(int);
	void remove();
	void setTraverser();
};

class LAFR : public AdderRemover{ // LAFR class
public:
	LAFR(); // Constructor
	void add(int);
	void remove();
	void setTraverser();
};

class LALR : public AdderRemover{ // LALR class
public:
	LALR();// Constructor
	void add(int);
	void remove();
	void setTraverser();
};

FAFR::FAFR(){ // Constructor
	name = "FAFR";
	head = NULL;
	tail = NULL;
	nodeCount = 0;
	traverser = NULL;
}

FALR::FALR(){// Constructor
	name = "FALR";
	head = NULL;
	tail = NULL;
	nodeCount = 0;
	traverser = NULL;
}

LAFR::LAFR(){// Constructor
	name = "LAFR";
	head = NULL;
	tail = NULL;
	nodeCount = 0;
	traverser = NULL;
}

LALR::LALR(){// Constructor
	name = "LALR";
	head = NULL;
	tail = NULL;
	nodeCount = 0;
	traverser = NULL;
}

void FAFR::add(int toadd){ // FAFR add function
	if (head == NULL){
		head = new Node;
		head->data = toadd;
		head->next = NULL;
		head->back = NULL;
		tail = head;
	}
	else{
		Node *add = new Node;
		add->data = toadd;
		add->next = head;
		head->back = add;
		add->next = head;
		head = add;
	}
	nodeCount++;
}

void FAFR::remove(){ // FAFR remove function
	Node *remove = head;
	if (head == NULL){
		cout << "There is no element to remove" << endl;
	}
	else{
		head = head->next;
		head->back = NULL;
		delete remove;
		nodeCount--;
	}
	
}

void FALR::add(int toadd){ // FALR add function
	if (head == NULL){
		head = new Node;
		head->data = toadd;
		head->next = NULL;
		head->back = NULL;
		tail = head;
	}
	else{
		Node *add = new Node;
		add->data = toadd;
		add->next = head;
		head->back = add;
		add->next = head;
		head = add;
	}
	nodeCount++;
}

void FALR::remove(){ // FALR remove function
	Node *remove;
	remove = tail;
	if (head == NULL){
		cout << "There is no element to remove" << endl;
	}
	else{
		tail = tail->back;
		tail->next = NULL;
		remove->back = NULL;
		delete remove;
		nodeCount--;
	}
}

void LAFR::add(int toadd){ // LAFR add function
	if (head == NULL){
		head = new Node;
		head->data = toadd;
		head->next = NULL;
		head->back = NULL;
		tail = head;
	}
	else {
		Node *add = new Node;
		add->data = toadd;
		add->back = tail;
		add->next = NULL;
		tail->next = add;
		tail = add;
	}
	nodeCount++;
}

void LAFR::remove(){ // LAFR remove function
	if (head == NULL){
		cout << "There is no element to remove" << endl;
	}
	else{
		Node *remove = head;
		head = head->next;
		head->back = NULL;
		delete remove;
		nodeCount--;
	}

}

void LALR::add(int toadd){ // LALR add function
	if (head == NULL){
		head = new Node;
		head->data = toadd;
		head->next = NULL;
		head->back = NULL;
		tail = head;
	}
	else {
		Node *add = new Node;
		add->data = toadd;
		add->back = tail;
		add->next = NULL;
		tail->next = add;
		tail = add;
	}
	nodeCount++;
}

void LALR::remove(){ // LALR remove function
	Node *remove;
	remove = tail;
	if (head == NULL){
		cout << "There is no element to remove" << endl;
	}
	else{
		tail = tail->back;
		tail->next = NULL;
		remove->back = NULL;
		delete remove;
		nodeCount--;
	}
}

void FAFR::setTraverser(){ // FAFR setTraverser function
	traverser = new ARTF(head);
}

void FALR::setTraverser(){// FALR setTraverser function
	traverser = new ARTF(head);
}

void LALR::setTraverser(){// LALR setTraverser function
	traverser = new ARTL(tail);
}
void LAFR::setTraverser(){// LAFR setTraverser function
	traverser = new ARTL(tail);
}


