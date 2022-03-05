#include "school_year.h"
#include "semester_manager.h"
#include "course_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//Return true if Student ID existed in the class file, else return false;
bool isStdIDExisted(Users stdent) {
	char temp[256];
	
	strcpy(temp, stdent.classoom);
	strcat(temp, ".dat");
	
	ifstream inpFile(temp, ios::binary);
	
	if (!inpFile)
		return false;
		
	Users usr_temp;
		
	while (true) {
		inpFile.read(reinterpret_cast<char *>(&usr_temp), sizeof(usr_temp));
		
		if (inpFile.eof())
			break;
		
		if (stdent.id == usr_temp.id) {
			inpFile.close();
			return true;
		}
	}
	
	inpFile.close();
	return false;
}

//add 1st year student
void addFirstYearStudent() {
	Users stdent;
	
	cout << "Enter your ID: ";
	cin.ignore();
	cin >> stdent.id;
	
	cout << "Enter your first name: ";
	cin.ignore();
	cin >> stdent.fName;
	
	cout << "Enter your last name: ";
	cin.ignore();
	cin >> stdent.lName;
	
	cout << "Enter your class: ";
	cin.ignore();
	cin >> stdent.classoom;
	
	cout << "Enter your gender (0: male; 1: female): ";
	cin.ignore();
	cin >> stdent.gender;
	
	cout << "Enter your date of birthday: ";
	cin.ignore();
	cin >> stdent.birth;
	
	cout << "Enter your program (APCS, CLC, VP, CQ): ";
	cin.ignore();
	cin >> stdent.program;
	
	cout << "Enter your social ID: ";
	cin >> stdent.social_id;
	
	cout << "Enter your generation: ";
	cin >> stdent.generation;
	
	strcpy(stdent.username, "");
	strcpy(stdent.password, "");
	
	stdent.role = false;
	
	if (isStdIDExisted(stdent))
		cout << "Please try again!";
	else {
		char temp[256];
	
		strcpy(temp, stdent.classoom);
		strcat(temp, "_class.dat");
		
		ofstream outFile(temp, ios::binary | ios::app);
		
		outFile.write(reinterpret_cast<char *>(&stdent), sizeof(stdent));
		
		outFile.close();
	}
}

void addStudentCSV() {
	system("cls");
	
	string path;
	
//	cout << "Note: Double the splash!\n";
	cout << "Enter the CSV file path: ";
	cin >> path;
	
	ifstream inpFile(path);
	
	if (!inpFile) {
		cout << "ERROR: File not found!";
		exit;
	}
	
	Users usr;
	string line, word;
	
	//step over the first row
	getline(inpFile, line);
	
	while (getline(inpFile, line)) {
		stringstream str(line);
		
		getline(str, word, ';'); //step over the 'no' col
		
		//student id
		getline(str, word, ';');
		usr.id = stoi(word);
		
		//student first name
		getline(str, word, ';');
		strcpy(usr.fName, word.c_str());
		
		//student last name
		getline(str, word, ';');
		strcpy(usr.lName, word.c_str());
		
		//student class
		getline(str, word, ';');
		strcpy(usr.classoom, word.c_str());
		
		//student gender
		getline(str, word, ';');
		usr.gender = stoi(word);
		
		//student birthday
		getline(str, word, ';');
		strcpy(usr.birth, word.c_str());
		
		//student program
		getline(str, word, ';');
		strcpy(usr.program, word.c_str());
		
		//student social id
		getline(str, word, ';');
		usr.social_id = stoi(word);
		
		//student generation
		getline(str, word, ';');
		usr.generation = stoi(word);
		
		//student username
		getline(str, word, ';');
		strcpy(usr.username, word.c_str());
		
		//student password
		getline(str, word, ';');
		strcpy(usr.password, word.c_str());
		
		//add student to the file
		if (!isStdIDExisted(usr)) {
			char temp[256];
		
			strcpy(temp, usr.classoom);
			strcat(temp, "_class.dat");
			
			ofstream outFile(temp, ios::binary | ios::app);
			
			outFile.write(reinterpret_cast<char *>(&usr), sizeof(usr));
			
			outFile.close();
		}
	}
}

//Return true if classroom is existed, otherwise, return false
bool isClassExisted(string name) {
	ifstream inpFile(name, ios::binary);
	
	if (inpFile) {
		inpFile.close();
		return true;
	}
	else {
		inpFile.close();
		return false;
	}
}

//add classroom
void addClassroom() {
	string class_name;
	
	cout << "Enter class name: ";
	cin.ignore();
	cin >> class_name;
	
	if (isClassExisted(class_name + "_class.dat")) {
		cout << "Please try again!";
	}
	else {
		ofstream outFile(class_name + "_class.dat", ios::binary);
		outFile.close();
	}
	
}

//School year menu
void schoolYearMenu() {
	system("cls");
	
	cout << "\t1. Create school year.\n";
	cout << "\t2. Create class.\n";
	cout << "\t3. Add 1st year student.\n";
	cout << "\t4. Add 1st year student by CSV file.\n";
	cout << "\t5. Create a semester\n";
	cout << "\t6. Create a course\n";
	cout << "\t7. View created courses\n";
	
	int choice;
	cout << "Your choice: ";
	cin >> choice;
	
	if (choice == 1) 
		createSchoolYear();
	else if (choice == 2) 
		addClassroom();
	else if (choice == 3) 
		addFirstYearStudent();
	else if (choice == 4)
		addStudentCSV();
	else if (choice == 5)
		createSemester();
	else if (choice == 6)
		createCourses();
	else if (choice == 7)
		printCourses();
}

//Create school years
void createSchoolYear() {
	ScYears year;
	
	cout << "Year start: ";
	cin >> year.start;
	
	cout << "Year end: ";
	cin >> year.end;
	
	if (isSchoolYearExisted(year)) 
		cout << "Please try again!";
	else {
		ofstream outFile("school_years.dat", ios::binary | ios::app);
		outFile.write(reinterpret_cast<char *>(&year), sizeof(year));
		outFile.close();
		
		string fileName = to_string(year.start) + "_" + to_string(year.end) + "_school_year.dat";
		outFile.open(fileName, ios::binary);
		outFile.close();
	}
}

//Return true if the school year is exist, otherwise, return false
bool isSchoolYearExisted(ScYears year) {
	ifstream inpFile("school_years.dat", ios::binary);
	
	ScYears t_year;
	
	if (!inpFile)
		return false;
	
	while(true) {
		inpFile.read(reinterpret_cast<char *>(&t_year), sizeof(t_year));
		
		if (inpFile.eof())
			break;
		
		if (t_year.start == year.start && t_year.end == year.end) {
			inpFile.close();
			return true;
		}
	}
	
	inpFile.close();
	return false;
}