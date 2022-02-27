#include <iostream>
#include <fstream>
#include <cstring>
#include "account_manager.h"

using namespace std;

//Print the menu for users to login, sign up,...
void accountManagerMenu(Users &usr) {
	
	cout << "--- A course registration system ---\n";
	cout << "\t1. Login\n";
	cout << "\t2. Sign up\n";
	
	int choice;
	cout << "\nEnter your choice: ";
	cin >> choice;
	
	if (choice == 1) {
		while (!loginUser(usr)) {
			cout << "Invalid account, please try again!\n\n";
		}
		
		cout << "Welcome back, " << usr.name;
		
	}
	else if (choice == 2) {
		while (!registerUser(usr)) {
			cout << "Invalid account, please try again!\n\n";
		}
		
		cout << "Signed up successfully!";
	}
}

//Let user login to the system
bool loginUser(Users &usr) {
	cout << "Enter your username: ";
	cin >> usr.username;
	
	cout << "Enter your password: ";
	cin.ignore();
	cin >> usr.password;
	
	Users usr_temp;
	ifstream inpFile("account_manager.dat", ios::binary);
	
	while(!inpFile.eof()) {
		inpFile.read(reinterpret_cast<char *>(&usr_temp), sizeof(usr_temp));
		
		if (!strcmp(usr_temp.username, usr.username) && !strcmp(usr_temp.password, usr.password)) {
			inpFile.close();
			usr = usr_temp;
			return true; //If login successfully, return true, otherwise, return false
		}
	}
	
	inpFile.close();
	return false;
}

//Check if the usernamae is existed in the file 'account_manager.dat'
bool isUsernameExisted(Users usr) {
	Users usr_temp;
	ifstream inpFile("account_manager.dat", ios::binary);
	
	if (!inpFile)
		return false;
	
	while (!inpFile.eof()) {
		inpFile.read(reinterpret_cast<char *>(&usr_temp), sizeof(usr_temp));
		
		if (!strcmp(usr_temp.username, usr.username)) {
			inpFile.close();
			return true; //if it is existed, return true, otherwise, return false;
		}
	}
	
	inpFile.close();
	return false;
}

bool registerUser(Users &usr) {
	cout << "Enter your username: ";
	cin.ignore();
	cin >> usr.username;
	
	cout << "Enter your password: ";
	cin.ignore();
	cin >> usr.password;
	
	cout << "Enter your name: ";
	cin.ignore();
	cin.getline(usr.name, sizeof(usr.name));
	
	cout << "Enter your role (0: teacher; 1: student): ";
	cin >> usr.role;
	
	cout << "Enter your gender (0: male; 1: female): ";
	cin >> usr.gender;
	
	if (usr.role) {
		cout << "Enter your student ID: ";
		cin >> usr.id;
		
		cout << "Enter your generation (18, 19, 20, 21,...): ";
		cin >> usr.generation;
		
		cout << "Enter your program (APCS, CLC, VP, CQ,...): ";
		cin.ignore();
		cin >> usr.program;
	}
	
	if (isUsernameExisted(usr)) 
		return false; //if sign up failed, return false, otherwise, return true
		
	ofstream outFile("account_manager.dat", ios::binary);
	outFile.write(reinterpret_cast<char *>(&usr), sizeof(usr));
	
	outFile.close();
	return true;
}