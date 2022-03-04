#include "course_manager.h"
#include <iostream>

using namespace std;

void createCourses() {
	system("cls");
	
	CRses courses;
	
	cout << "Enter course ID: ";
	cin.ignore();
	cin >> courses.crs_id;
	
	cout << "Enter the course name: ";
	cin.ignore();
	cin.getline(courses.crs_name, sizeof(courses.crs_name));
	
	cout << "Enter start registration date: ";
	cin.ignore();
	cin >> courses.reg_start;
	
	cout << "Enter end registration date: ";
	cin.ignore();
	cin >> courses.reg_end;
	
	cout << "Enter number of credits: ";
	cin >> courses.credit;
	
	cout << "Enter the maximum number of student (default 50 students): ";
	cin >> courses.max_std;
	
	cout << "\n\t1. Monday";
	cout << "\n\t2. Tuesday";
	cout << "\n\t3. Wednesday";
	cout << "\n\t4. Thursday";
	cout << "\n\t5. Friday";
	cout << "\n\t6. Saturday\n";
	
	cout << "Enter the date for session 1: ";
	cin >> courses.dSession1;
	cout << "Enter the date for session 2: ";
	cin >> courses.dSession2;
	
	cout << "\n\t1. 7:30";
	cout << "\n\t2. 9:30";
	cout << "\n\t3. 13:30";
	cout << "\n\t4. 15:30\n";
	
	cout << "Enter the starting time for session 1: ";
	cin >> courses.tSesstion1;
	
	cout << "Enter the starting time for session 2: ";
	cin >> courses.tSesstion2;
	
	cout << "Enter the number of teacher in the course: ";
	cin >> courses.num_tch;
	
	getTcherName(courses);
	
}

void getTcherName(CRses &courses) {
	if (courses.num_tch == 1) {
		cout << "Enter the 1st teacher's name: ";
		cin.ignore();
		cin >> courses.tcher1;
	}
	else if (courses.num_tch == 2) {
		cout << "Enter the 1st teacher's name: ";
		cin.ignore();
		cin >> courses.tcher1;
		
		cout << "Enter the 2nd teacher's name: ";
		cin.ignore();
		cin >> courses.tcher2;
	}
	else if (courses.num_tch == 3) {
		cout << "Enter the 1st teacher's name: ";
		cin.ignore();
		cin >> courses.tcher1;
		
		cout << "Enter the 2nd teacher's name: ";
		cin.ignore();
		cin >> courses.tcher2;
		
		cout << "Enter the 3rd teacher's name: ";
		cin.ignore();
		cin >> courses.tcher3;
	}
	else if (courses.num_tch == 4) {
		cout << "Enter the 1st teacher's name: ";
		cin.ignore();
		cin >> courses.tcher1;
		
		cout << "Enter the 2nd teacher's name: ";
		cin.ignore();
		cin >> courses.tcher2;
		
		cout << "Enter the 3rd teacher's name: ";
		cin.ignore();
		cin >> courses.tcher3;
		
		cout << "Enter the 4nd teacher's name: ";
		cin.ignore();
		cin >> courses.tcher4;
	}
}