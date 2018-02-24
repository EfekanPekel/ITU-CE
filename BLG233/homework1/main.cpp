/* @Author
* Student Name: Mustafa Efekan PEKEL
* Student ID : 150140050
* Date: 18.10.2016
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

int patientNumber = 0;

struct patient_record {
	char name[20], doctorName[20], diagnosis[25];
	int patientNumber, polyclinicNumber;
	char branchName[20];
};

struct branch {  // branch struct to keep polyclinic numbers, patients per polyclinic and patients
    char name[20];
    int polyclinic[2]; // polyclinic numbers of each branch
    int patient_polyclinic[2]; // patient number of each polyclinic
    patient_record patients[2][11]; //first index for polyclinic and second index for patients
};

branch list_ar[100]; // branch struct array to keep all branches
int branchNumber; // number of branches


void searchPatient(patient_record *arr) {
	char text[20]; // char array for searching branch
	bool test = true; // to check if there is no found
	//cin.ignore(1000,'\n');
	cout << "Please enter branch name: ";
	getchar();
	cin.getline(text, 20);

	for (int i = 0; i<patientNumber; i++){ //searching
		if (!strncmp((arr + i)->branchName, text, strlen(text))) {
			cout << arr[i].name << ' ' << arr[i].doctorName << ' ' << arr[i].diagnosis << ' ' << arr[i].patientNumber << ' ' << arr[i].polyclinicNumber << ' ' << arr[i].branchName << endl;
			test = false;
		}
	}
	if (test)
		cout << "Branch name not found." << endl;

	cout << endl;
}

void searchPolyclinic(patient_record *arr) {
	int number;
	bool test = true;

	cout << "Please enter polyclinic number: ";
	getchar();
	cin >> number;
	for (int i = 0; i<patientNumber; i++){
		if (number == (arr + i)->polyclinicNumber) {
			cout << arr[i].name << ' ' << arr[i].doctorName << ' ' << arr[i].diagnosis << ' ' << arr[i].patientNumber << ' ' << arr[i].polyclinicNumber << ' ' << arr[i].branchName << endl;
			test = false;
		}
	}
	if (test)
		cout << "Polyclinic number not found" << endl;

	cout << endl;
}

void add(patient_record one) { // function for reading from file, this function used for also insert
    for(int i=0;i<branchNumber;i++) { // function is adding, sorting and checking conditions
        if(strcmp(list_ar[i].name,one.branchName) == 0) {
            for(int j=0;j<branchNumber;j++){
                if(j!=i && (list_ar[j].polyclinic[0] == one.polyclinicNumber || list_ar[j].polyclinic[1] == one.polyclinicNumber)){
                    cout << "This polyclinic reserved for another branch!" << endl;
                    return;
                }
            }
            if(one.polyclinicNumber == list_ar[i].polyclinic[0]){
                list_ar[i].patients[0][list_ar[i].patient_polyclinic[0]] = one;
                ++list_ar[i].patient_polyclinic[0];

            }
            else if(one.polyclinicNumber == list_ar[i].polyclinic[1]){
                list_ar[i].patients[1][list_ar[i].patient_polyclinic[1]] = one;
                ++list_ar[i].patient_polyclinic[1];
            }
            else {
                if(list_ar[i].polyclinic[0] == -1) {
                    list_ar[i].patients[0][list_ar[i].patient_polyclinic[0]] = one;
                    list_ar[i].polyclinic[0] = one.polyclinicNumber;
                    ++list_ar[i].patient_polyclinic[0];
                }
                else if(list_ar[i].polyclinic[1] == -1) {
                    list_ar[i].patients[1][list_ar[i].patient_polyclinic[1]] = one;
                    list_ar[i].polyclinic[1] = one.polyclinicNumber;
                    ++list_ar[i].patient_polyclinic[1];
                    if(list_ar[i].polyclinic[0] > list_ar[i].polyclinic[1]){
                        swap(list_ar[i].polyclinic[0], list_ar[i].polyclinic[1]);
                        swap(list_ar[i].patient_polyclinic[0], list_ar[i].patient_polyclinic[1]);
                        swap(list_ar[i].patients[0], list_ar[i].patients[1]);
                    }
                }
                else {
                    cout << "You cannot open new polyclinc for this branch.!" << endl;
                    return;
                }
            }
            return;
        }

    }
     for(int j=0;j<branchNumber;j++){
            if(list_ar[j].polyclinic[0] == one.polyclinicNumber || list_ar[j].polyclinic[1] == one.polyclinicNumber){
                cout << "This polyclinic reserved for another branch!" << endl;
                return;
            }
    }
    strcpy(list_ar[branchNumber].name, one.branchName);
    list_ar[branchNumber].polyclinic[0] = one.polyclinicNumber;
    list_ar[branchNumber].patient_polyclinic[0] = 1;
    list_ar[branchNumber].polyclinic[1] = -1;
    list_ar[branchNumber].patient_polyclinic[1] = 0;
    list_ar[branchNumber].patients[0][0] = one;

    for(int i=branchNumber; i>0; i--) {
        if(strcmp(list_ar[i].name, list_ar[i-1].name)<0) {
            swap(list_ar[i], list_ar[i-1]);
        }
    }
    branchNumber++;
}

void insertPatient(patient_record *arr) {
	int a = patientNumber;
	patient_record temp; // to keep data to insert

	cout << "Please enter patient name: ";
	cin.ignore(1000, '\n');
	cin.getline(temp.name, 20);
	cout << "Please enter doctor name: ";
	cin.getline(temp.doctorName, 20);
	cout << "Please enter diagnosis: ";
	cin.getline(temp.diagnosis, 25);
	cout << "Please enter patient number: ";
	cin >> temp.patientNumber;
    int lengthCount = 0;
    int x = temp.patientNumber;
    for(; x != 0; x /= 10, lengthCount++);
    if(lengthCount != 4) {
        while(lengthCount != 4){ // checking if patient number is 4 digits.
            cout << "Please enter valid patient number: ";
            cin >> temp.patientNumber;
            int x = temp.patientNumber;
            lengthCount = 0;
            for(; x != 0; x /= 10, lengthCount++);
        }
    }
	cout << "Please enter polyclinic number: ";
	cin >> temp.polyclinicNumber;
	cout << "Please enter branch name: ";
	getchar();
	cin.getline(temp.branchName, 20);
	patientNumber++;
	add(temp);
	cout << endl;
}

void removePatient(patient_record *arr) {
	int number;
	bool test = true; //to check if there is no found

	cout << "Please enter patient number: ";
	getchar();
	cin >> number;
	int i = 0,record;
	for(i=0; i<branchNumber;i++){ // searching
        for(int j=0;j<list_ar[i].patient_polyclinic[0];j++){
            if(number == list_ar[i].patients[0][j].patientNumber) {
                for(int k=j;k<list_ar[i].patient_polyclinic[0]-1;k++)   {
                    swap(list_ar[i].patients[0][k], list_ar[i].patients[0][k+1]);
                }
                test = false;
                list_ar[i].patient_polyclinic[0]--;
            }
        }
        for(int j=0;j<list_ar[i].patient_polyclinic[1];j++){
            if(number == list_ar[i].patients[1][j].patientNumber) {
                for(int k=j;k<list_ar[i].patient_polyclinic[1]-1;k++)   {
                    swap(list_ar[i].patients[1][k], list_ar[i].patients[1][k+1]);
                }
                test = false;
                list_ar[i].patient_polyclinic[1]--;
            }
        }
	}
	if (test)
		cout << "Patient number not found" << endl;

	for (i = record; i<patientNumber; i++){
		swap(arr[i], arr[i + 1]);
	}

	patientNumber--;
	cout << "The record has been removed" <<  endl << endl;

}

void printmenu(bool warning) {
	if (warning) {
		cout << "Please enter a valid character for selection" << endl;
	}
	cout << "Please select the operation to perform and enter the operation code" << endl;
	cout << "(P) Print all of the patient records," << endl;
	cout << "(B) Search the data by the branch name," << endl;
	cout << "(C) Search the data by the polyclinic number," << endl;
	cout << "(I) Insert a new patient record," << endl;
	cout << "(R) Remove the patient record," << endl;
	cout << "(E) Exit the program," << endl;
	cout << "Your selection is: ";
}

void carrier(patient_record *arr) {
    patientNumber = 0;
    for(int i=0; i<branchNumber; i++) {
        for(int j=0; j<list_ar[i].patient_polyclinic[0]; j++) {
            arr[patientNumber] = list_ar[i].patients[0][j];
            patientNumber++;
        }
        for(int j=0; j<10-list_ar[i].patient_polyclinic[0];j++){
            strcpy(arr[patientNumber].branchName, "");
            strcpy(arr[patientNumber].diagnosis, "");
            strcpy(arr[patientNumber].doctorName, "");
            strcpy(arr[patientNumber].name, "");
            arr[patientNumber].patientNumber = 0;
            arr[patientNumber].polyclinicNumber = 0;
            patientNumber++;
        }
        if(list_ar[i].polyclinic[1] != -1){
            for(int j=0; j<list_ar[i].patient_polyclinic[1]; j++) {
                arr[patientNumber] = list_ar[i].patients[1][j];
                patientNumber++;
            }
            for(int j=0; j<10-list_ar[i].patient_polyclinic[1];j++){
                strcpy(arr[patientNumber].branchName, "");
                strcpy(arr[patientNumber].diagnosis, "");
                strcpy(arr[patientNumber].doctorName, "");
                strcpy(arr[patientNumber].name, "");
                arr[patientNumber].patientNumber = 0;
                arr[patientNumber].polyclinicNumber = 0;
                patientNumber++;
            }
        }
    }
}

void exit(patient_record *arr) {
    FILE *db;
    db = fopen("database.txt", "w");
    for(int i=0;i<patientNumber;i++){
        if(strcmp(arr[i].branchName, "") != 0){
            fprintf(db,"%s\t%s\t%s\t%d\t%d\t%s\n", arr[i].name, arr[i].doctorName, arr[i].diagnosis, arr[i].patientNumber, arr[i].polyclinicNumber, arr[i].branchName);
        }
    }
    fclose(db);
}

int main() {
	ifstream database; //opening file
	database.open("database.txt", ios::out | ios::in);
	FILE *db;
	patient_record arr[1000];
	patient_record temp;
	int i = 0;
	while (database.getline(temp.name, 20, '\t')){
		database.getline(temp.doctorName, 20, '\t');
		database.getline(temp.diagnosis, 25, '\t');
		database >> temp.patientNumber >> temp.polyclinicNumber;
		database.ignore(1, 't');
		database.getline(temp.branchName, 20);
		add(temp);
		i++;
		patientNumber++;
	}
	carrier(arr);
	char selection;
	bool warning = 0;
	while (1) {
		printmenu(warning);
		cin >> selection;
		cout << endl;
		if (selection == 'P' || selection == 'p'){
			int i = 0;
			while (i<patientNumber) {
                if(strcmp(arr[i].branchName, "") != 0) {
                    cout << arr[i].name << ' ' << arr[i].doctorName << ' ' << arr[i].diagnosis << ' ' << arr[i].patientNumber << ' ' << arr[i].polyclinicNumber << ' ' << arr[i].branchName << endl;
                }
                i++;
			}
			cout << endl;
		}
		else if (selection == 'B' || selection == 'b'){
			searchPatient(arr);
		}
		else if (selection == 'C' || selection == 'c'){
			searchPolyclinic(arr);
		}
		else if (selection == 'I' || selection == 'i'){
			insertPatient(arr);
			carrier(arr);
		}
		else if (selection == 'R' || selection == 'r'){
			removePatient(arr);
			carrier(arr);
		}
		else if (selection == 'E' || selection == 'e'){
            database.close();
            exit(arr);
            break;
		}
		else{
			cout << "Please enter a valid selection" << endl;
			continue;
		}
	}
	return 0;
}
