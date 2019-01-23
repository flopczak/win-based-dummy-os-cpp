#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../FileAccess/Acl.hpp"
#include "../shell/Interfejs.h"

using namespace std;
class User {

private:
	string username; 
	string password;
	string SID;			// security ID (one per account/group)
	static string currentLoggedUser;
	Interfejs* interfejs;
				
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
	void createGuest();
	void createAdmin();
	static void createUser();							//I
	static void printCurrentLoggedUser();				//I
	static void printUser(User* user);
	static void logOut();
	static void logIn();								//I 
	static void deleteUser(string user);				//I		
	void changePassword();								//I
	void generateSID();
	static bool currentLoggedGotAdminPermissions();					  // Sprawdza czy obecnie zalogowana osoba jest adminem
	static User* getUserbyName(string name);						 // Zwraca wsk. do obiektu (przeszukiwanie po nazwie uzytkownika)
	static string getUserBySID(string sid);							 // zwraca nazwe uzytkownika
				//Operacje na listach
	static void viewUserList();							//I
	static void viewStandardUserGroup();				//I
	static void viewAdminUserGroup();					//I
	static bool findInAdminUserGroup(string username);
	static bool findInStandardUserGroup(string username);
	static bool findInUserGroup(string username);
	static void addToUserList(User* user);
	static void addUserToStandardUserGroup(string username); //I				Add to Standard Group
	static void addUserToAdminGroup(string username);		//I				Add to Admin Group

	static void UserStart();										// Inicjalizacja poczatkowych parametrów

};
