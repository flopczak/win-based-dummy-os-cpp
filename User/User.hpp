#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Acl.hpp"

using namespace std;
class User {

private:
	string username; 
	string password;
	string SID;			// security ID (one per account/group)
	static string currentLoggedUser;
				
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
	void createUser();

	static void printUser(User* user);
	static void logOut();
	static void logIn();
	static void deleteUser(string user);
	void changePassword();
	void generateSID();
	static bool currentLoggedGotAdminPermissions(); // Sprawdza czy obecnie zalogowana osoba jest adminem
	static User* getUserbyName(string name); // Zwraca wsk. do obiektu (przeszukiwanie po nazwie uzytkownika)
	static string getUserBySID(string sid); // zwraca nazwe uzytkownika
				//Operacje na listach
	static void viewUserList();
	static void viewStandardUserGroup();
	static void viewAdminUserGroup();
	static bool findInAdminUserGroup(string username);
	static bool findInStandardUserGroup(string username);

	static void addToUserList(User* user); // Lista wszystkich istniejacych uzytkownikow
	static void addUserToStandardUserGroup(User* user);
	static void addUserToAdminGroup(User* user);

};
