#ifndef _ACCOUNT_MANAGER_
#define _ACCOUNT_MANAGER_

typedef struct Users {
	/*
		role: True if the person is academic staff, otherwise false
		gender: True if the person is female, otherwise false
		generation: K21, K20, K19,...
		id: Student ID
		program: APCS, CLC, VP, CQ,...
		- 'Generation', 'id', 'program' is only availabe when a person is student
	*/
	bool role, gender;
	long generation, id; 
	char name[256], username[256], password[256], program[256]; 
} Users;

//Print the menu for users to login, sign up,...
void accountManagerMenu(Users &usr);

//Let user login to the system
bool loginUser(Users &usr);

//Check if the usernamae is existed in the file 'account_manager.dat'
bool isUsernameExisted(Users usr);

//Let user creates their account
bool registerUser(Users &usr);

#endif