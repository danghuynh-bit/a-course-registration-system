#include "course_manager.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//Get new course information from user input
void getCourseInformation(CRses &courses) {
	cout << "\nCurrent course ID: " << courses.crs_id;
	cout << "\nEnter new course ID: ";
	cin.ignore();
	cin >> courses.crs_id;
	
	cout << "\nCurrent course name: " << courses.crs_name;
	cout << "\nEnter new course name: ";
	cin.ignore();
	cin.getline(courses.crs_name, sizeof(courses.crs_name));
	
	cout << "\nCurrent start registration date: " << courses.reg_start;
	cout << "\nEnter new start registration date: ";
	cin >> courses.reg_start;
	
	cout << "\nCurrent end registration date: " << courses.reg_end;
	cout << "\nEnter new end registration date: ";
	cin.ignore();
	cin >> courses.reg_end;
	
	cout << "\nCurrent number of credits: " << courses.credit;
	cout << "\nEnter new number of credits: ";
	cin >> courses.credit;
	
	cout << "\nCurrent maximum number of student: " << courses.max_std;
	cout << "\nEnter new maximum number of student: ";
	cin >> courses.max_std;
	
	cout << "\n\t1. Monday";
	cout << "\n\t2. Tuesday";
	cout << "\n\t3. Wednesday";
	cout << "\n\t4. Thursday";
	cout << "\n\t5. Friday";
	cout << "\n\t6. Saturday\n";
	
	cout << "\nCurrent date for session 1: " << courses.dSession1;
	cout << "\nEnter new date for session 1: ";
	cin >> courses.dSession1;
	
	cout << "\nCurrent date for session 2: " << courses.dSession2;
	cout << "\nEnter new date for session 2:";
	cin >> courses.dSession2;
	
	cout << "\n\t1. 7:30";
	cout << "\n\t2. 9:30";
	cout << "\n\t3. 13:30";
	cout << "\n\t4. 15:30\n";
	
	cout << "\nCurrent starting time for session 1: " << courses.tSesstion1;
	cout << "\nEnter new starting time for session 1: ";
	cin >> courses.tSesstion1;
	
	cout << "\nCurrent starting time for session 2: " << courses.tSesstion2;
	cout << "\nEnter new starting time for session 2: ";
	cin >> courses.tSesstion2;
	
	cout << "\nCurrent number of teacher in the course: " << courses.num_tch;
	
	//print teacher name list
	if (courses.num_tch == 1) {
		cout << "\t\n1. " << courses.tcher1 << endl;
	}
	else if (courses.num_tch == 2) {
		cout << "\t\n1. " << courses.tcher1 << endl;
		cout << "\t\n2. " << courses.tcher2 << endl;
	}
	else if (courses.num_tch == 3) {
		cout << "\t\n1. " << courses.tcher1 << endl;
		cout << "\t\n2. " << courses.tcher2 << endl;
		cout << "\t\n3. " << courses.tcher3 << endl;
	}
	else if (courses.num_tch == 4) {
		cout << "\t\n1. " << courses.tcher1 << endl;
		cout << "\t\n2. " << courses.tcher2 << endl;
		cout << "\t\n3. " << courses.tcher3 << endl;
		cout << "\t\n4. " << courses.tcher4 << endl;
	}
	
	cout << "Enter new number of teacher in the course: ";
	cin >> courses.num_tch;
	
	getTcherName(courses);
}

//Update the course information
void updateCourseInformation() {
	system("cls");
	
	sCourses *head = nullptr, *tale = nullptr;
	
	getCoursesLinkedList(head, tale);
	
	cout << "----- LIST OF COURSES -----\n";
	
	long cnt = 0;
	sCourses *currCRS = head;
	while (currCRS != nullptr) {
		cout << "\t" << ++cnt << ". " << currCRS->obt.crs_id << " - " << currCRS->obt.crs_name << endl;
		currCRS = currCRS->next;
	}
		
	long choice;
	cout << "\nEnter your choice: ";
	cin >> choice;
	
	if (choice > cnt)
		cout << "Please try again!";
	else {
		//get the courses information at the position 'choice'
		currCRS = head;
		for (int i = 2; i <= choice; i++)
			currCRS = currCRS->next;
			
		//get new course information from user input
		getCourseInformation(currCRS->obt);
		
		//write new course information to the file 'courses_manager.dat'
		currCRS = head;
		ofstream outFile("courses_manager.dat", ios::binary);
		
		while (currCRS != nullptr) {
			outFile.write(reinterpret_cast<char *>(&currCRS->obt), sizeof(currCRS->obt));
			currCRS = currCRS->next;
		}
		
		outFile.close();
	}
	
	deallocatingList_CRS(head, tale);
}

void addTaleNode_CRS(CRses obt, sCourses *&head, sCourses *&tale) {
	if (head == nullptr && tale == nullptr) { //check if the list is blank or not
		head = new sCourses;
		
		head->obt = obt;
		head->next = nullptr;
		head->prev = nullptr;
		
		tale = head;
	}
	else {
		sCourses *temp = new sCourses;
		
		temp->obt = obt;
		temp->next = nullptr;
		temp->prev = tale;
		
		tale->next = temp;
		tale = temp;
	}
}

void addHeadNode_CRS(CRses obt, sCourses *&head, sCourses *&tale) {
	if (head == nullptr && tale == nullptr) { //check if the list is blank or not
		head = new sCourses;
		
		head->obt = obt;
		head->next = nullptr;
		head->prev = nullptr;
		
		tale = head;
	}
	else {
		sCourses *temp = new sCourses;
		
		temp->obt = obt;
		temp->next = head;
		temp->prev = nullptr;

		head->prev = temp;
		head = temp;
	}
}

void deleteNode_CRS(long k, sCourses *&head, sCourses *&tale) {

	long position = 0;
	sCourses *sHead = head, *sTale = tale;
	
	while (position < k && sHead != nullptr) {
		position++;
		sHead = sHead->next;
	}
	
	if (sHead->prev == nullptr) { //check if it is the head node
		sHead->next->prev = nullptr;
		head = sHead->next;
		delete sHead;
	}
	else if (sHead->next == nullptr) { //check if it is the last node
		sHead->prev->next = nullptr;
		tale = sHead->prev;
		delete sHead;
	}
	else {
		sHead->prev->next = sHead->next;
		sHead->next->prev = sHead->prev;
		delete sHead;
	}
}

long getListLength_CRS(sCourses *head) {
	long cnt = 0;
	
	while (head != nullptr) {
		cnt++;
		head = head->next;
	}
	
	return cnt;
}

void insertAfterK_CRS(long k, CRses obt, sCourses *&head, sCourses *&tale) {
	long position = 0;
	sCourses *sHead = head, *sTale = tale;
	
	while (position < k) {
		position++;
		sHead = sHead->next;
	}
	
	sCourses *temp = new sCourses;
	temp->obt = obt;
	
	if (sHead->prev == nullptr) { //check if it is the head node
		sHead->prev = temp;
		temp->prev = nullptr;
		temp->next = sHead;
		head = temp;
	}
	else if (sHead->next == nullptr) { //check if it is the tale node
		tale->next = temp;
		temp->prev = tale;
		temp->next = nullptr;
		tale = temp;
	}
	else {
		temp->prev = sHead;
		temp->next = sHead->next;
		sHead->next->prev = temp;
		sHead->next = temp;	
	}
}

void deallocatingList_CRS(sCourses *& head, sCourses *&tale) {
	while (head != nullptr) {
		sCourses *temp = head;
		head = head->next;
		delete temp;
	}
	
	head = nullptr;
	tale = nullptr;
}

//print the courses to the screen
void printCourses() {
	system("cls");
	
	sCourses *head = nullptr, *tale = nullptr;
	
	if (!getCoursesLinkedList(head, tale))
		cout << "Please try again!";
	else {
		long cnt = 0;
		while (head != nullptr) {
			cout << "\t" << ++cnt << ". " << head->obt.crs_id << " - " << head->obt.crs_name << endl;
			head = head->next;
		}
	}
	
	deallocatingList_CRS(head, tale);
}

//get list of the courses, return true if the file 'couses_manager.dat' existed, otherwise, return false
bool getCoursesLinkedList(sCourses *&head, sCourses *&tale) {
	ifstream inpFile("courses_manager.dat", ios::binary);
	
	head = nullptr;
	tale = nullptr;
	
	if (!inpFile)
		return false;
	
	CRses courses;
	while (true) {
		inpFile.read(reinterpret_cast<char *>(&courses), sizeof(courses));
		
		if (inpFile.eof())
			break;
		
		addTaleNode_CRS(courses, head, tale);
	}
	
	return true;
}

//create a course
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
	
	cout << "\nEnter the date for session 1: ";
	cin >> courses.dSession1;
	cout << "Enter the date for session 2: ";
	cin >> courses.dSession2;
	
	cout << "\n\t1. 7:30";
	cout << "\n\t2. 9:30";
	cout << "\n\t3. 13:30";
	cout << "\n\t4. 15:30\n";
	
	cout << "\nEnter the starting time for session 1: ";
	cin >> courses.tSesstion1;
	
	cout << "Enter the starting time for session 2: ";
	cin >> courses.tSesstion2;
	
	cout << "Enter the number of teacher in the course: ";
	cin >> courses.num_tch;
	
	getTcherName(courses);
	
	if (isCsrIdExisted(courses)) 
		cout << "Please try again!";
	else {
		ofstream outFile("courses_manager.dat", ios::binary | ios::app);
		outFile.write(reinterpret_cast<char *>(&courses), sizeof(courses));
		outFile.close();
		
		char fileName[256];
		strcpy(fileName, courses.crs_id);
		strcat(fileName, "_course.dat");
		
		outFile.open(fileName, ios::binary);
		outFile.close();
	}
}

//Get the teacher name when creating the course
void getTcherName(CRses &courses) {
	if (courses.num_tch == 1) {
		cout << "Enter the 1st teacher's name: ";
		cin.ignore();
		cin.getline(courses.tcher1, sizeof(courses.tcher1));
	}
	else if (courses.num_tch == 2) {
		cout << "Enter the 1st teacher's name: ";
		cin.ignore();
		cin.getline(courses.tcher1, sizeof(courses.tcher1));
		
		cout << "Enter the 2nd teacher's name: ";
		cin.getline(courses.tcher2, sizeof(courses.tcher2));
	}
	else if (courses.num_tch == 3) {
		cout << "Enter the 1st teacher's name: ";
		cin.ignore();
		cin.getline(courses.tcher1, sizeof(courses.tcher1));
		
		cout << "Enter the 2nd teacher's name: ";
		cin.getline(courses.tcher2, sizeof(courses.tcher2));
		
		cout << "Enter the 3rd teacher's name: ";
		cin.getline(courses.tcher3, sizeof(courses.tcher3));
	}
	else if (courses.num_tch == 4) {
		cout << "Enter the 1st teacher's name: ";
		cin.ignore();
		cin.getline(courses.tcher1, sizeof(courses.tcher1));
		
		cout << "Enter the 2nd teacher's name: ";
		cin.getline(courses.tcher2, sizeof(courses.tcher2));
		
		cout << "Enter the 3rd teacher's name: ";
		cin.getline(courses.tcher3, sizeof(courses.tcher3));
		
		cout << "Enter the 4nd teacher's name: ";
		cin.getline(courses.tcher4, sizeof(courses.tcher4));
	}
}

//Return true if the course existed in 'course_manager.dat', otherwise, return false
bool isCsrIdExisted(CRses courses) {
	ifstream inpFile(("courses_manager.dat"), ios::binary);
	
	if (!inpFile)
		return false;
	
	CRses crs_temp;
	while (true) {
		inpFile.read(reinterpret_cast<char *>(&crs_temp), sizeof(crs_temp));
		
		if (inpFile.eof())
			break;
		
		if (!strcmp(crs_temp.crs_id, courses.crs_id)) {
			inpFile.close();
			return true;
		}
	}
	
	inpFile.close();
	return false;
}