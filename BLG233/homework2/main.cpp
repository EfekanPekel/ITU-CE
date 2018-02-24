/* @Author
* Student Name: Mustafa Efekan PEKEL
* Student ID : 150140050
* Date: 22.11.2016 */


#define _CRT_SECURE_NO_WARNINGS
#include "definitions.h" //including structures
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

list *liste = new list; //list of playlists
ifstream songbook("songbook.txt", ios::in | ios::out); // openning file to read
ofstream output("songbook.txt", ios::out | ios::app);  // openning file to write

void printList(playlist *head, bool sth); // function definitions
void myadd(playlist *pl, song_node *temp);
void deleteList(playlist *headpl, bool sth);
void addSong(playlist *headpl, bool sth);
void removeSong(playlist *headpl, bool sth);
playlist *createList(bool sth);

playlist *sorted; // defined globally to reach in every function
int default_number;

song_node *sortedPlaylist(song_node *head) { // this function produces sorted playlist
	//song_node *sorted = head;
	song_node *temp = new song_node;
	temp = head;
	for (int i = 0; i<1000; i++){
		temp = head;
		while (temp->next != head){
			if (strcmp(temp->data->singer, temp->next->data->singer) > 0) {
				swap(temp->data, temp->next->data);
			}
			else if (strcmp(temp->data->singer, temp->next->data->singer) == 0 && strcmp(temp->data->name, temp->data->name) > 0){
				swap(temp->data, temp->next->data);
			}
			temp = temp->next;
		}
	}
	return head;
}

song_node *randomPlaylist(song_node *one) { // this function produces random playlist
	srand(time(NULL));
	song_node *temp1 = one;
	song_node *temp2 = one;
	for (int k = 0; k<100; k++){
		int i = rand() % 20;
		int j = rand() % 20;
		for (int a = 0; a<i; a++){
			temp1 = temp1->next;
		}
		for (int a = 0; a<j; a++){
			temp2 = temp2->next;
		}
		swap(temp1->data, temp2->data);
	}
	return one;
}

void printMenu() { // printing the menu
	cout << "SONG BOX APPLICATION (USING DOUBLY, CIRCULAR MULTI LINKED LIST)" << endl;
	cout << "Choose an operation" << endl;
	cout << "P: Play" << endl;
	cout << "L: Show all playlists" << endl;
	cout << "A: Add songs to a playlist" << endl;
	cout << "R: Remove songs from a playlist" << endl;
	cout << "C: Create a new playlist" << endl;
	cout << "D: Delete a playlist" << endl;
	cout << "W: Write to file (SAVE)" << endl;
	cout << "E: Exit" << endl;
	cout << endl;
	cout << "Enter a choice (P,L,A,R,C,D,W,E): ";
}

void printList(playlist *head, bool sth) { // printing the playlists, has two inputs, playlist input for from which playlist, bool input for to call from another function
	// if bool is false, function just lists playlists
	cout << "PLAYLISTS :" << endl;
	playlist *temp = head;
	int i = 1;
	do {
		cout << i << ": " << temp->name << endl;
		temp = temp->next;
		i++;
	} while (temp != head);
	temp = head;
	if (sth == true){ // when calling function in main with bool true, function lists other options like play, add etc.
		i = 1;
		char choice;

		do {
			cout << endl;
			if (i>liste->playlist_count){
				i = i - liste->playlist_count;
			}
			else if (i == 0) {
				i = i + liste->playlist_count;
			}
			cout << i << ": " << temp->name << endl;
			cout << "PLAY(S) - DELETE(D) - ADD SONG(S) - REMOVE SONG(S) - NEXT(N) - PREVIOUS(P) - nth(index number) - EXIT(E)" << endl;
			cin >> choice;
			if (tolower(choice) == 's'){
				char choice2;
				cout << "P: Play the songs in the playlist" << endl;
				cout << "A: Add song to playlist" << endl;
				cout << "R: Remove song from playlist" << endl;
				cout << "Enter a choice (P,A,R): ";
				cin >> choice2;
				if (tolower(choice2) == 'p'){
					char choice3;
					song_node *temp1 = temp->head;
					do{
						cout << endl;
						cout << "PLAY>" << endl;
						cout << "playing . . ." << endl;
						cout << temp1->data->name << " - " << temp1->data->singer << " - " << temp1->data->style << endl;
						cout << "NEXT(N) - PREVIOUS(P) - EXIT(E)" << endl;
						cin >> choice3;
						if (tolower(choice3) == 'n'){
							temp1 = temp1->next;
						}
						else if (tolower(choice3) == 'p'){
							temp1 = temp1->prev;
						}

					} while (tolower(choice3) != 'e');
				}
				else if (tolower(choice2) == 'a'){
					addSong(temp, false);
				}
				else if (tolower(choice2) == 'r'){
					removeSong(temp, false);
				}
			}
			else if (tolower(choice) == 'd'){
				deleteList(temp, false);
				cout << endl;
				choice = 'e';
			}
			else if (tolower(choice) == 'n'){
				i++;
				temp = temp->next;
			}
			else if (tolower(choice) == 'p'){
				i--;
				temp = temp->prev;
			}
		} while (choice != 'e');
	}
}

playlist *createList(bool sth) { // function creating playlist
	playlist *soundtrack = new playlist;
	soundtrack->head = new song_node;
	soundtrack->head->data = new song;
	soundtrack->head = NULL;
	soundtrack->songnumber = 0;
	playlist *trav = liste->head->prev;
	int selection;
	if (sth == true){
		cout << "CREATE PLAYLIST > " << endl;
		cout << "Choose an option" << endl;
		cout << "1. Songs of specific style" << endl;
		cout << "2. Songs of specific singer" << endl;
		cout << "3. A combination of existing playlists" << endl;
		cout << "4. A combination of existing songs" << endl;
		cout << endl;
		cout << "Enter a choice(1,2,3,4): ";
		cin >> selection;
		cout << "Enter a playlist name:" << endl;
		getchar();
		cin.getline(soundtrack->name, LNAME_LENGTH);
		if (selection == 1) { // creating from specific style
			char style[STYLE_LENGTH];
			cout << "Please enter a style name: ";
			cin.getline(style, STYLE_LENGTH);
			cout << style << endl;
			song_node *temp = liste->head->head;
			do {
				if (strcmp(temp->data->style, style) == 0){
					myadd(soundtrack, temp);
				}
				temp = temp->next;
			} while (temp != liste->head->head);
		}
		else if (selection == 2){ // creating from specific singer
			char singer[SINGER_LENGTH];
			cout << "Please enter a singer name: ";
			cin.getline(singer, SINGER_LENGTH);
			cout << singer << endl;
			song_node *temp = liste->head->head;
			do {
				if (strcmp(temp->data->singer, singer) == 0){
					myadd(soundtrack, temp);
				}
				temp = temp->next;
			} while (temp != liste->head->head);
		}
		else if (selection == 3){ // creating with combining two playlist
			printList(liste->head, false);
			int one, two;
			cout << "Please enter two indexes: ";
			cin >> one;
			cin >> two;
			playlist *temp1 = liste->head;
			playlist *temp2 = liste->head;
			for (int i = 1; i<one; i++){
				temp1 = temp1->next;
			}
			for (int i = 1; i<two; i++){
				temp2 = temp2->next;
			}
			song_node *temp = temp1->head;
			do {
				myadd(soundtrack, temp);
				temp = temp->next;
			} while (temp != temp1->head);

			temp = temp2->head;
			do {
				myadd(soundtrack, temp);
				temp = temp->next;
			} while (temp != temp2->head);

		}
		else if (selection == 4){
			int selection;
			while (1){
				song_node *temp3 = sorted->head;
				int j = 1;
				do{
					cout << j << ". " << temp3->data->name << "\t" << temp3->data->singer << "\t" << temp3->data->style << endl;
					temp3 = temp3->next;
					j++;
				} while (temp3 != sorted->head);
				cout << "Please enter index of song to add playlist(to terminate enter -1): ";
				cin >> selection;
				if (selection == -1){
					break;
				}
				temp3 = sorted->head;
				for (int i = 1; i < selection; i++){
					temp3 = temp3->next;
				}
				myadd(soundtrack, temp3);
			}
		}
	}

	trav->next = soundtrack;
	soundtrack->prev = trav;
	soundtrack->next = liste->head;
	liste->head->prev = soundtrack;
	liste->playlist_count++;

	return soundtrack;
}

void deleteList(playlist *headpl, bool sth){ // deleting playlist, playlist input that first playlist or selected input, bool input to call from another function
	playlist *temp = headpl;
	if (sth == true){ // if bool is true function asks which playlist to delete
		printList(headpl, false);
		int selection;
		do{
			cout << "Please enter index of playlist to delete: ";
			cin >> selection;
		} while (selection == 1 || selection == 2 || selection == 3);
		for (int i = 1; i < selection; i++){
			temp = temp->next;
		}
	}
	// if bool is false function do not ask playlist, playlist input is deleting
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	song_node *temp1 = temp->head;
	do{
		delete[] temp1->data->name;
		delete[] temp1->data->singer;
		delete[] temp1->data->style;
		temp1 = temp1->next;
	} while (temp1 != temp->head);
	delete[] temp->name;
	liste->playlist_count--;
	cout << "Playlist deleted succesfully!" << endl;

}

void addSong(playlist *headpl, bool sth){ // adding song to the playlist, playlist input for first playlist to reach other playlists or selected input, bool input for calling from other functions
	playlist *temp = headpl;
	int selection, selection2;
	if (sth == true){ // if bool is true, function asks playlist to add song
		printList(headpl, false);
		cout << "Please enter index of playlist that you want to add song: ";
		cin >> selection;
		for (int i = 1; i < selection; i++){
			temp = temp->next;
		}
	}

	// if bool is false, playlist input is selected.
	song_node *temp1 = sorted->head;
	int j = 1;
	do {
		cout << j << ". " << temp1->data->singer << '\t' << temp1->data->name << endl;
		temp1 = temp1->next;
		j++;
	} while (temp1 != sorted->head);
	cout << "Please enter index of song that you want to add: ";
	cin >> selection2;
	temp1 = sorted->head;
	for (int i = 1; i < selection2; i++){
		temp1 = temp1->next;
	}
	myadd(temp, temp1);
	cout << "Song has added succesfully!" << endl;
}

void removeSong(playlist *headpl, bool sth){ // removing song from playlist, playlist input to reach all playlists or selected input, bool input for calling from other functions
	playlist *temp = headpl;
	int selection, selection2;
	if (sth == true){ // if bool is true, function asks playlist
		printList(headpl, false);
		cout << "Please enter index of playlist that you want to remove song:  ";
		cin >> selection;
		for (int i = 1; i < selection; i++){
			temp = temp->next;
		}
	}
	// if bool is false, playlist input is selected.
	song_node *temp1 = temp->head;
	int j = 1;
	do {
		cout << j << ". " << temp1->data->singer << '\t' << temp1->data->name << endl;
		temp1 = temp1->next;
		j++;
	} while (temp1 != temp->head);
	cout << "Please enter index of song that you want to remove: ";
	cin >> selection2;
	temp1 = temp->head;
	for (int i = 1; i < selection2; i++){
		temp1 = temp1->next;
	}

	temp1->prev->next = temp1->next;
	temp1->next->prev = temp1->prev;
	delete[] temp1->data->name;
	delete[] temp1->data->singer;
	delete[] temp1->data->style;
	cout << "Song has removed succesfully!" << endl;
}

void play(playlist *headpl) { // function to play playlist or song
	char selection2, selection4;
	int selection, selection3;
	cout << "PLAY >" << endl;
	cout << "Choose an option" << endl;
	cout << "L: Play a playlist" << endl;
	cout << "S: Play a playlist starting from a specific song" << endl;
	cout << "P: Play a single song" << endl;
	cout << "E: Exit" << endl;
	cout << endl;
	cout << "Enter a choice (L, S, P, E): ";
	cin >> selection2;
	playlist *temp = NULL;
	song_node *temp1 = NULL;
	if (selection2 == 'e'){
		return;
	}
	else{
		do {
			if (tolower(selection2) == 'l') { // playing playlist from first song
				printList(headpl, false);
				cout << "Please enter index of playlist that you want to play: ";
				cin >> selection;
				temp = headpl;
				for (int i = 1; i < selection; i++){
					temp = temp->next;
				}
				temp1 = temp->head;
			}
			else if (tolower(selection2) == 's'){ // playing playlist from selected song
				printList(headpl, false);
				cout << "Please enter index of playlist that you want to play: ";
				cin >> selection;
				temp = headpl;
				for (int i = 1; i < selection; i++){
					temp = temp->next;
				}
				temp1 = temp->head;
				int j = 1;
				do {
					cout << j << ". " << temp1->data->singer << '\t' << temp1->data->name << endl;
					temp1 = temp1->next;
					j++;
				} while (temp1 != temp->head);
				cout << "Please enter index of song that you want to play: ";
				cin >> selection3;
				temp1 = temp->head;
				for (int i = 1; i < selection3; i++){
					temp1 = temp1->next;
				}
			}
			else if (tolower(selection2) == 'p') { // playing song that user selected from sorted playlist
				song_node *temp2 = sorted->head;
				int j = 1;
				do {
					cout << j << ". " << temp2->data->singer << '\t' << temp2->data->name << endl;
					temp2 = temp2->next;
					j++;
				} while (temp2 != sorted->head);
				cout << "Please enter index of song that you want to play: ";
				cin >> selection3;
				temp = sorted;
				temp1 = temp->head;
				for (int i = 1; i < selection3; i++){
					temp1 = temp1->next;
				}
			}
			cout << endl;
			cout << "PLAY>" << endl;
			cout << "playing . . ." << endl;
			cout << temp1->data->name << " - " << temp1->data->singer << " - " << temp1->data->style << endl;
			cout << "NEXT(N) - PREVIOUS(P) - EXIT(E)" << endl;
			cin >> selection4;
			if (selection4 == 'n'){
				temp1 = temp1->next;
				selection2 = 'a';
			}
			else if (selection4 == 'p'){
				temp1 = temp1->prev;
				selection2 = 'a';
			}
		} while (selection2 != 'e' && selection4 != 'e');
	}
}

void myadd(playlist *pl, song_node *temp){ // adding song to playlist, copying song before adding to keep song
	song_node *mytemp = new song_node;
	mytemp->data = new song;
	strcpy(mytemp->data->name, temp->data->name);
	strcpy(mytemp->data->singer, temp->data->singer);
	strcpy(mytemp->data->style, temp->data->style);
	mytemp->data->year = temp->data->year;
	if (pl->head == NULL) {
		pl->head = mytemp;
		pl->head->next = pl->head;
		pl->head->prev = pl->head;
	}
	else {
		mytemp->next = pl->head;
		mytemp->prev = pl->head->prev;
		pl->head->prev->next = mytemp;
		pl->head->prev = mytemp;
	}
	pl->songnumber++;
}

void writeToFile() { // writing created playlist to the file
	//playlist *temp1 = sorted->next->next;
	playlist *temp1 = liste->head;
	for (int j = 0; j < default_number; j++){
		temp1 = temp1->next;
	}
	playlist *temp = temp1;

	while(temp!= liste->head){
		output << endl;
		output << "*****" << endl;
		output << temp->name << endl;
		for (int i = 0; i < temp->songnumber; i++){
			if (i == temp->songnumber - 1){
				output << temp->head->data->name << "\t" << temp->head->data->singer << "\t" << temp->head->data->year << "\t" << temp->head->data->style;
			}
			else {
				output << temp->head->data->name << "\t" << temp->head->data->singer << "\t" << temp->head->data->year << "\t" << temp->head->data->style << endl;
			}
			temp->head = temp->head->next;
		}
		temp = temp->next;
	}
}

void exit(){ // deleting all data
	playlist *temp = liste->head;
	do {
		for (int i = 0; i < temp->songnumber; i++){
			delete[] temp->head->data->name;
			delete[] temp->head->data->singer;
			delete[] temp->head->data->style;
			song *tmp1 = temp->head->data;
			song_node *tmp2 = temp->head;

			temp->head = temp->head->next;
			delete tmp1;
			delete tmp2;
		}
		delete[] temp->name;
		temp = temp->next;
	} while (temp != liste->head);
}


int main() {
	srand(time(NULL));
	song_node *head = NULL;
	song_node *temp = new song_node;
	playlist *chrono = new playlist;
	chrono->head = NULL;
	chrono->songnumber = 0;
	sorted = new playlist;
	sorted->head = NULL;
	sorted->songnumber = 0;
	playlist *random = new playlist;
	random->head = NULL;
	random->songnumber = 0;
	temp->data = new song;
	for (int i = 0; i < 22;i++) {
		songbook.getline(temp->data->name, 50, '\t');//reading file
		songbook.getline(temp->data->singer, 50, '\t'); // reading singer
		songbook >> temp->data->year; // reading year
		songbook.ignore(1, 't');
		songbook.getline(temp->data->style, 50, '\n'); // reading style
		myadd(sorted, temp); // adding to the sorted playlist with calling myadd function
		myadd(chrono, temp); // adding to the chrono playlist with calling myadd function
		myadd(random, temp); // adding to the random playlist with calling myadd function
		temp = new song_node; // emptying temp song
		temp->data = new song;
	}

	liste->head = NULL;
	temp = head;
	chrono->name = "CHRONOLOGICAL";
	playlist *headpl = chrono; // defining headpl to send functions and set to first playlist
	// connections of default playlists
	liste->head = headpl;
	sorted->head = sortedPlaylist(sorted->head); // producing sorted list
	sorted->name = "SORTED";
	random->head = randomPlaylist(random->head); // producing random list
	random->name = "RANDOM";
	chrono->next = sorted;
	sorted->prev = chrono;
	sorted->next = random;
	random->prev = sorted;
	random->next = chrono;
	chrono->prev = random;

	liste->playlist_count = 3;
	char *tester = "*****";
	char *temp2 = new char[5];
	char *temp3 = new char[500];
	songbook.getline(temp3, 50, '\n');
	while (strncmp(temp3, tester,5) == 0){
		playlist *created = new playlist;
		created = createList(false);
		songbook.getline(created->name, 50, '\n');
		temp = new song_node;
		temp->data = new song;
		temp->next = NULL;
		temp->prev = NULL;

		while (songbook.getline(temp3, 500, '\n') && strncmp(temp3, tester, 5)){
			temp->data->name = strtok(temp3, "\t");
			temp->data->singer = strtok(NULL, "\t");
			temp->data->year = atoi(strtok(NULL, "\t"));
			temp->data->style = strtok(NULL, "\n");
			myadd(created, temp);
			temp = new song_node;
			temp->data = new song;
		}

	}

	default_number = liste->playlist_count;

	char selection;

	while (1){
		printMenu(); // printing menu with function
		cin >> selection; // getting input of selection
		if (tolower(selection) == 'p') {
			play(headpl); // calling play function
		}
		else if (tolower(selection) == 'l'){
			printList(headpl, true); // calling printList function with bool true
			cout << endl;
		}
		else if (tolower(selection) == 'a'){
			addSong(headpl, true); // calling addSong function with bool true
			cout << endl;
		}
		else if (tolower(selection) == 'r'){
			removeSong(headpl, true); // calling removeSong function with bool true
			cout << endl;
		}
		else if (tolower(selection) == 'c'){
			createList(true); // calling createList function
			cout << "Playlist created succesfully!" << endl;
			cout << endl;
		}
		else if (tolower(selection) == 'd'){
			deleteList(headpl, true); // calling deleteList function with bool true
		}
		else if (tolower(selection) == 'w' || tolower(selection) == 'e' ){

			writeToFile(); // calling writeToFile function
			output.close(); // closing output file after writing
			if (tolower(selection) == 'e'){
				songbook.close(); // closing input file after all operations
				exit(); // calling exit function
				break; // breaking if and while
			}
		}
	}

	return 0;
}
