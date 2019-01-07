#pragma once

#include <iostream>
#include <vector>
#include "../FileAccess/FileAccess.hpp"

using namespace std;
class User {

private:
	User();
	string username; 
	string password;
	string SID;			// security ID (one per account/group)
				
				//User's groups
	static vector<User*> standardUserGroup;
	static vector<User*> adminGroup;

	void createAdmin();

public:
				//setters
	void setUsername(string username);
	void setPassword(string password);
	void setSID(string SID);
				//getters
	void getUsername();
	void getPassword();
	void getSID();
				//other functions
	void createUser();
	void deleteUser(User* user);
	void changePassword();
	void generateSID();

	static void addUserToUserGroup();
	static void addUserToAdminGroup();
};