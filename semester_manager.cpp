#include "semester_manager.h"
#include <iostream>
#include <fstream>

using namespace std;

//create a semester;
void createSemester() {
	system("cls");
	
	SMSTer semester;
	
	cout << "Enter start day: ";
	cin.ignore();
	cin >> semester.start;
	
	cout << "Enter end day: ";
	cin.ignore();
	cin >> semester.end;
	
	cout << "Enter semester order (1: Fall; 2: Spring; 3: Autumn): ";
	cin >> semester.order;
	
	if (isSchoolYearEmpty())
		cout  << "Please create a school year first!";
	else {
		cout << "Avaiable school years: \n";
		
		long cnt = 0;
		ScYears year;
		ifstream inpFile("school_years.dat", ios::binary);
		
		while (true) {
			inpFile.read(reinterpret_cast<char *>(&year), sizeof(year));
			
			if (inpFile.eof())
				break;
			
			cout << "\t" << ++cnt << ". " << year.start << " - " << year.end << endl;
		}
		
		inpFile.close();
		
		long choice;
		cout << "Enter your choice: ";
		cin >> choice;
		
		cnt = 0;
		inpFile.open("school_years.dat", ios::binary);
		while (true) {
			inpFile.read(reinterpret_cast<char *>(&year), sizeof(year));
			
			if (++cnt == choice)
				break;
		}
		
		inpFile.close();
		
		if (choice > cnt) {
			cout << "Please try again!";
			exit;
		}
		
		semester.school_year.start = year.start;
		semester.school_year.end = year.end;
		
		if (isSemesterExisted(semester))
			cout << "Please try again!";
		else {
			string fileName = to_string(year.start) + "_" + to_string(year.end) + "_school_year.dat";
			ofstream outFile(fileName, ios::binary | ios::app);
			
			outFile.write(reinterpret_cast<char *>(&semester), sizeof(semester));
			
			outFile.close();
			
			cout << "Created a semester successfully!";
		}
	}
}

//Return true if a semester is existed, otherwise, return false
bool isSemesterExisted(SMSTer semester) {
	string fileName = to_string(semester.school_year.start) + "_" + to_string(semester.school_year.end) + "_school_year.dat";
	
	ifstream inpFile(fileName, ios::binary);
	
	if (!inpFile)
		return false;
		
	SMSTer smr_temp;
	while (true) {
		inpFile.read(reinterpret_cast<char *>(&smr_temp), sizeof(smr_temp));
		
		if (inpFile.eof())
			break;
		
		if (semester.order == smr_temp.order)
			return true;
	}
	
	return false;
}

//return true if any school years does not exists, otherwise, return false
bool isSchoolYearEmpty() {
	ifstream inpFile("school_years.dat", ios::binary);
	
	if (!inpFile)
		return true;
		
	int cnt = 0;
	ScYears year;
	while (true) {
		inpFile.read(reinterpret_cast<char *>(&year), sizeof(year));
		
		if (inpFile.eof())
			break;
			
		string fileName = to_string(year.start) + "_" + to_string(year.end) + "_school_year.dat";
		
		ifstream tempFile(fileName, ios::binary);
		
		if (tempFile)
			cnt++;
		
		tempFile.close();
	}
	
	if (!cnt)
		return true;
		
	return false;
}