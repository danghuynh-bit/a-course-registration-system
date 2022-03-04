#ifndef _SEMESTER_MANAGER_H_
#define _SEMESTER_MANAGER_H_
#include "school_year.h"

typedef struct semester {
	/*
	order: 1 = semester 1, 2 = semester 2, 3 = semester 3
	start, end: start and end day of the semester
	school_years: To choose which school years that this current semester belongs to
	*/
	
	long order;
	char start[256], end[256];
	ScYears school_year;
}SMSTer;

//create a semester;
void createSemester();

//return true if any school years does not exists, otherwise, return false
bool isSchoolYearEmpty();

//Return true if a semester is existed, otherwise, return false
bool isSemesterExisted(SMSTer semester);

#endif