#ifndef _SCHOOL_YEAR_
#define _SCHOOL_YEAR_
#include "account_manager.h"

typedef struct schoolYears {
	long start, end;
} ScYears;

//Return true if Student ID existed in the class file, else return false;
bool isStdIDExisted(Users stdent);

//add 1st year student
void addFirstYearStudent();

//add 1st year student by file CSV
void addStudentCSV();

//Return true if classroom is existed, otherwise, return false
bool isClassExisted(char *name);

//add classroom
void addClassroom();

//School year menu
void schoolYearMenu();

//Create school years
void createSchoolYear();

//Return true if the school year file is exist, otherwise, return false
bool isSchoolYearExisted(ScYears);

#endif