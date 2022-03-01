#include <iostream>
#include <fstream>
#include <cstring>
#include "account_manager.h"

using namespace std;

//View account profile
void viewAccProfile(Users usr) {
	system("cls");
	
	cout << "Username: " << usr.username << endl;
	cout << "Name: " << usr.name << endl;
	
	cout << "Role: ";
	if (usr.role)
		cout << "Teacher\n";
	else
		cout << "Student\n";
		
	cout << "Gender: ";
	if (usr.gender)
		cout << "Female\n";
	else
		cout << "Male\n";
		
	if (!usr.role) {
		cout << "Generation: K" << usr.generation << endl;
		cout << "ID: " << usr.id << endl;
		cout << "Program: " << usr.program << endl;
	} 
}

//Change account password
void changeAccPassword(Users &usr) {
	cout << "Chanh Tin";
	char pass[256], rpass1[256], rpass2[256];
	
	cout << "Enter your current password: ";
	cin >> pass;
	
	if (!strcmp(pass, usr.password)) {
		cout << "Enter new password: ";
		cin >> rpass1;
		
		cout << "Re-enter new password: ";
		cin >> rpass2;
		
		if (!strcmp(rpass1, rpass2)) {
			Users usr_temp;
			ofstream outFile("temporary.dat", ios::binary);
			ifstream inpFile("account_manager.dat", ios::binary);
			
			while (!inpFile.eof()) {
				inpFile.read(reinterpret_cast<char *>(&usr_temp), sizeof(usr_temp));
				
				if (!strcmp(usr_temp.username, usr.username) && !strcmp(usr_temp.password, pass)) 
					strcpy(usr_temp.password, rpass1);
					
				outFile.write(reinterpret_cast<char *>(&usr_temp), sizeof(usr_temp));
			}			
			
			inpFile.close();
			outFile.close();
			
			inpFile.open("temporary.dat", ios::binary);
			outFile.open("account_manager.dat", ios::binary);
			
			while (!inpFile.eof()) {
				inpFile.read(reinterpret_cast<char *>(&usr_temp), sizeof(usr_temp));
				outFile.write(reinterpret_cast<char *>(&usr_temp), sizeof(usr_temp));
			}
			
			inpFile.close();
			outFile.close();
		}
		else 
			cout << "Try again!";
	}
	else
		cout << "Try again!";
} 

void logOutUser(Users &usr) {
	strcpy(usr.username, "");
	strcpy(usr.password, "");
}

//Modify account
void accountDetail(Users &usr) {
	cout << "\t1. View profile\n";
	cout << "\t2. Change password\n";
	cout << "\t3. Log out\n";
	
	int choice;
	cout << "Your choice: ";
	cin >> choice;
	
	if (choice == 1)
		viewAccProfile(usr);
	else if (choice == 2)
		changeAccPassword(usr);
	else if (choice == 3) 
		logOutUser(usr);
}

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
		
		system("cls");
		cout << "Welcome back, " << usr.name << "!\n";
		accountDetail(usr);
		
	}
	else if (choice == 2) {
		while (!registerUser(usr)) {
			cout << "Invalid account, please try again!\n\n";
		}
		
		system("cls");
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
	
	cout << "Enter your role (0: student; 1: teacher): ";
	cin >> usr.role;
	
	cout << "Enter your gender (0: male; 1: female): ";
	cin >> usr.gender;
	
	if (!usr.role) {
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
		
	ofstream outFile("account_manager.dat", ios::binary | ios::app);
	outFile.write(reinterpret_cast<char *>(&usr), sizeof(usr));
	
	outFile.close();
	return true;
}