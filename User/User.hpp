#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "FileAccess.hpp"

using namespace std;
class User {

private:
	string username; 
	string password;
	string SID;			// security ID (one per account/group)
	static string currentLoggedUser;
				
	

	void createAdmin();
	//static void deleteFromList(); //Funkcja pomocnicza do usuwania z list statycznych

public:
	User();
	User(string username, string password);
	~User();
	
				//Users' groups
	static vector<User*> standardUserGroup;
	static vector<User*> adminGroup;
	static vector<User*> userList;
				//setters
	void setUsername(string username);
	void setPassword(string password);
	void setSID(string SID);
	static void setCurrentLoggedUser(string SID);
				//getters
	string getUsername();
	string getPassword();
	string getSID();
	static string getCurrentLoggedUser();
				//other functions
	void createUser();
	void changeUser(); // "logout"
	void deleteUser(User* user);
	void changePassword();
	void generateSID();
	static bool currentLoggedGotAdminPermissions(); // Sprawdza czy obecnie zalogowana osoba jest adminem
				//Operacje na listach
	static void viewUserList();
	static void viewStandardUserGroup();
	static void viewAdminUserGroup();

	static void addToUserList(User* user); // Lista wszystkich istniejacych uzytkownikow
	static void addUserToStandardUserGroup(User* user);
	static void addUserToAdminGroup(User* user);

};
