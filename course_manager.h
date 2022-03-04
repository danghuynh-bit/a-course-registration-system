#ifndef _COURSE_MANAGER_H_
#define _COURSE_MANAGER_H_

typedef struct Courses {
	/*
		reg_start[256]: The start date of the course registration
		reg_end[256]: The end date of the course registration
		crs_id[256]: The course ID (ex: CSC10002)
		crs_name[256]: The course name
		tcher1[256], tcher2[256], tcher3[256], tcher4[256]: The teachers name
		num_tch: Number of the teachers in the course
		dSesstion1, dSesstion2: The date that the session will take place (Monday, Tuesday,... Saturday) of the session 1 and the session 2
		tSesstion1, tSesstion2: The time that the session will take place (7:30, 9:30, 13:30, 15:30) of the session 1 and the session 2
		max_std: maxium number of students in the course
	*/
	
	char reg_start[256], reg_end[256], crs_id[256], crs_name[256], tcher1[256], tcher2[256], tcher3[256], tcher4[256];
	long num_tch, credit, dSession1, dSession2, tSesstion1, tSesstion2, max_std = 50;
}CRses;

//create a course
void createCourses();

//Get the teacher name when creating the course
void getTcherName(CRses &courses);

#endif