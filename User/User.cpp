#include "Acl.hpp"
#include "User.hpp"
#include "Interfejs.h"
#include <random>

User::User() {}
User::User(string username, string password) 
{
	this->username = username;
	this->password = password;
	this->generateSID();
	User::addToUserList(this);
}
User::~User() {}

//Deklaracja zmiennych statycznych
string User::currentLoggedUser = "";
vector<User*> User::userList = {};
vector<User*> User::standardUserGroup = {};
vector<User*> User::adminGroup = {};

void User::createAdmin()
{
	setUsername("Adm");
	setPassword("");
	setSID("a-1");
}
void User::createGuest() {
	setUsername("Guest");
	setPassword("");
	setSID("g-1");
}

//setters
void User::setUsername(string username) 
{
	this->username = username;
}
void User::setPassword(string password) 
{
	this->password = password;
}
void User::setSID(string SID) 
{
	this->SID = SID;
}
//Statyczna funkcja do przypisania obecnie "zalogowanego" uzytkownika
void User::setCurrentLoggedUser(string SID) 
{
	User::currentLoggedUser = SID;
}

//getters
string User::getUsername() 
{
	return username;
}
string User::getPassword() 
{
	return password;
}
string User::getSID() 
{
	return SID;
}
// Statyczna funkcja do pozyskania obecnie "zalogowanego" uzytkownika
string User::getCurrentLoggedUser() 
{
	return User::currentLoggedUser;
}
//other functions
void User::createUser() 
{
	if (getCurrentLoggedUser()[0] == 'g') {
		 Interfejs::DisplayLog("\nGosc nie moze tworzyc uzytkownikow");
		return;
	}
	string temp;
	User* temporary = new User();
	 Interfejs::DisplayLog("\nPodaj nazwe uzytkownika: ");
	std::cin >> temp;
	temporary->setUsername(temp);
	 Interfejs::DisplayLog("\nPodaj haslo: ");
	std::cin >> temp;
	temporary->setPassword(temp);
	temporary->generateSID();
	User::addUserToStandardUserGroup(temporary);
	User::addToUserList(temporary);
}
void User::deleteUser(string username) 
{
	if (getCurrentLoggedUser()[0] == 'g') return;
	User* user = User::getUserbyName(username);
	if (currentLoggedGotAdminPermissions() == true) {
		if (user->getSID() == User::getCurrentLoggedUser()) {
			Interfejs::DisplayLog("\nUzytkownik jest obecnie zalogowany.");
			return;
		}
		if (user->getSID()[0] == 'a') {
			vector<User*>::iterator it;
			for (it = User::adminGroup.begin(); it != User::adminGroup.end(); it++) {
				if ((*it)->getSID() == user->getSID()) {
					User::adminGroup.erase(it);
				}
			}
		}
		if (user->getSID()[0] == 's') {
			vector<User*>::iterator it;
			for (it = User::standardUserGroup.begin(); it != User::standardUserGroup.end(); it++) {
				if ((*it)->getSID() == user->getSID()) {
					User::standardUserGroup.erase(it);
					break;
				}
			}
		}
		vector<User*>::iterator it;
		for (it = User::userList.begin(); it != User::userList.end(); it++) {
			if ((*it)->getSID() == user->getSID()) {
				User::userList.erase(it);
				break;
			}
		}
	}
	else {
		Interfejs::DisplayLog("\nWystapil blad. Brak uprawnien.");
		return;
	}
	Interfejs::DisplayLog("\nPomyslnie usunieto uzytkownika.");
	delete user;
}
void User::changePassword() 
{
	if (getCurrentLoggedUser()[0] == 'g') return;
	string check, temp;
	Interfejs::DisplayLog("\nPodaj stare haslo: ");
	std::cin >> check;
	while (check != this->getPassword()) {
		Interfejs::DisplayLog("\nBledne haslo! Sprobuj ponownie lub zakoncz wpisujac '0'.");
		std::cin >> check;
		if (check == "0") return;
	}
	Interfejs::DisplayLog("\nPodaj nowe haslo: ");
	std::cin >> temp;
	Interfejs::DisplayLog("\nPowtorz wprowadzone haslo: ");
	std::cin >> check;
	while (check != temp) {
		Interfejs::DisplayLog("\nWprowadzone hasla nie sa takie same.  Sprobuj ponownie lub zakoncz wpisujac '0'.");
		std::cin >> check;
		if (check == "0") return;
	}
	this->setPassword(temp);
	Interfejs::DisplayLog("\nPoprawnie zmieniono haslo!");
}
void User::logOut() {
	User::setCurrentLoggedUser("-1");
	Interfejs::DisplayLog("\nWylogowano.");
}
void User::logIn() {
	User::logOut();
	string temp;
	Interfejs::DisplayLog("\nPodaj nazwe uzytkownika: ");
	std::cin >> temp;
	vector<User*>::iterator it;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		if ((*it)->getUsername() == temp) {
			if ((*it)->getPassword() == "") break;
			else if ((*it)->getPassword() != "") {
				Interfejs::DisplayLog("\nPodaj haslo: ");
				std::cin >> temp;
				while (temp != (*it)->getPassword()) {
					std::cout << "\nBledne haslo! Sprobuj ponownie lub zakoncz wpisujac '0'.";
					std::cin >> temp;
					if (temp == "0") return;
				}
				break;
			}
		}
	}
	if (it == User::userList.end()) {
		std::cout << "\nBledna nazwa uzytkownika.";
		return;
	}
	User::setCurrentLoggedUser((*it)->getSID());
	std::cout << "\nPomyslnie zalogowano. Biezacy uzytkownik: "; User::printUser(*it);
	return;
}
void User::generateSID() 
{
	vector<User*>::iterator it;
	int random = rand() % 899 + 100;
	//std::cout << "Pierwszy rand: " << random;
	string strRandom = std::to_string(random);
	bool not_found = false;
	string tempSID;
	std::size_t found = 0;

	while (not_found != true) {
		for (it = User::userList.begin(); it != User::userList.end(); it++) {
			tempSID = (*it)->getSID();
			//std::cout<< "tempSID: " << tempSID << " (*it->getSID()): " << (*it)->getSID() << "\n";
			found = tempSID.find(strRandom);
			//std::cout << " found: " << found << "\n";
			if (found != std::string::npos) {
			//	std::cout << " Znalazlem! Przerywam." << std::endl;
				random = rand() % 899 + 100;
				strRandom = std::to_string(random);
			//	std::cout << "Przerwano wiec stworzylem nowy: " << strRandom;
				break;
			}
		}
		if (found == std::string::npos) {
		//	std::cout << "Za petelka, nie znalazlem wiec tworze i przydzielam!\n";
			not_found = true;
		}
	}
	this->setSID(strRandom);
}
void User::printUser(User* user) {
	string napis = "\nNazwa uzytkownika: " + user->getUsername() + " haslo: " + user->getPassword() + " SID: " + user->getSID();
	Interfejs::DisplayLog(napis);
}
bool User::currentLoggedGotAdminPermissions()
{
	string temp = User::getCurrentLoggedUser();
	vector<User*>::iterator it;
	for (it = User::adminGroup.begin(); it != User::adminGroup.end(); it++) {
		if ((*it)->getSID() == temp) return true;
	}
	return false;
}
//Operations on Lists
User* User::getUserbyName(string name) {
	vector<User*>::iterator it;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		if ((*it)->getUsername() == name) {
			return *it;
		}
	}
	return nullptr;
}
string User::getUserBySID(string sid) {
	vector<User*>::iterator it;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		if ((*it)->getSID() == sid) {
			return (*it)->getUsername();
		}
	}
	return "";
}

void User::viewUserList() 
{
	Interfejs::DisplayLog("\nLista wszystkichh uzytkownikow: ");
	vector<User*>::iterator it; string napis;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		napis = "\n| Nazwa uzytkownika: " + (*it)->getUsername() + "| Haslo: " + (*it)->getPassword() + "| SID: " + (*it)->getSID();
		Interfejs::DisplayLog(napis);
	}
}
void User::viewStandardUserGroup() 
{
	std::cout << "Lista standardowych uzytkownikow: " << std::endl;
	vector<User*>::iterator it;
	for (it = User::standardUserGroup.begin(); it != User::standardUserGroup.end(); it++) {
		std::cout << "Nazwa uzytkownika: " << (*it)->getUsername() << " SID: " << (*it)->getSID() << "\n";
	}
}
void User::viewAdminUserGroup() 
{
	std::cout << "Lista Administratorow: \n";
	vector<User*>::iterator it;
	for (it = User::adminGroup.begin(); it != User::adminGroup.end(); it++) {
		std::cout << "Nazwa uzytkownika: " << (*it)->getUsername() << " SID: " << (*it)->getSID() << "\n";
	}
}
bool User::findInAdminUserGroup(string username) {
	vector<User*>::iterator it;
	for (it = User::adminGroup.begin(); it != User::adminGroup.end(); it++) {
		if ((*it)->getUsername() == username) {
			return true;
		}
	}
	return false;
}
bool User::findInStandardUserGroup(string username) {
	vector<User*>::iterator it;
	for (it = User::standardUserGroup.begin(); it != User::standardUserGroup.end(); it++) {
		if ((*it)->getUsername() == username) {
			return true;
		}
	}
	return false;
}
bool User::findInUserGroup(string username) {
	vector<User*>::iterator it;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		if ((*it)->getUsername() == username) {
			return true;
		}
	}
	return false;
}

void User::addToUserList(User* user)
{
	User::userList.push_back(user);
}
void User::addUserToStandardUserGroup(User* user) 
{
	if (getCurrentLoggedUser()[0] == 'g') return;
	vector<User*>::iterator itS, itG;
		for (itS = User::standardUserGroup.begin(); itS != User::standardUserGroup.end(); itS++) {
			if (user->getSID() == (*itS)->getSID()) {
				std::cout << "Uzytkownik znajduje sie juz na liscie.\n"; 
				return;
			}
	}
		for(itG = User::adminGroup.begin(); itG!= User::adminGroup.end(); itG++)
		{
			if (user->getSID() == (*itG)->getSID()) {
				User::adminGroup.erase(itG);
			}
		}
		string temp = user->getSID();
		string ending;
		if (temp[0] == 'a') {
			ending.push_back(temp[2]);
			ending.push_back(temp[3]);
			ending.push_back(temp[4]);
			user->setSID("s-" + ending);
		}
		else user->setSID("s-" + user->getSID());
		User::standardUserGroup.push_back(user);
}
void User::addUserToAdminGroup(User* user) 
{
	vector<User*>::iterator itG,itS;
	if (currentLoggedGotAdminPermissions() == true) {
		for (itG = User::adminGroup.begin(); itG != User::adminGroup.end(); itG++) {
			if (user->getSID() == (*itG)->getSID()) {
				std::cout << "uzytkownik znajdujes sie juz na liscie Adminow.\n";
				return;
			}
		}
		for (itS = User::standardUserGroup.begin(); itS != User::standardUserGroup.end(); itS++) {
			if (user->getSID() == (*itS)->getSID()) {
				User::standardUserGroup.erase(itS);
				break;
			}
		}
		string temp = user->getSID();
		string ending;
		if (temp[0] == 's') {
			ending.push_back(temp[2]);
			ending.push_back(temp[3]);
			ending.push_back(temp[4]);
			user->setSID("a-" + ending);
		}
		User::adminGroup.push_back(user);
	}
	else  std::cout << "Obecnie zalogowany uzytkownik nie ma uprawnien administratora!.\n"; 
	
}

